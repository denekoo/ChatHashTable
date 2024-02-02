#include "HashTable.h"


// ???????????? ???????????
int HashTable::hash_func(UserName usr_name, int offset) {
	// ????????? ??????
	int sum = 0, i = 0;
	for (; i < strlen(usr_name); i++) {
		sum += usr_name[i];
	}
	// ???????????? ?????
	return (sum % mem_size + offset * offset) % mem_size;
}



void HashTable::add(UserName usr_name, int usr_pass)
{
	int index = -1;
	int i = 0;
	for (; i < mem_size; ++i)
	{
		index = hash_func(usr_name, i);
		if (array[index].status != enPairStatus::engaged)
		{
			break;
		}
	}
	if (i >= mem_size)
	{
		resize();
		add(usr_name, usr_pass);
	}
	else
	{
		array[index] = Pair(usr_name, usr_pass);
		count++;
	}
}

int HashTable::find(UserName usr_name)
{
	// ??????? ????? ????????, ??????????????? ????? usr_name
	// ???? ?????? ????? ???? ? ???????, ?? ??????? -1
	// ??? ???

	for (int i = 0; i < mem_size; ++i)
	{
		int index = hash_func(usr_name, i);
		if (!strcmp(array[index].user_name, usr_name) && array[index].status == enPairStatus::engaged)
		{
			return array[index].user_pass;
		}
	}

	return -1;
}

void HashTable::del(UserName usr_name)
{
	// ??? ???
	for (int i = 0; i < mem_size; ++i)
	{
		int index = hash_func(usr_name, i);
		if (!strcmp(array[index].user_name, usr_name))
		{
			array[index].status = deleted;
			count--;
			break;
		}
	}
}

void HashTable::resize() {

	Pair* pairArray = array;
	int oldSize = mem_size;
	mem_size *= 2;
	array = new Pair[mem_size];
	count = 0;

	for (int i = 0; i < oldSize; ++i)
	{
		Pair& oldPair = pairArray[i];
		if (pairArray[i].status == enPairStatus::engaged)
		{
			add(oldPair.user_name, oldPair.user_pass);
		}
	}
	delete[] pairArray;
}


//// Zlobin`s code
//void HashTable::resize() {
//	Pair* save = array;
//	int save_ms = mem_size;
//
//	mem_size *= 2;
//	array = new Pair[mem_size];
//	count = 0;
//
//	for (int i = 0; i < save_ms; i++) {
//		Pair& old_pair = save[i];
//		if (old_pair.status == enPairStatus::engaged) {
//			add(old_pair.user_name, old_pair.user_pass);
//		}
//	}
//
//	delete[] save;
//}
