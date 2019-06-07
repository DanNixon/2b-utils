#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include "2b/powerbox_digitallink.hpp"

namespace
{
  std::string const sample_status_message{"512:90:20:50:150:1:L:0:2.105"};

  class MockPowerboxDigitalLink : public estim2b::PowerboxDigitalLink
  {
  public:
    MOCK_METHOD0(close_connection, void());
    MOCK_METHOD1(request_and_response, std::string(std::string const &message));
  };
} // namespace

using ::testing::Return;

TEST(powerbox_digitallink_test, test_status_cached)
{
  MockPowerboxDigitalLink powerbox;

  EXPECT_CALL(powerbox, request_and_response("")).Times(0);

  powerbox.status(true);
}

TEST(powerbox_digitallink_test, test_status_not_cached)
{
  MockPowerboxDigitalLink powerbox;

  EXPECT_CALL(powerbox, request_and_response(""))
      .Times(1)
      .WillOnce(Return(sample_status_message));

  powerbox.status(false);
}

TEST(powerbox_digitallink_test, test_kill)
{
  MockPowerboxDigitalLink powerbox;

  EXPECT_CALL(powerbox, request_and_response("K"))
      .Times(1)
      .WillOnce(Return(sample_status_message));

  powerbox.kill();
}

TEST(powerbox_digitallink_test, test_reset)
{
  MockPowerboxDigitalLink powerbox;

  EXPECT_CALL(powerbox, request_and_response("E"))
      .Times(1)
      .WillOnce(Return(sample_status_message));

  powerbox.reset();
}

TEST(powerbox_digitallink_test, test_set_power_level_low)
{
  MockPowerboxDigitalLink powerbox;

  EXPECT_CALL(powerbox, request_and_response("L"))
      .Times(1)
      .WillOnce(Return(sample_status_message));

  powerbox.set_power_level(estim2b::PowerLevel::Low);
  powerbox.commit();
}

TEST(powerbox_digitallink_test, test_set_power_level_high)
{
  MockPowerboxDigitalLink powerbox;

  EXPECT_CALL(powerbox, request_and_response("H"))
      .Times(1)
      .WillOnce(Return(sample_status_message));

  powerbox.set_power_level(estim2b::PowerLevel::High);
  powerbox.commit();
}

TEST(powerbox_digitallink_test, test_set_channel_link_independant)
{
  MockPowerboxDigitalLink powerbox;

  EXPECT_CALL(powerbox, request_and_response("J0"))
      .Times(1)
      .WillOnce(Return(sample_status_message));

  powerbox.set_channel_link(estim2b::ChannelLink::Independant);
  powerbox.commit();
}

TEST(powerbox_digitallink_test, test_set_channel_link_linked)
{
  MockPowerboxDigitalLink powerbox;

  EXPECT_CALL(powerbox, request_and_response("J1"))
      .Times(1)
      .WillOnce(Return(sample_status_message));

  powerbox.set_channel_link(estim2b::ChannelLink::Linked);
  powerbox.commit();
}

TEST(powerbox_digitallink_test, test_set_mode)
{
  MockPowerboxDigitalLink powerbox;

  EXPECT_CALL(powerbox, request_and_response("M2"))
      .Times(1)
      .WillOnce(Return(sample_status_message));

  powerbox.set_mode(estim2b::Mode::Continuous);
  powerbox.commit();
}

TEST(powerbox_digitallink_test, test_set_channel_a_intensity)
{
  MockPowerboxDigitalLink powerbox;

  EXPECT_CALL(powerbox, request_and_response("A35"))
      .Times(1)
      .WillOnce(Return(sample_status_message));

  powerbox.set_channel_intensity(estim2b::Channel::A, 35);
  powerbox.commit();
}

TEST(powerbox_digitallink_test, test_set_channel_b_intensity)
{
  MockPowerboxDigitalLink powerbox;

  EXPECT_CALL(powerbox, request_and_response("B30"))
      .Times(1)
      .WillOnce(Return(sample_status_message));

  powerbox.set_channel_intensity(estim2b::Channel::B, 30);
  powerbox.commit();
}

TEST(powerbox_digitallink_test, test_set_adjustment_c)
{
  MockPowerboxDigitalLink powerbox;

  EXPECT_CALL(powerbox, request_and_response("C45"))
      .Times(1)
      .WillOnce(Return(sample_status_message));

  powerbox.set_adjustment(estim2b::Adjustment::C, 45);
  powerbox.commit();
}

TEST(powerbox_digitallink_test, test_set_adjustment_d)
{
  MockPowerboxDigitalLink powerbox;

  EXPECT_CALL(powerbox, request_and_response("D55"))
      .Times(1)
      .WillOnce(Return(sample_status_message));

  powerbox.set_adjustment(estim2b::Adjustment::D, 55);
  powerbox.commit();
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
