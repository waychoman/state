#include "GameManager.h"
#include"Gamestate.h"

GameManager::GameManager() 
	: isRunning(true), gameTime(0.0f) 
{
}

void GameManager::ChangeState(std::unique_ptr<Gamestate> newState)
{
	currentState->OnExit(this);
	currentState = std::move(newState);
	currentState->OnEnter(this);
}

void GameManager::Update(float deltaTime)
{
	gameTime += deltaTime;
	if (currentState)
	{
		currentState->OnUpdate(this, deltaTime);
	}
}