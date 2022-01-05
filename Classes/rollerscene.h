#pragma once
#include "cocos2d.h"
#include <vector>
#include<iterator>
#include <level2.h>


// D�finition de la classe principale pour le 1er stage
class rollerscene : public cocos2d::Layer

{ 
public :  

	// D�claration des toutes les variables et les m�thodes n�cessaire pour le 1er stage du jeux

	int posmodify__x;
    int posmodify__y;
	std::vector<Sprite*> theway;
	

	void keyPressed(cocos2d::EventKeyboard::KeyCode keyCode, cocos2d::Event* event);
    static cocos2d::Scene* createScene();


	virtual bool init();
	
    Sprite* sprite;
    Sprite* ball;
    Sprite* Path;


	CREATE_FUNC(rollerscene);

	int paint = 0;
	bool isnotcolored(Sprite*);
	void update(float dt);
	bool ismoving = false;

	// D�claration de la m�thode qui accorde un monde physique � notre scene
	void SetPhysicsWorld(cocos2d::PhysicsWorld* world) { sceneWorld = world; };
	cocos2d::PhysicsWorld* sceneWorld;
    
	// La m�thode qui d�tecte le contact entre deux corps physiques dans la sc�ne
	bool onContactBegin(cocos2d::PhysicsContact& contact);


};  

