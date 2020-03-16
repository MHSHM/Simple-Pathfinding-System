#pragma once
#include <vector>
#include "Math.h"
class Actor
{

public:
	Actor(class Game *game);
	virtual ~Actor();

	void Update(float deltaTime);
	// for any custom behaviour
	virtual void UpdateActor(float deltaTime);
	virtual void UpdateComponents(float deltaTime); 

	void AddComponent(class Component* comp); 
	void RemoveComponent(class Component* comp);

	void SetPosition(const Vector2& pos) { mPosition = pos; }
	void SetScale(float val) { mScale = val;  }
	void SetRotation(float val) { mRotation = val;  }
	void SetActive(bool val) { isActive = val;  }
	void SetPaused(bool val) { isPaused = val;  }

	Vector2& GetPosition() { return mPosition; }
	float GetScale() const { return mScale;  }
	float GetRotation() const { return mRotation;  }
	class Game *GetGame() const { return game;  }
	Vector2 GetForward() const { return Vector2(Math::Cos(mRotation), -Math::Sin(mRotation)); }

	
	bool IsActive() const { return isActive;  }
	bool IsPaused() const { return isPaused; }

private:

	Vector2 mPosition; 
	float mScale;
	float mRotation; 

	std::vector<class Component*> mComponents; 

	bool isActive; 
	bool isPaused; 

	class Game *game; 

};

bool proceed(const class Component *c1, const class Component *c2); 


