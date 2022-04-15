//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     Jakub Mašek <xmasek19@stud.fit.vutbr.cz>
// $Date:       $2022-02-03
//============================================================================//
/**
 * @file white_box_tests.cpp
 * @author Jakub Mašek
 *
 * @brief Implementace testu prace s maticemi.
 */

#include "gtest/gtest.h"
#include "white_box_code.h"

class EmptyMatrix : public ::testing::Test
{
protected:
    Matrix matrix;
};

class Matrix3x3 : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        std::vector<std::vector<double>> matrixInVector{
            {1, 2, 3},
            {4, 5, 6},
            {7, 8, 9}};
        matrix.set(matrixInVector);
    }
    Matrix matrix = {3, 3};
};
class Matrix3x3InverseTest : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        std::vector<std::vector<double>> matrixInVector{
            {1, 2, 3},
            {0, 1, 4},
            {5, 6, 0}};
        matrix.set(matrixInVector);
    }
    Matrix matrix = {3, 3};
};

class Matrix4x4 : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        std::vector<std::vector<double>> matrixInVector{
            {2, 1, 1, 1},
            {1, 2, 1, 1},
            {1, 1, 2, 1},
            {1, 1, 1, 2}};
        matrix.set(matrixInVector);
    }
    Matrix matrix = {4, 4};
};

class Matrix5x5 : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        std::vector<std::vector<double>> matrixInVector{
            {4, 1, 2, -3, 5},
            {-3, 3, -1, 4, -2}, 
            {-1, 2, 5, 1, 3}, 
            {5, 4, 3, -1, 2}, 
            {1, -2, 3, -4, 5}};
        matrix.set(matrixInVector);
    }
    Matrix matrix = {5, 5};
};

TEST_F(EmptyMatrix, CreateMatrix_1x1)
{
    ASSERT_EQ(matrix.get(0, 0), 0);
}

TEST_F(EmptyMatrix, CreateMatrix_5x7)
{
    Matrix matrix(5, 7);
    for(int row = 0;row < 5;row++)
    {
        for (int col = 0; col < 7; col++)
        {
            ASSERT_EQ(matrix.get(row, col), 0);
        }
    }
}

TEST_F(EmptyMatrix, CreateMatrix_WrongSize)
{
    EXPECT_ANY_THROW(Matrix matrix(0, 5));
    EXPECT_ANY_THROW(Matrix matrix(1, 0));
}

TEST_F(EmptyMatrix, Setvalue_plus){
    EXPECT_TRUE(matrix.set(0, 0, 8));
    EXPECT_EQ(matrix.get(0, 0), 8);
}

TEST_F(EmptyMatrix, Setvalue_minus)
{
    EXPECT_TRUE(matrix.set(0, 0, -9.5));
    EXPECT_EQ(matrix.get(0, 0), -9.5);
}

TEST_F(EmptyMatrix, Setvalue_big)
{
    Matrix matrix(260, 212);
    EXPECT_TRUE(matrix.set(136, 111, 5468.4));
}

TEST_F(EmptyMatrix, Setvalue_vector)
{
    std::vector<std::vector<double>> matrixInVector{
        {1, 1, 1, 1},
        {2, 2, 2, 2},
        {3, 3, 3, 3}};
    Matrix matrix(3, 4);
    EXPECT_TRUE(matrix.set(matrixInVector));

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            EXPECT_EQ(matrix.get(row, col), row+1);
        }
    }
}

TEST_F(EmptyMatrix, Setvalue_vector2)
{
    std::vector<std::vector<double>> matrixInVector{
        {0, -1, 16579, -3, -4},
        {-5, -6654, -7, -8, -999},
        {156, -1999, 9845, 0, 0},
        {15, -6, 17000, -9555, -1},
        {0, 0, 0, 0, 0}};
    Matrix matrix(5, 5);
    EXPECT_TRUE(matrix.set(matrixInVector));
    EXPECT_EQ(matrix.get(1, 4), -999);
}

TEST_F(EmptyMatrix, Setvalue_OutOfRange)
{
    EXPECT_FALSE(matrix.set(1, 0, 2));
}

TEST_F(EmptyMatrix, Setvalue_OutOfRange2)
{
    Matrix matrix(10, 10);
    EXPECT_FALSE(matrix.set(10, 9, 2));
    EXPECT_FALSE(matrix.set(9, 10, 2));
}

TEST_F(EmptyMatrix, Setvalue_VectorOutOfRange)
{
    std::vector<std::vector<double>> matrixInVector(1, std::vector<double>(2, 0));
    EXPECT_FALSE(matrix.set(matrixInVector));
}

TEST_F(EmptyMatrix, Setvalue_VectorOutOfRange2)
{
    std::vector<std::vector<double>> matrixInVector{
        {0, -1, 16579, -3, -4},
        {-5, -6654, -7, -8, -999},
        {156, -1999, 9845, 0, 0},
        {15, -6, 17000, -9555, -1},
        {0, 0, 0, 0, 0}};

    Matrix matrix(5, 4);
    EXPECT_FALSE(matrix.set(matrixInVector));
    
    Matrix matrix2(4, 5);
    EXPECT_FALSE(matrix2.set(matrixInVector));
}

TEST_F(EmptyMatrix, Getvalue)
{
    Matrix matrix(4, 4);
    matrix.set(2, 2, 1);
    EXPECT_EQ(matrix.get(2, 2), 1);
    EXPECT_EQ(matrix.get(0, 0), 0);
}

TEST_F(EmptyMatrix, Getvalue_OutOfRange)
{
    Matrix matrix(3, 3);
    EXPECT_ANY_THROW(matrix.get(3, 0));
    EXPECT_ANY_THROW(matrix.get(0, 3));
}

TEST_F(EmptyMatrix, OperatorEqual)
{
    Matrix matrix1;
    Matrix matrix2;
    bool result = matrix1 == matrix2;
    EXPECT_TRUE(result);
}

TEST_F(EmptyMatrix, OperatorEqual_2)
{
    Matrix matrix1;
    Matrix matrix2;
    matrix1.set(0, 0, 1);
    bool result = matrix1 == matrix2;
    EXPECT_FALSE(result);
}

TEST_F(EmptyMatrix, OperatorEqual_WrongSize)
{
    Matrix matrix1(1, 1);
    Matrix matrix2(1, 2);
    EXPECT_ANY_THROW(matrix1 == matrix2);

    Matrix matrix3(2, 1);
    EXPECT_ANY_THROW(matrix1 == matrix3);
}

TEST_F(EmptyMatrix, OperatorPlus)
{
    Matrix matrix1(1, 1);
    Matrix matrix2(1, 1);
    auto result = matrix1 + matrix2;
    EXPECT_EQ(result.get(0, 0), 0);
}

TEST_F(EmptyMatrix, OperatorPlus_WrongSize)
{
    Matrix matrix1(1, 1);
    Matrix matrix2(1, 2);
    EXPECT_ANY_THROW(matrix1 + matrix2);

    Matrix matrix3(2, 1);
    EXPECT_ANY_THROW(matrix1 + matrix3);
}

TEST_F(EmptyMatrix, OperatorTimes)
{
    Matrix matrix1(1, 1);
    Matrix matrix2(1, 1);
    auto result = matrix1 * matrix2;
    EXPECT_EQ(result.get(0, 0), 0);
}

TEST_F(EmptyMatrix, OperatorTimes_2)
{
    Matrix matrix1(1, 1);
    Matrix matrix2(1, 1);
    auto result = matrix1 * 2;
    EXPECT_EQ(result.get(0, 0), 0);
}

TEST_F(EmptyMatrix, OperatorTimes_WrongSize)
{
    Matrix matrix1(2, 3);
    EXPECT_ANY_THROW(matrix1 * matrix);

    Matrix matrix3(2, 3);
    EXPECT_ANY_THROW(matrix1 * matrix3);
}

TEST_F(EmptyMatrix, SolveEquation)
{
    matrix.set(0, 0, 1);
    std::vector<double> rightSide{-1};
    std::vector<double> expectedRes{-1};
    auto res = matrix.solveEquation(rightSide);
    EXPECT_EQ(res, expectedRes);
}

TEST_F(EmptyMatrix, SolveEquation_WrongInputSize)
{
    matrix.set(0, 0, 1);
    std::vector<double> rightSide{1, 1};
    EXPECT_ANY_THROW(matrix.solveEquation(rightSide));
}

TEST_F(EmptyMatrix, SolveEquation_WrongInputSize2)
{
    Matrix matrix(1, 2);
    matrix.set(0, 0, 1);
    std::vector<double> rightSide{1, 1};
    EXPECT_ANY_THROW(matrix.solveEquation(rightSide));

    Matrix matrix2(3, 1);
    matrix2.set(0, 0, 1);
    EXPECT_ANY_THROW(matrix2.solveEquation(rightSide));
}

TEST_F(EmptyMatrix, SolveEquation_Singular)
{
    Matrix matrix(2, 2);
    std::vector<double> rightSide{1, 1};
    EXPECT_ANY_THROW(matrix.solveEquation(rightSide));
}

TEST_F(EmptyMatrix, Transpose)
{
    Matrix matrix2;
    EXPECT_EQ(matrix.transpose(), matrix2);
}

TEST_F(EmptyMatrix, Inverse)
{
    Matrix matrix(2, 3);
    EXPECT_ANY_THROW(matrix.inverse());

    Matrix matrix2(4, 4);
    EXPECT_ANY_THROW(matrix2.inverse());

    Matrix matrix3;
    EXPECT_ANY_THROW(matrix3.inverse());
}

TEST_F(EmptyMatrix, Inverse_2)
{
    Matrix matrix(2, 2);
    matrix.set(0, 0, 1);
    matrix.set(1, 1, 1);
    EXPECT_EQ(matrix.inverse(), matrix);
}

TEST_F(EmptyMatrix, Inverse_3)
{
    Matrix matrix(2, 2);
    EXPECT_ANY_THROW(matrix.inverse());
}

TEST_F(Matrix3x3, Setvalue)
{
    EXPECT_TRUE(matrix.set(2, 2, 5));
    EXPECT_EQ(matrix.get(2,2),5);
}

TEST_F(Matrix3x3, Setvalue_Vector)
{
    int matrixSize = 3;
    int num = 0;
    std::vector<std::vector<double>> matrixInVector{
        {1, 1, 1},
        {1, 1, 1},
        {1, 1, 1}};

    EXPECT_TRUE(matrix.set(matrixInVector));
    
    for (int row = 0; row < matrixSize; row++)
    {
        for (int col = 0; col < matrixSize; col++)
        {
            EXPECT_EQ(matrix.get(row, col), 1);
        }
    }
}

TEST_F(Matrix3x3, getValue)
{
    EXPECT_EQ(matrix.get(2, 2), 9);
}

TEST_F(Matrix3x3, operatorEquals)
{
    EXPECT_TRUE(matrix == matrix);

    Matrix matrix2(3, 3);
    matrix2.set(0, 0, 0);
    EXPECT_FALSE(matrix == matrix2);
}

TEST_F(Matrix3x3, operatorPlus)
{
    auto result = matrix + matrix;
    double num = 1;
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            EXPECT_EQ(result.get(row, col), num + num);
            num++;
        }
    }
}

TEST_F(Matrix3x3, operatorTimesNum)
{
    auto result = matrix * -6;
    double num = 1;
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            EXPECT_EQ(result.get(row, col), (num * -6));
            num++;
        }
    }
}

TEST_F(Matrix3x3, operatorTimes_Matrix)
{
    auto result = matrix * matrix;
    std::vector<std::vector<double>> expectedResult{
        {30, 36, 42},
        {66, 81, 96},
        {102, 126, 150}};

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {

            EXPECT_EQ(result.get(row, col), expectedResult[row][col]);
        }
    }
}

TEST_F(Matrix3x3, SolveEquation)
{
    std::vector<double> rightSide{1, 1, 1};
    matrix.set(2, 2, 1);
    std::vector<double> expectedArray{-1, 1, 0};
    EXPECT_EQ(matrix.solveEquation(rightSide), expectedArray);
}

TEST_F(Matrix3x3, SolveEquation_Singular)
{
    std::vector<double> rightSide{1, 1, 1};
    EXPECT_ANY_THROW(matrix.solveEquation(rightSide));
}

TEST_F(Matrix3x3, Transpone)
{
    double num = 1;
    Matrix matrixT(3, 3);
    matrixT = matrix.transpose();
    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            EXPECT_EQ(matrixT.get(col, row), num++);
        }
    }
}

TEST_F(Matrix3x3, Inverse_singular)
{
    EXPECT_ANY_THROW(matrix.inverse());
}

TEST_F(Matrix3x3InverseTest, Inverse)
{
    std::vector<std::vector<double>> expectedResult
    {
        {-24, 18, 5}, 
        {20, -15, -4}, 
        {-5, 4, 1}
    };
    Matrix matrixExpected(3,3);
    matrixExpected.set(expectedResult);

    Matrix matrixI(3, 3);
    matrixI = matrix.inverse();

    for (int row = 0; row < 3; row++)
    {
        for (int col = 0; col < 3; col++)
        {
            EXPECT_EQ(matrixI.get(row, col), matrixExpected.get(row,col));
        }
    }
}

TEST_F(Matrix4x4, SolveEquation)
{
    std::vector<double> rightSide{5, 5, 5, 5};
    std::vector<double> expectedArray{1, 1, 1, 1};
    EXPECT_EQ(matrix.solveEquation(rightSide), expectedArray);
}

TEST_F(Matrix5x5, SolveEquation)
{
    std::vector<double> rightSide{-16, 20, -4, -10, 3};
    std::vector<double> expectedArray{(double)(-3209) / 209, (double)3305 / 209, (double)(-370) / 209, (double)(-4629) / 209, (double)(-1392) / 209};
    EXPECT_EQ(matrix.solveEquation(rightSide), expectedArray);
}

/*** Konec souboru white_box_tests.cpp ***/
