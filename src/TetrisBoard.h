#pragma once

#include "Tetromino.h"
#include "raylib.h"
#include <vector>
#include "models.h"

class TetrisBoard
{
public:
  static const int ROWS = 20;
  static const int COLUMNS = 10;

  template <typename T>
  using MultiDimArray = std::array<
      std::array<std::optional<T>, ROWS>,
      COLUMNS>;
  using TetrisBoardGrid = MultiDimArray<BoardCell>;

private:
  Vector2 m_position = {0, 0};
  // std::vector<BoardCell> m_occupiedCells;
  // int m_cells[COLUMNS][ROWS];
  TetrisBoardGrid m_grid;
  int m_cellSize = 0;
  int m_width = 0;
  int m_height = 0;

public:
  TetrisBoard(int screenWidth, int screenHeight);

  void calculateSize(int screenWidth, int screenHeight);
  void addOccupiedCells(std::vector<BoardCell> cells);
  bool canPlace(Tetromino tetromino);
  int collapseFullRows();

  const Vector2 &getPosition() const
  {
    return m_position;
  }

  // const std::vector<BoardCell> &getOccupiedCells() const
  // {
  //   return m_occupiedCells;
  // }

  const TetrisBoardGrid &getGrid() const
  {
    return m_grid;
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
};