#ifndef _HASH_H
#define _HASH_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include <math.h>

using std::vector;
using std::pair;

enum EntryState{
	EMPTY = 0,
	VALID = 1,
	DELETED = 2
};

template<typename K, typename V> class HashTable{
private:

	int numvalidelements, vectorsize;

	struct hashobject{
		std::pair<K, V> entry;
		EntryState state;
	}

	std::vector<hashobject> linvector;

	int findNextPrime(int n);

	int isPrime(int n);

public:

HashTable(int n = 11);

~HashTable();

bool empty();

int size();

V& at(const K& key);

V& operator[](const K& key);

int count(const K& key);

void emplace(K key, V value);

void insert(const std::pair<K, V>& pair);

void erase(const K& key);

void clear();

int bucket_count();

int bucket_size(int n);

int bucket(const k& key);

float load_factor();

void rehash();

void rehash(int n);
};

#endif //_HASH_H