#include "GizmoBase.h"
#include "TranslationHandle.h"
#include "RotationHandle.h"

using namespace osg;

GizmoBase::GizmoBase(HandleManager* handleManager, MatrixTransform* transformBase, const Camera* camera)
{
	m_HandleManager = handleManager;
	
	//Set up translation handles
	ref_ptr<TranslationHandle> translationHandleX = new TranslationHandle(Vec3(1, 0, 0), Vec4(1, 0, 0, 0));
	translationHandleX->SetBase(transformBase);
	translationHandleX->SetMouseSensitivity(0.05f);
	translationHandleX->SetCamera(camera);
	handleManager->AddHandle(translationHandleX);
	transformBase->addChild(translationHandleX);

	ref_ptr<TranslationHandle> translationHandleY = new TranslationHandle(Vec3(0, 1, 0), Vec4(0, 1, 0, 0));
	translationHandleY->SetBase(transformBase);
	translationHandleY->SetMouseSensitivity(0.05f);
	translationHandleY->SetCamera(camera);
	handleManager->AddHandle(translationHandleY);
	transformBase->addChild(translationHandleY);

	ref_ptr<TranslationHandle> translationHandleZ = new TranslationHandle(Vec3(0, 0, 1), Vec4(0, 0, 1, 0));
	translationHandleZ->SetBase(transformBase);
	translationHandleZ->SetMouseSensitivity(0.05f);
	translationHandleZ->SetCamera(camera);
	handleManager->AddHandle(translationHandleZ);
	transformBase->addChild(translationHandleZ);


	//Set up rotation handles
	ref_ptr<RotationHandle> rotationHandleX = new RotationHandle(Vec3(1, 0, 0), Vec4(1, 0, 0, 0));
	rotationHandleX->SetBase(transformBase);
	rotationHandleX->SetCamera(camera);
	handleManager->AddHandle(rotationHandleX);
	transformBase->addChild(rotationHandleX);

	ref_ptr<RotationHandle> rotationHandleY = new RotationHandle(Vec3(0, 1, 0), Vec4(0, 1, 0, 0));
	rotationHandleY->SetBase(transformBase);
	rotationHandleY->SetCamera(camera);
	handleManager->AddHandle(rotationHandleY);
	transformBase->addChild(rotationHandleY);

	ref_ptr<RotationHandle> rotationHandleZ = new RotationHandle(Vec3(0, 0, 1), Vec4(0, 0, 1, 0));
	rotationHandleZ->SetBase(transformBase);
	rotationHandleZ->SetCamera(camera);
	handleManager->AddHandle(rotationHandleZ);
	transformBase->addChild(rotationHandleZ);
}
