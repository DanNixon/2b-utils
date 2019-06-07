#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "2b/powerbox.hpp"

namespace
{
  class MockPowerbox : public estim2b::Powerbox
  {
  public:
    MOCK_METHOD0(close_connection, void());
    MOCK_METHOD0(reset, void());
    MOCK_METHOD0(kill, void());
    MOCK_METHOD0(commit, void());
    MOCK_METHOD0(update_status, void());
  };
} // namespace

TEST(powerbox_test, test_close_connection)
{
  MockPowerbox powerbox;
  EXPECT_CALL(powerbox, close_connection()).Times(1);
  powerbox.close_connection();
}

TEST(powerbox_test, test_status_cached)
{
  MockPowerbox powerbox;
  EXPECT_CALL(powerbox, update_status()).Times(0);
  powerbox.status(true);
}

TEST(powerbox_test, test_status_not_cached)
{
  MockPowerbox powerbox;
  EXPECT_CALL(powerbox, update_status()).Times(1);
  powerbox.status(false);
}

TEST(powerbox_test, test_kill)
{
  MockPowerbox powerbox;
  EXPECT_CALL(powerbox, kill()).Times(1);
  powerbox.kill();
}

TEST(powerbox_test, test_reset)
{
  MockPowerbox powerbox;
  EXPECT_CALL(powerbox, reset()).Times(1);
  powerbox.reset();
}

TEST(powerbox_test, test_set_power_level_low)
{
  using estim2b::PowerLevel;
  MockPowerbox powerbox;
  powerbox.set_power_level(PowerLevel::Low);
  EXPECT_EQ(+PowerLevel::Low, powerbox.staged_settings().power_level);
}

TEST(powerbox_test, test_set_power_level_low_string)
{
  MockPowerbox powerbox;
  powerbox.set_power_level("Low");
  using estim2b::PowerLevel;
  EXPECT_EQ(+PowerLevel::Low, powerbox.staged_settings().power_level);
}

TEST(powerbox_test, test_set_power_level_high)
{
  using estim2b::PowerLevel;
  MockPowerbox powerbox;
  powerbox.set_power_level(PowerLevel::High);
  EXPECT_EQ(+PowerLevel::High, powerbox.staged_settings().power_level);
}

TEST(powerbox_test, test_set_power_level_high_string)
{
  MockPowerbox powerbox;
  powerbox.set_power_level("High");
  using estim2b::PowerLevel;
  EXPECT_EQ(+PowerLevel::High, powerbox.staged_settings().power_level);
}

TEST(powerbox_test, test_set_channel_link_independant)
{
  using estim2b::ChannelLink;
  MockPowerbox powerbox;
  powerbox.set_channel_link(ChannelLink::Independant);
  EXPECT_EQ(+ChannelLink::Independant, powerbox.staged_settings().channel_link);
}

TEST(powerbox_test, test_set_channel_link_independant_string)
{
  MockPowerbox powerbox;
  powerbox.set_channel_link("Independant");
  using estim2b::ChannelLink;
  EXPECT_EQ(+ChannelLink::Independant, powerbox.staged_settings().channel_link);
}

TEST(powerbox_test, test_set_channel_link_linked)
{
  using estim2b::ChannelLink;
  MockPowerbox powerbox;
  powerbox.set_channel_link(ChannelLink::Linked);
  EXPECT_EQ(+ChannelLink::Linked, powerbox.staged_settings().channel_link);
}

TEST(powerbox_test, test_set_channel_link_linked_string)
{
  MockPowerbox powerbox;
  powerbox.set_channel_link("Linked");
  using estim2b::ChannelLink;
  EXPECT_EQ(+ChannelLink::Linked, powerbox.staged_settings().channel_link);
}

TEST(powerbox_test, test_set_mode)
{
  using estim2b::Mode;
  MockPowerbox powerbox;
  powerbox.set_mode(Mode::Continuous);
  EXPECT_EQ(+Mode::Continuous, powerbox.staged_settings().mode);
}

TEST(powerbox_test, test_set_mode_string)
{
  MockPowerbox powerbox;
  powerbox.set_mode("Continuous");
  using estim2b::Mode;
  EXPECT_EQ(+Mode::Continuous, powerbox.staged_settings().mode);
}

TEST(powerbox_test, test_set_channel_a_intensity)
{
  MockPowerbox powerbox;
  powerbox.set_channel_intensity(estim2b::Channel::A, 35);
  EXPECT_EQ(35, powerbox.staged_settings().intensity_channel_a);
}

TEST(powerbox_test, test_set_channel_a_intensity_string)
{
  MockPowerbox powerbox;
  powerbox.set_channel_intensity("A", 35);
  EXPECT_EQ(35, powerbox.staged_settings().intensity_channel_a);
}

TEST(powerbox_test, test_set_channel_b_intensity)
{
  MockPowerbox powerbox;
  powerbox.set_channel_intensity(estim2b::Channel::B, 30);
  EXPECT_EQ(30, powerbox.staged_settings().intensity_channel_b);
}

TEST(powerbox_test, test_set_channel_b_intensity_string)
{
  MockPowerbox powerbox;
  powerbox.set_channel_intensity("B", 30);
  EXPECT_EQ(30, powerbox.staged_settings().intensity_channel_b);
}

TEST(powerbox_test, test_set_adjustment_c)
{
  MockPowerbox powerbox;
  powerbox.set_adjustment(estim2b::Adjustment::C, 45);
  EXPECT_EQ(45, powerbox.staged_settings().adjustment_c);
}

TEST(powerbox_test, test_set_adjustment_c_string)
{
  MockPowerbox powerbox;
  powerbox.set_adjustment("C", 45);
  EXPECT_EQ(45, powerbox.staged_settings().adjustment_c);
}

TEST(powerbox_test, test_set_adjustment_d)
{
  MockPowerbox powerbox;
  powerbox.set_adjustment(estim2b::Adjustment::D, 55);
  EXPECT_EQ(55, powerbox.staged_settings().adjustment_d);
}

TEST(powerbox_test, test_set_adjustment_d_string)
{
  MockPowerbox powerbox;
  powerbox.set_adjustment("D", 55);
  EXPECT_EQ(55, powerbox.staged_settings().adjustment_d);
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
