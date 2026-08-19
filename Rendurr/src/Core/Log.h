#pragma once

#include <spdlog/spdlog.h>

namespace rnd
{
    class Log
    {
    public:
        static void Init();

        static std::shared_ptr<spdlog::logger>& GetCoreLogger()
        {
            return s_coreLogger;
        }

        static std::shared_ptr<spdlog::logger>& GetClientLogger()
        {
            return s_clientLogger;
        }

    private:
        static std::shared_ptr<spdlog::logger> s_coreLogger;
        static std::shared_ptr<spdlog::logger> s_clientLogger;
    };
} // namespace rnd

#ifdef RND_ENABLE_ASSERTS

#if defined(_MSC_VER)
#define RND_DEBUGBREAK() __debugbreak()
#else
#include <signal.h>
#define RND_DEBUGBREAK() raise(SIGTRAP)
#endif

#define RND_CORE_ASSERT(condition, ...)                                                            \
    do {                                                                                           \
        if (!(condition)) {                                                                        \
            RND_CORE_ERROR("Assertion Failed: {}", __VA_ARGS__);                                   \
            RND_DEBUGBREAK();                                                                      \
        }                                                                                          \
    } while (false)

#define RND_ASSERT(condition, ...)                                                                 \
    do {                                                                                           \
        if (!(condition)) {                                                                        \
            RND_ERROR("Assertion Failed: {}", __VA_ARGS__);                                        \
            RND_DEBUGBREAK();                                                                      \
        }                                                                                          \
    } while (false)

#else

#define RND_CORE_ASSERT(condition, ...)
#define RND_ASSERT(condition, ...)

#endif
#define RND_CORE_TRACE(...) ::rnd::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RND_CORE_INFO(...) ::rnd::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RND_CORE_WARN(...) ::rnd::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RND_CORE_ERROR(...) ::rnd::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RND_CORE_CRITICAL(...) ::rnd::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define RND_TRACE(...) ::rnd::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RND_INFO(...) ::rnd::Log::GetClientLogger()->info(__VA_ARGS__)
#define RND_WARN(...) ::rnd::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RND_ERROR(...) ::rnd::Log::GetClientLogger()->error(__VA_ARGS__)
#define RND_CRITICAL(...) ::rnd::Log::GetClientLogger()->critical(__VA_ARGS__)
