#ifndef AWESOME_DESKTOP_SCREEN_H
#define AWESOME_DESKTOP_SCREEN_H

class DesktopApp;
class Window;
class DesktopWindow;
class MenuBarWindow;

class Screen
{
 private:
    DesktopApp* m_app = nullptr;
    Geek::Rect m_rect;
    float m_scale;


    DesktopWindow* m_desktopWindow = nullptr;
    MenuBarWindow* m_menuBarWindow = nullptr;

 public:
    Screen(DesktopApp* app, Geek::Rect rect, float scale);
    ~Screen();

    bool init();

};

#endif //AWESOME_DESKTOP_SCREEN_H
