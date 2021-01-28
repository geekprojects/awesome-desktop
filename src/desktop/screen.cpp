//
//

#include "desktop.h"
#include "screen.h"
#include "desktopwindow.h"
#include "menubarwindow.h"

Screen::Screen(DesktopApp* app, Geek::Rect rect, float scale)
{
    m_app = app;
    m_rect = rect;
    m_scale = scale;
}

bool Screen::init()
{
    m_desktopWindow = new DesktopWindow(m_app, m_rect, m_scale);
    m_desktopWindow->create();

    m_menuBarWindow = new MenuBarWindow(m_app, m_rect, m_scale);
    m_menuBarWindow->create();

    return false;
}
