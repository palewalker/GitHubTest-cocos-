//
//  CRyuPathFinder.hpp
//  exam_findpath_0
//
//  Created by pokpoongryu on 2016. 7. 17..
//
//

#ifndef CRyuPathFinder_hpp
#define CRyuPathFinder_hpp

#include <stdio.h>
#include <iostream>

#include <cocos2d.h>


#include "CRyuNodeList.hpp"

class CMap;

using namespace cocos2d;


#define GRID_COL 50
#define GRID_ROW 30

#define MAP_INDEX 1500


/*
 created by pokpoongryu
 
    최적의 경로 찾기 담당 클래스.
 
 */
class CRyuPathFinder
{
protected:
    CRyuNodeList m_OpenList;
    CRyuNodeList m_ClosedList;
    
    SRyuPathInfo *mpRyuPathInfo = NULL;
    
    
    SRyuPathInfo *mpStart   = NULL;
    SRyuPathInfo *mpNew     = NULL;
    

    Vec2 m_StartNodeCoord;
    Vec2 m_EndNodeCoord;
    
    
public:
    //확정된 경로를 담는 곳.
    std::vector<Vec2> m_RoadVec;
    
protected:
    Vec2 ConvertNodeCoordFromIndex(int Index);
    int ConvertIndexFromNodeCoord(Vec2 nodecoord);
    
    void ClearRoadData();

    
public:
    CRyuPathFinder();
    virtual ~CRyuPathFinder();
    
    void Clear();
    void Create();
    void Destroy();
	
    
    
    void InputClickData( Vec2 tVecBegin,Vec2 tVecEnd );
    bool FindPath(CMap *tpMap);
    
    void SetRoadData();
};

#endif /* CRyuPathFinder_hpp */
