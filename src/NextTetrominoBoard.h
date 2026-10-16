#pragma once

#include "raylib.h"

class NextTetrominoBoard
{
private:
  Vector2 m_position = {0, 0};
  int m_width = 0;
  int m_height = 0;
  int m_cellSize = 0;

public:
  NextTetrominoBoard();

  void setPosition(const Vector2 &newPosition);
  void calculateSize(int screenWidth, int screenHeight);

  const Vector2 &getPosition() const
  {
    return m_position;
  }

  int getHeight() const
  {
    return m_height;
  }

  int getWidth() const
  {
    return m_width;
  }

  int getCellSize() const
  {
    return m_cellSize;
  }
};