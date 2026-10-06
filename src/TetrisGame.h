#pragma once

#include "TetrisBoard.h"
#include "Tetromino.h"
#include "models.h"

class TetrisGame
{
private:
  TetrisBoard m_board;
  Tetromino m_activeTetromino;
  float m_moveDuration = 0.6f;
  float m_timer = m_moveDuration;
  bool m_gameOver = false;

public:
  TetrisGame();

  void update(float dt);

  void applyAction(Action action);

  const TetrisBoard &getBoard() const
  {
    return m_board;
  }

  const Tetromino &getActiveTetromino() const
  {
    return m_activeTetromino;
  }

  const bool getIsGameOver() const
  {
    return m_gameOver;
  }

private:
  void tryMove(Vec2i direction);
  void tryRotate(int direction);
};