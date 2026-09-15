#pragma once
#include "Gamestate.h"

#include <memory>

class GameManager
{
	std::unique_ptr<Gamestate> currentState;
	std::unique_ptr<Gamestate> nextState;
	bool isRunning;
	bool isUpdating;
	float gameTime;

	void ApplyStateChange();

public:
	GameManager();
	void ChangeState(std::unique_ptr<Gamestate> newState);
	void Update(float deltaTime);
};

