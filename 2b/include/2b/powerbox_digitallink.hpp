#pragma once

#include "2b/powerbox.hpp"

namespace estim2b
{
  class PowerboxDigitalLink : public Powerbox
  {
  public:
    virtual void close_connection() = 0;

    virtual void reset();
    virtual void kill();

    virtual void commit();

  protected:
    virtual void update_status();

  protected:
    virtual std::string request_and_response(std::string const &message) = 0;

  private:
    void send_command_and_update_status(const std::string &message);
  };
} // namespace estim2b
