
#include "levels.h"
#include "rollerscene.h"
//#include "level2.h"

USING_NS_CC;

Scene* levels::createScene()
{
  
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = levels::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool levels::init()
{
    
    if (!Layer::init())
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    auto backgroundSprite = Sprite::create("background.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(backgroundSprite);

   
   auto level1 = MenuItemImage::create("level1.png", "clicked_level1.png", CC_CALLBACK_1(levels::GoToGameScene, this));
   level1->setPosition(Point(visibleSize.width / 2 + origin.x , visibleSize.height*0.73 + origin.y ) );
   level1->setScale(0.8);


   auto level2 = MenuItemImage::create("level2.png", "clicked_level2.png", CC_CALLBACK_1(levels::GoToLevel2, this));
   level2->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.50 + origin.y));
   level2->setScale(0.8);

   auto level3 = MenuItemImage::create("level3.png", "clicked_level3.png", CC_CALLBACK_1(levels::GoToLevel3, this));
   level3->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height * 0.27 + origin.y));
   level3->setScale(0.8);

    menu = Menu::create(level1, level2, level3, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu,4);

    return true;
}




void levels::GoToGameScene(cocos2d::Ref* sender)
{
    auto scene = rollerscene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}




void levels::GoToLevel2(cocos2d::Ref* sender)
{
    auto scene = level2::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}


void levels::GoToLevel3(cocos2d::Ref* sender)
{
    auto scene = level3::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}