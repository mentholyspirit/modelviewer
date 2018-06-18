#pragma once
#include "Windows.h"
#include <osg/MatrixTransform>

class GizmoHandle : public osg::Group
{

private:
	osg::ref_ptr<osg::MatrixTransform> m_Root;
	osg::Vec4 m_Color;
	void HighlightSubNodes(Group* node, bool highlight);

public:
	GizmoHandle(osg::Vec4 color);
	const osg::ref_ptr<osg::MatrixTransform>& GetRoot() const;
	void Show();
	void Hide();
	void ToggleHighlight(bool highlight);
};

