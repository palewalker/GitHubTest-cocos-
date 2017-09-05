//
//#include "CSpotLight.h"
//
//#define THIS CSpotLight
//
//
//CSpotLight* CSpotLight::createWithRenderTexture(RenderTexture* rt, float radius, ccColor4B spotlightColor)
//{
//
//	CSpotLight *pRet = new CSpotLight();
//	if (pRet && pRet->init(rt, radius, spotlightColor))
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
//CSpotLight::CSpotLight()
//	:m_spreadTime(2.0f)
//	, m_spreadOutRadius(0)
//	, m_isRunningSpreadAnimation(false)
//	, m_isSpreadOut(true)
//{
//
//}
//
//CSpotLight::~CSpotLight() {
//	CCLog("CSpotLight destory");
//}
//
//bool CSpotLight::init(RenderTexture* pRenderTexture, float radius, Color4B spotlightColor)
//{
//	if (!Sprite::init()) {
//		return false;
//	}
//
//	Size visiableSize = Director::getInstance()->getVisibleSize();
//	Vec2 origin = Director::getInstance()->getVisibleOrigin();
//	disRect = Rect(origin.x, origin.y, visiableSize.width + origin.x, visiableSize.height + origin.y);
//
//	this->followSprite = NULL;
//	this->setPosition(CCPoint(disRect.size.width / 2, disRect.size.height / 2));
//	this->m_spotLightRadius = radius;
//	this->setRenderTexture(pRenderTexture);
//	//    this->setCanShadowMake(true);
//	this->spotlightColor = spotlightColor;
//	this->scheduleUpdate();
//
//	return true;
//}
//
//
//
///**=====================================================================////
//
//public
//
///======================================================================///*/
//
//
//
///**=====================================================================////
//
//private
//
///======================================================================///*/
//
//void CSpotLight::update(float dt) {
//	
//	int segs = 45;
//	GLfloat* vertices = new GLfloat[segs * 2];
//	Color4B* colors = new Color4B[segs];
//
//	
//	colors[0] = ccc4(spotlightColor.r, spotlightColor.g, spotlightColor.b, 255 - spotlightColor.a);
//	for (int i = 1; i < segs; i++) {
//		colors[i] = ccc4(0, 0, 0, 0);
//	}
//
//	const float coef = 2.0f * (float)M_PI / (segs - 2);
//	
//	vertices[0] = followSprite == NULL ? this->getPositionX() : followSprite->getPositionX();
//	vertices[1] = followSprite == NULL ? this->getPositionY() : followSprite->getPositionY();
//
//	
//	for (int i = 1; i < segs; i++)
//	{
//	
//		float rads = i*coef;
//		
//		float x = this->m_spotLightRadius * cosf(rads) + vertices[0];
//		float y = this->m_spotLightRadius * sinf(rads) + vertices[1];
//
//		vertices[i * 2] = x;
//		vertices[i * 2 + 1] = y;
//	}
//
//
//	m_renderTexture->begin();
//
//	
//	setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionColor));
//	CC_NODE_DRAW_SETUP();
//
//	ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color);
//
//	//    glBindTexture(GL_TEXTURE_2D, (GLuint) rt);    
//
//	if (spotlightColor.a == 0) {
//		glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
//		glColorMask(0.0f, 0.0f, 0.0f, 1.0f);
//	}
//	else {
//		glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);
//	}
//
//	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
//	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, colors);
//	glDrawArrays(GL_TRIANGLE_FAN, 0, segs);
//
//	glColorMask(1.0f, 1.0f, 1.0f, 1.0f);
//	glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);
//
//	CHECK_GL_ERROR_DEBUG();
//
//	
//	m_renderTexture->end();
//
//	
//	delete[] colors;
//	delete[] vertices;
//}
//
//void CSpotLight::spreadOutAndRemove(float pTime, float pSpreadOutRadius) {
//	m_spreadTime = pTime;
//
//	CCAssert(pSpreadOutRadius != 0, "");
//	m_spreadOutRadius = pSpreadOutRadius;
//	m_isRunningSpreadAnimation = true;
//	this->schedule(schedule_selector(THIS::updateSpreadOutAndRemove));
//}
//
//void CSpotLight::spread(float pTime, float pSpreadOutRadius, bool isOut) {
//	m_isSpreadOut = isOut;
//	m_spreadTime = pTime;
//	CCAssert(pSpreadOutRadius != 0, "");
//	m_spreadOutRadius = pSpreadOutRadius;
//	m_isRunningSpreadAnimation = true;
//	this->schedule(schedule_selector(THIS::updateSpreadOutTimer));
//}
//
//void CSpotLight::updateSpreadOutAndRemove(float dt) {
//
//	if (m_spreadTime > 0)
//	{
//		m_spreadTime -= dt;
//		//this->m_spotLightRadius += 3;
//		float deltaRadius = m_spreadOutRadius - m_spotLightRadius;
//		m_spotLightRadius += deltaRadius * dt / m_spreadTime;
//
//		if (this->m_spotLightRadius > m_spreadOutRadius)
//		{
//			m_isRunningSpreadAnimation = false;
//			this->unschedule(schedule_selector(THIS::updateSpreadOutAndRemove));
//			this->unscheduleUpdate();
//			this->removeFromParentAndCleanup(true);
//		}
//
//	}
//	else
//	{
//		m_isRunningSpreadAnimation = false;
//		this->unschedule(schedule_selector(THIS::updateSpreadOutAndRemove));
//		this->unscheduleUpdate();
//		this->removeFromParentAndCleanup(true);
//	}
//}
//void CSpotLight::updateSpreadOutTimer(float dt) {
//
//	if (m_spreadTime > 0)
//	{
//		m_spreadTime -= dt;
//
//		//this->m_spotLightRadius += 3;
//		float deltaRadius = m_spreadOutRadius - m_spotLightRadius;
//		m_spotLightRadius += deltaRadius * dt / m_spreadTime;
//		if (m_isSpreadOut) {
//			if (this->m_spotLightRadius > m_spreadOutRadius)
//			{
//				this->unschedule(schedule_selector(THIS::updateSpreadOutTimer));
//				m_isRunningSpreadAnimation = false;
//			}
//
//		}
//		else {
//			if (this->m_spotLightRadius < m_spreadOutRadius)
//			{
//				this->unschedule(schedule_selector(THIS::updateSpreadOutTimer));
//				m_isRunningSpreadAnimation = false;
//			}
//		}
//	}
//	else
//	{
//		this->unschedule(schedule_selector(THIS::updateSpreadOutTimer));
//		m_isRunningSpreadAnimation = false;
//	}
//}

//
//  CCSpotLight.cpp
//  exSpotLigt
//
//  Created by ������ on 13. 7. 15..
//
//

#include "CSpotLight.h"

#define THIS CCSpotLight


CCSpotLight* CCSpotLight::createWithRenderTexture(CCRenderTexture* rt, float radius, ccColor4B spotlightColor)
{

	CCSpotLight *pRet = new CCSpotLight();
	if (pRet && pRet->init(rt, radius, spotlightColor))
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
	:m_spreadTime(2.0f)
	, m_spreadOutRadius(0)
	, m_isRunningSpreadAnimation(false)
	, m_isSpreadOut(true)
{

}

THIS::~THIS() {
	//CCLog("CCSpotLight destory");
	log("CCSpotLight destory");
}

bool THIS::init(CCRenderTexture* pRenderTexture, float radius, ccColor4B spotlightColor)
{
	if (!CCSprite::init()) {
		return false;
	}

	CCSize visiableSize = CCDirector::sharedDirector()->getVisibleSize();
	CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();
	disRect = CCRectMake(origin.x, origin.y, visiableSize.width + origin.x, visiableSize.height + origin.y);

	this->followSprite = NULL;
	this->setPosition(CCPoint(disRect.size.width / 2, disRect.size.height / 2));
	this->m_spotLightRadius = radius;
	this->setRenderTexture(pRenderTexture);
	//    this->setCanShadowMake(true);
	this->spotlightColor = spotlightColor;
	this->scheduleUpdate();

	return true;
}



/**=====================================================================////

public

/======================================================================///*/



/**=====================================================================////

private

/======================================================================///*/

void THIS::update(float dt) {
	//���޹��� rt(�������Ҽ��ִ³༮)�ι����Ŭ�����ϰ�׸��⸦�����Ѵ�.
	int segs = 45;
	GLfloat* vertices = new GLfloat[segs * 2];
	ccColor4B* colors = new ccColor4B[segs];

	//���� �����ǻ����������Ѵ�.
	//�߽����� �༮�� ���� ���� �״�� ������ �Ѵ�.
	colors[0] = ccc4(spotlightColor.r, spotlightColor.g, spotlightColor.b, 255 - spotlightColor.a);
	for (int i = 1; i < segs; i++) {
		colors[i] = ccc4(0, 0, 0, 0);
	}

	const float coef = 2.0f * (float)M_PI / (segs - 2);
	//�׷��� �ﰢ������ ������ �߽��� ����. ����ٳ�� �� sprite�� ���� ������ �༮�� �߽����� ������.
	vertices[0] = followSprite == NULL ? this->getPositionX() : followSprite->getPositionX();
	vertices[1] = followSprite == NULL ? this->getPositionY() : followSprite->getPositionY();

	//8���� �������� �߽����� �����ϴ� �ﰢ���� �׸���. ��... ���̵�.
	for (int i = 1; i < segs; i++)
	{
		//���翡�� 8���� ���� ���� ����.
		float rads = i*coef;
		//spotLightRadius ������ ������ ���̸� ���� �� ���� 8�� �������� x,y��ǥ�� ���ϰ� �ִ�.
		//x = cx + cos(��) * r
		//y = cy + sin(��) * r
		float x = this->m_spotLightRadius * cosf(rads) + vertices[0];
		float y = this->m_spotLightRadius * sinf(rads) + vertices[1];

		vertices[i * 2] = x;
		vertices[i * 2 + 1] = y;
	}

	//������ ����!
	m_renderTexture->begin();

	//����� �׸��� �⺻ ���̴����޾ƿͼ� �����Ѵ�.
	setShaderProgram(CCShaderCache::sharedShaderCache()->programForKey(GLProgram::SHADER_NAME_POSITION_COLOR));
	CC_NODE_DRAW_SETUP();

	ccGLEnableVertexAttribs(kCCVertexAttribFlag_Position | kCCVertexAttribFlag_Color);

	//    glBindTexture(GL_TEXTURE_2D, (GLuint) rt);    

	if (spotlightColor.a == 0) {
		glBlendFunc(GL_ZERO, GL_ONE_MINUS_SRC_ALPHA);
		glColorMask(0.0f, 0.0f, 0.0f, 1.0f);
	}
	else {
		glBlendFunc(GL_SRC_COLOR, GL_ONE_MINUS_SRC_ALPHA);
	}

	glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glVertexAttribPointer(kCCVertexAttrib_Color, 4, GL_UNSIGNED_BYTE, GL_TRUE, 0, colors);
	glDrawArrays(GL_TRIANGLE_FAN, 0, segs);

	glColorMask(1.0f, 1.0f, 1.0f, 1.0f);
	glBlendFunc(CC_BLEND_SRC, CC_BLEND_DST);

	CHECK_GL_ERROR_DEBUG();

	//�������������Ѵ�.
	m_renderTexture->end();

	//��������Ȱ���ߴ��迭�������Ѵ�.
	delete[] colors;
	delete[] vertices;
}

void THIS::spreadOutAndRemove(float pTime, float pSpreadOutRadius) {
	m_spreadTime = pTime;

	CCAssert(pSpreadOutRadius != 0, "");
	m_spreadOutRadius = pSpreadOutRadius;
	m_isRunningSpreadAnimation = true;
	this->schedule(schedule_selector(THIS::updateSpreadOutAndRemove));
}

void THIS::spread(float pTime, float pSpreadOutRadius, bool isOut) {
	m_isSpreadOut = isOut;
	m_spreadTime = pTime;
	CCAssert(pSpreadOutRadius != 0, "");
	m_spreadOutRadius = pSpreadOutRadius;
	m_isRunningSpreadAnimation = true;
	this->schedule(schedule_selector(THIS::updateSpreadOutTimer));
}

void THIS::updateSpreadOutAndRemove(float dt) {

	if (m_spreadTime > 0)
	{
		m_spreadTime -= dt;
		//this->m_spotLightRadius += 3;
		float deltaRadius = m_spreadOutRadius - m_spotLightRadius;
		m_spotLightRadius += deltaRadius * dt / m_spreadTime;

		if (this->m_spotLightRadius > m_spreadOutRadius)
		{
			m_isRunningSpreadAnimation = false;
			this->unschedule(schedule_selector(THIS::updateSpreadOutAndRemove));
			this->unscheduleUpdate();
			this->removeFromParentAndCleanup(true);
		}

	}
	else
	{
		m_isRunningSpreadAnimation = false;
		this->unschedule(schedule_selector(THIS::updateSpreadOutAndRemove));
		this->unscheduleUpdate();
		this->removeFromParentAndCleanup(true);
	}
}
void THIS::updateSpreadOutTimer(float dt) {

	if (m_spreadTime > 0)
	{
		m_spreadTime -= dt;

		//this->m_spotLightRadius += 3;
		float deltaRadius = m_spreadOutRadius - m_spotLightRadius;
		m_spotLightRadius += deltaRadius * dt / m_spreadTime;
		if (m_isSpreadOut) {
			if (this->m_spotLightRadius > m_spreadOutRadius)
			{
				this->unschedule(schedule_selector(THIS::updateSpreadOutTimer));
				m_isRunningSpreadAnimation = false;
			}

		}
		else {
			if (this->m_spotLightRadius < m_spreadOutRadius)
			{
				this->unschedule(schedule_selector(THIS::updateSpreadOutTimer));
				m_isRunningSpreadAnimation = false;
			}
		}
	}
	else
	{
		this->unschedule(schedule_selector(THIS::updateSpreadOutTimer));
		m_isRunningSpreadAnimation = false;
	}
}