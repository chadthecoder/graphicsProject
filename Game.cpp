#include "Game.hpp"
#include <iostream>
//using namespace std;

Game::Game() : mIsRunning(true), mTicksCount(0), mBallVel(-200.0f, 235.0f) {}

bool Game::Initialize()
{
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
  {
    SDL_Log("Error: %s", SDL_GetError());
    return false;
  }

  SDL_GetCurrentDisplayMode(0, &this->DM);
  this->screenHeight = this->DM.h;
  this->screenWidth = this->DM.w;
  this->thickness = this->screenWidth / 100;
  this->paddleHeight = this->thickness * 6;
  this->paddleU.height = paddleHeight;
  this->paddleWidth = this->thickness;
  this->paddleU.width = this->paddleWidth;

/* Making it fullscreen only is the only non complicated way   *
 * to make it look good on Ubuntu because of Ubuntu's top bar. */
  this->mWindow = SDL_CreateWindow(
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
  }

  mBallPos.x = this->screenWidth / 2;
  mBallPos.y = this->screenHeight / 2;

  paddleU.x = this->screenWidth / 16;
  paddleU.y = this->screenHeight / 2;

  InitializeObjects();

  return true;
}

void Game::InitializeObjects()
{
  this->funny = this->createPaddle(
  400.0f,//static_cast<int>(paddleU.x - this->thickness / 2),
  400.0f,//static_cast<int>(paddleU.y - this->thickness / 2),
  this->paddleWidth,
  this->paddleHeight,
  0
  );
}

void Game::Shutdown()
{
  SDL_DestroyRenderer(mRenderer);
  SDL_DestroyWindow(mWindow);
  SDL_Quit();
}

void Game::RunLoop()
{
  while (this->mIsRunning)
  {
    this->ProcessInput();
    this->UpdateGame();
    this->GenerateOutput();
  }
}

void Game::ProcessInput()
{
  while (SDL_PollEvent(&this->event))
  {
    switch (this->event.type)
    {
    case SDL_QUIT:
      mIsRunning = false;
      break;
    }
  }

    const Uint8 *state = SDL_GetKeyboardState(NULL);
    std::cout << state[SDL_SCANCODE_ESCAPE];
    if (state[SDL_SCANCODE_ESCAPE])
    {
      mIsRunning = false;
    }

    //paddle direction
    this->paddleU.direction = 0;
    if (state[SDL_SCANCODE_W])
    {
      this->paddleU.direction -= 1;
    }

    if (state[SDL_SCANCODE_S])
    {
      this->paddleU.direction += 1;
    }
}

void Game::UpdateGame()
{
  while (!SDL_TICKS_PASSED(SDL_GetTicks(), this->mTicksCount + 16))
    ;

  this->deltaTime = (SDL_GetTicks() - this->mTicksCount);
  this->mTicksCount = SDL_GetTicks();
  if (this->deltaTime > 0.05f)
  {
    this->deltaTime = 0.05f;
  }

  //update objects using deltaTime
  this->mBallPos.x += 50 * this->deltaTime;

  if (this->paddleU.direction != 0)
  {
    if(this->paddleU.y < this->thickness)
    {
      this->paddleU.y = this->thickness;
    }
    else if(this->paddleU.y > (this->screenHeight - this->thickness - this->paddleU.height))
    {
      this->paddleU.y = this->screenHeight - this->thickness - this->paddleU.height;
    }
    this->paddleU.y += this->paddleU.direction * 300.0f * this->deltaTime;
    //std::cout << paddleU.y << std::endl;
  }
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
    SDL_Rect rectMPaddle{
        static_cast<int>(mPaddle.x - this->thickness / 2),
        static_cast<int>(mPaddle.y - this->thickness / 2),
        mPaddle.width,
        mPaddle.height};
    SDL_RenderFillRect(this->mRenderer, &rectMPaddle);
  }

  SDL_Rect Game::createPaddleU()
  {
      SDL_Rect myPaddle{
        static_cast<int>(paddleU.x - this->thickness / 2),
        static_cast<int>(paddleU.y - this->thickness / 2),
        this->paddleU.width,
        this->paddleU.height};
      return myPaddle;
  }
  void Game::drawPaddleU(SDL_Rect myPaddle)
  {
    SDL_RenderFillRect(this->mRenderer, &myPaddle);
  }

void Game::GenerateOutput()
{
  //renderer, rgba; black
  SDL_SetRenderDrawColor(
      this->mRenderer,
      0,
      0,
      0,
      255);

  //draw scene

  //background
  SDL_RenderClear(this->mRenderer);

  //white for walls
  SDL_SetRenderDrawColor(
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
  SDL_RenderFillRect(this->mRenderer, &wall_bottom);

  SDL_Rect ball{
      static_cast<int>(mBallPos.x - this->thickness / 2),
      static_cast<int>(mBallPos.y - this->thickness / 2),
      this->thickness,
      this->thickness};
  SDL_RenderFillRect(this->mRenderer, &ball);


  SDL_Rect myPaddle = this->createPaddleU();
  this->drawPaddleU(myPaddle);

  
  this->funny.x += 5;
  this->drawPaddle(this->funny);

  SDL_RenderPresent(this->mRenderer);
}
