#pragma once
#include "Gamestate.h"

class MainMenuState : public Gamestate
{
public:
	void OnEnter(GameManager* manager) override;
	void OnUpdate(GameManager* manager) override;
};
