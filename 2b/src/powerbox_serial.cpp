#include "2b/powerbox_serial.hpp"

#include <spdlog/spdlog.h>

namespace estim2b
{
  PowerboxSerial::PowerboxSerial(std::string const &port_name)
      : m_port()
  {
    m_port.port().open(port_name);
    m_port.port().set_option(boost::asio::serial_port_base::baud_rate(9600));
    SPDLOG_INFO("Opened serial port \"{}\" for powerbox communication",
                port_name);
  }

  void PowerboxSerial::close_connection()
  {
    m_port.close();
  }

  std::string PowerboxSerial::request_and_response(std::string const &message)
  {
    SPDLOG_DEBUG("sending message to powerbox: \"{}\"", message);
    m_port.write(message + "\n\r");

    auto const response = m_port.read();
    SPDLOG_DEBUG("response from powerbox: \"{}\"", response);
    return response;
  }
}; // namespace estim2b
