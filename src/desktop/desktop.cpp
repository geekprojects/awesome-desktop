//
//

#include "desktop.h"
#include "screen.h"
#include "window.h"

#include <frontier/widgets/label.h>

using namespace std;
using namespace Awesome;
using namespace Frontier;
using namespace Geek;
using namespace Geek::Gfx;

DesktopApp::DesktopApp() : FrontierApp(L"Awesome Desktop")
{
}

DesktopApp::~DesktopApp() = default;

bool DesktopApp::init()
{
    bool res;
    res = FrontierApp::init();
    if (!res)
    {
        return false;
    }

    ((Frontier::AwesomeEngine*)getEngine())->unhandledEventSignal().connect(sigc::mem_fun(*this, &DesktopApp::handleEvent));
    ClientConnection* client = getConnection();

    InfoResponse* info = client->getInfo();
    printf("ads-test: name=%s, vendor=%s\n", info->name, info->vendor);
    printf("ads-test: numDisplays=%d\n", info->numDisplays);

    m_backgroundImage = Surface::loadJPEG("../data/anteater.jpg");

    unsigned int i;
    for (i = 0; i < info->numDisplays; i++)
    {
        InfoDisplayRequest infoDisplayRequest;
        infoDisplayRequest.display = i;
        InfoDisplayResponse* response = (InfoDisplayResponse*)client->send(
            &infoDisplayRequest,
            sizeof(infoDisplayRequest));

        printf("display %u: poa: %d, %d, size: %d, %d\n", i, response->x, response->y, response->width, response->height);

        Screen* screen = new Screen(
            this,
            Geek::Rect(response->x, response->y, response->width, response->height),
            response->scale);
        screen->init();
        m_screens.push_back(screen);

        free(response);
    }

    delete info;

    FrontierWindow* welcomeWindow = new FrontierWindow(this, L"Welcome", Frontier::WINDOW_NORMAL);
    welcomeWindow->setContent(new Label(this, L"Welcome to the Awesome Desktop!"));
    welcomeWindow->show();

    return true;
}

void DesktopApp::handleEvent(Awesome::Event* event)
{
    auto windowIt = m_windows.find(event->windowId);
    Window* window = nullptr;
    if (windowIt != m_windows.end())
    {
        window = windowIt->second;
    }

    log(DEBUG, "handleEvent: Window: %p", window);
    if (window != nullptr)
    {
        window->handleEvent(event);
    }
}

void DesktopApp::addWindow(Window* window)
{
    m_windows.insert(make_pair(window->getMWindowId(), window));
}
