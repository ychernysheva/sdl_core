#ifndef NSAPPLINKRPC_TEXTFIELDMARSHALLER_INCLUDE
#define NSAPPLINKRPC_TEXTFIELDMARSHALLER_INCLUDE

#include <string>
#include <json/json.h>

#include "../include/JSONHandler/ALRPCObjects/TextField.h"


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

  struct TextFieldMarshaller
  {
    static bool checkIntegrity(TextField& e);
    static bool checkIntegrityConst(const TextField& e);
  
    static bool fromString(const std::string& s,TextField& e);
    static const std::string toString(const TextField& e);
  
    static bool fromJSON(const Json::Value& s,TextField& e);
    static Json::Value toJSON(const TextField& e);
  };
}

#endif
