#pragma once
#include "GizmoHandle.h"

class TranslationHandle : public GizmoHandle
{
private:
	osg::Vec3 m_Direction;
public:
	TranslationHandle(osg::Vec3 direction, osg::Vec4 color);
	void Drag(const osgGA::GUIEventAdapter& ea, osg::Vec2 mouseDelta) override;
};

