#include "InGameState.h"

#include <conio.h>
#include <iostream>
#include <memory>
#include <random>

#include "GameManager.h"
#include "ResultState.h"

InGameState::InGameState()
	: randomEngine(std::random_device{}()), distribution(1, 10), drawCount(0)
{
}

void InGameState::OnEnter(GameManager* manager)
{
	std::cout << "\n=== ゲーム画面 ===\n";
	std::cout << "Enterキーを押すたびに1～10の数字を抽選します。\n";
}

void InGameState::OnUpdate(GameManager* manager, float deltaTime)
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
		manager->ChangeState(std::make_unique<ResultState>(result, drawCount));
	}
}

void InGameState::OnExit(GameManager* manager)
{
}

const std::string InGameState::GetName() const
{
	return "InGameState";
}
