//
//  CPathFinder.cpp
//  exam_findpath_0
//
//  Created by pokpoongryu on 2016. 7. 17..
//
//

#include "CPathFinder.h"


CPathFinder::CPathFinder()
{
	Clear();
}
CPathFinder::~CPathFinder()
{

}

void CPathFinder::Clear()
{
	m_OpenList.Clear();
	m_ClosedList.Clear();


	mpStart = NULL;
	mpNew = NULL;


	m_StartNodeCoord.x = 0;
	m_StartNodeCoord.y = 0;
	m_EndNodeCoord.x = 0;
	m_EndNodeCoord.y = 0;



	m_RoadVec.clear();

}
void CPathFinder::Create()
{
	m_OpenList.Create();
	m_ClosedList.Create();



	m_RoadVec.reserve(1000);

}
void CPathFinder::Destroy()
{
	m_OpenList.Destroy();
	m_ClosedList.Destroy();



	m_RoadVec.clear();

}
void CPathFinder::InputUnitData(Vec2 tVecBegin, Vec2 tVecEnd)
{
	m_StartNodeCoord.x = tVecBegin.x;
	m_StartNodeCoord.y = tVecBegin.y;


	m_EndNodeCoord.x = tVecEnd.x;
	m_EndNodeCoord.y = tVecEnd.y;

}
Vec2 CPathFinder::ConvertNodeCoordFromIndex(int Index)
{
	Vec2 tNodeCoord;


	tNodeCoord.y = Index / GRID_COL;
	tNodeCoord.x = Index%GRID_COL;

	return tNodeCoord;
}
int CPathFinder::ConvertIndexFromNodeCoord(Vec2 nodecoord)
{
	int tResult = 0;

	tResult = GRID_COL*nodecoord.y + nodecoord.x;

	return tResult;
}


//이 부분이 길찾기 알고리즘이 구현된 핵심 부분이다.
bool CPathFinder::FindPath(CMap *tpMap)
{
	int tStartX = m_StartNodeCoord.x;
	int tStartY = m_StartNodeCoord.y;

	int tEndX = m_EndNodeCoord.x;
	int tEndY = m_EndNodeCoord.y;






	mpStart = new SPathInfo();          //P

	mpStart->mX = tStartX;
	mpStart->mY = tStartY;
	mpStart->mpParentPathNode = NULL;

	mpStart->mCostFromStart = 0;
	//비용 추정: 직선거리 검사
	mpStart->mCostToGoal = (tEndX - mpStart->mX)*(tEndX - mpStart->mX) +
		(tEndY - mpStart->mY)*(tEndY - mpStart->mY);
	//총비용
	mpStart->mTotalCost = mpStart->mCostFromStart + mpStart->mCostToGoal;

	//속한 목록 표시
	mpStart->mIsOpen = false;
	mpStart->mIsClosed = false;




	m_OpenList.OrderedInsert(mpStart);
	mpStart->mIsOpen = true;

	//open list에서 노드를 하나 꺼내어
	while (1)
	{
		if (m_OpenList.IsEmpty())
		{
			break;
		}

		SPathInfo *tpNode = NULL;                   //B

		tpNode = m_OpenList.Pop();
		tpNode->mIsOpen = false;

		//목표지점이면 경로찾기를 중단하고
		if (tpNode->mX == tEndX && tpNode->mY == tEndY)
		{
			mpPathInfo = tpNode;

			break;
		}
		else
		{
			//목표지점이 아니면, 인접한 지점들에 대해 각각 추정경로비용을 검사한다.

			//네 방향 검사.
			//8방향을 검사하고 싶으면, 8방향 격자를 switch문으로 해주면 된다.
			//for(int tDir=0; tDir<8; tDir++)
			for (int tDir = 0; tDir<4; tDir++)
			{
				//해당 방향에 따라, 경로노드를 새로 하나 만듦
				mpNew = NULL;
				mpNew = new SPathInfo();            //C


				switch (tDir)
				{
					//우
					case 0:
					{
						mpNew->mX = tpNode->mX + 1;
						mpNew->mY = tpNode->mY;

						mpNew->mIsOpen = false;
						mpNew->mIsClosed = false;
					}

					break;

					//하
					case 1:
					{
						mpNew->mX = tpNode->mX;
						mpNew->mY = tpNode->mY - 1;

						mpNew->mIsOpen = false;
						mpNew->mIsClosed = false;
					}

					break;

					//좌
					case 2:
					{
						mpNew->mX = tpNode->mX - 1;
						mpNew->mY = tpNode->mY;

						mpNew->mIsOpen = false;
						mpNew->mIsClosed = false;
					}

					break;

					//상
					case 3:
					{
						mpNew->mX = tpNode->mX;
						mpNew->mY = tpNode->mY + 1;

						mpNew->mIsOpen = false;
						mpNew->mIsClosed = false;
					}

					break;




				}


			


				if (mpNew->mX < 0 || mpNew->mX >= GRID_COL)
				{
					delete mpNew;
					mpNew = NULL;

					continue;
				}
				if (mpNew->mY < 0 || mpNew->mY >= GRID_ROW)
				{
					delete mpNew;
					mpNew = NULL;

					continue;
				}

				int tResult = 0;
				int tGID = tpMap->GetTMX()->getLayer("TileLayer")->
					getTileGIDAt(Vec2(mpNew->mX, mpNew->mY));
				Value tValue = tpMap->GetTMX()->getPropertiesForGID(tGID);

				if (false == tValue.isNull())
				{
					tResult = tValue.asValueMap()["Attrib"].asInt();
				}
				else
				{

				}

				if (1 == tResult)
				{
					delete mpNew;
					mpNew = NULL;

					continue;
				}



				int tNewCost = 0;               //f

												//비용 계산: 여기서는 직선거리를 비용으로 삼아 시작점에서 새 노드의 실제비용(f)으로 다루고 있다.
				tNewCost = tpNode->mCostFromStart +
					(tpNode->mX - mpNew->mX)*(tpNode->mX - mpNew->mX) +
					(tpNode->mY - mpNew->mY)*(tpNode->mY - mpNew->mY);



				mpNew->mpParentPathNode = tpNode;

				//비용 계산: 여기서는 직선거리를 비용으로 삼아 추정비용(g)을 다루고 있다.
				mpNew->mCostFromStart = tNewCost;                                    //f
				mpNew->mCostToGoal = (mpNew->mX - tEndX)*(mpNew->mX - tEndX) +
					(mpNew->mY - tEndY)*(mpNew->mY - tEndY);    //g

																//h = f + g, 이것은  '추정 총비용 = 현재까지의 실제 비용 + 지금부터 목적지까지의 추정비용' 이다.
				mpNew->mTotalCost = mpNew->mCostFromStart + mpNew->mCostToGoal;  //h



																				 //오픈리스트에 있거나 클로즈리스트에 있으면 해당 노드의 경로비용 데이터만 갱신한다.
				SPathInfo *tpPathInfoA = NULL;
				tpPathInfoA = m_OpenList.IsBe(mpNew);

				SPathInfo *tpPathInfoB = NULL;
				tpPathInfoB = m_ClosedList.IsBe(mpNew);

				if (NULL != tpPathInfoA)
				{
					if (mpNew->mTotalCost <= tpPathInfoA->mTotalCost)
					{
						//경로비용 데이터 갱신
						//tpPathInfoA->mX           = mpNew->mX;
						//tpPathInfoA->mY           = mpNew->mY;
						tpPathInfoA->mCostFromStart = mpNew->mCostFromStart;
						tpPathInfoA->mCostToGoal = mpNew->mCostToGoal;
						tpPathInfoA->mTotalCost = mpNew->mTotalCost;
						//tpPathInfoA->mpParentPathNode = mpNew->mpParentPathNode;
					}

					delete mpNew;
					mpNew = NULL;

					continue;
				}
				else if (NULL != tpPathInfoB)
				{
					if (mpNew->mTotalCost <= tpPathInfoB->mTotalCost)
					{
						//경로비용 데이터 갱신
						//tpPathInfoB->mX           = mpNew->mX;
						//tpPathInfoB->mY           = mpNew->mY;
						tpPathInfoB->mCostFromStart = mpNew->mCostFromStart;
						tpPathInfoB->mCostToGoal = mpNew->mCostToGoal;
						tpPathInfoB->mTotalCost = mpNew->mTotalCost;
						//tpPathInfoB->mpParentPathNode = mpNew->mpParentPathNode;
					}

					delete mpNew;
					mpNew = NULL;

					continue;
				}
				else
				{
					//오픈리스트에도 없고 클로즈리스트에도 없고 새로 계산한 h비용이 더 작은(효율적인) 비용이면
					//이 노드를 OpenList에 넣는다.

					mpNew->mIsOpen = false;
					mpNew->mIsClosed = false;

					m_OpenList.OrderedInsert(mpNew);
					mpNew->mIsOpen = true;
				}
			}//


		}

		m_ClosedList.OrderedInsert(tpNode);
		tpNode->mIsClosed = true;

	}//while



	 //test
	m_OpenList.TestDisplayCount("open list");
	m_ClosedList.TestDisplayCount("closed list");





	return true;
}




void CPathFinder::SetRoadData()
{
	ClearRoadData();

	SPathInfo *tpEndNode = NULL;

	tpEndNode = mpPathInfo;


	if (NULL != tpEndNode)
	{
		Vec2 tTempNode;

		while (tpEndNode->mpParentPathNode != NULL)
		{
			tTempNode.x = tpEndNode->mX;
			tTempNode.y = tpEndNode->mY;


			m_RoadVec.push_back(tTempNode);


			tpEndNode = tpEndNode->mpParentPathNode;

			log("CPathFinder: x: %d, y: %d ", (int)tTempNode.x, (int)tTempNode.y);
		}
	}






	SPathInfo *node = NULL;

	while (!m_OpenList.IsEmpty())
	{
		node = m_OpenList.Pop();
		if (node != NULL)
		{
			delete node;
			node = NULL;
		}
	}
	while (!m_ClosedList.IsEmpty())
	{
		node = m_ClosedList.Pop();
		if (node != NULL)
		{
			delete node;
			node = NULL;
		}
	}



}
void CPathFinder::ClearRoadData()
{
	m_RoadVec.clear();
}


