#ifndef NSAPPLINKRPC_MENUPARAMS_V2_INCLUDE
#define NSAPPLINKRPC_MENUPARAMS_V2_INCLUDE

#include <string>



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

  class MenuParams_v2
  {
  public:
  
    MenuParams_v2(const MenuParams_v2& c);
    MenuParams_v2(void);
  
    bool checkIntegrity(void);
  
    ~MenuParams_v2(void);
    MenuParams_v2& operator =(const MenuParams_v2&);

// getters

    const std::string& get_menuName(void) const;
    const unsigned int* get_parentID(void) const;
    const unsigned int* get_position(void) const;

// setters

    bool set_menuName(const std::string& menuName_);
    void reset_parentID(void);
    bool set_parentID(unsigned int parentID_);
    void reset_position(void);
    bool set_position(unsigned int position_);

  private:

    friend class MenuParams_v2Marshaller;


///  Text to show in the menu for this sub menu.
      std::string menuName;	//!< (500)

/**
     unique ID of the sub menu, the command will be added to.
     If not provided, it will be provided to the top level of the in application menu.
*/
      unsigned int* parentID;	//!<  (0,2000000000)

/**
     Position within the items that are are at top level of the in application menu.
     0 will insert at the front.
     1 will insert at the second position.
     if position is greater or equal than the number of items on top level, the sub menu will be appended to the end.
     If this param was omitted the entry will be added at the end.
*/
      unsigned int* position;	//!<  (0,1000)
  };

}

#endif
