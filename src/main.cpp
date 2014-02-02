// The MIT License (MIT)
// 
// Copyright (c) 2013-2014 Julio Delgado Mangas, julio.delgadomangas@gmail.com
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.


#include <iostream>
#include <string>
#include <pion/http/server.hpp>
#include <pion/process.hpp>
#include <boost/bind.hpp>

#include "TestHandler.hpp"

#define HANDLER(CLASS,METHOD) boost::bind(&METHOD, &CLASS, _1, _2)

int main(int argc, char** argv) {
  std::cout << "[INFO] Starting server on port " << 8080 << std::endl;

  pion::process::initialize();
  pion::http::server server(8080);

  TestHandler testHandler;
 
  server.add_resource("/test", HANDLER(testHandler, TestHandler::handle));
  server.add_resource("/", HANDLER(testHandler, TestHandler::indexRequestHandler));
  server.add_resource("/proc", HANDLER(testHandler, TestHandler::procRequestHandler));
  server.start();
  
  pion::process::wait_for_shutdown();
}
