#ifndef _SHOPPING_LIST_FRAME_H_
#define _SHOPPING_LIST_FRAME_H_

#include "tizenx.h"

class ShoppingListFrame
	: public Tizen::Ui::Controls::Frame
{
public:
	ShoppingListFrame(void);
	virtual ~ShoppingListFrame(void);

private:
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
};

#endif	//_SHOPPING_LIST_FRAME_H_
