#pragma once

#include <map>
#include <string>

#include "2b/protocol.hpp"

namespace estim2b
{
  struct ModeDocumentation
  {
    std::string const description;
    std::map<Adjustment const, std::string const> const adjustments;
  };

  extern std::map<Mode const, ModeDocumentation const> const mode_descriptions;
} // namespace estim2b
