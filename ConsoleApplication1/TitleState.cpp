#include "TitleState.h"

#include <conio.h>
#include <iostream>
#include <memory>

#include "GameManager.h"
#include "MainMenuState.h"

void TitleState::OnEnter(GameManager* manager)
{
	std::cout << "\n=== タイトル ===\n";
	std::cout << "何かキーを押すとメインメニューへ進みます。\n";
}

void TitleState::OnUpdate(GameManager* manager, float deltaTime)
{
	_getch();
	manager->ChangeState(std::make_unique<MainMenuState>());
}

void TitleState::OnExit(GameManager* manager)
{
}

const std::string TitleState::GetName() const
{
	return "TitleState";
}
