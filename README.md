# Adaptive Replacement Cache Algorithm

A c++ implementation of Adaptive replacement cache (ARC) - a self-tuning ,low-overhead, scan-resistant algo.

This repo is for educational purpose only , use at your own risk in production systems as the algorithm is patented by IBM.

The complete paper can be accessed here : https://dbs.uni-leipzig.de/file/ARC.pdf

A very good presentation on this paper by Bryan Cantrill : https://www.youtube.com/watch?v=F8sZRBdmqc0&t=2641s

# Test cases:
Below tests have be added to main.

1. (4.3) Test cache miss - L1 size should go upto PAGE_SIZE and remain constant.
2. (4.1) Test cache miss when L1 = PAGE_SIZE & T1 < c implies that there is a key in B1.
3. (4.2) Test cache miss when L1  < PAGE_SIZE.
4. (1) Test frequent hit - T2 should go upto PAGE_SIZE and T1 should simultaneously go down.
5. (2) requested page in B1 - This should ultimately increase p to increase the T1 capacity ( recency).
6. (3) requested page in B2 - This should ultimately decrease p to increase the T2 capacity ( frequency).

Use option 7 for custom inputs to the cache.

# TODO:
Record hit and miss ratio and perform stress test to find the effeciency of algo in frequency vs recency.

