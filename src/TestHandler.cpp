#include <iostream>
#include <string>
#include "TestHandler.hpp"

/*
 * Anonymous namespaces reduce the visibility of the variables/classes/functions/...
 * declared in the, to just the current compilation unit. It is the recommended way
 * preferred to declaring static const variables.
 */
namespace {
  const std::string pageHeader("<html><body>\n");
  const std::string pageFooter("</body></html>\n");
}

void TestHandler::handle(pion::http::request_ptr& req, pion::tcp::connection_ptr& conn) {
  pion::http::response_writer_ptr respWriter(pion::http::response_writer::create(conn, *req.get(), boost::bind(&pion::tcp::connection::finish, conn)));  
  respWriter->write("<html><title></title><body>");
  respWriter->write("<h1>Hi there</h1>");
  respWriter->write("</body></html>");
  respWriter->send();
  std::cout << "Finished Test Request" << std::endl;
  return;
}

void TestHandler::sendFile(const std::string& path, pion::http::response_writer_ptr& respWriter ) {
  int fd = open(path.c_str(),O_RDONLY);
  if (fd < 0) {
    std::cout << "Coudl not open file " << path << std::endl;
    respWriter->send();
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

void TestHandler::indexRequestHandler(pion::http::request_ptr& req, pion::tcp::connection_ptr& conn)
{
  const std::string& resourcePath = "/opt/julio/content" + req->get_resource();
  std::cout << resourcePath << std::endl;
  pion::http::response_writer_ptr respWriter(pion::http::response_writer::create(conn, *req.get(), boost::bind(&pion::tcp::connection::finish, conn)));
  sendFile(resourcePath, respWriter);
  std::cout << "Finished request for " << resourcePath << std::endl;
  return;
}

void TestHandler::procRequestHandler(pion::http::request_ptr& req, pion::tcp::connection_ptr& conn) {
  const std::string& path = "/proc/meminfo";
  pion::http::response_writer_ptr respWriter(pion::http::response_writer::create(conn, *req.get(), boost::bind(&pion::tcp::connection::finish, conn)));
  sendFile(path, respWriter);
  return;
}
