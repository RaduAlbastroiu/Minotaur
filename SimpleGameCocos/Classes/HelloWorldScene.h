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

#pragma once

#include "cocos2d.h"
#include "EnemiesCollection.h"
#include "Hero.h"

class HelloWorld : public cocos2d::Scene
{
public:
  static cocos2d::Scene* createScene();
  virtual bool init();

  void AddBackground();
  void update(float delta) override;
  void Reset();

  CREATE_FUNC(HelloWorld);

private:

  float mTimePassed = 0;
  float lastSecond = 0;
  int currentMinotaur = 0;
  int maxMinotaur = 9;
  int minotaurLine = 3;

  float mTimeLastSpawn = -0.5f;
  float mTimeBetweenSpawns = 1.0f;
  float mTimeLastUpdate = 1.0f;
  float mTimeUpdateLevel = 5.0f;
  float mDifficultyRateIncrease = 0.7;
  bool isHeroDead = false;
  float mTimeHeroDead = -0.5f;

  KeyboardListener* keyboardListener;

  cocos2d::Label* mScoreLabel;
  cocos2d::Label* mResetLabel;

  Hero* mHero;
  EnemiesCollection mEnemiesCollection;

  cocos2d::Sprite* aHero;
  cocos2d::Director* mDirector;

  struct WindowSize
  {
    int height;
    int width;
  }mWindow;
};
