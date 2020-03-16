#include "pch.h"
#include "CircleComponent.h"
#include "Actor.h"

CircleComponent::CircleComponent(Actor *actor):
	Component(actor),
	mRadius(0.0f)
{
}

Vector2 CircleComponent::GetCenter() 
{
	return mOwner->GetPosition(); 
}

CircleComponent::~CircleComponent()
{
}
