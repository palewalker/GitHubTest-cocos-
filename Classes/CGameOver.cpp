
#include "CGameOver.h"


CGameOver::CGameOver()
{

}

CGameOver::~CGameOver()
{

}


void CGameOver::Create(Node* tpNode)
{
	winSize = Director::getInstance()->getWinSize();

	mBackLayer = LayerColor::create(Color4B(255, 255, 255, 100), winSize.width, winSize.height);
	mBackLayer->setAnchorPoint(Vec2(0, 0));
	tpNode->addChild(mBackLayer, 1000);
	//mBackLayer->setVisible(true);
	

	
	mGameOverSpr = Sprite::create("GameOver.png");
	mGameOverSpr->setPosition(Vec2((winSize.width - mGameOverSpr->getContentSize().width) / 2,
		(winSize.height - mGameOverSpr->getContentSize().height) / 2 ));
	mGameOverSpr->setAnchorPoint(Vec2(0, 0));
	mBackLayer->addChild(mGameOverSpr);
	

	this->Hide();
}

void CGameOver::SetVisible(bool isPlayerState)
{
	if (true == isPlayerState)
	{
		if (true == mBackLayer->isVisible())
		{
			mBackLayer->setVisible(false);
		}
	}
	else
	{
		//ryu
		if (false == mBackLayer->isVisible())

		{
			mBackLayer->setVisible(true);
			
		}
	}
	
}

Sprite* CGameOver::GetSprite()
{
	return mGameOverSpr;
}

int CGameOver::GetState()
{
	return mState;
}

void CGameOver::Show()
{
	mBackLayer->setVisible(true);
}
void CGameOver::Hide()
{
	mBackLayer->setVisible(false);
}

bool CGameOver::IsShow()
{
	return mBackLayer->isVisible();
}