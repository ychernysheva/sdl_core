/*
 * Copyright (c) 2016, Ford Motor Company
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following
 * disclaimer in the documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of the Ford Motor Company nor the names of its contributors
 * may be used to endorse or promote products derived from this software
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 */

#include "application_manager/application_state.h"
#include "application_manager/event_engine/event_dispatcher.h"
#include "application_manager/hmi_state.h"
#include "application_manager/mock_application.h"
#include "application_manager/mock_application_manager.h"
#include "application_manager/policies/policy_handler.h"
#include "application_manager/resumption/resume_ctrl.h"
#include "application_manager/state_controller.h"
#include "gtest/gtest.h"
#include "resumption/last_state.h"

namespace test {
namespace components {
namespace application_manager_test {

using namespace application_manager;
using namespace mobile_apis;
typedef HmiState::StateID StateID;

namespace {

const WindowID kDefaultWindowId =
    mobile_apis::PredefinedWindows::DEFAULT_WINDOW;
const std::string kDefaultWindowName = "DefaultName";

std::vector<StateID> GenerateCurrentStates() {
  std::vector<StateID> states;
  states.push_back(StateID::STATE_ID_PHONE_CALL);
  states.push_back(StateID::STATE_ID_SAFETY_MODE);
  states.push_back(StateID::STATE_ID_VR_SESSION);
  states.push_back(StateID::STATE_ID_TTS_SESSION);
  states.push_back(StateID::STATE_ID_VIDEO_STREAMING);
  states.push_back(StateID::STATE_ID_DEACTIVATE_HMI);
  return states;
}
}  // namespace

class ApplicationStateTest : public ::testing::Test {
 public:
  void SetUp() OVERRIDE {
    mock_app_.reset(new MockApplication);
  }

 protected:
  static std::vector<StateID> added_states_;
  ApplicationState app_state;
  const StateID current_id = StateID::STATE_ID_CURRENT;
  const StateID postponed_id = StateID::STATE_ID_POSTPONED;
  std::shared_ptr<MockApplication> mock_app_;
  MockApplicationManager app_mngr_;
};

std::vector<StateID> ApplicationStateTest::added_states_ =
    GenerateCurrentStates();

TEST_F(ApplicationStateTest, AddStates_GetCurrentStates) {
  std::vector<StateID>::iterator new_state = added_states_.begin();
  for (; new_state != added_states_.end(); ++new_state) {
    HmiStatePtr state = std::make_shared<HmiState>(
        static_cast<std::shared_ptr<Application> >(mock_app_),
        app_mngr_,
        *new_state);
    app_state.AddState(kDefaultWindowId, state);
    EXPECT_EQ(state, app_state.GetState(kDefaultWindowId, current_id));
  }
}

TEST_F(ApplicationStateTest, AddStates_RemoveStates_GetCurrentState) {
  std::vector<StateID>::iterator new_state = added_states_.begin();
  for (; new_state != added_states_.end(); ++new_state) {
    HmiStatePtr state = std::make_shared<HmiState>(
        static_cast<std::shared_ptr<Application> >(mock_app_),
        app_mngr_,
        *new_state);
    app_state.AddState(kDefaultWindowId, state);

    HmiStatePtr curr_state = app_state.GetState(kDefaultWindowId, current_id);
    ASSERT_EQ(*new_state, curr_state->state_id());
  }

  new_state = added_states_.end() - 1;
  while (new_state != added_states_.begin()) {
    app_state.RemoveState(kDefaultWindowId, *new_state);
    HmiStatePtr curr_state = app_state.GetState(kDefaultWindowId, current_id);
    --new_state;
    EXPECT_EQ(*new_state, curr_state->state_id());
  }
}

TEST_F(ApplicationStateTest, AddStatesAddPostponedState_GetPostponedState) {
  // Added some states
  std::vector<StateID>::iterator new_state = added_states_.begin();
  for (; new_state != added_states_.end(); ++new_state) {
    HmiStatePtr state = std::make_shared<HmiState>(
        static_cast<std::shared_ptr<Application> >(mock_app_),
        app_mngr_,
        *new_state);
    app_state.AddState(kDefaultWindowId, state);
  }
  // Postponed state wasn't added
  HmiStatePtr get_postponed_id =
      app_state.GetState(kDefaultWindowId, postponed_id);
  EXPECT_EQ(nullptr, get_postponed_id);
  // Add posponed state
  HmiStatePtr state = std::make_shared<HmiState>(
      static_cast<std::shared_ptr<Application> >(mock_app_),
      app_mngr_,
      postponed_id);
  app_state.AddState(kDefaultWindowId, state);
  // Postponed state exists
  get_postponed_id = app_state.GetState(kDefaultWindowId, postponed_id);
  EXPECT_EQ(state, get_postponed_id);
}

TEST_F(ApplicationStateTest, AddStates_GetRegularState) {
  // Add state
  std::vector<StateID>::iterator new_state = added_states_.begin();
  HmiStatePtr state = std::make_shared<HmiState>(
      static_cast<std::shared_ptr<Application> >(mock_app_),
      app_mngr_,
      *new_state);
  state->set_hmi_level(HMILevel::HMI_FULL);
  app_state.AddState(kDefaultWindowId, state);
  ++new_state;
  // Add some other
  for (; new_state != added_states_.end(); ++new_state) {
    state = std::make_shared<HmiState>(
        static_cast<std::shared_ptr<Application> >(mock_app_),
        app_mngr_,
        *new_state);
    app_state.AddState(kDefaultWindowId, state);
    state->set_hmi_level(HMILevel::HMI_LIMITED);
  }

  // Regular state will be the first added state
  new_state = added_states_.begin();
  HmiStatePtr reg_state =
      app_state.GetState(kDefaultWindowId, StateID::STATE_ID_REGULAR);
  EXPECT_EQ(*new_state, reg_state->state_id());
  EXPECT_EQ(HMILevel::HMI_FULL, reg_state->hmi_level());
}

TEST_F(ApplicationStateTest, AddRegularState_RemoveFirstState_GetRegularState) {
  std::vector<StateID>::iterator new_state = added_states_.begin();
  HmiStatePtr state = std::make_shared<HmiState>(
      static_cast<std::shared_ptr<Application> >(mock_app_),
      app_mngr_,
      *new_state);
  app_state.AddState(kDefaultWindowId, state);
  ++new_state;

  // Add postponed state
  state = std::make_shared<HmiState>(
      static_cast<std::shared_ptr<Application> >(mock_app_),
      app_mngr_,
      postponed_id);
  app_state.AddState(kDefaultWindowId, state);

  // Make sure that the state was added
  HmiStatePtr post_state = app_state.GetState(kDefaultWindowId, postponed_id);
  ASSERT_EQ(state, post_state);

  for (; new_state != added_states_.end(); ++new_state) {
    state = std::make_shared<HmiState>(
        static_cast<std::shared_ptr<Application> >(mock_app_),
        app_mngr_,
        *new_state);
    app_state.AddState(kDefaultWindowId, state);
  }

  // Regular state will be the first added state
  new_state = added_states_.begin();
  HmiStatePtr reg_state =
      app_state.GetState(kDefaultWindowId, StateID::STATE_ID_REGULAR);
  ASSERT_EQ(*new_state, reg_state->state_id());

  app_state.RemoveState(kDefaultWindowId, *new_state);

  ++new_state;
  // Now regular state is the next state except postponed
  reg_state = app_state.GetState(kDefaultWindowId, StateID::STATE_ID_REGULAR);
  EXPECT_EQ(*new_state, reg_state->state_id());
}

TEST_F(ApplicationStateTest, AddRegularState_PreviousStatePostponed) {
  // Add some state
  StateID first_state = StateID::STATE_ID_PHONE_CALL;
  HmiStatePtr state = std::make_shared<HmiState>(
      static_cast<std::shared_ptr<Application> >(mock_app_),
      app_mngr_,
      first_state);
  app_state.AddState(kDefaultWindowId, state);

  // Add postponed state
  state = std::make_shared<HmiState>(
      static_cast<std::shared_ptr<Application> >(mock_app_),
      app_mngr_,
      postponed_id);
  app_state.AddState(kDefaultWindowId, state);

  // Add new postponed state
  std::shared_ptr<MockApplication> mock_app_2(new MockApplication);
  state = std::make_shared<HmiState>(
      static_cast<std::shared_ptr<Application> >(mock_app_),
      app_mngr_,
      postponed_id);
  app_state.AddState(kDefaultWindowId, state);

  // Add regular state
  state = std::make_shared<HmiState>(
      static_cast<std::shared_ptr<Application> >(mock_app_),
      app_mngr_,
      StateID::STATE_ID_REGULAR);
  app_state.AddState(kDefaultWindowId, state);

  // Postponed state is the first
  HmiStatePtr reg_state =
      app_state.GetState(kDefaultWindowId, StateID::STATE_ID_POSTPONED);
  ASSERT_EQ(postponed_id, reg_state->state_id());

  // Regular state is the second one
  reg_state = app_state.GetState(kDefaultWindowId, StateID::STATE_ID_REGULAR);
  EXPECT_EQ(StateID::STATE_ID_REGULAR, reg_state->state_id());
}

TEST_F(ApplicationStateTest, InitState_GetRegularState) {
  StateID init_state = StateID::STATE_ID_REGULAR;
  HmiStatePtr state = std::make_shared<HmiState>(
      static_cast<std::shared_ptr<Application> >(mock_app_),
      app_mngr_,
      init_state);

  app_state.InitState(kDefaultWindowId, kDefaultWindowName, state);

  HmiStatePtr reg_state =
      app_state.GetState(kDefaultWindowId, StateID::STATE_ID_REGULAR);
  EXPECT_EQ(state, reg_state);

  HmiStatePtr curr_state =
      app_state.GetState(kDefaultWindowId, StateID::STATE_ID_CURRENT);
  EXPECT_EQ(state, curr_state);
}

TEST_F(ApplicationStateTest, AddPosponedState_DeletePosponedState) {
  // Precondition
  StateID init_state = StateID::STATE_ID_REGULAR;
  HmiStatePtr state = std::make_shared<HmiState>(
      static_cast<std::shared_ptr<Application> >(mock_app_),
      app_mngr_,
      init_state);
  state->set_hmi_level(mobile_apis::HMILevel::HMI_FULL);

  app_state.InitState(kDefaultWindowId, kDefaultWindowName, state);

  // Add postponed state
  state = std::make_shared<HmiState>(
      static_cast<std::shared_ptr<Application> >(mock_app_),
      app_mngr_,
      postponed_id);
  app_state.AddState(kDefaultWindowId, state);

  // Make sure that state was added
  HmiStatePtr get_postponed_state =
      app_state.GetState(kDefaultWindowId, postponed_id);
  ASSERT_EQ(state, get_postponed_state);

  // Remove postponed state
  app_state.RemoveState(kDefaultWindowId, postponed_id);

  get_postponed_state = app_state.GetState(kDefaultWindowId, postponed_id);
  EXPECT_EQ(nullptr, get_postponed_state);
}

TEST_F(ApplicationStateTest,
       AddRegularState_RemoveRegularState_RegularStateNotDeleted) {
  StateID reg_state = StateID::STATE_ID_REGULAR;
  HmiStatePtr state = std::make_shared<HmiState>(
      static_cast<std::shared_ptr<Application> >(mock_app_),
      app_mngr_,
      reg_state);
  app_state.InitState(kDefaultWindowId, kDefaultWindowName, state);

  // Try deleting regular state
  app_state.RemoveState(kDefaultWindowId, reg_state);

  // Get regular state
  HmiStatePtr get_reg_state = app_state.GetState(kDefaultWindowId, reg_state);
  EXPECT_EQ(state, get_reg_state);
}

}  // namespace application_manager_test
}  // namespace components
}  // namespace test
