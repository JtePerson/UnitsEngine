#pragma once
#include <stdint.h>

namespace units {
  // Window Flags
  using WindowFlags= uint64_t;
} // namespace units

#define UE_WINDOW_FULLSCREEN           UINT64_C(0x0000000000000001)    /**< window is in fullscreen mode */
#define UE_WINDOW_OPENGL               UINT64_C(0x0000000000000002)    /**< window usable with OpenGL context */
#define UE_WINDOW_OCCLUDED             UINT64_C(0x0000000000000004)    /**< window is occluded */
// #define UE_WINDOW_HIDDEN               UINT64_C(0x0000000000000008)    /**< window is neither mapped onto the desktop nor shown in the taskbar/dock/window list; UE_ShowWindow() is required for it to become visible */
#define UE_WINDOW_BORDERLESS           UINT64_C(0x0000000000000010)    /**< no window decoration */
#define UE_WINDOW_RESIZABLE            UINT64_C(0x0000000000000020)    /**< window can be resized */
#define UE_WINDOW_MINIMIZED            UINT64_C(0x0000000000000040)    /**< window is minimized */
#define UE_WINDOW_MAXIMIZED            UINT64_C(0x0000000000000080)    /**< window is maximized */
#define UE_WINDOW_MOUSE_GRABBED        UINT64_C(0x0000000000000100)    /**< window has grabbed mouse input */
#define UE_WINDOW_INPUT_FOCUS          UINT64_C(0x0000000000000200)    /**< window has input focus */
#define UE_WINDOW_MOUSE_FOCUS          UINT64_C(0x0000000000000400)    /**< window has mouse focus */
#define UE_WINDOW_EXTERNAL             UINT64_C(0x0000000000000800)    /**< window not created by UnitsEngine */
#define UE_WINDOW_MODAL                UINT64_C(0x0000000000001000)    /**< window is modal */
#define UE_WINDOW_HIGH_PIXEL_DENSITY   UINT64_C(0x0000000000002000)    /**< window uses high pixel density back buffer if possible */
#define UE_WINDOW_MOUSE_CAPTURE        UINT64_C(0x0000000000004000)    /**< window has mouse captured (unrelated to MOUSE_GRABBED) */
#define UE_WINDOW_MOUSE_RELATIVE_MODE  UINT64_C(0x0000000000008000)    /**< window has relative mode enabled */
#define UE_WINDOW_ALWAYS_ON_TOP        UINT64_C(0x0000000000010000)    /**< window should always be above others */
#define UE_WINDOW_UTILITY              UINT64_C(0x0000000000020000)    /**< window should be treated as a utility window, not showing in the task bar and window list */
#define UE_WINDOW_TOOLTIP              UINT64_C(0x0000000000040000)    /**< window should be treated as a tooltip and does not get mouse or keyboard focus, requires a parent window */
#define UE_WINDOW_POPUP_MENU           UINT64_C(0x0000000000080000)    /**< window should be treated as a popup menu, requires a parent window */
#define UE_WINDOW_KEYBOARD_GRABBED     UINT64_C(0x0000000000100000)    /**< window has grabbed keyboard input */
#define UE_WINDOW_VULKAN               UINT64_C(0x0000000010000000)    /**< window usable for Vulkan surface */
#define UE_WINDOW_METAL                UINT64_C(0x0000000020000000)    /**< window usable for Metal view */
#define UE_WINDOW_TRANSPARENT          UINT64_C(0x0000000040000000)    /**< window with transparent buffer */
#define UE_WINDOW_NOT_FOCUSABLE        UINT64_C(0x0000000080000000)    /**< window should not be focusable */