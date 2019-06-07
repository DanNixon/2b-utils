#include "2b/serial_port.hpp"

namespace estim2b
{
  SerialPort::SerialPort()
      : m_io()
      , m_port(m_io)
      , m_timer(m_io)
  {
  }

  boost::asio::serial_port &SerialPort::port()
  {
    return m_port;
  }

  bool SerialPort::is_open() const
  {
    return m_port.is_open();
  }

  void SerialPort::close()
  {
    if (is_open())
    {
      m_port.close();
    }
  }

  void SerialPort::write(std::string_view const &sv)
  {
    m_port.write_some(boost::asio::buffer(sv, sv.size()));
  }

  std::string SerialPort::read()
  {
    /* Remove any existing buffered data */
    m_data.consume(m_data.size());

    /* Start read */
    m_status = Status::InProgress;
    boost::asio::async_read_until(
        m_port, m_data, "\n",
        boost::bind(&SerialPort::on_read_completed, this,
                    boost::asio::placeholders::error,
                    boost::asio::placeholders::bytes_transferred));

    /* Setup timeout */
    m_timer.expires_from_now(boost::posix_time::milliseconds(500));
    m_timer.async_wait(boost::bind(&SerialPort::on_timeout, this,
                                   boost::asio::placeholders::error));

    for (;;)
    {
      m_io.run_one();

      switch (m_status)
      {
      case Status::Ok:
      {
        m_timer.cancel();

        std::istream is(&m_data);
        std::string result;
        is >> result;
        return result;
      }
      case Status::Timeout:
        m_port.cancel();
        throw std::runtime_error("Serial port timeout");
      case Status::Error:
        m_timer.cancel();
        m_port.cancel();
        throw std::runtime_error("Serial port read error");
      }
    }
  }
  void SerialPort::on_timeout(boost::system::error_code const &error)
  {
    if (!error)
    {
      /* The timer was not cancelled, so the serial port timed out */
      m_port.cancel();
      m_status = Status::Timeout;
    }
  }

  void SerialPort::on_read_completed(boost::system::error_code const &error,
                                     size_t const bytesTransferred)
  {
    if (error)
    {
      m_status = Status::Error;
    }

    m_status = Status::Ok;
  }
} // namespace estim2b
