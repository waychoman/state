#include <iostream>
#include <memory>
#include <Windows.h>

#include "GameManager.h"
#include "StartupState.h"

GameManager manager;

int main()
{
	SetConsoleOutputCP(CP_UTF8);

	manager.ChangeState(std::make_unique<StartupState>());

	// メインゲームループ
	while (true)
	{
		manager.Update(1.0f);
	}

	return 0;
}
