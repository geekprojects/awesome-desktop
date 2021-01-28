#ifndef AWESOME_DESKTOP_DESKTOPWINDOW_H
#define AWESOME_DESKTOP_DESKTOPWINDOW_H

#include "window.h"

class DesktopWindow : public Window
{
 public:
    DesktopWindow(DesktopApp* app, Geek::Rect rect, float scale);
    ~DesktopWindow() override;

    void draw() override;
};

#endif //AWESOME_DESKTOP_DESKTOPWINDOW_H
