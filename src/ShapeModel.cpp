#include "ShapeModel.h"
#include <algorithm>
#include "TtrAssert.h"

namespace
{
  Vec2i rotateInBox(Vec2i currentCell, Rotation rotation, int modelSize)
  {
    const int m = modelSize - 1;
    switch (rotation)
    {
    case Rotation::Deg0:
      return {currentCell.x, currentCell.y};
    case Rotation::Deg90:
      return {m - currentCell.y, currentCell.x};
    case Rotation::Deg180:
      return {m - currentCell.x, m - currentCell.y};
    case Rotation::Deg270:
      return {currentCell.y, m - currentCell.x};
    }
    return currentCell;
  }
}

ShapeModel::ShapeModel(
    const std::vector<Vec2i> &cells,
    const std::vector<Rotation> &rotations)
{
  TTR_ASSERT(!cells.empty() && !rotations.empty());

  int width = 0;
  int height = 0;
  for (const Vec2i &cell : cells)
  {
    width = std::max(cell.x + 1, width);
    height = std::max(cell.y + 1, height);
  }
  m_boxSize = std::max(width, height);

  std::vector<Rotation> uniqueSortedRotations = rotations;
  std::sort(uniqueSortedRotations.begin(), uniqueSortedRotations.end());
  uniqueSortedRotations.erase(
      std::unique(uniqueSortedRotations.begin(), uniqueSortedRotations.end()),
      uniqueSortedRotations.end());

  m_orientations.reserve(uniqueSortedRotations.size());
  for (Rotation r : uniqueSortedRotations)
  {
    createOrientationVariant(r, cells);
  }
}

const std::vector<Vec2i> &ShapeModel::cells(size_t index) const
{
  return orientation(index).cells;
}

const Orientation &ShapeModel::orientation(size_t index) const
{
  TTR_ASSERT(index < m_orientations.size());
  return m_orientations[index];
}

size_t ShapeModel::orientationsCount() const
{
  return m_orientations.size();
}

void ShapeModel::createOrientationVariant(Rotation rotation, const std::vector<Vec2i> &cells)
{
  Orientation &orientation = m_orientations.emplace_back();
  orientation.rotation = rotation;
  orientation.cells.reserve(cells.size());
  for (const Vec2i &cell : cells)
  {
    orientation.cells.push_back(rotateInBox(cell, rotation, m_boxSize));
  }
}
