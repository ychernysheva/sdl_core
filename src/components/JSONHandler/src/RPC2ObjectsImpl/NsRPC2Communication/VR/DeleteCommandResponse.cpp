#include "../src/../include/JSONHandler/RPC2Objects/NsRPC2Communication/VR/DeleteCommandResponse.h"
#include "../src/../include/JSONHandler/RPC2Objects/Marshaller.h"

/*
  interface	NsRPC2Communication::VR
  version	1.2
  generated at	Thu Nov 29 14:32:09 2012
  source stamp	Thu Nov 29 14:32:05 2012
  author	robok0der
*/

using namespace NsRPC2Communication::VR;


DeleteCommandResponse& DeleteCommandResponse::operator =(const DeleteCommandResponse& c)
{
  return *this;
}


DeleteCommandResponse::~DeleteCommandResponse(void)
{
}


DeleteCommandResponse::DeleteCommandResponse(void) : 
  RPC2Response(Marshaller::METHOD_NSRPC2COMMUNICATION_VR__DELETECOMMANDRESPONSE)
{
}


DeleteCommandResponse::DeleteCommandResponse(const DeleteCommandResponse& c) : RPC2Response(Marshaller::METHOD_NSRPC2COMMUNICATION_VR__DELETECOMMANDRESPONSE,c.getId(),c.getResult())
{
  *this=c;
}


bool DeleteCommandResponse::checkIntegrity(void)
{
  return DeleteCommandResponseMarshaller::checkIntegrity(*this);
}
