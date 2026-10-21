#include "TetrisBoard.h"

TetrisBoard::TetrisBoard(int screenWidth, int screenHeight)
{
  calculateSize(screenWidth, screenHeight);
}

void TetrisBoard::calculateSize(int screenWidth, int screenHeight)
{
  const int tetrisPadding = screenHeight * 0.025;

  float draftHeight = (screenHeight - (tetrisPadding) * 2);

  m_cellSize = draftHeight / ROWS;
  m_height = m_cellSize * ROWS;
  m_width = m_cellSize * COLUMNS;

  m_position.x = (screenHeight - m_height) / 2;
  m_position.y = m_position.x;
}

void TetrisBoard::addOccupiedCells(const std::vector<BoardCell> &cells)
{
  for (const BoardCell &cell : cells)
  {
    if (cell.x < 0 || cell.x > COLUMNS - 1 || cell.y > ROWS - 1 || cell.y < 0)
    {
      continue;
    }
    m_grid[cell.x][cell.y] = cell;
  }
}

bool TetrisBoard::canPlace(const Tetromino &tetromino) const
{
  const std::vector<BoardCell> &tetrominoCells = tetromino.cells();

  for (const BoardCell &tetrominoCell : tetrominoCells)
  {
    if (tetrominoCell.y < 0)
    {
      continue;
    }
    if (tetrominoCell.x < 0 || tetrominoCell.x > COLUMNS - 1 || tetrominoCell.y > ROWS - 1)
    {
      return false;
    }
    if (m_grid[tetrominoCell.x][tetrominoCell.y].has_value())
    {
      return false;
    }
  }
  return true;
}

Tetromino TetrisBoard::dropped(Tetromino tetromino) const
{
  while (canPlace(tetromino))
  {
    tetromino.move({0, 1});
  }
  // move one cell up
  tetromino.move({0, -1});
  return tetromino;
}

int TetrisBoard::collapseFullRows()
{
  int moveRowBy = 0;

  /* Check rows from bottom up. Once we find full row(s),
    we move all subsequent rows down by that amount
   */
  for (int y = ROWS - 1; y >= 0; y--)
  {
    bool rowFilled = true;
    bool rowHasFilledCell = false;
    for (int x = 0; x < COLUMNS; x++)
    {
      if (!m_grid[x][y].has_value())
      {
        rowFilled = false;
      }
      else
      {
        rowHasFilledCell = true;
      }
      if (moveRowBy != 0)
      {
        m_grid[x][y + moveRowBy] = m_grid[x][y];
        m_grid[x][y] = std::nullopt;
      }
    }
    if (rowFilled)
    {
      moveRowBy++;
    }
    if (!rowHasFilledCell)
    {
      // when there is no filled cell in a row, we can stop checking further
      // no float rows are allowed
      break;
    }
  }

  return moveRowBy;
}