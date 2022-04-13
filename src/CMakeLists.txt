add_subdirectory(ui)
add_subdirectory(qtscrcpy)

set(OPENSSL_BIN
        ${THIRD_DIR_PATH}/openssl/bin/win64/libcrypto-1_1-x64.dll
        ${THIRD_DIR_PATH}/openssl/bin/win64/libssl-1_1-x64.dll
        )
set(FFMPEG_BIN
        ${THIRD_DIR_PATH}/ffmpeg/bin/win64/avcodec-58.dll
        ${THIRD_DIR_PATH}/ffmpeg/bin/win64/avformat-58.dll
        ${THIRD_DIR_PATH}/ffmpeg/bin/win64/avutil-56.dll
        ${THIRD_DIR_PATH}/ffmpeg/bin/win64/swresample-3.dll
        ${THIRD_DIR_PATH}/ffmpeg/bin/win64/swscale-5.dll
        )
set(ADB_BIN
        ${THIRD_DIR_PATH}/adb/win/adb.exe
        ${THIRD_DIR_PATH}/adb/win/AdbWinApi.dll
        ${THIRD_DIR_PATH}/adb/win/AdbWinUsbApi.dll
        )
set(SCRCPY_BIN
        ${THIRD_DIR_PATH}/scrcpy-server
        )


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(FRAMELESS_BIN
            ${THIRD_DIR_PATH}/frameless/bin/win64/debug/FramelessHelperd.dll
            )

    set(ZXING_BIN
            ${THIRD_DIR_PATH}/zxing/bin/win64/debug/QZXing3.dll
            )

    set(GLOG_BIN
            ${THIRD_DIR_PATH}/glog/bin/win64/debug/glogd.dll
            )
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Release")
    set(FRAMELESS_BIN
            ${THIRD_DIR_PATH}/frameless/bin/win64/release/FramelessHelper.dll
            )

    set(ZXING_BIN
            ${THIRD_DIR_PATH}/zxing/bin/win64/release/QZXing3.dll
            )

    set(GLOG_BIN
            ${THIRD_DIR_PATH}/glog/bin/win64/release/glog.dll
            )
endif()

set(OPENCV_BIN
        ${THIRD_DIR_PATH}/opencv/bin/win64/opencv_core455.dll
        ${THIRD_DIR_PATH}/opencv/bin/win64/opencv_imgcodecs455.dll
        ${THIRD_DIR_PATH}/opencv/bin/win64/opencv_imgproc455.dll
        )

install(FILES ${OPENSSL_BIN} DESTINATION bin)
install(FILES ${ZXING_BIN} DESTINATION bin)
install(FILES ${FFMPEG_BIN} DESTINATION bin)
install(FILES ${ADB_BIN} DESTINATION bin)
install(FILES ${SCRCPY_BIN} DESTINATION bin)
install(FILES ${FRAMELESS_BIN} DESTINATION bin)
install(FILES ${GLOG_BIN} DESTINATION bin)
install(FILES ${OPENCV_BIN} DESTINATION bin)