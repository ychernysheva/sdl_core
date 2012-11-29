#ifndef NSAPPLINKRPC_PERMISSIONITEMMARSHALLER_INCLUDE
#define NSAPPLINKRPC_PERMISSIONITEMMARSHALLER_INCLUDE

#include <string>
#include <json/json.h>

#include "../include/JSONHandler/ALRPCObjects/PermissionItem.h"


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

  struct PermissionItemMarshaller
  {
    static bool checkIntegrity(PermissionItem& e);
    static bool checkIntegrityConst(const PermissionItem& e);
  
    static bool fromString(const std::string& s,PermissionItem& e);
    static const std::string toString(const PermissionItem& e);
  
    static bool fromJSON(const Json::Value& s,PermissionItem& e);
    static Json::Value toJSON(const PermissionItem& e);
  };
}

#endif
