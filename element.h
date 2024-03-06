#ifndef HLL_ELEMENT_H
#define HLL_ELEMENT_H

#include <string>
#include <functional>

/**
 * @brief An element is a string value that is hashed to a 64-bit integer.
 * 
 */
class Element {
public:
    // The value of the element.
    std::string value;

    Element(std::string value) : value(value) {}

    /**
     * @brief Get the Hash object
     * 
     * @return unsigned long 
     */
    unsigned long getHash() const {
        return std::hash<std::string>{}(value);
    }
};

#endif
