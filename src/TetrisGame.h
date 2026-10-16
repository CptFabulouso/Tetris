#pragma once

#include "TetrisBoard.h"
#include "NextTetrominoBoard.h"
#include "Tetromino.h"
#include "models.h"

class TetrisGame
{
private:
  TetrisBoard m_board;
  NextTetrominoBoard m_nextTetrominoBoard;
  std::array<Tetromino, 3> m_nextTetrominos;
  Tetromino m_activeTetromino;
  Tetromino m_shadowTetromino;
  float m_moveDuration = 0.6f;
  float m_timer = m_moveDuration;
  bool m_gameOver = false;

public:
  TetrisGame();
  explicit TetrisGame(const Tetromino &tetromino);

  void update(float dt);

  void applyAction(Action action);

  const TetrisBoard &getBoard() const
  {
    return m_board;
  }

  const NextTetrominoBoard &getNextTetrominoBoard() const
  {
    return m_nextTetrominoBoard;
  }

  const Tetromino &getActiveTetromino() const
  {
    return m_activeTetromino;
  }

  const Tetromino &getShadowTetromino() const
  {
    return m_shadowTetromino;
  }

  const std::array<Tetromino, 3> &getNextTetrominos() const
  {
    return m_nextTetrominos;
  }

  bool getIsGameOver() const
  {
    return m_gameOver;
  }

private:
  bool tryMove(Vec2i direction);
  void tryRotate(int direction);
  void calculateShadowTetromino();
  void placeTetromino(const Tetromino &tetromino);
  void spawnTetromino();
  static Tetromino getRandomTetromino();
};