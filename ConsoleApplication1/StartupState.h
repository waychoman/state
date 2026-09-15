#pragma once
#include "Gamestate.h"

class StartupState : public Gamestate
{
public:
	void OnEnter(GameManager* manager) override;
	void OnUpdate(GameManager* manager, float deltaTime) override;
	void OnExit(GameManager* manager) override;
	const std::string GetName() const override;
};
