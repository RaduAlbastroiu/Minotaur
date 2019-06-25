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
#include "HealthLabel.h"
#include "Updater.h"

class MainScene : public cocos2d::Scene
{
public:
  static cocos2d::Scene* createScene();
  virtual bool init();

  
  void update(float delta) override;

  CREATE_FUNC(MainScene);

private:

  void InitUpdater();
  void InitKeyboardListener();
  void InitHealthLabel();
  void InitBackground();
  void InitEnemiesCollectionAndHero();
  void InitScoreLabel();

  float mTimePassed = 0;
  float lastSecond = 0;
  int currentMinotaur = 0;
  int maxMinotaur = 9;
  int minotaurLine = 3;

  float mTimeLastSpawn = -0.5f;
  float mTimeBetweenSpawns = 1.0f;
  float mTimeLastUpdate = 1.0f;
  float mTimeUpdateLevel = 5.0f;
  float mDifficultyRateIncrease = 0.5;
  bool isHeroDead = false;
  float mTimeHeroDead = -0.5f;

  cocos2d::Label* mScoreLabel;

  unique_ptr<Hero> mHero;
  unique_ptr<EnemiesCollection> mEnemiesCollection;
  unique_ptr<KeyboardListener> keyboardListener;
  unique_ptr<HealthBar> healthLabel;
  unique_ptr<Updater> updater;
};
