#pragma once
class GameStateInterface
{
public:
	GameStateInterface() {}
	virtual void update() {}
	virtual bool gameOver() {}
	virtual ~GameStateInterface() {}
};

