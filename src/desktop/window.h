#ifndef AWESOME_DESKTOP_WINDOW_H
#define AWESOME_DESKTOP_WINDOW_H

#include <wchar.h>

#include <string>
#include <geek/gfx-surface.h>
#include <awesome/connection.h>

class DesktopApp;

class Window
{
 protected:
    DesktopApp* m_app;
    std::wstring m_name;
    Geek::Rect m_rect;
    float m_scale;
    int m_flags;

    uint64_t m_windowId = 0;

 protected:
    Geek::Gfx::Surface* m_surface = nullptr;
    Awesome::ClientSharedMemory* m_csm = nullptr;

 public:
    Window(DesktopApp* app, std::wstring name, Geek::Rect rect, float scale, int flags);
    virtual ~Window();

    virtual bool init();

    bool create();
    void update();
    void close();

    virtual void draw() = 0;
    virtual void handleEvent(Awesome::Event* event);

    uint64_t getMWindowId() const
    {
        return m_windowId;
    }
};

#endif //AWESOME_DESKTOP_WINDOW_H
