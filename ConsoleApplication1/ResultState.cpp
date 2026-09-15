#include "ResultState.h"

#include <conio.h>
#include <iostream>
#include <memory>

#include "GameManager.h"
#include "MainMenuState.h"

ResultState::ResultState(int result, int drawCount)
	: result(result), drawCount(drawCount)
{
}

void ResultState::OnEnter(GameManager* manager)
{
	std::cout << "\n=== 結果 ===\n";
	std::cout << "当たりの数字は" << result << "でした。\n";
	std::cout << drawCount << "回目の抽選で1が出ました。\n";
	std::cout << "何かキーを押すとメインメニューへ戻ります。\n";
}

void ResultState::OnUpdate(GameManager* manager, float deltaTime)
{
	_getch();
	manager->ChangeState(std::make_unique<MainMenuState>());
}

void ResultState::OnExit(GameManager* manager)
{
}

const std::string ResultState::GetName() const
{
	return "ResultState";
}
