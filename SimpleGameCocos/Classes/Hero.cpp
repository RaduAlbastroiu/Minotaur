
#include "Hero.h"
#include "EnemiesCollection.h"

Hero::Hero(cocos2d::Scene * scene, EnemiesCollection* aEnemiesCollection, KeyboardListener* aKeyboardListener)
{
  mScene = scene;
  mEnemiesCollection = aEnemiesCollection;
  keyboardListener = aKeyboardListener;

  Init();
}

void Hero::Init()
{
  mCurrentPosition.x = Director::getInstance()->getVisibleSize().width / 2;
  mCurrentPosition.y = Director::getInstance()->getVisibleSize().height / 2;
  mDirection = NODIRECTION;
  mCurrentState = heroState::idle;

  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Minotaur.plist");

  mHealthSprite = cocos2d::Sprite::create("LifeBar/100.png");
  mHealthSprite->setScale(0.5f);
  mHealthSprite->setPosition(Director::getInstance()->getVisibleSize().width / 9, Director::getInstance()->getVisibleSize().height / 1.07);

  mHero = Sprite::create("MinotaurFirst.png");
  mHero->setPosition(Vec2(mCurrentPosition.x, mCurrentPosition.y));
  mHero->setScale(3);
  mHero->setAnchorPoint(Vec2(0.5, 0.5));

  mScene->addChild(mHealthSprite, 100);
  mScene->addChild(mHero, 10);

  RunAnimation(mHeroIdle, 1000, mIdleFrecv);
}

void Hero::RunAnimation(vector<string>& aAnimSprites, int aNrRuns, float aFrecv)
{
  auto spritecache = SpriteFrameCache::getInstance();
  Vector<SpriteFrame *> anim;
  for (int i = 0; i < aAnimSprites.size(); i++)
  {
    anim.pushBack(spritecache->getSpriteFrameByName(aAnimSprites[i]));
  }
  auto animation = Animation::createWithSpriteFrames(anim, aFrecv);
  cocos2d::Action* action = Repeat::create(Animate::create(animation), aNrRuns);
  mLastAction = action;
  mHero->runAction(action);
}

void Hero::ChangeState(heroState newState)
{
  if (mCurrentState == heroState::idle)
  {
    if (newState == heroState::move)
    {
      mCurrentState = heroState::move;
      mHero->stopAction(mLastAction);
      RunAnimation(mHeroMove, 1000, mMoveFrecv);
    }
    if (newState == heroState::attack)
    {
      mCurrentState = heroState::attack;
      mHero->stopAction(mLastAction);
      mAttackTimeStart = mTimePassed;
      RunAnimation(mHeroAttack, 1000, mAttackFrecv);
    }
    if (newState == heroState::dead)
    {
      mCurrentState = heroState::dead;
      mDeadTimeStart = mTimePassed;
      mHero->stopAction(mLastAction);
      RunAnimation(mHeroDead, 1, mDeadFrecv);
    }
  }
  if (mCurrentState == heroState::move)
  {
    if (newState == heroState::idle)
    {
      mCurrentState = heroState::idle;
      mHero->stopAction(mLastAction);
      RunAnimation(mHeroIdle, 1000, mIdleFrecv);
    }
    if (newState == heroState::attack)
    {
      mCurrentState = heroState::attack;
      mHero->stopAction(mLastAction);
      mAttackTimeStart = mTimePassed;
      RunAnimation(mHeroAttack, 1000, mAttackFrecv);
    }
    if (newState == heroState::dead)
    {
      mCurrentState = heroState::dead;
      mDeadTimeStart = mTimePassed;
      mHero->stopAction(mLastAction);
      RunAnimation(mHeroDead, 1, mDeadFrecv);
    }
  }
  if (mCurrentState == heroState::attack)
  {
    if (newState == heroState::idle)
    {
      mCurrentState = heroState::idle;
      mHero->stopAction(mLastAction);
      RunAnimation(mHeroIdle, 1000, mIdleFrecv);
    }
    if (newState == heroState::move)
    {
      mCurrentState = heroState::move;
      mHero->stopAction(mLastAction);
      RunAnimation(mHeroMove, 1000, mMoveFrecv);
    }
    if (newState == heroState::dead)
    {
      mCurrentState = heroState::dead;
      mDeadTimeStart = mTimePassed;
      mHero->stopAction(mLastAction);
      RunAnimation(mHeroDead, 1, mDeadFrecv);
    }
  }
}

void Hero::MovePosition()
{
  auto direction = Vec2(0, 0);
  float X = mHero->getPositionX();
  float Y = mHero->getPositionY();

  if (mDirection == LEFT)
  {
    direction = Vec2(-1 * mSpeed, 0);
    X += -1 * mSpeed;
  }
  if (mDirection == RIGHT)
  {
    direction = Vec2(1 * mSpeed, 0);
    X += mSpeed;
  }
  if (mDirection == UP)
  {
    direction = Vec2(0, 1 * mSpeed);
    Y += mSpeed;
  }
  if (mDirection == DOWN)
  {
    direction = Vec2(0, -1 * mSpeed);
    Y -= mSpeed;
  }
  
  if (mEnemiesCollection->CanMoveAt(mHero->getPositionX(), mHero->getPositionY(), X, Y))
  {
    auto moveBy = MoveBy::create(0.01667f, direction);
    mHero->runAction(moveBy);
  }
}

void Hero::Attack()
{
  if (mCurrentState != heroState::attack && mCurrentState != heroState::dead)
  {
    mAttackTimeStart = mTimePassed;
    mEnemiesCollection->AttackAt(mHero->getPositionX(), mHero->getPositionY(), HERO_ATTACK_RADIUS);
    ChangeState(heroState::attack);
  }
}

void Hero::SetMoveDirection(int direction)
{
  mDirection = direction;
}

void Hero::TakeDamage(int damage)
{
  if (mTimePassed - mHitTimeStart > 1.0f)
  {
    mHealth -= damage;
    mHealth = max(0, mHealth);
    mHealthSprite->setTexture(mLifeBar[mHealth / 10]);
    mHitTimeStart = mTimePassed;
  }
}

bool Hero::IsAlive()
{
  return mHealth > 0;
}

void Hero::Reset()
{
  Init();
  mHealth = 100;
  mCurrentState = heroState::idle;
}

void Hero::Update(float delta)
{
  mTimePassed += delta;
  GetKeyboardInput();

  // change direction
  if (mHealth > 0)
  {
    if (mDirection == LEFT)
      mHero->setFlippedX(true);
    if (mDirection == RIGHT)
      mHero->setFlippedX(false);
  }

  // change position relative to framerate
  if (mCurrentState == heroState::move)
  {
    MovePosition();
  }

  // change between walking and idling
  if (mDirection != NODIRECTION && mCurrentState == heroState::idle)
  {
    ChangeState(heroState::move);
  }

  if (mDirection == NODIRECTION && mCurrentState == heroState::move)
  {
    ChangeState(heroState::idle);
  }

  // change between attack and idle
  if (mCurrentState == heroState::attack && mTimePassed - mAttackTimeStart > 0.3f)
  {
    ChangeState(heroState::idle);
  }

  // update health 
  if (mHealth <= 0 && mCurrentState != heroState::dead)
  {
    ChangeState(heroState::dead);
  }

  if (mCurrentState == heroState::hit && mTimePassed - mHitTimeStart < 0.5f)
  {
    ChangeState(heroState::idle);
  }
}

void Hero::GetKeyboardInput()
{
  SetMoveDirection(keyboardListener->GetMoveDirection());
  if (keyboardListener->GetAttackStatus())
    Attack();
}

pair<float, float> Hero::GetPosition()
{
  pair<float, float> pos;
  pos.first = mHero->getPositionX();
  pos.second = mHero->getPositionY();
  return pos;
}
