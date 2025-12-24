module;

#ifdef UE_INCLUDE_GLFW
#  include <GLFW/glfw3.h>
#endif

#ifdef __INTELLISENSE__
#  include "../modules/inputs.mpp"
#endif

module units.Inputs;

import units.Events;
import units.Window;

#ifdef UE_INCLUDE_GLFW

namespace units {
  bool Inputs::s_initialized_= false;

  void Inputs::init(void) noexcept {
    if (glfwInit() == GLFW_FALSE)
      return;

    s_initialized_= true;
  }
  void Inputs::quit(void) noexcept {
    if (!s_initialized_)
      return;

    glfwTerminate();
  }

  void Inputs::pollInputs(Events::EventBus& p_event_bus) noexcept {
    if (!s_initialized_)
      return;

    glfwPollEvents();
    Window::pollCloseEvents(p_event_bus);
  }
} // namespace units

#endif