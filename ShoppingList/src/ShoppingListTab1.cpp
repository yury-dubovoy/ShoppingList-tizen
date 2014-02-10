#include "ShoppingListTab1.h"
#include "AppResourceId.h"

using namespace Tizen::Base;
using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;

static const int INDENT = 20;

ShoppingListTab1::ShoppingListTab1(void)
{

}

ShoppingListTab1::~ShoppingListTab1(void)
{

}

bool
ShoppingListTab1::Initialize(void)
{
	result r = Construct(IDL_PANEL1);
	if (IsFailed(r))
	{
		return false;
	}

	return true;
}

result
ShoppingListTab1::OnInitializing(void)
{
	result r = E_SUCCESS;

	// Layout setting
	const Form* pForm = dynamic_cast< Form* >(GetParent());
	if (pForm)
	{
		RelativeLayout* pRelativeLayout = dynamic_cast< RelativeLayout* >(pForm->GetLandscapeLayoutN());
		if (pRelativeLayout)
		{
			pRelativeLayout->SetHorizontalFitPolicy(*this, FIT_POLICY_PARENT);
			pRelativeLayout->SetVerticalFitPolicy(*this, FIT_POLICY_PARENT);
			delete pRelativeLayout;
		}
		pRelativeLayout = dynamic_cast< RelativeLayout* >(pForm->GetPortraitLayoutN());
		if (pRelativeLayout)
		{		
			pRelativeLayout->SetHorizontalFitPolicy(*this, FIT_POLICY_PARENT);
			pRelativeLayout->SetVerticalFitPolicy(*this, FIT_POLICY_PARENT);
			delete pRelativeLayout;
		}
	}

	ListView* pListview1 = static_cast<ListView*>(GetControl(IDC_LISTVIEW1));  
	if(pListview1)
	{
		pListview1->AddListViewItemEventListener(*this);
		pListview1->SetItemProvider(*this);
	}
	return r;
}

result
ShoppingListTab1::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void
ShoppingListTab1::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs)
{
	// TODO: Activate your scene here.

}

void
ShoppingListTab1::OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
								const Tizen::Ui::Scenes::SceneId& nextSceneId)
{
	// TODO: Deactivate your scene here.

}

void
ShoppingListTab1::OnListViewContextItemStateChanged(Tizen::Ui::Controls::ListView& listView, int index, int elementId, Tizen::Ui::Controls::ListContextItemStatus status)
{
	// TODO: Add your implementation codes here

}

void
ShoppingListTab1::OnListViewItemLongPressed(Tizen::Ui::Controls::ListView& listView, int index, int elementId, bool& invokeListViewItemCallback)
{
	// TODO: Add your implementation codes here

}

void
ShoppingListTab1::OnListViewItemStateChanged(Tizen::Ui::Controls::ListView& listView, int index, int elementId, Tizen::Ui::Controls::ListItemStatus status)
{
	// TODO: Add your implementation codes here

}

void
ShoppingListTab1::OnListViewItemSwept(Tizen::Ui::Controls::ListView& listView, int index, Tizen::Ui::Controls::SweepDirection direction)
{
	// TODO: Add your implementation codes here

}

Tizen::Ui::Controls::ListItemBase *
ShoppingListTab1::CreateItem(int index, int itemWidth)
{
	String strName = "Hello";

	int textWidth = GetWidth() - INDENT*2;

	EnrichedText enrichedText;
	enrichedText.Construct(FloatDimension(textWidth, 112));
	enrichedText.SetVerticalAlignment(TEXT_ALIGNMENT_MIDDLE);
	enrichedText.SetHorizontalAlignment(TEXT_ALIGNMENT_LEFT);
	enrichedText.SetTextWrapStyle(TEXT_WRAP_WORD_WRAP);

	Font pFont;
	pFont.Construct(FONT_STYLE_BOLD, 44.0f);

	TextElement* pTextElement = new (std::nothrow) TextElement();
	pTextElement->Construct(strName + "\n");
	pTextElement->SetFont(pFont);
	enrichedText.Add(*pTextElement);

	int textHeight = enrichedText.GetTotalLineHeight();

	CustomItem* pItem = new CustomItem();
	pItem->Construct(Dimension(GetWidth(), textHeight + INDENT*2), LIST_ANNEX_STYLE_NORMAL);
	pItem->AddElement(Rectangle(INDENT, INDENT, textWidth, textHeight), 0, enrichedText);

	return pItem;

}

bool
ShoppingListTab1::DeleteItem(int index, Tizen::Ui::Controls::ListItemBase *pItem, int itemWidth)
{
    delete pItem;
    pItem = null;
    return true;
}

int
ShoppingListTab1::GetItemCount(void)
{
	return 20;
}
