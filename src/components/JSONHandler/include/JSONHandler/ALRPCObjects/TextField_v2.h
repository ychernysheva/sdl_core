#ifndef NSAPPLINKRPC_TEXTFIELD_V2_INCLUDE
#define NSAPPLINKRPC_TEXTFIELD_V2_INCLUDE


#include "CharacterSet.h"
#include "TextFieldName_v2.h"


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

  class TextField_v2
  {
  public:
  
    TextField_v2(const TextField_v2& c);
    TextField_v2(void);
  
    bool checkIntegrity(void);
  // getters

    const CharacterSet& get_characterSet(void) const;
    const TextFieldName_v2& get_name(void) const;
    unsigned int get_rows(void) const;
    unsigned int get_width(void) const;

// setters

    bool set_characterSet(const CharacterSet& characterSet_);
    bool set_name(const TextFieldName_v2& name_);
    bool set_rows(unsigned int rows_);
    bool set_width(unsigned int width_);

  private:

    friend class TextField_v2Marshaller;


///  The character set that is supported in this field. See CharacterSet.
      CharacterSet characterSet;

///  The name that identifies the field. See TextFieldName.
      TextFieldName_v2 name;

///  The number of rows of this field.
      unsigned int rows;	//!<  (1,3)

///  The number of characters in one row of this field.
      unsigned int width;	//!<  (1,500)
  };

}

#endif
