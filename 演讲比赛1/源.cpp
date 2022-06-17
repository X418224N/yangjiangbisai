#include<iostream>
#include"speechManager.h"
#include<ctime>
using namespace std;
int main()
{
	SpeechManager sm;
	
	int i = -1;
	while (true)
	{
		srand((unsigned int )time(NULL));
		sm.show_Menu();
		cout << "ÇëÊäÈëÄãµÄÑ¡Ôñ" << endl;
		cin >> i;
		switch (i)
		{
		case 1:
			sm.startSpeech();
			break;
		case 2:
			sm.showrecord();
			break;
		case 3:
			sm.clearrecord();
			break;
		case 0:
			sm.exitSystem();
			break;
		default:
			system("cls");
			break;
		}
	}
	system("pause");
	return 0;
}