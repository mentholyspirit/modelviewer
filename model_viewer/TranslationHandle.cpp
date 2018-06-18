#include "TranslationHandle.h"
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Depth>

using namespace osg;

inline static Geode* ConvertShapeToGeode(const Shape& shape, const TessellationHints* hints, const Vec4& color)
{
	Geode* geode = new Geode();
	geode->addDrawable(convertShapeToGeometry(shape, hints, color));
	return geode;
}

static MatrixTransform* CreateCone(const ref_ptr<TessellationHints>& hints, Vec4 color)
{
	ref_ptr<Cone> prop = new Cone(Vec3(0.0f, 0.0f, 4.0f), 0.4f, 1.0f);
	ref_ptr<Geode> propGeode = ConvertShapeToGeode(*prop.get(), hints.get(), color);
	ref_ptr<MatrixTransform> matrixTransform = new MatrixTransform();
	matrixTransform->addChild(propGeode);
	propGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
	//propGeode->getOrCreateStateSet()->setAttributeAndModes(new Depth(Depth::ALWAYS), osg::StateAttribute::ON);
	return matrixTransform.release();
}

static MatrixTransform* CreateCylinder(const ref_ptr<TessellationHints>& hints, Vec4 color)
{
	ref_ptr<Cylinder> prop = new Cylinder(Vec3(0.0f, 0.0f, 3.0f), 0.1f, 4.0f);
	ref_ptr<Geode> propGeode = ConvertShapeToGeode(*prop.get(), hints.get(), color);
	ref_ptr<MatrixTransform> matrixTransform = new MatrixTransform();
	matrixTransform->addChild(propGeode);
	propGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
	//propGeode->getOrCreateStateSet()->setAttributeAndModes(new Depth(Depth::ALWAYS), osg::StateAttribute::ON);
	return matrixTransform.release();
}

TranslationHandle::TranslationHandle(Vec3 direction, Vec4 color) : GizmoHandle(color)
{
	ref_ptr<TessellationHints> tessHints = new TessellationHints;
	tessHints->setCreateTextureCoords(true);
	tessHints->setDetailRatio(0.75f);
	ref_ptr<MatrixTransform> cone_up = CreateCone(tessHints, color);
	Matrix rotMatrix = Matrix::rotate(Vec3(0, 0, 1), direction);
	cone_up->setMatrix(Matrix::translate(0.0f, 0.0f, 2.0f) * rotMatrix);
	GetRoot()->addChild(cone_up.get());
	ref_ptr<MatrixTransform> cylinder_up = CreateCylinder(tessHints, color);
	cylinder_up->setMatrix(Matrix::translate(0.0f, 0.0f, 1.0f) * rotMatrix);
	GetRoot()->addChild(cylinder_up);
	m_Direction = direction;
}

void TranslationHandle::Drag(const osgGA::GUIEventAdapter& ea, Vec2 mouseDelta)
{
	//Use the dot product between the screen space projection of the axis and the mousedelta
	Vec3 position = m_Base->getMatrix().getTrans();
	Vec3 screenDirection = WorldToScreenPoint(position +  m_Base->getMatrix().getRotate() * m_Direction) - WorldToScreenPoint(position);
	Vec2 a = Vec2(screenDirection.x(), screenDirection.y());
	a.normalize();
	Vec2 b = Vec2(mouseDelta);
	b.normalize();
	float magnitude = a * b;
	Matrix matrix = m_Base->getMatrix();
	matrix = Matrix::translate(m_Direction * mouseDelta.length() * magnitude * m_MouseSensitivity) * matrix;
	m_Base->setMatrix(matrix);
}
