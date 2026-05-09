cmake_minimum_required(VERSION 3.28)
project(tho3ban++ LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Prefer a locally installed SFML; fallback to fetching when unavailable.
find_package(SFML 3 QUIET COMPONENTS Graphics Window System)
if(NOT SFML_FOUND)
    include(FetchContent)
    
    set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build static libraries" FORCE) 
    
    set(SFML_BUILD_AUDIO OFF CACHE BOOL "Disable SFML audio module" FORCE)
    set(SFML_BUILD_NETWORK OFF CACHE BOOL "Disable SFML network module" FORCE)
    FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.1.0
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
    FetchContent_MakeAvailable(SFML)
endif()

# Only glob the core files (so we don't mix main.cpp and main_cli.cpp)
file(GLOB_RECURSE THO3BAN_CORE_SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/src/core/*.cpp"
)

# Exclude menu.cpp from the shared core because it requires SFML
list(REMOVE_ITEM THO3BAN_CORE_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/core/menu.cpp")

# ------------------------------
# 1. GUI Executable (tho3ban++)
# ------------------------------
# We explicitly add src/core/menu.cpp here so only the GUI builds it
add_executable(tho3ban src/main.cpp src/core/menu.cpp ${THO3BAN_CORE_SOURCES})
target_compile_features(tho3ban PRIVATE cxx_std_17)
target_link_libraries(tho3ban PRIVATE SFML::Graphics SFML::Window SFML::System)
set_target_properties(tho3ban PROPERTIES OUTPUT_NAME "tho3ban++")

target_link_options(tho3ban PRIVATE -static -static-libgcc -static-libstdc++)

# Automatically copy the resources folder to the output directory after building
add_custom_command(TARGET tho3ban POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_CURRENT_SOURCE_DIR}/resources
    $<TARGET_FILE_DIR:tho3ban>/resources
)

# ------------------------------
# 2. CLI Executable (tho3ban_cli)
# ------------------------------
# This will now safely build without menu.cpp!
add_executable(tho3ban_cli src/main_cli.cpp ${THO3BAN_CORE_SOURCES})
target_compile_features(tho3ban_cli PRIVATE cxx_std_17)

# Make the GUI version the default startup project in Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT tho3ban)