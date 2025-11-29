#pragma once
#include "UnitsEngine/engine_api.h"
#include "UnitsEngine/app_specs.h"

#include <memory>
#include <type_traits>

namespace Units {
  // Interface class for Application
  class UE_API IApplication {
  public:
    virtual ~IApplication() noexcept;
    // Get Singleton Instance
    template<typename ApplicationType= IApplication>
    static inline ApplicationType* getInstance() noexcept {
      static_assert((std::is_base_of<IApplication, ApplicationType>::value && "ApplicationType must derive from IApplication!"));
      return static_cast<ApplicationType*>(s_instance_ptr_);
    }
    // Runs Application
    void run() const noexcept;
    // Attempts to Quit Application
    void quit() const noexcept;
  protected:
    IApplication(IApplication* p_derived_ptr, AppSpecs&& p_specs) noexcept;
    static inline IApplication* s_instance_ptr_= nullptr;
  };

  // Defined in Client
  extern IApplication* createApplication() noexcept;
} // namespace Units