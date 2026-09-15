#pragma once
class GameManager;

class Gamestate
{
public:
	virtual ~Gamestate() = default;
	virtual void OnEnter(GameManager* manager) = 0;
	virtual void OnUpdate(GameManager* manager) = 0;
	virtual void OnExit(GameManager*) {}
};
