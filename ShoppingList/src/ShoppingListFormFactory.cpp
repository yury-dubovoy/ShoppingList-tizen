#include <new>
#include "ShoppingListFormFactory.h"
#include "ShoppingListMainForm.h"
#include "AppResourceId.h"

using namespace Tizen::Ui::Scenes;


ShoppingListFormFactory::ShoppingListFormFactory(void)
{
}

ShoppingListFormFactory::~ShoppingListFormFactory(void)
{
}

Tizen::Ui::Controls::Form*
ShoppingListFormFactory::CreateFormN(const Tizen::Base::String& formId, const Tizen::Ui::Scenes::SceneId& sceneId)
{
	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);
	Tizen::Ui::Controls::Form* pNewForm = null;

	if (formId == IDL_FORM)
	{
		ShoppingListMainForm* pForm = new (std::nothrow) ShoppingListMainForm();
		TryReturn(pForm != null, null, "The memory is insufficient.");
		pForm->Initialize();
		pNewForm = pForm;
	}
	// TODO: Add your form creation code here

	return pNewForm;
}
