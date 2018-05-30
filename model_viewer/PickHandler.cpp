#include "PickHandler.h"
#include "Handles.h"

#include <osg/Geode>
#include <osg/Geometry>

inline void Highlight(const osg::NodePath& nodePath)
{
	//TODO: Move this to HandleManager.Highlight()
	for (int p = nodePath.size() - 1; p >= 0; p--)
	{
		osg::Node* node = nodePath[p];
		Handles* handles = dynamic_cast<Handles*>(node);
		
		if (handles)
		{
			handles->ToggleHighlight(true);
		}
	}
}
PickHandler::PickHandler (const HandleManager* handleManager)
{
	m_HandleManager = handleManager;
}

inline void Pick(osgViewer::View* view, const osgGA::GUIEventAdapter& event)
{
	osgUtil::LineSegmentIntersector::Intersections intersections;
	if (view->computeIntersections(event, intersections))
	{
		osgUtil::LineSegmentIntersector::Intersection intersection = *intersections.begin();
		Highlight(intersection.nodePath);
	}
}


bool PickHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
	if (!view) return false;
	int c = ea.getEventType();
	switch (ea.getEventType())
	{
		case(osgGA::GUIEventAdapter::FRAME):
		{
			Pick(view, ea);
			break;
		}
		default:
			break;
	}
	return false;
}

	
