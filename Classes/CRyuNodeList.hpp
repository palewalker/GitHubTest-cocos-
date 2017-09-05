//
//  CRyuNodeList.hpp
//  exam_findpath_0
//
//  Created by pokpoongryu on 2016. 7. 18..
//
//

#ifndef CRyuNodeList_hpp
#define CRyuNodeList_hpp

#include <stdio.h>
#include <vector>

#include <string>
using namespace std;

//경로를 이루는 하나의 원소를 나타낸다. (이 원소의 정보는 기본적으로 '위치' 이며 그 외 부가적인 정보들이 함께 담겨 있다.)
//다음에 나올 CRyuNode의 값 부분에 해당한다.
//
//멤버로 다음 원소의 링크들을 가지고 있고
//path find 동작이 모두 끝난 후에는 마지막 원소의 링크에 이전 모든 경로 원소가 연결되어 있어
//이것이 바로 원하는 경로이다.
struct SRyuPathInfo
{
    int mX = 0;
    int mY = 0;
    
    int mTotalCost           = 0;
    int mCostFromStart       = 0;
    int mCostToGoal          = 0;
    
    
    bool mIsOpen            = false;
    bool mIsClosed          = false;
    
    
    SRyuPathInfo *mpParentPathNode = NULL; //경로 원소의 링크.
};

//'심플링크드리스트'를 구성할 노드
struct SRyuNode
{
    SRyuPathInfo *mpPathInfo   = NULL;   //data
    
    SRyuNode *mpNext        = NULL;   //link
};


typedef std::vector<SRyuPathInfo *>::iterator PathNodeVecItor;

//'SRyuNode타입의 노드들로 구성된 심플링크드리스트' 클래스
//이것은 길찾기 알고리즘에서 쓰일 OpenList, ClosedList, MasterList 가 될 것이다. 
class CRyuNodeList
{
public:
    int mTestCount = 0;
    
    void TestDisplayCount(string tString);
    
private:
    SRyuNode *mpHead = NULL;        //link
    SRyuNode *mpTail = NULL;        //link
    
public:
    CRyuNodeList();
    virtual ~CRyuNodeList();
    
    void Clear();
    
    void Create();
    void Destroy();
    
    void Reset();
    
    bool IsEmpty();
    //bool IsBe(SRyuPathInfo *node);
    SRyuPathInfo *IsBe(SRyuPathInfo *node);
    
    void SetLocation(SRyuPathInfo *node);
    SRyuPathInfo *Pop();
    
    
    
    SRyuPathInfo *FindPathInfoList(SRyuPathInfo *tpPathInfo);
    
    bool DeletePathInfo(SRyuPathInfo *tpPathInfo);
    
    
    SRyuNode *OrderedInsert(SRyuPathInfo *tpPathInfo);
    
    
    
};



#endif /* CRyuNodeList_hpp */
