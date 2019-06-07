#include "2b/powerbox_digitallink.hpp"

namespace estim2b
{
  void PowerboxDigitalLink::reset()
  {
    std::string const message{"E"};
    send_command_and_update_status(message);
  }

  void PowerboxDigitalLink::kill()
  {
    std::string const message{"K"};
    send_command_and_update_status(message);
  }

  void PowerboxDigitalLink::commit()
  {
    if (m_staged_settings.power_level != std::nullopt)
    {
      std::string const message{(*m_staged_settings.power_level)._value};
      send_command_and_update_status(message);
    }

    if (m_staged_settings.channel_link != std::nullopt)
    {
      std::string const message =
          "J" + std::to_string((*m_staged_settings.channel_link)._value);
      send_command_and_update_status(message);
    }

    if (m_staged_settings.mode != std::nullopt)
    {
      std::string const message =
          "M" + std::to_string((*m_staged_settings.mode)._value);
      send_command_and_update_status(message);
    }

    if (m_staged_settings.intensity_channel_a != std::nullopt)
    {
      std::string message{static_cast<Channel>(Channel::A)._value};
      message += std::to_string(*m_staged_settings.intensity_channel_a);
      send_command_and_update_status(message);
    }

    if (m_staged_settings.intensity_channel_b != std::nullopt)
    {
      std::string message{static_cast<Channel>(Channel::B)._value};
      message += std::to_string(*m_staged_settings.intensity_channel_b);
      send_command_and_update_status(message);
    }

    if (m_staged_settings.adjustment_c != std::nullopt)
    {
      std::string message{static_cast<Adjustment>(Adjustment::C)._value};
      message += std::to_string(*m_staged_settings.adjustment_c);
      send_command_and_update_status(message);
    }

    if (m_staged_settings.adjustment_d != std::nullopt)
    {
      std::string message{static_cast<Adjustment>(Adjustment::D)._value};
      message += std::to_string(*m_staged_settings.adjustment_d);
      send_command_and_update_status(message);
    }

    m_staged_settings.reset();
  }

  void PowerboxDigitalLink::update_status()
  {
    send_command_and_update_status("");
  }

  void PowerboxDigitalLink::send_command_and_update_status(
      const std::string &message)
  {
    auto const response = request_and_response(message);
    m_status = decode_status_message(response);
  }
} // namespace estim2b
