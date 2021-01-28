#include "desktop.h"

int main(int argc, char** argv)
{
    DesktopApp* desktopApp = new DesktopApp();
    desktopApp->init();
    desktopApp->main();

    return 0;
}
