//
//  CRyuPathFinder.hpp
//  exam_findpath_0
//
//  Created by pokpoongryu on 2016. 7. 17..
//
//

#pragma once

#include <stdio.h>
#include <iostream>

#include <cocos2d.h>


#include "CNodeList.h"
#include "Map.h"

using namespace cocos2d;


#define GRID_COL 50
#define GRID_ROW 30

#define MAP_INDEX 1500


/*
created by pokpoongryu

������ ��� ã�� ��� Ŭ����.

*/
class CPathFinder
{
protected:
	CNodeList m_OpenList;
	CNodeList m_ClosedList;

	SPathInfo *mpPathInfo = NULL;


	SPathInfo *mpStart = NULL;
	SPathInfo *mpNew = NULL;


	Vec2 m_StartNodeCoord;
	Vec2 m_EndNodeCoord;

	


public:
	//Ȯ���� ��θ� ��� ��.
	std::vector<Vec2> m_RoadVec;

protected:
	Vec2 ConvertNodeCoordFromIndex(int Index);
	int ConvertIndexFromNodeCoord(Vec2 nodecoord);

	void ClearRoadData();


public:
	CPathFinder();
	virtual ~CPathFinder();

	void Clear();
	void Create();
	void Destroy();


	void InputUnitData(Vec2 tVecBegin, Vec2 tVecEnd);
	bool FindPath(CMap *tpMap);

	void SetRoadData();
	void Reset();
};

