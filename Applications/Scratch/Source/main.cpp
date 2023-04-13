#include <array>
#include <cstdint>
#include <iostream>
#include <SDL.h>
#include <SDL_ttf.h>
#include <Windows.h>
#include "Slither/Controller.hpp"
#include "Version.hpp"

using namespace Slither;

void render(const Controller& controller, SDL_Renderer& renderer) {
  static const auto TILE_SIZE = 32;
  static auto COLORS = std::array<SDL_Color, 6>{{
    {0, 0, 0, 255},
    {144, 238, 144, 255},
    {34, 139, 34, 255},
    {139, 69, 19, 255},
    {255, 0, 0, 255},
    {255, 255, 255, 255}
  }};
  auto& board = controller.get_board();
  auto board_width = board.get_width() * TILE_SIZE;
  auto board_height = board.get_height() * TILE_SIZE;
  auto screen_width = 0;
  auto screen_height = 0;
  SDL_GetRendererOutputSize(&renderer, &screen_width, &screen_height);
  SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);
  SDL_RenderClear(&renderer);
  for(auto x = -1; x <= board.get_width(); ++x) {
    for(auto y = -1; y <= board.get_height(); ++y) {
      auto color = [&] {
        if(x == -1 || y == -1 || x == board.get_width() ||
            y == board.get_height()) {
          return COLORS[5];
        } else {
          auto cell = board.get(x, y);
          return COLORS[static_cast<int>(cell)];
        }
      }();
      SDL_SetRenderDrawColor(&renderer, color.r, color.g, color.b, color.a);
      auto rect = SDL_Rect();
      rect.x = (screen_width - board_width) / 2 + x * TILE_SIZE;
      rect.y = (screen_height - board_height) / 2 + y * TILE_SIZE;
      rect.w = TILE_SIZE;
      rect.h = TILE_SIZE;
      SDL_RenderFillRect(&renderer, &rect);
    }
  }
  SDL_RenderPresent(&renderer);
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR pCmdLine, int nCmdShow) {
  freopen("stdout.log", "w", stdout);
  freopen("stderr.log", "w", stderr);
  if(SDL_Init(SDL_INIT_EVERYTHING) < 0) {
    std::cout << "Error initializing SDL: " << SDL_GetError() << std::endl;
    return 1;
  }
  TTF_Init();
  auto width = 1920;
  auto height = 1080;
  auto window = SDL_CreateWindow(
    "Example", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
    SDL_WINDOW_SHOWN);
  if(!window) {
    std::cout << "Error creating window: " << SDL_GetError() << std::endl;
    return 1;
  }
  auto renderer_flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  auto renderer = SDL_CreateRenderer(window, -1, renderer_flags);
  if(!renderer) {
    std::cout << "Error creating renderer: " << SDL_GetError() << std::endl;
    return 1;
  }
  auto board = Board(16, 16);
  board.set(5, 0, Board::Cell::HEAD);
  board.set(4, 0, Board::Cell::BODY);
  board.set(3, 0, Board::Cell::BODY);
  board.set(2, 0, Board::Cell::TAIL);
  board.set(12, 6, Board::Cell::APPLE);
  auto controller = Controller(board);
  auto quit = false;
  auto event = SDL_Event();
  auto direction = Controller::Direction::RIGHT;
  auto last_update_time = SDL_GetTicks();
  auto update_interval = 333;
  while(!quit) {
    while (SDL_PollEvent(&event)) {
      if(event.type == SDL_QUIT) {
        quit = true;
      } else if(event.type == SDL_KEYDOWN) {
        switch(event.key.keysym.sym) {
          case SDLK_UP:
            direction = Controller::Direction::UP;
            break;
          case SDLK_DOWN:
            direction = Controller::Direction::DOWN;
            break;
          case SDLK_LEFT:
            direction = Controller::Direction::LEFT;
            break;
          case SDLK_RIGHT:
            direction = Controller::Direction::RIGHT;
            break;
          case SDLK_ESCAPE:
            quit = true;
            break;
        }
      }
    }
    auto current_time = SDL_GetTicks();
    if(static_cast<int>(current_time - last_update_time) >= update_interval) {
      last_update_time = current_time;
      controller.update(direction);
    }
    render(controller, *renderer);
  }
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
