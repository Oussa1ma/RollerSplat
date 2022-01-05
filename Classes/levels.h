#ifndef __LEVELS_H__
#define __LEVELS_H__

#include "cocos2d.h"

class levels : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(levels);

    cocos2d::Menu* menu;
private:
    void GoToGameScene(cocos2d::Ref* sender);
    void GoToLevel2(cocos2d::Ref* sender);
    void GoToLevel3(cocos2d::Ref* sender);
};

#endif // __LEVELS_H__