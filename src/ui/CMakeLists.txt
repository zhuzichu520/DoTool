set(UILibrary_SRS
        MainWindow.cpp
        )

set(UILibrary_HEADERS
        MainWindow.h
        )

set(UILibrary_RCC
        res/qml.qrc
        )

add_library(UILibrary SHARED ${UILibrary_SRS} ${UILibrary_RCC})
install(TARGETS UILibrary LIBRARY DESTINATION lib)
install(FILES ${UILibrary_HEADERS} DESTINATION include/${CMAKE_PROJECT_NAME}/ui)
target_link_libraries(UILibrary
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Quick
        )
target_include_directories(UILibrary SYSTEM PUBLIC ${CMAKE_SOURCE_DIR}/src/ui)
