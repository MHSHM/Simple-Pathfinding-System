#include "pch.h"
#include "Component.h"
#include "Actor.h"


Component::Component(Actor *actor , int updateOrder):
	mOwner(actor),
	updateOrder(updateOrder)
{
	mOwner->AddComponent(this); 
}

void Component::Update(float deltaTime) 
{
	
}

Component::~Component()
{
	mOwner->RemoveComponent(this); 
}
