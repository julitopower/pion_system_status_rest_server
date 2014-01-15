#ifndef TEST_HANDLER_H
#define TEST_HANDLER_H
#include <pion/http/request.hpp>
#include <pion/http/response.hpp>
#include <pion/http/response_writer.hpp>

class TestHandler {

public:
  void handle(pion::http::request_ptr& req, pion::tcp::connection_ptr& conn);
  void indexRequestHandler(pion::http::request_ptr& req, pion::tcp::connection_ptr& conn);
  void procRequestHandler(pion::http::request_ptr& req, pion::tcp::connection_ptr& conn);

private:
  void sendFile(const std::string& path, pion::http::response_writer_ptr& respWriter);
};


#endif // TEST_HANDLER_H
