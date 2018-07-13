CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
PROJECT(clogger VERSION 1.1.0 LANGUAGES CXX)

INCLUDE_DIRECTORIES(include)

ADD_LIBRARY(clogger
    src/CChannel.cpp
    src/CConfig.cpp
    src/CLog.cpp
    src/CLogger.cpp
    src/CManager.cpp
    src/CWriters/CWriter.cpp
    src/CWriters/CConsoleWriter.cpp
    src/CWriters/CFileWriter.cpp
    src/CWriters/CSysLogWriter.cpp
    src/CWriters/CWriterFactory.cpp)

ADD_LIBRARY(CLogger::clogger ALIAS clogger)
    
TARGET_INCLUDE_DIRECTORIES(clogger
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/src
)

TARGET_COMPILE_FEATURES(clogger PRIVATE cxx_auto_type)
TARGET_COMPILE_OPTIONS(clogger PRIVATE $<$<CXX_COMPILER_ID:GNU>:-Wall>)

INCLUDE(GNUInstallDirs)
SET(INSTALL_CONFIGDIR ${CMAKE_INSTALL_LIBDIR}/cmake/CLogger)

INSTALL(TARGETS clogger
    EXPORT clogger-targets
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

SET_TARGET_PROPERTIES(clogger PROPERTIES EXPORT_NAME CLogger)

INSTALL(DIRECTORY include/ 
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

INSTALL(EXPORT clogger-targets
    FILE
        CLoggerTargets.cmake
    NAMESPACE
        CLogger::
    DESTINATION
        ${INSTALL_CONFIGDIR}
)

INCLUDE(CMakePackageConfigHelpers)
WRITE_BASIC_PACKAGE_VERSION_FILE(
    ${CMAKE_CURRENT_BINARY_DIR}/CLoggerConfigVersion.cmake
    VERSION ${PROJECT_VERSION}
    COMPATIBILITY AnyNewerVersion
)

INSTALL(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/CLoggerConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/CLoggerConfigVersion.cmake
    DESTINATION 
        ${INSTALL_CONFIGDIR}
)

CONFIGURE_PACKAGE_CONFIG_FILE(
    ${CMAKE_CURRENT_LIST_DIR}/cmake/CLoggerConfig.cmake.in
    ${CMAKE_CURRENT_BINARY_DIR}/CLoggerConfig.cmake
    INSTALL_DESTINATION 
        ${INSTALL_CONFIGDIR}
)

EXPORT(EXPORT clogger-targets FILE ${CMAKE_CURRENT_BINARY_DIR}/CLoggerTargets.cmake NAMESPACE CLogger::)

EXPORT(PACKAGE CLogger)

ADD_SUBDIRECTORY(tests)