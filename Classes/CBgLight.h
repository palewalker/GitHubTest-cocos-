//#pragma once
//#include "CSpotLight.h"
//
//using namespace cocos2d;
//
//
//class CBgLight : public Sprite
//{
//public:
//
//	static CBgLight* createWithRenderTexture(Node* Parent, Color4B bgColor);
//
//	virtual bool init(Node* parent, Color4B bgColor);
//
//	CSpotLight* createSpotLight(struct CSpotLightDef* def);
//
//private:
//
//	Rect disRect;
//	CBgLight();
//	~CBgLight();
//
//	void update(float dt);
//
//	CC_SYNTHESIZE(RenderTexture*, m_renderTexture, RenderTexture);
//	CC_SYNTHESIZE(Color4B, bgColor, bgColor);
//
//};

//  v1.1
//  CCBgLight.h
//  exSpotLigt
//
//  Created by 이정우 on 13. 7. 19..
//
//

#ifndef __exSpotLigt__CCBgLight__
#define __exSpotLigt__CCBgLight__

#include "cocos2d.h"
#include "CSpotLight.h"

using namespace cocos2d;

class CCBgLight : public CCSprite
{
public:

	static CCBgLight* createWithRenderTexture(CCNode* parent, ccColor4B bgColor);

	virtual bool init(CCNode* parent, ccColor4B bgColor);

	//캐릭터가 화면 밖으로 이동하게 되거나 해서 화면이 따라간다면 이 함수로 이동해야 제대로 따라간다.
	//스케줄러에서 호출하면 된다. 화면 안에서 이동한다면 setPosition하면 된다.
	void setRtPosition(CCPoint rtP);
	CCSpotLight* createSpotLight(struct CCSpotLightDef* def);

private:

	CCRect disRect;
	CCBgLight();
	~CCBgLight();

	void update(float dt);

	//protected 변수 선언과 동시에 getter,setter 설정
	CC_SYNTHESIZE(CCRenderTexture*, m_renderTexture, RenderTexture);
	CC_SYNTHESIZE(ccColor4B, bgColor, bgColor);
};


#endif /* defined(__exSpotLigt__CCBgLight__) */
