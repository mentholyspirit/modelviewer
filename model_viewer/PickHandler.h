#pragma once
#include "HandleManager.h"

#include <windows.h>
#include <osgViewer/Viewer>

class PickHandler : public osgGA::GUIEventHandler
{
private:
	const HandleManager* m_HandleManager;
public:

	PickHandler(const HandleManager* handleManager);

	~PickHandler() {}

	bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);
};

