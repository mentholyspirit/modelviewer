#include "Logging.h"
#include "Config.h"
#include "OBJLoader.h"
#include "PickHandler.h"
#include "HandleManager.h"
#include "TranslationHandles.h"
#include <windows.h>
#include <iostream>
#include <osgViewer/Viewer>
#include <osgViewer/CompositeViewer>
#include <osgViewer/config/SingleWindow>
#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>


INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, INT nCmdShow)
{
	Config cfg;
	cfg.LoadFromFile("config.cfg");
	MVLOG(cfg.objectToLoad.c_str());


	osg::ref_ptr<osg::Group> root = new osg::Group;

	osg::ref_ptr<osg::Node> model = OBJLoader::LoadObj(cfg.objectToLoad);

	osg::ref_ptr<osg::MatrixTransform> matrixTransform = new osg::MatrixTransform();
	matrixTransform->setMatrix(osg::Matrix::scale(0.5, 0.5, 0.5));
	matrixTransform->addChild(model);
	root->addChild(matrixTransform);

	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
	traits->x = 100;
	traits->y = 100;
	traits->width = 800;
	traits->height = 800;
	traits->windowDecoration = true;
	traits->doubleBuffer = true;
	traits->sharedContext = 0;

	osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());
	osgViewer::View* view = new osgViewer::View();

	HandleManager handleManager;
	view->addEventHandler(new PickHandler(&handleManager));

	view->setSceneData(root);
	view->setUpViewAcrossAllScreens();

	osgViewer::CompositeViewer viewer;
	viewer.addView(view);

	view->getCamera()->setViewport(new osg::Viewport(0, 0, traits->width, traits->height));
	view->getCamera()->setGraphicsContext(gc.get());

	osg::ref_ptr<TranslationHandles> translationHandles = new TranslationHandles();
	handleManager.AddHandles(translationHandles);

	root->addChild(translationHandles);

	MVLOG("Loaded .obj file.");
	viewer.run();
}