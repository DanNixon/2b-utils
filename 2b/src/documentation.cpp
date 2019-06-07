#include "2b/documentation.hpp"

namespace
{
  std::string const unused{"not used in this mode"};
  std::string const pulse_rate{"pulse rate, higher is faster"};
  std::string const sensation{"sensation, low is soft, high is spiky"};
  std::string const step_delay{"step delay, lower is shorter"};
}; // namespace

namespace estim2b
{
  std::map<Mode const, ModeDocumentation const> const mode_descriptions{
      {Mode::Pulse,
       {"both channels pulse on and off together",
        {{Adjustment::C, pulse_rate}, {Adjustment::D, sensation}}}},
      {Mode::Bounce,
       {"channels pulse on and off alternately",
        {{Adjustment::C, pulse_rate}, {Adjustment::D, sensation}}}},
      {Mode::Continuous,
       {"both channels are on continuously",
        {{Adjustment::C, sensation}, {Adjustment::D, unused}}}},
      {Mode::Split_A,
       {"channel A is pulsed, channel B is continuous",
        {{Adjustment::C, pulse_rate}, {Adjustment::D, sensation}}}},
      {Mode::Split_B,
       {"channel A is continuous, channel B is pulsed",
        {{Adjustment::C, pulse_rate}, {Adjustment::D, sensation}}}},
      {Mode::Wave,
       {"output level increases from 0\% to the selected limit and then drops "
        "back to 0\%",
        {{Adjustment::C, "speed of intensty ramp up"},
         {Adjustment::D, sensation}}}},
      {Mode::Waterfall,
       {"output level increases from 0\% to the selected limit and then slowly "
        "decreases back to 0\%",
        {{Adjustment::C, "speed on intensty ramp up and down"},
         {Adjustment::D, sensation}}}},
      {Mode::Squeeze,
       {"pulse rate increases and then drops to nearly continuous producing a "
        "synchronised \"squeeze\" sensation",
        {{Adjustment::C, pulse_rate}, {Adjustment::D, sensation}}}},
      {Mode::Milk,
       {"pulse rate increases and then drops to nearly continuous alternating "
        "between both channels",
        {{Adjustment::C, pulse_rate}, {Adjustment::D, sensation}}}},
      {Mode::Throb,
       {"continuous with the pulse feel cycling between 10 and adjustment C",
        {{Adjustment::C, sensation}, {Adjustment::D, unused}}}},
      {Mode::Thrust,
       {"continuous with the pulse feel cycling between 10, adjustment C and "
        "back to 0",
        {{Adjustment::C, sensation}, {Adjustment::D, unused}}}},
      {Mode::Random,
       {"produces random pulse output",
        {{Adjustment::C,
          "\"randomness\", lower values give more shorter pulses"},
         {Adjustment::D, sensation}}}},
      {Mode::Step,
       {"increases output in 1\% steps before dropping back to 0",
        {{Adjustment::C, step_delay}, {Adjustment::D, sensation}}}},
      {Mode::Training,
       {"increases output in steps of 1/12 channel value before dropping back "
        "to 0",
        {{Adjustment::C, step_delay}, {Adjustment::D, sensation}}}},
  };
}
