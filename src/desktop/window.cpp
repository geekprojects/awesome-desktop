
#include "desktop.h"
#include "window.h"

using namespace std;
using namespace Awesome;
using namespace Geek;
using namespace Geek::Gfx;

Window::Window(DesktopApp* app, wstring name, Geek::Rect rect, float scale, int flags)
{
    m_app = app;
    m_name = name;
    m_rect = rect;
    m_scale = scale;
    m_flags = flags;
}

Window::~Window()
{

}

bool Window::create()
{
    int scaledWidth = (int)(m_rect.w * m_scale);
    int scaledHeight = (int)(m_rect.h * m_scale);

    ClientConnection* client = m_app->getConnection();

    m_csm = client->createSharedMemory(scaledWidth * scaledHeight * 4);
    m_surface = new Surface(scaledWidth, scaledHeight, 4, (uint8_t*)m_csm->getAddr());

    WindowCreateRequest createWindowRequest;
    createWindowRequest.x = 0;
    createWindowRequest.y = 0;
    createWindowRequest.width = m_rect.w;
    createWindowRequest.height = m_rect.h;
    createWindowRequest.flags = m_flags;
    wcscpy(createWindowRequest.title, m_name.c_str());
    WindowCreateResponse* windowCreateResponse = static_cast<WindowCreateResponse*>(
        client->send(
            &createWindowRequest,
            sizeof(createWindowRequest)));

    m_windowId = windowCreateResponse->windowId;

    m_app->addWindow(this);

    init();

    draw();

    update();

    return true;
}

void Window::update()
{
    WindowUpdateRequest windowUpdateRequest;
    windowUpdateRequest.windowId = m_windowId;
    windowUpdateRequest.width = m_surface->getWidth();
    windowUpdateRequest.height = m_surface->getHeight();
    strncpy(windowUpdateRequest.shmPath, m_csm->getPath().c_str(), 256);
    m_app->getConnection()->send(&windowUpdateRequest, sizeof(windowUpdateRequest));
}

void Window::close()
{

}

void Window::handleEvent(Awesome::Event* event)
{
}

bool Window::init()
{
    return true;
}
