#pragma once
#include "Gamestate.h"

#include <random>

class InGameState : public Gamestate
{
	std::mt19937 randomEngine;
	std::uniform_int_distribution<int> distribution;
	int drawCount;

public:
	explicit InGameState(int drawRangeMaximum);
	void OnEnter(GameManager* manager) override;
	void OnUpdate(GameManager* manager) override;
};
