#include "Launcher.hpp"

namespace UniCoil {
    
    float HSV_RAINBOW_SPEED = 0.002;
    static float HSV_RAINBOW_HUE = 0;
    void SV_RAINBOW(float saturation, float value, float opacity)
    {
        HSV_RAINBOW_HUE -= HSV_RAINBOW_SPEED;
        if (HSV_RAINBOW_HUE < -1.f) HSV_RAINBOW_HUE += 1.f;
        for (int i = 0; i < 860; i++)
        {
            float hue = HSV_RAINBOW_HUE + (1.f / (float)860) * i;
            if (hue < 0.f) hue += 1.f;
            g_LauncherVariables->cRainbow = ImColor::HSV(hue, (saturation / 255), (value / 255), (opacity / 255));
        }
    }

    void TextCentered(std::string text) {
        auto windowWidth = ImGui::GetWindowSize().x;
        auto textWidth = ImGui::CalcTextSize(text.c_str()).x;
        ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
        ImGui::Text(text.c_str());
    }


    LauncherVariables::LauncherVariables()
    {
        m_LauncherRunning = TRUE;
        m_ShowWindow = TRUE;
        hInstance;
        m_MainMenu = TRUE;
        m_MenuOptions = FALSE;
        return;
    }

    Launcher::Launcher()
    {
        InitStyle();
    }

    //  MAIN DRAW LOOP
    void Launcher::Draw()
    {
        ImGui::SetNextWindowBgAlpha(0.0f);
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(g_LauncherVariables->cRainbow));
        ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(g_LauncherVariables->cRainbow));
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(g_LauncherVariables->cRainbow));
        if (!ImGui::Begin("UniCoil", (bool*)&g_Running, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_AlwaysAutoResize)) {
            ImGui::PopStyleColor();
            ImGui::PopStyleColor();
            ImGui::PopStyleColor();
            ImGui::End();
            return;
        }
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();
        ImGui::PopStyleColor();

        SV_RAINBOW(169, 169, 200);
        if (!g_LauncherVariables->m_DemoWindow)
            InitStyle();

        if (g_LauncherVariables->m_MainMenu)
            Menu();

        if (g_LauncherVariables->m_MenuOptions)
            MenuOptions();

        if (g_LauncherVariables->m_DemoWindow)
            ImGui::ShowDemoWindow(&g_LauncherVariables->m_DemoWindow);

        ImGui::End();
    }

    //  MAIN MENU
    void Launcher::Menu()
    {
        ImGui::Checkbox("RECOIL SETTINGS", &g_LauncherVariables->bRECOIL);
        if (g_LauncherVariables->bRECOIL) {
            ImGui::Text("STRENGTH ");
            ImGui::SameLine();
            ImGui::SliderInt("##STRENGTH", &g_LauncherVariables->recoilStrength1, 0, 25);
            ImGui::Text("DELAY    ");
            ImGui::SameLine();
            ImGui::SliderInt("##DELAY", &g_LauncherVariables->recoilDelay1, 0, 25);
            ImGui::Separator();
            ImGui::Spacing();
        }

        ImGui::Checkbox("RAPID FIRE SETTINGS", &g_LauncherVariables->bRAPID);
        if (g_LauncherVariables->bRAPID) {
            ImGui::Text("SPEED    ");
            ImGui::SameLine();
            ImGui::SliderInt("##SPEED", &g_LauncherVariables->rapidFireDelay, 0, 25);
            ImGui::Spacing();
        }

        ImGui::Spacing();
        ImGui::Separator();
        ImGui::Spacing();

        // MENU PRESETS
        ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth() - 3);
        ImGui::Combo("##PRESETS", &g_LauncherVariables->selectedPRESET, g_LauncherVariables->presets, IM_ARRAYSIZE(g_LauncherVariables->presets));
        ImGui::Spacing();

        //  MENU OPTIONS
        if (ImGui::Button("OPTIONS", ImVec2(ImGui::GetWindowContentRegionWidth() - 3, g_LauncherVariables->BUTTONS[1]))) {
            if (g_LauncherVariables->bRAPID || g_LauncherVariables->bRECOIL) {
                g_LauncherVariables->bRAPID = FALSE;
                g_LauncherVariables->bRECOIL = FALSE;
            }
            g_LauncherVariables->m_MainMenu = FALSE;
            g_LauncherVariables->m_MenuOptions = TRUE;
            return;
        }

        ImGui::Spacing();

        //  EXIT
        if (ImGui::Button("EXIT", ImVec2(ImGui::GetWindowContentRegionWidth() - 3, g_LauncherVariables->BUTTONS[1]))) g_Running = FALSE;
    }

    //  MENU OPTIONS
    void Launcher::MenuOptions()
    {
        TextCentered("MENU COLORS");
        ImGui::ColorEdit4("##BUTTON-BORDERS", (float*)&g_LauncherVariables->m_CustomColors);
        ImGui::Spacing();

        if (ImGui::Button("SHOW IMGUI::DEMO", ImVec2(ImGui::GetWindowContentRegionWidth(), g_LauncherVariables->BUTTONS[1])))
            g_LauncherVariables->m_DemoWindow = !g_LauncherVariables->m_DemoWindow;

        ImGui::Spacing();
        ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(g_LauncherVariables->cRainbow));
        ImGui::Separator();
        ImGui::PopStyleColor();
        ImGui::Spacing();

        if (ImGui::Button("BACK", ImVec2(ImGui::GetWindowContentRegionWidth(), g_LauncherVariables->BUTTONS[1]))) {
            g_LauncherVariables->m_MainMenu = TRUE;
            g_LauncherVariables->m_MenuOptions = FALSE;
        }

        ImGui::Spacing();

        if (ImGui::Button("EXIT", ImVec2(ImGui::GetWindowContentRegionWidth(), g_LauncherVariables->BUTTONS[1]))) g_Running = FALSE;
    }

    void Launcher::InitStyle()
    {
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec4* colors = ImGui::GetStyle().Colors;
        ImGui::StyleColorsDark();
        style.WindowTitleAlign = ImVec2(0.5f, 0.5f);
        style.FrameRounding = 1.0f;
        style.GrabRounding = style.FrameRounding; // Make GrabRounding always the same value as FrameRounding
        style.WindowRounding = 4.0f;
        style.FrameBorderSize = 0.75f;

        /// CUSTOM USER COLORS
        colors[ImGuiCol_Border] = g_LauncherVariables->m_CustomColors;
        colors[ImGuiCol_BorderShadow] = g_LauncherVariables->m_CustomColors;

        //	COLORS
        colors[ImGuiCol_Text] = ImVec4(0.75f, 0.75f, 0.29f, 1.00f);
        colors[ImGuiCol_TextDisabled] = ImVec4(0.86f, 0.93f, 0.89f, 0.28f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.27f, 0.00f, 0.63f, 0.43f);
        colors[ImGuiCol_WindowBg] = ImVec4(0.10f, 0.10f, 0.10f, 0.70f);
        colors[ImGuiCol_ChildBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_PopupBg] = ImVec4(0.19f, 0.19f, 0.19f, 0.92f);
        colors[ImGuiCol_FrameBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        colors[ImGuiCol_FrameBgHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
        colors[ImGuiCol_FrameBgActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_TitleBgActive] = ImVec4(0.06f, 0.06f, 0.06f, 1.00f);
        colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_MenuBarBg] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_ScrollbarBg] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
        colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.40f, 0.40f, 0.40f, 0.54f);
        colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
        colors[ImGuiCol_CheckMark] = ImVec4(0.74f, 0.74f, 0.29f, 1.00f);
        colors[ImGuiCol_SliderGrab] = ImVec4(0.34f, 0.34f, 0.34f, 0.54f);
        colors[ImGuiCol_SliderGrabActive] = ImVec4(0.56f, 0.56f, 0.56f, 0.54f);
        colors[ImGuiCol_Button] = ImVec4(0.05f, 0.05f, 0.05f, 0.54f);
        colors[ImGuiCol_ButtonHovered] = ImVec4(0.19f, 0.19f, 0.19f, 0.54f);
        colors[ImGuiCol_ButtonActive] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 0.36f);
        colors[ImGuiCol_HeaderActive] = ImVec4(0.20f, 0.22f, 0.23f, 0.33f);
        colors[ImGuiCol_Separator] = ImVec4(0.28f, 0.28f, 0.28f, 0.90f);
        colors[ImGuiCol_SeparatorHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
        colors[ImGuiCol_SeparatorActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
        colors[ImGuiCol_ResizeGrip] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        colors[ImGuiCol_ResizeGripHovered] = ImVec4(0.44f, 0.44f, 0.44f, 0.29f);
        colors[ImGuiCol_ResizeGripActive] = ImVec4(0.40f, 0.44f, 0.47f, 1.00f);
        colors[ImGuiCol_Tab] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TabHovered] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_TabActive] = ImVec4(0.20f, 0.20f, 0.20f, 0.36f);
        colors[ImGuiCol_TabUnfocused] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TabUnfocusedActive] = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
        colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotLinesHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogram] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_TableHeaderBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TableBorderStrong] = ImVec4(0.00f, 0.00f, 0.00f, 0.52f);
        colors[ImGuiCol_TableBorderLight] = ImVec4(0.28f, 0.28f, 0.28f, 0.29f);
        colors[ImGuiCol_TableRowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
        colors[ImGuiCol_TableRowBgAlt] = ImVec4(1.00f, 1.00f, 1.00f, 0.06f);
        colors[ImGuiCol_TextSelectedBg] = ImVec4(0.20f, 0.22f, 0.23f, 1.00f);
        colors[ImGuiCol_DragDropTarget] = ImVec4(0.33f, 0.67f, 0.86f, 1.00f);
        colors[ImGuiCol_NavHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 1.00f);
        colors[ImGuiCol_NavWindowingHighlight] = ImVec4(1.00f, 0.00f, 0.00f, 0.70f);
        colors[ImGuiCol_NavWindowingDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.20f);
        colors[ImGuiCol_ModalWindowDimBg] = ImVec4(1.00f, 0.00f, 0.00f, 0.35f);
        return;
    }
}