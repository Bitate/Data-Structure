#include <list>
#include <vector>
#include <iostream>

template<typename K, typename V>
class Entry
{
public:
	Entry(const K& k = K(), const V& v = V())
		: _key(k), _value(v) {}
	const& K key() { return _key; }
	const& V value() { return _value; }
	void setKey(const K& k) { _key = k; }
	void setValue(const V& v) { _value = v; }
private:
	K _key;
	V _value;
};




template<typename K, typename V>
class HashMap
{
public:
	typedef Entry<K, V> Entry;
	class Iterator;

public:
	HashMap(int capacity = 100);
	Iterator& find(const K& k);


	

	
	








	
	
protected:
		typedef typename std::list<Entry> Bucket;
		typedef typename std::vector<Bucket> BucketArray;
		typedef typename Bucket::iterator BucketIterator;
		typedef typename BucketArray::iterator BucketArrayIterator;

private:
	Bucket bucket;
	BucketArray bucketArray;

public:
	class Iterator
	{
	public:
		Iterator(const BktArray& a, const BItor& b, const EItor& q = EItor())
			: ent(q), bkt(b), ba(&a) { };
		~Iterator();

		BucketIterator operator++()
		{

		}

		BucketIterator operator--()
		{

		}

		EntryIterator operator*()
		{

		}
	public:
		friend class HashMap;

	private:
		EntryIterator entryIterator;
		BucketIterator bucketIterator;
		const BucketArray* ba;
	};
};


