#ifndef GAME_H
#define GAME_H

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
#include "libsWin\glew\include\GL\glew.h"
#include "libsWin\glfw\include\GLFW\glfw3.h"
#include "libsWin\SDL2\i686-w64-mingw32\include\SDL2\SDL.h"
#else
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <SDL2/SDL.h>
#endif

#include <string>
#include <iostream>
#include <cmath>

struct Vector2
{
  float x, y;
  Vector2() {}
  Vector2(float x, float y)
  {
    this->x = x;
    this->y = y;
  }
};

struct Paddle
{
  float x, y;
  int width, height, direction;
};

struct Ball
{
  float x, y, xVelocity, yVelocity;
  int width, height;

  Ball(float x, float y, float xVel, float yVel, int width, int height)
  {
    this->x = x;
    this->y = y;
    this->xVelocity = xVel;
    this->yVelocity = xVel;
    this->width = width;
    this->height = height;
  }

    /*bool collidesWith(Ball ball)
    {
      int xDist = abs(ball.x - this->x);
      int yDist = abs(ball.y - this->y);
      int actualDist = sqrt(pow(xDist, 2) + pow(yDist, 2));
      //std::cout << "yeeeeeeeeet" << actualDist << std::endl;
      if(actualDist<60)
      {
        std::cout << "collision\n";
        return true;
      }
      return false;
    }*/

    bool collidesWith(Paddle paddle)
    {
      bool test1 = false, test2 = false, test3 = false, test4 = false;
      if((paddle.x - (paddle.width/2.0f)) < (this->x + (this->width/2.0f)))
      {
        std::cout << "1 ";
        test1 = true;
      }
      if((this->x - (this->width/2.0f)) < (paddle.x + (paddle.width/2.0f)))
      {
        std::cout << "2 ";
        test2 = true;;
      }
      if((paddle.y - (paddle.height/2.0f)) < (this->y + (this->height/2.0f)))
      {
        std::cout << "3 ";
        test3 = true;
      }
      if((this->y - (this->height/2.0f)) < (paddle.y + (paddle.height/2.0f)))
      {
        std::cout << "4 ";
        test4 = true;
      }
      std::cout << std::endl;
      std::cout << "this->: " << this->x << " " << this->y << " " << this->width << " " << this->height << std::endl;
      std::cout << "paddle.: " << paddle.x << " " << paddle.y << " " << paddle.width << " " << paddle.height << std::endl;

      if(test1 && test2 && test3 && test4)
      {
        std::cout << "collision\n";
        return true;
      }
      else
      {
        return false;
      }
    }
};

class Game
{
public:
  Game();
  bool Initialize();
  void RunLoop();
  void Shutdown();

private:
  void InitializeObjects();

  void ProcessInput();
  bool UpdateGame();
  void GenerateOutput();

  void centerVector2(Vector2 vec);

  Paddle createPaddle(float x, float y, int width, int height, int direction);
  void drawPaddle(Paddle mPaddle);

  SDL_Rect createPaddleU();
  void drawPaddleU(SDL_Rect myPaddle);

  SDL_Window *mWindow;
  SDL_Renderer *mRenderer;
  Paddle paddleU, funny;
  Ball gameBall;
  Uint32 mTicksCount;
  SDL_DisplayMode DM;
  SDL_Event event;
  float deltaTime;
  bool mIsRunning;
  int screenHeight, screenWidth, thickness, paddleWidth, paddleHeight;
  int testyFunny = 400, leftPoints, rightPoints;
};

#endif
