#include "ShoppingListMainForm.h"
#include "AppResourceId.h"

using namespace Db;
using namespace Tizen::Base;
using namespace Tizen::App;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;

Db::DbAccess* ShoppingListMainForm::pDb = null;

static const int ID_HEADER_ITEM1 = 101;
static const int ID_HEADER_ITEM2 = 102;

static const int ID_OPTION_ADD = 201;


ShoppingListMainForm::ShoppingListMainForm(void)
{
	pDb = null;
	pOptionMenu = null;
}


ShoppingListMainForm::~ShoppingListMainForm(void)
{
}


bool
ShoppingListMainForm::Initialize(void)
{
	result r = E_SUCCESS;

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


	r = Construct(IDL_FORM);
	TryReturn(r == E_SUCCESS, false, "Failed to construct form");

	return true;
}


void
ShoppingListMainForm::LaunchNewListDialog()
{
	AppLogDebug("BUBUBUB");
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
	case ID_OPTION_ADD:
		LaunchNewListDialog();
		break;
	default:
		break;
	}
}


void
ShoppingListMainForm::OnFormBackRequested(Form& source)
{
	UiApp* pApp = UiApp::GetInstance();
	AppAssert(pApp);
	pApp->Terminate();
}


void
ShoppingListMainForm::OnFormMenuRequested(Form& source)
{
	pOptionMenu->SetShowState(true);
	pOptionMenu->Show();
}


result
ShoppingListMainForm::OnInitializing(void)
{
	result r = E_SUCCESS;

	Header* pHeader = GetHeader();
	if (pHeader)
	{
		pHeader->AddActionEventListener(*this);
	}

	SetFormBackEventListener(this);
	SetFormMenuEventListener(this);

   pOptionMenu = new (std::nothrow) OptionMenu();
   pOptionMenu->Construct();
   pOptionMenu->AddItem(L"Add a new list", ID_OPTION_ADD);
   pOptionMenu->AddActionEventListener(*this);
   pOptionMenu->SetShowState(false);

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


