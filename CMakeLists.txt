cmake_minimum_required(VERSION 3.16)
project(awesome-desktop)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
#find_package(Vulkan REQUIRED)

include(FindOpenGL)
pkg_check_modules(libawesome REQUIRED libawesome)
pkg_check_modules(libfrontier REQUIRED libfrontier)

add_definitions(${libawesome_CFLAGS} ${libfrontier_CFLAGS})

#
# awesome-desktop
#
add_executable(
        awesome-desktop
        src/desktop/main.cpp
        src/desktop/desktop.cpp
        src/desktop/screen.cpp
        src/desktop/window.cpp
        src/desktop/desktopwindow.cpp
        src/desktop/menubarwindow.cpp
)
target_link_libraries(awesome-desktop ${libawesome_LDFLAGS} ${libfrontier_LDFLAGS})

#
# awesome-login
#
add_executable(
        awesome-login
        src/login/main.cpp
)
target_link_libraries(awesome-login ${libawesome_LDFLAGS} ${libfrontier_LDFLAGS} -lpam)


