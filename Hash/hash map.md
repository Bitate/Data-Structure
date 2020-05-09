## Map
1. A map stores key-value pairs (k,v), which we call **entries**;
2. In map each key must be unique. The key is an unique identifier.
3. For example, if we wish to store student records, we would probably use student ID as keys.
4. Maps are sometimes referred to as **associative stores** or **associative containers**
5. A iterator provides a way to reference entries of the map, and a special sentinel value to indicate a nonexistent entry.
6. A map is a collection of key-value entries, with each value associated with a distinct key.
7. Map applications: a compiler's symbol table, a registry of environment variables.
## Skip List
1. A data structure to efficiently realize the **ordered map**.
2. It makes random choices in arranging the entries in such a way that search and update times are **O(logn) on average, where n is the number of entries.

## Hash Table
1. The worst-case runnig time of map operations in an n-entry hash table is O(n). A hash table can usually performs it to O(1) time.
2. A hash table consists of two major components: **bucket/slots array** and **hash function**.
3. If two or more keys with the same hash value, then two different entries will be mapped to the same bucket in A. In this case, we say that a **collision** has happened.
4. A **hash code** is an integer. Hash code need not to be in the range [0, N-1], and may even be negative.


## Dictionary
1. A dictionary allows for multiple entries to have the same key, just like an English Dictionary, which allows for multiple definitions for the same word.
2. For example, we use zoom with the same meeting ID.
3. 


 