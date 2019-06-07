#pragma once

#include <optional>

#include <better_enums/enum.h>

namespace estim2b
{
  BETTER_ENUM(PowerLevel, char, Low = 'L', High = 'H');
  BETTER_ENUM(ChannelLink, int, Independant = 0, Linked = 1);
  BETTER_ENUM(Channel, char, A = 'A', B = 'B');
  BETTER_ENUM(Adjustment, char, C = 'C', D = 'D');
  BETTER_ENUM(Mode, int, Pulse = 0, Bounce = 1, Continuous = 2, Split_A = 3,
              Split_B = 4, Wave = 5, Waterfall = 6, Squeeze = 7, Milk = 8,
              Throb = 9, Thrust = 10, Random = 11, Step = 12, Training = 13);

  struct Settings
  {
    std::optional<PowerLevel> power_level;
    std::optional<ChannelLink> channel_link;
    std::optional<Mode> mode;
    std::optional<int> intensity_channel_a;
    std::optional<int> intensity_channel_b;
    std::optional<int> adjustment_c;
    std::optional<int> adjustment_d;

    void reset();
  };

  std::ostream &operator<<(std::ostream &os, Settings const &settings);

  struct Status : public Settings
  {
    int battery_level;
    std::string firmware_version;
  };

  std::ostream &operator<<(std::ostream &os, Status const &status);

  Status decode_status_message(std::string const &message);
}; // namespace estim2b
