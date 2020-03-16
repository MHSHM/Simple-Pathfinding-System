#pragma once
#include "Actor.h"
class Cheese : public Actor
{
public:
	Cheese(class Game *game);


	~Cheese();


	class CircleComponent* GetCircle() { return mCircle;  }


private:

	class CircleComponent* mCircle;
};