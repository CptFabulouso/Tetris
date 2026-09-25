#include "raylib.h"
#include <iostream>
#include <algorithm>
#include <vector>

const int ROWS = 20;
const int COLUMNS = 10;

// TODO: refactor to struct
struct GameData
{
};

struct Shape
{
	int width = 0;
	int height = 0;
	std::vector<std::vector<int>> points;
	int x = 0;
	int y = 0;

	Shape() {}

	Shape(const std::vector<std::vector<int>> &pts) : points(pts)
	{
		width = points.size();
		height = points[0].size();
	}

	void rotate()
	{
		std::vector<std::vector<int>> newPoints;

		for (int y = height - 1; y >= 0; y--)
		{
			std::vector<int> columnValues;
			for (int x = 0; x < width; x++)
			{
				columnValues.push_back(points[x][y]);
			}
			newPoints.push_back(columnValues);
		}
		y = y + (height - width);
		int tempHeight = height;
		height = width;
		width = tempHeight;
		points = newPoints;
	}
};

int main()
{

	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	int screenWidth = 800;
	int screenHeight = 450;

	InitWindow(screenWidth, screenHeight, "Tetris");
	SetWindowMinSize(400, 200);

	bool gameOver = false;

	std::vector<Shape> shapes;

	std::vector<std::vector<int>> lShapePoints;
	lShapePoints.push_back({0, 0, 0, 1});
	lShapePoints.push_back({1, 1, 1, 1});
	shapes.push_back(lShapePoints);

	const float moveTimeDuration = 0.6;
	float timer = moveTimeDuration;

	Shape *latestShape;

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

		for (int ty = 0; ty < ROWS; ty++)
		{
			for (int tx = 0; tx < COLUMNS; tx++)
			{
				for (auto shape : shapes)
				{
					int shapeX = tx - shape.x;
					int shapeY = ty - shape.y;
					if (shapeX >= 0 && shapeX < shape.width && shapeY >= 0 && shapeY < shape.height)
					{
						int shapeValue = shape.points[shapeX][shapeY];
						if (shapeValue > 0)
						{
							DrawRectangle(tetrisLeft + tx * tetrisCellSize, tetrisTop + ty * tetrisCellSize, tetrisCellSize, tetrisCellSize, GREEN);
						}
					}
				}
			}
		}

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

		if (!shapes.empty())
		{
			latestShape = &shapes.back();
		}

		if (latestShape)
		{
			if (IsKeyPressed(KEY_LEFT))
			{
				latestShape->x = std::max(latestShape->x - 1, 0);
			}
			if (IsKeyPressed(KEY_RIGHT))
			{
				latestShape->x = std::min(latestShape->x + 1, COLUMNS - latestShape->width);
			}
			if (IsKeyPressed(KEY_UP))
			{
				latestShape->rotate();
				if (latestShape->x + latestShape->width > COLUMNS)
				{
					latestShape->x = COLUMNS - latestShape->width;
				}
			}

			timer -= GetFrameTime();
			if (timer < 0)
			{
				timer += moveTimeDuration;
				latestShape->y += 1;
				if (latestShape->y + latestShape->height > ROWS)
				{
					latestShape->y = ROWS - latestShape->height;

					std::vector<std::vector<int>> lShapePoints;
					lShapePoints.push_back({0, 0, 0, 1});
					lShapePoints.push_back({1, 1, 1, 1});
					shapes.push_back(lShapePoints);
				}
			}
		}

		EndDrawing();
	}

	CloseWindow();
	return 0;
}