#include "stdafx.h"
#include "Game.h"

Game::Game()
{
	Reset();
}

void Game::Reset()
{
	Console::SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	Console::CursorVisible(false);

	pauseMessage = "";
	lives = 2;

	Console::BackgroundColor(DarkGray);
	Console::Clear();

	paddle.width = 12;
	paddle.height = 2;
	paddle.x_position = 32;
	paddle.y_position = 30;

	ball.visage = 'O';
	ball.color = ConsoleColor::Cyan;
	ResetBall();

	// TODO #2 - Add this brick and 4 more bricks to the vector
	bricks.clear();

	// define brick spacing
	int brickWidth = 10;

	int brickHeight = 2;
	int spacing = 2;
	int numBricks = 5;
	int totalWidth = numBricks * brickWidth + (numBricks - 1) * spacing;
	int startX = (WINDOW_WIDTH - totalWidth) / 2;
	int brickY = 5;

	//add bricks
	for (int i = 0; i < numBricks; i++)
	{
		Box newBrick;
		newBrick.width = brickWidth;
		newBrick.height = brickHeight;
		newBrick.x_position = startX + i * (brickWidth + spacing);
		newBrick.y_position = brickY;
		newBrick.doubleThick = true;
		newBrick.color = ConsoleColor::DarkGreen;

		bricks.push_back(newBrick);
	}
}

void Game::ResetBall()
{
	ball.x_position = paddle.x_position + paddle.width / 2;
	ball.y_position = paddle.y_position - 1;
	ball.x_velocity = rand() % 2 ? 1 : -1;
	ball.y_velocity = -1;
	ball.moving = false;
}

bool Game::Update()
{
	if (GetAsyncKeyState(VK_ESCAPE) & 0x1)
		Reset();

	if (GetAsyncKeyState(VK_RIGHT) && paddle.x_position < WINDOW_WIDTH - paddle.width)
		paddle.x_position += 2;

	if (GetAsyncKeyState(VK_LEFT) && paddle.x_position > 0)
		paddle.x_position -= 2;

	if (GetAsyncKeyState(VK_SPACE) & 0x1)
	{
		if (!pauseMessage.empty()) 
		{
			pauseMessage = ""; 
			ball.moving = true;
		}
		else
		{
			ball.moving = !ball.moving; 
		}
	}

	if (GetAsyncKeyState('R') & 0x1)
		ResetBall();

	ball.Update();
	CheckCollision();
	return true;
}

//  All rendering should be done between the locks in this function
void Game::Render() const
{
	Console::Lock(true);
	Console::Clear();
	
	paddle.Draw();
	ball.Draw();

	// TODO #3 - Update render to render all bricks
	for (const auto& brick : bricks)
		brick.Draw();

	int livesX = WINDOW_WIDTH / 2 - 5; 
	int livesY = WINDOW_HEIGHT - 3;    
	Console::SetCursorPosition(livesX, livesY);
	Console::ForegroundColor(White);
	std::cout << "Lives: " << lives;

	if (!pauseMessage.empty())
	{
		Console::ForegroundColor(Black);
		int centerX = WINDOW_WIDTH / 2 - pauseMessage.length() / 2;
		int centerY = WINDOW_HEIGHT / 2;
		Console::SetCursorPosition(centerX, centerY);
		std::cout << pauseMessage;
	}

	Console::Lock(false);
}

void Game::CheckCollision()
{
	// TODO #4 - Update collision to check all bricks
	for (int i = 0; i < bricks.size(); i++)
	{

		if (bricks[i].Contains(ball.x_position + ball.x_velocity, ball.y_position + ball.y_velocity))
		{
			bricks[i].hitCount++;
			ball.y_velocity *= -1;

			// TODO #5 - If the ball hits the same brick 3 times (color == black), remove it from the vector
			if (bricks[i].hitCount < 3)
			{
				bricks[i].color = ConsoleColor(bricks[i].color - 1);
			}
			else
			{
				bricks.erase(bricks.begin() + i);
				i--;
			}
		}
	}

	// TODO #6 - If no bricks remain, pause ball and display victory text with R to reset
	if (bricks.empty())
	{
		PauseGame("You win! Press 'R' to play again.");
	}


	if (paddle.Contains(ball.x_position + ball.x_velocity, ball.y_velocity + ball.y_position))
	{
		ball.y_velocity *= -1;
	}

	// TODO #7 - If ball touches bottom of window, pause ball and display defeat text with R to reset

	//Make this 3 lives and remake a lose stat
	if (ball.y_position >= WINDOW_HEIGHT - 1)
	{
		
		if (lives > 0)
		{
			lives--;
			PauseGame("You lost a life! Press SPACE to continue.");
			ResetBall();
		}
		else
		{
			PauseGame("You lose. Press ESC to restart.");
			ball.moving = false;
		}
	}
}

void Game::PauseGame(const std::string& message)
{
	paused = true;
	pauseMessage = message;
	ball.moving = false;

}

