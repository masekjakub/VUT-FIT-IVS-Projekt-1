//======== Copyright (c) 2021, FIT VUT Brno, All rights reserved. ============//
//
// Purpose:     Test Driven Development - priority queue code
//
// $NoKeywords: $ivs_project_1 $tdd_code.cpp
// $Author:     Jakub Mašek <xmasek19@stud.fit.vutbr.cz>
// $Date:       $2022-02-18
//============================================================================//
/**
 * @file tdd_code.cpp
 * @author JMENO PRIJMENI
 *
 * @brief Implementace metod tridy prioritni fronty.
 */

#include <stdlib.h>
#include <stdio.h>

#include "tdd_code.h"

//============================================================================//
// ** ZDE DOPLNTE IMPLEMENTACI **
//
// Zde doplnte implementaci verejneho rozhrani prioritni fronty (Priority Queue)
// 1. Verejne rozhrani fronty specifikovane v: tdd_code.h (sekce "public:")
//    - Konstruktor (PriorityQueue()), Destruktor (~PriorityQueue())
//    - Metody Insert/Remove/Find/GetHead ...
//    - Pripadne vase metody definovane v tdd_code.h (sekce "protected:")
//
// Cilem je dosahnout plne funkcni implementace prioritni fronty implementovane
// pomoci tzv. "singly linked list", ktera bude splnovat dodane testy
// (tdd_tests.cpp).
//============================================================================//

PriorityQueue::PriorityQueue(){
     m_pHead = NULL;
}

PriorityQueue::~PriorityQueue()
{
    struct Element_t *pItem = m_pHead;
    while (pItem != NULL){
        struct Element_t *tmp = pItem->pNext;
        free(pItem);
        pItem = tmp;
    }
}

void PriorityQueue::Insert(int value)
{   
    /*struct Element_t *pItem,*pPrevItem;
    pItem = m_pHead;
    printf("Curr list");
    if(m_pHead != NULL)
    do
    {
        printf("%d\n",pItem->value);
    pItem = pItem->pNext;
    }while (pItem != NULL);*/

    if (m_pHead == NULL)
    {
        Element_t *pNewItem = (struct Element_t *)malloc(sizeof(struct Element_t));
        pNewItem->value = value;
        pNewItem->pNext = NULL;
        m_pHead = pNewItem;
        return;
    }

    if(value >= m_pHead->value){
        Element_t *pNewItem = (struct Element_t *)malloc(sizeof(struct Element_t));
        pNewItem->value = value;
        pNewItem->pNext = m_pHead;
        m_pHead = pNewItem;
        return;
    }
    struct Element_t *pItem,*pPrevItem;
    pItem = m_pHead;
    while (pItem != NULL){
        if (value >= pItem->value)
        {
            Element_t *pNewItem = (struct Element_t *)malloc(sizeof(struct Element_t));
            pNewItem->value = value;
            pPrevItem->pNext = pNewItem;
            pNewItem->pNext = pItem;
            return;
        }
        pPrevItem = pItem;
        pItem = pItem->pNext;
    }

    Element_t *pNewItem = (struct Element_t *)malloc(sizeof(struct Element_t));
    pNewItem->value = value;
    pNewItem->pNext = NULL;
    pPrevItem->pNext = pNewItem;
    return;
}

bool PriorityQueue::Remove(int value)
{
    if(m_pHead == NULL){
        return false;
    }
    struct Element_t *pItem = m_pHead;
    struct Element_t *pPrevItem;

    if(value == pItem->value){
        m_pHead = pItem->pNext;
        free(pItem);
        return true;
    }
    while (pItem != NULL){
        if(pItem->value == value){
            pPrevItem->pNext = pItem->pNext;
            free(pItem);
            return true;
        }
        pPrevItem = pItem;
        pItem = pItem->pNext;
    }
    return false;
}

PriorityQueue::Element_t *PriorityQueue::Find(int value)
{
    if(m_pHead == NULL){
        return NULL;
    }

    struct Element_t *pItem = m_pHead;
    while(pItem != NULL){
        if(pItem->value == value){
            return pItem;
        }
        pItem = pItem->pNext;
    }
    return NULL;
}

size_t PriorityQueue::Length()
{
    struct Element_t *pItem = m_pHead;
    size_t count=0;
    while (pItem != NULL){
        count++;
        pItem = pItem->pNext;
    }
    return count;
}

PriorityQueue::Element_t *PriorityQueue::GetHead()
{
    return m_pHead;
}

/*** Konec souboru tdd_code.cpp ***/
