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
  void UpdateGame();
  void GenerateOutput();

  Paddle createPaddle(float x, float y, int width, int height, int direction);
  void drawPaddle(Paddle mPaddle);

  SDL_Rect createPaddleU();
  void drawPaddleU(SDL_Rect myPaddle);

  SDL_Window *mWindow;
  SDL_Renderer *mRenderer;
  Vector2 mBallPos, mBallVel;
  Paddle paddleU, funny;
  Uint32 mTicksCount;
  SDL_DisplayMode DM;
  SDL_Event event;
  float deltaTime;
  bool mIsRunning;
  int screenHeight, screenWidth, thickness, paddleWidth, paddleHeight;
  int testyFunny = 400;
};

#endif
