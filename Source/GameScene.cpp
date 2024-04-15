#include "GameScene.h"
#include "MainMenuScene.h"
#include "PopupLayer.h"

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
  const auto color = Color4B(245, 245, 245, 255);
  
  return LayerColor::create(color);
}

BoardLayer* newBoardLayer(OnTouch onTouch)
{
  const auto layer = BoardLayer::create();
  
  layer->setOnTouchCallback(onTouch);
  
  return layer;
}
}

bool GameScene::init()
{
  if (!Scene::init())
  {
    return false;
  }
  
  this->addChild(newBackground());
  
  const auto onTouch = std::bind(&GameScene::onTouch, this,
                                 std::placeholders::_1,
                                 std::placeholders::_2);
  
  boardLayer = newBoardLayer(onTouch);
  
  this->addChild(boardLayer);
  
  return true;
}

void GameScene::onTouch(int rank, int file)
{
  const auto mark = game.getCurrentMark();
  const auto event = game.apply(rank, file);
  
  if (event == GameEvent::AlreadyOccupied)
  {
    return;
  }
  
  drawMark(rank, file, mark);
  
  if (event == GameEvent::Applied)
  {
    return;
  }
  
  std::string message = "Done!";
  if (event == GameEvent::Draw)
  {
    message = "Draw!";
  }
  else if (event == GameEvent::WinForX)
  {
    message = "X Wins!";
  }
  else if (event == GameEvent::WinForO)
  {
    message = "O Wins!";
  }
  
  const auto popup = PopupLayer::createWithMessage(message);
  this->addChild(popup, 100);
  
  exit();
}

void GameScene::drawMark(int rank, int file, Mark mark)
{
  if (mark == Mark::X)
  {
    boardLayer->drawX(rank, file);
  }
  else if (mark == Mark::O)
  {
    boardLayer->drawO(rank, file);
  }
}

void GameScene::exit()
{
  const auto delay = DelayTime::create(2.0F);
  const auto transition = CallFunc::create([this]() {
    transitionToMainMenu();
  });
  
  const auto sequence = Sequence::create(delay, transition, nullptr);
  
  this->runAction(sequence);
}
