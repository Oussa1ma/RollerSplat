#include "LastScene.h"
#include <cocos2d.h>

USING_NS_CC;

Scene* LastScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = LastScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// La méthode iniit pour initialiser les intances 
bool LastScene::init()
{

    if (!Layer::init())
    {
        return false;
    }


    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    

    auto backgroundSprite = Sprite::create("background.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(backgroundSprite,-11);



    auto titleSprite = Sprite::create("title.png");
    titleSprite->setPosition(Point(visibleSize.width * 0.57 + origin.x, visibleSize.height * 0.68));
    titleSprite->setScale(0.6);
    this->addChild(titleSprite, 4);


    //L'addition des effets de particules

    auto emitter = ParticleFireworks::create();
    emitter->setPosition(Point(visibleSize.width/2 , visibleSize.height * 0.30));
    addChild(emitter, -10);

    return true;
}
