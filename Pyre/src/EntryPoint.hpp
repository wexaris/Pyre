#pragma once

extern Pyre::Application* Pyre::CreateApplication();

int main(int argc, char* argv[]) {
    Pyre::Log::Init("Pyre.log");
    PYRE_CORE_INFO("Initialized Logger");

    PYRE_PROFILE_BEGIN("Startup", "PyreProfile-Startup.json");
    auto app = Pyre::CreateApplication();
    PYRE_PROFILE_END();

    PYRE_PROFILE_BEGIN("Runtime", "PyreProfile-Runtime.json");
    app->Run();
    PYRE_PROFILE_END();

    PYRE_PROFILE_BEGIN("Shutdown", "PyreProfile-Shutdown.json");
    delete app;
    PYRE_PROFILE_END();

    return 0;
}


#ifdef PYRE_PLATFORM_WINDOWS

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow) {
    return main(__argc, __argv);
}

#endif

