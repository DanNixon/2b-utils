#include <gtest/gtest.h>

#include <sstream>

#include "2b/protocol.hpp"

TEST(protocol_test, settings_default)
{
  estim2b::Settings settings;

  EXPECT_EQ(std::nullopt, settings.power_level);
  EXPECT_EQ(std::nullopt, settings.channel_link);
  EXPECT_EQ(std::nullopt, settings.mode);
  EXPECT_EQ(std::nullopt, settings.intensity_channel_a);
  EXPECT_EQ(std::nullopt, settings.intensity_channel_b);
  EXPECT_EQ(std::nullopt, settings.adjustment_c);
  EXPECT_EQ(std::nullopt, settings.adjustment_d);
}

TEST(protocol_test, settings_reset)
{
  estim2b::Settings settings;

  using estim2b::ChannelLink;
  using estim2b::Mode;
  using estim2b::PowerLevel;
  settings.power_level = PowerLevel::High;
  settings.channel_link = ChannelLink::Linked;
  settings.mode = Mode::Throb;
  settings.intensity_channel_a = 20;
  settings.intensity_channel_b = 75;
  settings.adjustment_c = 40;
  settings.adjustment_d = 60;

  settings.reset();

  EXPECT_EQ(std::nullopt, settings.power_level);
  EXPECT_EQ(std::nullopt, settings.channel_link);
  EXPECT_EQ(std::nullopt, settings.mode);
  EXPECT_EQ(std::nullopt, settings.intensity_channel_a);
  EXPECT_EQ(std::nullopt, settings.intensity_channel_b);
  EXPECT_EQ(std::nullopt, settings.adjustment_c);
  EXPECT_EQ(std::nullopt, settings.adjustment_d);
}

TEST(protocol_test, settings_to_string_default)
{
  estim2b::Settings settings;

  std::stringstream ss;
  ss << settings;

  EXPECT_EQ(
      "A=none, B=none, C=none, D=none, Mode=none, ChannelLink=none, Power=none",
      ss.str());
}

TEST(protocol_test, settings_to_string)
{
  estim2b::Settings settings;

  using estim2b::ChannelLink;
  using estim2b::Mode;
  using estim2b::PowerLevel;
  settings.power_level = PowerLevel::High;
  settings.channel_link = ChannelLink::Linked;
  settings.mode = Mode::Throb;
  settings.intensity_channel_a = 20;
  settings.intensity_channel_b = 75;
  settings.adjustment_c = 40;
  settings.adjustment_d = 60;

  std::stringstream ss;
  ss << settings;

  EXPECT_EQ(
      "A=20, B=75, C=40, D=60, Mode=Throb, ChannelLink=Linked, Power=High",
      ss.str());
}

TEST(protocol_test, status_to_string)
{
  estim2b::Status status;
  status.battery_level = 512;
  status.firmware_version = "2.105";

  std::stringstream ss;
  ss << status;

  EXPECT_EQ("Battery=512, A=none, B=none, C=none, D=none, Mode=none, "
            "ChannelLink=none, Power=none, Firmware=2.105",
            ss.str());
}

TEST(protocol_test, decode_status_message_good)
{
  std::string const &msg{"512:90:20:50:150:1:L:0:2.105"};
  auto const &s = estim2b::decode_status_message(msg);

  using estim2b::ChannelLink;
  using estim2b::Mode;
  using estim2b::PowerLevel;
  EXPECT_EQ(+PowerLevel::Low, s.power_level);
  EXPECT_EQ(+ChannelLink::Independant, s.channel_link);
  EXPECT_EQ(+Mode::Bounce, s.mode);
  EXPECT_EQ(45, s.intensity_channel_a);
  EXPECT_EQ(10, s.intensity_channel_b);
  EXPECT_EQ(25, s.adjustment_c);
  EXPECT_EQ(75, s.adjustment_d);
  EXPECT_EQ(512, s.battery_level);
  EXPECT_EQ("2.105", s.firmware_version);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
