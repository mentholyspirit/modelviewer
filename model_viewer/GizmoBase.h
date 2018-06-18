#pragma once
#include "Windows.h"
#include "HandleManager.h"
#include <osg/MatrixTransform>

class GizmoBase
{
	HandleManager* m_HandleManager;
public:
	GizmoBase(HandleManager* handleManager, osg::MatrixTransform* transformBase, const osg::Camera* camera);
};

