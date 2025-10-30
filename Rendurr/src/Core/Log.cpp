#include "Log.hpp"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace Rendurr
{
	std::shared_ptr<spdlog::logger> Log::s_coreLogger;
	std::shared_ptr<spdlog::logger> Log::s_clientLogger;

	void Log::Init()
	{
		// Create a color console sink
		auto consoleSink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
		consoleSink->set_pattern("[%T] [%^%l%$] %n: %v");

		// Core Logger
		s_coreLogger = std::make_shared<spdlog::logger>("RENDURR", consoleSink);
		s_coreLogger->set_level(spdlog::level::trace);
		spdlog::register_logger(s_coreLogger);

		// Client Logger
		s_clientLogger = std::make_shared<spdlog::logger>("APPLICATION", consoleSink);
		s_clientLogger->set_level(spdlog::level::trace);
		spdlog::register_logger(s_clientLogger);
	}
}
