#pragma once
#include <vector>
struct Vector2
{
	float x;
	float y;
};
class Actor
{
public:
	enum State {
		EActive,
		EPaused,
		EDead
	};
	//Constructor/destructor
	Actor(class Game* game);
	virtual ~Actor();
	//Update function called from Game
	void Update(float deltaTime);
	void UpdateComponents(float deltaTime);
	virtual void UpdateActor(float deltaTime);

	// Getters/setters
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	void SetScale(float scale) { mScale = scale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

	State GetState() const { return mState; }
	//Add/remove components

	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);
private:
	State mState; //actor state
	Vector2 mPosition; //Position of actor
	float mScale;
	float mRotation;
	std::vector<class Component*> mComponents;
	class Game* mGame;
};

