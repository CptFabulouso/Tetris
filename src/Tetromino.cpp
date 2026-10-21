#include "Tetromino.h"
#include "TtrAssert.h"

Tetromino::Tetromino(const ShapeModel &model) : m_shapeModel(&model)
{
  m_shapeCells.resize(model.cells(0).size());
  calculateShapeCellsPosition();
}

Tetromino::Tetromino(const ShapeModel &model, Color color) : Tetromino(model)
{
  setColor(color);
}

void Tetromino::calculateShapeCellsPosition()
{
  const std::vector<Vec2i> &modelCells = m_shapeModel->cells(m_orientation);

  TTR_ASSERT(modelCells.size() == m_shapeCells.size());
  for (size_t i = 0; i < modelCells.size(); i++)
  {
    m_shapeCells[i].x = m_position.x + modelCells[i].x;
    m_shapeCells[i].y = m_position.y + modelCells[i].y;
  }
}

const std::vector<BoardCell> &Tetromino::cells() const
{
  return m_shapeCells;
}

const ShapeModel *Tetromino::getModel() const
{
  return m_shapeModel;
}

Vec2i Tetromino::getPosition() const
{
  return m_position;
}

size_t Tetromino::getOrientation() const
{
  return m_orientation;
}

void Tetromino::move(Vec2i direction)
{
  m_position.x += direction.x;
  m_position.y += direction.y;
  calculateShapeCellsPosition();
}

void Tetromino::rotate(int direction)
{
  const int count = static_cast<int>(m_shapeModel->orientationsCount());

  const int next = (static_cast<int>(m_orientation) + direction % count + count) % count;
  m_orientation = static_cast<size_t>(next);
  calculateShapeCellsPosition();
}

void Tetromino::setPosition(Vec2i position)
{
  m_position = position;
  calculateShapeCellsPosition();
}

void Tetromino::setOrientation(size_t orientation)
{
  TTR_ASSERT(orientation < m_shapeModel->orientationsCount());
  m_orientation = orientation;
  calculateShapeCellsPosition();
}

void Tetromino::setColor(Color color)
{
  for (BoardCell &cell : m_shapeCells)
  {
    cell.color = color;
  }
}

namespace TetrominoModels
{
  const ShapeModel JShape({{0, 0}, {0, 1}, {1, 1}, {2, 1}});
  const ShapeModel LShape({{0, 1}, {1, 1}, {2, 1}, {2, 0}});
  const ShapeModel IShape({{0, 1}, {1, 1}, {2, 1}, {3, 1}});
  const ShapeModel OShape({{0, 0}, {1, 0}, {0, 1}, {1, 1}});
  const ShapeModel SShape({{0, 1}, {1, 1}, {1, 0}, {2, 0}});
  const ShapeModel TShape({{0, 1}, {1, 1}, {1, 0}, {2, 1}});
  const ShapeModel ZShape({{0, 0}, {1, 0}, {1, 1}, {2, 1}});
}
