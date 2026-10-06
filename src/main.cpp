#include "raylib.h"
#include <iostream>
#include <algorithm>
#include <vector>

#include "Player.h"
#include "TetrisBoard.h"
#include "TetrisGame.h"
#include "Tetromino.h"
#include "Renderer.h"

#include "imgui.h"
#include "imguiThemes.h"
#include "rlImGui.h"

const int ROWS = 20;
const int COLUMNS = 10;

int main()
{

	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Tetris");
	SetWindowMinSize(400, 200);

	Renderer renderer;
	TetrisGame tetrisGame;
	Player player;

	while (!WindowShouldClose() && tetrisGame.getIsGameOver() == false)
	{
		BeginDrawing();
		ClearBackground(SKYBLUE);

		Action action = player.getAction();
		tetrisGame.applyAction(action);
		tetrisGame.update(GetFrameTime());

		renderer.render(tetrisGame);
		renderer.renderImGUI();

		EndDrawing();
	}

	CloseWindow();
	return 0;
}