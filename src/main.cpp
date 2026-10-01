#include "raylib.h"
#include <iostream>
#include <algorithm>
#include <vector>

#include "Player.h"
#include "TetrisBoard.h"

const int ROWS = 20;
const int COLUMNS = 10;

// TODO: refactor to struct
struct GameData
{
};

struct Cell
{
	int x = 0;
	int y = 0;
};

struct Shape
{
	std::vector<Cell> cells;
	int size = 0;
	Vec2i shapeOffset;

	Shape() {}

	Shape(const std::vector<Cell> &cls) : cells(cls)
	{
		int width = cells[0].x;
		int height = cells[0].y;
		shapeOffset.x = cells[0].x;
		shapeOffset.y = cells[0].y;

		for (Cell &cell : cells)
		{
			shapeOffset.x = std::min(cell.x, shapeOffset.x);
			shapeOffset.y = std::min(cell.y, shapeOffset.y);
			width = std::max(cell.x, width);
			height = std::max(cell.y, height);
		}

		size = std::max(width, height);
	}

	void moveLeft(int moveCount = 1)
	{
		for (Cell &cell : cells)
		{
			cell.x -= moveCount;
		}
	}

	void moveRight(int moveCount = 1)
	{
		for (Cell &cell : cells)
		{
			cell.x += moveCount;
		}
	}

	void moveDown()
	{
		for (Cell &cell : cells)
		{
			cell.y += 1;
		}
	}

	void moveUp()
	{
		for (Cell &cell : cells)
		{
			cell.y -= 1;
		}
	}

	void rotate()
	{
		if (cells.empty())
		{
			return;
		}
		int leftMostX = cells[0].x;
		// int rightMostX = cells[0].x;
		int topMostY = cells[0].y;
		// int bottomMostY = cells[0].y;
		for (Cell &cell : cells)
		{
			leftMostX = std::min(cell.x, leftMostX);
			// 	rightMostX = std::max(cell.x, rightMostX);
			topMostY = std::min(cell.y, topMostY);
			// 	bottomMostY = std::max(cell.y, bottomMostY);
		}
		// int width = rightMostX - leftMostX;
		// int height = bottomMostY - topMostY;
		// int heightAdjust = height - width;

		int nextOffsetX = 0;
		int nextOffsetY = 0;
		for (Cell &cell : cells)
		{
			// move shape to 0,0
			cell.x += -leftMostX - size / 2 + shapeOffset.x;
			cell.y += -topMostY - size / 2 + shapeOffset.y;

			int newX = -cell.y;
			int newY = cell.x;
			// rotate
			cell.x = newX;
			cell.y = newY;
			// move to origin place and adjust position to keep shape at same height
			cell.x += leftMostX + size / 2 - shapeOffset.x;
			cell.y += topMostY + size / 2 - shapeOffset.y;
		}
		int tempX = shapeOffset.x;
		shapeOffset.x = shapeOffset.y;
		shapeOffset.y = tempX;
	}
};

ShapeModel creteJShapeModel()
{

	std::vector<Vec2i> shapeCells;
	shapeCells.push_back({0, 0});
	shapeCells.push_back({0, 1});
	shapeCells.push_back({1, 1});
	shapeCells.push_back({2, 1});

	return ShapeModel(shapeCells);
}

ShapeModel creteLShapeModel()
{

	std::vector<Vec2i> shapeCells;
	shapeCells.push_back({0, 1});
	shapeCells.push_back({1, 1});
	shapeCells.push_back({2, 1});
	shapeCells.push_back({2, 0});

	return ShapeModel(shapeCells);
}

ShapeModel creteIShapeModel()
{

	std::vector<Vec2i> shapeCells;
	shapeCells.push_back({1, 0});
	shapeCells.push_back({1, 1});
	shapeCells.push_back({1, 2});
	shapeCells.push_back({1, 3});

	return ShapeModel(shapeCells);
}

ShapeModel creteOShapeModel()
{

	std::vector<Vec2i> shapeCells;
	shapeCells.push_back({0, 0});
	shapeCells.push_back({1, 0});
	shapeCells.push_back({0, 1});
	shapeCells.push_back({1, 1});

	return ShapeModel(shapeCells);
}

ShapeModel creteSShapeModel()
{

	std::vector<Vec2i> shapeCells;
	shapeCells.push_back({0, 1});
	shapeCells.push_back({1, 1});
	shapeCells.push_back({1, 0});
	shapeCells.push_back({2, 0});

	return ShapeModel(shapeCells);
}

ShapeModel creteTShapeModel()
{

	std::vector<Vec2i> shapeCells;
	shapeCells.push_back({0, 1});
	shapeCells.push_back({1, 1});
	shapeCells.push_back({1, 0});
	shapeCells.push_back({2, 1});

	return ShapeModel(shapeCells);
}

ShapeModel creteZShapeModel()
{

	std::vector<Vec2i> shapeCells;
	shapeCells.push_back({0, 0});
	shapeCells.push_back({1, 0});
	shapeCells.push_back({1, 1});
	shapeCells.push_back({2, 1});

	return ShapeModel(shapeCells);
}

void drawTetrisBoardBackground(TetrisBoard &tetrisBoard)
{
	Vector2 position = tetrisBoard.getPosition();
	int width = tetrisBoard.getWidth();
	int height = tetrisBoard.getHeight();
	int borderWidth = 6;
	DrawRectangle(position.x - borderWidth, position.y - borderWidth, width + 2 * borderWidth, height + 2 * borderWidth, DARKGRAY);
	DrawRectangle(position.x, position.y, width, height, LIGHTGRAY);
}

void drawTetrisCells(TetrisBoard &tetrisBoard, Player &player)
{
	Vector2 tetrisPosition = tetrisBoard.getPosition();
	int tetrisCellSize = tetrisBoard.getCellSize();
	std::vector<BoardCell> tetrisCells = tetrisBoard.getOccupiedCells();

	for (BoardCell &cell : tetrisCells)
	{
		DrawRectangle(tetrisPosition.x + cell.x * tetrisCellSize, tetrisPosition.y + cell.y * tetrisCellSize, tetrisCellSize, tetrisCellSize, GREEN);
	}

	std::vector<BoardCell> playerCells = player.getCells();
	ShapeModel model = player.getModel();
	Vec2i position = player.getPosition();

	DrawRectangle(tetrisPosition.x + position.x * tetrisCellSize, tetrisPosition.y + position.y * tetrisCellSize, tetrisCellSize * model.getSize(), tetrisCellSize * model.getSize(), PURPLE);
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

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Tetris");
	SetWindowMinSize(400, 200);

	bool gameOver = false;

	TetrisBoard tetrisBoard{screenWidth, screenHeight};

	Player player;
	player.attachModel(creteZShapeModel());

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

		drawTetrisCells(tetrisBoard, player);

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

		EndDrawing();
	}

	CloseWindow();
	return 0;
}