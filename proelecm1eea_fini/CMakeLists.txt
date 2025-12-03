cmake_minimum_required(VERSION 3.16)

project(proelecm1eea LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Trouve Qt avec Core + Widgets
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Widgets)

add_executable(proelecm1eea
  main.cpp
  waveformwidget.h waveformwidget.cpp


  # --- Ajout des nouvelles classes ---
  schematicwidget.h schematicwidget.cpp
  inputparser.h inputparser.cpp
  circuitengine.h circuitengine.cpp
  logicsimulator.h logicsimulator.cpp
)



# Ajoute la librairie Qt Widgets au lien
target_link_libraries(proelecm1eea
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Widgets
)

include(GNUInstallDirs)
install(TARGETS proelecm1eea
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
