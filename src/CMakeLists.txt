add_subdirectory(app)
add_subdirectory(ui)
add_subdirectory(qtscrcpy)

set(OPENSSL_DLL
        ${THIRD_DIR_PATH}/openssl/libcrypto-1_1-x64.dll
        ${THIRD_DIR_PATH}/openssl/libssl-1_1-x64.dll
        )

install(FILES ${OPENSSL_DLL} DESTINATION bin)

set(ZXING_DLL
        ${THIRD_DIR_PATH}/zxing/msvc/lib/QZXing3.dll
        )

install(FILES ${ZXING_DLL} DESTINATION bin)