//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     Jakub Mašek <xmasek19@stud.fit.vutbr.cz>
// $Date:       $2022-02-17
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author Jakub Mašek
 *
 * @brief Implementace testu binarniho stromu.
 */

#include <vector>

#include "gtest/gtest.h"

#include "red_black_tree.h"

class EmptyTree : public ::testing::Test
{
protected:
    BinaryTree tree;
};

class NonEmptyTree : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        int values[] = {112, 5, 10, 15, 90, 30, 40, 80, 65, 60, 85, 55, 45, 50, 20, 35, 70, 75, 95, 250, 0,-5,INT32_MAX,INT32_MIN};
        for (int i = 0; i < 24; ++i)
        {
            tree.InsertNode(values[i]);
        }
    }
    BinaryTree tree;
};

class TreeAxioms : public ::testing::Test
{
protected:
    virtual void SetUp()
    {
        int values[] = {112, 5, 10, 15, 90, 30, 40, 80, 65, 60, 85, 55, 45, 50, 20, 35, 70, 75, 95, 250, 0,-5};
        for (int i = 0; i < 22; ++i)
        {
            auto res = tree.InsertNode(values[i]);
        }
    }
    BinaryTree tree;
};

TEST_F(EmptyTree, InsertNode_notExistingNode)
{
    auto result = tree.InsertNode(999);
    ASSERT_TRUE(result.first);
    ASSERT_EQ(result.second->key, 999);

    result = tree.InsertNode(0);
    ASSERT_TRUE(result.first);
    ASSERT_EQ(result.second->key, 0);

    result = tree.InsertNode(-5);
    ASSERT_TRUE(result.first);
    ASSERT_EQ(result.second->key, -5);
}

TEST_F(EmptyTree, InsertNode_existingNode)
{
    tree.InsertNode(0);
    tree.InsertNode(INT16_MIN);

    auto result = tree.InsertNode(0);
    ASSERT_FALSE(result.first);
    ASSERT_EQ(result.second->key, 0);

    result = tree.InsertNode(INT16_MIN);
    ASSERT_FALSE(result.first);
    ASSERT_EQ(result.second->key, INT16_MIN);
}

TEST_F(EmptyTree, DeleteNode_notExistingNode)
{
    auto result = tree.DeleteNode(0);
    EXPECT_FALSE(result);

    result = tree.DeleteNode(16123);
    EXPECT_FALSE(result);
}

TEST_F(EmptyTree, DeleteNode_existingNode)
{
    tree.InsertNode(0);
    tree.InsertNode(22);
    tree.InsertNode(-5);

    auto result = tree.DeleteNode(0);
    EXPECT_TRUE(result);
    result = tree.DeleteNode(0);
    EXPECT_FALSE(result);

    result = tree.DeleteNode(22);
    EXPECT_TRUE(result);

    result = tree.DeleteNode(-5);
    EXPECT_TRUE(result);
}

TEST_F(EmptyTree, FindNode_notExistingNode)
{
    auto result = tree.FindNode(0);
    EXPECT_EQ(result, nullptr);

    result = tree.FindNode(1652);
    EXPECT_EQ(result, nullptr);
}

TEST_F(EmptyTree, FindNode_existingNode)
{
    tree.InsertNode(0);
    tree.InsertNode(35);
    tree.InsertNode(-5);

    auto result = tree.FindNode(0);
    EXPECT_EQ(result->key, 0);

    result = tree.FindNode(35);
    EXPECT_EQ(result->key, 35);

    result = tree.FindNode(-5);
    EXPECT_EQ(result->key, -5);
}

TEST_F(NonEmptyTree, InsertNode_notExistingNode)
{
    auto result = tree.InsertNode(22);
    ASSERT_TRUE(result.first);
    ASSERT_EQ(result.second->key, 22);
    
    result = tree.InsertNode(-25);
    ASSERT_TRUE(result.first);
    ASSERT_EQ(result.second->key, -25);
}

TEST_F(NonEmptyTree, InsertNode_existingNode)
{
    auto result = tree.InsertNode(15);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second->key, 15);

    result = tree.InsertNode(0);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second->key, 0);

    result = tree.InsertNode(-5);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second->key, -5);
}

TEST_F(NonEmptyTree, DeleteNode_notExistingNode)
{
    auto result = tree.DeleteNode(25);
    EXPECT_FALSE(result);

    result = tree.DeleteNode(-1);
    EXPECT_FALSE(result);
}

TEST_F(NonEmptyTree, DeleteNode_existingNode)
{
    auto result = tree.DeleteNode(15);
    EXPECT_TRUE(result);

    result = tree.DeleteNode(0);
    EXPECT_TRUE(result);

    result = tree.DeleteNode(INT32_MIN);
    EXPECT_TRUE(result);
}

TEST_F(NonEmptyTree, FindNode_notExistingNode)
{
    auto result = tree.FindNode(22);
    EXPECT_EQ(result, nullptr);

    result = tree.FindNode(-1);
    EXPECT_EQ(result, nullptr);
}

TEST_F(NonEmptyTree, FindNode_existingNode)
{
    auto result = tree.FindNode(15);
    EXPECT_EQ(result->key, 15);

    result = tree.FindNode(INT32_MAX);
    EXPECT_EQ(result->key, INT32_MAX);

    result = tree.FindNode(INT32_MIN);
    EXPECT_EQ(result->key, INT32_MIN);
}

TEST_F(TreeAxioms, Axiom1)
{
    std::vector<Node_t *> nodes{};
    tree.GetLeafNodes(nodes);
    bool result = true;
    for (auto node : nodes)
    {
        if (node->color != BLACK)
        {
            result = false;
            break;
        }
    }
    EXPECT_TRUE(result);
}

TEST_F(TreeAxioms, Axiom2)
{
    std::vector<Node_t *> nodes{};
    tree.GetAllNodes(nodes);
    bool result = true;
    for (auto node : nodes)
    {
        if (node->color == RED)
        {
            auto leftColor = node->pLeft->color;
            auto rightColor = node->pRight->color;
            if (leftColor != BLACK || rightColor != BLACK)
            {
                result = false;
                break;
            }
        }
    }
    EXPECT_TRUE(result);
}

TEST_F(TreeAxioms, Axiom3)
{
    std::vector<Node_t *> nodes{};
    tree.GetLeafNodes(nodes);
    bool result = true;
    int blackCount = 0, lastBlackCount = EOF;
    for (auto node : nodes)
    {
        while (node != NULL)
        {
            if (node->color == BLACK)
            {
                blackCount++;
            }
            node = node->pParent;
        }

        if (blackCount != lastBlackCount && lastBlackCount != EOF)
        {
            result = false;
            break;
        }
        lastBlackCount = blackCount;
        blackCount = 0;
    }
    EXPECT_TRUE(result);
}
/*** Konec souboru black_box_tests.cpp ***/
