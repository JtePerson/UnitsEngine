#pragma once

import units.Log;

#ifdef UE_ENABLE_LOGGING
#  ifdef UE_BUILD_DLL
#    define UE_TRACE(...) ::units::Log::engineLogger()->trace(__VA_ARGS__)
#    define UE_DEBUG(...) ::units::Log::engineLogger()->debug(__VA_ARGS__)
#    define UE_INFO(...) ::units::Log::engineLogger()->info(__VA_ARGS__)
#    define UE_WARN(...) ::units::Log::engineLogger()->warn(__VA_ARGS__)
#    define UE_ERROR(...) ::units::Log::engineLogger()->error(__VA_ARGS__)
#    define UE_CRITICAL(...) ::units::Log::engineLogger()->critical(__VA_ARGS__)
#  else
#    define UE_TRACE(...) ::units::Log::userLogger()->trace(__VA_ARGS__)
#    define UE_DEBUG(...) ::units::Log::userLogger()->debug(__VA_ARGS__)
#    define UE_INFO(...) ::units::Log::userLogger()->info(__VA_ARGS__)
#    define UE_WARN(...) ::units::Log::userLogger()->warn(__VA_ARGS__)
#    define UE_ERROR(...) ::units::Log::userLogger()->error(__VA_ARGS__)
#    define UE_CRITICAL(...) ::units::Log::userLogger()->critical(__VA_ARGS__)
#  endif
#else
#  define UE_TRACE(...)
#  define UE_DEBUG(...)
#  define UE_INFO(...)
#  define UE_WARN(...)
#  define UE_ERROR(...)
#  define UE_CRITICAL(...)
#endif