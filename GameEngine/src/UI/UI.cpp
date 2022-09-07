#include "UI.h"
#include "../ImGui/imgui.h"
#include "../ImGui/imgui_impl_sdl.h"
#include "../ImGui/imgui_impl_opengl3.h"

using namespace core::ui;

void UI::InitGUI(Window* window)
{
    this->window = window;

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    //io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer bindings
    // window is the SDL_Window*
    // context is the SDL_GLContext
    ImGui_ImplSDL2_InitForOpenGL(window->GetWindow(), window->GetContext());
    ImGui_ImplOpenGL3_Init();
}

void UI::OnFrameStart()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(window->GetWindow());
    ImGui::NewFrame();
}

void UI::DrawGUI()
{

    ImGui::Begin("MyWindow");
    ImGui::Checkbox("Boolean property", &this->someBoolean);
    if (ImGui::Button("Reset Speed")) {
        this->speed = 0;
    }
    ImGui::SliderFloat("Speed", &this->speed, 0.0f, 10.0f);
    ImGui::End();

    ImGui::ShowDemoWindow();

    ImGui::Render();

    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    
    SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
    SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
    SDL_GL_MakeCurrent(backup_current_window, backup_current_context);

}

void UI::CleanUpGui()
{

}
