/*
 * Matrix4Test.cpp
 *
 *  Created on: Apr 11, 2014
 *      Author: hudo
 */
#include "gtest/gtest.h"
#include "Matrix4.h"

class Matrix4Test : public ::testing::Test
{
public:

};

TEST_F(Matrix4Test, initializationIdentity)
{
	Matrix4 m1;
	bool passed = true;
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(i != j && m1.m_data[i*4 + j] != 0)
			{
				passed = false;
			}
		}
		if(m1.m_data[i*4 + i] != 1)
		{
			passed = false;
		}
	}

	ASSERT_EQ(passed,true);
}

TEST_F(Matrix4Test, identity)
{
	Matrix4 m1;
	m1.identity();
	bool passed = true;
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(i != j && m1.m_data[i*4 + j] != 0)
			{
				passed = false;
			}
		}
		if(m1.m_data[i*4 + i] != 1)
		{
			passed = false;
		}
	}

	ASSERT_EQ(passed,true);
}

TEST_F(Matrix4Test, transpose)
{
	Matrix4 m1;
	Matrix4 transposed;

	for(int i=0; i<16; i++)
	{
		m1.m_data[i] = i;
		transposed.m_data[i] = i;
	}

	transposed.transpose();

	bool passed = true;
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(m1.m_data[i*4 + j] != transposed.m_data[j*4 + i])
			{
				passed = false;
			}
		}
	}

	ASSERT_EQ(passed,true);
}

TEST_F(Matrix4Test, getTranspose)
{
	Matrix4 m1;
	Matrix4 transposed;

	for(int i=0; i<16; i++)
	{
		m1.m_data[i] = i;
	}

	transposed = m1.getTranspose();

	bool passed = true;
	for(int i=0; i<4; i++)
	{
		for(int j=0; j<4; j++)
		{
			if(m1.m_data[i*4 + j] != transposed.m_data[j*4 + i])
			{
				passed = false;
			}
		}
	}

	ASSERT_EQ(passed,true);
}

TEST_F(Matrix4Test,add)
{
	Matrix4 m1;
	Matrix4 m2;
	Matrix4 result;

	for(int i=0; i<16; i++)
	{
		m1.m_data[i] = i;
		m2.m_data[i] = 2*i;
		result.m_data[i] = 3*i;
	}

	ASSERT_EQ(result,m1 + m2);
	ASSERT_EQ(result,m2 + m1);
}

TEST_F(Matrix4Test,minus)
{
	Matrix4 m1;
	Matrix4 m2;
	Matrix4 result1;
	Matrix4 result2;

	for(int i=0; i<16; i++)
	{
		m1.m_data[i] = i;
		m2.m_data[i] = 2*i;
		result1.m_data[i] = -i;
		result2.m_data[i] = i;
	}

	ASSERT_EQ(result1,m1 - m2);
	ASSERT_EQ(result2,m2 - m1);
}

TEST_F(Matrix4Test,multiply)
{
	Matrix4 m1;
	Matrix4 m2;
	Matrix4 aux1;
	Matrix4 aux2;
	Matrix4 result1;
	Matrix4 result2;

	m1.m_data[0]  = 0.5834934; m1.m_data[1]  = 0.9720255; m1.m_data[2]  = 0.6263024; m1.m_data[3]  = 0.5695552;
	m1.m_data[4]  = 0.3113521; m1.m_data[5]  = 0.1241831; m1.m_data[6]  = 0.0086063; m1.m_data[7]  = 0.0526544;
	m1.m_data[8]  = 0.2839275; m1.m_data[9]  = 0.7394651; m1.m_data[10] = 0.0688203; m1.m_data[11] = 0.3535056;
	m1.m_data[12] = 0.2790526; m1.m_data[13] = 0.9923491; m1.m_data[14] = 0.1892270; m1.m_data[15] = 0.3986340;

	m2.m_data[0]  = 0.39233; m2.m_data[1]  = 0.48845; m2.m_data[2]  = 0.39435; m2.m_data[3]  = 0.91546;
	m2.m_data[4]  = 0.86943; m2.m_data[5]  = 0.50851; m2.m_data[6]  = 0.72616; m2.m_data[7]  = 0.78159;
	m2.m_data[8]  = 0.37471; m2.m_data[9]  = 0.69444; m2.m_data[10] = 0.58757; m2.m_data[11] = 0.29795;
	m2.m_data[12] = 0.91639; m2.m_data[13] = 0.17187; m2.m_data[14] = 0.49844; m2.m_data[15] = 0.65011;

    result1.m_data[0]  = 1.83064; result1.m_data[1]  = 1.31211; result1.m_data[2]  = 1.58783; result1.m_data[3]  = 1.85077;
    result1.m_data[4]  = 0.28160; result1.m_data[5]  = 0.23026; result1.m_data[6]  = 0.24426; result1.m_data[7]  = 0.41889;
    result1.m_data[8]  = 1.10404; result1.m_data[9]  = 0.62326; result1.m_data[10] = 0.86558; result1.m_data[11] = 1.08820;
    result1.m_data[12] = 1.40847; result1.m_data[13] = 0.84084; result1.m_data[14] = 1.14053; result1.m_data[15] = 1.34661;

    result2.m_data[0]  = 0.74843; result2.m_data[1]  = 1.64207; result2.m_data[2]  = 0.45029; result2.m_data[3]  = 0.75351;
	result2.m_data[4]  = 1.08992; result2.m_data[5]  = 2.22084; result2.m_data[6]  = 0.74678; result2.m_data[7]  = 1.09024;
	result2.m_data[8]  = 0.68482; result2.m_data[9]  = 1.18062; result2.m_data[10] = 0.33747; result2.m_data[11] = 0.57646;
	result2.m_data[12] = 0.91115; result2.m_data[13] = 1.92581; result2.m_data[14] = 0.73274; result2.m_data[15] = 0.96634;

	aux1 = m1 * m2;
	aux2 = m2 * m1;

	for(int i=0; i<16; i++)
	{
		ASSERT_NEAR(result1.m_data[i],aux1.m_data[i],0.00001);
		ASSERT_NEAR(result2.m_data[i],aux2.m_data[i],0.00001);
	}
}








