#include "hash.h"

template <class K, class V>
HashTable<K, V>::HashTable(int n = 11){
	/*
	Trying to do the line:
	linvector.resize(n);

	But it doesn't know what linvector is
	*/
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