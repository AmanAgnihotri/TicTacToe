#include "BoardLayer.h"

bool BoardLayer::init()
{
  if (!Layer::init())
  {
    return false;
  }
  
  const auto safeAreaRect = _director->getSafeAreaRect();
  
  setup(safeAreaRect);
  drawGrid();
  addTouchListener();
  
  return true;
}

void BoardLayer::setOnTouchCallback(OnTouch onTouch)
{
  this->onTouch = onTouch;
}

void BoardLayer::setup(const Rect& rect)
{
  const auto size = MIN(rect.size.width, rect.size.height) * 0.95F;
  
  tileSize = size / 3;
  
  const auto centerX = rect.getMidX() - size / 2;
  const auto centerY = rect.getMidY() - size / 2;
  
  this->setPosition(Vec2(centerX, centerY));
}

void BoardLayer::drawGrid()
{
  const auto color = Color4F::BLACK;
  const auto size = tileSize * 3;
  
  const auto node = DrawNode::create();
  
  // Draw vertical lines
  for (int i = 1; i < 3; i++)
  {
    const auto origin = Vec2(i * tileSize, 0);
    const auto destination = Vec2(i * tileSize, size);
    
    node->drawLine(origin, destination, color);
  }
  
  // Draw horizontal lines
  for (int i = 1; i < 3; ++i)
  {
    const auto origin = Vec2(0, i * tileSize);
    const auto destination = Vec2(size, i * tileSize);
    
    node->drawLine(origin, destination, color);
  }
  
  this->addChild(node);
}

void BoardLayer::addTouchListener()
{
  const auto listener = EventListenerTouchOneByOne::create();
  
  listener->onTouchBegan = [this](Touch* touch, Event* event) -> bool
  {
    const auto locationInNode = this->convertToNodeSpace(touch->getLocation());
    
    const int rank = locationInNode.y / tileSize;
    const int file = locationInNode.x / tileSize;
    
    if (rank < 0 || rank > 2 || file < 0 || file > 2)
    {
      return false;
    }
    
    if (onTouch)
    {
      onTouch(rank, file);
    }
  };
  
  listener->setSwallowTouches(true);
  
  _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void BoardLayer::drawX(int rank, int file)
{
  auto const margin = tileSize * 0.1F;
  auto const color = Color4F::RED;
  
  const auto centerX = file * tileSize + tileSize / 2;
  const auto centerY = rank * tileSize + tileSize / 2;
  const auto center = Vec2(centerX, centerY);
  
  const auto halfLength = tileSize / 2 - margin;
  
  const auto leftX = centerX - halfLength;
  const auto rightX = centerX + halfLength;
  
  const auto topY = centerY - halfLength;
  const auto bottomY = centerY + halfLength;
  
  const auto topLeft = Vec2(leftX, topY);
  const auto topRight = Vec2(rightX, topY);
  const auto bottomLeft = Vec2(leftX, bottomY);
  const auto bottomRight = Vec2(rightX, bottomY);
  
  const auto node = DrawNode::create();
  
  node->drawLine(topLeft, bottomRight, color);
  node->drawLine(bottomLeft, topRight, color);
  
  this->addChild(node);
}

void BoardLayer::drawO(int rank, int file)
{
  auto const margin = tileSize * 0.1F;
  auto const color = Color4F::BLUE;
  
  const auto centerX = file * tileSize + tileSize / 2;
  const auto centerY = rank * tileSize + tileSize / 2;
  const auto center = Vec2(centerX, centerY);
  
  const auto radius = tileSize / 2 - margin;
  
  const auto node = DrawNode::create();
  node->drawCircle(center, radius, 0, 50, false, color);
  
  this->addChild(node);
}
