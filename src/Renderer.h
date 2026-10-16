#pragma once

#include "TetrisGame.h"
#include "imgui.h"

class Renderer
{
private:
  bool m_drawShapeRect = false;

public:
  Renderer();
  ~Renderer();
  Renderer(const Renderer &) = delete;
  Renderer &operator=(const Renderer &) = delete;

  void render(const TetrisGame &game);
  void renderImGUI(TetrisGame &game);

private:
  void drawTetrisBoardBackground(const TetrisGame &game);
  void drawTetrisBoardGrid(const TetrisGame &game);
  void drawTetrisOccupiedCells(const TetrisGame &game);
  void drawTetrisActiveTetromino(const TetrisGame &game);
  void drawTetrisShadowTetromino(const TetrisGame &game);
  void drawNextTetrominoBoard(const TetrisGame &game);
  void drawGameOver(const TetrisGame &game);
};