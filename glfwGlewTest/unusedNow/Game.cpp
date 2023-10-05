#include "Game.hpp"
#include <iostream>
// using namespace std;

// SDL_Texture *zText;

// Game::Game() : mIsRunning(true), mTicksCount(0), gameBall(1500.0f, 500.0f, -100.0f, 117.5f, 15, 15), leftPoints(0), rightPoints(0) {}

void Game::centerVector2(Vector2 vec)
{
  vec.x = this->screenWidth / 2;
  vec.y = this->screenHeight / 2;
}

bool Game::Initialize()
{
  /*if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    SDL_Log("Error: %s", SDL_GetError());
    return false;
  }

  SDL_GetCurrentDisplayMode(0, &this->DM);
  this->screenHeight = this->DM.h;
  this->screenWidth = this->DM.w;*/
  this->thickness = this->screenWidth / 100;
  this->paddleHeight = this->thickness * 6;
  this->paddleU.height = paddleHeight;
  this->paddleWidth = this->thickness;
  this->paddleU.width = this->paddleWidth;

  /* Making it fullscreen only is the only non complicated way   *
   * to make it look good on Ubuntu because of Ubuntu's top bar. */
  /*   this->mWindow = SDL_CreateWindow(
        "Chapter 1",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        this->screenWidth,
        this->screenHeight,
        SDL_WINDOW_FULLSCREEN);

    if (!this->mWindow)
    {
      SDL_Log("Error: %s", SDL_GetError());
      return false;
    }

    mRenderer = SDL_CreateRenderer(
        this->mWindow,
        -1,
        SDL_RENDERER_ACCELERATED || SDL_RENDERER_PRESENTVSYNC);

    if (!mRenderer)
    {
      SDL_Log("Failed to create renderer: %s", SDL_GetError());
      return false;
    } */

  // mBallPos.x = this->screenWidth / 2;
  // mBallPos.y = this->screenHeight / 2;
  // this->centerVector2(this->mBallPos);
  gameBall.x = this->screenWidth / 2;
  gameBall.y = this->screenHeight / 2;

  paddleU.x = this->screenWidth / 16;
  paddleU.y = this->screenHeight / 2;

  // funny.x = this->screenWidth * 15 / 16;
  // funny.y = this->screenHeight / 2;

  // keep this and remove initalize objects function?
  this->funny = this->createPaddle(
      this->screenWidth * 15 / 16, // static_cast<int>(paddleU.x - this->thickness / 2),
      this->screenHeight / 2,      // static_cast<int>(paddleU.y - this->thickness / 2),
      this->paddleU.width,
      this->paddleU.height,
      0);

  // scorekeeper?

  return true;
}

void Game::Shutdown()
{
  /*   SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit(); */
}

void Game::RunLoop()
{
  while (this->mIsRunning)
  {
    this->ProcessInput();
    if (!this->UpdateGame())
    {
      break;
    }
    this->GenerateOutput();
  }
}

void Game::UpdateScore()
{
  // this->leftPoints, this->rightPoints
  /*   SDL_Surface *zSurface = IMG_Load("assets/zero.png");
    zText = SDL_CreateTextureFromSurface(mRenderer, zSurface);
    SDL_FreeSurface(zSurface); */
}

void Game::ProcessInput()
{
  /*   while (SDL_PollEvent(&this->event))
    {
      switch (this->event.type)
      {
      case SDL_QUIT:
        mIsRunning = false;
        break;
      }
    } */

  /*  const Uint8 *state = SDL_GetKeyboardState(NULL);

   if (state[SDL_SCANCODE_ESCAPE])
   {
     mIsRunning = false;
   } */

  // paddle direction
  /*  this->paddleU.direction = 0;
   if (state[SDL_SCANCODE_W])
   {
     this->paddleU.direction -= 1;
   }

   if (state[SDL_SCANCODE_S])
   {
     this->paddleU.direction += 1;
   } */

  // paddle2, funny
  /*  this->funny.direction = 0;
   if (state[SDL_SCANCODE_I])
   {
     this->funny.direction -= 1;
   }

   if (state[SDL_SCANCODE_K])
   {
     this->funny.direction += 1;
   } */
}

bool Game::UpdateGame()
{
  /*  while (!SDL_TICKS_PASSED(SDL_GetTicks(), this->mTicksCount + 16))
     ;

   this->deltaTime = (SDL_GetTicks() - this->mTicksCount);
   this->mTicksCount = SDL_GetTicks();
   if (this->deltaTime > 0.05f)
   {
     this->deltaTime = 0.05f;
   } */

  // if paddle hits sides of screen
  if ((gameBall.y >= (this->screenHeight - this->thickness)) && (gameBall.yVelocity > 0.0f))
  {
    gameBall.yVelocity *= -1;
  }
  else if ((gameBall.y <= this->thickness) && (gameBall.yVelocity < 0.0f))
  {
    gameBall.yVelocity *= -1;
  }
  else if ((gameBall.x <= this->thickness) && (gameBall.xVelocity < 0.0f))
  {
    this->rightPoints += 1;
    gameBall.x = this->screenWidth / 2;
    gameBall.y = this->screenHeight / 2;
    // gameBall.xVelocity *= -1;
  }
  else if ((gameBall.x >= (this->screenWidth - this->thickness)) && (gameBall.xVelocity > 0.0f))
  {
    this->leftPoints += 1;
    gameBall.x = this->screenWidth / 2;
    gameBall.y = this->screenHeight / 2;
    // gameBall.xVelocity *= -1;
  }

  if (this->leftPoints == 7)
  {
    std::cout << "The left side wins!\n";
    /*
      Doesn't do anything right now since returning false stops loop, but could be used in the future.
      this->mIsRunning = false;
    */
    return false;
  }

  if (this->rightPoints == 7)
  {
    std::cout << "The right side wins!\n";
    /*
      Doesn't do anything right now since returning false stops loop, but could be used in the future.
      this->mIsRunning = false;
    */
    return false;
  }

  // update objects using deltaTime
  this->gameBall.x += gameBall.xVelocity * this->deltaTime;
  this->gameBall.y += gameBall.yVelocity * this->deltaTime;

  if (this->paddleU.direction != 0)
  {
    if (this->paddleU.y < this->thickness)
    {
      this->paddleU.y = this->thickness;
    }
    else if (this->paddleU.y > (this->screenHeight - this->thickness - this->paddleU.height))
    {
      this->paddleU.y = this->screenHeight - this->thickness - this->paddleU.height;
    }
    this->paddleU.y += this->paddleU.direction * 300.0f * this->deltaTime;
  }

  if (this->funny.direction != 0)
  {
    if (this->funny.y < this->thickness)
    {
      this->funny.y = this->thickness;
    }
    else if (this->funny.y > (this->screenHeight - this->thickness - this->funny.height))
    {
      this->funny.y = this->screenHeight - this->thickness - this->funny.height;
    }
    this->funny.y += this->funny.direction * 300.0f * this->deltaTime;
  }

  if (gameBall.collidesWith(paddleU))
  {
    // gameBall.xVelocity *= -1;
  }

  if (gameBall.collidesWith(funny))
  {
    // gameBall.xVelocity *= -1;
  }

  this->UpdateScore();

  return true;
}

Paddle Game::createPaddle(float xq, float yq, int widthq, int heightq, int directionq)
{
  Paddle mPaddle;
  mPaddle.x = xq;
  mPaddle.y = yq;
  mPaddle.width = widthq;
  mPaddle.height = heightq;
  mPaddle.direction = directionq;
  return mPaddle;
}

void Game::drawPaddle(Paddle mPaddle)
{
  /*   SDL_Rect rectMPaddle{
        static_cast<int>(mPaddle.x - (mPaddle.width / 2.0f)),
        static_cast<int>(mPaddle.y - (mPaddle.height / 2.0f)),
        mPaddle.width,
        mPaddle.height};
    SDL_RenderFillRect(this->mRenderer, &rectMPaddle); */
}

/* SDL_Rect Game::createPaddleU()
{
  SDL_Rect myPaddle{
      static_cast<int>(paddleU.x - (paddleU.width / 2.0f)),
      static_cast<int>(paddleU.y - (paddleU.height / 2.0f)),
      this->paddleU.width,
      this->paddleU.height};
  return myPaddle;
}
void Game::drawPaddleU(SDL_Rect myPaddle)
{
  SDL_RenderFillRect(this->mRenderer, &myPaddle);
} */

void Game::GenerateOutput()
{
  // renderer, rgba; black
  /*  SDL_SetRenderDrawColor(
       this->mRenderer,
       0,
       0,
       0,
       255); */

  // draw scene

  // background
  /*  SDL_RenderClear(this->mRenderer); */

  // white for walls
  /*  SDL_SetRenderDrawColor(
       this->mRenderer,
       255,
       255,
       255,
       255);
   SDL_Rect wall_left{
       0,
       0,
       this->thickness,
       this->screenHeight};
   SDL_Rect wall_right{
       this->screenWidth - (this->thickness),
       0,
       this->thickness,
       this->screenHeight};
   SDL_Rect wall_top{
       0,
       0,
       this->screenWidth,
       this->thickness};
   SDL_Rect wall_bottom{
       0,
       this->screenHeight - (this->thickness),
       this->screenWidth,
       this->thickness};
   SDL_RenderFillRect(this->mRenderer, &wall_left);
   SDL_RenderFillRect(this->mRenderer, &wall_right);
   SDL_RenderFillRect(this->mRenderer, &wall_top);
   SDL_RenderFillRect(this->mRenderer, &wall_bottom); */

  // create sdl rect for ball
  /*   SDL_Rect ball{
        static_cast<int>(gameBall.x - (gameBall.width / 2.0f)),
        static_cast<int>(gameBall.y - (gameBall.height / 2.0f)),
        gameBall.width,
        gameBall.height};
    // fill sdl rect info into render
    SDL_RenderFillRect(this->mRenderer, &ball); */

  /*//sdl drawing test
  SDL_Rect ball2{
      static_cast<int>(0),
      static_cast<int>(0),
      100,
      100};
  SDL_RenderFillRect(this->mRenderer, &ball2);
  */

  /*  SDL_Rect myPaddle = this->createPaddleU();
   this->drawPaddleU(myPaddle); */

  // this->funny.x += 5;
  /*   this->drawPaddle(this->funny);

    SDL_RenderCopy(mRenderer, zText, NULL, NULL);

    SDL_RenderPresent(this->mRenderer); */
}
