#include "TranslationHandle.h"
#include <osg/Geode>
#include <osg/Geometry>

using namespace osg;

Geode* convertShapeToGeode(const Shape& shape, const TessellationHints* hints, const Vec4& color)
{
	Geode* geode = new Geode();
	geode->addDrawable(convertShapeToGeometry(shape, hints, color));
	return geode;
}

static MatrixTransform* CreateCone(const ref_ptr<TessellationHints>& hints, Vec4 color)
{
	ref_ptr<Cone> prop = new Cone(Vec3(0.0f, 0.0f, 0.0f), 0.1f, 0.25f);
	ref_ptr<Geode> propGeode = convertShapeToGeode(*prop.get(), hints.get(), color);
	ref_ptr<MatrixTransform> matrixTransform = new MatrixTransform();
	matrixTransform->addChild(propGeode);
	return matrixTransform.release();
}

static MatrixTransform* CreateCylinder(const ref_ptr<TessellationHints>& hints, Vec4 color)
{
	ref_ptr<Cylinder> prop = new Cylinder(Vec3(0.0f, 0.0f, 0.0f), 0.05f, 1.0f);
	ref_ptr<Geode> propGeode = convertShapeToGeode(*prop.get(), hints.get(), color);
	ref_ptr<MatrixTransform> matrixTransform = new MatrixTransform();
	matrixTransform->addChild(propGeode);
	return matrixTransform.release();
}

TranslationHandle::TranslationHandle(Vec4 color) : GizmoHandle(color)
{
	ref_ptr<TessellationHints> tessHints = new TessellationHints;
	tessHints->setCreateTextureCoords(true);
	tessHints->setDetailRatio(0.75f);
	ref_ptr<MatrixTransform> cone_up = CreateCone(tessHints, color);
	cone_up->setMatrix(Matrix::translate(0.0f, 0.0f, 1.0f));
	GetRoot()->addChild(cone_up.get());
	ref_ptr<MatrixTransform> cylinder_up = CreateCylinder(tessHints, color);
	cylinder_up->setMatrix(Matrix::translate(0.0f, 0.0f, 0.5f));
	GetRoot()->addChild(cylinder_up);
}
