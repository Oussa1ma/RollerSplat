#pragma once
#include "level2.h"
#include <cocos2d.h>
#include <vector> 
#include<iostream>
using namespace std;
using namespace cocos2d;
Scene* level2::createScene()
{

	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	auto layer = level2::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);

	return scene;

}
bool level2::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	for (int i = 0; i <= 6; i++) {
		for (int j = 0; j <= 5; j++) {
			if (i == 0 || j == 0 || j == 5 || i == 6 || i == 3 && j == 3 || i == 1 && j == 2 || i == 3 && j == 3 || i == 3 && j == 2 || i == 4 && j == 2 || i == 4 && j == 3) {
				sprite = Sprite::create("thewall.png ");
				sprite->setAnchorPoint(Vec2(0, 0));
				sprite->setColor(Color3B(169, 169, 169));
				auto physicsBody = PhysicsBody::createBox(Size(50.0f, 50.0f), PhysicsMaterial(0, 0, 0));
				physicsBody->setDynamic(false);
				sprite->setPhysicsBody(physicsBody);
				physicsBody->setCollisionBitmask(2);
				physicsBody->setContactTestBitmask(true);
				sprite->setPosition(100 + 50 * i, 10 + 50 * j);

				this->addChild(sprite);

			}
			else
			{
				Path = Sprite::create("thewall.png ");
				Path->setPosition(125 + 50 * i, 35 + 50 * j);

				theway.push_back(Path);
				this->addChild(Path);
			}
		}
	}


	ball = Sprite::create("ball1.png ");

	auto spriteBody1 = PhysicsBody::createCircle(ball->getContentSize().width / 2);
	ball->setPhysicsBody(spriteBody1);
	spriteBody1->setCollisionBitmask(1);
	spriteBody1->setContactTestBitmask(true);
	spriteBody1->setDynamic(true);
	ball->setAnchorPoint(Vec2(0, 0));
	ball->setPosition(160, 70);


	this->addChild(ball);
	ball->getBoundingBox();
	sprite->getBoundingBox();


	auto backgroundSprite = Sprite::create("background2.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite, -11);



	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(level2::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);


	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(level2::keyPressed, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	this->scheduleUpdate();




	return true;
}
void level2::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (ismoving == false) {
		if (keyCode == EventKeyboard::KeyCode::KEY_UP_ARROW)
		{
			posmodify__x = 0;
			posmodify__y = 1;
			ismoving = true;

		}
		if (keyCode == EventKeyboard::KeyCode::KEY_LEFT_ARROW)
		{
			posmodify__x = -1;
			posmodify__y = 0;
			ismoving = true;

		}if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
		{
			posmodify__x = 1;
			posmodify__y = 0;
			ismoving = true;

		}
		if (keyCode == EventKeyboard::KeyCode::KEY_DOWN_ARROW)
		{
			posmodify__x = 0;
			posmodify__y = -1;
			ismoving = true;

		}
	}
}


void level2::update(float delta) {
	auto position = ball->getPosition();
	if (ismoving == true) {

		position.x += 10 * posmodify__x;
		position.y += 10 * posmodify__y;
		ball->setPosition(position);

	}

	for (auto i = 0; i <= 60; i++) {
		for (auto j = 0; j <= 60; j++) {
			for (auto object : this->theway)
			{
				if ((ball->getPositionX() + i) == object->getPositionX() && (ball->getPositionY() + j) == object->getPositionY() && isnotcolored(object) == true && paint<15) {
					object->setColor(Color3B(77, 45, 100));
					++paint;

				}

			}


		}
	}
	if (paint == 15) {
		for (auto object : this->theway) {
			object->setColor(Color3B(1, 1, 1));
			auto scene = level3::createScene();

			Director::getInstance()->replaceScene(TransitionFade::create(0, scene));
		}
	}




}
bool level2::onContactBegin(cocos2d::PhysicsContact& contact)
{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	// check if the bodies have collided
	if ((1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) || (2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
	{
		ismoving = false;

		auto x = ball->getPositionX();
		auto y = ball->getPositionY();
		if (posmodify__x == 0 && posmodify__y == 1) {
			ball->setPosition(x, y - 10);
		}
		if (posmodify__x == 0 && posmodify__y == -1) {
			ball->setPosition(x, y + 10);
		}
		if (posmodify__x == 1 && posmodify__y == 0) {
			ball->setPosition(x - 10, y);
		}
		if (posmodify__x == -1 && posmodify__y == 0) {
			ball->setPosition(x + 10, y);
		}

	}

	return true;
}
bool level2::isnotcolored(Sprite* object) {

	if (object->getColor() == Color3B(77, 45, 100)) {
		return false;
	}
	return true;
}