#include "SplashScene.h"
#include "MainMenuScene.h"
#include "ui/axmol-ui.h"

namespace
{
void transitionToMainMenu()
{
  const auto duration = 0.75F;
  const auto scene = MainMenuScene::create();
  const auto color = Color3B(20, 20, 20);
  
  const auto transition = TransitionFade::create(duration, scene, color);
  
  Director::getInstance()->replaceScene(transition);
}

LayerColor* newBackground()
{
  const auto color = Color4B(0, 0, 0, 255);
  
  return LayerColor::create(color);
}

Sprite* newLogo(const Rect& rect)
{
  const auto sprite = Sprite::create("HelloWorld.png");
  
  const auto center = Vec2(rect.getMidX(), rect.getMidY());
  
  sprite->setPosition(center);
  
  return sprite;
}
}

bool SplashScene::init()
{
  if (!Scene::init())
  {
    return false;
  }
  
  const auto safeAreaRect = _director->getSafeAreaRect();
  
  this->addChild(newBackground());
  this->addChild(newLogo(safeAreaRect));
  
  return true;
}

void SplashScene::onEnter()
{
  Scene::onEnter();
  
  const auto delay = DelayTime::create(0.75F);
  const auto transition = CallFunc::create([this]() {
    transitionToMainMenu();
  });
  
  const auto sequence = Sequence::create(delay, transition, nullptr);
  
  this->runAction(sequence);
}
