#include "hash.h"

template <class K, class V>
HashTable<K, V>::HashTable(int n = 11){
	linvector.resize(n);
	for(int i = 0; i < n; i++){
		linvector[i].state = EMPTY;
	}
	numvalidelements = 0;
	vectorsize = n;
}

template<class K, class V>
HashTable<K, V>::~HashTable(){
	int size = bucket_count();
	auto iter = linvector.begin();
	for(int i = 0; i < vectorsize; i++){
		if(linvector[i].state != EMPTY){
			victor.erase(iter->entry.first);
		}
		iter++;
	}
}

template<class K, class V>
bool HashTable<K, V>::empty(){
	if(numvalidelements > 0){
		return false;
	}
	return true;
}

template<class K, class V>
int HashTable<K, V>::size(){
	return numvalidelements;
}

template<class K, class V>
V& HashTable<K, V>::at(const K& key){
	int index = bucket(key);
	return linvector[index].entry.second;
}

template<class K, class V>
V& HashTable<K, V>::operator[](const K& key){
	int index = bucket(key);
	return linvector[index].entry.second;
}

template<class K, class V>
int HashTable<K, V>::count(const K& key){
	int num = 0;
	for(int i = 0; i < bucket_count(); i++){
		if(victor[i].state == VALID){
			if(victor[i].input.first == key){
				num++;
			}
		}
	}
	return num;
}

template<class K, class V>
void HashTable<K, V>::emplace(K key, V value){
	int index = hash(key);
	std::pair<K, V> temppair;
	temppair.first = key;
	temppair.second = value;
	while(linvector[index].state == VALID){
		if(index == bucket_count() - 1){
			index = 0;
		}
		else[
			index++;
		]
	}
	linvector[index].input = temppair;
	linvector[index].state = VALID;
	numvalidelements++;
}

template<class K, class V>
void HashTable<K, V>::insert(const std::pair<K, V>& pair){
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
}

template<class K, class V>
void HashTable<K, V>::erase(const K& key){
	int index = bucket(key);
	linvector[index].state = DELETED;
	numvalidelements--;
}

template<class K, class V>
void HashTable<K, V>::clear(){
	linvector.clear();
}

template<class K, class V>
int HashTable<K, V>::bucket_count(){
	return vectorsize;
}

template<class K, class V>
int HashTable<K, V>::bucket_size(int n){
	if(linvector[n].state == VALID){
		return 1;
	}
	return 0;
}

template<class K, class V>
int HashTable<K, V>::bucket(const K& key){
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

template<class K, class V>
float HashTable<K, V>::load_factor(){
	return((double)numvalidelements / (double)vectorsize);
}

template<class K, class V>
void HashTable<K, V>::rehash(){
	std::vector<hashobject> tempvect = linvector;
	for(int i = 0; i < vectorsize; i++){
		linvector[i].state = EMPTY;
	}
	linvector.clear();
	numvalidelements = 0;
	int oldsize = vectorsize;
	vectorsize = findNextPrime(2 * oldsize);
	linvector.resize(vectorsize);
	for(int i = 0; i < oldsize; i++){
		if(tempvect[i].state == VALID){
			insert(tempvect[i].input);
		}
	}
}

template<class K, class V>
void HashTable<K, V>::rehash(int n){
	std::vector<hashobject> tempvect = victor;
	if(!isPrime(n)){
		findNextPrime(n);
	}
	int oldsize = vectorsize;
	for(int i = 0; i < vectorsize; i++){
		linvector[i].state = EMPTY;
	}
	linvector.clear();
	vectorsize = n;
	linvector.resize(n);
	numvalidelements = 0;
	for(int i= 0; i < oldsize; i++){
		if(tempvect[i].state == VALID){
			insert(tempvect[i].input);
		}
	}
}

template<class K, class V>
int HashTable<K, V>::hash(const K& key){
	int num = atoi(key);
	return num;
}

template <class K, class V>
int HashTable<K, V>::findNextPrime(int n){
	while(!isPrime(n)){
		n++;
	}
	return n;
}

template <class K, class V>
int HashTable<K, V>::isPrime(int n){
	for(int i = 2; i <= sqrt(n); i++){
		if(n % i == 0){
			return false;
		}
	}
	return true;
}