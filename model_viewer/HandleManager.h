#pragma once
#include "GizmoHandle.h"
#include <vector>
#include <osgGA/GUIEventAdapter>

class HandleManager
{
private:
	std::vector<GizmoHandle*> m_Handles;
	GizmoHandle* m_HighlightedHandle;
	void DisableHighlights();

public:
	void AddHandle(GizmoHandle* Handle);
	bool HighlightPick(const osg::NodePath* nodePath);
	bool IsHandleHighlighted() const;
	void Drag(const osgGA::GUIEventAdapter& ea, osg::Vec2 mouseDelta);
};

