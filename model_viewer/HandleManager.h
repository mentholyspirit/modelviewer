#pragma once
#include "Handles.h"

#include <vector>

class HandleManager
{
private:
	std::vector<Handles*> m_Handles;

public:
	void AddHandles(Handles* handles);
	void Highlight();
	void Drag();
};

