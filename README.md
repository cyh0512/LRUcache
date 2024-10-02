Implement LRU cache (update position of items in O(n))

Usage:
LRUCache(int capacity) 
Initialize the LRU cache with positive size capacity.

int get(int key) 
Return the value of the key if the key exists, otherwise return -1.

void put(int key, int value) 
Update the value of the key if the key exists. Otherwise, add the key-value pair to the cache. 
If the number of keys exceeds the capacity from this operation, evict the least recently used key.
