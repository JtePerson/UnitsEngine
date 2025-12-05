#include "UnitsEngine/core/log.h"

#include <spdlog/spdlog.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include "UnitsEngine/core/engine_api.h"

#if defined(UE_LOGGING_ENABLED)
  namespace units {
    std::shared_ptr<spdlog::logger> Log::s_core_logger_;
    std::shared_ptr<spdlog::logger> Log::s_client_logger_;
    void Log::init() noexcept {
      if (m_initialized_) { return; }
      spdlog::set_pattern("%^[%T] %n: %v%$");
      s_core_logger_= spdlog::stdout_color_mt("UNITS-ENGINE");
      s_core_logger_->set_level(spdlog::level::trace);
      s_client_logger_= spdlog::stdout_color_mt("CLIENT");
      s_client_logger_->set_level(spdlog::level::trace);
      s_core_logger_->info("Logging Initialized");
      m_initialized_= true;
    }
  } // namespace units
#endif