#include <cstdint>
#include <iostream>
#include <GL/glew.h>
#include <SDL.h>
#include <SDL_ttf.h>
#include <Windows.h>
#include "Version.hpp"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR pCmdLine, int nCmdShow) {
  freopen("stdout.log", "w", stdout);
  freopen("stderr.log", "w", stderr);
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
    return 1;
  }
  TTF_Init();
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
  auto width = 1920;
  auto height = 1080;
  auto window = SDL_CreateWindow(
    "Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
    SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN);
  if(!window) {
    std::cout << "Error creating window: " << SDL_GetError() << std::endl;
    return 1;
  }
  auto gl_context = SDL_GL_CreateContext(window);
  if(glewInit() != GLEW_OK) {
    std::cout << "Error initializing GLEW." << std::endl;
    return 1;
  }
  if(SDL_GL_SetSwapInterval(1) < 0) {
    std::cout <<
      "Warning: Unable to set VSync: " << SDL_GetError() << std::endl;
    return 1;
  }
  SDL_DestroyWindow(window);
  SDL_GL_DeleteContext(gl_context);
  SDL_Quit();
  return 0;
}
