#include "pch.h"
#include "MoveComponent.h"
#include "Actor.h"


MoveComponent::MoveComponent(Actor *actor , int updateOrder):
	Component(actor , updateOrder),
	mForwardSpeed(0.0f)
{
}

void MoveComponent::Update(float deltaTime) 
{
	
	if (!Math::NearZero(mForwardSpeed))
	{
		Vector2 pos = mOwner->GetPosition();
		pos += mForwardSpeed * mOwner->GetForward() * deltaTime;
		mOwner->SetPosition(pos); 
	}
}


MoveComponent::~MoveComponent()
{
}
