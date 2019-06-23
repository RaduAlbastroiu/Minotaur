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

#include "MainScene.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
  // 'scene' is an autorelease object
  auto scene = Scene::create();
  auto layer = MainScene::create();

  scene->addChild(layer);

  return scene;
}

bool MainScene::init()
{
  if (!Scene::init())
  {
    return false;
  }

  InitUpdater();
  InitKeyboardListener();
  InitHealthLabel();
  InitBackground();
  InitEnemiesCollectionAndHero();
  InitScoreLabel();

  this->scheduleUpdate();

  return true;
}

void MainScene::InitBackground()
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

void MainScene::InitEnemiesCollectionAndHero()
{
  // create enemy collection
  mEnemiesCollection = make_unique<EnemiesCollection>(updater.get());
  mHero = make_unique<Hero>(updater.get(), mEnemiesCollection.get(), keyboardListener.get());
  auto heroSprite = mHero->GetSprite();
  this->addChild(heroSprite, 10);
  mEnemiesCollection->SetHero(mHero.get());
}

void MainScene::InitScoreLabel()
{
  // add score label
  mScoreLabel = Label::createWithSystemFont("Killed: 0", "Arial", 50);
  mScoreLabel->setPosition(Director::getInstance()->getVisibleSize().width / 10 * 9, Director::getInstance()->getVisibleSize().height / 1.07);
  mScoreLabel->setTextColor(cocos2d::Color4B::BLACK);
  this->addChild(mScoreLabel);
}

void MainScene::update(float delta)
{
  mTimePassed += delta;

  // update health label
  healthLabel->UpdateValue(mHero->GetHealth());

  if (isHeroDead == false && mHero->IsAlive() == false)
  {
    isHeroDead = true;
    mTimeHeroDead = mTimePassed;
  }

  if (mTimePassed - mTimeHeroDead > 1.0f && isHeroDead == true)
  {
    auto gameOverLabel = Label::createWithSystemFont("Game Over", "Arial", 60);
    gameOverLabel->setAnchorPoint(Vec2(0.5, 0.5));
    gameOverLabel->setPosition(Director::getInstance()->getVisibleSize().width / 2, Director::getInstance()->getVisibleSize().height / 4 * 3);
    gameOverLabel->setTextColor(cocos2d::Color4B::BLACK);
    this->addChild(gameOverLabel, 100);
  }

  // spawn
  if (mTimePassed - mTimeLastSpawn > mTimeBetweenSpawns && mHero->IsAlive())
  {
    mTimeLastSpawn = mTimePassed;
    const int width = Director::getInstance()->getVisibleSize().width;
    const int height = Director::getInstance()->getVisibleSize().height;

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

    mEnemiesCollection->AddEnemy(this, X, Y);
  }

  if (mTimePassed - mTimeLastUpdate > mTimeUpdateLevel && mHero->IsAlive())
  {
    mTimeLastUpdate = mTimePassed;
    mTimeBetweenSpawns = mTimeBetweenSpawns * mDifficultyRateIncrease;
  }

  const int killed = mEnemiesCollection->GetNumberKilled();
  mScoreLabel->setString("Killed: " + to_string(killed));

  updater->UpdateAll(delta);
}

void MainScene::InitUpdater()
{
  updater = make_unique<Updater>();
}

void MainScene::InitKeyboardListener()
{
  // set keyboard
  keyboardListener = make_unique<KeyboardListener>();
  auto eventKeyboardListener = keyboardListener->initKeyboard();
  Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(eventKeyboardListener, this);
}

void MainScene::InitHealthLabel()
{
  // set healt label
  healthLabel = make_unique<HealthLabel>();
  auto label = healthLabel->GetLabel();
  this->addChild(label, 100);
}
