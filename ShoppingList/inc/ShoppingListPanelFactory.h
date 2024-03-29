#ifndef _SHOPPING_LIST_PANEL_FACTORY_H_
#define _SHOPPING_LIST_PANEL_FACTORY_H_

#include "tizenx.h"


class ShoppingListPanelFactory
	: public Tizen::Ui::Scenes::IPanelFactory
{
public:
	ShoppingListPanelFactory(void);
	virtual ~ShoppingListPanelFactory(void);

	virtual Tizen::Ui::Controls::Panel* CreatePanelN(const Tizen::Base::String& panelId, const Tizen::Ui::Scenes::SceneId& sceneId);
};

#endif // _SHOPPING_LIST_PANEL_FACTORY_H_
