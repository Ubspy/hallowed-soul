#pragma once

#include <cmath>
#include "SFML/System/Vector2.hpp"

class VectorUtil
{
    public:
        /**
         * @brief Get the magnitude of a vector
         *
         * @param vec The vector to get the magnitude of
         *
         * @return The magnitude of the vector 
         */
        template <typename T>
        static T getVectorMagnitude(const sf::Vector2<T>& vec)
        {
            // Use sqrt(x^2 + y^2) to get the magnitude of the incoming vector
            return std::sqrt((vec.x * vec.x) + (vec.y * vec.y)); 
        }

        /**
         * @brief Get the unit vector of any vector
         *
         * @param vec The vector to get the unit of
         *
         * @return The unit vector 
         */
        template <typename T>
        static sf::Vector2<T> getUnitVector(const sf::Vector2<T>& vec)
        {
            return vec / getVectorMagnitude(vec);
        } 
};
