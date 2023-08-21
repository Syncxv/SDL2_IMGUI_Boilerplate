#pragma once
#include <SDL.h>
#include <iostream>
#include <map>
#include <functional>
#include <vector>

class SDL_Handler {
public:
	SDL_Handler();
	~SDL_Handler();

	bool Initalize();
	void Destroy();

	int GetWindowHeight();
	int GetWindowWidth();

	SDL_Window* GetWindow();
	SDL_Renderer* GetRenderer();

	bool IsRunning();

	void PollEvents();

	size_t RegisterCallBack(SDL_EventType eventType, std::function<void(SDL_Event&)> callback);
	void UnregisterCallback(size_t callbackId);


	inline static const SDL_EventType CUSTOM_ALL = (SDL_EventType)0x69420;
private:
	SDL_Window* m_window;
	SDL_Renderer* m_renderer;

	bool m_isRunning = true;

	std::map<SDL_EventType, std::vector<std::function<void(SDL_Event&)>>> m_eventCallbacks;
	std::map<size_t, std::pair<SDL_EventType, size_t>> m_callbackIds;
	size_t m_nextCallbackId = 0;
	FILE* m_stdout;

};

