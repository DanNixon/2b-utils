#include "2b/protocol.hpp"

#include <vector>

#include <boost/algorithm/string.hpp>

namespace
{
  std::ostream &output_optional_value(std::ostream &os, std::string const &name,
                                      auto const value)
  {
    os << name << "=";
    if (value == std::nullopt)
    {
      os << "none";
    }
    else
    {
      os << *value;
    }
    return os;
  }
} // namespace

namespace estim2b
{
  void Settings::reset()
  {
    intensity_channel_a = std::nullopt;
    intensity_channel_b = std::nullopt;
    adjustment_c = std::nullopt;
    adjustment_d = std::nullopt;
    mode = std::nullopt;
    channel_link = std::nullopt;
    power_level = std::nullopt;
  }

  std::ostream &operator<<(std::ostream &os, Settings const &settings)
  {
    output_optional_value(os, "A", settings.intensity_channel_a) << ", ";
    output_optional_value(os, "B", settings.intensity_channel_b) << ", ";
    output_optional_value(os, "C", settings.adjustment_c) << ", ";
    output_optional_value(os, "D", settings.adjustment_d) << ", ";
    output_optional_value(os, "Mode", settings.mode) << ", ";
    output_optional_value(os, "ChannelLink", settings.channel_link) << ", ";
    output_optional_value(os, "Power", settings.power_level);

    return os;
  }

  std::ostream &operator<<(std::ostream &os, Status const &status)
  {
    os << "Battery=" << status.battery_level << ", "
       << static_cast<Settings>(status) << ", "
       << "Firmware=" << status.firmware_version;

    return os;
  }

  Status decode_status_message(std::string const &message)
  {
    std::vector<std::string> parts;
    boost::split(parts, message, boost::is_any_of(":"));

    if (parts.size() != 9)
    {
      throw std::runtime_error("Status decode error, message: " + message);
    }

    Status rv;
    rv.battery_level = std::stoi(parts[0]);
    rv.intensity_channel_a = std::stoi(parts[1]) / 2;
    rv.intensity_channel_b = std::stoi(parts[2]) / 2;
    rv.adjustment_c = std::stoi(parts[3]) / 2;
    rv.adjustment_d = std::stoi(parts[4]) / 2;
    rv.mode = Mode::_from_integral(std::stoi(parts[5]));
    rv.power_level = PowerLevel::_from_integral(parts[6].front());
    rv.channel_link = ChannelLink::_from_integral(std::stoi(parts[7]));
    rv.firmware_version = parts[8];

    return rv;
  }
} // namespace estim2b
