#pragma once
#include "GizmoHandle.h"

class RotationHandle : public GizmoHandle
{
private:
	osg::Vec3 m_Axis;
public:
	RotationHandle(osg::Vec3 axis, osg::Vec4 color);
	void Drag(const osgGA::GUIEventAdapter& ea, osg::Vec2 mouseDelta) override;
};

