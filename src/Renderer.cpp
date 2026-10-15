#include "Renderer.h"
#include "rlImGui.h"
#include "imguiThemes.h"

Renderer::Renderer()
{
#pragma region imgui
  rlImGuiSetup(true);

  // you can use whatever imgui theme you like!
  imguiThemes::green();

  m_ImGUIio = &ImGui::GetIO();
  // (void)m_ImGUIio;
  m_ImGUIio->ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  m_ImGUIio->ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
  m_ImGUIio->FontGlobalScale = 1;

  ImGuiStyle &style = ImGui::GetStyle();
  if (m_ImGUIio->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    style.Colors[ImGuiCol_WindowBg].w = 0.5f;
  }
#pragma endregion
}

void Renderer::render(const TetrisGame &game)
{
  drawTetrisBoardBackground(game);
  drawTetrisOccupiedCells(game);
  drawTetrisShadowTetromino(game);
  drawTetrisActiveTetromino(game);
  drawTetrisBoardGrid(game);
  drawNextTetrominoBoard(game);
}

void Renderer::renderImGUI()
{
#pragma region imgui
  rlImGuiBegin();

  ImGui::PushStyleColor(ImGuiCol_WindowBg, {});
  ImGui::PushStyleColor(ImGuiCol_DockingEmptyBg, {});
  ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
  ImGui::PopStyleColor(2);
#pragma endregion

  ImGui::Begin("Dev");

  ImGui::Checkbox("Show shape rect", &m_drawShapeRect);

  ImGui::End();

#pragma region imgui
  rlImGuiEnd();

  if (m_ImGUIio->ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
  }
#pragma endregion
}

void Renderer::drawTetrisBoardBackground(const TetrisGame &game)
{
  TetrisBoard tetrisBoard = game.getBoard();
  Vector2 position = tetrisBoard.getPosition();
  int width = tetrisBoard.getWidth();
  int height = tetrisBoard.getHeight();
  int borderWidth = 6;
  DrawRectangle(position.x - borderWidth, position.y - borderWidth, width + 2 * borderWidth, height + 2 * borderWidth, DARKGRAY);
  DrawRectangle(position.x, position.y, width, height, LIGHTGRAY);
}

void Renderer::drawTetrisBoardGrid(const TetrisGame &game)
{
  TetrisBoard tetrisBoard = game.getBoard();

  Vector2 position = tetrisBoard.getPosition();
  int cellSize = tetrisBoard.getCellSize();
  int width = tetrisBoard.getWidth();
  int height = tetrisBoard.getHeight();
  int borderWidth = 5;

  for (int row = 1; row < TetrisBoard::ROWS; row++)
  {
    DrawLineV(
        {position.x, position.y + cellSize * row},
        {position.x + width, position.y + cellSize * row},
        DARKGRAY);
  }
  for (int column = 1; column < TetrisBoard::COLUMNS; column++)
  {
    DrawLineV(
        {position.x + column * cellSize, position.y},
        {position.x + column * cellSize, position.y + height},
        DARKGRAY);
  }
}

void Renderer::drawTetrisOccupiedCells(const TetrisGame &game)
{
  TetrisBoard tetrisBoard = game.getBoard();

  Vector2 tetrisPosition = tetrisBoard.getPosition();
  int tetrisCellSize = tetrisBoard.getCellSize();
  TetrisBoard::TetrisBoardGrid tetrisGrid = tetrisBoard.getGrid();

  for (size_t x = 0; x < tetrisGrid.size(); x++)
  {
    for (size_t y = 0; y < tetrisGrid[x].size(); y++)
    {
      if (tetrisGrid[x][y].has_value())
      {
        DrawRectangle(tetrisPosition.x + x * tetrisCellSize, tetrisPosition.y + y * tetrisCellSize, tetrisCellSize, tetrisCellSize, tetrisGrid[x][y]->color);
      };
    }
  }
}

void Renderer::drawTetrisActiveTetromino(const TetrisGame &game)
{
  TetrisBoard tetrisBoard = game.getBoard();
  Vector2 tetrisPosition = tetrisBoard.getPosition();
  int tetrisCellSize = tetrisBoard.getCellSize();

  Tetromino activeTetromino = game.getActiveTetromino();

  std::vector<BoardCell> activeTetrominoCells = activeTetromino.getCells();
  const ShapeModel *model = activeTetromino.getModel();
  Vec2i position = activeTetromino.getPosition();

  if (m_drawShapeRect)
  {
    DrawRectangle(tetrisPosition.x + position.x * tetrisCellSize, tetrisPosition.y + position.y * tetrisCellSize, tetrisCellSize * model->getSize(), tetrisCellSize * model->getSize(), PURPLE);
  }
  for (BoardCell &cell : activeTetrominoCells)
  {
    DrawRectangle(tetrisPosition.x + cell.x * tetrisCellSize, tetrisPosition.y + cell.y * tetrisCellSize, tetrisCellSize, tetrisCellSize, cell.color);
  }
}

void Renderer::drawTetrisShadowTetromino(const TetrisGame &game)
{
  TetrisBoard tetrisBoard = game.getBoard();
  Vector2 tetrisPosition = tetrisBoard.getPosition();
  int tetrisCellSize = tetrisBoard.getCellSize();

  Tetromino shadowTetromino = game.getShadowTetromino();

  std::vector<BoardCell> shadowTetrominoCells = shadowTetromino.getCells();
  const ShapeModel *model = shadowTetromino.getModel();
  Vec2i position = shadowTetromino.getPosition();

  for (BoardCell &cell : shadowTetrominoCells)
  {
    DrawRectangle(tetrisPosition.x + cell.x * tetrisCellSize, tetrisPosition.y + cell.y * tetrisCellSize, tetrisCellSize, tetrisCellSize, MAGENTA);
  }
}

void Renderer::drawNextTetrominoBoard(const TetrisGame &game)
{
  NextTetrominoBoard nextTetrominoBoard = game.getNextTetrominoBoard();
  Vector2 position = nextTetrominoBoard.getPosition();
  int width = nextTetrominoBoard.getWidth();
  int height = nextTetrominoBoard.getHeight();
  int borderWidth = 6;
  DrawRectangle(position.x - borderWidth, position.y - borderWidth, width + 2 * borderWidth, height + 2 * borderWidth, DARKGRAY);
  DrawRectangle(position.x, position.y, width, height, LIGHTGRAY);

  int fontSize = 20;
  int textWidth = MeasureText("Next", fontSize);
  float textPadding = (width - textWidth) / 2;
  DrawText("Next", position.x + textPadding, position.y + 5, fontSize, DARKGRAY);

  std::array<Tetromino, 3> nextTetrominos = game.getNextTetrominos();

  int cellSize = nextTetrominoBoard.getCellSize();
  int tetrominoY = position.y + 30;

  for (int i = 0; i < nextTetrominos.size(); i++)
  {
    std::vector<BoardCell> tetrominoCells = nextTetrominos[i].getCells();
    int modelSize = nextTetrominos[i].getModel()->getSize();
    int modelWidth = cellSize * modelSize;
    float startX = position.x + (width - modelWidth) / 2;
    for (BoardCell &cell : tetrominoCells)
    {
      DrawRectangle(startX + cell.x * cellSize, tetrominoY + cell.y * cellSize, cellSize, cellSize, cell.color);
    }
    tetrominoY += cellSize * modelSize + 10;
  }
}
