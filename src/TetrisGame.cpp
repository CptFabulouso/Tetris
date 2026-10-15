#include "TetrisGame.h"
#include "raylib.h"

TetrisGame::TetrisGame(const Tetromino &tetromino) : m_board{0, 0},
                                                     m_activeTetromino(tetromino),
                                                     m_shadowTetromino(tetromino),
                                                     m_nextTetrominos{
                                                         getRandomTetromino(),
                                                         getRandomTetromino(),
                                                         getRandomTetromino(),
                                                     }
{
}

TetrisGame::TetrisGame() : TetrisGame(getRandomTetromino())
{
}

void TetrisGame::update(float dt)
{
  int screenHeight = GetScreenHeight();
  int screenWidth = GetScreenWidth();

  m_board.calculateSize(screenWidth, screenHeight);
  int boardWidth = m_board.getWidth();
  Vector2 boardPosition = m_board.getPosition();
  m_nextTetrominoBoard.setPosition({boardPosition.x + boardWidth + 20, boardPosition.y});
  m_nextTetrominoBoard.calculateSize(screenWidth, screenHeight);

  m_timer -= dt;
  if (m_timer < 0)
  {
    m_timer = m_moveDuration;
    // m_activeTetromino.move({0, 1});
    if (!m_board.canPlace(m_activeTetromino))
    {
      m_activeTetromino.move({0, -1});
      placeTetromino(m_activeTetromino);
    }
  }

  calculateShadowTetromino();
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
  case MOVE_DOWN:
  {
    if (!tryMove({0, 1}))
    {
      placeTetromino(m_activeTetromino);
    }
    break;
  }
  case INSTANT_DOWN:
    placeTetromino(m_shadowTetromino);
    break;
  case ROTATE:
    tryRotate(1);
    break;
  default:
    break;
  }
}

bool TetrisGame::tryMove(Vec2i direction)
{
  Tetromino canditate = m_activeTetromino;

  canditate.move(direction);
  if (m_board.canPlace(canditate))
  {
    m_activeTetromino.setPosition(canditate.getPosition());
    return true;
  }
  return false;
}

void TetrisGame::tryRotate(int direction)
{
  Tetromino canditate = m_activeTetromino;
  canditate.rotate(direction);

  if (m_board.canPlace(canditate))
  {
    m_activeTetromino.setRotation(canditate.getRotation());
    m_activeTetromino.setPosition(canditate.getPosition());
    return;
  }

  /* try wall kick to the right */
  for (int kick = 0; kick <= 2; kick++)
  {
    canditate.move({1, 0});
    if (m_board.canPlace(canditate))
    {
      m_activeTetromino.setRotation(canditate.getRotation());
      m_activeTetromino.setPosition(canditate.getPosition());
      return;
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
      return;
    }
  }
}

void TetrisGame::calculateShadowTetromino()
{
  m_shadowTetromino.setPosition(m_activeTetromino.getPosition());
  m_shadowTetromino.setRotation(m_activeTetromino.getRotation());

  while (m_board.canPlace(m_shadowTetromino))
  {
    m_shadowTetromino.move({0, 1});
  }
  // move one cell up
  m_shadowTetromino.move({0, -1});
}

void TetrisGame::placeTetromino(Tetromino &tetromino)
{
  m_board.addOccupiedCells(tetromino.getCells());
  spawnTetromino();

  int collapsedRows = m_board.collapseFullRows();
}

void TetrisGame::spawnTetromino()
{
  Tetromino nextTetromino = m_nextTetrominos[0];

  m_activeTetromino = m_nextTetrominos[0];
  m_shadowTetromino = m_nextTetrominos[0];

  for (int i = 0; i < m_nextTetrominos.size() - 1; i++)
  {
    m_nextTetrominos[i] = m_nextTetrominos[i + 1];
  }
  m_nextTetrominos[m_nextTetrominos.size() - 1] = getRandomTetromino();
}

const Tetromino TetrisGame::getRandomTetromino()
{
  int random = rand() % 8;

  switch (random)
  {
  case 1:
    return {&TetrominoModels::JShape, GREEN};
  case 2:
    return {&TetrominoModels::LShape, BLUE};
  case 3:
    return {&TetrominoModels::IShape, PURPLE};
  case 4:
    return {&TetrominoModels::OShape, LIME};
  case 5:
    return {&TetrominoModels::SShape, MAROON};
  case 6:
    return {&TetrominoModels::TShape, RED};
  case 7:
  default:
    return {&TetrominoModels::ZShape, YELLOW};
    break;
  }
}
