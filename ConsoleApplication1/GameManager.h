#pragma once
#include"Gamestate.h"

#include<memory>
class Gamestate;
class GameManager
{

	std::unique_ptr<Gamestate> currentState;
	bool isRunning;
	float gameTime;
public:
	GameManager() : isRunning(true), gameTime(0.0f) {}
	void ChangeState(std::unique_ptr<Gamestate> newState)
	{
		currentState->OnExit(this);
		currentState = std::move(newState);
		currentState->OnEnter(this);
	}
	void Update(float deltaTime)
	{
		gameTime += deltaTime;
		if (currentState)
		{
			currentState->OnUpdate(this, deltaTime);
		}
	}
};

