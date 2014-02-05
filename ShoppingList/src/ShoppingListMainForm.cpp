#include "ShoppingListMainForm.h"
#include "AppResourceId.h"

using namespace Tizen::Base;
using namespace Tizen::App;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;


ShoppingListMainForm::ShoppingListMainForm(void)
{
}

ShoppingListMainForm::~ShoppingListMainForm(void)
{
}

bool
ShoppingListMainForm::Initialize(void)
{
	result r = Construct(IDL_FORM);
	TryReturn(r == E_SUCCESS, false, "Failed to construct form");

	return true;
}

result
ShoppingListMainForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	// TODO: Add your initialization code here
	Header* pHeader = GetHeader();
	if (pHeader)
	{
		pHeader->AddActionEventListener(*this);
	}

	// Setup back event listener
	SetFormBackEventListener(this);

	return r;
}

result
ShoppingListMainForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your termination code here
	return r;
}

void
ShoppingListMainForm::OnActionPerformed(const Tizen::Ui::Control& source, int actionId)
{
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);

	switch(actionId)
	{
	case ID_HEADER_ITEM1:
		pSceneManager->GoForward(SceneTransitionId(IDSCNT_1));
		break;
	case ID_HEADER_ITEM2:
		pSceneManager->GoForward(SceneTransitionId(IDSCNT_2));
		break;
	case ID_HEADER_ITEM3:
		pSceneManager->GoForward(SceneTransitionId(IDSCNT_3));
		break;
	default:
		break;
	}
}

void
ShoppingListMainForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source)
{
	UiApp* pApp = UiApp::GetInstance();
	AppAssert(pApp);
	pApp->Terminate();
}
