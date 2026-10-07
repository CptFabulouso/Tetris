#pragma once

#include "TetrisBoard.h"
#include "Tetromino.h"
#include "models.h"

class TetrisGame
{
private:
  TetrisBoard m_board;
  Tetromino m_activeTetromino;
  Tetromino m_shadowTetromino;
  float m_moveDuration = 0.6f;
  float m_timer = m_moveDuration;
  bool m_gameOver = false;

public:
  TetrisGame(const ShapeModel *model);

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
  const Tetromino &getShadowTetromino() const
  {
    return m_shadowTetromino;
  }

  const bool getIsGameOver() const
  {
    return m_gameOver;
  }

private:
  bool tryMove(Vec2i direction);
  void tryRotate(int direction);
  void calculateShadowTetromino();
  void placeTetromino(Tetromino &tetromino);
  const ShapeModel *getRandomTetrominoShape();
};