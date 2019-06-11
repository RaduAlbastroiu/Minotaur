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

  // set keyboard
  keyboardListener = new KeyboardListener();
  auto eventKeyboardListener = keyboardListener->initKeyboard();
  Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventKeyboardListener, this);

  // set private members
  mDirector = Director::getInstance();
  mWindow.width = mDirector->getVisibleSize().width;
  mWindow.height = mDirector->getVisibleSize().height;

  AddBackground();
  
  this->scheduleUpdate();

  mEnemiesCollection = EnemiesCollection();
  mHero = new Hero(this, &mEnemiesCollection, keyboardListener);
  mEnemiesCollection.SetHero(mHero);

  mScoreLabel = Label::createWithSystemFont("Killed: 0", "Arial", 50);
  mScoreLabel->setPosition(Director::getInstance()->getVisibleSize().width / 10 * 9, Director::getInstance()->getVisibleSize().height / 1.07);
  mScoreLabel->setTextColor(cocos2d::Color4B::BLACK);
  this->addChild(mScoreLabel);

  return true;
}

void HelloWorld::AddBackground()
{
  for (int i = 0; i < 3; i++)
  {
    for (int j = 0; j < 2; j++)
    {
      cocos2d::Sprite* background = Sprite::create("grass.png");
      if (background != nullptr)
      {
        background->setAnchorPoint(Vec2(0, 0));
        background->setPosition(Vec2(1024 * i, 1024 * j));
        this->addChild(background);
      }
    }
  }
}

void HelloWorld::update(float delta)
{
  mTimePassed += delta;

  if (isHeroDead == false && mHero->IsAlive() == false)
  {
    isHeroDead = true;
    mTimeHeroDead = mTimePassed;
  }

  // reset
  if (isHeroDead && mTimePassed - mTimeHeroDead > 2.5f)
  {
    if (mResetLabel == nullptr)
    {
      mResetLabel = Label::createWithSystemFont("Press any key to play again!", "Arial", 40);
      mResetLabel->setAnchorPoint(Vec2(0.5, 0.5));
      mResetLabel->setPosition(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 4 * 3);
      mResetLabel->setTextColor(cocos2d::Color4B::BLACK);
      this->addChild(mResetLabel, 100);
    }
    //if (isKeyboardPressed)
    //{
    //  Reset();
    //}
  }

  // spawn
  if (mTimePassed - mTimeLastSpawn > mTimeBetweenSpawns && mHero->IsAlive())
  {
    mTimeLastSpawn = mTimePassed;
    const int width = mDirector->getVisibleSize().width;
    const int height = mDirector->getVisibleSize().height;

    float X = 0;
    float Y = 0;

    const int direction = rand() % 4;
    if (direction == 0)
    {
      X = -50;
      Y = rand() % height;
    }
    if (direction == 1)
    {
      X = rand() % width;
      Y = height + 50;
    }
    if (direction == 2)
    {
      X = width + 50;
      Y = rand() % height;
    }
    if (direction == 3)
    {
      X = rand() % width;
      Y = -50;
    }

    mEnemiesCollection.AddEnemy(this, X, Y);
  }

  if (mTimePassed - mTimeLastUpdate > mTimeUpdateLevel && mHero->IsAlive())
  {
    mTimeLastUpdate = mTimePassed;
    mTimeBetweenSpawns = mTimeBetweenSpawns * mDifficultyRateIncrease;
  }

  const int killed = mEnemiesCollection.GetNumberKilled();
  mScoreLabel->setString("Killed: " + to_string(killed));

  mHero->Update(delta);
  mEnemiesCollection.Update(delta);
}

void HelloWorld::Reset()
{
  // set environment
  mTimePassed = 0;
  lastSecond = 0;
  currentMinotaur = 0;
  maxMinotaur = 9;
  minotaurLine = 3;

  mTimeLastSpawn = -0.5f;
  mTimeBetweenSpawns = 2.5f;
  mTimeLastUpdate = 1.0f;
  mTimeUpdateLevel = 5.0f;
  isHeroDead = false;
  mTimeHeroDead = -0.5f;

  mEnemiesCollection.Reset();
  mHero->Reset();
  mResetLabel->removeFromParent();
  isHeroDead = false;
  this->removeAllChildren();
  init();
}
