#pragma once
#include <string.h>
#define NAMELENGHT 10
typedef char UserName[NAMELENGHT];


class HashTable
{
public:
	HashTable();
	~HashTable();
	void add(UserName usr_name, int usr_pass);
	void del(UserName usr_name);
	int  find(UserName usr_name);
	void resize();

private:

	enum enPairStatus
	{
		free,
		engaged,
		deleted
	};
	struct Pair
	{
		Pair() : user_name(""), user_pass(-1), status(enPairStatus::free)
		{   }

		Pair(UserName usr_name, int usr_pass) :
			user_pass(usr_pass), status(enPairStatus::free)
		{
			strcpy(user_name, usr_name);
		}

		Pair& operator = (const Pair& other)
		{
			user_pass = other.user_pass;
			status = other.status;
			strcpy(user_name, other.user_name);
			return *this;
		}

		UserName user_name;
		int user_pass;
		enPairStatus status;
	};

	int hash_func(UserName usr_name, int offset);

	Pair* array;
	int count;
	int mem_size;
};
HashTable::HashTable()
{
	count = 0;
	int mem_size = 8;
	array = new Pair[mem_size];
}
HashTable::	~HashTable()
{
	delete[] array;
}
