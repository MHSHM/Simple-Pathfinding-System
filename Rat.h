#pragma once
#include "Actor.h"

class Rat : public Actor
{
public:
	Rat(class Game *game);
	~Rat();


	void UpdateActor(float deltaTime) override; 
	class CircleComponent *GetCircle() { return mCircle;  }
	

private:

	class CircleComponent *mCircle; 
	class NavComponent *nav; 

	bool mIsPathFound;
	

};

bool Intersect(class CircleComponent* c1, class CircleComponent* c2); 
