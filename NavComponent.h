#pragma once
#include "MoveComponent.h"
#include "Math.h"
#include <queue>
class NavComponent : public MoveComponent
{
public:
	NavComponent(class Actor *actor , int updateOrder = 10);
	~NavComponent();

	void Update(float deltaTime) override; 

	void TurnTo(Vector2 destination);
	void StartPath(class Tile* start); 


private:
	class Tile* mNextPoint; 
};

