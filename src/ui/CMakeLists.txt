set(UILibrary_SRS
        main.cpp
        MainWindow.cpp
        ScreenImageProvider.cpp
        ColorFinderController.cpp
        JsonParserController.cpp
        ScreenCaptureController.cpp
        ItemImage.cpp
        QUIHelper.cpp
        QLogHelper.cpp
        GlobalStatic.cpp
        ScrcpyController.cpp
        PhoneController.cpp
        VideoItem.cpp
        I420Render.cpp
        ItemOpenGL.cpp
        PackController.cpp
        OpencvController.cpp
        )

set(UILibrary_HEADERS
        MainWindow.h
        ScreenImageProvider.h
        ColorFinderController.h
        JsonParserController.h
        ScreenCaptureController.h
        ItemImage.h
        QUIHelper.h
        QLogHelper.h
        GlobalStatic.h
        ScrcpyController.h
        PhoneController.h
        VideoItem.h
        I420Render.h
        ItemOpenGL.h
        PackController.h
        OpencvController.h
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

if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
    add_executable(${CMAKE_PROJECT_NAME} WIN32 ${UILibrary_SRS} ${UILibrary_RCC} ${PROJECT_SOURCE_DIR}/rc/dotool.rc)
    add_custom_command(TARGET ${PROJECT_NAME}
            POST_BUILD
            COMMAND ${DEPLOYQT_EXECUTABLE} "$<TARGET_FILE:${PROJECT_NAME}>"
            --$<LOWER_CASE:$<CONFIG>> --qmldir ${CMAKE_SOURCE_DIR}
            )
else()
    add_executable(${CMAKE_PROJECT_NAME} ${UILibrary_SRS} ${UILibrary_RCC})
endif()

install(FILES ${UILibrary_HEADERS} DESTINATION include/${CMAKE_PROJECT_NAME}/ui)

target_link_libraries(${CMAKE_PROJECT_NAME}
        QtScrcpy
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Quick
        Qt${QT_VERSION_MAJOR}::QuickControls2
        Qt${QT_VERSION_MAJOR}::Multimedia
        Qt${QT_VERSION_MAJOR}::WebEngine
        ${THIRD_DIR_PATH}/zxing/lib/win64/QZXing3.lib
        ${THIRD_DIR_PATH}/glog/lib/win64/glog.lib
        ${THIRD_DIR_PATH}/opencv/lib/win64/opencv_core455.lib
        ${THIRD_DIR_PATH}/opencv/lib/win64/opencv_imgproc455.lib
        ${THIRD_DIR_PATH}/opencv/lib/win64/opencv_imgcodecs455.lib
        )

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_link_libraries(${CMAKE_PROJECT_NAME}
            ${THIRD_DIR_PATH}/frameless/lib/win64/debug/FramelessHelperd.lib
            ${THIRD_DIR_PATH}/zxing/lib/win64/debug/QZXing3.lib
            ${THIRD_DIR_PATH}/glog/lib/win64/debug/glogd.lib
            ${THIRD_DIR_PATH}/hotkey/lib/win64/qhotkeyd.lib
            )
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    target_link_libraries(${CMAKE_PROJECT_NAME}
            ${THIRD_DIR_PATH}/frameless/lib/win64/release/FramelessHelper.lib
            ${THIRD_DIR_PATH}/zxing/lib/win64/release/QZXing3.lib
            ${THIRD_DIR_PATH}/glog/lib/win64/release/glog.lib
            ${THIRD_DIR_PATH}/hotkey/lib/win64/qhotkey.lib
            )
endif()

target_include_directories(
        ${CMAKE_PROJECT_NAME} SYSTEM PUBLIC
        ${CMAKE_SOURCE_DIR}/src/ui
        ${THIRD_DIR_PATH}/zxing/include
        ${THIRD_DIR_PATH}/frameless/include
        ${THIRD_DIR_PATH}/glog/include
        ${THIRD_DIR_PATH}/hotkey/include
        ${THIRD_DIR_PATH}/opencv/include
)
