#include "raylib.h"
#include <iostream>
#include <vector>

const int ROWS = 20;
const int COLUMNS = 10;

// TODO: refactor to struct
struct GameData
{
};

int main()
{

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Tetris");
	SetWindowMinSize(400, 200);

	bool gameOver = false;

	while (!WindowShouldClose() && gameOver == false)
	{
		BeginDrawing();
		ClearBackground(SKYBLUE);

		screenHeight = GetScreenHeight();
		screenWidth = GetScreenWidth();

		const int tetrisPadding = screenHeight * 0.025;
		const float tetrisAspectRatio = 1.0f / 2.0f;
		const float tetrisLeft = tetrisPadding;
		const float tetrisTop = tetrisPadding;
		const float tetrisBottom = screenHeight - tetrisPadding;
		const float tetrisHeight = tetrisBottom - tetrisTop;
		const float tetrisWidth = tetrisHeight * tetrisAspectRatio;
		const float tetrisCellSize = tetrisHeight / ROWS;
		const float tetrisBorderWidth = tetrisWidth * 0.02;

		DrawRectangle(tetrisLeft - tetrisBorderWidth, tetrisTop - tetrisBorderWidth, tetrisWidth + 2 * tetrisBorderWidth, tetrisHeight + 2 * tetrisBorderWidth, DARKGRAY);
		DrawRectangle(tetrisLeft, tetrisTop, tetrisWidth, tetrisHeight, LIGHTGRAY);

		for (int row = 1; row < ROWS; row++)
		{
			DrawLineV(
					{tetrisLeft, tetrisTop + tetrisCellSize * row},
					{tetrisLeft + tetrisWidth, tetrisTop + tetrisCellSize * row},
					DARKGRAY);
		}
		for (int column = 1; column < COLUMNS; column++)
		{
			DrawLineV(
					{tetrisLeft + column * tetrisCellSize, tetrisTop},
					{tetrisLeft + column * tetrisCellSize, tetrisBottom},
					DARKGRAY);
		}

		EndDrawing();
	}

	CloseWindow();
	return 0;
}