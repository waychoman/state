#include "MainMenuState.h"

#include <conio.h>
#include <iostream>
#include <memory>

#include "GameManager.h"
#include "InGameState.h"

void MainMenuState::OnEnter(GameManager* manager)
{
	std::cout << "\n=== メインメニュー ===\n";
	std::cout << "1キーを押すとゲームを開始します。\n";
}

void MainMenuState::OnUpdate(GameManager* manager, float deltaTime)
{
	if (_getch() == '1')
	{
		manager->ChangeState(std::make_unique<InGameState>());
	}
}

void MainMenuState::OnExit(GameManager* manager)
{
}

const std::string MainMenuState::GetName() const
{
	return "MainMenuState";
}
