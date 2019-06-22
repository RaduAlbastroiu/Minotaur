#pragma once

#include "cocos2d.h"
#include "Includes.h"
#include "Character.h"
#include "KeyboardListener.h"

class EnemiesCollection;

class Hero : public Character
{
public:
  Hero(EnemiesCollection* aEnemiesCollection, KeyboardListener* aKeyboardListener);

  void Attack() override;
  void Reset();
  void Update(float delta) override;
  void GetKeyboardInput();
  void TakeDamage(int damage) override;
  int GetHealth();

  cocos2d::Sprite* GetSprite();

protected:

  bool CanMoveAt(float currentX, float currentY, float X, float Y);

  KeyboardListener* keyboardListener;

  void Init();
  void RunAnimation(vector<string>& aAnimSprites, int aNrRuns, float aFrecv);


  // Inherited via Character
  virtual void RunAttackAnimation() override;

  virtual void RunIdleAnimation() override;

  virtual void RunMoveAnimation() override;

  virtual void RunHitAnimation() override;

  virtual void RunDeadAnimation() override;

  void MovePosition();

  int mDirection = 0;

  EnemiesCollection* mEnemiesCollection;

  float mSpeed = 6;

  vector<string> mHeroAttack = { "MinotaurAttack_0.png",
  "MinotaurAttack_1.png" ,
  "MinotaurAttack_2.png" ,
  "MinotaurAttack_3.png" ,
  "MinotaurAttack_4.png" ,
  "MinotaurAttack_5.png" ,
  "MinotaurAttack_6.png" ,
  "MinotaurAttack_7.png" ,
  "MinotaurAttack_8.png" };

  vector<string> mHeroIdle = { "MinotaurIdle_0.png",
  "MinotaurIdle_1.png" ,
  "MinotaurIdle_2.png" ,
  "MinotaurIdle_3.png" ,
  "MinotaurIdle_4.png" };

  vector<string> mHeroDead = { "MinotaurDead_0.png",
  "MinotaurDead_1.png" ,
  "MinotaurDead_2.png" ,
  "MinotaurDead_3.png" ,
  "MinotaurDead_4.png" ,
  "MinotaurDead_5.png" };

  vector<string> mHeroMove = { "MinotaurMove_0.png",
  "MinotaurMove_1.png" ,
  "MinotaurMove_2.png" ,
  "MinotaurMove_3.png" ,
  "MinotaurMove_4.png" ,
  "MinotaurMove_5.png" ,
  "MinotaurMove_6.png" ,
  "MinotaurMove_7.png" };

};
