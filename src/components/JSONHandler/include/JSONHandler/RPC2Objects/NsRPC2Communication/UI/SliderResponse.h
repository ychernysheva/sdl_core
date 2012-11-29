#ifndef NSRPC2COMMUNICATION_UI_SLIDERRESPONSE_INCLUDE
#define NSRPC2COMMUNICATION_UI_SLIDERRESPONSE_INCLUDE

#include "JSONHandler/RPC2Response.h"


/*
  interface	NsRPC2Communication::UI
  version	1.2
  generated at	Thu Nov 29 14:32:09 2012
  source stamp	Thu Nov 29 14:32:05 2012
  author	robok0der
*/

namespace NsRPC2Communication
{
  namespace UI
  {

    class SliderResponse : public ::NsRPC2Communication::RPC2Response
    {
    public:
    
      SliderResponse(const SliderResponse& c);
      SliderResponse(void);
    
      SliderResponse& operator =(const SliderResponse&);
    
      virtual ~SliderResponse(void);
    
      bool checkIntegrity(void);
    
// getters
      unsigned int get_sliderPosition(void);


// setters
/// 1 <= sliderPosition <= 26
      bool set_sliderPosition(unsigned int sliderPosition);


    private:

      friend class SliderResponseMarshaller;

      unsigned int sliderPosition;

    };
  }
}

#endif
