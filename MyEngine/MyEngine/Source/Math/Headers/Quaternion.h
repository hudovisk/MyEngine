/*
 * Quaternion.h
 *
 *  Created on: Apr 11, 2014
 *      Author: hudo
 */
#pragma once

#include "Vec3.h"

class Quaternion
{
public:
	Quaternion(float w, Vec3 axis);
	Quaternion();

	Quaternion& makeFromDegree(float angle, Vec3 axis);

	Quaternion& inverse();
	Quaternion getInverse() const;

	Quaternion operator*(const Quaternion& rhs) const;
	Quaternion operator+(const Quaternion& rhs) const;
	Quaternion operator-(const Quaternion& rhs) const;

	float m_w;
	Vec3 m_axis;
};
