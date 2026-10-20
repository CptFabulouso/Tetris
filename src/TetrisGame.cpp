#include "TetrisGame.h"
#include "raylib.h"

TetrisGame::TetrisGame(const Tetromino &tetromino) : m_board{0, 0},
                                                     m_nextTetrominos{
                                                         getRandomTetromino(),
                                                         getRandomTetromino(),
                                                         getRandomTetromino(),
                                                     },
                                                     m_activeTetromino(tetromino),
                                                     m_shadowTetromino(tetromino)

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

  if (m_gameOver)
  {
    return;
  }
  m_timer -= dt;
  if (m_timer < 0)
  {
    m_timer = m_moveDuration;
    applyAction(Action::MoveDown);
  }

  calculateShadowTetromino();
}

void TetrisGame::applyAction(Action action)
{
  switch (action)
  {
  case Action::MoveLeft:
    tryMove({-1, 0});
    break;
  case Action::MoveRight:
    tryMove({1, 0});
    break;
  case Action::MoveDown:
  {
    if (!tryMove({0, 1}))
    {
      placeTetromino(m_activeTetromino);
    }
    break;
  }
  case Action::InstantDown:
    placeTetromino(m_shadowTetromino);
    break;
  case Action::Rotate:
    tryRotate(1);
    break;
  default:
    break;
  }
}

void TetrisGame::resetGame()
{
  *this = {};
}

bool TetrisGame::tryMove(Vec2i direction)
{
  Tetromino candidate = m_activeTetromino;

  candidate.move(direction);
  if (m_board.canPlace(candidate))
  {
    m_activeTetromino.setPosition(candidate.getPosition());
    return true;
  }
  return false;
}

void TetrisGame::tryRotate(int direction)
{
  Tetromino candidate = m_activeTetromino;
  candidate.rotate(direction);

  if (m_board.canPlace(candidate))
  {
    m_activeTetromino.setRotation(candidate.getRotation());
    m_activeTetromino.setPosition(candidate.getPosition());
    return;
  }

  /* try wall kick to the right */
  for (int kick = 0; kick <= 2; kick++)
  {
    candidate.move({1, 0});
    if (m_board.canPlace(candidate))
    {
      m_activeTetromino.setRotation(candidate.getRotation());
      m_activeTetromino.setPosition(candidate.getPosition());
      return;
    }
  }

  /*  try wall kick to the left */
  // reset position
  candidate.setPosition(m_activeTetromino.getPosition());
  for (int kick = 0; kick <= 2; kick++)
  {
    candidate.move({-1, 0});
    if (m_board.canPlace(candidate))
    {
      m_activeTetromino.setRotation(candidate.getRotation());
      m_activeTetromino.setPosition(candidate.getPosition());
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

void TetrisGame::placeTetromino(const Tetromino &tetromino)
{
  for (auto &cell : tetromino.getCells())
  {
    if (cell.y < 0)
    {
      m_gameOver = true;
      return;
    }
  }

  m_board.addOccupiedCells(tetromino.getCells());
  int collapsedRows = m_board.collapseFullRows();

  spawnTetromino();
}

void TetrisGame::spawnTetromino()
{
  m_timer = m_moveDuration;
  Tetromino nextTetromino = m_nextTetrominos[0];

  m_activeTetromino = nextTetromino;

  bool checkGameOver = false;
  // make sure tetromino can be placed at the spawn location, otherwise try to move it up
  while (!m_board.canPlace(m_activeTetromino))
  {
    checkGameOver = true;
    m_activeTetromino.move({0, -1});
  }

  if (checkGameOver)
  {
    bool isGameOver = true;
    // if there is no cell of the tetromino on the play board, it's game over
    for (auto &cell : m_activeTetromino.getCells())
    {
      if (cell.y >= 0)
      {
        isGameOver = false;
        break;
      }
    }
    m_gameOver = isGameOver;
  }
  if (m_gameOver)
  {
    return;
  }

  m_shadowTetromino = nextTetromino;

  for (int i = 0; i < m_nextTetrominos.size() - 1; i++)
  {
    m_nextTetrominos[i] = m_nextTetrominos[i + 1];
  }
  m_nextTetrominos[m_nextTetrominos.size() - 1] = getRandomTetromino();
}

Tetromino TetrisGame::getRandomTetromino()
{
  int random = rand() % 7;

  switch (random)
  {
  case 0:
    return Tetromino{TetrominoModels::JShape, GREEN};
  case 1:
    return Tetromino{TetrominoModels::LShape, BLUE};
  case 2:
    return Tetromino{TetrominoModels::IShape, PURPLE};
  case 3:
    return Tetromino{TetrominoModels::OShape, LIME};
  case 4:
    return Tetromino{TetrominoModels::SShape, MAROON};
  case 5:
    return Tetromino{TetrominoModels::TShape, RED};
  case 6:
  default:
    return Tetromino{TetrominoModels::ZShape, YELLOW};
  }
}
