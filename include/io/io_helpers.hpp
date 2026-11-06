#pragma once

#include <cstdlib>
#include <iostream>
#include <limits>

/**
 * @brief Following helper functions were copied from learncpp.com and are used to maintain robust user input
 * checks for std::cin.
 */
namespace IO {

    /// Clears out any items within the buffer past the extracted value
    void ignoreLine()
    {
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    /// returns true if extraction failed, false otherwise
    bool clearFailedExtraction()
    {
        // Check for failed extraction
        if (!std::cin) // If the previous extraction failed
        {
            if (std::cin.eof()) // If the stream was closed
            {
                std::exit(0); // Shut down the program now
            }

            // Let's handle the failure
            std::cin.clear(); // Put us back in 'normal' operation mode
            ignoreLine();     // And remove the bad input

            return true;
        }

        return false;
    }
}
