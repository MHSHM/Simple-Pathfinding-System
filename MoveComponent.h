#pragma once
#include "Component.h"
class MoveComponent : public Component
{
public:
	MoveComponent(class Actor *actor , int UpdateOrder = 10);
	~MoveComponent();

	void Update(float deltaTime) override; 

	void SetForwardSpeed(float val) { mForwardSpeed = val;  }

	float GetForwardSpeed() const { return mForwardSpeed;  }

private:
	float mForwardSpeed; 
};

