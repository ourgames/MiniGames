//
//  Obstacle.hpp
//  fightGame
//
//  Created by 葛富臻 on 15/12/24.
//
//

#ifndef Obstacle_hpp
#define Obstacle_hpp

#include <stdio.h>
class Obstacle :public cocos2d::Sprite
{
public:
	Obstacle(void);
	~Obstacle(void);
	CREATE_FUNC(Obstacle);
	virtual bool init();
public:
	void show();
	void hide();
	void reset();
	bool isAlive();
    //bool IsCollideWithPlayer(Player *player);
private:
	bool m_isAtive;
};
#endif /* Obstacle_hpp */
