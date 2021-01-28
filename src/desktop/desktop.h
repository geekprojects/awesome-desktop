#ifndef AWESOME_DESKTOP_DESKTOP_H
#define AWESOME_DESKTOP_DESKTOP_H

#include <geek/gfx-surface.h>
#include <awesome/connection.h>
#include <frontier/frontier.h>
#include <frontier/engines/awesome.h>

#include <vector>

class Screen;
class Window;

class DesktopApp : public Frontier::FrontierApp
{
 private:
    Geek::Gfx::Surface* m_backgroundImage = nullptr;

    std::vector<Screen*> m_screens;
    std::map<uint64_t, Window*> m_windows;

    void handleEvent(Awesome::Event* event);

 public:
    DesktopApp();
    ~DesktopApp() override;

    bool init() override;

    void addWindow(Window* window);

    Awesome::ClientConnection* getConnection() { return ((Frontier::AwesomeEngine*)getEngine())->getConnection(); }
    Geek::Gfx::Surface* getBackgroundImage() const { return m_backgroundImage; }
};

#endif //AWESOME_DESKTOP_DESKTOP_H
