#include "GameManager.h"

#include <utility>

GameManager::GameManager() 
	: isRunning(true), isUpdating(false), gameTime(0.0f)
{
}

void GameManager::ChangeState(std::unique_ptr<Gamestate> newState)
{
	nextState = std::move(newState);

	if (!isUpdating)
	{
		ApplyStateChange();
	}
}

void GameManager::ApplyStateChange()
{
	if (!nextState)
	{
		return;
	}

	if (currentState)
	{
		currentState->OnExit(this);
	}

	currentState = std::move(nextState);
	currentState->OnEnter(this);
}

void GameManager::Update(float deltaTime)
{
	gameTime += deltaTime;
	if (currentState)
	{
		isUpdating = true;
		currentState->OnUpdate(this, deltaTime);
		isUpdating = false;
		ApplyStateChange();
	}
}
