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
		for (osgUtil::LineSegmentIntersector::Intersection intersection : intersections)
		{
			if (handleManager->HighlightPick(&intersection.nodePath))
			{
				return true;
			}
		}
		return false;
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
			m_LastMousePosition = Vec2(ea.getX(), ea.getY());
			return !m_MouseDown && Pick(m_HandleManager, view, ea);
		}
		case osgGA::GUIEventAdapter::DRAG:
		{
			if (m_HandleManager->IsHandleHighlighted())
			{
				m_HandleManager->Drag(ea, Vec2(ea.getX(), ea.getY()) - m_LastMousePosition);
				return true;
			}
			return false;
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

	
