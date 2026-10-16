#include "raylib.h"
#include <ctime>

#include "Player.h"
#include "TetrisBoard.h"
#include "TetrisGame.h"
#include "Tetromino.h"
#include "Renderer.h"

#include "imgui.h"
#include "imguiThemes.h"
#include "rlImGui.h"

int main()
{

	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Tetris");
	SetWindowMinSize(400, 200);

	srand(time(0));
	{
		// Game scope
		Renderer renderer;
		TetrisGame tetrisGame{};
		Player player;

		while (!WindowShouldClose())
		{
			BeginDrawing();
			ClearBackground(SKYBLUE);

			float dt = GetFrameTime();
			if (!tetrisGame.getIsGameOver())
			{
				Action action = player.getAction(dt);
				tetrisGame.applyAction(action);
			}
			tetrisGame.update(dt);

			renderer.render(tetrisGame);
			renderer.renderImGUI(tetrisGame);

			EndDrawing();
		}
	}

	CloseWindow();
	return 0;
}