#ifndef NSAPPLINKRPC_SPEAK_V2_REQUEST_INCLUDE
#define NSAPPLINKRPC_SPEAK_V2_REQUEST_INCLUDE

#include <vector>

#include "TTSChunk_v2.h"
#include "JSONHandler/ALRPCRequest.h"


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

///  Speaks a text.

  class Speak_v2_request : public ALRPCRequest
  {
  public:
  
    Speak_v2_request(const Speak_v2_request& c);
    Speak_v2_request(void);
    
    virtual ~Speak_v2_request(void);
  
    bool checkIntegrity(void);

    const std::vector<TTSChunk_v2>& get_ttsChunks(void) const;

    bool set_ttsChunks(const std::vector<TTSChunk_v2>& ttsChunks_);

  private:
  
    friend class Speak_v2_requestMarshaller;


/**
     An array of text chunks of type TTSChunk. See TTSChunk
     The array must have at least one item
*/
      std::vector<TTSChunk_v2> ttsChunks;	//!<   [%s..%s] 
  };

}

#endif
