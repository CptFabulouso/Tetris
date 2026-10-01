#pragma once

#include <iostream>
#include <vector>
#include "models.h"

class ShapeModel
{
private:
  std::vector<Vec2i> m_cells = {};
  int m_size = 0;
  Vec2i m_shapeOffset = {0, 0};

public:
  ShapeModel() : m_cells({})
  {
  }

  ShapeModel(const std::vector<Vec2i> &cells) : m_cells(cells)
  {
    int width = cells[0].x;
    int height = cells[0].y;
    m_shapeOffset.x = cells[0].x;
    m_shapeOffset.y = cells[0].y;

    for (Vec2i &cell : m_cells)
    {
      m_shapeOffset.x = std::min(cell.x, m_shapeOffset.x);
      m_shapeOffset.y = std::min(cell.y, m_shapeOffset.y);
      width = std::max(cell.x + 1, width);
      height = std::max(cell.y + 1, height);
    }

    m_size = std::max(width, height);

    for (Vec2i &cell : m_cells)
    {
      cell.x -= m_size / 2;
      cell.y -= m_size / 2;
    }
  }

  const std::vector<Vec2i> &getCells() const
  {
    return m_cells;
  }

  const int getSize() const
  {
    return m_size;
  }

  const Mat3 getRotationMatrix(Rotation rotation)
  {
    float move = m_size % 2 == 0 ? -1 : 0;
    if (rotation == DEG0)
    {
      return Mat3{{{1, 0, 0}, {0, 1, 0}, {0, 0, 0}}};
    }
    else if (rotation == DEG90)
    {
      return Mat3{{{0, -1, move}, {1, 0, 0}, {0, 0, 0}}};
    }
    else if (rotation == DEG180)
    {
      return Mat3{{{-1, 0, move}, {0, -1, move}, {0, 0, 0}}};
    }
    return Mat3{{{0, 1, 0}, {-1, 0, move}, {0, 0, 0}}};
  }
};
