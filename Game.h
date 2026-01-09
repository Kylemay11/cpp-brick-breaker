#pragma once
#include "Box.h"
#include "Ball.h"
#include "vector"

class Game
{
	Ball ball;
	Box paddle;


	// TODO #1 - Instead of storing 1 brick, store a vector of bricks (by value)
	std::vector<Box> bricks;

	bool paused = false;
	std::string pauseMessage = "";

	int lives = 2;

public:
	Game();
	bool Update();
	void Render() const;
	void Reset();
	void ResetBall();
	void CheckCollision();
	void PauseGame(const std::string& message);
	
};