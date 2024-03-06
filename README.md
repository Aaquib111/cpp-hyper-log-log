# C++ HyperLogLog Implementation

## Setup
To build the driver, run:
```
g++ -std=c++2b -o driver driver.cpp bucket.cpp hyperloglog.cpp

./driver
```

## What is HyperLogLog?

HyperLogLog is a probabilistic algorithm for finding the number of distinct elements in a multiset.

### Naive Approach
Typical algorithms to find the number of distinct elements in a list of N elements take O(N) memory. An example of a naive approach is below:

```python
unique_elements = set()
for object in [obj1, ...,  objN]:
  unique_elements.add(object)
return len(unique_elements)
```

### HyperLogLog
If the number of elements is large, we (sometimes) can tolerate having an approximation of the number of distinct elements.
HyperLogLog follows the following steps to achieve this:

1. Have $m$ buckets that hold a roughly equal number of objects, hashed into a binary representation.
2. For each bucket, count the maximum number of 0s before the leading 1 in all element's binary representation.
   The idea is that observing a maximum of $n$ leading 0s increases the probability that there are around $2^n$ unique elements.
3. We take the harmonic mean $mZ$ of this number across buckets to make our estimation more robust.
   $$Z = (\sum_{i=1}^{m}2^{-n_i})^{-1}$$
   Where $n_i$ is the maximum number of leading 0s in the ith bucket.
5. We then correct this estimation using a constant factor $a_m$, calculated as:
  $$a_m = m\int_{0}^{\inf}(\log_{2}(\frac{2+u}{1+u})^m du)^{-1}$$

  Our final estimation is:
  $$E = a_m * m^2 * Z$$

**Example**

When running with 64 buckets, 50k total elements, and 5k unique elements:

```
./driver
Enter number of total elements: 
50000
Enter number of unique elements to estimate: 
5000
Z: 1.08356
alpha: 0.709
numBuckets: 64
Total number of unique elements: 5000
Estimated number of unique elements: 5360.24
Percent Error: 7.20483%
```

### Complexity
Space: O($loglogn + logn$), $n$ is the set cardinality

Time:
- `add()`: O(1)
- `estimateCardinality()`: O(1)
