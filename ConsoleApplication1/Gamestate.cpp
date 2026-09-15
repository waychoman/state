#include <memory>
#include <Windows.h>

#include "GameManager.h"
#include "StartupState.h"

int main()
{
	SetConsoleOutputCP(CP_UTF8);

	GameManager manager;
	manager.ChangeState(std::make_unique<StartupState>());

	// メインゲームループ
	while (true)
	{
		manager.Update();
	}
}
