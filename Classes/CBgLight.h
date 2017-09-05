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
//  Created by ������ on 13. 7. 19..
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

	//ĳ���Ͱ� ȭ�� ������ �̵��ϰ� �ǰų� �ؼ� ȭ���� ���󰣴ٸ� �� �Լ��� �̵��ؾ� ����� ���󰣴�.
	//�����ٷ����� ȣ���ϸ� �ȴ�. ȭ�� �ȿ��� �̵��Ѵٸ� setPosition�ϸ� �ȴ�.
	void setRtPosition(CCPoint rtP);
	CCSpotLight* createSpotLight(struct CCSpotLightDef* def);

private:

	CCRect disRect;
	CCBgLight();
	~CCBgLight();

	void update(float dt);

	//protected ���� ����� ���ÿ� getter,setter ����
	CC_SYNTHESIZE(CCRenderTexture*, m_renderTexture, RenderTexture);
	CC_SYNTHESIZE(ccColor4B, bgColor, bgColor);
};


#endif /* defined(__exSpotLigt__CCBgLight__) */
