add_executable(${CMAKE_PROJECT_NAME} WIN32 main.cpp)
target_link_libraries(${CMAKE_PROJECT_NAME}
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::WebEngine
        UILibrary
        )
install(TARGETS ${CMAKE_PROJECT_NAME} DESTINATION bin)
