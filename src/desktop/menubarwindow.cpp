//
//
#include "desktop.h"
#include "menubarwindow.h"

#include <geek/core-timers.h>

using namespace std;
using namespace Awesome;
using namespace Geek;
using namespace Geek::Core;
using namespace Geek::Gfx;

MenuBarWindow::MenuBarWindow(DesktopApp* app, Geek::Rect rect, float scale)
    : Window(app, L"MenuBar", Geek::Rect(rect.x, rect.y, rect.w, 24), scale, WINDOW_FOREGROUND)
{
}

MenuBarWindow::~MenuBarWindow() = default;

bool MenuBarWindow::init()
{
    Timer* timer = new Timer(TIMER_PERIODIC, 1000);
    timer->signal().connect(sigc::mem_fun(*this, &MenuBarWindow::timer));
    m_app->getTimerManager()->addTimer(timer);

    return true;
}

void MenuBarWindow::draw()
{
    m_surface->clear(0xffffffff);
    m_surface->drawLine(0, 47, m_surface->getWidth() - 1, 47, 0xff000000);

    int scaledFontHeight = (int)(12 * m_scale);

    FontManager* fontManager = m_app->getFontManager();
    FontHandle* titleFont = fontManager->openFont("Helvetica Neue", "Bold", scaledFontHeight);
    fontManager->write(titleFont, m_surface, 10, 10, L"A", 0x0, true, nullptr);
    fontManager->write(titleFont, m_surface, 40, 10, L"Awesome", 0x0, true, nullptr);
    FontHandle* menuFont = fontManager->openFont("Helvetica Neue", "Regular", scaledFontHeight);
    fontManager->write(menuFont, m_surface, 250, 10, L"File", 0x0, true, nullptr);
    fontManager->write(menuFont, m_surface, 300, 10, L"Edit", 0x0, true, nullptr);

    wchar_t timeStr[256];
    time_t t;
    t = time(nullptr);

    struct tm tm;
    localtime_r(&t, &tm);

    wcsftime(timeStr, 256, L"%d %b %Y %H:%M", &tm);
    int width = fontManager->width(menuFont, timeStr);
    fontManager->write(menuFont, m_surface, m_surface->getWidth() - (width + 10), 10, timeStr, 0x0, true, nullptr);
}

void MenuBarWindow::timer(Geek::Core::Timer*)
{
    draw();
    update();
}

