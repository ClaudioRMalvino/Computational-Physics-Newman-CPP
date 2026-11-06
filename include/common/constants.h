#pragma once
#include <numbers>

/**
 * @file constants.h
 * @brief Physical constants utilized to calculate various exercises within Computational Physics by Mark Newman.
 */
namespace Constants{
    namespace Astro
    {
        constexpr double newtons_grav {6.67e-11};           ///< Newton's Gravitational constant [ m^{3}*kg^{-1}*s^{-2} ]
        constexpr double speed_of_light {299'792'458};      ///< Speed of light in a vacuum [ m*s^{-1} ]
    }
    namespace Atomic
    {
        constexpr double volume_coeff {15.8};                ///< Semi-empirical formula volume coefficient [ MeV ]
        constexpr double surface_coeff {18.3};               ///< Semi-empirical formula surface coefficient [ MeV ]
        constexpr double coulomb_coeff {0.714};              ///< Semi-empirical formula Coulomb coefficient [ MeV ]
        constexpr double asymmetry_coeff {23.2};            ///< Semi-empirical formula asymmetry coefficient [ MeV ]

    }
    namespace Earth
    {
        constexpr double gravity {9.81};                    ///< Gravitational constant on Earth [ m*s^{-1} ]
        constexpr double radius {6'371'000.0};              ///< Earth's radius [ m ]
        constexpr double mass {5.97e24};                    ///< Earth's mass [ kg ]
        constexpr double perihelion_vel {3.0287e4};         ///< Earth's perihelion velocity [ m/s ]
        constexpr double perihelion_dist {1.4710e11};       ///< Earth's perihelion distance from the Sun [ m ]
    }
    namespace ElecMag
    {
        constexpr double vac_mag_perm {1.25663706127e-6};   ///< Vacuum Magnetic permeability [ N*A^{-2} ]
        constexpr double vac_permitivity {8.8541878188e-12};///< Vacuum permitivity [ F*m^{-1} ]
    }
    namespace Quantum
    {
        constexpr double h {6.62607015e-34};                ///< Planck's constant [ j*s ]
        constexpr double h_eV {4.135667696e-15};            ///< Planck's constant [ eV*s ]
        constexpr double h_MeV {4.135667696e-21};           ///< Planck's constant [ MeV*s ]
        constexpr double h_bar {1.054571817e-34};           ///< Reduced Planck's constant [ j*s ]
        constexpr double h_bar_eV {6.582119569e-16};        ///< Reduced Planck's constant [ eV*s ]
        constexpr double h_bar_MeV {6.582119569e-12};       ///< Reduced Planck's constant [ MeV*s ]

        constexpr double electron_mass {9.1093837139e-31};  ///< Rest mass of an electron [ kg ]
        constexpr double electron_mass_c {5.10998095069e5}; ///< Rest mass of an electron [ eV/c^2 ]
        constexpr double electron_charge {1.60217663e-19};  ///< Charge of an electron [ C ]
    }
    namespace Sol
    {
        constexpr double mass{1.9891e30};                   ///< Solar mass [ kg ]
    }
    }
