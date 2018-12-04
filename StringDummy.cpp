#include ".\stringdummy.h"

StringDummy::StringDummy(void)
{
}

StringDummy::~StringDummy(void)
{
}

void StringDummy::fill()
{
	for (int i = 0; i < 10; i++)
	{
		veel[i].table1 =		1;/*rand();*/
		veel[i].table2 =		0;/*rand();*/
		veel[i].table3 =		0;/*rand();*/
		veel[i].AudioTable =	rand();
	}
}

arraystuks StringDummy::retrieve()
{
	return veel[(rand()%10)];
}