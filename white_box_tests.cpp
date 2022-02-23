//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     White Box - Tests suite
//
// $NoKeywords: $ivs_project_1 $white_box_code.cpp
// $Author:     Jakub Mašek <xmasek19@stud.fit.vutbr.cz>
// $Date:       $2022-22-02
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

    virtual void SetUp() {
        int matrixSize = 3;
        int num = 1;
        std::vector<std::vector< double > > matrixInVector(matrixSize, std::vector<double> (matrixSize));
        for(int row = 0;row<matrixSize;row++){
            for(int col = 0;col<matrixSize;col++){
                matrixInVector[row][col]=num++;
            }
        matrix.set(matrixInVector);
        }
    }
    Matrix matrix={3,3};
};

class Matrix4x4 : public ::testing::Test
{
protected:

    virtual void SetUp() {
        int matrixSize = 4;
        std::vector<std::vector< double > > matrixInVector(matrixSize, std::vector<double> (matrixSize));
        for(int row = 0;row<matrixSize;row++){
            for(int col = 0;col<matrixSize;col++){
                if(row != col){
                    matrixInVector[row][col]=1;
                }else{
                    matrixInVector[row][col]=2;
                }
            }
        matrix.set(matrixInVector);
        }
    }
    Matrix matrix={4,4};
};

TEST_F(EmptyMatrix,CreateMatrix){
    EXPECT_EQ(matrix.get(0,0),0);
}

TEST_F(EmptyMatrix,CreateMatrix2){
    Matrix matrix(2,2);
    EXPECT_EQ(matrix.get(1,1),0);
}

TEST_F(EmptyMatrix,CreateMatrix3){
    EXPECT_ANY_THROW(Matrix matrix(0,5));
    EXPECT_ANY_THROW(Matrix matrix(1,0));
}

TEST_F(EmptyMatrix, Setvalue){
    EXPECT_TRUE(matrix.set(0,0,8));
}

TEST_F(EmptyMatrix, Setvalue2){
    EXPECT_TRUE(matrix.set(0,0,-9.5));
}

TEST_F(EmptyMatrix, Setvalue3){
    Matrix matrix(50,50);
    EXPECT_TRUE(matrix.set(49,49,23));
}

TEST_F(EmptyMatrix, SetvalueVector){
    auto matrixInVector = std::vector<std::vector< double > >(2, std::vector<double>(3, 0));
    matrixInVector[1][1]=4;
    Matrix matrix(2,3);
    EXPECT_TRUE(matrix.set(matrixInVector));
    EXPECT_EQ(matrix.get(1,1),4);
}

TEST_F(EmptyMatrix, SetvalueVector2){
    int matrixSize = 5;
    double num = 0;
    std::vector<std::vector< double > > matrixInVector(matrixSize, std::vector<double> (matrixSize,0));
    for(int row = 0;row<matrixSize;row++){
        for(int col = 0;col<matrixSize;col++){
            matrixInVector[row][col]=num++;
        }
    }
    Matrix matrix(matrixSize,matrixSize);
    EXPECT_TRUE(matrix.set(matrixInVector));
    EXPECT_EQ(matrix.get(1,4),9);
}

TEST_F(EmptyMatrix, SetvalueOutOfRange){
    EXPECT_FALSE(matrix.set(1,1,2));
}

TEST_F(EmptyMatrix, SetvalueOutOfRange2){
    Matrix matrix(10,10);
    EXPECT_FALSE(matrix.set(10,9,2));
    EXPECT_FALSE(matrix.set(9,10,2));
}

TEST_F(EmptyMatrix, SetvalueVectorOutOfRange){
    auto matrixInVector = std::vector<std::vector< double > >(1, std::vector<double>(2, 0));
    EXPECT_FALSE(matrix.set(matrixInVector));
}

TEST_F(EmptyMatrix, SetvalueVectorOutOfRange2){
    int matrixSize = 5;
    int num = 0;
    std::vector<std::vector< double > > matrixInVector(matrixSize, std::vector<double> (matrixSize+1,1));
    for(int row = 0;row<matrixSize;row++){
        for(int col = 0;col<matrixSize;col++){
            matrixInVector[row][col]=num++;
        }
    }
    Matrix matrix(matrixSize,matrixSize);
    EXPECT_FALSE(matrix.set(matrixInVector));
}

TEST_F(EmptyMatrix, SetvalueVectorOutOfRange3){
    std::vector<std::vector< double > > matrixInVector(2, std::vector<double> (1,1));
    EXPECT_FALSE(matrix.set(matrixInVector));
}


TEST_F(EmptyMatrix, Getvalue){
    Matrix matrix(4,4);
    matrix.set(2,2,1);
    EXPECT_EQ(matrix.get(2,2),1);
}

TEST_F(EmptyMatrix, GetvalueOutOfRange){
    Matrix matrix(3,3);
    EXPECT_ANY_THROW(matrix.get(3,0));
    EXPECT_ANY_THROW(matrix.get(0,3));
}

TEST_F(EmptyMatrix, OperatorEqual){
    Matrix matrix1;
    Matrix matrix2;
    bool result = matrix1 == matrix2;
    EXPECT_TRUE(result);
}

TEST_F(EmptyMatrix, OperatorEqual2){
    Matrix matrix1;
    Matrix matrix2;
    matrix1.set(0,0,1);
    bool result = matrix1 == matrix2;
    EXPECT_FALSE(result);
}

TEST_F(EmptyMatrix, OperatorEqualWrongSize){
    Matrix matrix1(1,1);
    Matrix matrix2(1,2);
    EXPECT_ANY_THROW(matrix1 == matrix2);

    Matrix matrix3(2,1);
    EXPECT_ANY_THROW(matrix1 == matrix3);
}

TEST_F(EmptyMatrix, OperatorPlus){
    Matrix matrix1(1,1);
    Matrix matrix2(1,1);
    auto result = matrix1 + matrix2;
    EXPECT_EQ(result.get(0,0),0);
}

TEST_F(EmptyMatrix, OperatorPlusWrongSize){
    Matrix matrix1(1,1);
    Matrix matrix2(1,2);
    EXPECT_ANY_THROW(matrix1 + matrix2);

    Matrix matrix3(2,1);
    EXPECT_ANY_THROW(matrix1 + matrix3);
}

TEST_F(EmptyMatrix, OperatorTimes){
    Matrix matrix1(1,1);
    Matrix matrix2(1,1);
    auto result = matrix1 * matrix2;
    EXPECT_EQ(result.get(0,0),0);
}

TEST_F(EmptyMatrix, OperatorTimes2){
    Matrix matrix1(1,1);
    Matrix matrix2(1,1);
    auto result = matrix1 * 2;
    EXPECT_EQ(result.get(0,0),0);
}

TEST_F(EmptyMatrix, OperatorTimesWrongSize){
    Matrix matrix1(1,2);
    Matrix matrix2(1,1);
    EXPECT_ANY_THROW(matrix1 * matrix2);

    Matrix matrix3(3,2);
    EXPECT_ANY_THROW(matrix1 * matrix3);
}

TEST_F(EmptyMatrix, SolveEquation){
    matrix.set(0,0,1);
    std::vector< double > rightSide;
    std::vector< double > expectedRes;
    rightSide.push_back(1);
    expectedRes.push_back(1);
    auto res = matrix.solveEquation(rightSide);
    EXPECT_EQ(res,expectedRes);
}

TEST_F(EmptyMatrix, SolveEquationWrongInputSize){
    matrix.set(0,0,1);
    std::vector< double > rightSide;
    rightSide.push_back(1);
    rightSide.push_back(1);
    EXPECT_ANY_THROW(matrix.solveEquation(rightSide));
}

TEST_F(EmptyMatrix, SolveEquationWrongInputSize2){
    Matrix matrix(1,2);
    matrix.set(0,0,1);
    std::vector< double > rightSide;
    rightSide.push_back(1);
    rightSide.push_back(1);
    EXPECT_ANY_THROW(matrix.solveEquation(rightSide));

    Matrix matrix2(2,1);
    matrix2.set(0,0,1);
    EXPECT_ANY_THROW(matrix2.solveEquation(rightSide));
}

TEST_F(EmptyMatrix, SolveEquationSingular){
    Matrix matrix(2,2);
    std::vector< double > rightSide;
    rightSide.push_back(1);
    rightSide.push_back(1);
    EXPECT_ANY_THROW(matrix.solveEquation(rightSide));
}

TEST_F(EmptyMatrix, EmptyMatrix_Transpos_Test){
    Matrix matrix2;
    EXPECT_EQ(matrix.transpose() ,matrix2);
}

TEST_F(EmptyMatrix, EmptyMatrix_inverse_Test){
    Matrix matrix(2,3);
    EXPECT_ANY_THROW(matrix.inverse());
    Matrix matrix2(4,4);
    EXPECT_ANY_THROW(matrix2.inverse());
    Matrix matrix3;
    EXPECT_ANY_THROW(matrix3.inverse());
}

TEST_F(EmptyMatrix, EmptyMatrix_inverse_Test2){
    Matrix matrix(2,2);
    matrix.set(0,0,1);
    matrix.set(1,1,1);
    EXPECT_EQ(matrix.inverse() ,matrix);
}

TEST_F(EmptyMatrix, EmptyMatrix_inverse_Test3){
    Matrix matrix(3,3);
    matrix.set(0,0,1);
    matrix.set(1,1,1);
    matrix.set(2,2,1);
    EXPECT_EQ(matrix.inverse() ,matrix);
}


TEST_F(EmptyMatrix, EmptyMatrix_inverse_Test4){
    Matrix matrix(2,2);
    EXPECT_ANY_THROW(matrix.inverse());
}

TEST_F(Matrix3x3,setValue){
    EXPECT_TRUE(matrix.set(2,2,5));
}

TEST_F(Matrix3x3, SetvalueVector){
    int matrixSize = 3;
    int num = 0;
    std::vector<std::vector< double > > matrixInVector(matrixSize, std::vector<double> (matrixSize,0));
    for(int row = 0;row<matrixSize;row++){
        for(int col = 0;col<matrixSize;col++){
            matrixInVector[row][col]=1;
        }
    }
    EXPECT_TRUE(matrix.set(matrixInVector));
    EXPECT_EQ(matrix.get(1,2),1);
}

TEST_F(Matrix3x3,getValue){
    EXPECT_EQ(matrix.get(2,2),9);
}

TEST_F(Matrix3x3,operatorEquals){
    EXPECT_TRUE(matrix==matrix);
    Matrix matrix2(3,3);
    matrix2.set(0,0,0);
    EXPECT_FALSE(matrix==matrix2);
}

TEST_F(Matrix3x3,operatorPlus){
    auto result = matrix+matrix;
    double num = 1;
    for (int row=0;row<3;row++){
        for(int col=0;col<3;col++){
            EXPECT_EQ(result.get(row,col), num+num);
            num++;
        }
    }
}

TEST_F(Matrix3x3, SolveEquation){
    std::vector< double > rightSide;
    rightSide.push_back(1);
    rightSide.push_back(1);
    rightSide.push_back(1);
    matrix.set(2,2,1);
    std::vector<double> expectedArray={-1,1,0};
    EXPECT_EQ(matrix.solveEquation(rightSide),expectedArray);
}

TEST_F(Matrix3x3, SolveEquationSingular){
    std::vector< double > rightSide;
    rightSide.push_back(1);
    rightSide.push_back(1);
    rightSide.push_back(1);
    EXPECT_ANY_THROW(matrix.solveEquation(rightSide));
}

TEST_F(Matrix3x3, transpone){
    double num = 1;
    Matrix matrixT(3,3);
    matrixT=matrix.transpose();
    for (int row=0;row<3;row++){
        for(int col=0;col<3;col++){
            EXPECT_EQ(matrixT.get(col,row), num);
            num++;
        }
    }
}

TEST_F(Matrix3x3, inverseSingular){
    EXPECT_ANY_THROW(matrix.inverse());
}

TEST_F(Matrix4x4, SolveEquation){
    std::vector< double > rightSide;
    for(int i = 0;i < 4;i++){
        rightSide.push_back(5);
    }
    std::vector<double> expectedArray={1,1,1,1};
    EXPECT_EQ(matrix.solveEquation(rightSide),expectedArray);
}


//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy operaci nad maticemi. Cilem testovani je:
// 1. Dosahnout maximalniho pokryti kodu (white_box_code.cpp) testy.
// 2. Overit spravne chovani operaci nad maticemi v zavislosti na rozmerech 
//    matic.
//============================================================================//

/*** Konec souboru white_box_tests.cpp ***/
