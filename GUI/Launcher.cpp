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
            g_Launcher->cRainbow = ImColor::HSV(hue, (saturation / 255), (value / 255), (opacity / 255));
        }
    }

    void TextCentered(std::string text) {
        auto windowWidth = ImGui::GetWindowSize().x;
        auto textWidth = ImGui::CalcTextSize(text.c_str()).x;
        ImGui::SetCursorPosX((windowWidth - textWidth) * 0.5f);
        ImGui::Text(text.c_str());
    }

    Profile::Profile()
    {
        hInstance;
        return;
    }

    void Profile::UniCoil(int Speed, int Delay, bool flag)
    {
        switch (flag) {
        case(TRUE):
            if ((GetKeyState(VK_RBUTTON) & 0x100) != 0)
            {
                if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
                {
                    mouse_event(MOUSEEVENTF_MOVE, 0, Speed, NULL, NULL);
                    Sleep(Delay);
                }
            }
            break;
        case(FALSE):
            if ((GetKeyState(VK_LBUTTON) & 0x100) != 0)
            {
                mouse_event(MOUSEEVENTF_MOVE, 0, Speed, NULL, NULL);
                Sleep(Delay);
            }
            break;
        }
        return;
    }

    void Profile::RapidFire(int delay)
    {
        if (GetAsyncKeyState(VK_RBUTTON) != NULL) {
            mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
            Sleep(1);
            mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
            Sleep(delay);
        }
        return;
    }

    Launcher::Launcher()
    {
        m_MainMenu = TRUE;
        m_MenuOptions = FALSE;
        m_LauncherRunning = TRUE;
        m_ShowWindow = TRUE;
        InitStyle();
        return;
    }

    //  MAIN DRAW LOOP
    void Launcher::Draw()
    {
        ImGui::SetNextWindowBgAlpha(0.0f);
        ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(cRainbow));
        ImGui::PushStyleColor(ImGuiCol_BorderShadow, ImVec4(cRainbow));
        ImGui::PushStyleColor(ImGuiCol_Border, ImVec4(cRainbow));
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
        if (!m_DemoWindow)
            InitStyle();

        if (m_MainMenu)
            Menu();

        if (m_MenuOptions)
            MenuOptions();

        if (m_DemoWindow)
            ImGui::ShowDemoWindow(&m_DemoWindow);

        ImGui::End();
    }

    //  MAIN MENU
    void Launcher::Menu()
    {
        // MENU PRESETS
        ImGui::SetNextItemWidth(ImGui::GetWindowContentRegionWidth());
        ImGui::Combo("##PRESETS", &g_Profile->selectedPRESET, g_Profile->presets, IM_ARRAYSIZE(g_Profile->presets));
        switch (g_Profile->selectedPRESET) {
        case(NULL):
            break;
        case(1):
            g_Profile->recoilStrength = g_Profile->config.recoilStrength[0];
            g_Profile->recoilDelay = g_Profile->config.recoilDelay[0];
            g_Profile->rapidFireDelay = g_Profile->config.rapidFireDelay[0];
            g_Profile->bADSFLAG_RECOIL = g_Profile->config.recoilADSFlag[0];
            g_Profile->bADSFLAG_RAPID = g_Profile->config.rapidADSFlag[0];
            break;
        case(2):
            g_Profile->recoilStrength = g_Profile->config.recoilStrength[1];
            g_Profile->recoilDelay = g_Profile->config.recoilDelay[1];
            g_Profile->rapidFireDelay = g_Profile->config.rapidFireDelay[1];
            g_Profile->bADSFLAG_RECOIL = g_Profile->config.recoilADSFlag[1];
            g_Profile->bADSFLAG_RAPID = g_Profile->config.rapidADSFlag[1];
            break;
        case(3):
            g_Profile->recoilStrength = g_Profile->config.recoilStrength[2];
            g_Profile->recoilDelay = g_Profile->config.recoilDelay[2];
            g_Profile->rapidFireDelay = g_Profile->config.rapidFireDelay[2];
            g_Profile->bADSFLAG_RECOIL = g_Profile->config.recoilADSFlag[2];
            g_Profile->bADSFLAG_RAPID = g_Profile->config.rapidADSFlag[2];
            break;
        }

        //  User Configuration
        if (g_Profile->selectedPRESET == NULL) {
            if (ImGui::Button("LOAD CONFIG", ImVec2(ImGui::GetWindowContentRegionWidth(), 0)))
                g_Console->LoadCFG();

            if (ImGui::Button("SAVE CONFIG", ImVec2(220, 0))) {
                g_Profile->config.recoilStrength[g_Profile->savePRESET] = g_Profile->recoilStrength;
                g_Profile->config.recoilDelay[g_Profile->savePRESET] = g_Profile->recoilDelay;
                g_Profile->config.rapidFireDelay[g_Profile->savePRESET] = g_Profile->rapidFireDelay;
                g_Profile->config.recoilADSFlag[g_Profile->savePRESET] = g_Profile->bADSFLAG_RECOIL;
                g_Profile->config.rapidADSFlag[g_Profile->savePRESET] = g_Profile->bADSFLAG_RAPID;
                g_Console->SaveCFG();
            }
            ImGui::SameLine();
            ImGui::SetNextItemWidth(50);
            ImGui::Combo("##PRESETS2", &g_Profile->savePRESET, g_Profile->save_slots, IM_ARRAYSIZE(g_Profile->save_slots));

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            if (g_Profile->bRECOIL) {
                ImGui::TextColored(ImColor(0, 255, 0, 200), "[ENABLED]");
                ImGui::SameLine();
            }
            TextCentered("ANTI-RECOIL");
            ImGui::Spacing();

            ImGui::Checkbox("TOGGLE RECOIL SCRIPT", &g_Profile->bRECOIL);
            ImGui::Checkbox("REQUIRE ADS (Aim Down Sight)", &g_Profile->bADSFLAG_RECOIL);
            ImGui::Text("STRENGTH ");
            ImGui::SameLine();
            ImGui::SliderInt("##STRENGTH", &g_Profile->recoilStrength, 0, 25);
            ImGui::Text("DELAY    ");
            ImGui::SameLine();
            ImGui::SliderInt("##DELAY", &g_Profile->recoilDelay, 0, 25);

            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            if (g_Profile->bRAPID) {
                ImGui::TextColored(ImColor(0, 255, 0, 200), "[ENABLED]");
                ImGui::SameLine();
            }
            TextCentered("RAPID FIRE");
            ImGui::Spacing();

            ImGui::Checkbox("TOGGLE RAPID FIRE SCRIPT", &g_Profile->bRAPID);
            ImGui::Checkbox("REQUIRE ADS (aim down sight)", &g_Profile->bADSFLAG_RAPID);
            ImGui::Text("SPEED    ");
            ImGui::SameLine();
            ImGui::SliderInt("##SPEED", &g_Profile->rapidFireDelay, 0, 25);
            ImGui::Spacing();
        }
        else {
            ImGui::Spacing();
            ImGui::Separator();
            ImGui::Spacing();

            ImGui::Checkbox("NO RECOIL", &g_Profile->bRECOIL);
            ImGui::Checkbox("RAPID FIRE", &g_Profile->bRAPID);

            //  Include method to show user their presets
            ImGui::Text("Recoil Strength: %d", g_Profile->recoilStrength);
            ImGui::Text("Recoil Delay: %d", g_Profile->recoilDelay);
            ImGui::Text("Rapid Fire Delay: %d", g_Profile->rapidFireDelay);
        }

        ImGui::Spacing();
        ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(cRainbow));
        ImGui::Separator();
        ImGui::PopStyleColor();
        ImGui::Spacing();

        //  MENU OPTIONS
        if (ImGui::Button("OPTIONS", ImVec2(ImGui::GetWindowContentRegionWidth(), BUTTONS[1]))) {
            m_MainMenu = FALSE;
            m_MenuOptions = TRUE;
            return;
        }

        ImGui::Spacing();

        //  EXIT
        if (ImGui::Button("EXIT", ImVec2(ImGui::GetWindowContentRegionWidth(), BUTTONS[1]))) g_Running = FALSE;
    }

    //  MENU OPTIONS
    void Launcher::MenuOptions()
    {
        TextCentered("MENU COLORS");
        ImGui::ColorEdit4("##BUTTON-BORDERS", (float*)&g_Profile->m_CustomColors);
        ImGui::Spacing();

        if (ImGui::Button("SHOW IMGUI::DEMO", ImVec2(ImGui::GetWindowContentRegionWidth(), BUTTONS[1])))
            m_DemoWindow = !m_DemoWindow;

        ImGui::Spacing();
        ImGui::PushStyleColor(ImGuiCol_Separator, ImVec4(cRainbow));
        ImGui::Separator();
        ImGui::PopStyleColor();
        ImGui::Spacing();

        if (ImGui::Button("BACK", ImVec2(ImGui::GetWindowContentRegionWidth(), BUTTONS[1]))) {
            m_MainMenu = TRUE;
            m_MenuOptions = FALSE;
            g_Console->SaveCFG();
        }

        ImGui::Spacing();

        if (ImGui::Button("EXIT", ImVec2(ImGui::GetWindowContentRegionWidth(), BUTTONS[1]))) g_Running = FALSE;
    }

    void Launcher::Loops()
    {
        if (g_Profile->bRECOIL)
            g_Profile->UniCoil(g_Profile->recoilStrength, g_Profile->recoilDelay, g_Profile->bADSFLAG_RECOIL);

        if (g_Profile->bRAPID)
            g_Profile->RapidFire(g_Profile->rapidFireDelay);
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
        colors[ImGuiCol_Border] = g_Profile->m_CustomColors;
        colors[ImGuiCol_BorderShadow] = g_Profile->m_CustomColors;

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