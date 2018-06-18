#include "GizmoBase.h"
#include "TranslationHandle.h"

using namespace osg;

GizmoBase::GizmoBase(HandleManager* handleManager, MatrixTransform* transformBase, const Camera* camera)
{
	m_HandleManager = handleManager;
	
	ref_ptr<TranslationHandle> translationHandleX = new TranslationHandle(Vec3(1, 0, 0), Vec4(1, 0, 0, 0));
	translationHandleX->SetBase(transformBase);
	translationHandleX->SetMouseSensitivity(0.01f);
	translationHandleX->SetCamera(camera);
	handleManager->AddHandle(translationHandleX);
	transformBase->addChild(translationHandleX);

	ref_ptr<TranslationHandle> translationHandleY = new TranslationHandle(Vec3(0, 1, 0), Vec4(0, 1, 0, 0));
	translationHandleY->SetBase(transformBase);
	translationHandleY->SetMouseSensitivity(0.01f);
	translationHandleY->SetCamera(camera);
	handleManager->AddHandle(translationHandleY);
	transformBase->addChild(translationHandleY);

	ref_ptr<TranslationHandle> translationHandleZ = new TranslationHandle(Vec3(0, 0, 1), Vec4(0, 0, 1, 0));
	translationHandleZ->SetBase(transformBase);
	translationHandleZ->SetMouseSensitivity(0.01f);
	translationHandleZ->SetCamera(camera);
	handleManager->AddHandle(translationHandleZ);
	transformBase->addChild(translationHandleZ);
}
