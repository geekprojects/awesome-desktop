//
//

#include "desktop.h"
#include "desktopwindow.h"

using namespace std;
using namespace Awesome;
using namespace Geek;
using namespace Geek::Gfx;

DesktopWindow::DesktopWindow(DesktopApp* app, Geek::Rect rect, float scale)
    : Window(app, L"Desktop", rect, scale, WINDOW_BACKGROUND)
{

}

DesktopWindow::~DesktopWindow()
{

}

void DesktopWindow::draw()
{
    Surface* backgroundImage = m_app->getBackgroundImage();
    int scaledWidth = m_surface->getWidth();
    int scaledHeight = m_surface->getHeight();
    float zx = (float) scaledWidth / (float) backgroundImage->getWidth();
    float zy = (float) scaledHeight / (float) backgroundImage->getHeight();
    Surface* resizedBackground = backgroundImage->scale(MAX(zx, zy));

    m_surface->clear(0);
    m_surface->blit(0, 0, resizedBackground);

    delete resizedBackground;
}
