#ifndef NSAPPLINKRPC_UNSUBSCRIBEBUTTON_V2_RESPONSEMARSHALLER_INCLUDE
#define NSAPPLINKRPC_UNSUBSCRIBEBUTTON_V2_RESPONSEMARSHALLER_INCLUDE

#include <string>
#include <json/json.h>

#include "../include/JSONHandler/ALRPCObjects/UnsubscribeButton_v2_response.h"


/*
  interface	Ford Sync RAPI
  version	1.2 / 2.0O
  date		2011-05-17 / 2012-11-02
  generated at	Thu Nov 29 14:49:08 2012
  source stamp	Thu Nov 29 06:50:10 2012
  author	robok0der
*/

namespace NsAppLinkRPC
{

  struct UnsubscribeButton_v2_responseMarshaller
  {
    static bool checkIntegrity(UnsubscribeButton_v2_response& e);
    static bool checkIntegrityConst(const UnsubscribeButton_v2_response& e);
  
    static bool fromString(const std::string& s,UnsubscribeButton_v2_response& e);
    static const std::string toString(const UnsubscribeButton_v2_response& e);
  
    static bool fromJSON(const Json::Value& s,UnsubscribeButton_v2_response& e);
    static Json::Value toJSON(const UnsubscribeButton_v2_response& e);
  };
}

#endif
