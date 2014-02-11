#ifndef _SHOPPING_LIST_MAIN_FORM_H_
#define _SHOPPING_LIST_MAIN_FORM_H_

#include "tizenx.h"
#include "Db/DbAccess.h"

class ShoppingListMainForm
	: public Tizen::Ui::Controls::Form
	, public Tizen::Ui::IActionEventListener
	, public Tizen::Ui::Controls::IFormBackEventListener,
 	public Tizen::Ui::Scenes::ISceneEventListener
{
public:
	ShoppingListMainForm(void);
	virtual ~ShoppingListMainForm(void);
	bool Initialize(void);

private:
	Db::DbAccess* pDb;

	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

protected:
	static const int ID_HEADER_ITEM1 = 101;
	static const int ID_HEADER_ITEM2 = 102;
	static const int ID_HEADER_ITEM3 = 103;

	virtual void OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								   const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs);
	virtual void OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
									const Tizen::Ui::Scenes::SceneId& nextSceneId);
};

#endif	//_SHOPPING_LIST_MAIN_FORM_H_
