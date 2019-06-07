#pragma once

#include "2b/powerbox_digitallink.hpp"
#include "2b/serial_port.hpp"

namespace estim2b
{
  class PowerboxSerial : public PowerboxDigitalLink
  {
  public:
    PowerboxSerial(std::string const &port_name);

    virtual void close_connection();

  protected:
    virtual std::string request_and_response(std::string const &message);

  private:
    SerialPort m_port;
  };
}; // namespace estim2b
