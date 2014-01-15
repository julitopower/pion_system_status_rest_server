#include <iostream>
#include <string>
#include <pion/http/server.hpp>
#include <pion/process.hpp>
#include <boost/bind.hpp>

#include "TestHandler.hpp"

#define HANDLER(CLASS_METHOD) boost::bind(CLASS_METHOD, &testHandler, _1, _2)

int main(int argc, char** argv) {
  std::cout << "[INFO] Starting server on port " << 8080 << std::endl;

  pion::process::initialize();
  pion::http::server server(8080);

  TestHandler testHandler;
 
  server.add_resource("/test", HANDLER(&TestHandler::handle));
  server.add_resource("/", HANDLER(&TestHandler::indexRequestHandler));
  server.add_resource("/proc", HANDLER(&TestHandler::procRequestHandler));
  server.start();
  
  pion::process::wait_for_shutdown();
}
