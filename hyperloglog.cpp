#include "hyperloglog.h"
#include <iostream>

HyperLogLog::HyperLogLog(size_t numBuckets) : numBuckets(numBuckets), buckets(numBuckets){}

void HyperLogLog::add(const Element& element) {
    // Calculate how many bits are needed for numBuckets. This assumes numBuckets is a power of 2.
    unsigned int bitsForBuckets = static_cast<unsigned int>(std::log2(numBuckets));

    // Use the top N bits for the bucket index.
    unsigned long hashValue = element.getHash();
    const unsigned int bucketIndex = hashValue >> (sizeof(hashValue)*CHAR_BIT - bitsForBuckets);

    buckets[bucketIndex].add(element, numBuckets);
}

double HyperLogLog::getAlpha() const {
    // The value of alpha depends on the number of buckets
    if(numBuckets == 16){
        return 0.673;
    }else if(numBuckets == 32){
        return 0.697;
    }else if(numBuckets == 64){
        return 0.709;
    }else{
        return 0.7213 / (1 + 1.079 / numBuckets);
    }
}

double HyperLogLog::estimateCardinality() const {
    const double alpha{getAlpha()};
    double Z{0.0};
    for(const auto& bucket : buckets){
        Z += std::pow(2.0, -static_cast<double>(bucket.getLeadingZeros()));
    }
    std::cout << "Z: " << Z << std::endl;
    std::cout << "alpha: " << alpha << std::endl;
    std::cout << "numBuckets: " << numBuckets << std::endl;

    // Need to add correction factor of 2, I suspect 
    // this is because of our hash function
    return 2 * alpha * (numBuckets * numBuckets) / Z;
}
