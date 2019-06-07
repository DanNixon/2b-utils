#include <gtest/gtest.h>

#include "2b/documentation.hpp"

TEST(documentation_test, all_modes_documented)
{
  EXPECT_EQ(estim2b::Mode::_size(), estim2b::mode_descriptions.size())
      << "there are modes missing from the description list";

  for (auto const &[m, d] : estim2b::mode_descriptions)
  {
    EXPECT_FALSE(d.description.empty())
        << "mode " << m << " should have a description";

    EXPECT_EQ(estim2b::Adjustment ::_size(), d.adjustments.size())
        << "not all adjustments are documented for mode " << m;

    for (auto const &[a, ad] : d.adjustments)
    {
      EXPECT_FALSE(ad.empty())
          << "adjustment " << a << " is undocumented for mode " << m;
    }
  }
}

int main(int argc, char **argv)
{
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
