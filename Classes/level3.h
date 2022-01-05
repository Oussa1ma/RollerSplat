#pragma once
#include "cocos2d.h"
#include <vector>
#include<iterator>
using namespace cocos2d;





class level3 : public cocos2d::Layer

{ 
public :
	int posmodify__x;
    int posmodify__y;
	std::vector<Sprite*> theway;
	

	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    static cocos2d::Scene* createScene();


	virtual bool init();
	
Sprite* sprite;
Sprite* ball;
Sprite* Path;


	CREATE_FUNC(level3);

	int paint = 0;
	void SwitchToMainMenu(float dt);
	bool isnotcolored(Sprite*);
	void update(float dt);
	bool ismoving = false;
	void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; };
	cocos2d::PhysicsWorld* sceneWorld;
	bool onContactBegin(cocos2d::PhysicsContact& contact);


};  

