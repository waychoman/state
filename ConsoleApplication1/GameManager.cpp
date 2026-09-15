#include "GameManager.h"

#include <utility>

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

void GameManager::Update()
{
	if (currentState)
	{
		isUpdating = true;
		currentState->OnUpdate(this);
		isUpdating = false;
		ApplyStateChange();
	}
}

int GameManager::GetDrawRangeMaximum() const
{
	return drawRangeMaximum;
}

bool GameManager::SetDrawRangeMaximum(int maximum)
{
	if (maximum < 1)
	{
		return false;
	}

	drawRangeMaximum = maximum;
	return true;
}
