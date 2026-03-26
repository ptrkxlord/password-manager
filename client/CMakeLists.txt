cmake_minimum_required(VERSION 3.16)
project(ptkxlord LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick QuickControls2 Sql Network)
qt_standard_project_setup()

cmake_policy(SET CMP0135 NEW)
include(FetchContent)

FetchContent_Declare(
  libsodium
  URL      https://download.libsodium.org/libsodium/releases/libsodium-1.0.19-stable-mingw.tar.gz
  URL_HASH SHA256=f67d02f324f9a2b4dd4fb8a61396c8f604099abf55b2aac7b665267c6c708754
  DOWNLOAD_EXTRACT_TIMESTAMP true
)

FetchContent_MakeAvailable(libsodium)

set(SODIUM_INCLUDE_DIR ${libsodium_SOURCE_DIR}/libsodium-win64/include)
# For MinGW, we need the .a file inside the libsodium-win64 subfolder
set(SODIUM_LIBRARY ${libsodium_SOURCE_DIR}/libsodium-win64/lib/libsodium.a)

add_executable(ptkxlord
    src/main.cpp
    src/security/CryptoManager.cpp
    src/security/KeyDerivationService.cpp
    src/storage/DatabaseManager.cpp
    src/domain/VaultManager.cpp
    src/domain/EntryService.cpp
    src/domain/PasswordGenerator.cpp
    src/domain/ClipboardManager.cpp
    src/network/ApiClient.cpp
    src/network/AuthCallbackServer.cpp
)

target_include_directories(ptkxlord PRIVATE 
    src/security 
    src/storage 
    src/domain
    src/network
    ${SODIUM_INCLUDE_DIR}
)

target_link_libraries(ptkxlord PRIVATE 
    Qt6::Core 
    Qt6::Gui 
    Qt6::Qml 
    Qt6::Quick 
    Qt6::QuickControls2
    Qt6::Sql 
    Qt6::Network
    ${SODIUM_LIBRARY}
)

qt_add_qml_module(ptkxlord
    URI ptkxlord
    VERSION 1.0
    QML_FILES src/qml/main.qml
)

install(TARGETS ptkxlord RUNTIME DESTINATION bin)
