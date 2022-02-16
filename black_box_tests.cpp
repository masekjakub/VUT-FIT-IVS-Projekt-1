//======== Copyright (c) 2017, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Red-Black Tree - public interface tests
//
// $NoKeywords: $ivs_project_1 $black_box_tests.cpp
// $Author:     JMENO PRIJMENI <xlogin00@stud.fit.vutbr.cz>
// $Date:       $2017-01-04
//============================================================================//
/**
 * @file black_box_tests.cpp
 * @author JMENO PRIJMENI
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
    virtual void SetUp() {
        int values[] = { 10, 85, 15, 70, 20, 60, 30, 50, 65, 80, 90, 40, 5, 55 };
        for(int i = 0; i < 14; ++i){
            tree.InsertNode(values[i]);
        }
    }
    BinaryTree tree;
};

class TreeAxioms : public ::testing::Test
{
protected:

    BinaryTree tree;
};

TEST_F(EmptyTree,InsertNode_notExisting){
    auto result = tree.InsertNode(999);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second->key,999);
}

TEST_F(EmptyTree,InsertNode_existing){
    tree.InsertNode(999);
    auto result = tree.InsertNode(999);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second->key,999);
}

TEST_F(EmptyTree,DeleteNode_notExisting){
    auto result = tree.DeleteNode(22);
    EXPECT_FALSE(result);
}

TEST_F(EmptyTree,DeleteNode_existing){
    tree.InsertNode(22);
    auto result = tree.DeleteNode(22);
    EXPECT_TRUE(result);
}

TEST_F(EmptyTree,FindNode_notExisting){
    auto result = tree.FindNode(35);
    EXPECT_EQ(result, nullptr);
}

TEST_F(EmptyTree,FindNode_existing){
    tree.InsertNode(35);
    auto result_2 = tree.FindNode(35);
    EXPECT_EQ(result_2->key,35);
}

TEST_F(NonEmptyTree,InsertNode_notExisting){
    auto result = tree.InsertNode(25);
    EXPECT_TRUE(result.first);
    EXPECT_EQ(result.second->key,25);
}

TEST_F(NonEmptyTree,InsertNode_existing){
    auto result = tree.InsertNode(15);
    EXPECT_FALSE(result.first);
    EXPECT_EQ(result.second->key,15);
}

TEST_F(NonEmptyTree, DeleteNode_notExisting){
    auto result = tree.DeleteNode(25);
    EXPECT_FALSE(result);
}

TEST_F(NonEmptyTree, DeleteNode_existing){
    auto result = tree.DeleteNode(15);
    EXPECT_TRUE(result);
}

TEST_F(NonEmptyTree,FindNode_notExisting){
    auto result = tree.FindNode(25);
    EXPECT_EQ(result,nullptr);
}

TEST_F(NonEmptyTree,FindNode_existing){
    auto result = tree.FindNode(15);
    EXPECT_EQ(result->key,15);
}

TEST_F(TreeAxioms,Axiom1){
    std::vector<Node_t *> vector {};
    tree.GetLeafNodes(vector);
    bool result = true;
    for (auto node : vector){
        if(node->color != BLACK){
            result = false;
            break;
        }
    }
    EXPECT_TRUE(result);
}

TEST_F(TreeAxioms,Axiom2){
    std::vector<Node_t *> vector {};
    tree.GetAllNodes(vector);
    bool result = true;
    for (auto node : vector){
        if(node->color == RED){
            auto leftColor = node->pLeft->color;
            auto rightColor = node->pRight->color;
            if(leftColor != BLACK || rightColor != BLACK)
            result = false;
            break;
        }
    }
    EXPECT_TRUE(result);
}

TEST_F(TreeAxioms,Axiom3){
    std::vector<Node_t *> vector {};
    tree.GetLeafNodes(vector);
    bool result = true;
    int blackCount = 0, lastBlackCount = 0;
    for (auto node : vector){
        if(node->color == BLACK){
            blackCount++;
        }
        if(blackCount != lastBlackCount && lastBlackCount != 0){
            result = false;
            break;
        }
        node = node->pParent;
        lastBlackCount = blackCount;
    }
    EXPECT_TRUE(result);
}
//============================================================================//
// ** ZDE DOPLNTE TESTY **
//
// Zde doplnte testy Red-Black Tree, testujte nasledujici:
// 1. Verejne rozhrani stromu
//    - InsertNode/DeleteNode a FindNode
//    - Chovani techto metod testuje pro prazdny i neprazdny strom.
// 2. Axiomy (tedy vzdy platne vlastnosti) Red-Black Tree:
//    - Vsechny listove uzly stromu jsou *VZDY* cerne.
//    - Kazdy cerveny uzel muze mit *POUZE* cerne potomky.
//    - Vsechny cesty od kazdeho listoveho uzlu ke koreni stromu obsahuji
//      *STEJNY* pocet cernych uzlu.
//============================================================================//

/*** Konec souboru black_box_tests.cpp ***/
