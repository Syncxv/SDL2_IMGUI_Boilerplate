#include "SDL_Handler.h"


SDL_Handler::SDL_Handler() {
    Initalize();
}

SDL_Handler::~SDL_Handler() {
    Destroy();
}

bool SDL_Handler::Initalize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cout << "Failed to initialize the SDL2 library\n";
        return false;
    }

    m_window = SDL_CreateWindow(
        "SDL2 TESTING",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        1280, 720,
        SDL_WINDOW_RESIZABLE
    );

    if (!m_window)
    {
        std::cout << "Failed to create window\n";
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, 0);

    return true;
}



void SDL_Handler::Destroy() {
    SDL_DestroyWindow(m_window);
    SDL_DestroyRenderer(m_renderer);
    SDL_Quit();
}

int SDL_Handler::GetWindowHeight() {
    return SDL_GetWindowSurface(m_window)->h;
}

int SDL_Handler::GetWindowWidth() {
    return SDL_GetWindowSurface(m_window)->w;
}

SDL_Window* SDL_Handler::GetWindow()
{
    return m_window;
}

SDL_Renderer* SDL_Handler::GetRenderer()
{
    return m_renderer;
}

bool SDL_Handler::IsRunning()
{
    return m_isRunning;
}

void SDL_Handler::PollEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // Handle events here
        switch (event.type) {
        case SDL_QUIT:
            m_isRunning = false;
            break;
        }

        if (m_eventCallbacks.count(CUSTOM_ALL) > 0) {
            for (auto& callback : m_eventCallbacks[CUSTOM_ALL]) {
                callback(event);
            }
        }

        if (m_eventCallbacks.count(static_cast<SDL_EventType>(event.type)) > 0) {
            for (auto& callback : m_eventCallbacks[static_cast<SDL_EventType>(event.type)]) {
                callback(event);
            }
        }
    }
}
size_t SDL_Handler::RegisterCallBack(SDL_EventType eventType, std::function<void(SDL_Event&)> callback) {
    m_eventCallbacks[eventType].push_back(callback);
    size_t callbackId = m_nextCallbackId++;
    m_callbackIds[callbackId] = { eventType, m_eventCallbacks[eventType].size() - 1 };
    return callbackId;
}

void SDL_Handler::UnregisterCallback(size_t callbackId) {
    if (m_callbackIds.count(callbackId) > 0) {
        SDL_EventType eventType = m_callbackIds[callbackId].first;
        size_t index = m_callbackIds[callbackId].second;
        if (index < m_eventCallbacks[eventType].size()) {
            m_eventCallbacks[eventType].erase(m_eventCallbacks[eventType].begin() + index);
            // Adjust the indices of all remaining callbacks for this event type
            for (auto& pair : m_callbackIds) {
                if (pair.second.first == eventType && pair.second.second > index) {
                    --pair.second.second;
                }
            }
        }
        m_callbackIds.erase(callbackId);
    }
}