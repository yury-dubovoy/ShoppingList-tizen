#ifndef _SHOPPING_LIST_TAB1_H_
#define _SHOPPING_LIST_TAB1_H_

#include "tizenx.h"

#include <Db/DbAccess.h>

#include "RowList.h"

class ShoppingListTab1
	: public Tizen::Ui::Controls::Panel
	, public Tizen::Ui::Scenes::ISceneEventListener
 	, public Tizen::Ui::Controls::IListViewItemEventListener
 	, public Tizen::Ui::Controls::IListViewItemProvider
	, public Db::DbRowBuilderInterface
{
public:
	ShoppingListTab1(void);
	virtual ~ShoppingListTab1(void);
	bool Initialize(void);

public:

	void
	GetLists();

	virtual Db::DbRow*
	BuildNewRowN(unsigned int tableId, unsigned int rowIndex, void* content = null) const;

	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								   const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs);
	virtual void OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
									const Tizen::Ui::Scenes::SceneId& nextSceneId);


	virtual void OnListViewContextItemStateChanged(Tizen::Ui::Controls::ListView& listView, int index, int elementId, Tizen::Ui::Controls::ListContextItemStatus status);
	virtual void OnListViewItemLongPressed(Tizen::Ui::Controls::ListView& listView, int index, int elementId, bool& invokeListViewItemCallback);
	virtual void OnListViewItemStateChanged(Tizen::Ui::Controls::ListView& listView, int index, int elementId, Tizen::Ui::Controls::ListItemStatus status);
	virtual void OnListViewItemSwept(Tizen::Ui::Controls::ListView& listView, int index, Tizen::Ui::Controls::SweepDirection direction);
	virtual Tizen::Ui::Controls::ListItemBase * 	CreateItem(int index, int itemWidth);
	virtual bool 	DeleteItem(int index, Tizen::Ui::Controls::ListItemBase *pItem, int itemWidth);
	virtual int 	GetItemCount(void);

private:

	Db::DbDataSet 							theTableLists;

	Tizen::Ui::Controls::ListView* 			pListview1;

	Tizen::Ui::Controls::ListContextItem* 	pItemContext;


};

#endif // _SHOPPING_LIST_TAB1_H_
