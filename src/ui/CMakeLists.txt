set(UILibrary_SRS
    MainWindow.cpp
    ScreenImageProvider.cpp
    ColorPickerController.cpp
    JsonParserController.cpp
    BBDownloaderController.cpp
    QrCode.cpp
    Network.cpp
    ItemImage.cpp
    Settings.cpp
    Extractor.cpp
    Utils.cpp
    )

set(UILibrary_HEADERS
        MainWindow.h
        ScreenImageProvider.h
        ColorPickerController.h
        JsonParserController.h
        BBDownloaderController.h
        QrCode.h
        Network.h
        ItemImage.h
        Settings.h
        Extractor.h
        Utils.h
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

add_library(UILibrary SHARED ${UILibrary_HEADERS} ${UILibrary_SRS} ${UILibrary_RCC})
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
