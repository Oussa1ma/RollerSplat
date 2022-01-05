#pragma once
#include "rollerscene.h"
#include <cocos2d.h>
#include <vector> 
using namespace cocos2d;
Scene* rollerscene::createScene()/*creation une scene du jeux */
{
	/*creation de layer */
	auto scene = Scene::createWithPhysics();
	scene->getPhysicsWorld()->setGravity(Vec2(0, 0));
	auto layer = rollerscene::create();
	layer->SetPhysicsWorld(scene->getPhysicsWorld());
	scene->addChild(layer);

	return scene;

}
bool rollerscene::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	/*--------la creation de la Labyrinthe que la balle soit positionner---------*/
	for (int i = 0; i <= 5; i++)
	{
		for (int j = 0; j <= 5; j++) 
		{
			if (i == 0 || j == 0 || j == 5 || i == 5 || i == 3 && j == 3 || i == 3 && j == 2 || i == 2 && j == 2 || i == 2 && j == 3) 
			{
				/*-----creation de la sprite du mure--------*/
				sprite = Sprite::create("thewall.png ");
				sprite->setAnchorPoint(Vec2(0, 0));
				sprite->setColor(Color3B(169, 169, 169));
				/*la partie physique de mure */
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
				/* la creation de chemin de la balle */

				Path = Sprite::create("thewall.png ");
				Path->setPosition(125 + 50 * i, 35 + 50 * j);
				theway.push_back(Path);
				this->addChild(Path);
			}
		}
	}


	/*--------la creation du Sprite balle est la mise en forme des caracteristique lde la balle ---------*/


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



	/* l addition d un backround aux jeu */


	auto backgroundSprite = Sprite::create("background1.png");
	backgroundSprite->setPosition(Point(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(backgroundSprite,-10);


	
	/*creation d un event listener qui detecte s'il y a un contact  */

	auto contactListener = EventListenerPhysicsContact::create();
	contactListener->onContactBegin = CC_CALLBACK_1(rollerscene::onContactBegin, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);




	/*creation d un event listener de keyboard */

	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(rollerscene::keyPressed, this);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);

	this->scheduleUpdate();




	return true;
}




/*la fontion qui responsable au mouvement de la balle en utilisant le clavier */

void rollerscene::keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event)
{
	if (ismoving == false)
	{
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

		}
		
		if (keyCode == EventKeyboard::KeyCode::KEY_RIGHT_ARROW)
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



/* la fonction update */


void rollerscene::update(float delta)
{
	/*condition de mouvement*/

	auto position = ball->getPosition();
	if (ismoving == true)
	{
		position.x += 10 * posmodify__x;
		position.y += 10 * posmodify__y;
		ball->setPosition(position);
	}

	/*la partie responsable de changement de couleur de chemin*/

	for (auto i = 0; i <= 60; i++) 
	{
		for (auto j = 0; j <= 60; j++)
		{
			for (auto object : this->theway)
			{
				if ((ball->getPositionX() + i) == object->getPositionX() && (ball->getPositionY() + j) == object->getPositionY() && isnotcolored(object) == true && paint<12) 
				{
					object->setColor(Color3B(102, 255, 102));
					++paint;

				}

			}


		}
	}


	/* la partie resposable de changement de scene */
 
	if (paint == 12) {
		for (auto object : this->theway) 
		{
			object->setColor(Color3B(1, 1, 1));
			auto scene = level2::createScene();

			Director::getInstance()->replaceScene(TransitionFade::create(0, scene));

		}
	}
}

/*la fonction qui detecte la collision entre les objets physique */

bool rollerscene::onContactBegin(cocos2d::PhysicsContact& contact)
{
	PhysicsBody* a = contact.getShapeA()->getBody();
	PhysicsBody* b = contact.getShapeB()->getBody();

	// check if the bodies have collided
	if ((1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask()) || (2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask()))
	{

		ismoving = false;
		/* la parite de la correction de deplacement de la balle*/

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


/*la verification du couler s'il est colore ou non */

bool rollerscene::isnotcolored(Sprite* object) {

	if (object->getColor() == Color3B(102, 255, 102)) {
		return false;
	}
	return true;
}