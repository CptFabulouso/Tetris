#pragma once

#include "models.h"
#include "TetrisBoard.h"
#include "NextTetrominoBoard.h"
#include "Tetromino.h"

class Player
{
private:
  static constexpr float ACTION_TIMEOUT = 0.1f;
  Action m_lastAction = Action::None;
  float m_actionTimeout = ACTION_TIMEOUT;

  // new
  // TetrisBoard m_board;
  // std::array<Tetromino, 3> m_nextTetrominos;
  // Tetromino m_activeTetromino;
  // float m_gravityTimer = 0;

public:
  Player() = default;

  Action getAction(float dt);

  // new
  // void update(float dt);

private:
  Action getNextAction(float dt);
};