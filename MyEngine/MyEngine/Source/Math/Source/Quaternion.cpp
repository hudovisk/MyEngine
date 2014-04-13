/*
 * Quaternion.cpp
 *
 *  Created on: Apr 12, 2014
 *      Author: hudo
 */

#include <cmath>

#include "Quaternion.h"

const float PIdiv180 = 0.017453;

Quaternion::Quaternion(float w, Vec3 axis) :
		m_w(w), m_axis(axis)
{

}

Quaternion::Quaternion()
{
	m_w = 1;
	m_axis = Vec3(0,0,0);
}

Quaternion& Quaternion::makeFromDegree(float angle, Vec3 axis)
{
	if(axis.magnitudeSquared() != 1)
	{
		axis.normalize();
	}
	float halfAngleInRad = angle*0.5*PIdiv180;
	m_w = cos(halfAngleInRad);
	m_axis = axis * sin(halfAngleInRad);

	return *this;
}

Quaternion& Quaternion::inverse()
{
	m_axis.inverse();

	return *this;
}

Quaternion Quaternion::getInverse()const
{
	return Quaternion(m_w,m_axis.getInverse());
}

Quaternion Quaternion::operator*(const Quaternion& rhs) const
{
	float w = m_w * rhs.m_w - m_axis.dotProduct(rhs.m_axis);
	Vec3 axis = m_w*rhs.m_axis + rhs.m_w*m_axis + m_axis.crossProduct(rhs.m_axis);
	return Quaternion(w, axis);
}

Quaternion Quaternion::operator+(const Quaternion& rhs) const
{
	return Quaternion(m_w + rhs.m_w, m_axis + rhs.m_axis);
}

Quaternion Quaternion::operator-(const Quaternion& rhs) const
{
	return Quaternion(m_w - rhs.m_w, m_axis - rhs.m_axis);
}




