#include "Transform.h"
using namespace ci;
using namespace ci::app;


void tol::Transform::lookAt(const Transform & target_)
{
	Vec3f target_vec = target_.position - position;

	target_vec.normalize();

	Vec3f cross = direction.cross(target_vec);

	if (cross.lengthSquared() > 0.0f)
	{
		Quatf rotate(cross.normalized(), cross.length());

		rotation = rotation * rotate;
		direction = rotation * Vec3f(0.0f, 0.0f, 1.0f);
	}
}

void tol::Transform::lookAt(const ci::Vec2f & position_)
{

}

void tol::Transform::rotate(const ci::Vec3f& angle_)
{
	Quatf quat_x, quat_y, quat_z;

	quat_x = Quatf(Vec3f(1.0f, 0.0f, 0.0f), angle_.x);
	quat_y = Quatf(Vec3f(0.0f, 1.0f, 0.0f), angle_.y);
	quat_z = Quatf(Vec3f(0.0f, 0.0f, 1.0f), angle_.z);

	//rotation = quat_x * quat_y * quat_z;
	rotation = quat_x.toMatrix44() * quat_y.toMatrix44() * quat_z.toMatrix44();
}

void tol::Transform::rotate(ci::Vec3f axis_, float angle_)
{
	rotation = Quatf(axis_, angle_);
}

void tol::Transform::rotate(float angle_x_, float angle_y_, float angle_z_)
{

}

void tol::Transform::translateXZ(const ci::Vec3f& vector_, const float& angle_y_)
{
	position += translationXZ(vector_, angle_y_);
}

Vec3f tol::Transform::translationXZ(const ci::Vec3f & vector_, const float & angle_y_)
{
	Matrix44f my = Matrix44f(cos(angle_y_), 0, sin(angle_y_), 0,
							 0, 1, 0, 0,
							 -sin(angle_y_), 0, cos(angle_y_), 0,
							 0, 0, 0, 1);

	return my * vector_;
}

void tol::Transform::translate(const ci::Vec3f & vector_, const ci::Vec3f angle_)
{
	position += translation(vector_, angle_);
}

ci::Vec3f tol::Transform::translation(const ci::Vec3f & vector_, const ci::Vec3f & angle_)
{
	Matrix44f mx = Matrix44f(1, 0, 0, 0,
							 0, cos(angle_.x), -sin(angle_.x), 0,
							 0, sin(angle_.x), cos(angle_.x), 0,
							 0, 0, 0, 1);
	Matrix44f my = Matrix44f(cos(angle_.y), 0, sin(angle_.y), 0,
							 0, 1, 0, 0,
							 -sin(angle_.y), 0, cos(angle_.y), 0,
							 0, 0, 0, 1);
	return my * mx * vector_;
}

ci::Vec3f tol::Transform::rotateMatrix(const ci::Vec3f & angle_, float z_)
{

	Matrix44f mx = Matrix44f(1, 0, 0, 0,
							 0, cos(angle_.x), -sin(angle_.x), 0,
							 0, sin(angle_.x), cos(angle_.x), 0,
							 0, 0, 0, 1);

	Matrix44f my = Matrix44f(cos(angle_.y), 0, sin(angle_.y), 0,
							 0, 1, 0, 0,
							 -sin(angle_.y), 0, cos(angle_.y), 0,
							 0, 0, 0, 1);

	Vec3f r = Vec3f(0, 0, z_);
	Matrix44f matrix = my * mx;

	return matrix * r;
}
