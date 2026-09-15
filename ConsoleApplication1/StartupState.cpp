#include "StartupState.h"

#include <iostream>
#include <memory>

#include "GameManager.h"
#include "TitleState.h"

void StartupState::OnEnter(GameManager* manager)
{
	std::cout << "=== 起動 ===\n";
	std::cout << "ゲームを初期化しています...\n";
}

void StartupState::OnUpdate(GameManager* manager, float deltaTime)
{
	manager->ChangeState(std::make_unique<TitleState>());
}

void StartupState::OnExit(GameManager* manager)
{
}

const std::string StartupState::GetName() const
{
	return "StartupState";
}
