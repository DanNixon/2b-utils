#include "2b/powerbox.hpp"

namespace estim2b
{
  Status const &Powerbox::status(bool const cached)
  {
    if (!cached)
    {
      update_status();
    }
    return m_status;
  }

  Settings const &Powerbox::staged_settings() const noexcept
  {
    return m_staged_settings;
  }

  void Powerbox::rollback() noexcept
  {
    m_staged_settings.reset();
  }

  void Powerbox::set_power_level(PowerLevel level) noexcept
  {
    m_staged_settings.power_level = level;
  }

  void Powerbox::set_power_level(std::string const &level)
  {
    set_power_level(PowerLevel::_from_string(level.c_str()));
  }

  void Powerbox::set_channel_link(ChannelLink link) noexcept
  {
    m_staged_settings.channel_link = link;
  }

  void Powerbox::set_channel_link(std::string const &link)
  {
    set_channel_link(ChannelLink::_from_string(link.c_str()));
  }

  void Powerbox::set_mode(Mode mode) noexcept
  {
    m_staged_settings.mode = mode;
  }

  void Powerbox::set_mode(std::string const &mode)
  {
    set_mode(Mode::_from_string(mode.c_str()));
  }

  void Powerbox::set_channel_intensity(Channel channel, int intensity)
  {
    if (intensity < 0 || intensity > 100)
    {
      throw std::invalid_argument("Intensity must be in the range 0-100");
    }

    switch (channel)
    {
    case Channel::A:
      m_staged_settings.intensity_channel_a = intensity;
      break;
    case Channel::B:
      m_staged_settings.intensity_channel_b = intensity;
      break;
    }
  }

  void Powerbox::set_channel_intensity(std::string const &channel,
                                       int intensity)
  {
    set_channel_intensity(Channel::_from_string(channel.c_str()), intensity);
  }

  void Powerbox::set_adjustment(Adjustment parameter, int value)
  {
    if (value < 0 || value > 100)
    {
      throw std::invalid_argument("Value must be in the range 2-100");
    }

    switch (parameter)
    {
    case Adjustment::C:
      m_staged_settings.adjustment_c = value;
      break;
    case Adjustment::D:
      m_staged_settings.adjustment_d = value;
      break;
    }
  }

  void Powerbox::set_adjustment(std::string const &parameter, int value)
  {
    set_adjustment(Adjustment::_from_string(parameter.c_str()), value);
  }
} // namespace estim2b
