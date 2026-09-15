#pragma once
#include "Gamestate.h"

class ResultState : public Gamestate
{
	int result;
	int drawCount;

public:
	ResultState(int result, int drawCount);
	void OnEnter(GameManager* manager) override;
	void OnUpdate(GameManager* manager, float deltaTime) override;
	void OnExit(GameManager* manager) override;
	const std::string GetName() const override;
};
