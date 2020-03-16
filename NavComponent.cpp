#include "pch.h"
#include "NavComponent.h"
#include "Tile.h"


NavComponent::NavComponent(Actor *actor , int updateOrder):
	MoveComponent(actor , updateOrder),
	mNextPoint(nullptr)
{
}

void NavComponent::Update(float deltaTime)
{
	if (mNextPoint) 
	{
		Vector2 diff = mOwner->GetPosition() - mNextPoint->GetPosition(); 
		if (Math::NearZero(diff.Length() , 2.0f)) 
		{
			mNextPoint = mNextPoint->GetParent();
			if (mNextPoint) 
			{
				TurnTo(mNextPoint->GetPosition());
			} 
		}
		MoveComponent::Update(deltaTime); 
	}
}

void NavComponent::StartPath(Tile* startPoint) 
{
	mNextPoint = startPoint->GetParent(); 
	TurnTo(mNextPoint->GetPosition()); 
}

void NavComponent::TurnTo(Vector2 destination) 
{
	Vector2 diff = destination - mOwner->GetPosition(); 
	//diff.Normalize(); 
	float angle = Math::Atan2(-diff.y , diff.x) ; 
	mOwner->SetRotation(angle); 
}


NavComponent::~NavComponent()
{
}
