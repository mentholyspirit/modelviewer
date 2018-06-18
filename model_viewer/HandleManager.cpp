#include "HandleManager.h"

using namespace osg;

void HandleManager::AddHandle(GizmoHandle* Handle)
{
	m_Handles.push_back(Handle);
}

bool HandleManager::HighlightPick(const NodePath* nodePath)
{
	if (nodePath != nullptr)
	{
		for (int p = nodePath->size() - 1; p >= 0; p--)
		{
			Node* node = (*nodePath)[p];
			GizmoHandle* handle = dynamic_cast<GizmoHandle*>(node);

			if (handle != nullptr)
			{
				if (m_HighlightedHandle != handle)
				{
					DisableHighlights();
					m_HighlightedHandle = handle;
					handle->ToggleHighlight(true);
				}
				return true;
			}
		}
	}
	DisableHighlights();
	return false;
}

bool HandleManager::IsHandleHighlighted() const
{
	return m_HighlightedHandle != nullptr;
}

void HandleManager::DisableHighlights()
{
	if (m_HighlightedHandle == nullptr)
		return;
	m_HighlightedHandle->ToggleHighlight(false);
	m_HighlightedHandle = nullptr;
}

void HandleManager::Drag(const osgGA::GUIEventAdapter& ea, Vec2 mouseDelta)
{
	if (m_HighlightedHandle == nullptr)
		return;
	m_HighlightedHandle->Drag(ea, mouseDelta);
}
