#ifndef _SHOPPING_LIST_FORM_FACTORY_H_
#define _SHOPPING_LIST_FORM_FACTORY_H_

#include "tizenx.h"

class ShoppingListFormFactory
	: public Tizen::Ui::Scenes::IFormFactory
{
public:
	ShoppingListFormFactory(void);
	virtual ~ShoppingListFormFactory(void);

	virtual Tizen::Ui::Controls::Form* CreateFormN(const Tizen::Base::String& formId, const Tizen::Ui::Scenes::SceneId& sceneId);
};

#endif // _SHOPPING_LIST_FORM_FACTORY_H_
