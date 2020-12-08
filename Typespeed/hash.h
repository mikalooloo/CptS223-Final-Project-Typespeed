#ifndef _HASH_H
#define _HASH_H

#include <vector>
#include <stdexcept>
#include <iostream>
#include <math.h>
#include <fstream>
#include <sstream>

using std::vector;
using std::pair;

enum EntryState{
	EMPTY = 0,
	VALID = 1,
	DELETED = 2,
	ONSCREEN = 3
};

template<typename K, typename V> class HashTable{
private:

	int numvalidelements, vectorsize;

	struct hashobject{
		std::pair<K, V> entry;
		EntryState state;
	};

	std::vector<hashobject> linvector;

	int findNextPrime(int n)
	{
		while(!isPrime(n)){
			n++;
		}
		return n;
	}

	int isPrime(int n)
	{
		for(int i = 2; i <= sqrt(n); i++){
			if(n % i == 0){
			return false;
			}
	}
	return true;
	}

	int hash(const K& key)
	{
		int sum = 0;
		for (long unsigned int i = 0; i < key.length(); ++i)
		{
			sum += int(key[i]);
		}
		return sum % vectorsize;
	}

public:

HashTable(int n)
{
	linvector.resize(n);
	for(int i = 0; i < n; i++){
		linvector[i].state = EMPTY;
	}
	numvalidelements = 0;
	vectorsize = n;
}

~HashTable()
{
	int size = bucket_count();
	auto iter = linvector.begin();
	for(int i = 0; i < vectorsize; i++){
		if(linvector[i].state != EMPTY){
			linvector.erase(iter->entry.first);
		}
		iter++;
	}
}

bool empty()
{
	if(numvalidelements > 0) return false;
	return true;
}

int size()
{
	return numvalidelements;
}

V& at(const K& key)
{
	int index = bucket(key);
	return linvector[index].entry.second;
}

V& operator[](const K& key)
{
	int index = bucket(key);
	return linvector[index].entry.second;
}

int count(const K& key)
{
	int num = 0;
	for(int i = 0; i < bucket_count(); i++){
		if(linvector[i].state == VALID){
			if(linvector[i].input.first == key){
				num++;
			}
		}
	}
	return num;
}

void emplace(K key, V value)
{
	insert(std::make_pair(key, value));
}

void insert(const std::pair<K, V>& pair)
{
	int index = hash(pair.first);

	while(linvector[index].state == VALID){
		if(index == vectorsize - 1){
			index = 0;
		}
		else{
			index++;
		}
	}
	linvector[index].entry = pair;
	linvector[index].state = VALID;
	numvalidelements++;
	rehash();
}

void erase(const K& key)
{
	linvector[bucket(key)].state = DELETED;
	numvalidelements--;
}

void clear()
{
	linvector.clear();
}

int bucket_count()
{
	return vectorsize;
}

int bucket_size(int n)
{
	if(linvector[n].state == VALID){
		return 1;
	}
	return 0;
}

int bucket(const K& key)
{
	int index = hash(key);
	int iterations = 0;
	while(linvector[index].first != key && iterations != bucket_count()){
		if(index == bucket_count() - 1){
			index = 0;
		}
		else{
			index++;
		}
		iterations++;
	}
	if(linvector[index].entry.first == key){
		return index;
	}
	else{
		return -1;
	}
}

float load_factor()
{
	return((double)numvalidelements / (double)vectorsize);
}

void rehash()
{
	if (load_factor() >= 0.75) rehash(vectorsize * 2);
}

void rehash(int n)
{
	std::vector<hashobject> tempvect = linvector;
	vectorsize = findNextPrime(n);

	linvector.clear();
	linvector.resize(vectorsize);

	for(int i = 0; i < vectorsize; i++) linvector[i].state = EMPTY;
	numvalidelements = 0;

	for(long unsigned int i = 0; i < tempvect.size(); ++i)
	{
		if (tempvect[i].state == VALID)
		{
			insert(tempvect[i].entry);
		}
	}
}

void print_hash(void) 
{
    for (size_t i = 0; i < linvector.size(); ++i)
    {
        if (linvector.at(i).state == VALID) std::cout << linvector.at(i).entry.first << std::endl;
    }
}

};



#endif //_HASH_H