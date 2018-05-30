#include "Handles.h"

#include <Windows.h>
#include <osg/Geode>
#include <osg/Geometry>

const osg::ref_ptr<osg::MatrixTransform>& Handles::GetRoot() const
{
	return m_Root;
}

static void HighlightSubNodes(osg::Group* node, bool highlight)
{
	osg::Geode* geode = dynamic_cast<osg::Geode*>(node);
	if (geode)
	{
		unsigned int numGeoms = geode->getNumDrawables();

		for (unsigned int geodeIdx = 0; geodeIdx < numGeoms; geodeIdx++)
		{
			osg::Geometry* curGeom = geode->getDrawable(geodeIdx)->asGeometry();

			if (curGeom)
			{
				osg::Vec4Array* colorArrays = new osg::Vec4Array();
				osg::Vec4 color;
				color.set(1.0, 0.25, 0.25, 1.0);
				colorArrays->push_back(color);
				curGeom->setColorArray(colorArrays);
				curGeom->setColorBinding(osg::Geometry::BIND_OVERALL);
			}
		}
	}
	else
	{
		unsigned int numChildren = node->getNumChildren();

		for (unsigned int nodeIdx = 0; nodeIdx < numChildren; nodeIdx++)
		{
			osg::Group* child = dynamic_cast<osg::Group*>(node->getChild(nodeIdx));
			if (child)
			{
				HighlightSubNodes(child, highlight);
			}
		}
	}
}

void Handles::ToggleHighlight(bool highlight)
{
	HighlightSubNodes(m_Root, highlight);
}

Handles::Handles()
{
	m_Root = new osg::MatrixTransform();
	this->addChild(m_Root);
}
