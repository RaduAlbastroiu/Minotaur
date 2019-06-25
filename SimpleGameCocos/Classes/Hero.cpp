
#include "Hero.h"
#include "EnemiesCollection.h"

Hero::Hero(Updater* updater, EnemiesCollection* aEnemiesCollection, KeyboardListener* aKeyboardListener, HealthBar* aHealthBar)
  : Character(updater)
{
  mEnemiesCollection = aEnemiesCollection;
  keyboardListener = aKeyboardListener;
  healthBar = aHealthBar;

  Init();
}

void Hero::Init()
{
  mDirection = NODIRECTION;
  currentState = internalState::idle;

  SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Minotaur.plist");

  characterSprite = Sprite::create("MinotaurFirst.png");

  auto X = Director::getInstance()->getVisibleSize().width / 2;
  auto Y = Director::getInstance()->getVisibleSize().height / 2;
  
  characterSprite->setPosition(Vec2(X, Y));
  characterSprite->setScale(3);
  characterSprite->setAnchorPoint(Vec2(0.5, 0.5));

  RunAnimation(mHeroIdle, 1000, 0.15f);
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
  lastAction = action;
  characterSprite->runAction(action);
}

// move in the mDirection
void Hero::MovePosition()
{
  auto direction = Vec2(0, 0);
  float X = characterSprite->getPositionX();
  float Y = characterSprite->getPositionY();

  switch (mDirection)
  {
  case LEFT:
    direction = Vec2(-1 * mSpeed, 0);
    X += -1 * mSpeed;
    break;

  case RIGHT:
    direction = Vec2(1 * mSpeed, 0);
    X += mSpeed;
    break;

  case UP:
    direction = Vec2(0, 1 * mSpeed);
    Y += mSpeed;
    break;

  case DOWN:
    direction = Vec2(0, -1 * mSpeed);
    Y -= mSpeed;
    break;
  }
  
  if (CanMoveAt(characterSprite->getPositionX(), characterSprite->getPositionY(), X, Y))
  {
    auto moveBy = MoveBy::create(0.01667f, direction);
    characterSprite->runAction(moveBy);
  }
}

void Hero::RunAttackAnimation()
{
  RunAnimation(mHeroAttack, 1000, 0.045f);
}

void Hero::RunIdleAnimation()
{
  RunAnimation(mHeroIdle, 1000, 0.15f);
}

void Hero::RunMoveAnimation()
{
  RunAnimation(mHeroMove, 1000, 0.065f);
}

void Hero::RunHitAnimation()
{
}

void Hero::RunDeadAnimation()
{
  RunAnimation(mHeroDead, 1, 0.1f);
}

void Hero::Attack()
{
  if (currentState != internalState::attack && currentState != internalState::dead)
  {
    timeAttackStart = timePassed;
    mEnemiesCollection->AttackCollection();
    ChangeState(internalState::attack);
  }
}

void Hero::Reset()
{
  Init();
  health = 100;
  currentState = internalState::idle;
}

void Hero::DoUpdate(float delta)
{
  timePassed += delta;
  GetKeyboardInput();

  // change direction
  if (health > 0)
  {
    if (mDirection == LEFT)
      characterSprite->setFlippedX(true);
    if (mDirection == RIGHT)
      characterSprite->setFlippedX(false);
  }

  // change position relative to framerate
  if (currentState == internalState::move)
  {
    MovePosition();
  }

  // change between walking and idling
  if (mDirection != NODIRECTION && currentState == internalState::idle)
  {
    ChangeState(internalState::move);
  }

  if (mDirection == NODIRECTION && currentState == internalState::move)
  {
    ChangeState(internalState::idle);
  }

  // change between attack and idle
  if (currentState == internalState::attack && timePassed - timeAttackStart > 0.6f)
  {
    ChangeState(internalState::idle);
  }

  // update health 
  if (health <= 0 && currentState != internalState::dead)
  {
    ChangeState(internalState::dead);
  }

  // after hit go back to idle
  if (currentState == internalState::hit && timePassed - timeHitStart < 0.5f)
  {
    ChangeState(internalState::idle);
  }
}

void Hero::GetKeyboardInput()
{
  mDirection = keyboardListener->GetMoveDirection();
  if (keyboardListener->GetAttackStatus())
    Attack();
}

void Hero::TakeDamage(int damage)
{
  health -= damage;
  health = max(0, health);
  healthBar->UpdateValue(health);
}

int Hero::GetHealth()
{
  return health;
}

cocos2d::Sprite* Hero::GetSprite()
{
  return characterSprite;
}

bool Hero::CanMoveAt(float currentX, float currentY, float X, float Y)
{
  const auto width = Director::getInstance()->getVisibleSize().width;
  const auto height = Director::getInstance()->getVisibleSize().height;

  // left margin
  if (X < currentX && X < 25)
  {
    return false;
  }
  // right margin
  if (X > currentX && X > width - 25)
  {
    return false;
  }
  // top
  if (Y > currentY && Y > height - 25)
  {
    return false;
  }
  // bottom
  if (Y < currentY && Y < 25)
  {
    return false;
  }

  return true;
}
