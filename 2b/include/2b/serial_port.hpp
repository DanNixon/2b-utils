#pragma once

#include <string>
#include <string_view>

#include <boost/asio.hpp>
#include <boost/asio/serial_port.hpp>
#include <boost/bind.hpp>

namespace estim2b
{
  class SerialPort
  {
  public:
    enum class Status
    {
      None,
      InProgress,
      Ok,
      Timeout,
      Error,
    };

  public:
    SerialPort();

    boost::asio::serial_port &port();

    bool is_open() const;
    void close();

    void write(std::string_view const &sv);
    std::string read();

  private:
    void on_timeout(boost::system::error_code const &error);
    void on_read_completed(boost::system::error_code const &error,
                           size_t const bytesTransferred);

  private:
    boost::asio::io_service m_io;
    boost::asio::serial_port m_port;
    boost::asio::deadline_timer m_timer;

    boost::asio::streambuf m_data;
    Status m_status;
  };
} // namespace estim2b
