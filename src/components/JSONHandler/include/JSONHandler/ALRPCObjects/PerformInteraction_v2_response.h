#ifndef NSAPPLINKRPC_PERFORMINTERACTION_V2_RESPONSE_INCLUDE
#define NSAPPLINKRPC_PERFORMINTERACTION_V2_RESPONSE_INCLUDE

#include <string>

#include "Result_v2.h"
#include "TriggerSource.h"
#include "JSONHandler/ALRPCResponse.h"


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

  class PerformInteraction_v2_response : public ALRPCResponse
  {
  public:
  
    PerformInteraction_v2_response(const PerformInteraction_v2_response& c);
    PerformInteraction_v2_response(void);
    
    virtual ~PerformInteraction_v2_response(void);
  
    PerformInteraction_v2_response& operator =(const PerformInteraction_v2_response&);
  
    bool checkIntegrity(void);

    bool get_success(void) const;
    const Result_v2& get_resultCode(void) const;
    const std::string* get_info(void) const;
    const unsigned int* get_choiceID(void) const;
    const TriggerSource* get_triggerSource(void) const;

    bool set_success(bool success_);
    bool set_resultCode(const Result_v2& resultCode_);
    void reset_info(void);
    bool set_info(const std::string& info_);
    void reset_choiceID(void);
    bool set_choiceID(unsigned int choiceID_);
    void reset_triggerSource(void);
    bool set_triggerSource(const TriggerSource& triggerSource_);

  private:
  
    friend class PerformInteraction_v2_responseMarshaller;


/**
     true, if successful
     false, if failed
*/
      bool success;

///  See Result
      Result_v2 resultCode;

///  Provides additional human readable info regarding the result.
      std::string* info;	//!< (1000)

///  ID of the choice that was selected in response to PerformInteraction.
      unsigned int* choiceID;	//!<  (0,2000000000)

///  See TriggerSource
      TriggerSource* triggerSource;
  };

}

#endif
