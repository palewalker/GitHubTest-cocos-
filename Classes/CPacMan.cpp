
#include "CPacMan.h"
#include <math.h>
#include<cmath>

#define EPSILON 0.000001//Á¤È®µµ


bool DoFloatCompare(float tA, float tB)
{
	return fabs(tA - tB) < EPSILON;
}


CPacMan::CPacMan()
{

}

CPacMan::~CPacMan()
{

}

void CPacMan::Create()
{
	PacMan_UP = new AnimationBox();
	PacMan_DOWN = new AnimationBox();
	PacMan_LEFT = new AnimationBox();
	PacMan_RIGHT = new AnimationBox();

	PacMan_UP->Create("PacMan_UP", 3, 0.2f);
	PacMan_DOWN->Create("PacMan_DOWN", 3, 0.2f);
	PacMan_LEFT->Create("PacMan_LEFT", 3, 0.2f);
	PacMan_RIGHT->Create("PacMan_RIGHT", 3, 0.2f);

	
}

void CPacMan::SetScene(Node *tpNode)
{
	PacMan_UP->SetScene(tpNode);
	PacMan_DOWN->SetScene(tpNode);
	PacMan_LEFT->SetScene(tpNode);
	PacMan_RIGHT->SetScene(tpNode);
	
}
void CPacMan::Hide()
{
	PacMan_UP->Hide();
	PacMan_DOWN->Hide();
	PacMan_LEFT->Hide();
	PacMan_RIGHT->Hide();
}

void CPacMan::Show()
{
	switch (mState)
	{
		case UP:
		{
			PacMan_UP->Show();
			PacMan_DOWN->Hide();
			PacMan_LEFT->Hide();
			PacMan_RIGHT->Hide();
		}break;

		case DOWN:
		{
			PacMan_UP->Hide();
			PacMan_DOWN->Show();
			PacMan_LEFT->Hide();
			PacMan_RIGHT->Hide();
		}break;

		case LEFT:
		{
			PacMan_UP->Hide();
			PacMan_DOWN->Hide();
			PacMan_LEFT->Show();
			PacMan_RIGHT->Hide();
		}break;

		case RIGHT:
		{
			PacMan_UP->Hide();
			PacMan_DOWN->Hide();
			PacMan_LEFT->Hide();
			PacMan_RIGHT->Show();
		}break;

	}
	
}

void CPacMan::SetPosition(Vec2 tVec)
{
	mVec = tVec;


	PacMan_UP->SetPosition(tVec);
	PacMan_DOWN->SetPosition(tVec);
	PacMan_LEFT->SetPosition(tVec);
	PacMan_RIGHT->SetPosition(tVec);
	
}

Vec2 CPacMan::GetPosition()
{
	//return PacMan_UP->GetPosition();
	return mVec;
}

void CPacMan::Build()
{
	PacMan_UP->Build();
	PacMan_DOWN->Build();
	PacMan_LEFT->Build();
	PacMan_RIGHT->Build();
}
void CPacMan::UnBuild()
{
	PacMan_UP->UnBuild();
	PacMan_DOWN->UnBuild();
	PacMan_LEFT->UnBuild();
	PacMan_RIGHT->UnBuild();
}

void CPacMan::Destroy()
{
	PacMan_UP->Destroy();
	PacMan_DOWN->Destroy();
	PacMan_LEFT->Destroy();
	PacMan_RIGHT->Destroy();
}
void CPacMan::RunAni()
{
	PacMan_UP->RunAni();
	PacMan_DOWN->RunAni();
	PacMan_LEFT->RunAni();
	PacMan_RIGHT->RunAni();
}
void CPacMan::StopAni()
{
	PacMan_UP->StopAni();
	PacMan_DOWN->StopAni();
	PacMan_LEFT->StopAni();
	PacMan_RIGHT->StopAni();
}

void CPacMan::BeginMove()
{
	mIsMove = true;

	mCurTargetIndex = 0;
}

void CPacMan::UpdateMove(float dt)
{
	if (m_RoadVec.size() <= 0)
	{
		return;
	}

	if (true == mIsMove)
	{
		int tRow = m_RoadVec[mCurTargetIndex].y;
		int tCol = m_RoadVec[mCurTargetIndex].x;

		if (mVec.y < 480 - tRow * 16)
		{
			mVec.y += mSpeed *dt;

			mState = UP;
		}
		else if (mVec.y > 480 - tRow * 16)
		{
			mVec.y -= mSpeed *dt;

			mState = DOWN;
		}
		
		if (mVec.x < tCol * 16)
		{
			mVec.x += mSpeed *dt;

			mState = RIGHT;
		}
		else if (mVec.x > tCol * 16)
		{
			mVec.x -= mSpeed *dt;

			mState = LEFT;
		}

		SetPosition(mVec);


		if (mSpeed * dt >= fabs(mVec.x - tCol * 16))
		{
			mVec.x = tCol * 16;
		}

		if(mSpeed * dt >= fabs(mVec.y - (480 - tRow *  16)))
		{
			mVec.y = 480 - tRow * 16;
		}

		if (DoFloatCompare(mVec.x, tCol * 16) &&
			DoFloatCompare(mVec.y, 480 - tRow * 16))
		{
			mRow = tRow;
			mCol = tCol;

			mVec.x = mCol * 16;
			mVec.y = 480 - mRow * 16;

			SetPosition(mVec);

			if (mCurTargetIndex < m_RoadVec.size() - 1)
			{
				mCurTargetIndex++;
			}
			else
			{
				m_RoadVec.clear();

				mIsMove = false;

				mCurTargetIndex = 0;
			}
		}
	}
}

int CPacMan::GetCol()
{
	return mCol;
}
int CPacMan::GetRow()
{
	return mRow;
}

void CPacMan::StopMove()
{
	mIsMove = false;
	mCurTargetIndex = 0;
	m_RoadVec.clear();
}

