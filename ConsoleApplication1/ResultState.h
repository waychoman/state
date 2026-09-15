#pragma once
#include "Gamestate.h"

class ResultState : public Gamestate
{
	int drawCount;

public:
	explicit ResultState(int drawCount);
	void OnEnter(GameManager* manager) override;
	void OnUpdate(GameManager* manager) override;
};
