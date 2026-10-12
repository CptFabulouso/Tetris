#include "NextTetrominoBoard.h"

NextTetrominoBoard::NextTetrominoBoard()
{
}

void NextTetrominoBoard::setPosition(const Vector2 &newPosition)
{
  m_position = newPosition;
}

void NextTetrominoBoard::calculateSize(int screenWidth, int screenHeight)
{
  int availableWidth = screenWidth - m_position.x;
  int availableHeight = screenHeight - m_position.y;

  m_width = availableHeight * 0.2;
  m_height = m_width * 3;
}
