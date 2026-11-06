/**
 * @file conversions.h
 * @brief Contains conversions used throughout the exercises.
 */

#pragma once
#include <numbers>

namespace Conversions
{
    namespace Chrono
    {
        constexpr double sec_to_yrs {1.0 / 31556952.0};                  ///< Conversion from seconds -> years
        constexpr double yrs_to_sec {31556952.0};                        ///< Conversion from years -> seconds
    }
    namespace Energy
    {
        constexpr double eV_to_MeV {1.0e-6};
        constexpr double MeV_to_eV {1.0e+6};

    }
    namespace Length
    {
        constexpr double radian_to_degrees {(180.0 / std::numbers::pi)}; ///< Conversion from radians -> degrees
        constexpr double lyr_to_meters {9.460730e+15};                   ///< Conversion from light year -> meters
        constexpr double meters_to_lyr {1.0 / 9.460730e+15};             ///< Conversion from light year -> meters
    }
    namespace Mass
    {

    }
    namespace Volume
    {

    }

}
