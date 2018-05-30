#pragma once
#include "Windows.h"
#include <osg/MatrixTransform>

class Handles : public osg::Group
{

private:
	osg::ref_ptr<osg::MatrixTransform> m_Root;

public:
	Handles();
	const osg::ref_ptr<osg::MatrixTransform>& GetRoot() const;

	void Show();
	void Hide();
	void ToggleHighlight(bool highlight);
};

