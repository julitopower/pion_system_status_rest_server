#include <iostream>
#include <string>
#include <pion/http/server.hpp>
#include <pion/process.hpp>
#include <pion/http/request.hpp>
#include <pion/http/response.hpp>
#include <pion/http/response_writer.hpp>

#include <cstdio>

static const std::string pageHeader("<html><body>\n");
static const std::string pageFooter("</body></html>\n");

void sendFile(const char* path, pion::http::response_writer_ptr& respWriter ) {
  int fd = open(path,O_RDONLY);
  if (fd < 0) {
    std::cout << "Coudl not open file " << path << std::endl;
    return;
  }
  int n;
  char buffer[4096];
  while ((n = read(fd, buffer, 4096)) > 0) {
    buffer[n] = 0;
    respWriter->write(buffer);
  }
  close(fd);
  respWriter->send();
}

void indexRequestHandler(pion::http::request_ptr& req, pion::tcp::connection_ptr& conn)
{
  /*
  
  respWriter->write_no_copy(pageHeader);
  respWriter->write("<h1>Hi there</h1>");
  respWriter->write_no_copy(pageFooter);
  respWriter->send();
  */
  char path[] = "/opt/julio/content/index.html";
  pion::http::response_writer_ptr respWriter(pion::http::response_writer::create(conn, *req.get()));
  sendFile(path, respWriter);
  return;
}

void procRequestHandler(pion::http::request_ptr& req, pion::tcp::connection_ptr& conn) {
  char path[] = "/proc/meminfo";
  pion::http::response_writer_ptr respWriter(pion::http::response_writer::create(conn, *req.get()));
  sendFile(path, respWriter);
  return;
}
int main(int argc, char** argv) {
  std::cout << "[INFO] Starting server on port " << 8080 << std::endl;
  pion::process::initialize();
  pion::http::server server(8080);
  server.add_resource("/", &indexRequestHandler);
  server.add_resource("/proc/", &procRequestHandler);
  server.start();
  pion::process::wait_for_shutdown();
}
