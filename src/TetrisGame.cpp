#include "TetrisGame.h"
#include "raylib.h"

TetrisGame::TetrisGame() : m_board{0, 0}, m_activeTetromino(&TetrominoModels::IShape)
{
}

void TetrisGame::update(float dt)
{
  int screenHeight = GetScreenHeight();
  int screenWidth = GetScreenWidth();

  m_board.calculateSize(screenWidth, screenHeight);

  m_timer -= dt;
  if (m_timer < 0)
  {
    m_timer += m_moveDuration;
    // TODO: move down
  }
}

void TetrisGame::applyAction(Action action)
{
  switch (action)
  {
  case MOVE_LEFT:
    tryMove({-1, 0});
    break;
  case MOVE_RIGHT:
    tryMove({1, 0});
    break;
  case ROTATE:
    tryRotate(1);
  default:
    break;
  }
}

void TetrisGame::tryMove(Vec2i direction)
{
  Tetromino canditate = m_activeTetromino;

  canditate.move(direction);
  if (m_board.canPlace(canditate))
  {
    m_activeTetromino.setPosition(canditate.getPosition());
  }
}

void TetrisGame::tryRotate(int direction)
{
  Tetromino canditate = m_activeTetromino;
  canditate.rotate(direction);
  /* try wall kick to the right */
  for (int kick = 0; kick <= 2; kick++)
  {
    canditate.move({1, 0});
    if (m_board.canPlace(canditate))
    {
      m_activeTetromino.setRotation(canditate.getRotation());
      m_activeTetromino.setPosition(canditate.getPosition());
      break;
    }
  }

  /*  try wall kick to the left */
  // reset position
  canditate.setPosition(m_activeTetromino.getPosition());
  for (int kick = 0; kick <= 2; kick++)
  {
    canditate.move({-1, 0});
    if (m_board.canPlace(canditate))
    {
      m_activeTetromino.setRotation(canditate.getRotation());
      m_activeTetromino.setPosition(canditate.getPosition());
      break;
    }
  }
}