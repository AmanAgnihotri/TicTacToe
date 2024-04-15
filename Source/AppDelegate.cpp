#include "AppDelegate.h"
#include "SplashScene.h"

namespace
{
const Size designSize{720, 1280};
const Size smallSize{320, 480};
const Size mediumSize{768, 1024};
const Size largeSize{1536, 2048};

Size getRelevantSize(Vec2 frameSize)
{
  if (frameSize.height > mediumSize.height)
  {
    return largeSize;
  }
  
  if (frameSize.height > smallSize.height)
  {
    return mediumSize;
  }
  
  return smallSize;
}

float getContentScaleFactor(Vec2 frameSize)
{
  Size size = getRelevantSize(frameSize);
  
  return MIN(size.height / designSize.height, size.width / designSize.width);
}
}

bool AppDelegate::applicationDidFinishLaunching()
{
  auto director = Director::getInstance();
  director->setAnimationInterval(1 / 30.0f);
  
  auto view = GLViewImpl::create("TicTacToe");
  director->setGLView(view);
  
  using enum ResolutionPolicy;
  view->setDesignResolutionSize(designSize.width, designSize.height, SHOW_ALL);
  
  auto frameSize = view->getFrameSize();
  
  auto scaleFactor = getContentScaleFactor(frameSize);
  director->setContentScaleFactor(scaleFactor);
  
  auto scene = SplashScene::create();
  director->runWithScene(scene);
  
  return true;
}

void AppDelegate::applicationDidEnterBackground()
{
  Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground()
{
  Director::getInstance()->startAnimation();
}
