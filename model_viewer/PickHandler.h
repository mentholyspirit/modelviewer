#pragma once
#include "HandleManager.h"

#include <windows.h>
#include <osgViewer/Viewer>

class PickHandler : public osgGA::GUIEventHandler
{
private:
	HandleManager* m_HandleManager;
	bool m_MouseDown;

public:

	PickHandler(HandleManager* handleManager);

	~PickHandler() {}

	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
};

