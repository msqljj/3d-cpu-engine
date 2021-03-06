// -----------------------------------------------------------------------------
// Unit Tests for VectF3 class
// GoogleTest Framework
// -----------------------------------------------------------------------------
#include <iostream>

#include "gtest/gtest.h"
#include "math/VectF3.h"


// ----------------------------------------------------------------------------
// MACRO
// ----------------------------------------------------------------------------
#define ASSERT_VECTF3_EQ(v1, v2) \
    ASSERT_FLOAT_EQ(v1.x, v2.x); \
    ASSERT_FLOAT_EQ(v1.y, v2.y); \
    ASSERT_FLOAT_EQ(v1.z, v2.z)

#define ASSERT_VECTF3_VALUES_EQ(vect, X, Y, Z) \
    ASSERT_FLOAT_EQ(vect.x, X); \
    ASSERT_FLOAT_EQ(vect.y, Y); \
    ASSERT_FLOAT_EQ(vect.z, Z)


namespace {

// ----------------------------------------------------------------------------
// Fixture object to test VectF3
// ----------------------------------------------------------------------------
class VectF3Test : public ::testing::Test {
    protected:
        VectF3 v0;
        VectF3 v1;
        VectF3 v2;
        VectF3 v3;
    protected:
        VectF3Test()
            : v1(1.0f, 2.0f, 3.0f),
              v2(5.5f, 3.5f, -1.0f),
              v3(-10.0f, 2.1f, -2.1f){
        }
        virtual ~VectF3Test() {}
        virtual void SetUp() {}
        virtual void TearDown() {}
};


// -----------------------------------------------------------------------------
// Constructors / Setters
// -----------------------------------------------------------------------------
TEST_F(VectF3Test, constructors) {
    VectF3 vec0;
    ASSERT_VECTF3_VALUES_EQ(vec0, 0.0f, 0.0f, 0.0f);
    VectF3 vec1(42.0f);
    ASSERT_VECTF3_VALUES_EQ(vec1, 42.0f, 42.0f, 42.0f);
    VectF3 vec2(-32.0f, 89.0f, -4.2f);
    ASSERT_VECTF3_VALUES_EQ(vec2, -32.0f, 89.0f, -4.2f);
}

TEST_F(VectF3Test, setters) {
    v0.set(4, -3, 2);
    ASSERT_VECTF3_VALUES_EQ(v0, 4, -3, 2);
    v0.set(v1);
    ASSERT_VECTF3_VALUES_EQ(v0, 1, 2, 3);
}

TEST_F(VectF3Test, attributes) {
    ASSERT_TRUE(v0.x == 0);
    ASSERT_TRUE(v0.x == v0.r);
    ASSERT_TRUE(v1.x == 1.0f);
    ASSERT_TRUE(v1.x == v1.r);
    ASSERT_TRUE(v1.y == 2.0f);
    ASSERT_TRUE(v1.y == v1.g);
    ASSERT_TRUE(v1.z == 3.0f);
    ASSERT_TRUE(v1.z == v1.b);
}


// -----------------------------------------------------------------------------
// Class Functions
// -----------------------------------------------------------------------------
TEST_F(VectF3Test, length) {
    ASSERT_FLOAT_EQ(v0.length(), 0);
    ASSERT_FLOAT_EQ(v1.length(), 3.7416574);
    ASSERT_FLOAT_EQ(v2.length(), 6.595453);
    ASSERT_FLOAT_EQ(v3.length(), 10.4316825);
}

TEST_F(VectF3Test, squareLength) {
    ASSERT_FLOAT_EQ(v0.squareLength(), 0);
    ASSERT_FLOAT_EQ(v1.squareLength(), 14.0);
    ASSERT_FLOAT_EQ(v2.squareLength(), 43.5);
    ASSERT_FLOAT_EQ(v3.squareLength(), 108.82);
}

TEST_F(VectF3Test, getNormalFast) {
    ASSERT_VECTF3_VALUES_EQ(v1.getNormalFast(), 0.2672612, 0.5345225, 0.8017837);
    ASSERT_VECTF3_VALUES_EQ(v2.getNormalFast(), 0.8339078, 0.5306686, -0.1516196);
    ASSERT_VECTF3_VALUES_EQ(v3.getNormalFast(), -0.9586181, 0.2013098, -0.2013098);
}

TEST_F(VectF3Test, normalizeFast) {
    v1.normalizeFast();
    v2.normalizeFast();
    v3.normalizeFast();
    ASSERT_VECTF3_VALUES_EQ(v1, 0.2672612, 0.5345225, 0.8017837);
    ASSERT_VECTF3_VALUES_EQ(v2, 0.8339078, 0.5306686, -0.1516196);
    ASSERT_VECTF3_VALUES_EQ(v3, -0.9586181, 0.2013098, -0.2013098);
}

TEST_F(VectF3Test, getCrossProduct) {
    // v1
    ASSERT_VECTF3_VALUES_EQ(v1.getCrossProduct(v1), 0,0,0);
    ASSERT_VECTF3_VALUES_EQ(v1.getCrossProduct(v2), -12.5, 17.5, -7.5);
    ASSERT_VECTF3_VALUES_EQ(v1.getCrossProduct(v3), -10.5, -27.9, 22.1);
    // v2
    ASSERT_VECTF3_VALUES_EQ(v2.getCrossProduct(v1), 12.5, -17.5, 7.5);
    ASSERT_VECTF3_VALUES_EQ(v2.getCrossProduct(v2), 0,0,0);
    ASSERT_VECTF3_VALUES_EQ(v2.getCrossProduct(v3), -5.25, 21.55, 46.55);
    // v3
    ASSERT_VECTF3_VALUES_EQ(v3.getCrossProduct(v1), 10.5, 27.9, -22.1);
    ASSERT_VECTF3_VALUES_EQ(v3.getCrossProduct(v2), 5.25, -21.55, -46.55);
    ASSERT_VECTF3_VALUES_EQ(v3.getCrossProduct(v3), 0,0,0);
}


// -----------------------------------------------------------------------------
// Static functions
// -----------------------------------------------------------------------------
TEST_F(VectF3Test, dotProduct) {
    // v1
    ASSERT_FLOAT_EQ(VectF3::dotProduct(v1, v1), 14);
    ASSERT_FLOAT_EQ(VectF3::dotProduct(v1, v2), 9.5);
    ASSERT_FLOAT_EQ(VectF3::dotProduct(v1, v3), -12.100000000000001);
    // v2
    ASSERT_FLOAT_EQ(VectF3::dotProduct(v2, v1), 9.5);
    ASSERT_FLOAT_EQ(VectF3::dotProduct(v2, v2), 43.5);
    ASSERT_FLOAT_EQ(VectF3::dotProduct(v2, v3), -45.55);
    // v3
    ASSERT_FLOAT_EQ(VectF3::dotProduct(v3, v1), -12.100000000000001);
    ASSERT_FLOAT_EQ(VectF3::dotProduct(v3, v2), -45.55);
    ASSERT_FLOAT_EQ(VectF3::dotProduct(v3, v3), 108.82);
}

TEST_F(VectF3Test, crossProduct) {
    // v1
    ASSERT_VECTF3_VALUES_EQ(VectF3::crossProduct(v1,v1), 0,0,0);
    ASSERT_VECTF3_VALUES_EQ(VectF3::crossProduct(v1,v2), -12.5, 17.5, -7.5);
    ASSERT_VECTF3_VALUES_EQ(VectF3::crossProduct(v1,v3), -10.5, -27.9, 22.1);
    // v2
    ASSERT_VECTF3_VALUES_EQ(VectF3::crossProduct(v2,v1), 12.5, -17.5, 7.5);
    ASSERT_VECTF3_VALUES_EQ(VectF3::crossProduct(v2,v2), 0,0,0);
    ASSERT_VECTF3_VALUES_EQ(VectF3::crossProduct(v2,v3), -5.25, 21.55, 46.55);
    // v3
    ASSERT_VECTF3_VALUES_EQ(VectF3::crossProduct(v3,v1), 10.5, 27.9, -22.1);
    ASSERT_VECTF3_VALUES_EQ(VectF3::crossProduct(v3,v2), 5.25, -21.55, -46.55);
    ASSERT_VECTF3_VALUES_EQ(VectF3::crossProduct(v3,v3), 0,0,0);
}


// -----------------------------------------------------------------------------
// Operators overload
// -----------------------------------------------------------------------------
TEST_F(VectF3Test, multiply_scalar) {
    float s1 = 13.3;
    float s2 = -9.2;
    float s3 = 4.9;
    // v0
    ASSERT_VECTF3_VALUES_EQ((v0 * s1), 0,0,0);
    ASSERT_VECTF3_VALUES_EQ((v0 * s2), 0,0,0);
    ASSERT_VECTF3_VALUES_EQ((v0 * s3), 0,0,0);
    // v1
    ASSERT_VECTF3_VALUES_EQ((v1 * s1), 13.3, 26.6, 39.9);
    ASSERT_VECTF3_VALUES_EQ((v1 * s2), -9.2, -18.4, -27.6);
    ASSERT_VECTF3_VALUES_EQ((v1 * s3), 4.9, 9.8, 14.7);
    // v2
    ASSERT_VECTF3_VALUES_EQ((v2 * s1), 73.15, 46.55, -13.3);
    ASSERT_VECTF3_VALUES_EQ((v2 * s2), -50.6, -32.2, 9.2);
    ASSERT_VECTF3_VALUES_EQ((v2 * s3), 26.95, 17.15, -4.9);
    // v3
    ASSERT_VECTF3_VALUES_EQ((v3 * s1), -133.0, 27.93, -27.93);
    ASSERT_VECTF3_VALUES_EQ((v3 * s2), 92.0, -19.32, 19.32);
    ASSERT_VECTF3_VALUES_EQ((v3 * s3), -49.0, 10.29, -10.29);
}

TEST_F(VectF3Test, multiply_vector) {
    ASSERT_VECTF3_VALUES_EQ((v1 * v1), 1, 4, 9);
    ASSERT_VECTF3_VALUES_EQ((v1 * v2), 5.5, 7, -3);
}

TEST_F(VectF3Test, divide_scalar) {
    float s1 = 13.3;
    float s2 = -9.2;
    float s3 = 4.9;
    // v0
    ASSERT_VECTF3_VALUES_EQ((v0 / s1), 0,0,0);
    ASSERT_VECTF3_VALUES_EQ((v0 / s2), 0,0,0);
    ASSERT_VECTF3_VALUES_EQ((v0 / s3), 0,0,0);
    // v1
    ASSERT_VECTF3_VALUES_EQ((v1 / s1), 0.075187966, 0.1503759, 0.2255639);
    ASSERT_VECTF3_VALUES_EQ((v1 / s2), -0.10869566, -0.2173913, -0.326087);
    ASSERT_VECTF3_VALUES_EQ((v1 / s3), 0.2040816, 0.4081633, 0.6122449);
    // v2
    ASSERT_VECTF3_VALUES_EQ((v2 / s1), 0.4135338, 0.2631579, -0.075187966);
    ASSERT_VECTF3_VALUES_EQ((v2 / s2), -0.5978261, -0.3804348, 0.10869566);
    ASSERT_VECTF3_VALUES_EQ((v2 / s3), 1.122449, 0.7142857, -0.2040816);
    // v3
    ASSERT_VECTF3_VALUES_EQ((v3 / s1), -0.7518797, 0.1578947, -0.1578947);
    ASSERT_VECTF3_VALUES_EQ((v3 / s2), 1.0869565, -0.2282609, 0.2282609);
    ASSERT_VECTF3_VALUES_EQ((v3 / s3), -2.0408163, 0.4285714, -0.4285714);
}

TEST_F(VectF3Test, divide_vector) {
    ASSERT_VECTF3_VALUES_EQ((v0 / v2), 0, 0, 0);
    ASSERT_VECTF3_VALUES_EQ((v1 / v1), 1, 1, 1);
}

TEST_F(VectF3Test, add_scalar) {
    ASSERT_VECTF3_VALUES_EQ((v0 + 10), 10, 10, 10);
    ASSERT_VECTF3_VALUES_EQ((v1 + 3.9), 4.9, 5.9, 6.9);
    ASSERT_VECTF3_EQ((v3 + 0), v3);
}

TEST_F(VectF3Test, add_vector) {
    // v1
    ASSERT_VECTF3_VALUES_EQ((v1 + v1), 2, 4, 6);
    ASSERT_VECTF3_VALUES_EQ((v1 + v2), 6.5, 5.5, 2);
    ASSERT_VECTF3_VALUES_EQ((v1 + v3), -9, 4.1, 0.9);
    // v2
    ASSERT_VECTF3_VALUES_EQ((v2 + v1), 6.5, 5.5, 2);
    ASSERT_VECTF3_VALUES_EQ((v2 + v2), 11.0, 7.0, -2);
    ASSERT_VECTF3_VALUES_EQ((v2 + v3), -4.5, 5.6, -3.1);
    // v3
    ASSERT_VECTF3_VALUES_EQ((v3 + v1), -9, 4.1, 0.9);
    ASSERT_VECTF3_VALUES_EQ((v3 + v2), -4.5, 5.6, -3.1);
    ASSERT_VECTF3_VALUES_EQ((v3 + v3), -20, 4.2, -4.2);
}

TEST_F(VectF3Test, substract_scalar) {
    ASSERT_VECTF3_VALUES_EQ((v0 - 10), -10, -10, -10);
    ASSERT_VECTF3_VALUES_EQ((v2 - 2.5), 3, 1, -3.5);
    ASSERT_VECTF3_EQ((v3 - 0), v3);
}

TEST_F(VectF3Test, substract_vector) {
    // v1
    ASSERT_VECTF3_VALUES_EQ((v1 - v1), 0,0,0);
    ASSERT_VECTF3_VALUES_EQ((v1 - v2), -4.5, -1.5, 4);
    ASSERT_VECTF3_VALUES_EQ((v1 - v3), 11, -0.099999905, 5.1);
    // v2
    ASSERT_VECTF3_VALUES_EQ((v2 - v1), 4.5, 1.5, -4);
    ASSERT_VECTF3_VALUES_EQ((v2 - v2), 0,0,0);
    ASSERT_VECTF3_VALUES_EQ((v2 - v3), 15.5, 1.4, 1.1);
    // v3
    ASSERT_VECTF3_VALUES_EQ((v3 - v1), -11, 0.099999905, -5.1);
    ASSERT_VECTF3_VALUES_EQ((v3 - v2), -15.5, -1.4, -1.1);
    ASSERT_VECTF3_VALUES_EQ((v3 - v3), 0,0,0);
}


// -----------------------------------------------------------------------------
// Operators overload (Inplace)
// -----------------------------------------------------------------------------
TEST_F(VectF3Test, multiplyin_scalar_place) {
    v0 *= 13.3;
    v1 *= -9.2;
    v2 *= 4.9;
    v3 *= 13.3;
    ASSERT_VECTF3_VALUES_EQ(v0, 0,0,0);
    ASSERT_VECTF3_VALUES_EQ(v1, -9.2, -18.4, -27.6);
    ASSERT_VECTF3_VALUES_EQ(v2, 26.95, 17.15, -4.9);
    ASSERT_VECTF3_VALUES_EQ(v3, -133.0, 27.93, -27.93);
}

TEST_F(VectF3Test, multiply_vector_inplace) {
    v0 *= v3;
    v1 *= v2;
    ASSERT_VECTF3_VALUES_EQ(v0, 0, 0, 0);
    ASSERT_VECTF3_VALUES_EQ(v1, 5.5, 7, -3);
}

TEST_F(VectF3Test, divide_scalar_inplace) {
    v0 /= 13.3;
    v1 /= -9.2;
    v2 /= 13.3;
    v3 /= 4.9;
    ASSERT_VECTF3_VALUES_EQ(v0, 0,0,0);
    ASSERT_VECTF3_VALUES_EQ(v1, -0.10869566, -0.2173913, -0.326087);
    ASSERT_VECTF3_VALUES_EQ(v2, 0.4135338, 0.2631579, -0.075187966);
    ASSERT_VECTF3_VALUES_EQ(v3, -2.0408163, 0.4285714, -0.4285714);
}

TEST_F(VectF3Test, divide_vector_inplace) {
    v0 /= v3;
    v1 /= v1;
    ASSERT_VECTF3_VALUES_EQ(v0, 0, 0, 0);
    ASSERT_VECTF3_VALUES_EQ(v1, 1, 1, 1);
}

TEST_F(VectF3Test, add_scalar_inplace) {
    v0 += 2.4;
    v2 += 0;
    ASSERT_VECTF3_VALUES_EQ(v0, 2.4, 2.4, 2.4);
    ASSERT_VECTF3_VALUES_EQ(v2, 5.5, 3.5, -1);
}

TEST_F(VectF3Test, add_vector_inplace) {
    v1 += v1;
    v2 += v3;
    ASSERT_VECTF3_VALUES_EQ(v1, 2, 4, 6);
    ASSERT_VECTF3_VALUES_EQ(v2, -4.5, 5.6, -3.1);
}

TEST_F(VectF3Test, subtract_scalar_inplace) {
    v0 -= -922.32;
    v1 -= v1;
    v3 -= 0;
    ASSERT_VECTF3_VALUES_EQ(v0, 922.32, 922.32, 922.32);
    ASSERT_VECTF3_VALUES_EQ(v1, 0, 0, 0);
    ASSERT_VECTF3_VALUES_EQ(v3, -10, 2.1, -2.1);
}

TEST_F(VectF3Test, substract_vector_inplace) {
    v2 -= v1;
    v3 -= v3;
    ASSERT_VECTF3_VALUES_EQ(v2, 4.5, 1.5, -4);
    ASSERT_VECTF3_VALUES_EQ(v3, 0,0,0);
}


// -----------------------------------------------------------------------------
// Operators overload (Other)
// -----------------------------------------------------------------------------
TEST_F(VectF3Test, equal) {
    ASSERT_TRUE(v0==v0);
    ASSERT_TRUE(v1==v1);
    ASSERT_TRUE(v2==v2);
    ASSERT_TRUE(v3==v3);
}

TEST_F(VectF3Test, notequal) {
    ASSERT_FALSE(v0!=v0);
    ASSERT_FALSE(v1!=v1);
    ASSERT_FALSE(v2!=v2);
    ASSERT_FALSE(v3!=v3);
    ASSERT_TRUE(v0!=v3);
    ASSERT_TRUE(v1!=v0);
    ASSERT_TRUE(v2!=v3);
    ASSERT_TRUE(v3!=v2);
}

TEST_F(VectF3Test, access_operator) {
    ASSERT_EQ(v0[2], 0);
    ASSERT_EQ(v1[1], 2);
    ASSERT_EQ(v3[0], -10);
}



} // End namespace



