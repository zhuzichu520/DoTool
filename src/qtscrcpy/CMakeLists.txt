set(QtScrcpy_HEADERS
        adb/adbprocess.h
        common/qscrcpyevent.h
        device/android/input.h
        device/android/keycodes.h
        device/controller/controller.h
        device/controller/inputconvert/inputconvertbase.h
        device/controller/inputconvert/inputconvertnormal.h
        device/controller/inputconvert/inputconvertgame.h
        device/controller/inputconvert/controlmsg.h
        device/controller/inputconvert/keymap/keymap.h
        device/controller/receiver/devicemsg.h
        device/controller/receiver/receiver.h
        device/decoder/avframeconvert.h
        device/decoder/decoder.h
        device/decoder/fpscounter.h
        device/decoder/videobuffer.h
        device/filehandler/filehandler.h
        device/recorder/recorder.h
        device/server/server.h
        device/server/tcpserver.h
        device/server/videosocket.h
        device/stream/stream.h
        util/compat.h
        util/config.h
        util/bufferutil.h
        util/mousetap/mousetap.h
        util/mousetap/winmousetap.h
        )

set(QtScrcpy_SRS
        adb/adbprocess.cpp
        device/controller/controller.cpp
        device/controller/inputconvert/inputconvertbase.cpp
        device/controller/inputconvert/inputconvertnormal.cpp
        device/controller/inputconvert/inputconvertgame.cpp
        device/controller/inputconvert/controlmsg.cpp
        device/controller/inputconvert/keymap/keymap.cpp
        device/controller/receiver/devicemsg.cpp
        device/controller/receiver/receiver.cpp
        device/decoder/avframeconvert.cpp
        device/decoder/decoder.cpp
        device/decoder/fpscounter.cpp
        device/decoder/videobuffer.cpp
        device/filehandler/filehandler.cpp
        device/recorder/recorder.cpp
        device/server/server.cpp
        device/server/tcpserver.cpp
        device/server/videosocket.cpp
        device/stream/stream.cpp
        util/config.cpp
        util/bufferutil.cpp
        util/mousetap/mousetap.cpp
        util/mousetap/winmousetap.cpp
        )

add_library(QtScrcpy STATIC ${QtScrcpy_SRS})

install(TARGETS QtScrcpy LIBRARY DESTINATION lib)
install(FILES ${QtScrcpy_HEADERS} DESTINATION include/${CMAKE_PROJECT_NAME}/qtscrcpy)

target_link_libraries(QtScrcpy
        Qt${QT_VERSION_MAJOR}::Core
        Qt${QT_VERSION_MAJOR}::Quick
        Qt${QT_VERSION_MAJOR}::Multimedia
        ${THIRD_DIR_PATH}/ffmpeg/lib/x64/avcodec.lib
        ${THIRD_DIR_PATH}/ffmpeg/lib/x64/avformat.lib
        ${THIRD_DIR_PATH}/ffmpeg/lib/x64/avutil.lib
        ${THIRD_DIR_PATH}/ffmpeg/lib/x64/swresample.lib
        ${THIRD_DIR_PATH}/ffmpeg/lib/x64/swscale.lib
        )

target_include_directories(
        QtScrcpy SYSTEM PUBLIC
        ${THIRD_DIR_PATH}/ffmpeg/include
        adb
        common
        util
        device/android
        device/controller
        device/decoder
        device/filehandler
        device/recorder
        device/server
        device/stream
        device/controller/receiver
        device/controller/inputconvert
        device/controller/inputconvert/keymap
)

