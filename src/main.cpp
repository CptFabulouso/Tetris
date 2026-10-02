#include "raylib.h"
#include <iostream>
#include <algorithm>
#include <vector>

#include "Player.h"
#include "TetrisBoard.h"

#include "imgui.h"
#include "imguiThemes.h"
#include "rlImGui.h"

const int ROWS = 20;
const int COLUMNS = 10;

// TODO: refactor to struct
struct GameData
{
};

void drawTetrisBoardBackground(TetrisBoard &tetrisBoard)
{
	Vector2 position = tetrisBoard.getPosition();
	int width = tetrisBoard.getWidth();
	int height = tetrisBoard.getHeight();
	int borderWidth = 6;
	DrawRectangle(position.x - borderWidth, position.y - borderWidth, width + 2 * borderWidth, height + 2 * borderWidth, DARKGRAY);
	DrawRectangle(position.x, position.y, width, height, LIGHTGRAY);
}

void drawTetrisCells(TetrisBoard &tetrisBoard, Player &player, bool showShapeRect)
{
	Vector2 tetrisPosition = tetrisBoard.getPosition();
	int tetrisCellSize = tetrisBoard.getCellSize();
	std::vector<BoardCell> tetrisCells = tetrisBoard.getOccupiedCells();

	for (BoardCell &cell : tetrisCells)
	{
		DrawRectangle(tetrisPosition.x + cell.x * tetrisCellSize, tetrisPosition.y + cell.y * tetrisCellSize, tetrisCellSize, tetrisCellSize, GREEN);
	}

	std::vector<BoardCell> playerCells = player.getCells();
	const ShapeModel *model = player.getModel();
	Vec2i position = player.getPosition();

	if (showShapeRect)
	{
		DrawRectangle(tetrisPosition.x + position.x * tetrisCellSize, tetrisPosition.y + position.y * tetrisCellSize, tetrisCellSize * model->getSize(), tetrisCellSize * model->getSize(), PURPLE);
	}
	for (BoardCell &cell : playerCells)
	{
		DrawRectangle(tetrisPosition.x + cell.x * tetrisCellSize, tetrisPosition.y + cell.y * tetrisCellSize, tetrisCellSize, tetrisCellSize, GREEN);
	}
}

void drawTetrisBoardGrid(TetrisBoard &tetrisBoard)
{
	Vector2 position = tetrisBoard.getPosition();
	int cellSize = tetrisBoard.getCellSize();
	int width = tetrisBoard.getWidth();
	int height = tetrisBoard.getHeight();
	int borderWidth = 5;

	for (int row = 1; row < ROWS; row++)
	{
		DrawLineV(
				{position.x, position.y + cellSize * row},
				{position.x + width, position.y + cellSize * row},
				DARKGRAY);
	}
	for (int column = 1; column < COLUMNS; column++)
	{
		DrawLineV(
				{position.x + column * cellSize, position.y},
				{position.x + column * cellSize, position.y + height},
				DARKGRAY);
	}
}

int main()
{

	SetConfigFlags(FLAG_MSAA_4X_HINT | FLAG_VSYNC_HINT | FLAG_WINDOW_RESIZABLE);
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Tetris");
	SetWindowMinSize(400, 200);

#pragma region imgui
	rlImGuiSetup(true);

	// you can use whatever imgui theme you like!
	imguiThemes::green();

	ImGuiIO &io = ImGui::GetIO();
	(void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;			// Enable Docking
	io.FontGlobalScale = 1;

	ImGuiStyle &style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.Colors[ImGuiCol_WindowBg].w = 0.5f;
	}

#pragma endregion

	bool gameOver = false;
	bool showShapeRect = false;

	TetrisBoard tetrisBoard{screenWidth, screenHeight};

	Player player;
	player.attachModel(&ShapeModels::JShape);

	const float moveTimeDuration = 0.6;
	float timer = moveTimeDuration;

	while (!WindowShouldClose() && gameOver == false)
	{
		BeginDrawing();
		ClearBackground(SKYBLUE);

		screenHeight = GetScreenHeight();
		screenWidth = GetScreenWidth();

		tetrisBoard.calculateSize(screenWidth, screenHeight);

		drawTetrisBoardBackground(tetrisBoard);

		drawTetrisCells(tetrisBoard, player, showShapeRect);

		drawTetrisBoardGrid(tetrisBoard);

		if (IsKeyPressed(KEY_LEFT))
		{
			player.move({-1, 0});

			// for (Cell &cell : latestShape->cells)
			// {
			// 	if (cell.x < 0)
			// 	{
			// 		latestShape->moveRight();
			// 		break;
			// 	}
			// }
		}

		if (IsKeyPressed(KEY_RIGHT))
		{
			player.move({1, 0});

			// for (Cell &cell : latestShape->cells)
			// {
			// 	if (cell.x > COLUMNS - 1)
			// 	{
			// 		latestShape->moveLeft();
			// 		break;
			// 	}
			// }
		}
		if (IsKeyPressed(KEY_UP))
		{
			player.rotate();

			// for (Cell &cell : latestShape->cells)
			// {
			// 	if (cell.x > COLUMNS - 1)
			// 	{
			// 		latestShape->moveLeft(cell.x - COLUMNS + 1);
			// 		break;
			// 	}
			// }
		}

		if (IsKeyPressed(KEY_DOWN))
		{
			player.move({0, 1});
		}

		timer -= GetFrameTime();
		if (timer < 0)
		{
			timer += moveTimeDuration;
		}

		// bool hit = false;
		// for (Cell &cell : latestShape->cells)
		// {
		// 	if (cell.y > ROWS - 1)
		// 	{
		// 		latestShape->moveUp();
		// 		hit = true;
		// 		break;
		// 	}
		// 	int shapesCount = shapes.size();
		// 	for (int i = 0; i < shapesCount - 1; i++)
		// 	{
		// 		for (Cell &otherCell : shapes[i].cells)
		// 		{
		// 			// TODO: check and adjust for horizontal collision
		// 			if (cell.y == otherCell.y & cell.x == otherCell.x)
		// 			{
		// 				latestShape->moveUp();
		// 				hit = true;
		// 			}
		// 		}
		// 	}
		// }

		// if (hit)
		// {
		// 	// TODO: check current shape is above top
		// 	shapes.push_back(createLShape());
		// }
#pragma region imgui
		rlImGuiBegin();

		ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
		ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
		ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
		ImGui::PopStyleColor(2);
#pragma endregion

		ImGui::Begin("Dev");

		ImGui::Checkbox("Show shape rect", &showShapeRect);

		ImGui::End();

#pragma region imgui
		rlImGuiEnd();

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
		}
#pragma endregion

		EndDrawing();
	}

	CloseWindow();
	return 0;
}