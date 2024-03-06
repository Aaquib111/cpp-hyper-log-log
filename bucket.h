#ifndef HLL_BUCKET_H
#define HLL_BUCKET_H

#include "element.h"

/**
 * @brief A bucket is a container for elements with the same hash prefix. 
 */
class Bucket {
private:
    // The maximum number of leading zeros in the hash prefix of the elements in the bucket.
    unsigned int maxLeadingZeros;

    /**
     * @brief Count the number of leading zeros in the hash prefix of the given hash.
     * 
     * @param hash The hash value of the element.
     * @param numBuckets The number of buckets.
     * @return unsigned int The number of leading zeros in the hash prefix. 
     */
    unsigned int countLeadingZeros(unsigned long hash, const size_t numBuckets) const;
    
public:
    Bucket() : maxLeadingZeros(0) {};

    /**
     * @brief Add an element to the bucket.
     * 
     * @param element The element to add.
     * @param numBuckets The number of buckets.
     */
    void add(const Element& element, const size_t numBuckets);

    /**
     * @brief Get the maximum number of leading zeros in the hash prefix of the elements in the bucket.
     * 
     * @return unsigned int 
     */
    unsigned int getLeadingZeros() const;

};
#endif
