#include"speechManager.h"
SpeechManager::SpeechManager()
{
	this->initSpeecch();
	this->creatSpeaker();
	this->loadrecord();//加载往届记录
}
void SpeechManager::show_Menu()//菜单
{
	cout << "-----------------------------------" << endl;
	cout << "-----------演讲比赛----------------" << endl;
	cout << "-----------1,开始比赛--------------" << endl;
	cout << "-----------2,查看往届记录----------" << endl;
	cout << "-----------3,清空-------------------" << endl;
	cout << "-----------0,退出------------------" << endl;
	cout << endl;
}
void SpeechManager::exitSystem()//退出程序
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	system("cls");
	exit(0);
}
void SpeechManager::initSpeecch()//初始化容器
{
	this->v1.clear();
	this->v2.clear();
	this->victory.clear();
	this->m_index = 1;
	this->m_record.clear();
}
void SpeechManager::creatSpeaker()//创建选手
{
	string nameseed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameseed.size(); i++)
	{
		string name = "选手";
		name += nameseed[i];
		Speaker sp;
		sp.m_name = name;
		for (int i = 0; i < 2; i++)
		{
			sp.m_score[i] = 0;
		}
		this->v1.push_back(i + 10001);
		this->m_Speakre.insert(make_pair(i + 10001, sp));
	}
}
void SpeechManager::startSpeech()//开始比赛，控制整个流程
{
	//第一轮比赛
	//1.抽签
	this->speechdraw();
	//2.比赛
	this->speechcontest();
	//3.显示晋级结果
	this->showScore();
	//第二轮比赛
	this->m_index++;
	//1.抽签
	 this->speechdraw();
	//2.比赛
	 this->speechcontest();
	//3.显示最总结果
	 this->showScore();
	//4.保存
	 this->saverecord();
	 this->initSpeecch();
	 this->creatSpeaker();
	 this->loadrecord();
	 cout << "第" << m_index << "届比赛完毕" << endl;
	 system("pause");
	 system("cls");
}
void SpeechManager::speechdraw()//抽签
{
	cout << "------第" << this->m_index << "轮选手正在抽签-------------" << endl;
	cout << "抽签后顺序如下" << endl;
	if (m_index == 1)//第一轮抽签
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl; 
	}
	else//第二轮抽签
	{
		random_shuffle(v2.begin(), v2.end());
		for (vector<int>::iterator it = v2.begin(); it != v2.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl;
	}
	system("pause");
	cout << endl;
}
void SpeechManager::speechcontest()//比赛
{
	cout << "-------第" << this->m_index << "轮正式比赛开始--------" << endl;
	multimap<double, int, greater<double>> grourpScore;
	int num = 0;//记录人数，6人为一组
	vector<int>m_src;
	if (m_index == 1)
	{
		m_src = v1;
	}
	else
	{
		m_src = v2;
	}
	for (vector<int>::iterator it = m_src.begin(); it != m_src.end(); it++)
	{
		num++;
		deque<int>d;
		for (int i = 0; i < 10; i++)
		{
			double score = (rand() % 401 + 600) / 10.f;
			d.push_back(score);
		}
		sort(d.begin(), d.end());
		d.pop_back();
		d.pop_front();
		double sum = accumulate(d.begin(), d.end(), 0);
		double avg = sum / (double)d.size();
		this->m_Speakre[*it].m_score[m_index - 1] = avg;
		grourpScore.insert(make_pair(avg, *it));//key为得分,value为选手编号
		if (num % 6 == 0)
		{
			cout << "第" << num / 6 << "小组比赛名次" << endl;
			for (multimap<double, int, greater<double>>::iterator it = grourpScore.begin(); it != grourpScore.end(); it++)
			{
				cout << "编号" << it->second << "姓名" << this->m_Speakre[it->second].m_name << "成绩" << this->m_Speakre[it->second].m_score[m_index-1] << endl;
			}
			int count = 0;
			for (multimap<double, int, greater<double>>::iterator it = grourpScore.begin();it != grourpScore.end() && count < 3; it++, count++)
			{
				if (this->m_index == 1)
				{
					v2.push_back((*it).second);
				}
				else
				{
					victory.push_back((*it).second);
				}
			}
			grourpScore.clear();
		}
	}
	cout << endl;
}
void SpeechManager::showScore()//展示成绩
{
	cout << "-------第" << m_index << "轮选手信息如下---------------" << endl;
	vector<int>v;
	if (m_index == 1)
	{
		v = v2;
	}
	else
	{
		v = victory;
	}
	for (vector<int>::iterator it = v.begin(); it != v.end(); it++)
	{
		cout << "选手编号:" << *it << "姓名" << this->m_Speakre[*it].m_name << "得分:" << this->m_Speakre[*it].m_score[m_index - 1] << endl;
	}
	system("pause");
	system("cls");
}
void SpeechManager::saverecord()//保存记录
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	for (vector<int>::iterator it = victory.begin(); it != victory.end(); it++)
	{
		ofs << *it << "," << this->m_Speakre[*it].m_score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "记录已保存" << endl;
	this->fileisempty = false;
}
void SpeechManager::loadrecord()//读取记录
{
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open())
	{
		this->fileisempty = true;
		//cout << "文件不存在" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "文件为空" << endl;
		this->fileisempty = true;
		ifs.close();
		return;
	}
	this->fileisempty = false;
	ifs.putback(ch);//将上面读取的单个字符再放回来
	string data;
	int index = 0;
	while (ifs >> data)
	{
		vector<string>v;//存放6个string字符串
		int pos = -1;
		int start = 0;
		while (true)
		{
			pos = data.find(",", start);
			if (pos == -1)
			{
				break;
			}
			string temp = data.substr(start, pos - start);
			/*cout << temp << endl;*/
			v.push_back(temp);
			start = pos + 1;
		}
		this->m_record.insert(make_pair(index, v));
		index++;
	}
	ifs.close();
	for (map<int, vector<string>>::iterator it = m_record.begin(); it != m_record.end(); it++)
	{
		cout << it->first << "冠军编号：" << it->second[0] << "分数:" << it->second[1] << endl;
	}
}
void SpeechManager::showrecord()//展示历届冠军
{
	if (this->fileisempty)
	{
		cout << "文件不存在" << endl;
	}
	else
	{


		for (int i = 0; i < this->m_record.size(); i++)
		{
			cout << "第" << i + 1 << "届" << "冠军编号:" << this->m_record[i][0] << "得分:" << this->m_record[i][1] <<
				"亚军编号:" << this->m_record[i][2] << "得分:" << this->m_record[i][3] <<
				"季军编号:" << this->m_record[i][4] << "得分:" << this->m_record[i][5] << endl;
		}
	}
	system("pause");
	system("cls");
}
void SpeechManager::clearrecord()//清空
{
	cout << "确认清空?" << endl;
	cout << "1.确定" << endl;
	cout << "2.返回" << endl;
	int choose = -1;
	cin >> choose;
	if (choose == 1)
	{
		ofstream ofs("speech.csv",ios::trunc);
		ofs.close();
		this->initSpeecch();
		this->creatSpeaker();
		this->loadrecord();
		cout << "清空成功" << endl;
	}
	system("pause");
	system("cls");
}

SpeechManager::~SpeechManager()
{

}