#include "Logging.h"
#include "Config.h"
#include "OBJLoader.h"
#include "PickHandler.h"
#include "TranslationHandle.h"
#include "HandleManager.h"
#include <windows.h>
#include <iostream>
#include <osgViewer/Viewer>
#include <osgViewer/CompositeViewer>
#include <osgViewer/config/SingleWindow>
#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>

using namespace osg;

INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, INT nCmdShow)
{
	Config cfg;
	cfg.LoadFromFile("config.cfg");
	MVLOG(cfg.objectToLoad.c_str());


	ref_ptr<Group> root = new Group;

	ref_ptr<Node> model = OBJLoader::LoadObj(cfg.objectToLoad);

	ref_ptr<MatrixTransform> matrixTransform = new MatrixTransform();
	matrixTransform->setMatrix(Matrix::scale(0.5, 0.5, 0.5));
	matrixTransform->addChild(model);
	root->addChild(matrixTransform);

	ref_ptr<GraphicsContext::Traits> traits = new GraphicsContext::Traits;
	traits->x = 100;
	traits->y = 100;
	traits->width = 640;
	traits->height = 480;
	traits->windowDecoration = true;
	traits->doubleBuffer = true;
	traits->sharedContext = 0;

	ref_ptr<GraphicsContext> gc = GraphicsContext::createGraphicsContext(traits.get());
	osgViewer::View* view = new osgViewer::View();

	HandleManager handleManager;
	view->addEventHandler(new PickHandler(&handleManager));

	view->setSceneData(root);
	view->setUpViewAcrossAllScreens();

	osgViewer::CompositeViewer viewer;
	viewer.addView(view);

	view->getCamera()->setViewport(new Viewport(0, 0, traits->width, traits->height));
	view->getCamera()->setGraphicsContext(gc.get());
	ref_ptr<TranslationHandle> translationHandle = new TranslationHandle(Vec4(1, 0, 0, 0));
	handleManager.AddHandle(translationHandle);

	root->addChild(translationHandle);

	MVLOG("Loaded .obj file.");
	viewer.run();
}