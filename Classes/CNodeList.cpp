#include "CNodeList.h"
#include <memory.h>

CNodeList::CNodeList()
{
	Clear();
}
CNodeList::~CNodeList()
{
	Destroy();
}

void CNodeList::Clear()
{
	mpHead = NULL;
	mpTail = NULL;
}

void CNodeList::Destroy()
{
	if (mpHead != NULL)
	{
		delete mpHead;
		mpHead = NULL;
	}
	if (mpTail != NULL)
	{
		delete mpTail;
		mpTail = NULL;
	}

	Clear();
}

void CNodeList::Create()
{
	if (mpHead == NULL && mpTail == NULL)
	{
		mpHead = new SNode();
		mpTail = new SNode();

		mpHead->mpNext = mpTail;
		mpTail->mpNext = mpTail;
	}
}

bool CNodeList::IsEmpty()
{
	SNode *tNode = NULL;

	tNode = mpHead->mpNext;
	if (tNode != mpTail)
	{

		return false;
	}

	return true;
}

SPathInfo *CNodeList::IsBe(SPathInfo *tpPathInfo)
{
	SPathInfo *tpResult = NULL;

	SNode *tpNode = NULL;

	tpNode = mpHead->mpNext;

	while (tpNode != mpTail)
	{
		if (tpNode->mpPathInfo->mX == tpPathInfo->mX && tpNode->mpPathInfo->mY == tpPathInfo->mY)
		{
			tpResult = tpNode->mpPathInfo;

			break;
		}
		else
		{
			tpNode = tpNode->mpNext;
		}
	}

	return tpResult;
}

SPathInfo *CNodeList::FindPathInfoList(SPathInfo *tpPathInfo)
{
	SNode *tpNode = NULL;

	tpNode = mpHead->mpNext;

	while (tpNode != mpTail)
	{
		if (tpNode->mpPathInfo->mTotalCost != tpPathInfo->mTotalCost)
		{
			return tpNode->mpPathInfo;
		}
		tpNode = tpNode->mpNext;
	}

	return NULL;
}

SNode *CNodeList::OrderedInsert(SPathInfo *tpPathInfo)
{
	SNode *s = NULL;
	SNode *p = NULL;
	SNode *tpNewNode = NULL;

	//OpenList
	p = mpHead;
	s = p->mpNext;

	while (s != mpTail && s->mpPathInfo->mTotalCost <= tpPathInfo->mTotalCost)
	{
		p = p->mpNext;
		s = p->mpNext;
	}
	tpNewNode = new SNode();
	tpNewNode->mpPathInfo = tpPathInfo;

	p->mpNext = tpNewNode;
	tpNewNode->mpNext = s;


	return tpNewNode;

}
void CNodeList::SetLocation(SPathInfo *tpPathInfo)
{
	SPathInfo *tmp = NULL;

	tmp = FindPathInfoList(tpPathInfo);

	tmp->mX = tpPathInfo->mX;
	tmp->mY = tpPathInfo->mY;
}
void CNodeList::Reset()
{
	SNode *t = NULL;
	SNode *s = NULL;

	t = mpHead->mpNext;
	while (t != mpTail)
	{
		s = t;
		t = t->mpNext;

		//free(s);
		delete s;
	}
	mpHead->mpNext = mpTail;

}



bool CNodeList::DeletePathInfo(SPathInfo *tpPathInfo)
{
	SNode *s = NULL;
	SNode *p = NULL;

	p = mpHead;
	s = p->mpNext;

	while (s != mpTail && s->mpPathInfo != tpPathInfo)
	{
		p = p->mpNext;
		s = p->mpNext;
	}

	if (s != mpTail)
	{
		p->mpNext = s->mpNext;
		//free(s);
		delete s;

		return true;
	}
	else
		return false;
}
SPathInfo *CNodeList::Pop()
{
	SNode *t = NULL;
	SPathInfo *i = NULL;

	if (mpHead->mpNext == mpTail)
	{
		return NULL;
	}

	t = mpHead->mpNext;
	i = t->mpPathInfo;
	mpHead->mpNext = t->mpNext;

	delete t;

	return i;
}





void CNodeList::TestDisplayCount(string tString)
{
	mTestCount = 0;

	SNode *t = NULL;

	t = mpHead->mpNext;
	while (t != mpTail)
	{
		mTestCount++;

		t = t->mpNext;
	}
	mpHead->mpNext = mpTail;

	log("%s Count: %d", tString.c_str(), (int)mTestCount);
}

