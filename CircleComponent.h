#pragma once
#include "Component.h"
#include "Math.h"
class CircleComponent : public Component
{
public:
	CircleComponent(class Actor *actor);
	~CircleComponent();

	void SetRadius(float val) { mRadius = val;  }

	Vector2 GetCenter(); 
	float GetRadius() { return mRadius;  }

private:
	float mRadius; 
};

