add_subdirectory(app)
add_subdirectory(ui)
add_subdirectory(qtscrcpy)

set(OPENSSL_BIN
        ${THIRD_DIR_PATH}/openssl/libcrypto-1_1-x64.dll
        ${THIRD_DIR_PATH}/openssl/libssl-1_1-x64.dll
        )
install(FILES ${OPENSSL_BIN} DESTINATION bin)

set(ZXING_BIN
        ${THIRD_DIR_PATH}/zxing/msvc/lib/QZXing3.dll
        )
install(FILES ${ZXING_BIN} DESTINATION bin)

set(FFMPEG_BIN
        ${THIRD_DIR_PATH}/ffmpeg/bin/x64/avcodec-58.dll
        ${THIRD_DIR_PATH}/ffmpeg/bin/x64/avformat-58.dll
        ${THIRD_DIR_PATH}/ffmpeg/bin/x64/avutil-56.dll
        ${THIRD_DIR_PATH}/ffmpeg/bin/x64/swresample-3.dll
        ${THIRD_DIR_PATH}/ffmpeg/bin/x64/swscale-5.dll
        )
install(FILES ${FFMPEG_BIN} DESTINATION bin)

set(ADB_BIN
        ${THIRD_DIR_PATH}/adb/win/adb.exe
        ${THIRD_DIR_PATH}/adb/win/AdbWinApi.dll
        ${THIRD_DIR_PATH}/adb/win/AdbWinUsbApi.dll
        )
install(FILES ${ADB_BIN} DESTINATION bin)

set(SCRCPY_BIN
        ${THIRD_DIR_PATH}/scrcpy-server
        )
install(FILES ${SCRCPY_BIN} DESTINATION bin)

set(FRAMELESS_BIN
        ${THIRD_DIR_PATH}/frameless/bin/FramelessHelper.dll
        )
install(FILES ${FRAMELESS_BIN} DESTINATION bin)