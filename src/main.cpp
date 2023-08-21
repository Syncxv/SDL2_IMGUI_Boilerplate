#include <iostream>
#include <SDL.h>
#include "SDL_Handler/SDL_Handler.h"
#include "ImguiMenu/ImguiMenu.h"


int main(int argc, char* argv[]) {

	SDL_Handler handler;
	ImguiMenu imguiMenu(&handler);

	SDL_Renderer* renderer = handler.GetRenderer();

	while (handler.IsRunning()) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		SDL_RenderClear(renderer);

		imguiMenu.Update();
		handler.PollEvents();

		SDL_RenderPresent(renderer);
	}

	return 0;
}
