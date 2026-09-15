#include "MainMenuState.h"

#include <conio.h>
#include <iostream>
#include <limits>
#include <memory>

#include "GameManager.h"
#include "InGameState.h"

void MainMenuState::OnEnter(GameManager* manager)
{
	std::cout << "\n=== メインメニュー ===\n";
	std::cout << "現在の抽選範囲: 1～" << manager->GetDrawRangeMaximum() << '\n';
	std::cout << "1: ゲーム開始\n";
	std::cout << "2: 抽選範囲を変更\n";
}

void MainMenuState::OnUpdate(GameManager* manager)
{
	const int selectedKey = _getch();

	if (selectedKey == '1')
	{
		manager->ChangeState(
			std::make_unique<InGameState>(manager->GetDrawRangeMaximum()));
		return;
	}

	if (selectedKey == '2')
	{
		std::cout << "\n抽選範囲の上限を入力してください: ";

		int maximum;
		if (std::cin >> maximum && manager->SetDrawRangeMaximum(maximum))
		{
			std::cout << "抽選範囲を1～" << maximum << "に変更しました。\n";
		}
		else
		{
			std::cin.clear();
			std::cout << "1以上の整数を入力してください。\n";
		}

		std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		std::cout << "1: ゲーム開始 / 2: 抽選範囲を変更\n";
	}
}
