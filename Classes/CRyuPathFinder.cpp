//
//  CRyuPathFinder.cpp
//  exam_findpath_0
//
//  Created by pokpoongryu on 2016. 7. 17..
//
//

#include "CRyuPathFinder.hpp"

#include "Map.h"


CRyuPathFinder::CRyuPathFinder()
{
    Clear();
}
CRyuPathFinder::~CRyuPathFinder()
{
    
}

void CRyuPathFinder::Clear()
{
    m_OpenList.Clear();
    m_ClosedList.Clear();

    
    mpStart            = NULL;
    mpNew              = NULL;
    
    
    m_StartNodeCoord.x  = 0;
    m_StartNodeCoord.y  = 0;
    m_EndNodeCoord.x    = 0;
    m_EndNodeCoord.y    = 0;
    
    
    
    m_RoadVec.clear();
    
}
void CRyuPathFinder::Create()
{
    m_OpenList.Create();
    m_ClosedList.Create();
    
    
    
    m_RoadVec.reserve(1000);
    
}
void CRyuPathFinder::Destroy()
{
    m_OpenList.Destroy();
    m_ClosedList.Destroy();
    
    
    
    m_RoadVec.clear();
    
}
void CRyuPathFinder::InputClickData(Vec2 tVecBegin,Vec2 tVecEnd)
{
	m_RoadVec.clear();

	m_OpenList.Reset();
	m_ClosedList.Reset();

	mpRyuPathInfo = NULL;

    m_StartNodeCoord.x  = tVecBegin.x;
    m_StartNodeCoord.y  = tVecBegin.y;
    
    
    m_EndNodeCoord.x    = tVecEnd.x;
    m_EndNodeCoord.y    = tVecEnd.y;
    
}
Vec2 CRyuPathFinder::ConvertNodeCoordFromIndex (int Index)
{
    Vec2 tNodeCoord;
    
    
    tNodeCoord.y        = Index/GRID_COL;
    tNodeCoord.x        = Index%GRID_COL;
    
    return tNodeCoord;
}
int CRyuPathFinder::ConvertIndexFromNodeCoord (Vec2 nodecoord)
{
    int tResult = 0;
    
    tResult = GRID_COL*nodecoord.y + nodecoord.x;
    
    return tResult;
}


//이 부분이 길찾기 알고리즘이 구현된 핵심 부분이다.
bool CRyuPathFinder::FindPath (CMap *tpMap)
{
	


    int tStartX = m_StartNodeCoord.x;
    int tStartY = m_StartNodeCoord.y;
    
    int tEndX = m_EndNodeCoord.x;
    int tEndY = m_EndNodeCoord.y;
    
    
    
    
    
    
    mpStart = new SRyuPathInfo();          //P
    
    mpStart->mX                 = tStartX;
    mpStart->mY                 = tStartY;
    mpStart->mpParentPathNode            = NULL;
    
    mpStart->mCostFromStart     = 0;

    mpStart->mCostToGoal        = (tEndX - mpStart->mX)*(tEndX - mpStart->mX)+
                                    (tEndY - mpStart->mY)*(tEndY - mpStart->mY);

    mpStart->mTotalCost         = mpStart->mCostFromStart + mpStart->mCostToGoal;
    
    mpStart->mIsOpen             = false;
    mpStart->mIsClosed           = false;
    
    
    
    
    m_OpenList.OrderedInsert(mpStart);
    mpStart->mIsOpen = true;
    
    while( !m_OpenList.IsEmpty() )
    {
        SRyuPathInfo *tpNode = NULL;                   //B
        
        tpNode            = m_OpenList.Pop();
        tpNode->mIsOpen   = false;
        
      
        if(tpNode->mX == tEndX && tpNode->mY == tEndY)
        {
            mpRyuPathInfo = tpNode;
            
            break;
        }
        else
        {
            
            //for(int tDir=0; tDir<8; tDir++)
            for(int tDir=0; tDir<4; tDir++)
            {
         
                mpNew = NULL;
                mpNew = new SRyuPathInfo();            //C
                
                
                switch(tDir)
                {
                        
                    case 0:
                    {
                        mpNew->mX = tpNode->mX + 1;
                        mpNew->mY = tpNode->mY;
                        
                        mpNew->mIsOpen    =false;
                        mpNew->mIsClosed  =false;
                    }
                        
                        break;
                        
                        
                    case 1:
                    {
                        mpNew->mX = tpNode->mX;
                        mpNew->mY = tpNode->mY - 1;
                        
                        mpNew->mIsOpen = false;
                        mpNew->mIsClosed = false;
                    }
                        
                        break;
                        
                       
                    case 2:
                    {
                        mpNew->mX = tpNode->mX - 1;
                        mpNew->mY = tpNode->mY;
                        
                        mpNew->mIsOpen =false;
                        mpNew->mIsClosed =false;
                    }
                        
                        break;
                        
                       
                    case 3:
                    {
                        mpNew->mX = tpNode->mX;
                        mpNew->mY = tpNode->mY + 1;
                        
                        mpNew->mIsOpen = false;
                        mpNew->mIsClosed = false;
                    }
                        
                        break;

                        
                      

                }
                
				
				//else
				//{
				//	tResult[mpNew->mY][mpNew->mX] = 0;
				//}



				//if( 1 == m_Tile[ mpNew->mY ][ mpNew->mX ] )
				static int tResult[50][30] = { 0, };
				int tGID = tpMap->GetTMX()->getLayer("TileLayer")->
					getTileGIDAt(Vec2(mpNew->mX, mpNew->mY));
				Value tValue = tpMap->GetTMX()->getPropertiesForGID(tGID);

				if (false == tValue.isNull())
				{
					tResult[mpNew->mY][mpNew->mX] = tValue.asValueMap()["Attrib"].asInt();
				}
				if (1 == tResult[mpNew->mY][mpNew->mX])
				{
					delete mpNew;
					mpNew = NULL;

					continue;
				}
                
                
                if(mpNew->mX < 0 || mpNew->mX >= GRID_COL)
                {
                    delete mpNew;
                    mpNew = NULL;
                    
                    continue;
                }
                if(mpNew->mY < 0 || mpNew->mY >= GRID_ROW)
                {
                    delete mpNew;
                    mpNew = NULL;
                    
                    continue;
                }

				
				//여기 코드 때문에 경로 잘 못찾는 것으로 추정.
				
			
				

                
                
                int tNewCost = 0;               //f
                
                
                tNewCost = tpNode->mCostFromStart+
                    (tpNode->mX - mpNew->mX)*(tpNode->mX - mpNew->mX)+
                    (tpNode->mY - mpNew->mY)*(tpNode->mY - mpNew->mY);
                
                
                
                mpNew->mpParentPathNode     = tpNode;
                
               
                mpNew->mCostFromStart        = tNewCost;                                    //f
                mpNew->mCostToGoal           = (mpNew->mX - tEndX)*(mpNew->mX - tEndX)+
                                                (mpNew->mY - tEndY)*(mpNew->mY - tEndY);    //g
                
               
                mpNew->mTotalCost            = mpNew->mCostFromStart + mpNew->mCostToGoal;  //h
                
                
                
          
                SRyuPathInfo *tpPathInfoA = NULL;
                tpPathInfoA = m_OpenList.IsBe( mpNew );
                
                SRyuPathInfo *tpPathInfoB = NULL;
                tpPathInfoB = m_ClosedList.IsBe( mpNew );
                
                if( NULL != tpPathInfoA )
                {
                    if( mpNew->mTotalCost <= tpPathInfoA->mTotalCost)
                    {
                        //경로비용 데이터 갱신
                        //tpPathInfoA->mX           = mpNew->mX;
                        //tpPathInfoA->mY           = mpNew->mY;
                        tpPathInfoA->mCostFromStart = mpNew->mCostFromStart;
                        tpPathInfoA->mCostToGoal    = mpNew->mCostToGoal;
                        tpPathInfoA->mTotalCost     = mpNew->mTotalCost;
                        //tpPathInfoA->mpParentPathNode = mpNew->mpParentPathNode;
                    }
                    
                    delete mpNew;
                    mpNew = NULL;
                    
                    continue;
                }
                else if( NULL != tpPathInfoB )
                {
                    if( mpNew->mTotalCost <= tpPathInfoB->mTotalCost)
                    {
                        //경로비용 데이터 갱신
                        //tpPathInfoB->mX           = mpNew->mX;
                        //tpPathInfoB->mY           = mpNew->mY;
                        tpPathInfoB->mCostFromStart = mpNew->mCostFromStart;
                        tpPathInfoB->mCostToGoal    = mpNew->mCostToGoal;
                        tpPathInfoB->mTotalCost     = mpNew->mTotalCost;
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
                    
                    mpNew->mIsOpen                = false;
                    mpNew->mIsClosed              = false;
                    
                    m_OpenList.OrderedInsert( mpNew );
                    mpNew->mIsOpen                = true;
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




void CRyuPathFinder::SetRoadData()
{
    ClearRoadData();
    
    SRyuPathInfo *tpEndNode = NULL;
    
    tpEndNode = mpRyuPathInfo;
    
    
    if( NULL != tpEndNode )
    {
        Vec2 tTempNode;
        
        while( tpEndNode->mpParentPathNode != NULL )
        {
            tTempNode.x = tpEndNode->mX;
            tTempNode.y = tpEndNode->mY;
            
            
            m_RoadVec.push_back(tTempNode);
            
            
            tpEndNode = tpEndNode->mpParentPathNode;
            
            log("CRyuPathFinder: x: %d, y: %d ", (int)tTempNode.x, (int)tTempNode.y );
        }
    }
    
    
    
    
    
    
    SRyuPathInfo *node = NULL;
    
    while(!m_OpenList.IsEmpty())
    {
        node = m_OpenList.Pop();
        if(node!=NULL)
        {
            delete node;
            node=NULL;
        }
    }
    while(!m_ClosedList.IsEmpty())
    {
        node=m_ClosedList.Pop();
        if(node!=NULL)
        {
            delete node;
            node=NULL;
        }
    }
    
    
    
}
void CRyuPathFinder::ClearRoadData()
{
    m_RoadVec.clear();
}



