#include<iostream>
#include "GameManager.h"
#include "TitleState.h"

GameManager manager;

int main()
{
	// ゲームの初期状態を設定
	manager.ChangeState(std::make_unique<TitleState>());
	// ゲームループ
	while (1)
	{
	
		manager.Update(1.0);
	}
	return 0;
}