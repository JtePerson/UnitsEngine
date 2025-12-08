#pragma once
#include <spdlog/spdlog.h>

#include <iostream>
#include <memory>

#include "UnitsEngine/core/debug.h"
#include "UnitsEngine/core/engine_api.h"

namespace units {
class UE_API Log final {
 public:
  static void init() noexcept;

  static inline std::shared_ptr<spdlog::logger>& getCoreLogger() noexcept {
    if (!s_initialized_) {
      std::cout << "Logging not Initialized!" << std::endl;
      UE_DEBUG_BREAK();
    }
    return s_core_logger_;
  }
  static inline std::shared_ptr<spdlog::logger>& getLogger() noexcept {
    if (!s_initialized_) {
      std::cout << "Logging not Initialized!" << std::endl;
      UE_DEBUG_BREAK();
    }
    return s_logger_;
  }

 private:
  inline Log() noexcept = delete;
  inline ~Log() noexcept = delete;

  static bool s_initialized_;

  static std::shared_ptr<spdlog::logger> s_core_logger_;
  static std::shared_ptr<spdlog::logger> s_logger_;
};
}  // namespace units

#if defined(UE_ENABLE_LOGGING)
#define UE_INIT_LOG() ::units::Log::init()

#define UE_CORE_TRACE(...) ::units::Log::getCoreLogger()->trace(__VA_ARGS__);
#define UE_CORE_INFO(...) ::units::Log::getCoreLogger()->info(__VA_ARGS__);
#define UE_CORE_WARN(...) ::units::Log::getCoreLogger()->warn(__VA_ARGS__);
#define UE_CORE_ERROR(...) ::units::Log::getCoreLogger()->error(__VA_ARGS__);
#define UE_CORE_CRITICAL(...) \
  ::units::Log::getCoreLogger()->critical(__VA_ARGS__);

#define UE_TRACE(...) ::units::Log::getLogger()->trace(__VA_ARGS__);
#define UE_INFO(...) ::units::Log::getLogger()->info(__VA_ARGS__);
#define UE_WARN(...) ::units::Log::getLogger()->warn(__VA_ARGS__);
#define UE_ERROR(...) ::units::Log::getLogger()->error(__VA_ARGS__);
#define UE_CRITICAL(...) ::units::Log::getLogger()->critical(__VA_ARGS__);
#else
#define UE_INIT_LOG()

#define UE_CORE_TRACE(...)
#define UE_CORE_INFO(...)
#define UE_CORE_WARN(...)
#define UE_CORE_ERROR(...)
#define UE_CORE_CRITICAL(...)

#define UE_TRACE(...)
#define UE_INFO(...)
#define UE_WARN(...)
#define UE_ERROR(...)
#define UE_CRITICAL(...)
#endif