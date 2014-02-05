#include "ShoppingListFrame.h"
#include "ShoppingListFormFactory.h"
#include "ShoppingListPanelFactory.h"
#include "AppResourceId.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Ui::Scenes;

ShoppingListFrame::ShoppingListFrame(void)
{
}

ShoppingListFrame::~ShoppingListFrame(void)
{
}

result
ShoppingListFrame::OnInitializing(void)
{
	
	// Prepare Scene management.
	SceneManager* pSceneManager = SceneManager::GetInstance();
	static ShoppingListFormFactory formFactory;
	static ShoppingListPanelFactory panelFactory;
	pSceneManager->RegisterFormFactory(formFactory);
	pSceneManager->RegisterPanelFactory(panelFactory);
	pSceneManager->RegisterScene(L"workflow");

	// Go to the scene.
	 result r = pSceneManager->GoForward(SceneTransitionId(IDSCNT_START));

	// TODO: Add your frame initialization code here.
	return r;
}

result
ShoppingListFrame::OnTerminating(void)
{
	result r = E_SUCCESS;

	// TODO: Add your frame termination code here.
	return r;
}
