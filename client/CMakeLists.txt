cmake_minimum_required(VERSION 3.16)

project(ptkxlord VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Core Gui Qml Quick Sql)
find_package(PkgConfig REQUIRED)
pkg_check_modules(SODIUM REQUIRED libsodium)

qt_add_executable(ptkxlord
    src/main.cpp
    src/security/CryptoManager.cpp
    src/security/KeyDerivationService.cpp
    src/storage/DatabaseManager.cpp
    src/domain/VaultManager.cpp
    src/domain/EntryService.cpp
    src/qml.qrc
)

target_include_directories(ptkxlord PRIVATE ${SODIUM_INCLUDE_DIRS})

target_link_libraries(ptkxlord PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::Quick
    Qt6::Sql
    ${SODIUM_LIBRARIES}
)

set_target_properties(ptkxlord PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.ptkxlord
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

install(TARGETS ptkxlord
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
