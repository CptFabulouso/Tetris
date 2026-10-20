#pragma once

#include <vector>
#include <algorithm>
#include "models.h"

class ShapeModel
{
private:
  std::vector<Vec2i> m_cells = {};
  int m_size = 0;

public:
  explicit ShapeModel(const std::vector<Vec2i> &cells);

  const std::vector<Vec2i> &getCells() const
  {
    return m_cells;
  }

  int getSize() const
  {
    return m_size;
  }
};
