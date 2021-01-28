#ifndef AWESOME_DESKTOP_MENUBARWINDOW_H
#define AWESOME_DESKTOP_MENUBARWINDOW_H

#include "window.h"


class MenuBarWindow : public Window
{
 private:
    void timer(Geek::Core::Timer* timer);

 public:
    MenuBarWindow(DesktopApp* app, Geek::Rect rect, float scale);
    ~MenuBarWindow() override;

    bool init() override;

    void draw() override;
};

#endif //AWESOME_DESKTOP_MENUBARWINDOW_H
