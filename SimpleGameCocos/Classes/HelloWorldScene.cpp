/****************************************************************************
 Copyright (c) 2017-2018 Xiamen Yaji Software Co., Ltd.
 
 http://www.cocos2d-x.org
 
 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in
 all copies or substantial portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 THE SOFTWARE.
 ****************************************************************************/

#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
  // 'scene' is an autorelease object
  auto scene = Scene::create();
  auto layer = HelloWorld::create();

  scene->addChild(layer);

  return scene;
}

bool HelloWorld::init()
{
  if (!Scene::init())
  {
    return false;
  }

  // set private members
  mDirector = Director::getInstance();
  mWindow.width = mDirector->getVisibleSize().width;
  mWindow.height = mDirector->getVisibleSize().height;

  AddBackground();
  //AddHelloWorld();
  AddCharacter();

  return true;
}

void HelloWorld::AddHelloWorld()
{
  auto label = Label::createWithSystemFont("Hello World", "Arial", 96);
  label->setAnchorPoint(cocos2d::Vec2(0.5, 0.5));
  label->setPosition(cocos2d::Vec2(mWindow.width / 2, mWindow.height / 2));

  this->addChild(label, 1);
}

void HelloWorld::AddBackground()
{
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      cocos2d::Sprite* background = Sprite::create("grass.png");
      background->setAnchorPoint(Vec2(0, 0));
      background->setPosition(Vec2(1024 * i, 1024 * j));
      this->addChild(background);
    }
  }
}

void HelloWorld::AddCharacter()
{
  // sprite
  auto frames = getAnimation("minotaur.png", 8);
  auto sprite = Sprite::createWithSpriteFrame(frames.front());
  background->addChild(sprite);
  sprite->setPosition(100, 620);

  auto animation = Animation::createWithSpriteFrames(frames, 1.0f / 8);
  sprite->runAction(RepeatForever::create(Animate::create(animation)));
}

Vector HelloWorld::getAnimation(const char *format, int count)
{
  auto spritecache = SpriteFrameCache::getInstance();
  Vector animFrames;
  char str[100];
  for (int i = 1; i <= count; i++)
  {
    sprintf(str, format, i);
    animFrames.pushBack(spritecache->getSpriteFrameByName(str));
  }
  return animFrames;
}