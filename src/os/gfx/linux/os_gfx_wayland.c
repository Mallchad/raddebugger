

B32
wayland_window_open(GFX_LinuxContext* gfx_context, OS_Handle* result,
                    Vec2F32 resolution, OS_WindowFlags flags, String8 title)
{
  NotImplemented;
  return 0;
}

B32
wayland_graphical_init(GFX_LinuxContext* out)
{
  NotImplemented;
  return 0;
}

B32
wayland_get_events(Arena *arena, B32 wait, OS_EventList* out)
{
  NotImplemented;
  return 0;
}

B32
wayland_push_monitors_array(Arena* arena, OS_HandleArray* monitor)
{
  (void)monitor;
  NotImplemented;
  return 0;
}

B32
wayland_monitor_from_window(OS_Handle window, OS_Handle* out_monitor)
{
  NotImplemented;
  return 0;
}

B32
wayland_name_from_monitor(Arena* arena, OS_Handle monitor, String8* result)
{
  NotImplemented;
  return 0;
}
