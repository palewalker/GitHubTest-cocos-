#pragma once

#include <stdio.h>
#include <vector>
#include <cocos2d.h>
#include<string>

using namespace cocos2d;
using namespace std;

struct SPathInfo
{
	int mX = 0;
	int mY = 0;

	float mTotalCost = 0;
	float mCostFromStart = 0;
	float mCostToGoal = 0;

	bool mIsOpen = false;
	bool mIsClosed = false;

	SPathInfo *mpParentPathNode = NULL;//경로 원소의 링크
};

struct SNode
{
	SPathInfo *mpPathInfo = NULL; //data

	SNode *mpNext = NULL; //LINK

};

typedef vector<SPathInfo *> ::iterator PathNodeVecIter;

class CNodeList
{
private:
	SNode *mpHead = NULL;
	SNode *mpTail = NULL;

public:
	CNodeList();
	virtual ~CNodeList();

	void Clear();

	void Create();
	void Destroy();

	void Reset();

	bool IsEmpty();
	SPathInfo *IsBe(SPathInfo *tpnode);

	void SetLocation(SPathInfo *tpNode);
	SPathInfo *Pop();

	SPathInfo *FindPathInfoList(SPathInfo *tpPathInfo);

	bool DeletePathInfo(SPathInfo *tpPathInfo);

	SNode *OrderedInsert(SPathInfo *tpPathInfo);

	void TestDisplayCount(string tString);

	int mTestCount = 0;

};