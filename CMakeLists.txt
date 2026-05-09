cmake_minimum_required(VERSION 3.19)
project(tho3ban LANGUAGES CXX)

find_package(Qt6 6.5 REQUIRED COMPONENTS Core Widgets)

qt_standard_project_setup()

qt_add_executable(tho3ban
    WIN32 MACOSX_BUNDLE
    main.cpp
    tho3ban.cpp
    tho3ban.h
    tho3ban.ui
    src/apple.cpp src/apple.h src/game.cpp src/game.h   src/snake.cpp src/snake.h src/types.cpp src/types.h
    .gitignore

)

target_link_libraries(tho3ban
    PRIVATE
        Qt::Core
        Qt::Widgets
)

install(TARGETS tho3ban
    BUNDLE  DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

qt_generate_deploy_app_script(
    TARGET tho3ban
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
