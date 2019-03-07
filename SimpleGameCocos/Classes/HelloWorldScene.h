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

#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__
#pragma once
#include "cocos2d.h"
#include "Hero.h"

class HelloWorld : public cocos2d::Scene
{
public:
  static cocos2d::Scene* createScene();
  virtual bool init();

  void AddHelloWorld();
  void AddBackground();
  void AddCharacter();
  void update(float delta) override;

  CREATE_FUNC(HelloWorld);

  cocos2d::Vector<SpriteFrame *> getAnimation(int count);

private:

  float elapsedTime = 0;
  float lastSecond = 0;
  int currentMinotaur = 0;
  int maxMinotaur = 9;
  int minotaurLine = 3;

  cocos2d::Sprite* aHero;
  cocos2d::Animation* AttackAnimation;

  vector<string> str = { "MinotaurAttack_0.png", 
  "MinotaurAttack_1.png" 
  "MinotaurAttack_2.png" 
  "MinotaurAttack_3.png" 
  "MinotaurAttack_4.png" 
  "MinotaurAttack_5.png" 
  "MinotaurAttack_6.png" 
  "MinotaurAttack_7.png" 
  "MinotaurAttack_8.png" };

  //Hero mHero;

  cocos2d::Director* mDirector;

  cocos2d::Sprite* minotaur;
  cocos2d::Sprite* lastSprite = nullptr;

  struct WindowSize
  {
    int height;
    int width;
  }mWindow;
};

#endif // __HELLOWORLD_SCENE_H__
