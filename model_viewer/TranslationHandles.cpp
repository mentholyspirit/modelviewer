#include "TranslationHandles.h"
#include <osg/Geode>
#include <osg/Geometry>

osg::Geode* convertShapeToGeode(const osg::Shape& shape, const osg::TessellationHints* hints, const osg::Vec4& color)
{
	osg::Geode* geode = new osg::Geode();
	geode->addDrawable(osg::convertShapeToGeometry(shape, hints, color));
	return geode;
}

static osg::MatrixTransform* CreateCone(const osg::ref_ptr<osg::TessellationHints>& hints)
{
	osg::ref_ptr<osg::Cone> prop = new osg::Cone(osg::Vec3(0.0f, 0.0f, 0.0f), 0.2f, 0.5f);
	osg::ref_ptr<osg::Geode> propGeode = convertShapeToGeode(*prop.get(), hints.get(), osg::Vec4(1.0f, 0.0f, 1.0f, 1.0f));
	osg::ref_ptr<osg::MatrixTransform> matrixTransform = new osg::MatrixTransform();
	matrixTransform->addChild(propGeode);
	return matrixTransform.release();
}

static osg::MatrixTransform* CreateCylinder(const osg::ref_ptr<osg::TessellationHints>& hints)
{
	osg::ref_ptr<osg::Cylinder> prop = new osg::Cylinder(osg::Vec3(0.0f, 0.0f, 0.0f), 0.1f, 1.0f);
	osg::ref_ptr<osg::Geode> propGeode = convertShapeToGeode(*prop.get(), hints.get(), osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	osg::ref_ptr<osg::MatrixTransform> matrixTransform = new osg::MatrixTransform();
	matrixTransform->addChild(propGeode);
	return matrixTransform.release();
}

TranslationHandles::TranslationHandles()
{
	osg::ref_ptr<osg::TessellationHints> tessHints = new osg::TessellationHints;
	tessHints->setCreateTextureCoords(true);
	tessHints->setDetailRatio(0.75f);
	osg::ref_ptr<osg::MatrixTransform> cone_up = CreateCone(tessHints);
	cone_up->setMatrix(osg::Matrix::translate(0.0f, 0.0f, 1.0f));
	GetRoot()->addChild(cone_up.get());
	osg::ref_ptr<osg::MatrixTransform> cylinder_up = CreateCylinder(tessHints);
	cylinder_up->setMatrix(osg::Matrix::translate(0.0f, 0.0f, 0.5f));
	GetRoot()->addChild(cylinder_up);
}
