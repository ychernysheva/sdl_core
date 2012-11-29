#include "../include/JSONHandler/ALRPCObjects/RegisterAppInterface_v2_response.h"
#include "ButtonCapabilities_v2Marshaller.h"
#include "DisplayCapabilities_v2Marshaller.h"
#include "HmiZoneCapabilitiesMarshaller.h"
#include "Language_v2Marshaller.h"
#include "PresetBankCapabilitiesMarshaller.h"
#include "Result_v2Marshaller.h"
#include "SoftButtonCapabilitiesMarshaller.h"
#include "SpeechCapabilities_v2Marshaller.h"
#include "SyncMsgVersionMarshaller.h"
#include "VehicleTypeMarshaller.h"
#include "VrCapabilities_v2Marshaller.h"

#include "RegisterAppInterface_v2_responseMarshaller.h"


/*
  interface	Ford Sync RAPI
  version	1.2 / 2.0O
  date		2011-05-17 / 2012-11-02
  generated at	Thu Nov 29 14:49:08 2012
  source stamp	Thu Nov 29 06:50:10 2012
  author	robok0der
*/

using namespace NsAppLinkRPC;


bool RegisterAppInterface_v2_responseMarshaller::checkIntegrity(RegisterAppInterface_v2_response& s)
{
  return checkIntegrityConst(s);
}


bool RegisterAppInterface_v2_responseMarshaller::fromString(const std::string& s,RegisterAppInterface_v2_response& e)
{
  try
  {
    Json::Reader reader;
    Json::Value json;
    if(!reader.parse(s,json,false))  return false;
    if(!fromJSON(json,e))  return false;
  }
  catch(...)
  {
    return false;
  }
  return true;
}


const std::string RegisterAppInterface_v2_responseMarshaller::toString(const RegisterAppInterface_v2_response& e)
{
  Json::FastWriter writer;
  return checkIntegrityConst(e) ? writer.write(toJSON(e)) : "";
}


bool RegisterAppInterface_v2_responseMarshaller::checkIntegrityConst(const RegisterAppInterface_v2_response& s)
{
  if(!Result_v2Marshaller::checkIntegrityConst(s.resultCode))  return false;
  if(s.info && s.info->length()>1000)  return false;
  if(s.syncMsgVersion && !SyncMsgVersionMarshaller::checkIntegrityConst(*s.syncMsgVersion))  return false;
  if(s.language && !Language_v2Marshaller::checkIntegrityConst(*s.language))  return false;
  if(s.hmiDisplayLanguage && !Language_v2Marshaller::checkIntegrityConst(*s.hmiDisplayLanguage))  return false;
  if(s.displayCapabilities && !DisplayCapabilities_v2Marshaller::checkIntegrityConst(*s.displayCapabilities))  return false;
  if(s.buttonCapabilities)
  {
    unsigned int i=s.buttonCapabilities[0].size();
    if(i>100 || i<1)  return false;
    while(i--)
    {
    if(!ButtonCapabilities_v2Marshaller::checkIntegrityConst(s.buttonCapabilities[0][i]))   return false;
    }
  }
  if(s.softButtonCapabilities)
  {
    unsigned int i=s.softButtonCapabilities[0].size();
    if(i>100 || i<1)  return false;
    while(i--)
    {
    if(!SoftButtonCapabilitiesMarshaller::checkIntegrityConst(s.softButtonCapabilities[0][i]))   return false;
    }
  }
  if(s.presetBankCapabilities && !PresetBankCapabilitiesMarshaller::checkIntegrityConst(*s.presetBankCapabilities))  return false;
  if(s.hmiZoneCapabilities)
  {
    unsigned int i=s.hmiZoneCapabilities[0].size();
    if(i>100 || i<1)  return false;
    while(i--)
    {
    if(!HmiZoneCapabilitiesMarshaller::checkIntegrityConst(s.hmiZoneCapabilities[0][i]))   return false;
    }
  }
  if(s.speechCapabilities)
  {
    unsigned int i=s.speechCapabilities[0].size();
    if(i>100 || i<1)  return false;
    while(i--)
    {
    if(!SpeechCapabilities_v2Marshaller::checkIntegrityConst(s.speechCapabilities[0][i]))   return false;
    }
  }
  if(s.vrCapabilities)
  {
    unsigned int i=s.vrCapabilities[0].size();
    if(i>100 || i<1)  return false;
    while(i--)
    {
    if(!VrCapabilities_v2Marshaller::checkIntegrityConst(s.vrCapabilities[0][i]))   return false;
    }
  }
  if(s.vehicleType && !VehicleTypeMarshaller::checkIntegrityConst(*s.vehicleType))  return false;
  return true;
}

Json::Value RegisterAppInterface_v2_responseMarshaller::toJSON(const RegisterAppInterface_v2_response& e)
{
  Json::Value json(Json::objectValue);
  if(!checkIntegrityConst(e))
    return Json::Value(Json::nullValue);

  json["response"]=Json::Value(Json::objectValue);
  json["response"]["name"]=Json::Value("RegisterAppInterface_v2");
  json["response"]["correlationID"]=Json::Value(e.getCorrelationID());

  Json::Value j=Json::Value(Json::objectValue);

  j["success"]=Json::Value(e.success);

  j["resultCode"]=Result_v2Marshaller::toJSON(e.resultCode);

  if(e.info)
    j["info"]=Json::Value(*e.info);

  if(e.syncMsgVersion)
    j["syncMsgVersion"]=SyncMsgVersionMarshaller::toJSON(*e.syncMsgVersion);

  if(e.language)
    j["language"]=Language_v2Marshaller::toJSON(*e.language);

  if(e.hmiDisplayLanguage)
    j["hmiDisplayLanguage"]=Language_v2Marshaller::toJSON(*e.hmiDisplayLanguage);

  if(e.displayCapabilities)
    j["displayCapabilities"]=DisplayCapabilities_v2Marshaller::toJSON(*e.displayCapabilities);

  if(e.buttonCapabilities)
  {
    unsigned int sz=e.buttonCapabilities->size();
    j["buttonCapabilities"]=Json::Value(Json::arrayValue);
    j["buttonCapabilities"].resize(sz);
    for(unsigned int i=0;i<sz;i++)
      j["buttonCapabilities"][i]=ButtonCapabilities_v2Marshaller::toJSON(e.buttonCapabilities[0][i]);
  }

  if(e.softButtonCapabilities)
  {
    unsigned int sz=e.softButtonCapabilities->size();
    j["softButtonCapabilities"]=Json::Value(Json::arrayValue);
    j["softButtonCapabilities"].resize(sz);
    for(unsigned int i=0;i<sz;i++)
      j["softButtonCapabilities"][i]=SoftButtonCapabilitiesMarshaller::toJSON(e.softButtonCapabilities[0][i]);
  }

  if(e.presetBankCapabilities)
    j["presetBankCapabilities"]=PresetBankCapabilitiesMarshaller::toJSON(*e.presetBankCapabilities);

  if(e.hmiZoneCapabilities)
  {
    unsigned int sz=e.hmiZoneCapabilities->size();
    j["hmiZoneCapabilities"]=Json::Value(Json::arrayValue);
    j["hmiZoneCapabilities"].resize(sz);
    for(unsigned int i=0;i<sz;i++)
      j["hmiZoneCapabilities"][i]=HmiZoneCapabilitiesMarshaller::toJSON(e.hmiZoneCapabilities[0][i]);
  }

  if(e.speechCapabilities)
  {
    unsigned int sz=e.speechCapabilities->size();
    j["speechCapabilities"]=Json::Value(Json::arrayValue);
    j["speechCapabilities"].resize(sz);
    for(unsigned int i=0;i<sz;i++)
      j["speechCapabilities"][i]=SpeechCapabilities_v2Marshaller::toJSON(e.speechCapabilities[0][i]);
  }

  if(e.vrCapabilities)
  {
    unsigned int sz=e.vrCapabilities->size();
    j["vrCapabilities"]=Json::Value(Json::arrayValue);
    j["vrCapabilities"].resize(sz);
    for(unsigned int i=0;i<sz;i++)
      j["vrCapabilities"][i]=VrCapabilities_v2Marshaller::toJSON(e.vrCapabilities[0][i]);
  }

  if(e.vehicleType)
    j["vehicleType"]=VehicleTypeMarshaller::toJSON(*e.vehicleType);

  json["response"]["parameters"]=j;
  return json;
}


bool RegisterAppInterface_v2_responseMarshaller::fromJSON(const Json::Value& js,RegisterAppInterface_v2_response& c)
{
  if(c.info)  delete c.info;
  c.info=0;

  if(c.syncMsgVersion)  delete c.syncMsgVersion;
  c.syncMsgVersion=0;

  if(c.language)  delete c.language;
  c.language=0;

  if(c.hmiDisplayLanguage)  delete c.hmiDisplayLanguage;
  c.hmiDisplayLanguage=0;

  if(c.displayCapabilities)  delete c.displayCapabilities;
  c.displayCapabilities=0;

  if(c.buttonCapabilities)  delete c.buttonCapabilities;
  c.buttonCapabilities=0;

  if(c.softButtonCapabilities)  delete c.softButtonCapabilities;
  c.softButtonCapabilities=0;

  if(c.presetBankCapabilities)  delete c.presetBankCapabilities;
  c.presetBankCapabilities=0;

  if(c.hmiZoneCapabilities)  delete c.hmiZoneCapabilities;
  c.hmiZoneCapabilities=0;

  if(c.speechCapabilities)  delete c.speechCapabilities;
  c.speechCapabilities=0;

  if(c.vrCapabilities)  delete c.vrCapabilities;
  c.vrCapabilities=0;

  if(c.vehicleType)  delete c.vehicleType;
  c.vehicleType=0;

  try
  {
    if(!js.isObject())  return false;

    if(!js.isMember("response"))  return false;

    if(!js["response"].isObject())  return false;
    const Json::Value& j2=js["response"];

    if(!j2.isMember("name") || !j2["name"].isString() || j2["name"].asString().compare("RegisterAppInterface_v2"))  return false;
    if(!j2.isMember("correlationID") || !j2["correlationID"].isInt())  return false;
    c.setCorrelationID(j2["correlationID"].asInt());

    if(!j2.isMember("parameters"))  return false;
    const Json::Value& json=j2["parameters"];
    if(!json.isObject())  return false;
    if(!json.isMember("success"))  return false;
    {
      const Json::Value& j=json["success"];
      if(!j.isBool())  return false;
      c.success=j.asBool();
    }
    if(!json.isMember("resultCode"))  return false;
    {
      const Json::Value& j=json["resultCode"];
      if(!Result_v2Marshaller::fromJSON(j,c.resultCode))
        return false;
    }
    if(json.isMember("info"))
    {
      const Json::Value& j=json["info"];
      if(!j.isString())  return false;
      c.info=new std::string(j.asString());
    }
    if(json.isMember("syncMsgVersion"))
    {
      const Json::Value& j=json["syncMsgVersion"];
      c.syncMsgVersion=new SyncMsgVersion();
      if(!SyncMsgVersionMarshaller::fromJSON(j,c.syncMsgVersion[0]))
        return false;
    }
    if(json.isMember("language"))
    {
      const Json::Value& j=json["language"];
      c.language=new Language_v2();
      if(!Language_v2Marshaller::fromJSON(j,c.language[0]))
        return false;
    }
    if(json.isMember("hmiDisplayLanguage"))
    {
      const Json::Value& j=json["hmiDisplayLanguage"];
      c.hmiDisplayLanguage=new Language_v2();
      if(!Language_v2Marshaller::fromJSON(j,c.hmiDisplayLanguage[0]))
        return false;
    }
    if(json.isMember("displayCapabilities"))
    {
      const Json::Value& j=json["displayCapabilities"];
      c.displayCapabilities=new DisplayCapabilities_v2();
      if(!DisplayCapabilities_v2Marshaller::fromJSON(j,c.displayCapabilities[0]))
        return false;
    }
    if(json.isMember("buttonCapabilities"))
    {
      const Json::Value& j=json["buttonCapabilities"];
      if(!j.isArray())  return false;
      c.buttonCapabilities=new std::vector<ButtonCapabilities_v2>();
      c.buttonCapabilities->resize(j.size());
      for(unsigned int i=0;i<j.size();i++)
      {
        ButtonCapabilities_v2 t;
        if(!ButtonCapabilities_v2Marshaller::fromJSON(j[i],t))
          return false;
        c.buttonCapabilities[0][i]=t;
      }

    }
    if(json.isMember("softButtonCapabilities"))
    {
      const Json::Value& j=json["softButtonCapabilities"];
      if(!j.isArray())  return false;
      c.softButtonCapabilities=new std::vector<SoftButtonCapabilities>();
      c.softButtonCapabilities->resize(j.size());
      for(unsigned int i=0;i<j.size();i++)
      {
        SoftButtonCapabilities t;
        if(!SoftButtonCapabilitiesMarshaller::fromJSON(j[i],t))
          return false;
        c.softButtonCapabilities[0][i]=t;
      }

    }
    if(json.isMember("presetBankCapabilities"))
    {
      const Json::Value& j=json["presetBankCapabilities"];
      c.presetBankCapabilities=new PresetBankCapabilities();
      if(!PresetBankCapabilitiesMarshaller::fromJSON(j,c.presetBankCapabilities[0]))
        return false;
    }
    if(json.isMember("hmiZoneCapabilities"))
    {
      const Json::Value& j=json["hmiZoneCapabilities"];
      if(!j.isArray())  return false;
      c.hmiZoneCapabilities=new std::vector<HmiZoneCapabilities>();
      c.hmiZoneCapabilities->resize(j.size());
      for(unsigned int i=0;i<j.size();i++)
      {
        HmiZoneCapabilities t;
        if(!HmiZoneCapabilitiesMarshaller::fromJSON(j[i],t))
          return false;
        c.hmiZoneCapabilities[0][i]=t;
      }

    }
    if(json.isMember("speechCapabilities"))
    {
      const Json::Value& j=json["speechCapabilities"];
      if(!j.isArray())  return false;
      c.speechCapabilities=new std::vector<SpeechCapabilities_v2>();
      c.speechCapabilities->resize(j.size());
      for(unsigned int i=0;i<j.size();i++)
      {
        SpeechCapabilities_v2 t;
        if(!SpeechCapabilities_v2Marshaller::fromJSON(j[i],t))
          return false;
        c.speechCapabilities[0][i]=t;
      }

    }
    if(json.isMember("vrCapabilities"))
    {
      const Json::Value& j=json["vrCapabilities"];
      if(!j.isArray())  return false;
      c.vrCapabilities=new std::vector<VrCapabilities_v2>();
      c.vrCapabilities->resize(j.size());
      for(unsigned int i=0;i<j.size();i++)
      {
        VrCapabilities_v2 t;
        if(!VrCapabilities_v2Marshaller::fromJSON(j[i],t))
          return false;
        c.vrCapabilities[0][i]=t;
      }

    }
    if(json.isMember("vehicleType"))
    {
      const Json::Value& j=json["vehicleType"];
      c.vehicleType=new VehicleType();
      if(!VehicleTypeMarshaller::fromJSON(j,c.vehicleType[0]))
        return false;
    }

  }
  catch(...)
  {
    return false;
  }
  return checkIntegrity(c);
}

