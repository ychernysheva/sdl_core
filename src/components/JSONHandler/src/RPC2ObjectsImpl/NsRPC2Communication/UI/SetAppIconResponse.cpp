#include "../src/../include/JSONHandler/RPC2Objects/NsRPC2Communication/UI/SetAppIconResponse.h"
#include "../src/../include/JSONHandler/RPC2Objects/Marshaller.h"

/*
  interface	NsRPC2Communication::UI
  version	1.2
  generated at	Thu Nov 29 14:32:09 2012
  source stamp	Thu Nov 29 14:32:05 2012
  author	robok0der
*/

using namespace NsRPC2Communication::UI;


SetAppIconResponse& SetAppIconResponse::operator =(const SetAppIconResponse& c)
{
  return *this;
}


SetAppIconResponse::~SetAppIconResponse(void)
{
}


SetAppIconResponse::SetAppIconResponse(void) : 
  RPC2Response(Marshaller::METHOD_NSRPC2COMMUNICATION_UI__SETAPPICONRESPONSE)
{
}


SetAppIconResponse::SetAppIconResponse(const SetAppIconResponse& c) : RPC2Response(Marshaller::METHOD_NSRPC2COMMUNICATION_UI__SETAPPICONRESPONSE,c.getId(),c.getResult())
{
  *this=c;
}


bool SetAppIconResponse::checkIntegrity(void)
{
  return SetAppIconResponseMarshaller::checkIntegrity(*this);
}
