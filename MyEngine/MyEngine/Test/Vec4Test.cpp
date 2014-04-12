/*
 * Vec4Test.cpp
 *
 *  Created on: Apr 8, 2014
 *      Author: hudo
 */

#include <cmath>

#include "gtest/gtest.h"
#include "Vec4.h"

class Vec4Test : public ::testing::Test
{
public:

};

TEST_F(Vec4Test, dotProduct4)
{
	Vec4 v1(1,2,3,4);
	Vec4 v2(5,6,7,8);

	ASSERT_EQ(70,v1.dotProduct(v2));
	ASSERT_EQ(70,v2.dotProduct(v1));
}

TEST_F(Vec4Test, dotProduct3)
{
	Vec4 v1(1,2,3,4);
	Vec4 v2(5,6,7,8);

	ASSERT_EQ(38,v1.dotProduct3(v2));
	ASSERT_EQ(38,v2.dotProduct3(v1));
}

TEST_F(Vec4Test, crossProduct)
{
	Vec4 v1(1,2,3,4);
	Vec4 v2(5,6,7,8);

	ASSERT_EQ(Vec4(-4,8,-4,0),v1.crossProduct(v2));
	ASSERT_EQ(Vec4(4,-8,4,0),v2.crossProduct(v1));
}

TEST_F(Vec4Test, add)
{
	Vec4 v1(1,2,3,4);
	Vec4 v2(5,6,7,8);

	ASSERT_EQ(Vec4(6,8,10,12),v1 + v2);
	ASSERT_EQ(Vec4(6,8,10,12),v2 + v1);
}

TEST_F(Vec4Test, minus)
{
	Vec4 v1(1,2,3,4);
	Vec4 v2(5,6,7,8);

	ASSERT_EQ(Vec4(-4,-4,-4,-4),v1 - v2);
	ASSERT_EQ(Vec4(4,4,4,4),v2 - v1);
}

TEST_F(Vec4Test, scalarProduct)
{
	Vec4 v1(1,2,3,4);
	Vec4 v2(5,6,7,8);

	float scalar = 3;

	ASSERT_EQ(Vec4(3,6,9,12),v1*scalar);
	ASSERT_EQ(Vec4(3,6,9,12),scalar*v1);
}

TEST_F(Vec4Test, magnitude)
{
	Vec4 v1(1,2,3,4);

	ASSERT_FLOAT_EQ(sqrt(30),v1.magnitude());
}

TEST_F(Vec4Test, magnitude3)
{
	Vec4 v1(1,2,3,4);

	ASSERT_FLOAT_EQ(sqrt(14),v1.magnitude3());
}

TEST_F(Vec4Test, normalize)
{
	Vec4 v1(1,2,3,4);
	Vec4 v2 = v1.normalize();
	ASSERT_FLOAT_EQ(1.0,v2.magnitude());
}

TEST_F(Vec4Test, normalize3)
{
	Vec4 v1(1,2,3,4);
	Vec4 v2 = v1.normalize3();
	Vec4 result(1/sqrt(14),2/sqrt(14),3/sqrt(14),0);
	ASSERT_FLOAT_EQ(1,v2.magnitude());
}

