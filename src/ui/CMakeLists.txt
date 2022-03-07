set(UILibrary_SRS
        MainWindow.cpp
        ScreenImageProvider.cpp
        ColorFinderController.cpp
        JsonParserController.cpp
        ItemImage.cpp
        QUIHelper.cpp
        GlobalStatic.cpp
        )

set(UILibrary_HEADERS
        MainWindow.h
        ScreenImageProvider.h
        ColorFinderController.h
        JsonParserController.h
        ItemImage.h
        QUIHelper.h
        GlobalStatic.h
        )

set(UILibrary_RCC
        res/qml.qrc
        )

add_definitions(-D
        QZXING_QML
        )

add_definitions(-D
        QZXING_MULTIMEDIA
        )

add_library(UILibrary SHARED ${UILibrary_SRS} ${UILibrary_RCC})
install(TARGETS UILibrary LIBRARY DESTINATION lib)
install(FILES ${UILibrary_HEADERS} DESTINATION include/${CMAKE_PROJECT_NAME}/ui)
target_link_libraries(UILibrary
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Quick
        ${THIRD_DIR_PATH}/zxing/msvc/lib/QZXing3.lib
        )
target_include_directories(
        UILibrary SYSTEM PUBLIC
        ${CMAKE_SOURCE_DIR}/src/ui
        ${THIRD_DIR_PATH}/zxing/win64/include
)
