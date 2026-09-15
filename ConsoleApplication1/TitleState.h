#pragma once
#include "Gamestate.h"
#include "GameManager.h"


class TitleState : public Gamestate
{
public:
	void onEnter(GameManager* manager)
	{
		std::cout << "タイトル画面" << std::endl;
	};
	void Onupdate(GameManager* manager, float deltaTime)
	{
	}
	void OnExit(GameManager* manager)
	{
		std::cout << "タイトル画面終了" << std::endl;
	};

const std::string GetName() const
	{
		return "TitleState";
}

};