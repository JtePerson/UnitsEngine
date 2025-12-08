#include "UnitsEngine/core/log.h"

#include <spdlog/sinks/stdout_color_sinks.h>

namespace units {
bool Log::s_initialized_;

std::shared_ptr<spdlog::logger> Log::s_core_logger_;
std::shared_ptr<spdlog::logger> Log::s_logger_;

void Log::init() noexcept {
  if (s_initialized_) {
    return;
  }
  spdlog::set_pattern("[%Y-%m-%d|%H-%M-%S.%e|%P-%t]%^ %n %l: %v%$");
  s_core_logger_ = spdlog::stdout_color_mt("UNITS-ENGINE");
  s_core_logger_->set_level(spdlog::level::trace);
  s_logger_ = spdlog::stdout_color_mt(" ");
  s_logger_->set_level(spdlog::level::trace);

  s_core_logger_->info("Logging Initialized");
  s_initialized_ = true;
}
}  // namespace units