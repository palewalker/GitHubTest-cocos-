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


//�� �κ��� ��ã�� �˰����� ������ �ٽ� �κ��̴�.
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
	//��� ����: �����Ÿ� �˻�
	mpStart->mCostToGoal = (tEndX - mpStart->mX)*(tEndX - mpStart->mX) +
		(tEndY - mpStart->mY)*(tEndY - mpStart->mY);
	//�Ѻ��
	mpStart->mTotalCost = mpStart->mCostFromStart + mpStart->mCostToGoal;

	//���� ��� ǥ��
	mpStart->mIsOpen = false;
	mpStart->mIsClosed = false;




	m_OpenList.OrderedInsert(mpStart);
	mpStart->mIsOpen = true;

	//open list���� ��带 �ϳ� ������
	while (1)
	{
		if (m_OpenList.IsEmpty())
		{
			break;
		}

		SPathInfo *tpNode = NULL;                   //B

		tpNode = m_OpenList.Pop();
		tpNode->mIsOpen = false;

		//��ǥ�����̸� ���ã�⸦ �ߴ��ϰ�
		if (tpNode->mX == tEndX && tpNode->mY == tEndY)
		{
			mpPathInfo = tpNode;

			break;
		}
		else
		{
			//��ǥ������ �ƴϸ�, ������ �����鿡 ���� ���� ������κ���� �˻��Ѵ�.

			//�� ���� �˻�.
			//8������ �˻��ϰ� ������, 8���� ���ڸ� switch������ ���ָ� �ȴ�.
			//for(int tDir=0; tDir<8; tDir++)
			for (int tDir = 0; tDir<4; tDir++)
			{
				//�ش� ���⿡ ����, ��γ�带 ���� �ϳ� ����
				mpNew = NULL;
				mpNew = new SPathInfo();            //C


				switch (tDir)
				{
					//��
					case 0:
					{
						mpNew->mX = tpNode->mX + 1;
						mpNew->mY = tpNode->mY;

						mpNew->mIsOpen = false;
						mpNew->mIsClosed = false;
					}

					break;

					//��
					case 1:
					{
						mpNew->mX = tpNode->mX;
						mpNew->mY = tpNode->mY - 1;

						mpNew->mIsOpen = false;
						mpNew->mIsClosed = false;
					}

					break;

					//��
					case 2:
					{
						mpNew->mX = tpNode->mX - 1;
						mpNew->mY = tpNode->mY;

						mpNew->mIsOpen = false;
						mpNew->mIsClosed = false;
					}

					break;

					//��
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

												//��� ���: ���⼭�� �����Ÿ��� ������� ��� ���������� �� ����� �������(f)���� �ٷ�� �ִ�.
				tNewCost = tpNode->mCostFromStart +
					(tpNode->mX - mpNew->mX)*(tpNode->mX - mpNew->mX) +
					(tpNode->mY - mpNew->mY)*(tpNode->mY - mpNew->mY);



				mpNew->mpParentPathNode = tpNode;

				//��� ���: ���⼭�� �����Ÿ��� ������� ��� �������(g)�� �ٷ�� �ִ�.
				mpNew->mCostFromStart = tNewCost;                                    //f
				mpNew->mCostToGoal = (mpNew->mX - tEndX)*(mpNew->mX - tEndX) +
					(mpNew->mY - tEndY)*(mpNew->mY - tEndY);    //g

																//h = f + g, �̰���  '���� �Ѻ�� = ��������� ���� ��� + ���ݺ��� ������������ �������' �̴�.
				mpNew->mTotalCost = mpNew->mCostFromStart + mpNew->mCostToGoal;  //h



																				 //���¸���Ʈ�� �ְų� Ŭ�����Ʈ�� ������ �ش� ����� ��κ�� �����͸� �����Ѵ�.
				SPathInfo *tpPathInfoA = NULL;
				tpPathInfoA = m_OpenList.IsBe(mpNew);

				SPathInfo *tpPathInfoB = NULL;
				tpPathInfoB = m_ClosedList.IsBe(mpNew);

				if (NULL != tpPathInfoA)
				{
					if (mpNew->mTotalCost <= tpPathInfoA->mTotalCost)
					{
						//��κ�� ������ ����
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
						//��κ�� ������ ����
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
					//���¸���Ʈ���� ���� Ŭ�����Ʈ���� ���� ���� ����� h����� �� ����(ȿ������) ����̸�
					//�� ��带 OpenList�� �ִ´�.

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


