#include "PickHandler.h"
#include "GizmoHandle.h"

#include <osg/Geode>
#include <osg/Geometry>


using namespace osg;

PickHandler::PickHandler(HandleManager* handleManager)
{
	m_HandleManager = handleManager;
}

inline bool Pick(HandleManager* handleManager, osgViewer::View* view, const osgGA::GUIEventAdapter& event)
{
	osgUtil::LineSegmentIntersector::Intersections intersections;
	if (view->computeIntersections(event, intersections))
	{
		osgUtil::LineSegmentIntersector::Intersection intersection = *intersections.begin();
		return handleManager->HighlightPick(&intersection.nodePath);
	}
	else
	{
		return handleManager->HighlightPick(nullptr);
	}
}


bool PickHandler::handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa)
{
	osgViewer::View* view = dynamic_cast<osgViewer::View*>(&aa);
	if (!view)
		return false;
	
	int c = ea.getEventType();
	switch (ea.getEventType())
	{
		case osgGA::GUIEventAdapter::FRAME:
		{
			return !m_MouseDown && Pick(m_HandleManager, view, ea);
		}
		case osgGA::GUIEventAdapter::DRAG:
		{
			return m_HandleManager->IsHandleHighlighted();
		}
		case (osgGA::GUIEventAdapter::PUSH):
		{
			m_MouseDown = true;
			break;
		}
		case osgGA::GUIEventAdapter::RELEASE:
		{
			m_MouseDown = false;
			break;
		}
		default:
			break;
	}
	return false;
}

	
