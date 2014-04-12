/*
 * Vec3Test.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: hudo
 */

#include <cmath>

#include "gtest/gtest.h"
#include "Vec3.h"

class Vec3Test : public ::testing::Test
{
public:

};

TEST_F(Vec3Test, dotProduct)
{
	Vec3 v1(1,2,3);
	Vec3 v2(5,6,7);

	ASSERT_EQ(38,v1.dotProduct(v2));
	ASSERT_EQ(38,v2.dotProduct(v1));
}

TEST_F(Vec3Test, crossProduct)
{
	Vec3 v1(1,2,3);
	Vec3 v2(5,6,7);

	ASSERT_EQ(Vec3(-4,8,-4),v1.crossProduct(v2));
	ASSERT_EQ(Vec3(4,-8,4),v2.crossProduct(v1));
}

TEST_F(Vec3Test, add)
{
	Vec3 v1(1,2,3);
	Vec3 v2(5,6,7);

	ASSERT_EQ(Vec3(6,8,10),v1 + v2);
	ASSERT_EQ(Vec3(6,8,10),v2 + v1);
}

TEST_F(Vec3Test, minus)
{
	Vec3 v1(1,2,3);
	Vec3 v2(5,6,7);

	ASSERT_EQ(Vec3(-4,-4,-4),v1 - v2);
	ASSERT_EQ(Vec3(4,4,4),v2 - v1);
}

TEST_F(Vec3Test, scalarProduct)
{
	Vec3 v1(1,2,3);

	float scalar = 3;

	ASSERT_EQ(Vec3(3,6,9),v1*scalar);
	ASSERT_EQ(Vec3(3,6,9),scalar*v1);
}

TEST_F(Vec3Test, magnitude)
{
	Vec3 v1(1,2,3);

	float mag = sqrt(14);

	ASSERT_FLOAT_EQ(mag,v1.magnitude());
}


TEST_F(Vec3Test, normalize)
{
	Vec3 v1(1,2,3);
	Vec3 v2 = v1.normalize();

	ASSERT_FLOAT_EQ(1.0,v2.magnitude());
}




