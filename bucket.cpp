#include "bucket.h"
#include <algorithm>
#include <climits>
#include <iostream>

unsigned int Bucket::countLeadingZeros(unsigned long hash, const size_t numBuckets) const {
    // Assume b bits are used for bucket indexing.
    int b = std::log2(numBuckets); // You need to pass numBuckets or calculate b based on it

    // Remove the first b bits used for the bucket index
    hash <<= b;

    unsigned int zeros{0};
    for (int i = b; i < sizeof(unsigned long) * CHAR_BIT; ++i) {
        if ((hash & (1UL << (sizeof(unsigned long) * CHAR_BIT - 1))) == 0) {
            zeros++;
            hash <<= 1; // Shift left to check the next bit
        } else {
            break; // Stop at the first 1 bit
        }
    }
    return zeros;
}

void Bucket::add(const Element& element, const size_t numBuckets) {
    unsigned long hash{element.getHash()};
    const unsigned int zeros{countLeadingZeros(hash, numBuckets)};
    maxLeadingZeros = std::max(maxLeadingZeros, zeros);
}

unsigned int Bucket::getLeadingZeros() const {
    return maxLeadingZeros;
}
