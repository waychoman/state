#include "InGameState.h"

#include <conio.h>
#include <iostream>
#include <memory>
#include <random>

#include "GameManager.h"
#include "ResultState.h"

InGameState::InGameState(int drawRangeMaximum)
	: randomEngine(std::random_device{}()),
	  distribution(1, drawRangeMaximum),
	  drawCount(0)
{
}

void InGameState::OnEnter(GameManager* manager)
{
	std::cout << "\n=== ゲーム画面 ===\n";
	std::cout << "Enterキーを押すたびに1～"
		<< manager->GetDrawRangeMaximum() << "の数字を抽選します。\n";
}

void InGameState::OnUpdate(GameManager* manager)
{
	if (_getch() != '\r')
	{
		return;
	}

	++drawCount;
	const int result = distribution(randomEngine);
	std::cout << drawCount << "回目の抽選結果: " << result << '\n';

	if (result == 1)
	{
		manager->ChangeState(std::make_unique<ResultState>(drawCount));
	}
}
