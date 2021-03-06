#include "OBJLoader.h"
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Vec3>
#include <osg/PolygonStipple>
#include <osgUtil/SmoothingVisitor>
#include <fstream>
#include <sstream>
#include <vector>


using namespace osg;

template<typename Out>
void split(const std::string &s, char delim, Out result)
{
	std::stringstream ss(s);
	std::string item;
	while (std::getline(ss, item, delim))
	{
		*(result++) = item;
	}
}

ref_ptr<Node> OBJLoader::LoadObj(const std::string& path)
{
	std::ifstream file(path);
	if (!file.is_open())
		return NULL;

	Geode* geode = new Geode();

	ref_ptr<Geometry> polyGeom = new Geometry();

	ref_ptr<Vec3Array> coords = new Vec3Array();

	std::vector<unsigned short> indices;

	//if line starts with 'v', we have a vertex, if it starts with 'f', we have a triangle
	std::string line;
	std::string elems[4];
	while (getline(file, line))
	{
		split(line, ' ', elems);
		if (elems[0].compare("v") == 0)
		{
			float x = stof(elems[1]);
			float y = stof(elems[2]);
			float z = stof(elems[3]);

			coords->push_back(Vec3(x, y, z));
		}
		else if (elems[0].compare("f") == 0)
		{
			//subtract 1 because .obj indices start with 1
			int a = stoi(elems[1]) - 1;
			int b = stoi(elems[2]) - 1;
			int c = stoi(elems[3]) - 1;

			indices.push_back(a);
			indices.push_back(b);
			indices.push_back(c);
		}
	}

	polyGeom->setVertexArray(coords);

	polyGeom->addPrimitiveSet(new DrawElementsUShort(PrimitiveSet::TRIANGLES, indices.size(), indices.data()));
	geode->addDrawable(polyGeom);

	osgUtil::SmoothingVisitor sv;
	geode->accept(sv);
	file.close();

	return geode;
}
