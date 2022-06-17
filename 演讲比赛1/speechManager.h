#pragma once
#include<iostream>
#include<string>
#include<vector>
#include<deque>
#include<algorithm>
#include<functional>
#include<map>
#include<numeric>
#include"Speaker.h"
#include<fstream>


using namespace std;
class SpeechManager
{
public:
	SpeechManager();
	void show_Menu();
	void exitSystem();
	void initSpeecch();
	void creatSpeaker();
	void startSpeech();
	void speechdraw();
	void speechcontest();
	void showScore();
	void saverecord();
	void loadrecord();
	void showrecord();
	void clearrecord();
	bool fileisempty;
	vector<int>v1;
	vector<int>v2;
	vector<int>victory;
	map<int, Speaker>m_Speakre;//´æ·ÅÆ½¾ù·ÖÈÝÆ÷
	map<int, vector<string>>m_record;//´æ´¢Íù½ì¼ÇÂ¼ÈÝÆ÷
	int m_index ;
	~SpeechManager();
};