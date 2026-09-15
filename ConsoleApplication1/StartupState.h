#pragma once
#include "Gamestate.h"

class StartupState : public Gamestate
{
public:
	void OnEnter(GameManager* manager) override;
	void OnUpdate(GameManager* manager) override;
};
