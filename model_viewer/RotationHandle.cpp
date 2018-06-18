#include "RotationHandle.h"
#include <osg/Geode>
#include <osg/Geometry>

//number of segments in the pseudo torus
#define NUM_SIDES 36

using namespace osg;

inline static Geode* ConvertShapeToGeode(const Shape& shape, const TessellationHints* hints, const Vec4& color)
{
	Geode* geode = new Geode();
	geode->addDrawable(convertShapeToGeometry(shape, hints, color));
	return geode;
}

static MatrixTransform* CreateTorus(const ref_ptr<TessellationHints>& hints, Vec4 color)
{
	MatrixTransform* matrixTransform = new MatrixTransform();
	for (int i = 0; i < NUM_SIDES; i++)
	{
		float r = 8;
		ref_ptr<MatrixTransform> propTransform = new MatrixTransform();
		//create segment cylinder, add to the length half the width, so their outer sides touch each other
		ref_ptr<Cylinder> prop = new Cylinder(Vec3(0.0f, 0.0f, 0.0f), 0.4f, 2.0f * osg::PI * (r + 0.2f) / (float)NUM_SIDES);
		ref_ptr<Geode> propGeode = ConvertShapeToGeode(*prop.get(), hints.get(), color);
		//We don't need lighting for the handles
		propGeode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::OVERRIDE);
		propTransform->addChild(propGeode);
		propTransform->setMatrix(Matrix::rotate(osg::PI_2, Vec3(0, 1, 0)) * Matrix::translate(0, r, 0) * Matrix::rotate(2.0f * i * osg::PI / NUM_SIDES, Vec3(0, 0, 1)));
		matrixTransform->addChild(propTransform);
	}
	return matrixTransform;
}

RotationHandle::RotationHandle(Vec3 axis, Vec4 color) : GizmoHandle(color)
{
	//Create the torus and rotate it so that it's around the axis
	ref_ptr<TessellationHints> tessHints = new TessellationHints;
	tessHints->setCreateTextureCoords(true);
	tessHints->setDetailRatio(0.75f);
	ref_ptr<MatrixTransform> torus = CreateTorus(tessHints, color);
	Matrix rotMatrix = Matrix::rotate(Vec3(0, 0, 1), axis);
	torus->setMatrix(rotMatrix);
	GetRoot()->addChild(torus.get());
	m_Axis = axis;
}

inline static Vec2 Vec3ToVec2(Vec3 v)
{
	return Vec2(v.x(), v.y());
}

void RotationHandle::Drag(const osgGA::GUIEventAdapter& ea, Vec2 mouseDelta)
{
	//Get the signed angle between the new and the old mouse position relative to the object's centre
	Vec3 position = m_Base->getMatrix().getTrans();
	Vec2 screenPos = Vec3ToVec2(WorldToScreenPoint(position));
	Vec2 newPos = Vec2(ea.getX(), ea.getY()) - screenPos;
	Vec2 oldPos = newPos - mouseDelta;
	float angleDiff = atan2(newPos.y(), newPos.x()) - atan2(oldPos.y(), oldPos.x());
	//atan2 returns a value between -π and π, so the difference between the two results can be wrong if one of them turns around, subtract 2π to fix that
	if (abs(angleDiff) > osg::PIf)
		angleDiff -= 2.0f * osg::PIf * sign(angleDiff);
	Matrix matrix = m_Base->getMatrix();
	matrix = Matrix::rotate(angleDiff, m_Axis * sign(m_Axis * (matrix * m_Axis))) * matrix;
	m_Base->setMatrix(matrix);
}
