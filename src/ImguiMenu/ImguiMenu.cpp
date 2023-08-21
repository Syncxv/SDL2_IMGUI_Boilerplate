#include "ImguiMenu.h"

#include <thread>

ImguiMenu::ImguiMenu(SDL_Handler* handler) {
	m_handler = handler;
	Initalize();
}

ImguiMenu::~ImguiMenu() {
	Destroy();
}

void ImguiMenu::Initalize() {
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();

	// Setup Platform/Renderer backends
	ImGui_ImplSDL2_InitForSDLRenderer(m_handler->window, m_handler->renderer);
	ImGui_ImplSDLRenderer2_Init(m_handler->renderer);

	m_handler->RegisterCallBack(m_handler->CUSTOM_ALL, [this](SDL_Event& event) {
		ImGui_ImplSDL2_ProcessEvent(&event);
	});

}

void ImguiMenu::Destroy() {
	ImGui_ImplSDLRenderer2_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();
}

void ImguiMenu::Update() {
	// Start the Dear ImGui frame
	ImGui_ImplSDLRenderer2_NewFrame();
	ImGui_ImplSDL2_NewFrame();
	ImGui::NewFrame();

	ImGui::ShowDemoWindow();

	// Render the ImGui frame
	ImGui::Render();
	ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
}

