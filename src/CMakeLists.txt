ADD_EXECUTABLE(app main.cpp TestHandler.cpp)
TARGET_LINK_LIBRARIES(app ${pion_LIB} ${Boost_LIBRARIES}
  ${OPENSSL_LIBRARIES})

INSTALL(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/app DESTINATION /opt/julio/)