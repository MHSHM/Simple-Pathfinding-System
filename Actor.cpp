#include "pch.h"
#include "Actor.h"
#include "Game.h"
#include "Component.h"
#include <algorithm>

Actor::Actor(Game *game) :
	game(game),
	mPosition(Vector2::Zero),
	mScale(1.0f),
	mRotation(0.0f),
	isActive(true)
{
	game->AddActor(this); 
}

bool proceed(const Component *c1, const Component *c2) 
{
	return c1->GetUpdateOrder() < c2->GetUpdateOrder(); 
}

void Actor::Update(float deltaTime) 
{
	if (isActive) 
	{
		if (!isPaused) 
		{
			UpdateActor(deltaTime);
		}
		UpdateComponents(deltaTime);
	}
}

void Actor::UpdateActor(float deltaTime) 
{
	
}

void Actor::UpdateComponents(float deltaTime) 
{
	for (auto comp : mComponents) 
	{
		comp->Update(deltaTime);
	}
}

void Actor::AddComponent(Component *comp) 
{
	// insert component then sort based on updateOrder
	mComponents.emplace_back(comp);
	std::sort(mComponents.begin(), mComponents.end(), proceed); 
}

void Actor::RemoveComponent(Component *comp) 
{
	auto iter = mComponents.begin(); 
	for (; iter != mComponents.end(); ++iter) 
	{
		if (*iter == comp) 
		{
			break; 
		}
	}
	std::iter_swap(iter, mComponents.end() - 1); 
	mComponents.pop_back(); 
}


Actor::~Actor()
{
	game->RemoveActor(this); 

	// remove components of this actor
	while (!mComponents.empty()) 
	{
		delete mComponents.back(); 
	}
}
