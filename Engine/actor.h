#include <iostream>
#include <vector>

struct Vector2 {
	float x;
	float y;
};

class Actor {
public:
	// Used to track the state of actor
	enum State {
		aActive,
		aPaused,
		aDead
	};

	// Constructor/ Destructor
	Actor(class Game* game);
	virtual ~Actor();

	// Update function called from Game (not overridable)
	void Update(float deltaTime);

	// Updates all the components attached to the actor (not overridable)
	void UpdateComponents(float deltaTime);

	// Any actor-specific update code (overridable)
	virtual void UpdateActor(float deltaTime);

	// Getters / Setters
	const Vector2& GetPosition() const { return mPosition; }
	void SetPosition(const Vector2& pos) { mPosition = pos; }
	float GetScale() const { return mScale; }
	float GetRotation() const { return mRotation; }
	void SetRotation(float rotation) { mRotation = rotation; }

	State GetState() const { return mState; }
	void SetState(State state) { mState = state; }

	class Game* GetGame() { return mGame; }

	// Add / Remove Components
	void AddComponent(class Component* component);
	void RemoveComponent(class Component* component);

private:
	// Actor's sate
	State mState;

	// Transform
	Vector2 mPosition;	// Center position of Actor
	float mScale;		// Uniforms scale of Actor (1.0f for 100%)
	float mRotation;	// Rotation angle (in radians)


	// Components held by this actor
	std::vector<class Component*> mComponents;
	
	class Game* mGame;
};