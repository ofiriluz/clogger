ADD_EXECUTABLE(clogger_test src/test.cpp)
TARGET_COMPILE_FEATURES(clogger_test PRIVATE cxx_auto_type)
TARGET_LINK_LIBRARIES(clogger_test CLogger::clogger)