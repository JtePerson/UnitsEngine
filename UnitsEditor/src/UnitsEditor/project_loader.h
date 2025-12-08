#pragma once
#include <memory>
#include <string>
#include <string_view>

namespace editor {
struct Project final {
  std::string name;
};
class ProjectLoader final {
 public:
  static std::unique_ptr<Project>& loadProject(
      const std::string& p_directory) noexcept;
  static std::unique_ptr<Project>& createProject(
      const std::string& p_directory) noexcept;
  static void unloadProject() noexcept;
  static inline std::unique_ptr<Project>& getProject() noexcept {
    return s_current_project_;
  }

 private:
  ProjectLoader() = delete;
  ~ProjectLoader() = delete;

  static std::unique_ptr<Project> s_current_project_;
};
}  // namespace editor