#pragma once

extern Pyre::Application* Pyre::CreateApplication();

int main(int argc, char* argv[]) {
	(void)argc;
	(void)argv;

	Pyre::Log::Init();
	PYRE_CORE_TRACE("Initialized Logger!");

	auto app = Pyre::CreateApplication();
	app->Run();
	delete app;
}


#ifdef PYRE_PLATFORM_WINDOWS

#else // PYRE_PLATFORM_LINUX

#endif