#include "GizmoHandle.h"

#include <Windows.h>
#include <osg/Geode>
#include <osg/Geometry>

using namespace osg;

const ref_ptr<MatrixTransform>& GizmoHandle::GetRoot() const
{
	return m_Root;
}

static inline Vec4 Lerp(Vec4 a, Vec4 b, float t)
{
	return a + (b - a) * t;
}

void GizmoHandle::HighlightSubNodes(Group* node, bool highlight)
{
	Geode* geode = dynamic_cast<Geode*>(node);
	if (geode)
	{
		unsigned int numGeoms = geode->getNumDrawables();

		for (unsigned int geodeIdx = 0; geodeIdx < numGeoms; geodeIdx++)
		{
			Geometry* curGeom = geode->getDrawable(geodeIdx)->asGeometry();

			if (curGeom)
			{
				Vec4Array* colorArrays = new Vec4Array();
				Vec4 color;
				if (highlight)
				{
					color = Lerp(m_Color, Vec4(1, 1, 1, 1), 0.5f);
				}
				else
				{
					color = m_Color;
				}
				colorArrays->push_back(color);
				curGeom->setColorArray(colorArrays);
				curGeom->setColorBinding(Geometry::BIND_OVERALL);
			}
		}
	}
	else
	{
		unsigned int numChildren = node->getNumChildren();

		for (unsigned int nodeIdx = 0; nodeIdx < numChildren; nodeIdx++)
		{
			Group* child = dynamic_cast<Group*>(node->getChild(nodeIdx));
			if (child)
			{
				HighlightSubNodes(child, highlight);
			}
		}
	}
}

void GizmoHandle::ToggleHighlight(bool highlight)
{
	HighlightSubNodes(m_Root, highlight);
}

GizmoHandle::GizmoHandle(Vec4 color)
{
	m_Color = color;
	m_Root = new MatrixTransform();
	this->addChild(m_Root);
}
