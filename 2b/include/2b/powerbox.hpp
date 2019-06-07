#pragma once

#include "2b/protocol.hpp"

namespace estim2b
{
  class Powerbox
  {
  public:
    virtual void close_connection() = 0;

    virtual void reset() = 0;
    virtual void kill() = 0;

    Status const &status(bool const cached = false);
    Settings const &staged_settings() const noexcept;

    void rollback() noexcept;
    virtual void commit() = 0;

    void set_power_level(PowerLevel level) noexcept;
    void set_power_level(std::string const &level);

    void set_channel_link(ChannelLink link) noexcept;
    void set_channel_link(std::string const &link);

    void set_mode(Mode mode) noexcept;
    void set_mode(std::string const &mode);

    void set_channel_intensity(Channel channel, int intensity);
    void set_channel_intensity(std::string const &channel, int intensity);

    void set_adjustment(Adjustment parameter, int value);
    void set_adjustment(std::string const &parameter, int value);

  protected:
    virtual void update_status() = 0;

  protected:
    Settings m_staged_settings;
    Status m_status;
  };
} // namespace estim2b
