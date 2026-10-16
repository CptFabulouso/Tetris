#include "Renderer.h"
#include "rlImGui.h"
#include "imguiThemes.h"

Renderer::Renderer()
{
#pragma region imgui
  rlImGuiSetup(true);

  // you can use whatever imgui theme you like!
  imguiThemes::green();

  ImGuiIO &io = ImGui::GetIO();
  io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
  io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
  io.FontGlobalScale = 1;

  ImGuiStyle &style = ImGui::GetStyle();
  if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    style.Colors[ImGuiCol_WindowBg].w = 0.5f;
  }
#pragma endregion
}

void Renderer::render(const TetrisGame &game)
{
  drawTetrisBoardBackground(game);
  drawTetrisOccupiedCells(game);
  if (!game.getIsGameOver())
  {
    drawTetrisShadowTetromino(game);
    drawTetrisActiveTetromino(game);
  }
  drawTetrisBoardGrid(game);
  drawNextTetrominoBoard(game);

  if (game.getIsGameOver())
  {
    drawGameOver(game);
  }
}

Renderer::~Renderer()
{
  rlImGuiShutdown();
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

  float framerate = ImGui::GetIO().Framerate;
  ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / framerate, framerate);
  ImGui::End();

#pragma region imgui
  rlImGuiEnd();

  if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
  {
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
  }
#pragma endregion
}

void Renderer::drawTetrisBoardBackground(const TetrisGame &game)
{
  const TetrisBoard &tetrisBoard = game.getBoard();
  const Vector2 &position = tetrisBoard.getPosition();
  int width = tetrisBoard.getWidth();
  int height = tetrisBoard.getHeight();
  int borderWidth = 6;
  DrawRectangle(position.x - borderWidth, position.y - borderWidth, width + 2 * borderWidth, height + 2 * borderWidth, DARKGRAY);
  DrawRectangle(position.x, position.y, width, height, LIGHTGRAY);
}

void Renderer::drawTetrisBoardGrid(const TetrisGame &game)
{
  const TetrisBoard &tetrisBoard = game.getBoard();

  const Vector2 &position = tetrisBoard.getPosition();
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
  const TetrisBoard &tetrisBoard = game.getBoard();

  const Vector2 &tetrisPosition = tetrisBoard.getPosition();
  int tetrisCellSize = tetrisBoard.getCellSize();
  const TetrisBoard::TetrisBoardGrid &tetrisGrid = tetrisBoard.getGrid();

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
  const TetrisBoard &tetrisBoard = game.getBoard();
  const Vector2 &tetrisPosition = tetrisBoard.getPosition();
  int tetrisCellSize = tetrisBoard.getCellSize();

  const Tetromino &activeTetromino = game.getActiveTetromino();

  const std::vector<BoardCell> &activeTetrominoCells = activeTetromino.getCells();
  const ShapeModel *model = activeTetromino.getModel();
  Vec2i position = activeTetromino.getPosition();

  if (m_drawShapeRect)
  {
    DrawRectangle(tetrisPosition.x + position.x * tetrisCellSize, tetrisPosition.y + position.y * tetrisCellSize, tetrisCellSize * model->getSize(), tetrisCellSize * model->getSize(), PURPLE);
  }
  for (const BoardCell &cell : activeTetrominoCells)
  {
    DrawRectangle(tetrisPosition.x + cell.x * tetrisCellSize, tetrisPosition.y + cell.y * tetrisCellSize, tetrisCellSize, tetrisCellSize, cell.color);
  }
}

void Renderer::drawTetrisShadowTetromino(const TetrisGame &game)
{
  const TetrisBoard &tetrisBoard = game.getBoard();
  const Vector2 &tetrisPosition = tetrisBoard.getPosition();
  int tetrisCellSize = tetrisBoard.getCellSize();

  const Tetromino &shadowTetromino = game.getShadowTetromino();

  const std::vector<BoardCell> &shadowTetrominoCells = shadowTetromino.getCells();

  for (const BoardCell &cell : shadowTetrominoCells)
  {
    DrawRectangle(tetrisPosition.x + cell.x * tetrisCellSize, tetrisPosition.y + cell.y * tetrisCellSize, tetrisCellSize, tetrisCellSize, MAGENTA);
  }
}

void Renderer::drawNextTetrominoBoard(const TetrisGame &game)
{
  const NextTetrominoBoard &nextTetrominoBoard = game.getNextTetrominoBoard();
  const Vector2 &position = nextTetrominoBoard.getPosition();
  int width = nextTetrominoBoard.getWidth();
  int height = nextTetrominoBoard.getHeight();
  int borderWidth = 6;
  DrawRectangle(position.x - borderWidth, position.y - borderWidth, width + 2 * borderWidth, height + 2 * borderWidth, DARKGRAY);
  DrawRectangle(position.x, position.y, width, height, LIGHTGRAY);

  int fontSize = 20;
  int textWidth = MeasureText("Next", fontSize);
  float textPadding = (width - textWidth) / 2;
  DrawText("Next", position.x + textPadding, position.y + 5, fontSize, DARKGRAY);

  const std::array<Tetromino, 3> &nextTetrominos = game.getNextTetrominos();

  int cellSize = nextTetrominoBoard.getCellSize();
  int tetrominoY = position.y + 30;

  for (int i = 0; i < nextTetrominos.size(); i++)
  {
    const std::vector<BoardCell> &tetrominoCells = nextTetrominos[i].getCells();
    int modelSize = nextTetrominos[i].getModel()->getSize();
    int modelWidth = cellSize * modelSize;
    float startX = position.x + (width - modelWidth) / 2;
    for (const BoardCell &cell : tetrominoCells)
    {
      DrawRectangle(startX + cell.x * cellSize, tetrominoY + cell.y * cellSize, cellSize, cellSize, cell.color);
    }
    tetrominoY += cellSize * modelSize + 10;
  }
}

void Renderer::drawGameOver(const TetrisGame &game)
{
  const TetrisBoard &tetrisBoard = game.getBoard();

  const Vector2 &position = tetrisBoard.getPosition();
  int cellSize = tetrisBoard.getCellSize();
  int width = tetrisBoard.getWidth();
  int height = tetrisBoard.getHeight();
  int textSize = 30;
  int textWidth = MeasureText("Game Over", textSize);
  int textPadding = 10;

  int textBoxHeight = textSize + textPadding * 2;
  int textBoxWidth = textWidth + textPadding * 2;
  int paddingHorizontal = (width - textBoxWidth) / 2;
  int paddingVertical = (height - textBoxHeight) / 2;
  int textBoxX = position.x + paddingHorizontal;
  int textBoxY = position.y + paddingVertical;

  DrawRectangle(textBoxX, textBoxY, textBoxWidth, textBoxHeight, BLACK);
  DrawText("Game over", textBoxX + textPadding, textBoxY + textPadding, textSize, WHITE);
}
