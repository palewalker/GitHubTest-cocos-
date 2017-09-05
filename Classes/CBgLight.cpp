//#include "CBgLight.h"
//
//
//CBgLight* CBgLight::createWithRenderTexture(Node* parent, Color4B bgColor)
//{
//	CBgLight *pRet = new CBgLight();
//	if (pRet && pRet->init(parent, bgColor))
//	{
//		pRet->autorelease();
//		return pRet;
//	}
//	else
//	{
//		CC_SAFE_DELETE(pRet);
//		return NULL;
//	}
//}
//
//CBgLight::CBgLight()
//{
//
//}
//
//CBgLight::~CBgLight()
//{
//	m_renderTexture->removeFromParentAndCleanup(true);
//	m_renderTexture = NULL;
//	CCLOG("CBgLight destroy");
//}
//
//bool CBgLight::init(Node* parent, Color4B bgColor)
//{
//	if (!Sprite::init())
//	{
//		return false;
//	}
//
//	Size visiableSize = Director::getInstance()->getVisibleSize();
//	Vec2 Origin = Director::getInstance()->getVisibleOrigin();
//	disRect = Rect(Origin.x, Origin.y, visiableSize.width + Origin.x, visiableSize.height + Origin.y);
//		
//	m_renderTexture = RenderTexture::create(disRect.size.width, disRect.size.height);
//	m_renderTexture->setPosition(disRect.size.width, disRect.size.height);
//	m_renderTexture->getSprite()->setBlendFunc(ccBlendFunc{ GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA });
//	parent->addChild(m_renderTexture, RT_ZORDER);
//
//	this->setPosition(Vec2(disRect.size.width / 2, disRect.size.height / 2));
//	this->bgColor = bgColor;
//	this->scheduleUpdate();
//
//	return true;
//
//}
//
//CSpotLight* CBgLight::createSpotLight(struct CSpotLightDef* def)
//{
//	CSpotLight* spotlight = CSpotLight::createWithRenderTexture(m_renderTexture, def->radius, def->spotlightColor);
//	spotlight->setPosition(def->position);
//
//	if (def->tag == -1)
//	{
//		this->addChild(spotlight, def->z);
//	}
//	else
//	{
//		this->addChild(spotlight, def->z, def->tag);
//	}
//
//	if (def->followSprite != NULL)
//	{
//		spotlight->setFollowSprite(def->followSprite);
//
//	}
//
//	return spotlight;
//}
//
//void CBgLight::update(float dt)
//{
//	GLfloat vertices_rect[] = {
//		disRect.size.width, disRect.size.height,  //v0
//		disRect.origin.x, disRect.size.height,  //v1
//		disRect.origin.x, disRect.origin.y,  //v2
//		disRect.size.width, 0.0f  //v3
//	};
//
//	Color4B* colors_rect = new Color4B[4];
//	for (int i = 0; i < 4; i++)
//	{
//		colors_rect[i] = Color4B(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
//
//	}
//
//	GLubyte indices_rect[] = { 0,1,3,2 };
//
//	m_renderTexture->clear(0, 0, 0, 255);
//	m_renderTexture->begin();
//
//	setShaderProgram(ShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
//	CC_NODE_DRAW_SETUP();
//
//	ccGLEnableVertexAttribs(kCCVertexAttrib_Position | kCCVertexAttribFlag_Color);
//
//	glBlendFunc(GL_ONE, GL_ZERO);
//
//	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices_rect);
//	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, colors_rect);
//	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, indices_rect);
//
//	glColorMask(1.0f, 1.0f, 1.0f, 1.0f);
//	glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
//
//	m_renderTexture->end();
//	delete[] colors_rect;
//
//}

//
//  CCBgLight.cpp
//  exSpotLigt
//
//  Created by 이정우 on 13. 7. 19..
//
//

#include "CBgLight.h"
#define THIS CCBgLight



USING_NS_CC;

CCBgLight* CCBgLight::createWithRenderTexture(CCNode* parent, ccColor4B bgColor)
{
	CCBgLight *pRet = new CCBgLight();
	if (pRet && pRet->init(parent, bgColor))
	{
		pRet->autorelease();
		return pRet;
	}
	else
	{
		CC_SAFE_DELETE(pRet);
		return NULL;
	}
}

THIS::THIS()
{
	//    spotList = new CCArray();
	//    spotList->retain();
}


THIS::~THIS()
{
	//    spotList->removeAllObjects();
	//    CC_SAFE_RELEASE(spotList);
	//    spotList = NULL;
	m_renderTexture->removeFromParentAndCleanup(true);
	m_renderTexture = NULL;
	//CCLog("CCBgLight destory");
}



bool THIS::init(CCNode* parent, ccColor4B bgColor)
{
	if (!CCSprite::init())
	{
		return false;
	}

	CCSize visiableSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	disRect = CCRectMake(origin.x, origin.y, visiableSize.width + origin.x, visiableSize.height + origin.y);

	m_renderTexture = CCRenderTexture::create(disRect.size.width, disRect.size.height);
	m_renderTexture->setPosition(disRect.size.width / 2, disRect.size.height / 2);
	m_renderTexture->getSprite()->setBlendFunc(ccBlendFunc{ GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA });
	parent->addChild(m_renderTexture, RT_ZORDER);

	this->setPosition(CCPoint(disRect.size.width / 2, disRect.size.height / 2));
	this->bgColor = bgColor;
	this->scheduleUpdate();

	return true;
}


/**=====================================================================////

public

/======================================================================///*/
void THIS::setRtPosition(CCPoint rtP) {
	m_renderTexture->setPosition(rtP);
}

CCSpotLight* THIS::createSpotLight(struct CCSpotLightDef* def)
{
	CCSpotLight* spotlight = CCSpotLight::createWithRenderTexture(m_renderTexture, def->radius, def->spotlightColor);
	spotlight->setPosition(def->position);

	if (def->tag == -1) {
		this->addChild(spotlight, def->z);
	}
	else {
		this->addChild(spotlight, def->z, def->tag);
	}

	//    spotlight->setCanShadowMake(def->canShadowMake);
	//    spotlight->setShadowColor(def->shadowColor);
	//    spotlight->setShadowOffset(def->shadowOffset);
	if (def->followSprite != NULL) spotlight->setFollowSprite(def->followSprite);

	return spotlight;
}

/**=====================================================================////

private

/======================================================================///*/

void THIS::update(float dt) {
	// 반투명한 화면을 위해. 네모 상자
	GLfloat vertices_rect[] = {
		disRect.size.width, disRect.size.height,  //v0
		disRect.origin.x, disRect.size.height,  //v1
		disRect.origin.x, disRect.origin.y,  //v2
		disRect.size.width, 0.0f  //v3
	};

	//네모 상자의 색깔.
	ccColor4B* colors_rect = new ccColor4B[4];
	for (int i = 0; i<4; i++) {
		colors_rect[i] = ccc4(bgColor.r, bgColor.g, bgColor.b, bgColor.a);
	}

	//drawElements로 그리기 위한 도면 같은 거.
	GLubyte indices_rect[] = { 0, 1, 3, 2 };

	m_renderTexture->clear(0, 0, 0, 255);
	m_renderTexture->begin();

	//setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
	setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(GLProgram::SHADER_NAME_POSITION_COLOR));
	CC_NODE_DRAW_SETUP();

	ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color);

	glBlendFunc(GL_ONE, GL_ZERO);

	//반투명 배경 그리기.
	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices_rect);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, colors_rect);
	glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_BYTE, indices_rect);

	glColorMask(1.0f, 1.0f, 1.0f, 1.0f);
	glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);

	m_renderTexture->end();
	delete[] colors_rect;
}

