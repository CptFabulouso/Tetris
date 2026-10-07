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

void TetrisBoard::addOccupiedCells(std::vector<BoardCell> cells)
{
  m_occupiedCells.insert(m_occupiedCells.end(), cells.begin(), cells.end());
}

bool TetrisBoard::canPlace(Tetromino tetromino)
{
  std::vector<BoardCell> tetrominoCells = tetromino.getCells();

  for (BoardCell &tetrominoCell : tetrominoCells)
  {
    if (tetrominoCell.x < 0 || tetrominoCell.x > COLUMNS - 1 || tetrominoCell.y > ROWS - 1)
    {
      return false;
    }

    for (BoardCell &occupiedCell : m_occupiedCells)
    {
      if (tetrominoCell.y == occupiedCell.y & tetrominoCell.x == occupiedCell.x)
      {
        return false;
      }
    }
  }
  return true;
}
