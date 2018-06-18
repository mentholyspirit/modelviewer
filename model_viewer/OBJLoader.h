#pragma once
#include <Windows.h>
#include <osg/Node>
#include <string>

class OBJLoader
{
public:
	static osg::ref_ptr<osg::Node> LoadObj(const std::string& path);
};

