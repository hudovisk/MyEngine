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
	Quaternion(float angle, Vec3 axis);
	Quaternion();

private:
	float m_angle;
	Vec3 m_axis;
};
