find_package(Qt6 REQUIRED COMPONENTS Core Gui Widgets)
find_package(Qt6 REQUIRED COMPONENTS GuiPrivate WidgetsPrivate)

set(widgetstyle_SRCS
    basestyle.cpp
    blurhelper.cpp
    shadowhelper.cpp
    pstyleplugin.cpp
    phantomcolor.cpp
    boxshadowrenderer.cpp
    tileset.cpp
)

add_library(cutefish-style MODULE ${widgetstyle_SRCS})

target_link_libraries(cutefish-style PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::GuiPrivate
    Qt6::Widgets
    Qt6::WidgetsPrivate
)

install(TARGETS cutefish-style DESTINATION ${QT6_INSTALL_PLUGINS}/styles)
