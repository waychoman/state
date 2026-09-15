#pragma once
#include "Gamestate.h"

#include <memory>

class GameManager
{
	std::unique_ptr<Gamestate> currentState;
	std::unique_ptr<Gamestate> nextState;
	bool isUpdating = false;
	int drawRangeMaximum = 10;

	void ApplyStateChange();

public:
	void ChangeState(std::unique_ptr<Gamestate> newState);
	void Update();
	int GetDrawRangeMaximum() const;
	bool SetDrawRangeMaximum(int maximum);
};

