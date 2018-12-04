#pragma once
#include <iostream>


struct arraystuks
{
	int table1;
	int table2;
	int table3;
	int AudioTable;
};
class StringDummy
{
private:
	arraystuks veel[10];
public:
	StringDummy();
	~StringDummy();

	void fill();
	arraystuks retrieve();

};
