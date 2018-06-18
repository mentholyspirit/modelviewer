#pragma once
#include "HandleManager.h"

#include <windows.h>
#include <osgViewer/Viewer>

class PickHandler : public osgGA::GUIEventHandler
{
private:
	HandleManager* m_HandleManager;
	bool m_MouseDown;
	osg::Vec2 m_LastMousePosition;

public:

	PickHandler(HandleManager* handleManager);

	~PickHandler() {}

	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa) override;
};

