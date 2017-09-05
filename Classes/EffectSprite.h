#ifndef _EFFECTSPRITE_H_
#define _EFFECTSPRITE_H_

#include "cocos2d.h"
USING_NS_CC;


class LightEffect;


class EffectSprite : public cocos2d::Sprite
{
public:
    static EffectSprite *create(const std::string &filename);
    static EffectSprite *createWithSpriteFrame(cocos2d::SpriteFrame *spriteFrame);
	static EffectSprite* createWithTexture(Texture2D *texture);
    
    void setEffect(LightEffect *effect, Texture2D* Normal);
    
protected:
    virtual void draw(cocos2d::Renderer *renderer, const cocos2d::Mat4 &transform, uint32_t flags) override;
    
    ~EffectSprite();
    
    LightEffect *_effect = nullptr;
    cocos2d::Texture2D *_normalmap = nullptr;
};

#endif
