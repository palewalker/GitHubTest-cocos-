//
//  CRyuNodeList.cpp
//  exam_findpath_0
//
//  Created by pokpoongryu on 2016. 7. 18..
//
//

#include "CRyuNodeList.hpp"

#include <cocos2d.h>

using namespace cocos2d;


#include <memory.h>

CRyuNodeList::CRyuNodeList()
{
    Clear();
}
CRyuNodeList::~CRyuNodeList()
{
    Destroy();
}
void CRyuNodeList::Clear()
{
    mpHead = NULL;
    mpTail = NULL;
}
void CRyuNodeList::Destroy()
{
    if(mpHead != NULL)
    {
        delete mpHead;
        mpHead = NULL;
    }
    if(mpTail != NULL)
    {
        delete mpTail;
        mpTail = NULL;
    }
    
    Clear();
}

void CRyuNodeList::Create()
{
    if(mpHead == NULL && mpTail == NULL)
    {
        mpHead = new SRyuNode();
        mpTail = new SRyuNode();
        
        mpHead->mpNext = mpTail;
        mpTail->mpNext = mpTail;
    }
}

bool CRyuNodeList::IsEmpty()
{
    SRyuNode *t = NULL;
    
    t = mpHead->mpNext;
    if( t != mpTail )
    {
        return false;
    }
    
    return true;
}
/*
bool CRyuNodeList::IsBe(SRyuPathInfo *tpPathInfo)
{
    
    SRyuNode *t = NULL;
    
    t = mpHead->mpNext;
    
    while( t != mpTail )
    {
        if(t->mpPathInfo->mX == tpPathInfo->mX && t->mpPathInfo->mY == tpPathInfo->mY)
        {
            //if( tpPathInfo->mCostFromStart <= t->mpPathInfo->mCostFromStart)
            if( tpPathInfo->mTotalCost <= t->mpPathInfo->mTotalCost)
            {
                //갱신
                //t->mpPathInfo->mX = tpPathInfo->mX;
                //t->mpPathInfo->mY = tpPathInfo->mY;
                t->mpPathInfo->mCostFromStart = tpPathInfo->mCostFromStart;
                t->mpPathInfo->mCostToGoal = tpPathInfo->mCostToGoal;
                t->mpPathInfo->mTotalCost = tpPathInfo->mTotalCost;
                //t->mpPathInfo->mpParentPathNode = tpPathInfo->mpParentPathNode;
                
                return true;
            }
            else
            {
            
                return false;
            }
        }
        else
        {
            t = t->mpNext;
        }
    }
    return false;
    
    
    
}
 */


SRyuPathInfo *CRyuNodeList::IsBe(SRyuPathInfo *tpPathInfo)
{
    SRyuPathInfo *tpResult = NULL;
    
    SRyuNode *t = NULL;
    t = mpHead->mpNext;
    
    while( t != mpTail )
    {
        if(t->mpPathInfo->mX == tpPathInfo->mX && t->mpPathInfo->mY == tpPathInfo->mY)
        {
            tpResult = t->mpPathInfo;
            
            break;
        }
        else
        {
            t = t->mpNext;
        }
    }
    
    
    
    return tpResult;
}



SRyuPathInfo *CRyuNodeList::FindPathInfoList(SRyuPathInfo *tpPathInfo)
{
    SRyuNode *tpRyuNode = NULL;
    
    tpRyuNode = mpHead->mpNext;
    
    while(tpRyuNode != mpTail)
    {
        if(tpRyuNode->mpPathInfo->mTotalCost != tpPathInfo->mTotalCost)
        {
            return tpRyuNode->mpPathInfo;
        }
        
        tpRyuNode = tpRyuNode->mpNext;
    }
    
    return NULL;
    
    
}
SRyuNode *CRyuNodeList::OrderedInsert(SRyuPathInfo *tpPathInfo)
{
    SRyuNode *s = NULL;
    SRyuNode *p = NULL;
    SRyuNode *tpNewNode = NULL;
    
    //OpenList
    p = mpHead;
    s = p->mpNext;
    
    while(s !=mpTail && s->mpPathInfo->mTotalCost <= tpPathInfo->mTotalCost)
    {
        p = p->mpNext;
        s = p->mpNext;
    }
    tpNewNode = new SRyuNode();
    tpNewNode->mpPathInfo = tpPathInfo;
    
    p->mpNext = tpNewNode;
    tpNewNode->mpNext = s;
    
    
    return tpNewNode;
    
}
void CRyuNodeList::SetLocation(SRyuPathInfo *tpPathInfo)
{
    SRyuPathInfo *tmp = NULL;
    
    tmp = FindPathInfoList(tpPathInfo);
    
    tmp->mX = tpPathInfo->mX;
    tmp->mY = tpPathInfo->mY;
}
void CRyuNodeList::Reset()
{
    SRyuNode *t = NULL;
    SRyuNode *s = NULL;
    
    t=mpHead->mpNext;
    while(t!=mpTail)
    {
        s = t;
        t = t->mpNext;
        
        //free(s);
        delete s;
    }
    mpHead->mpNext = mpTail;
    
}



bool CRyuNodeList::DeletePathInfo(SRyuPathInfo *tpPathInfo)
{	
    SRyuNode *s = NULL;
    SRyuNode *p = NULL;
    
    p = mpHead;
    s = p->mpNext;
    
    while(s!=mpTail && s->mpPathInfo!=tpPathInfo)
    {
        p = p->mpNext;
        s = p->mpNext;
    }
    
    if(s != mpTail)
    {
        p->mpNext = s->mpNext;
        //free(s);
        delete s;
        
        return true;
    }
    else
        return false;
}
SRyuPathInfo *CRyuNodeList::Pop()
{
    SRyuNode *t = NULL;
    SRyuPathInfo *i = NULL;
    
    if(mpHead->mpNext == mpTail)
    {
        return NULL;
    }
    
    t = mpHead->mpNext;
    i = t->mpPathInfo;
    mpHead->mpNext = t->mpNext;
    
    delete t;
    
    return i;
}




void CRyuNodeList::TestDisplayCount(string tString)
{
    mTestCount = 0;
    
    SRyuNode *t = NULL;
    
    t=mpHead->mpNext;
    while(t!=mpTail)
    {
        mTestCount++;
        
        t = t->mpNext;
    }
    mpHead->mpNext = mpTail;
    
    log("%s Count: %d",tString.c_str(), (int)mTestCount );
}

