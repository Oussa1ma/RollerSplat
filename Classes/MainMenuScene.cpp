
#include "MainMenuScene.h"
#include "rollerscene.h"
#include "levels.h"

USING_NS_CC;

/*creation de la scene menu  */

Scene* MainMenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = MainMenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainMenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if (!Layer::init())
    {
        return false;
    }

    /* la mise on forme de menu */

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    
    auto backgroundSprite = Sprite::create("background.png");
    backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
    this->addChild(backgroundSprite);


    auto titleSprite = Sprite::create("title.png");
    titleSprite->setPosition(Point(visibleSize.width * 0.57 + origin.x, visibleSize.height * 0.68));
    titleSprite->setScale(0.6);
    this->addChild(titleSprite, 4);

   
    auto playItem = MenuItemImage::create("play.png", "clicked_play.png", CC_CALLBACK_1(MainMenuScene::GoToGameScene, this));
    playItem->setPosition(Point(visibleSize.width / 2 + origin.x , visibleSize.height*0.56 + origin.y ) );
    playItem->setScale(0.8);


    auto levelsItem = MenuItemImage::create("levels.png", "clicked_levels.png", CC_CALLBACK_1(MainMenuScene::GoToLevels, this));
    levelsItem->setPosition(Point(visibleSize.width * 0.5+ origin.x, visibleSize.height * 0.33 + origin.y));
    levelsItem->setScale(0.8);

    auto menu = Menu::create(playItem, levelsItem, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu,4);

    return true;
}



/* la fonction responsable de la transition des scene */


void MainMenuScene::GoToGameScene(cocos2d::Ref* sender)
{
    auto scene = rollerscene::createScene();

    Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}




void MainMenuScene::GoToLevels(cocos2d::Ref* sender)
{
    auto scene = levels::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(1, scene));
}