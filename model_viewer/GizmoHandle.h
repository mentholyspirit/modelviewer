#pragma once
#include "Windows.h"
#include <osg/MatrixTransform>
#include <osgGA/GUIEventAdapter>

class GizmoHandle : public osg::Group
{

protected:
	osg::ref_ptr<osg::MatrixTransform> m_Root;
	osg::MatrixTransform* m_Base;
	osg::Vec4 m_Color;
	float m_MouseSensitivity;
	const osg::Camera* m_Camera;
	void HighlightSubNodes(osg::Group* node, bool highlight);
	osg::Vec3 WorldToScreenPoint(osg::Vec3 worldPoint) const;

public:
	GizmoHandle(osg::Vec4 color);
	const osg::ref_ptr<osg::MatrixTransform>& GetRoot() const;
	void Show();
	void Hide();
	void ToggleHighlight(bool highlight);
	void SetBase(osg::MatrixTransform* base);
	void SetMouseSensitivity(float sensitivity);
	void SetCamera(const osg::Camera* camera);
	virtual void Drag(const osgGA::GUIEventAdapter& ea, osg::Vec2 mouseDelta) = 0;
};

