cmake_minimum_required(VERSION 3.16)

# Include parent directory as the component
get_filename_component(CONSOLE_COMPONENT_DIR "${CMAKE_CURRENT_LIST_DIR}/../.." ABSOLUTE)
set(EXTRA_COMPONENT_DIRS "${CONSOLE_COMPONENT_DIR}")

include($ENV{IDF_PATH}/tools/cmake/project.cmake)
project(basic_console)

