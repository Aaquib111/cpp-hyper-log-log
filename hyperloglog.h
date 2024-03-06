#ifndef HLL_HYPERLOGLOG_H
#define HLL_HYPERLOGLOG_H

#include "bucket.h"
#include <vector>

/**
 * @brief A HyperLogLog data structure.
 * 
 */
class HyperLogLog {

private:
    // The number of buckets.
    size_t numBuckets;

    /**
     * @brief Get the value of alpha (constant correction).
     * 
     * @return double 
     */
    double getAlpha() const;

public:
    // The number of buckets.
    std::vector<Bucket> buckets;
    explicit HyperLogLog(size_t numBuckets);

    /**
     * @brief Add an element to the HyperLogLog data structure.
     * 
     * @param element The element to add.
     */
    void add(const Element& element);

    /**
     * @brief Estimate the cardinality of the HyperLogLog data structure.
     * 
     * @return double The estimated cardinality. 
     */
    double estimateCardinality() const;
};

#endif
