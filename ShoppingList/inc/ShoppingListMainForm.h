#ifndef _SHOPPING_LIST_MAIN_FORM_H_
#define _SHOPPING_LIST_MAIN_FORM_H_

#include "tizenx.h"

#include <Db/DbAccess.h>

class ShoppingListMainForm
	: public Tizen::Ui::Controls::Form
	, public Tizen::Ui::Controls::IFormBackEventListener
	, public Tizen::Ui::Controls::IFormMenuEventListener
	, public Tizen::Ui::IActionEventListener
 	, public Tizen::Ui::Scenes::ISceneEventListener
{


public:

	ShoppingListMainForm(void);
	virtual ~ShoppingListMainForm(void);
	bool Initialize(void);


private:

	/* Form */

	virtual result
	OnInitializing(void);

	virtual result
	OnTerminating(void);

	/* IFormBackEventListener */

	virtual void
	OnFormBackRequested(Tizen::Ui::Controls::Form& source);

	/* IFormMenuEventListener */

	virtual void
	OnFormMenuRequested(Tizen::Ui::Controls::Form& source);

	/* IActionEventListener */

	virtual void
	OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

	/* ISceneEventListener */

	virtual void
	OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId, const Tizen::Ui::Scenes::SceneId& currentSceneId,
								   Tizen::Base::Collection::IList* pArgs){}

	virtual void
	OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId, const Tizen::Ui::Scenes::SceneId& nextSceneId){}


private:

	void
	LaunchNewListDialog();


public:

	static Db::DbAccess*				pDb;


private:

	Tizen::Ui::Controls::OptionMenu* 	pOptionMenu;

};

#endif	//_SHOPPING_LIST_MAIN_FORM_H_
