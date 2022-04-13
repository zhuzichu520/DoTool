if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_executable(${CMAKE_PROJECT_NAME} main.cpp ${PROJECT_SOURCE_DIR}/rc/dotool.rc)
else()
    add_executable(${CMAKE_PROJECT_NAME} main.cpp)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(LIB_HOTKEY ${THIRD_DIR_PATH}/hotkey/lib/win64/qhotkeyd.lib)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
  set(LIB_HOTKEY ${THIRD_DIR_PATH}/hotkey/lib/win64/qhotkey.lib)
endif()

target_link_libraries(${CMAKE_PROJECT_NAME}
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::WebEngine
    Qt${QT_VERSION_MAJOR}::Quick
    Qt${QT_VERSION_MAJOR}::QuickControls2
    UILibrary
    ${LIB_HOTKEY}
    )

target_include_directories(
    ${CMAKE_PROJECT_NAME} SYSTEM PUBLIC
    ${THIRD_DIR_PATH}/hotkey/include
    )
install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION bin)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_import_qml_plugins(${CMAKE_PROJECT_NAME})
    qt_finalize_executable(${CMAKE_PROJECT_NAME})
endif()
