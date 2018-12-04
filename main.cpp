#include "MediaPlayer.h"
#include <conio.h>
#include <windows.h>
#include "StringDummy.h"

void main()
{
	MediaPlayer player;
	player.init();
	std::cout << "///////////////////////////////////////////////////" << std::endl
	<< "// HKU KMT Game Audio Sound Test Environment 	 //" << std::endl
	<< "// Copyright Game Audio 2006 \t\t	 //" << std::endl
	<< "// All Rights Reservered\t\t\t //" << std::endl
	<< "///////////////////////////////////////////////////" << std::endl
	<< "\nONLY N WORKS!\n" << std::endl;
	


	int key = 0;/*, prevkey = 0;*/
	
	StringDummy testenvironment;

	// breakpoint dummy inserts
	std::vector<int> breakpoints;
    int breakpoint1 = 300000;			// 6.8 sec		@ 44100 SR
	int breakpoint2 = 562500;			// 12.76 sec	@ 44100 SR
	int breakpoint3 = 605400;			// 13.72 sec	@ 44100 SR
	int breakpoint4 = 878100;			// 19.91 sec	@ 44100 SR
	breakpoints.push_back(breakpoint1);
	breakpoints.push_back(breakpoint2);
	breakpoints.push_back(breakpoint3);
	breakpoints.push_back(breakpoint4);
	// /breakpoint dummy inserts

	player.SETTEST(0);


	// File inserting. Order: vectornumber location, vectornumber threat, vectornumber succes, D_WORD filename, vector breakpoints
	player.InsertFile(1,0,0,"testfile1.wav", &breakpoints);
	player.InsertFile(1,0,0,"testfile2.wav", &breakpoints);
	player.InsertFile(1,0,0,"testfile3.wav", &breakpoints);
	player.InsertFile(1,0,0,"testfile4.wav", &breakpoints);
	player.InsertFile(1,0,0,"testfile5.wav", &breakpoints);
	player.InsertFile(1,0,0,"testfile6.wav", &breakpoints);
	player.InsertFile(1,0,0,"testfile7.wav", &breakpoints);
	// /File inserting.




	testenvironment.fill();
	do
	{
		// Windows keyboard hitting, extraction & ordering
		if (kbhit())
		{
			key = getch();
			switch(key)
			{
			//case '1':
			//case '2':
			//case '3':
			//case '4':
			//case '5':
			//case '6':
			//case '7':
			//	{
			//		std::cout << (int)(key - '0' -1 ) << std::endl;
			//		player.InsertAudio(0,0,0,((int)(key-'0'-1)));
			//		break;
			//	}
				case 'n':
				{
					player.InsertAudio(testenvironment.retrieve().table1, testenvironment.retrieve().table2, testenvironment.retrieve().table3);
					break;
				}
				case 'q':
				{
					player.quit();
					break;
				}
			}
		}
		// /Windows keyboard hitting, extration & ordering
		player.update();
		
	}while(true);
}