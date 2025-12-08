#include "project_loader.h"

#include <UnitsEngine/core/assert.h>
#include <rapidjson/document.h>
#include <rapidjson/filewritestream.h>
#include <rapidjson/writer.h>
#include <stdio.h>

#include <filesystem>
#include <fstream>
#include <sstream>

namespace editor {
std::unique_ptr<Project> ProjectLoader::s_current_project_;

std::unique_ptr<Project>& ProjectLoader::loadProject(
    const std::string& p_directory) noexcept {
  UE_CORE_ASSERT(std::filesystem::exists(p_directory) &&
                     std::filesystem::is_directory(p_directory),
                 "Directory does not exist!");
  const std::string project_path = p_directory + "./units-project.json";
  if (!std::filesystem::exists(project_path)) {
    return createProject(p_directory);
  }
  UE_CORE_TRACE("Loading Project");

  if (s_current_project_ != nullptr) {
    unloadProject();
  }

  std::fstream project_file{project_path};
  UE_CORE_ASSERT(project_file.is_open(), "Could not open ./units-project.json");
  std::stringstream buffer;
  buffer << project_file.rdbuf();
  std::string json_content = buffer.str();
  project_file.close();

  rapidjson::Document json_document;
  rapidjson::ParseResult json_parse_result =
      json_document.Parse(json_content.c_str());

  UE_CORE_ASSERT(json_parse_result, "Could not parse ./units-project.json");

  s_current_project_ = std::make_unique<Project>();
  s_current_project_->name =
      json_document.HasMember("name") && json_document["name"].IsString()
          ? json_document["name"].GetString()
          : "Default Name";
  return s_current_project_;
}
std::unique_ptr<Project>& ProjectLoader::createProject(
    const std::string& p_directory) noexcept {
  UE_CORE_TRACE("Creating New Project");
  UE_CORE_ASSERT(std::filesystem::exists(p_directory) &&
                     std::filesystem::is_directory(p_directory),
                 "Directory does not exist!");
  const std::string project_path = p_directory + "./units-project.json";

  s_current_project_ =
      std::make_unique<Project>(Project{.name = "New Project"});

  rapidjson::Document json_document;
  json_document.SetObject();

  rapidjson::Document::AllocatorType& json_allocator =
      json_document.GetAllocator();

  json_document.AddMember("name", "New Project", json_allocator);

  FILE* json_file_ptr;
  fopen_s(&json_file_ptr, project_path.c_str(), "wb");
  UE_CORE_ASSERT(json_file_ptr != nullptr,
                 "Could not open new ./units-project.json");
  char write_buffer[65536];
  rapidjson::FileWriteStream json_write_stream{json_file_ptr, write_buffer,
                                               sizeof(write_buffer)};

  rapidjson::Writer<rapidjson::FileWriteStream> json_writer{json_write_stream};
  if (!json_document.Accept(json_writer)) {
    fclose(json_file_ptr);
    UE_CORE_ASSERT(false, "Could not write to ./units-project.json");
  }

  fclose(json_file_ptr);

  return s_current_project_;
}
void ProjectLoader::unloadProject() noexcept { s_current_project_ = nullptr; }
}  // namespace editor