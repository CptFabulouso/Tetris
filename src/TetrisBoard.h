#pragma once

#include "raylib.h"
#include <vector>
#include "models.h"

class TetrisBoard
{
private:
  int m_width = 0;
  int m_height = 0;
  Vector2 m_position = {0, 0};
  int m_cellSize = 0;
  std::vector<BoardCell> m_occupiedCells;

public:
  TetrisBoard(int screenWidth, int screenHeight)
  {
    calculateSize(screenWidth, screenHeight);
  }

  void calculateSize(int screenWidth, int screenHeight)
  {
    const int tetrisPadding = screenHeight * 0.025;

    float draftHeight = (screenHeight - (tetrisPadding) * 2);

    m_cellSize = draftHeight / ROWS;
    m_height = m_cellSize * ROWS;
    m_width = m_cellSize * COLUMNS;

    m_position.x = (screenHeight - m_height) / 2;
    m_position.y = m_position.x;
  }

  void addOccupiedCells(std::vector<BoardCell> cells)
  {
    m_occupiedCells.insert(m_occupiedCells.end(), cells.begin(), cells.end());
  }

  const Vector2 &getPosition() const
  {
    return m_position;
  }

  const std::vector<BoardCell> &getOccupiedCells() const
  {
    return m_occupiedCells;
  }

  inline const int getHeight() const
  {
    return m_height;
  }

  inline const int getWidth() const
  {
    return m_width;
  }

  inline const int getCellSize() const
  {
    return m_cellSize;
  }

public:
  static const int ROWS = 20;
  static const int COLUMNS = 10;
};