
#include "CPlayer.h"
#include "CUnit.h"
#include "CPlayerBullet.h"




CPlayer::CPlayer()
{

}

CPlayer::~CPlayer()
{

}

void CPlayer::Create(CMap *tpMap)
{
	mpSprite = Sprite::create("Guy2.png");
	mpSprite->setPosition(tpMap->HeroSpawn());
	mVec = mpSprite->getPosition();
	mpSprite->setAnchorPoint(Vec2(0.5, 0));
	mpNode->addChild(mpSprite);

	for (int i = 0; i < 30; i++)
	{
		
		tPlayerBullet[i]->Create(this);
	}
	
	mpTestLabel = Label::createWithTTF("Test", "fonts/Marker Felt.ttf", 20);
	mpTestLabel->setPosition(Vec2(380, 50));
	mpNode->addChild(mpTestLabel);//pale

}

void CPlayer::SetScene(Node *tpNode)
{
	mpNode = tpNode;

	for (int i = 0; i < 30; i++)
	{
		tPlayerBullet[i] = new CPlayerBullet();
		tPlayerBullet[i]->SetScene(tpNode);
	}

	
	
}
void CPlayer::Hide()
{
	mpSprite->setVisible(false);
}

void CPlayer::Show()
{
	mpSprite->setVisible(true);
}

void CPlayer::SetPosition(Vec2 tVec)
{
	mpSprite->setPosition(tVec);
	
}

Vec2 CPlayer::GetPosition()
{
	return mpSprite->getPosition();
}




//void CPlayer::KeyPressed(EventKeyboard::KeyCode keyCode,
//	Event *event)
//{
//	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
//	{
//		mKeyPressed = true;
//
//		mDirX = DIR_LEFT;
//		mSpeedPower = 2.0f;
//
//		mpSprite->setFlippedX(true);
//
//		
//
//		mKeyInputCheckVec.push_back(1);
//	}
//	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
//	{
//		mKeyPressed = true;
//		
//		mDirX = DIR_RIGHT;
//		mSpeedPower = 2.0f;
//
//		mpSprite->setFlippedX(false);
//
//		mKeyInputCheckVec.push_back(1);
//	}
//	if (keyCode == EventKeyboard::KeyCode::KEY_Z)
//	{
//		mKeyPressed = true;
//		JumpStart();
//
//		mKeyInputCheckVec.push_back(1);
//	}
//	if (keyCode == EventKeyboard::KeyCode::KEY_X)
//	{
//		mKeyPressed = true;
//		if (mState == ALIVE)
//		{
//			if (mDirX == 0)
//			{
//				tPlayerBullet[mBulletIndex]->DirSet(1);
//				tPlayerBullet[mBulletIndex]->FireSetPosition(this);
//			}
//			else
//			{
//				tPlayerBullet[mBulletIndex]->DirSet(mDirX);
//				tPlayerBullet[mBulletIndex]->FireSetPosition(this);
//			}
//			mBulletIndex++;
//			if (mBulletIndex == 20)
//			{
//				mBulletIndex = 0;
//			}
//		}
//		
//		mKeyInputCheckVec.push_back(1);
//
//		
//	}
//	if (keyCode == EventKeyboard::KeyCode::KEY_R)
//	{
//		LoadPos();
//	}
//	
//	
//
//}
//
//void CPlayer::KeyReleased(EventKeyboard::KeyCode keyCode,
//	Event *event)
//{
//	if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
//	{
//		mSpeedPower = 0.0f;
//
//		mKeyInputCheckVec.pop_back();
//	}
//	if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
//	{
//		mSpeedPower = 0.0f;
//		
//		mKeyInputCheckVec.pop_back();
//	}
//	if (keyCode == EventKeyboard::KeyCode::KEY_Z)
//	{
//		
//		mKeyInputCheckVec.pop_back();
//	}
//
//	if (keyCode == EventKeyboard::KeyCode::KEY_X)
//	{
//		mKeyInputCheckVec.pop_back();
//	}
//
//	if (mKeyInputCheckVec.size() <= 0)
//	{
//		mKeyPressed = false;
//	}
//	//mKeyPressed = false;
//}


void CPlayer::Move(CMap *tpMap,float Dir)
{
	if (mState == ALIVE)
	{
		JoyStick *joypad;

		float tX = mpSprite->getPositionX() + Dir * mSpeedPower;
		mVec.x = tX;

		mDirX = Dir;

		if (Dir >0)
		{
			mpSprite->setFlippedX(false);
			mDirState = RIGHT;
			
		}
		else if(Dir<0)
		{
			mpSprite->setFlippedX(true);
			mDirState = LEFT;
		}


		TMXTiledMap *tMap = tpMap->GetTMX();

		float tTileW = tMap->getTileSize().width;
		float tTileH = tMap->getTileSize().height;

		float tTotalRowCount = tMap->getMapSize().height;

		int tCol = mVec.x / tTileW;
		int tRow = tTotalRowCount - (mVec.y + 16) / tTileH;

		Vec2 tVec = Vec2(tCol, tRow);

		int tAttribute = tpMap->CheckAttribute(tVec);

		if (1 == tAttribute || (mVec.x < 5 || mVec.x >795))
		{
			mVec.x = mpSprite->getPositionX();
		}
		else if (2 == tAttribute)
		{
			mState = DEAD;//pale
		}

		mpSprite->setPositionX(mVec.x);
		


	}


}
//
//void CPlayer::MoveByKeyboard(CMap *tpMap)
//{
//	
//	if (true == mKeyPressed)
//	{
//
//		if (mState == ALIVE)
//		{
//			float tX = mpSprite->getPositionX() + mDirX * mSpeedPower;
//			mVec.x = tX;
//
//
//
//
//			TMXTiledMap *tMap = tpMap->GetTMX();
//
//			float tTileW = tMap->getTileSize().width;
//			float tTileH = tMap->getTileSize().height;
//
//			float tTotalRowCount = tMap->getMapSize().height;
//
//			int tCol = mVec.x / tTileW;
//			int tRow = tTotalRowCount - (mVec.y + 16) / tTileH;
//
//			Vec2 tVec = Vec2(tCol, tRow);
//
//			int tAttribute = tpMap->CheckAttribute(tVec);
//
//			if (1 == tAttribute || (mVec.x < 5 || mVec.x >795))
//			{
//				mVec.x = mpSprite->getPositionX();
//			}
//			else if (2 == tAttribute)
//			{
//				mState = DEAD;
//			}
//
//			mpSprite->setPositionX(mVec.x);
//
//
//		}
//		
//	}
//
//	
//	
//}


void CPlayer::Collision(CMap *tpMap)
{
	if (mState == ALIVE)
	{
		mIsCollision = false;

		TMXTiledMap* tMap = tpMap->GetTMX();

		float tTileW = tMap->getTileSize().width;
		float tTileH = tMap->getTileSize().height;

		float tTotalRowCount = tMap->getMapSize().height;

		int tCol = mVec.x / tTileW;
		int tRow = tTotalRowCount - mVec.y / tTileH;

		Vec2 tVec = Vec2(tCol, tRow);

		int tAttribute = tpMap->CheckAttribute(tVec);

		if (mJumpState != JUMPSTATE_UP)
		{
			if (1 == tAttribute)
			{
				float tMapHeight = (tTotalRowCount - tRow) * tTileH;
				mpSprite->setPositionY(tMapHeight);

				mVec.y = mpSprite->getPositionY();

				mJumpState = JUMPSTATE_DEF;

				mIsCollision = true;
			}

			else if (2 == tAttribute)
			{
				mState = DEAD;//pale


			}
		}
		//pale
		else if (mJumpState == JUMPSTATE_UP)
		{
			if (1 == tAttribute)
			{
				float tMapHeight = (tTotalRowCount - tRow -1) * tTileH;
				mpSprite->setPositionY(tMapHeight);

				mVec.y = mpSprite->getPositionY();

				mJumpState = JUMPSTATE_DOWN;

				mIsCollision = true;
			}
			else if (mpSprite->getPositionY() > 470)
			{
				mpSprite->setPositionY(469);
			}
			else if (2 == tAttribute)
			{
				mState = DEAD;//pale


			}

		}

		if (2 == tAttribute)
		{
			mState = DEAD;//pale


		}

		if (false == mIsCollision)
		{
			if (mJumpState != JUMPSTATE_UP)
			{
				mJumpState = JUMPSTATE_DOWN;
			}
		}
	}
}

//ryu
void CPlayer::JumpStart()
{
	if (mState == ALIVE)
	{
		float tPower = 7.0f;

		if (1 >= mJumpCount)
		{
			if (tPower > 0)
			{
				mJumpPower = tPower;
				mJumpState = JUMPSTATE_UP;
				mJumpCount += 1;
			}
			else if (tPower <= 0)
			{
				mJumpPower = tPower;
				mJumpState = JUMPSTATE_DOWN;

			}
		}
	}
	
}

void CPlayer::Jump(CMap *tpMap)
{
	if (mState == ALIVE)
	{
		float tGravity = 0.7f;

		if (mJumpPower < 0)
		{
			mJumpState = JUMPSTATE_DOWN;
		}

		if (mJumpState == JUMPSTATE_UP)
		{

			mJumpPower -= tGravity;
			mpSprite->setPositionY(mpSprite->getPositionY() + mJumpPower);
			mVec.y = mpSprite->getPositionY();

		}

		else if (mJumpState == JUMPSTATE_DOWN)
		{
			if (mJumpPower < 10)
			{
				mJumpPower += tGravity;
			}


			if (mpSprite->getPositionY() > mJumpPower)
			{
				mpSprite->setPositionY(mpSprite->getPosition().y - mJumpPower);
			}
			else
			{
				mpSprite->setPositionY(mpSprite->getPosition().y);
				mState = DEAD;

			}

			mVec.y = mpSprite->getPositionY();
		}

		else if (mJumpState == JUMPSTATE_DEF)
		{
			mJumpPower = 0;
			mJumpCount = 0;

		}
	}
	else
	{
		mJumpState = JUMPSTATE_DEF;
	}
}

void CPlayer::ObjectCollision(CMap *tpMap)
{
	int JumpNum = tpMap->GetJumpPointNum();
	
	//more jump collision
	for (int i = 0; i < JumpNum; i++)
	{
		
		Sprite* tJumpSp = tpMap->GetJumpPtr(i)->GetSprite();
		Vec2 tVec = tJumpSp->getPosition();
		float tJumpR = tJumpSp->getContentSize().width * 0.5f;

		Rect tPlayerRect = mpSprite->getBoundingBox();
		bool tf = tPlayerRect.intersectsCircle(tVec, tJumpR);
		if (true == tf)
		{
			if (ALIVE == tpMap->GetJumpPtr(i)->GetState())
			{
				mJumpCount = mJumpCount - 1;
				tpMap->GetJumpPtr(i)->SetUsed();
			}
				
		}
	}

	//platform collision

	int PlatformNum = tpMap->GetPlatformNum();

	for (int i = 0; i < PlatformNum; i++)
	{
		bool tResult = false;

		Vec2 PlatformVec = tpMap->GetPlatformPtr(i)->GetPosition();
		Vec2 PlayerVec = mpSprite->getPosition();

		Sprite* tPlatformSp = tpMap->GetPlatformPtr(i)->GetSprite();
		float tPlayerWidthH = mpSprite->getContentSize().width*0.5f;
		float tPlayerHeightH = mpSprite->getContentSize().height*0.5f;

		float tPlatformWidthH = tPlatformSp->getContentSize().width*0.5f;
		float tPlatformHeightH = tPlatformSp->getContentSize().height*0.5f;

		if (PlayerVec.x + tPlayerWidthH >= PlatformVec.x - tPlatformWidthH && PlayerVec.x - tPlayerWidthH <=
			PlatformVec.x + tPlatformWidthH)
		{
			if (PlayerVec.y + tPlayerHeightH >= PlatformVec.y - tPlatformHeightH && PlayerVec.y - tPlayerHeightH <=
				PlatformVec.y + tPlatformHeightH)
			{
				tResult = true;
			}
		}

		if (mJumpState != JUMPSTATE_UP)
		{
			if (true == tResult)
			{
				
				mpSprite->setPositionY(tpMap->GetPlatformPtr(i)->GetPosition().y);

				mVec.y = mpSprite->getPositionY();

				mJumpState = JUMPSTATE_DEF;

				mIsCollision = true;

				tpMap->GetPlatformPtr(i)->FallAndReset(mpNode);

			}
		}
		
	}

	//savepoint vs bullet collision
	int SavePointNum = tpMap->GetSavePointNum();

	for (int k = 0; k < SavePointNum; k++)
	{
		for (int i = 0; i < 30; i++)
		{
			bool IsCollision= tPlayerBullet[i]->CollisionWithSavePoint(tpMap->GetSavePtr(k));
			if (IsCollision == true)
			{
				SavePos();
			}
		}
	}

	//NextStageLocCheck
}

void CPlayer::StateCheck()
{
	if (mState == ALIVE)
	{
		mpSprite->setVisible(true);
	}
	else if (mState == DEAD)
	{
		
		mpSprite->setVisible(false);
	}
}

void CPlayer::FireMove()
{
	for (int i = 0; i < 30; i++)
	{
		tPlayerBullet[i]->FireMove();
	}
}

void CPlayer::SavePos()
{
	UserDefault::getInstance()->setFloatForKey("key_x",
		mpSprite->getPositionX());
	UserDefault::getInstance()->setFloatForKey("key_y",
		mpSprite->getPositionY());
	UserDefault::getInstance()->setIntegerForKey("key_jumpstate",
		mJumpState);
	UserDefault::getInstance()->setFloatForKey("key_jumppower",
		mJumpPower);

	UserDefault::getInstance()->flush();

	float tX = UserDefault::getInstance()->getFloatForKey("key_x");
	float tY = UserDefault::getInstance()->getFloatForKey("key_y");
	int State = UserDefault::getInstance()->getIntegerForKey("key_jumpstate");
	float Power = UserDefault::getInstance()->getFloatForKey("key_jumppower");

	char tStr[512];
	memset(tStr, 0, 512);
	sprintf(tStr, "x: %f, y:%f, state: %i, power:%f", tX, tY, State, Power);
	mpTestLabel->setString(tStr);//pale

	IsSave = true;
	
}



void CPlayer::LoadPos()
{
	if (mState == DEAD)
	{

		mState = ALIVE;
	}
	

	mVec.x = UserDefault::getInstance()->getFloatForKey("key_x");
	mVec.y = UserDefault::getInstance()->getFloatForKey("key_y");
	mJumpState = UserDefault::getInstance()->getIntegerForKey("key_jumpstate");
	mJumpPower = UserDefault::getInstance()->getFloatForKey("key_jumppower");

	//ryu
	mpSprite->setPosition(mVec);

}


int CPlayer::GetState()
{
	return mState;
}

void CPlayer::FireStart(float Dir)
{
	if (mState == ALIVE)
	{
		
		if (mDirState ==RIGHT)
		{
			tPlayerBullet[mBulletIndex]->DirSet(1);
			tPlayerBullet[mBulletIndex]->FireSetPosition(this);
		}
		else if(mDirState== LEFT)
		{
			tPlayerBullet[mBulletIndex]->DirSet(-1);
			tPlayerBullet[mBulletIndex]->FireSetPosition(this);
		}
		mBulletIndex++;
		if (mBulletIndex == 20)
		{
			mBulletIndex = 0;
		}
	}
}

Sprite* CPlayer::GetSprite()
{
	return mpSprite;
}

void CPlayer::SaveInit()
{
	UserDefault::getInstance()->setFloatForKey("key_x",
		mpSprite->getPositionX());
	UserDefault::getInstance()->setFloatForKey("key_y",
		mpSprite->getPositionY());
	UserDefault::getInstance()->setIntegerForKey("key_jumpstate",
		mJumpState);
	UserDefault::getInstance()->setFloatForKey("key_jumppower",
		mJumpPower);

	UserDefault::getInstance()->flush();
}

