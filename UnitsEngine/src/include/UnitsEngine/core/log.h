#pragma once
#include "UnitsEngine/core/engine_api.h"

#include <spdlog/spdlog.h>

#if defined(UE_LOGGING_ENABLED)
  namespace Units {
    class UE_API Log final {
    public:
      static void init() noexcept;
      static inline std::shared_ptr<spdlog::logger> getCoreLogger() noexcept { if (!m_initialized_) { init(); } return s_core_logger_; }
      static inline std::shared_ptr<spdlog::logger> getClientLogger() noexcept { if (!m_initialized_) { init(); } return s_client_logger_; }
    private:
      inline Log() noexcept= delete;
      inline ~Log() noexcept= delete;

      static inline bool m_initialized_= false;

      static std::shared_ptr<spdlog::logger> s_core_logger_;
      static std::shared_ptr<spdlog::logger> s_client_logger_;
    };
  } // namespace Units

  // --- Init ---
  #define UE_INIT_LOG() ::Units::Log::init()
  // ------------
  // --- Core Logging Macros ---
  #define UE_CORE_TRACE(...) ::Units::Log::getCoreLogger()->trace(__VA_ARGS__)
  #define UE_CORE_INFO(...) ::Units::Log::getCoreLogger()->info(__VA_ARGS__)
  #define UE_CORE_WARN(...) ::Units::Log::getCoreLogger()->warn(__VA_ARGS__)
  #define UE_CORE_ERROR(...) ::Units::Log::getCoreLogger()->error(__VA_ARGS__)
  #define UE_CORE_CRITICAL(...) ::Units::Log::getCoreLogger()->critical(__VA_ARGS__)
  // ---------------------------
  // --- Core Logging Macros ---
  #define UE_TRACE(...) ::Units::Log::getClientLogger()->trace(__VA_ARGS__)
  #define UE_INFO(...) ::Units::Log::getClientLogger()->info(__VA_ARGS__)
  #define UE_WARN(...) ::Units::Log::getClientLogger()->warn(__VA_ARGS__)
  #define UE_ERROR(...) ::Units::Log::getClientLogger()->error(__VA_ARGS__)
  #define UE_CRITICAL(...) ::Units::Log::getClientLogger()->critical(__VA_ARGS__)
  // ---------------------------
#else
  // --- Init ---
  #define UE_INIT_LOG()
  // ------------
  // --- Core Logging Macros ---
  #define UE_CORE_TRACE(...)
  #define UE_CORE_INFO(...)
  #define UE_CORE_WARN(...)
  #define UE_CORE_ERROR(...)
  #define UE_CORE_CRITICAL(...)
  // ---------------------------
  // --- Client Logging Macros ---
  #define UE_TRACE(...)
  #define UE_INFO(...)
  #define UE_WARN(...)
  #define UE_ERROR(...)
  #define UE_CRITICAL(...)
  // ---------------------------
#endif