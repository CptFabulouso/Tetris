#include "ShapeModel.h"

ShapeModel::ShapeModel(const std::vector<Vec2i> &cells) : m_cells(cells)
{
  int width = 0;
  int height = 0;

  for (Vec2i &cell : m_cells)
  {
    width = std::max(cell.x + 1, width);
    height = std::max(cell.y + 1, height);
  }

  m_size = std::max(width, height);
}