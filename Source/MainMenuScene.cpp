#include "MainMenuScene.h"
#include "GameScene.h"
#include "ui/axmol-ui.h"

using namespace ax::ui;

namespace
{
const auto fontSize = 48;
const auto fontPath = "fonts/Marker Felt.ttf";

void transitionToGame()
{
  const auto duration = 0.75F;
  const auto scene = GameScene::create();
  const auto color = Color3B(245, 245, 245);
  
  const auto transition = TransitionFade::create(duration, scene, color);
  
  Director::getInstance()->replaceScene(transition);
}

void exitGame()
{
  Director::getInstance()->end();
}

LayerColor* newBackground()
{
  const auto color = Color4B(20, 20, 20, 255);
  
  return LayerColor::create(color);
}

RelativeLayoutParameter* newTitleParam()
{
  const auto param = RelativeLayoutParameter::create();
  
  using enum RelativeLayoutParameter::RelativeAlign;
  param->setAlign(PARENT_TOP_CENTER_HORIZONTAL);
  
  const auto topPadding = 50;
  param->setMargin({0, topPadding, 0, 0});
  
  return param;
}

Text* newTitle()
{
  const auto title = Text::create("TicTacToe", fontPath, 2*fontSize);
  title->setLayoutParameter(newTitleParam());
  
  return title;
}

MenuItemLabel* newCreateGameLabel()
{
  const auto text = "Create Game";
  
  const auto label = Label::createWithTTF(text, fontPath, fontSize);
  const auto callback = [](Ref* _) { transitionToGame(); };
  
  return MenuItemLabel::create(label, callback);
}

MenuItemLabel* newExitLabel()
{
  const auto text = "Exit";
  
  const auto label = Label::createWithTTF(text, fontPath, fontSize);
  const auto callback = [](Ref* _) { exitGame(); };
  
  return MenuItemLabel::create(label, callback);
}

Menu* newMenu(const Rect& rect)
{
  const auto createGameLabel = newCreateGameLabel();
  const auto exitLabel = newExitLabel();
  
  const auto menu = Menu::create(createGameLabel, exitLabel, NULL);
  
  const auto padding = 48.0F;
  menu->alignItemsVerticallyWithPadding(padding);
  
  menu->setPosition(rect.getMidX(), rect.getMidY());
  
  return menu;
}

Layout* newLayout(const Rect& rect)
{
  const auto layout = Layout::create();
  layout->setLayoutType(Layout::Type::RELATIVE);
  layout->setContentSize(rect.size);
  layout->setPosition(rect.origin);
  
  layout->addChild(newBackground());
  layout->addChild(newTitle());
  layout->addChild(newMenu(rect));
  
  return layout;
}
}

bool MainMenuScene::init()
{
  if (!Scene::init())
  {
    return false;
  }
  
  const auto safeAreaRect = _director->getSafeAreaRect();
  
  const auto layout = newLayout(safeAreaRect);
  
  this->addChild(layout);
  
  return true;
}
