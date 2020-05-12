#include <vector>   // Bucket Array is implemented in vector
#include <list>
#include <iostream>
// an entry class
template <typename K, typename V>
class Entry {						// a (key, value) pair
public:						// public functions
    Entry(const K& k = K(), const V& v = V())		// constructor
        : _key(k), _value(v) { }
    const K& key() const { return _key; }		// get key
    const V& value() const { return _value; }		// get value
    void setKey(const K& k) { _key = k; }		// set key
    void setValue(const V& v) { _value = v; }		// set value
private:						// private data
    K _key;						// key
    V _value;						// value
};


// A map provides a special pointer object, which allows us to reference entries of the map. Such an object is called position.
// Here we define a more general object called interator, which can both reference entriesand navivate around the map.
// Given a map interator p, we can access the associated entry by dereferencing the iterator, namely as *p.
// And accessing the individual keyand value by using p->key() and p->value(), respectively.
// We overload the increment operator++, so that ++p advances the iterator p to the next entry of the map.
// We enumerate all the entries by initializing p to M.begin() and then repeatedly incrementing p as long as it is not equal to M.end()
// In order to indicate that an object doesn't exist, we assume that there exist a special sentinel iterator called end. 
// TODO: This sentinel referes to an imaginary element that lies just beyong the last element of the map.
// We have provided two means of removing entries, one give a key and the other given an iterator p. 
// The key-based operation should be used only when key exists in the map. Otherweise, we must firstly use "p = M.find(k)", and if so, then apply the "M.erase(p)".
// The iterator-based operation has the advantage that it doesn't need to repeat the search for the key, thus it's more efficient.
// The operation put() may either insert an entry or modify/update an existing entry's value. Note that an iterator remains associated with an entry, even if its value has been changed.

// The map ADT:
// size():   return the number of entries in map M.
// empty():  Return true is M is empty and false otherwise.
// find(k):  If M contains an entry e = (k,v) with the key equal to k, then return an iterator p referring to this entry. Otherwise, return the special iterator end.
// put(k,v): If M doesn't contain an entry with the key equal to k, then add entry(k,v) to M. Otherwise, replace the value field of this entry with new v; return an iterator to the inserted/modified entry.
// erase(k): Remove from M the entry with the key equal to k. Otherwise, an error(M has no such entry) occurs.
// erase(p): Remove from M the entry referenced by iterator p. Otherwise, an error(p points to the end sentinel) occurs.
// begin():  Return an iterator to the first entry of M.
// end():    Return an iterator to a position just beyound the end of M.



///////////////////////////////////////////////////////////////////////////////////////////////////////
//									  A C++ Map Interface											 //
//																									 //
//	       This interface is templated by two types, the key type K, and the value type V.			 //
///////////////////////////////////////////////////////////////////////////////////////////////////////
//template <typename K, typename V>
//class Map {					// map interface
//public:
//    class Entry;				// a (key,value) pair
//    class Iterator;				// an iterator (and position)
//    // Outside the class, these would be accessed with Map<K,V>::Entry and Map<K,V>::Iterator, respectively
//
//    int size() const;				// number of entries in the map
//    bool empty() const;				// is the map empty?
//    Iterator find(const K& k) const;		// find entry with key k
//    Iterator put(const K& k, const V& v);	// insert/replace pair (k,v)
//    void erase(const K& k)			// remove entry with key k
//        throw(NonexistentElement);
//    void erase(const Iterator& p);		// erase entry at p
//    Iterator begin();				// iterator to first entry
//    Iterator end();				// iterator to end entry
//};



///////////////////////////////////////////////////////////////////////////////////////////////////////
//								A simple List-Based Map Implementation								 //
//																									 //
///////////////////////////////////////////////////////////////////////////////////////////////////////

// The list-based map implementation is simple, but it is only efficient for very small maps.
// Every one of the fundamental functions takes O(n) time on a map with n entries, because each function involves 
// searching through the entire list in the worst case.


///////////////////////////////////////////////////////////////////////////////////////////////////////
//								  A C++ Hash Table Implementation							    	 //
//								Based on hashing with separate chaining      						 //
///////////////////////////////////////////////////////////////////////////////////////////////////////
template <typename K, typename V, typename H>
class HashMap {
public:						// public types
    typedef Entry<const K, V> Entry;			    // Entry type Entry; a (key,value) pair；
    class Iterator;					                // Iterator type Iterator; a iterator/position
public:						// public functions
    HashMap(int capacity = 100);			        // constructor
    int size() const;					            // number of entries
    bool empty() const;					            // is the map empty?
    Iterator find(const K& k);				        // find entry with key k
    Iterator put(const K& k, const V& v);		    // insert/replace (k,v)
    void erase(const K& k);				            // remove entry with key k
    void erase(const Iterator& p);			        // erase entry at p
    Iterator begin();					            // iterator to first entry
    Iterator end();					                // iterator to end entry
protected:					                    	// protected types
    typedef std::list<Entry> Bucket;			    // a bucket of entries
    typedef std::vector<Bucket> BktArray;		    // a bucket array

    // HashMap utilities
    Iterator finder(const K& k);			                // find utility; read only
    Iterator inserter(const Iterator& p, const Entry& e);   // insert utility; read only
    void eraser(const Iterator& p);			                // remove utility; p is a reference to Iterator type that is const, which means you can't change iterator via p, because we actually want to change the entry referred by iterator p
    typedef typename BktArray::iterator BItor;		        // bucket iterator
    typedef typename Bucket::iterator EItor;		        // entry iterator
    static void nextEntry(Iterator& p)			            // bucket's next entry
    {
        ++p.ent;
    }
    static bool endOfBkt(const Iterator& p)		    // end of bucket?
    {
        return p.ent == p.bkt->end();
    }
private:
    int n;						                    // number of entries
    H hash;						                    // the hash comparator function
    BktArray B;				                        // bucket array
public:						                        // public types
  // Iterator class declaration here
    class Iterator {	                      		// an iterator (& position)
    private:
        EItor ent;					                // which entry; an iterator to the current entry
        BItor bkt;					                // which bucket; the bucket containing this entry
        const BktArray* ba;				            // which bucket array; bucket array containing the buckets
    public:
        Iterator(const BktArray& a, const BItor& b, const EItor& q = EItor())
            : ent(q), bkt(b), ba(&a) { }
        Entry& operator*() const;				        // get entry
        bool operator==(const Iterator& p) const;		// are iterators equal?
        Iterator& operator++();				            // advance to next entry
        friend class HashMap;				            // give HashMap access
    };
};


template <typename K, typename V, typename H>		// find utility
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::finder(const K& k) {
    // this is the original code
    // int i = hash(k) % B.size();				    // get hash index i
    // I simply change it to this
    int i = k % B.size();
    BItor bkt = B.begin() + i;				    // the ith bucket
    Iterator p(B, bkt, bkt->begin());			// start of ith bucket
    while (!endOfBkt(p) && (*p).key() != k)		// search for k
        nextEntry(p);
    return p;						// return final position
}

template <typename K, typename V, typename H>		// find key
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::find(const K& k) {
    Iterator p = finder(k);				// look for k
    if (endOfBkt(p))					// didn't find it?
        return end();					// return end iterator
    else
        return p;						// return its position TODO: position is iterator???
}



// get entry
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Entry&
HashMap<K, V, H>::Iterator::operator*() const
{
    return *ent;
}

// advance to next entry
template <typename K, typename V, typename H>
typename HashMap<K, V, H>::Iterator& HashMap<K, V, H>::Iterator::operator++() {
    ++ent;						// next entry in bucket
    if (endOfBkt(*this)) {				// at end of bucket?
        ++bkt;						// go to next bucket
        while (bkt != ba->end() && bkt->empty())		// find nonempty bucket
            ++bkt;
        if (bkt == ba->end()) return *this;		// end of bucket array?
        ent = bkt->begin();				// first nonempty entry
    }
    return *this;					// return self
}

// are iterators equal?
template <typename K, typename V, typename H>
bool HashMap<K, V, H>::Iterator::operator==(const Iterator& p) const {
    if (ba != p.ba || bkt != p.bkt) return false;	// ba or bkt differ?
    else if (bkt == ba->end()) return true;		// both at the end?
    else return (ent == p.ent);				// else use entry to decide
}



template <typename K, typename V, typename H>		// remove utility
void HashMap<K, V, H>::eraser(const Iterator& p) {
    p.bkt->erase(p.ent);		// remove entry from bucket; Note: erase() is std::vector::erase(), not below function
    n--;						// one fewer entry
}

template <typename K, typename V, typename H>		// remove entry at p
void HashMap<K, V, H>::erase(const Iterator& p)
{
    eraser(p);
}

template <typename K, typename V, typename H>		// remove entry with key k
void HashMap<K, V, H>::erase(const K& k) {
    Iterator p = finder(k);				// find k
    if (endOfBkt(p))					// not found? throw error
        // throw NonexistentElement("Erase of nonexistent");
        std::cout << "Erase of Nonexistent" << std::endl;
    eraser(p);						// remove it
}



template <typename K, typename V, typename H>		// iterator to end
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::end()
{
    return Iterator(B, B.end());
}

template <typename K, typename V, typename H>		// iterator to front
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::begin() {
    if (empty()) return end();				    // emtpty - return end
    BItor bkt = B.begin();				        // else search for an entry
    while (bkt->empty()) ++bkt;				    // find nonempty bucket
    return Iterator(B, bkt, bkt->begin());		// return first of bucket
}







template <typename K, typename V, typename H>		// constructor
HashMap<K, V, H>::HashMap(int capacity) : n(0), B(capacity) { }

template <typename K, typename V, typename H>		// number of entries
int HashMap<K, V, H>::size() const { return n; }

template <typename K, typename V, typename H>		// is the map empty?
bool HashMap<K, V, H>::empty() const { return size() == 0; }







template <typename K, typename V, typename H>		// insert utility
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::inserter(const Iterator& p, const Entry& e) {
    EItor ins = p.bkt->insert(p.ent, e);		// insert before p
    n++;						// one more entry
    return Iterator(B, p.bkt, ins);			// return this position
}

template <typename K, typename V, typename H>		// insert/replace (v,k)
typename HashMap<K, V, H>::Iterator HashMap<K, V, H>::put(const K& k, const V& v) {
    Iterator p = finder(k);				// search for k
    if (endOfBkt(p)) {					// k not found?
        return inserter(p, Entry(k, v));			// insert at end of bucket
    }
    else {						// found it?
        p.ent->setValue(v);				// replace value with v
        return p;						// return this position
    }
}