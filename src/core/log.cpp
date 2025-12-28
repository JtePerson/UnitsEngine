module;

#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

module units.Log;

namespace units {
  bool Log::s_initialized_= false;

  std::shared_ptr<spdlog::logger> Log::s_user_logger_uptr_= nullptr;
  std::shared_ptr<spdlog::logger> Log::s_engine_logger_uptr_= nullptr;

  bool Log::init() noexcept {
    if (s_initialized_)
      return true;

    s_user_logger_uptr_= std::make_shared<spdlog::logger>("User-Logger");
    spdlog::set_default_logger(s_user_logger_uptr_);

    auto console_sink= std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto debug_file_sink= std::make_shared<spdlog::sinks::basic_file_sink_mt>("./UnitsEngine-debug-log.txt");
    auto error_file_sink= std::make_shared<spdlog::sinks::basic_file_sink_mt>("./UnitsEngine-error-log.txt");

    console_sink->set_level(spdlog::level::trace);
    debug_file_sink->set_level(spdlog::level::debug);
    error_file_sink->set_level(spdlog::level::err);

    console_sink->set_pattern("%^[%-8l] %n: %v%$");
    debug_file_sink->set_pattern("[%Y/%m/%d | %I:%M:%S.%F-%p] [%-8l] %n: %v; %g - %!");
    error_file_sink->set_pattern("[%Y/%m/%d | %I:%M:%S.%F-%p] [%-8l] %n: %v; %g - %!");

    s_engine_logger_uptr_= std::make_shared<spdlog::logger>("UnitsEngine-Logger");

    engineLogger()->set_level(spdlog::level::trace);

    engineLogger()->sinks().emplace_back(console_sink);
    engineLogger()->sinks().emplace_back(debug_file_sink);
    engineLogger()->sinks().emplace_back(error_file_sink);

    return s_initialized_= true;
  }
  void Log::quit() noexcept {
    if (!s_initialized_)
      return;
    s_user_logger_uptr_= nullptr;
    s_engine_logger_uptr_= nullptr;
    s_initialized_= false;
  }
} // namespace units