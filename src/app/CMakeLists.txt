if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_executable(${CMAKE_PROJECT_NAME} WIN32 main.cpp ${PROJECT_SOURCE_DIR}/rc/dotool.rc)
else()
    add_executable(${CMAKE_PROJECT_NAME} WIN32 main.cpp)
endif()

target_link_libraries(${CMAKE_PROJECT_NAME}
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::WebEngine
        UILibrary
        )
install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION bin)
