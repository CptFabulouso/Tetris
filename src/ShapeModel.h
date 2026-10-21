#pragma once

#include <vector>
#include "models.h"

struct Orientation
{
  Rotation rotation;
  std::vector<Vec2i> cells;
};

class ShapeModel
{
private:
  std::vector<Orientation> m_orientations;
  int m_boxSize = 0;

public:
  explicit ShapeModel(
      const std::vector<Vec2i> &cells,
      const std::vector<Rotation> &rotations = {Rotation::Deg0, Rotation::Deg90, Rotation::Deg180, Rotation::Deg270});

  const std::vector<Vec2i> &cells(size_t index) const;
  const Orientation &orientation(size_t index) const;
  size_t orientationsCount() const;

  int getBoxSize() const
  {
    return m_boxSize;
  }

private:
  void createOrientationVariant(Rotation rotation, const std::vector<Vec2i> &cells);
};
