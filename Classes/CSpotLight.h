////  v1.1
////  CCSpotLight.h
////  exSpotLigt
////
////  Created by ������ on 13. 7. 15..
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
////���� ������ rect�� �������� ������ �����. ���⿡ ���� �ָ� ������ ������ ����� rect���� ���� ���� ���� �� �ִ�.
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
//	//    float shadowOffset; //sprite�� 4���� ���� ���� -offset
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
//	//�����ϴµ�, �׳� ������� �� �ƴ϶� ���� ���� Ŀ���鼭 �������.
//	void spreadOutAndRemove(float pTime, float pSpreadOutRadius);
//
//	//���� ���� Ŀ����. ������ ������� �ʴ´�.
//	void spread(float pTime, float pSpreadOutRadius, bool isOut);
//
//
//private:
//	//�������� ȭ�� ũ��
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
//	CC_SYNTHESIZE(float, m_spreadTime, Spreadtime); // Ȯ�� ���� �ð�
//	CC_SYNTHESIZE(float, m_spreadOutRadius, m_spreadOutRadius); // ������
//	CC_SYNTHESIZE(bool, m_isRunningSpreadAnimation, IsRunningSpreadAnimation); // Spreadout�� �����ϰ� �ִ°�? �ƴѰ�?
//	CC_SYNTHESIZE(bool, m_isSpreadOut, IsSpreadOut);
//
//};
//
//#endif /* defined(__exSpotLigt__CCSpotLight__) */

//  v1.1
//  CCSpotLight.h
//  exSpotLigt
//
//  Created by ������ on 13. 7. 15..
//
//

#ifndef __exSpotLigt__CCSpotLight__
#define __exSpotLigt__CCSpotLight__

#include "cocos2d.h"
USING_NS_CC;

#define CAN_SHADOW_SPRITE 10000
#define RT_ZORDER 1000
#define get_length(a) (sizeof(a)/ sizeof(a[0]))
//���� ������ rect�� �������� ������ �����. ���⿡ ���� �ָ� ������ ������ ����� rect���� ���� ���� ���� �� �ִ�.
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
	//    float shadowOffset; //sprite�� 4���� ���� ���� -offset

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


	//�����ϴµ�, �׳� ������� �� �ƴ϶� ���� ���� Ŀ���鼭 �������.
	void spreadOutAndRemove(float pTime, float pSpreadOutRadius);

	//���� ���� Ŀ����. ������ ������� �ʴ´�.
	void spread(float pTime, float pSpreadOutRadius, bool isOut);


private:
	//�������� ȭ�� ũ��
	CCRect disRect;

	CCSpotLight();
	~CCSpotLight();

	//�� ������ ���� �������� ȣ���ؼ� ���� �׸��� ���� �����ٷ� �Լ�.
	void update(float dt);


	//������ ���̴� ������ �о�����. �ð��� ������ �������.
	void updateSpreadOutAndRemove(float dt);


	//������ ���̴� ������ �о�����. �ð��� ������ ������ �����Ѵ�.
	void updateSpreadOutTimer(float dt);

	//protected ���� ����� ���ÿ� getter,setter ����
	CC_SYNTHESIZE(CCRenderTexture*, m_renderTexture, RenderTexture);
	CC_SYNTHESIZE(float, m_spotLightRadius, SpotLightRadius);

	CC_SYNTHESIZE(ccColor4B, spotlightColor, SpotlightColor);
	CC_SYNTHESIZE(ccColor4B, shadowColor, ShadowColor);
	//    CC_SYNTHESIZE(float, shadowOffset, ShadowOffset);
	//    CC_SYNTHESIZE(bool, canShadowMake, CanShadowMake);
	CC_SYNTHESIZE(CCSprite*, followSprite, FollowSprite);
	CC_SYNTHESIZE(CCRect, rect, Rect);


	// Spread Function
	CC_SYNTHESIZE(float, m_spreadTime, Spreadtime); // Ȯ�� ���� �ð�
	CC_SYNTHESIZE(float, m_spreadOutRadius, m_spreadOutRadius); // ������
	CC_SYNTHESIZE(bool, m_isRunningSpreadAnimation, IsRunningSpreadAnimation); // Spreadout�� �����ϰ� �ִ°�? �ƴѰ�?
	CC_SYNTHESIZE(bool, m_isSpreadOut, IsSpreadOut);

};

#endif /* defined(__exSpotLigt__CCSpotLight__) */

