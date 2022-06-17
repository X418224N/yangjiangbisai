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
	map<int, Speaker>m_Speakre;//���ƽ��������
	map<int, vector<string>>m_record;//�洢�����¼����
	int m_index ;
	~SpeechManager();
};