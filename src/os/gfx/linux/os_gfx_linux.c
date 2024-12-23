

global B32 gfx_lnx_wayland_preferred = 0;
global B32 gfx_lnx_wayland_disabled = 1;
global S32 gfx_egl_version_major = 0;
global S32 gfx_egl_version_minor = 0;
global U8* gfx_default_window_name = (U8*)"raddebugger";
GFX_Context gfx_context = {0};

global EGLContext gfx_egl_context = NULL;
global EGLDisplay gfx_egl_display = NULL;
global EGLSurface gfx_egl_draw_surface = NULL;
global EGLSurface gfx_egl_read_surface = NULL;
global S32 num_config;
global S32 gfx_egl_config[] = {
  EGL_SURFACE_TYPE,
  EGL_WINDOW_BIT, EGL_RENDERABLE_TYPE,
  EGL_OPENGL_BIT,
  EGL_NONE
};
EGLConfig gfx_egl_config_available[10];
global S32 gfx_egl_config_available_size = 0;
global S32 gfx_egl_context_config[] = {
  EGL_CONTEXT_CLIENT_VERSION,
  2,
  EGL_NONE
};


////////////////////////////////
//~ rjf: @os_hooks Main Initialization API (Implemented Per-OS)

/* NOTE(mallchad): The Linux graphic stack is messy and born out of this was
 * EGL, yet another khronos API. To me, this seems to solve no end user
 * problem, in fact it is actually more or less more work than using Xlib/xcb
 * and Wayland backends directly. However, they claim, EGL allows them to
 * solve backend technical problems with refresh orchestration, surface
 * resource management, graphics acceleration orchestration and the like.
 *
 * I have no idea the validity of this. And I would love to know the validty of
 * this, because the graphisc bugs on Linux are absurd and very few competent
 * people seems to know where exactly they come from. but Wayland *REQUIRES*
 * it. So be it.
 */

// Stub
B32
wayland_graphical_init(GFX_Context* out)
{ NotImplemented; }

internal void
os_graphical_init(void)
{
  gfx_context.window_name = gfx_default_window_name;
  gfx_context.default_window_size = vec_2s32(500, 500);
  gfx_context.window_size = gfx_context.default_window_size;
  gfx_context.default_window_pos = vec_2s32(500, 500);
  gfx_context.window_pos = gfx_context.default_window_pos;

  B32 init_result = 0;
  if (gfx_lnx_wayland_disabled)
  { init_result = x11_graphical_init(&gfx_context); }
  else
  { init_result = wayland_graphical_init(&gfx_context); }
  Assert(init_result);

  // Initialize EGL - Windowing Agnostic
  gfx_egl_display = eglGetDisplay(gfx_context.native_server);
  // Generate a stubby window on fail
  if (gfx_egl_display == EGL_NO_DISPLAY)
  { gfx_egl_display = eglGetDisplay((EGLNativeDisplayType)EGL_DEFAULT_DISPLAY); }
  Assert(gfx_egl_display != EGL_NO_DISPLAY);

  // NOTE: EGL_TRUE (1) if success, otherwise EGL_FALSE (0) or error code
  B32 egl_initial_result = eglInitialize(gfx_egl_display, &gfx_egl_version_minor,
                                         &gfx_egl_version_major);
  B32 egl_config_result = eglChooseConfig(gfx_egl_display, gfx_egl_config, gfx_egl_config_available,
                                          10, &gfx_egl_config_available_size);
  gfx_egl_draw_surface = eglCreateWindowSurface(gfx_egl_display, gfx_egl_config_available[0],
                                                (EGLNativeWindowType)gfx_context.native_window, NULL);
  gfx_egl_read_surface = eglCreateWindowSurface(gfx_egl_display, gfx_egl_config_available[0],
                                                (EGLNativeWindowType)gfx_context.native_window, NULL);
  B32 egl_bind_result = eglBindAPI(EGL_OPENGL_API);
  Assert(gfx_egl_config_available_size > 0);
  Assert(egl_initial_result == 1 && egl_config_result == 1 && egl_bind_result == 1);
  EGLConfig select_config = gfx_egl_config_available[0];
  gfx_egl_context = eglCreateContext(gfx_egl_display, select_config,
                                     EGL_NO_CONTEXT, gfx_egl_context_config );
  Assert(gfx_egl_context != EGL_NO_CONTEXT);
   eglMakeCurrent(gfx_egl_display, gfx_egl_draw_surface, gfx_egl_draw_surface, gfx_egl_context);

  Vec4F32 dark_magenta = vec_4f32( 0.2f, 0.f, 0.2f, 1.0f );
while (1){
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
  glClear( GL_COLOR_BUFFER_BIT  | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT );
  glClearColor(dark_magenta.x, dark_magenta.y, dark_magenta.z, dark_magenta.w);
  S32 swap_result =eglSwapBuffers(gfx_egl_display, gfx_egl_draw_surface);
  S32 err = eglGetError();
  Trap();
  static int i = 0;
  ++i;
}
}


////////////////////////////////
//~ rjf: @os_hooks Clipboards (Implemented Per-OS)

internal void
os_set_clipboard_text(String8 string)
{

NotImplemented;}

internal String8
os_get_clipboard_text(Arena *arena)
{
  String8 result = {0};
  return result;
NotImplemented;}

////////////////////////////////
//~ rjf: @os_hooks Windows (Implemented Per-OS)

internal OS_Handle
os_window_open(Vec2F32 resolution, OS_WindowFlags flags, String8 title)
{
  OS_Handle result = {0};
  return result;
NotImplemented;}
internal void
os_window_close(OS_Handle window)
{

NotImplemented;}

internal void
os_window_first_paint(OS_Handle window)
{

NotImplemented;}
internal void
os_window_equip_repaint(OS_Handle window, OS_WindowRepaintFunctionType *repaint,  void *user_data)
{

NotImplemented;}

internal void
os_window_focus(OS_Handle window)
{

NotImplemented;}

internal B32
os_window_is_focused(OS_Handle window)
{
  return 0;
NotImplemented;}

internal B32
os_window_is_fullscreen(OS_Handle window)
{
  return 0;
NotImplemented;}

internal void
os_window_set_fullscreen(OS_Handle window, B32 fullscreen)
{

NotImplemented;}

internal B32
os_window_is_maximized(OS_Handle window)
{

NotImplemented;}

internal void
os_window_set_maximized(OS_Handle window, B32 maximized)
{

NotImplemented;}

internal void
os_window_minimize(OS_Handle window)
{

NotImplemented;}

internal void
os_window_bring_to_front(OS_Handle window)
{

NotImplemented;}

internal void
os_window_set_monitor(OS_Handle window, OS_Handle monitor)
{

NotImplemented;}

internal void
os_window_clear_custom_border_data(OS_Handle handle)
{

NotImplemented;}

internal void
os_window_push_custom_title_bar(OS_Handle handle, F32 thickness)
{

NotImplemented;}

internal void
os_window_push_custom_edges(OS_Handle handle, F32 thickness)
{

NotImplemented;}

internal void
os_window_push_custom_title_bar_client_area(OS_Handle handle, Rng2F32 rect)
{

NotImplemented;}

internal Rng2F32
os_rect_from_window(OS_Handle window)
{

NotImplemented;}

internal Rng2F32
os_client_rect_from_window(OS_Handle window)
{

NotImplemented;}

internal F32
os_dpi_from_window(OS_Handle window)
{
  return 0.f;
NotImplemented;}


////////////////////////////////
//~ rjf: @os_hooks Monitors (Implemented Per-OS)

internal OS_HandleArray
os_push_monitors_array(Arena *arena)
{
NotImplemented;}

internal OS_Handle
os_primary_monitor(void)
{
  OS_Handle result = {0};
  return result;
  NotImplemented;}

internal OS_Handle
os_monitor_from_window(OS_Handle window)
{
  NotImplemented;
  OS_Handle result = {0};
  return result;
}

internal String8
os_name_from_monitor(Arena *arena, OS_Handle monitor)
{
  NotImplemented;
}

internal Vec2F32
os_dim_from_monitor(OS_Handle monitor)
{
  NotImplemented;
}


////////////////////////////////
//~ rjf: @os_hooks Events (Implemented Per-OS)

internal void
os_send_wakeup_event(void)
{
NotImplemented;}

internal OS_EventList
os_get_events(Arena *arena, B32 wait)
{
NotImplemented;}

internal OS_EventFlags
os_get_event_flags(void)
{
NotImplemented;}

internal B32
os_key_is_down(OS_Key key)
{
NotImplemented;}

internal Vec2F32
os_mouse_from_window(OS_Handle window)
{
NotImplemented;}


////////////////////////////////
//~ rjf: @os_hooks Cursors (Implemented Per-OS)

internal void
os_set_cursor(OS_Cursor cursor)
{
NotImplemented;}


////////////////////////////////
//~ rjf: @os_hooks System Properties (Implemented Per-OS)

internal F32
os_double_click_time(void)
{
  return 0.f;
  NotImplemented;
}

internal F32
os_caret_blink_time(void)
{
  return 0.f;
NotImplemented;}

internal F32
os_default_refresh_rate(void)
{
  return 0.f;
NotImplemented;}


////////////////////////////////
//~ rjf: @os_hooks Native Messages & Panics (Implemented Per-OS)

internal void
os_graphical_message(B32 error, String8 title, String8 message)
{

NotImplemented;}
