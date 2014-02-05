#include <new>
#include "ShoppingListPanelFactory.h"
#include "ShoppingListTab1.h"
#include "ShoppingListTab2.h"
#include "AppResourceId.h"

using namespace Tizen::Ui::Scenes;


ShoppingListPanelFactory::ShoppingListPanelFactory(void)
{
}

ShoppingListPanelFactory::~ShoppingListPanelFactory(void)
{
}

Tizen::Ui::Controls::Panel*
ShoppingListPanelFactory::CreatePanelN(const Tizen::Base::String& panelId, const Tizen::Ui::Scenes::SceneId& sceneId)
{
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);
	Tizen::Ui::Controls::Panel* pNewPanel = null;

	if (panelId == IDL_PANEL1)
	{
		ShoppingListTab1* pPanel = new (std::nothrow) ShoppingListTab1();
		pPanel->Initialize();
		pSceneManager->AddSceneEventListener(sceneId, *pPanel);
		pNewPanel = pPanel;
	}
	else
	if (panelId == IDL_PANEL2)
	{
		ShoppingListTab2* pPanel = new (std::nothrow) ShoppingListTab2();
		pPanel->Initialize();
		pSceneManager->AddSceneEventListener(sceneId, *pPanel);
		pNewPanel = pPanel;
	}
	// TODO: Add your panel creation code here
	return pNewPanel;
}
