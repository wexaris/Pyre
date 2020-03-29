#pragma once

extern Pyre::Application* Pyre::CreateApplication();

int main(int argc, char* argv[]) {
	(void)argc;
	(void)argv;

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
}