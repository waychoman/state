#include "StartupState.h"

#include <iostream>
#include <memory>

#include "GameManager.h"
#include "TitleState.h"

void StartupState::OnEnter(GameManager*)
{
	std::cout << "=== 起動 ===\n";
	std::cout << "ゲームを初期化しています...\n";
}

void StartupState::OnUpdate(GameManager* manager)
{
	manager->ChangeState(std::make_unique<TitleState>());
}
