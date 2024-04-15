#include "PopupLayer.h"

PopupLayer* PopupLayer::createWithMessage(const std::string& message)
{
  PopupLayer* pRet = new(std::nothrow) PopupLayer();
  
  if (pRet && pRet->initWithMessage(message))
  {
    pRet->autorelease();
    return pRet;
  }
  else
  {
    delete pRet;
    pRet = nullptr;
    return nullptr;
  }
}

bool PopupLayer::initWithMessage(const std::string& message)
{
  if (!LayerColor::initWithColor(Color4B(0, 0, 0, 180)))
  {
    return false;
  }
  
  const auto size = _director->getVisibleSize();
  const auto origin = _director->getVisibleOrigin();
  
  const auto fontPath = "fonts/Marker Felt.ttf";
  const auto fontSize = 60;
  
  const auto label = Label::createWithTTF(message, fontPath, fontSize);
  label->setPosition(origin.x + size.width / 2, origin.y + size.height / 2);
  
  this->addChild(label);
  
  const auto listener = EventListenerTouchOneByOne::create();
  
  listener->onTouchBegan = [&](Touch* touch, Event* event) {
    this->removeFromParentAndCleanup(true);
    return true;
  };
  
  listener->setSwallowTouches(true);
  
  _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
  
  return true;
}
