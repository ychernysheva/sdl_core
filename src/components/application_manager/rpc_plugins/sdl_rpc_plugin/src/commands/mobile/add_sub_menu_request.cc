/*

 Copyright (c) 2018, Ford Motor Company
 All rights reserved.

 Redistribution and use in source and binary forms, with or without
 modification, are permitted provided that the following conditions are met:

 Redistributions of source code must retain the above copyright notice, this
 list of conditions and the following disclaimer.

 Redistributions in binary form must reproduce the above copyright notice,
 this list of conditions and the following
 disclaimer in the documentation and/or other materials provided with the
 distribution.

 Neither the name of the Ford Motor Company nor the names of its contributors
 may be used to endorse or promote products derived from this software
 without specific prior written permission.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
 */

#include "sdl_rpc_plugin/commands/mobile/add_sub_menu_request.h"

#include "application_manager/application.h"
#include "application_manager/message_helper.h"
#include "utils/helpers.h"

namespace sdl_rpc_plugin {
using namespace application_manager;

namespace commands {

AddSubMenuRequest::AddSubMenuRequest(
    const application_manager::commands::MessageSharedPtr& message,
    ApplicationManager& application_manager,
    rpc_service::RPCService& rpc_service,
    HMICapabilities& hmi_capabilities,
    policy::PolicyHandlerInterface& policy_handler)
    : CommandRequestImpl(message,
                         application_manager,
                         rpc_service,
                         hmi_capabilities,
                         policy_handler) {}

AddSubMenuRequest::~AddSubMenuRequest() {}

void AddSubMenuRequest::Run() {
  LOG4CXX_AUTO_TRACE(logger_);

  ApplicationSharedPtr app = application_manager_.application(connection_key());

  if (!app) {
    LOG4CXX_ERROR(logger_, "NULL pointer");
    SendResponse(false, mobile_apis::Result::APPLICATION_NOT_REGISTERED);
    return;
  }

  smart_objects::SmartObject received_msg_params =
      (*message_)[strings::msg_params];
  mobile_apis::Result::eType verification_result =
      mobile_apis::Result::INVALID_ENUM;

  if (received_msg_params.keyExists(strings::menu_icon)) {
    verification_result = MessageHelper::VerifyImage(
        received_msg_params[strings::menu_icon], app, application_manager_);

    if (mobile_apis::Result::INVALID_DATA == verification_result) {
      LOG4CXX_ERROR(
          logger_, "MessageHelper::VerifyImage return " << verification_result);
      SendResponse(false, verification_result);
      return;
    }
  }

  const int32_t menu_id = received_msg_params[strings::menu_id].asInt();
  if (app->FindSubMenu(menu_id)) {
    LOG4CXX_ERROR(logger_, "Menu with id " << menu_id << " is not found.");
    SendResponse(false, mobile_apis::Result::INVALID_ID);
    return;
  }

  const std::string& menu_name =
      received_msg_params[strings::menu_name].asString();

  if (app->IsSubMenuNameAlreadyExist(menu_name)) {
    LOG4CXX_ERROR(logger_, "Menu name " << menu_name << " is duplicated.");
    SendResponse(false, mobile_apis::Result::DUPLICATE_NAME);
    return;
  }

  if (!CheckSubMenuName()) {
    LOG4CXX_ERROR(logger_, "Sub-menu name is not valid.");
    SendResponse(false, mobile_apis::Result::INVALID_DATA);
    return;
  }

  smart_objects::SmartObject msg_params =
      smart_objects::SmartObject(smart_objects::SmartType_Map);

  if (received_msg_params.keyExists(strings::menu_layout)) {
    auto menu_layout = static_cast<mobile_apis::MenuLayout::eType>(
        received_msg_params[strings::menu_layout].asUInt());
    if (app->menu_layout_supported(menu_layout)) {
      msg_params[strings::menu_layout] =
          received_msg_params[strings::menu_layout];
    } else {
      is_menu_layout_available_ = false;
    }
  }

  msg_params[strings::menu_id] = received_msg_params[strings::menu_id];
  if (received_msg_params.keyExists(strings::position)) {
    msg_params[strings::menu_params][strings::position] =
        received_msg_params[strings::position];
  }
  if (received_msg_params.keyExists(strings::menu_icon)) {
    msg_params[strings::menu_icon] = received_msg_params[strings::menu_icon];
  }
  msg_params[strings::menu_params][strings::menu_name] =
      received_msg_params[strings::menu_name];
  msg_params[strings::app_id] = app->app_id();

  StartAwaitForInterface(HmiInterfaces::HMI_INTERFACE_UI);
  SendHMIRequest(hmi_apis::FunctionID::UI_AddSubMenu, &msg_params, true);
}

void AddSubMenuRequest::on_event(const event_engine::Event& event) {
  LOG4CXX_AUTO_TRACE(logger_);
  const smart_objects::SmartObject& message = event.smart_object();

  switch (event.id()) {
    case hmi_apis::FunctionID::UI_AddSubMenu: {
      EndAwaitForInterface(HmiInterfaces::HMI_INTERFACE_UI);
      hmi_apis::Common_Result::eType result_code =
          static_cast<hmi_apis::Common_Result::eType>(
              message[strings::params][hmi_response::code].asInt());
      std::string response_info;
      GetInfo(message, response_info);
      const bool result = PrepareResultForMobileResponse(
          result_code, HmiInterfaces::HMI_INTERFACE_UI);

      ApplicationSharedPtr application =
          application_manager_.application(connection_key());

      if (!application) {
        LOG4CXX_ERROR(logger_, "NULL pointer");
        return;
      }

      if (result) {
        application->AddSubMenu(
            (*message_)[strings::msg_params][strings::menu_id].asInt(),
            (*message_)[strings::msg_params]);
        response_info =
            "The MenuLayout specified is unsupported, the "
            "default MenuLayout will be used." +
            response_info;
        SendResponse(result,
                     is_menu_layout_available_
                         ? MessageHelper::HMIToMobileResult(result_code)
                         : mobile_apis::Result::WARNINGS,
                     is_menu_layout_available_ ? NULL : response_info.c_str(),
                     &(message[strings::msg_params]));
      } else {
        SendResponse(result,
                     MessageHelper::HMIToMobileResult(result_code),
                     response_info.empty() ? NULL : response_info.c_str(),
                     &(message[strings::msg_params]));
      }
      break;
    }
    default: {
      LOG4CXX_ERROR(logger_, "Received unknown event" << event.id());
      return;
    }
  }
}

bool AddSubMenuRequest::Init() {
  hash_update_mode_ = HashUpdateMode::kDoHashUpdate;
  return true;
}

bool AddSubMenuRequest::CheckSubMenuName() {
  LOG4CXX_AUTO_TRACE(logger_);
  const char* str = NULL;

  str = (*message_)[strings::msg_params][strings::menu_name].asCharArray();
  if (!CheckSyntax(str)) {
    LOG4CXX_INFO(logger_, "Invalid subMenu name.");
    return false;
  }
  return true;
}

}  // namespace commands

}  // namespace sdl_rpc_plugin
