#-----------------------------------------------------------------------------
# Umicom Operations Module
# File: CMakeLists.txt
#
# PURPOSE:
#   Build a thin C23 product composition over Framework-owned application
#   experience, runtime and workbench contracts.
#
# Created by: Sammy Hegab
# Organisation: Umicom Foundation
# Licence: MIT
#-----------------------------------------------------------------------------
cmake_minimum_required(VERSION 3.24)

project(
    OperationsModule
    VERSION 0.1.0
    DESCRIPTION "Thin Umicom Operations composition over Umicom Framework"
    LANGUAGES C
)

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

option(UMICOM_OPERATIONS_BUILD_CONSOLE
       "Build the native Umicom Operations verification console"
       ON)

include(CTest)
include(GNUInstallDirs)

if(NOT TARGET Umicom::Framework)
    find_package(UmicomFramework CONFIG REQUIRED)
endif()

if(NOT TARGET Umicom::application)
    message(FATAL_ERROR
        "Umicom Operations requires Framework target Umicom::application")
endif()

if(NOT COMMAND umicom_apply_warnings)
    function(umicom_apply_warnings target)
        if(MSVC)
            target_compile_options(${target} PRIVATE /W4)
        else()
            target_compile_options(${target} PRIVATE
                -Wall -Wextra -Wpedantic -Wconversion -Wshadow)
        endif()
    endfunction()
endif()

if(NOT COMMAND umicom_apply_sanitizers)
    function(umicom_apply_sanitizers target)
    endfunction()
endif()

add_library(umicom_operations_module STATIC
    src/application.c
    src/workspace.c
)
add_library(Umicom::operations_module ALIAS umicom_operations_module)

target_include_directories(umicom_operations_module PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)
target_link_libraries(umicom_operations_module PUBLIC
    Umicom::Framework
    Umicom::application
)
umicom_apply_warnings(umicom_operations_module)
umicom_apply_sanitizers(umicom_operations_module)

if(UMICOM_OPERATIONS_BUILD_CONSOLE)
    add_executable(umicom-operations-console
        src/console/main.c)
    target_link_libraries(umicom-operations-console PRIVATE Umicom::operations_module)
    umicom_apply_warnings(umicom-operations-console)
    umicom_apply_sanitizers(umicom-operations-console)
endif()

if(BUILD_TESTING)
    add_executable(operations-application-test
        tests/test_application.c)
    target_link_libraries(operations-application-test PRIVATE Umicom::operations_module)
    umicom_apply_warnings(operations-application-test)
    umicom_apply_sanitizers(operations-application-test)
    add_test(NAME operations.module.application
             COMMAND operations-application-test)

    add_executable(operations-workspace-test
        tests/test_workspace.c)
    target_link_libraries(operations-workspace-test PRIVATE Umicom::operations_module)
    umicom_apply_warnings(operations-workspace-test)
    umicom_apply_sanitizers(operations-workspace-test)
    add_test(NAME operations.module.workspace
             COMMAND operations-workspace-test)
endif()

install(TARGETS umicom_operations_module
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
if(TARGET umicom-operations-console)
    install(TARGETS umicom-operations-console
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif()
install(DIRECTORY include/
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(FILES application.umicom.yaml
    DESTINATION ${CMAKE_INSTALL_DATADIR}/umicom/applications/operations)
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")
    install(FILES LICENSE
        DESTINATION ${CMAKE_INSTALL_DATADIR}/licenses/operations)
endif()

message(STATUS "Umicom Operations Module version: ${PROJECT_VERSION}")
message(STATUS "Umicom Operations uses Framework-owned application experience")
