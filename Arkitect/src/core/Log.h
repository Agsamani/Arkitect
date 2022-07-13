#pragma once

#pragma warning(push, 0)
#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>
#pragma warning(pop)

namespace Arkitect {
	class Log
	{
	public:
		static void Init();

		static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}


#define RKT_CORE_TRACE(...)    ::Arkitect::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RKT_CORE_INFO(...)     ::Arkitect::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RKT_CORE_WARN(...)     ::Arkitect::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RKT_CORE_ERROR(...)    ::Arkitect::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RKT_CORE_CRITICAL(...) ::Arkitect::Log::GetCoreLogger()->critical(__VA_ARGS__)

#define RKT_TRACE(...)         ::Arkitect::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RKT_INFO(...)          ::Arkitect::Log::GetClientLogger()->info(__VA_ARGS__)
#define RKT_WARN(...)          ::Arkitect::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RKT_ERROR(...)         ::Arkitect::Log::GetClientLogger()->error(__VA_ARGS__)
#define RKT_CRITICAL(...)      ::Arkitect::Log::GetClientLogger()->critical(__VA_ARGS__)

