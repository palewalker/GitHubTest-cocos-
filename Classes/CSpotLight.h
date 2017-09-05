////  v1.1
////  CCSpotLight.h
////  exSpotLigt
////
////  Created by 이정우 on 13. 7. 15..
////
////
//
//#ifndef __exSpotLigt__CCSpotLight__
//#define __exSpotLigt__CCSpotLight__
//
//#include "cocos2d.h"
//USING_NS_CC;
//
//#define CAN_SHADOW_SPRITE 10000
//#define RT_ZORDER 1000
//#define get_length(a) (sizeof(a)/ sizeof(a[0]))
////현재 조명의 rect를 반지름의 값으로 만든다. 여기에 값을 주면 반지름 값으로 만드는 rect보다 작은 값을 만들 수 있다.
//#define rectOffset 0.0f
//
//struct CSpotLightDef
//{
//	CSpotLightDef() {
//		//        canShadowMake = false;
//		//        shadowColor = ccc4(0, 0, 0, 160);
//		//        shadowOffset = 0.0f;
//		radius = 0.0f;
//		spotlightColor = ccc4(0, 0, 0, 0);
//		position = ccp(0.0f, 0.0f);
//		followSprite = NULL;
//		z = 0;
//		tag = -1;
//	}
//
//	//    bool canShadowMake;
//	//    ccColor4B shadowColor;
//	//    float shadowOffset; //sprite의 4개의 정점 값의 -offset
//
//	float radius;
//	Color4B spotlightColor;
//	Vec2 position;
//	Sprite* followSprite;
//	int z;
//	int tag;
//};
//
//class CSpotLight : public Sprite {
//public:
//
//	static CSpotLight* createWithRenderTexture(RenderTexture* rt, float radius, ccColor4B spotlightColor);
//
//	virtual bool init(RenderTexture* rt, float radius, Color4B spotlightColor);
//
//
//	//제거하는데, 그냥 사라지는 게 아니라 점점 원이 커지면서 사라진다.
//	void spreadOutAndRemove(float pTime, float pSpreadOutRadius);
//
//	//점점 원이 커진다. 하지만 사라지지 않는다.
//	void spread(float pTime, float pSpreadOutRadius, bool isOut);
//
//
//private:
//	//보여지는 화면 크기
//	Rect disRect;
//
//	CSpotLight();
//	~CSpotLight();
//
//
//	void update(float dt);
//
//
//	
//	void updateSpreadOutAndRemove(float dt);
//
//
//
//	void updateSpreadOutTimer(float dt);
//
//
//	CC_SYNTHESIZE(RenderTexture*, m_renderTexture, RenderTexture);
//	CC_SYNTHESIZE(float, m_spotLightRadius, SpotLightRadius);
//
//	CC_SYNTHESIZE(Color4B, spotlightColor, SpotlightColor);
//	CC_SYNTHESIZE(Color4B, shadowColor, ShadowColor);
//	//    CC_SYNTHESIZE(float, shadowOffset, ShadowOffset);
//	//    CC_SYNTHESIZE(bool, canShadowMake, CanShadowMake);
//	CC_SYNTHESIZE(Sprite*, followSprite, FollowSprite);
//	CC_SYNTHESIZE(Rect, rect, Rect);
//
//
//	// Spread Function
//	CC_SYNTHESIZE(float, m_spreadTime, Spreadtime); // 확대 지속 시간
//	CC_SYNTHESIZE(float, m_spreadOutRadius, m_spreadOutRadius); // 반지름
//	CC_SYNTHESIZE(bool, m_isRunningSpreadAnimation, IsRunningSpreadAnimation); // Spreadout이 진행하고 있는가? 아닌가?
//	CC_SYNTHESIZE(bool, m_isSpreadOut, IsSpreadOut);
//
//};
//
//#endif /* defined(__exSpotLigt__CCSpotLight__) */

//  v1.1
//  CCSpotLight.h
//  exSpotLigt
//
//  Created by 이정우 on 13. 7. 15..
//
//

#ifndef __exSpotLigt__CCSpotLight__
#define __exSpotLigt__CCSpotLight__

#include "cocos2d.h"
USING_NS_CC;

#define CAN_SHADOW_SPRITE 10000
#define RT_ZORDER 1000
#define get_length(a) (sizeof(a)/ sizeof(a[0]))
//현재 조명의 rect를 반지름의 값으로 만든다. 여기에 값을 주면 반지름 값으로 만드는 rect보다 작은 값을 만들 수 있다.
#define rectOffset 0.0f

struct CCSpotLightDef
{
	CCSpotLightDef() {
		//        canShadowMake = false;
		//        shadowColor = ccc4(0, 0, 0, 160);
		//        shadowOffset = 0.0f;
		radius = 0.0f;
		spotlightColor = ccc4(0, 0, 0, 0);
		position = ccp(0.0f, 0.0f);
		followSprite = NULL;
		z = 0;
		tag = -1;
	}

	//    bool canShadowMake;
	//    ccColor4B shadowColor;
	//    float shadowOffset; //sprite의 4개의 정점 값의 -offset

	float radius;
	ccColor4B spotlightColor;
	CCPoint position;
	CCSprite* followSprite;
	int z;
	int tag;
};

class CCSpotLight : public CCSprite {
public:

	static CCSpotLight* createWithRenderTexture(CCRenderTexture* rt, float radius, ccColor4B spotlightColor);

	virtual bool init(CCRenderTexture* rt, float radius, ccColor4B spotlightColor);


	//제거하는데, 그냥 사라지는 게 아니라 점점 원이 커지면서 사라진다.
	void spreadOutAndRemove(float pTime, float pSpreadOutRadius);

	//점점 원이 커진다. 하지만 사라지지 않는다.
	void spread(float pTime, float pSpreadOutRadius, bool isOut);


private:
	//보여지는 화면 크기
	CCRect disRect;

	CCSpotLight();
	~CCSpotLight();

	//매 프레임 마다 렌더러를 호출해서 새로 그리기 위한 스케줄러 함수.
	void update(float dt);


	//끝날때 보이는 영역이 넓어진다. 시간이 지나면 사라진다.
	void updateSpreadOutAndRemove(float dt);


	//끝날때 보이는 영역이 넓어진다. 시간이 지나면 가만히 존재한다.
	void updateSpreadOutTimer(float dt);

	//protected 변수 선언과 동시에 getter,setter 설정
	CC_SYNTHESIZE(CCRenderTexture*, m_renderTexture, RenderTexture);
	CC_SYNTHESIZE(float, m_spotLightRadius, SpotLightRadius);

	CC_SYNTHESIZE(ccColor4B, spotlightColor, SpotlightColor);
	CC_SYNTHESIZE(ccColor4B, shadowColor, ShadowColor);
	//    CC_SYNTHESIZE(float, shadowOffset, ShadowOffset);
	//    CC_SYNTHESIZE(bool, canShadowMake, CanShadowMake);
	CC_SYNTHESIZE(CCSprite*, followSprite, FollowSprite);
	CC_SYNTHESIZE(CCRect, rect, Rect);


	// Spread Function
	CC_SYNTHESIZE(float, m_spreadTime, Spreadtime); // 확대 지속 시간
	CC_SYNTHESIZE(float, m_spreadOutRadius, m_spreadOutRadius); // 반지름
	CC_SYNTHESIZE(bool, m_isRunningSpreadAnimation, IsRunningSpreadAnimation); // Spreadout이 진행하고 있는가? 아닌가?
	CC_SYNTHESIZE(bool, m_isSpreadOut, IsSpreadOut);

};

#endif /* defined(__exSpotLigt__CCSpotLight__) */

