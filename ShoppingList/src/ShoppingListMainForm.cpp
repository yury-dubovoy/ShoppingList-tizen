#include "ShoppingListMainForm.h"
#include "AppResourceId.h"

using namespace Db;
using namespace Tizen::Base;
using namespace Tizen::App;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;


ShoppingListMainForm::ShoppingListMainForm(void)
{
	pDb = null;
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

	pDb = new DbAccess();
	r = pDb->Construct();
	if (IsFailed(r))
	{
		AppLogDebug("ERROR: cannot construct DbAccess! [%s]", GetErrorMessage(r));
		return r;
	}

	String strDbName = "lists.sqlite";

	r = pDb->Connect(strDbName);
	if (IsFailed(r))
	{
		AppLogDebug("ERROR: cannot connect %S! [%s]", strDbName.GetPointer(), GetErrorMessage(r));
		return r;
	}

	return r;
}

result
ShoppingListMainForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	r = pDb->Close();
	if (IsFailed(r))
	{
		AppLogDebug("ERROR: cannot close DbAccess! [%s]", GetErrorMessage(r));
		return r;
	}

	delete pDb; pDb = null;

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

void
ShoppingListMainForm::OnSceneActivatedN(const Tizen::Ui::Scenes::SceneId& previousSceneId,
								const Tizen::Ui::Scenes::SceneId& currentSceneId, Tizen::Base::Collection::IList* pArgs)
{
	// TODO: Add your implementation codes here

}

void
ShoppingListMainForm::OnSceneDeactivated(const Tizen::Ui::Scenes::SceneId& currentSceneId,
								const Tizen::Ui::Scenes::SceneId& nextSceneId)
{
	// TODO: Add your implementation codes here

}
