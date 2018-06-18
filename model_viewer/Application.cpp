#include "Logging.h"
#include "Config.h"
#include "OBJLoader.h"
#include "PickHandler.h"
#include "TranslationHandle.h"
#include "HandleManager.h"
#include "GizmoBase.h"
#include <windows.h>
#include <iostream>
#include <osgViewer/Viewer>
#include <osgViewer/CompositeViewer>
#include <osgViewer/config/SingleWindow>
#include <osgDB/ReadFile>
#include <osgUtil/Optimizer>
#include <osg/Depth>
#include <osgGA/TrackballManipulator>

using namespace osg;

INT WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
	PSTR lpCmdLine, INT nCmdShow)
{
	//Load Config file
	Config cfg;
	cfg.LoadFromFile("config.cfg");
	MVLOG(cfg.objectToLoad.c_str());

	ref_ptr<Group> root = new Group;

	ref_ptr<Node> model = OBJLoader::LoadObj(cfg.objectToLoad);
	
	//Set up a MatrixTransform to be able to move the object
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

	//HandleManager controls the gizmo handle events
	HandleManager handleManager;
	view->addEventHandler(new PickHandler(&handleManager));

	view->setSceneData(root);
	view->setUpViewAcrossAllScreens();

	osgViewer::CompositeViewer viewer;
	viewer.addView(view);

	view->getCamera()->setViewport(new Viewport(0, 0, traits->width, traits->height));
	view->getCamera()->setGraphicsContext(gc.get());
	ref_ptr<osgGA::TrackballManipulator> trackballManipulator = new osgGA::TrackballManipulator();
	trackballManipulator->setAllowThrow(false);
	Vec3 eye(10.0f, 10.0f, 10.0f);
	Vec3 center(0.0f, 0.0f, 0.0f);
	Vec3 up(0.0f, 1.0f, 0.0f);
	trackballManipulator->setHomePosition(eye, center, up);
	view->setCameraManipulator(trackballManipulator);
	
	//GizmoBase creates the gizmos and attaches them to the MatrixTransorm
	GizmoBase gizmoBase(&handleManager, matrixTransform, view->getCamera());

	MVLOG("Loaded .obj file.");
	viewer.run();
}