#pragma once
class Component
{
public:
	Component(class Actor *actor , int updateOrder = 100);
	virtual ~Component();

	virtual void Update(float deltaTime); 

	int GetUpdateOrder() const { return updateOrder;  }
	class Actor* GetOwner() const { return mOwner;  }

protected:
	int updateOrder; 

	class Actor *mOwner; 
};

