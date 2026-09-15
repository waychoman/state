#pragma once
#include "Gamestate.h"
class TitleState : public Gamestate
{
public:
	void OnEnter(GameManager* manager) override;
	void OnUpdate(GameManager* manager) override;
};
