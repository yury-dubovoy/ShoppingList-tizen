#include "ShoppingListTab3.h"
#include "AppResourceId.h"

using namespace Tizen::Graphics;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;

ShoppingListTab3::ShoppingListTab3(void)
{

}

ShoppingListTab3::~ShoppingListTab3(void)
{

}

bool
ShoppingListTab3::Initialize(void)
{
	result r = Construct(IDL_PANEL3);
	if (IsFailed(r))
	{
		return false;
	}

	return true;
}

result
ShoppingListTab3::OnInitializing(void)
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

	return r;
}

result
ShoppingListTab3::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here

	return r;
}

void
ShoppingListTab3::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs)
{
	// TODO: Activate your scene here.

}

void
ShoppingListTab3::OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
								const Tizen::Ui::Scenes::SceneId& nextSceneId)
{
	// TODO: Deactivate your scene here.

}
