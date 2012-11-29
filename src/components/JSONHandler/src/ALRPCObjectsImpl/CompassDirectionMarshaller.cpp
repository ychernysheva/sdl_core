#include <cstring>
#include "../include/JSONHandler/ALRPCObjects/CompassDirection.h"
#include "CompassDirectionMarshaller.h"
#include "CompassDirectionMarshaller.inc"


/*
  interface	Ford Sync RAPI
  version	1.2 / 2.0O
  date		2011-05-17 / 2012-11-02
  generated at	Thu Nov 29 14:49:08 2012
  source stamp	Thu Nov 29 06:50:10 2012
  author	robok0der
*/

using namespace NsAppLinkRPC;


const CompassDirection::CompassDirectionInternal CompassDirectionMarshaller::getIndex(const char* s)
{
  if(!s)
    return CompassDirection::INVALID_ENUM;
  const struct PerfectHashTable* p=CompassDirection_intHash::getPointer(s,strlen(s));
  return p ? static_cast<CompassDirection::CompassDirectionInternal>(p->idx) : CompassDirection::INVALID_ENUM;
}


bool CompassDirectionMarshaller::fromJSON(const Json::Value& s,CompassDirection& e)
{
  e.mInternal=CompassDirection::INVALID_ENUM;
  if(!s.isString())
    return false;

  e.mInternal=getIndex(s.asString().c_str());
  return (e.mInternal!=CompassDirection::INVALID_ENUM);
}


Json::Value CompassDirectionMarshaller::toJSON(const CompassDirection& e)
{
  if(e.mInternal==CompassDirection::INVALID_ENUM) 
    return Json::Value(Json::nullValue);
  const char* s=getName(e.mInternal);
  return s ? Json::Value(s) : Json::Value(Json::nullValue);
}


bool CompassDirectionMarshaller::fromString(const std::string& s,CompassDirection& e)
{
  e.mInternal=CompassDirection::INVALID_ENUM;
  try
  {
    Json::Reader reader;
    Json::Value json;
    if(!reader.parse(s,json,false))  return false;
    if(fromJSON(json,e))  return true;
  }
  catch(...)
  {
    return false;
  }
  return false;
}

const std::string CompassDirectionMarshaller::toString(const CompassDirection& e)
{
  Json::FastWriter writer;
  return e.mInternal==CompassDirection::INVALID_ENUM ? "" : writer.write(toJSON(e));

}

const PerfectHashTable CompassDirectionMarshaller::mHashTable[8]=
{
  {"NORTH",0},
  {"NORTHWEST",1},
  {"WEST",2},
  {"SOUTHWEST",3},
  {"SOUTH",4},
  {"SOUTHEAST",5},
  {"EAST",6},
  {"NORTHEAST",7}
};
