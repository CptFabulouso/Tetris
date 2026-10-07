#pragma once

#include "TetrisGame.h"
#include "imgui.h"

class Renderer
{
private:
  ImGuiIO *m_ImGUIio;
  bool m_drawShapeRect = false;

public:
  Renderer();
  void render(const TetrisGame &game);
  void renderImGUI();

private:
  void drawTetrisBoardBackground(const TetrisGame &game);
  void drawTetrisBoardGrid(const TetrisGame &game);
  void drawTetrisOccupiedCells(const TetrisGame &game);
  void drawTetrisActiveTetromino(const TetrisGame &game);
  void drawTetrisShadowTetromino(const TetrisGame &game);
};