#include "ResultState.h"

#include <conio.h>
#include <iostream>
#include <memory>

#include "GameManager.h"
#include "MainMenuState.h"

ResultState::ResultState(int drawCount)
	: drawCount(drawCount)
{
}

void ResultState::OnEnter(GameManager*)
{
	std::cout << "\n=== 結果 ===\n";
	std::cout << "当たりの数字は1でした。\n";
	std::cout << drawCount << "回目の抽選で1が出ました。\n";
	std::cout << "何かキーを押すとメインメニューへ戻ります。\n";
}

void ResultState::OnUpdate(GameManager* manager)
{
	_getch();
	manager->ChangeState(std::make_unique<MainMenuState>());
}
