#pragma once

#include <spdlog/spdlog.h>

namespace Rendurr {
	class Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_coreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_clientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_coreLogger;
		static std::shared_ptr<spdlog::logger> s_clientLogger;
	};
}

#define RND_CORE_TRACE(...) ::Rendurr::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RND_CORE_INFO(...) ::Rendurr::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RND_CORE_WARN(...) ::Rendurr::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RND_CORE_ERROR(...) ::Rendurr::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RND_CORE_CRITICAL(...) ::Rendurr::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define RND_TRACE(...) ::Rendurr::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RND_INFO(...) ::Rendurr::Log::GetClientLogger()->info(__VA_ARGS__)
#define RND_WARN(...) ::Rendurr::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RND_ERROR(...) ::Rendurr::Log::GetClientLogger()->error(__VA_ARGS__)
#define RND_CRITICAL(...) ::Rendurr::Log::GetClientLogger()->critical(__VA_ARGS__)
