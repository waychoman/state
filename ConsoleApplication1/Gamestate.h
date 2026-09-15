#pragma once
#include <string>
class GameManager;
class Gamestate
{
public:
	virtual ~Gamestate() = default;
	virtual void OnEnter(GameManager* manager) = 0;
	virtual void OnUpdate(GameManager* manager, float deltaTime) = 0;
	virtual void OnExit(GameManager* manager) = 0;
	virtual const std::string GetName() const = 0;
};