find_package(Qt6 REQUIRED COMPONENTS Core Gui DBus Widgets)
find_package(Qt6 REQUIRED COMPONENTS GuiPrivate DBusPrivate)
find_package(KF6WindowSystem REQUIRED) # 关键：引入 KF6 版本
find_package(X11 REQUIRED)

set(platformtheme_SRCS
    platformtheme.cpp
    main.cpp
    hintsettings.cpp
    qdbusmenubar.cpp
    systemtrayicon.cpp
    x11integration.cpp
)

qt6_add_dbus_interface(platformtheme_SRCS org.kde.StatusNotifierWatcher.xml statusnotifierwatcher_interface)

add_library(cutefish-platformtheme MODULE ${platformtheme_SRCS})

target_link_libraries(cutefish-platformtheme PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::GuiPrivate
    Qt6::DBus
    Qt6::DBusPrivate
    Qt6::Widgets
    KF6::WindowSystem
    ${X11_LIBRARIES} xcb
)

install(TARGETS cutefish-platformtheme DESTINATION ${QT6_INSTALL_PLUGINS}/platformthemes)
