#include"speechManager.h"
SpeechManager::SpeechManager()
{
	this->initSpeecch();
	this->creatSpeaker();
	this->loadrecord();//���������¼
}
void SpeechManager::show_Menu()//�˵�
{
	cout << "-----------------------------------" << endl;
	cout << "-----------�ݽ�����----------------" << endl;
	cout << "-----------1,��ʼ����--------------" << endl;
	cout << "-----------2,�鿴�����¼----------" << endl;
	cout << "-----------3,���-------------------" << endl;
	cout << "-----------0,�˳�------------------" << endl;
	cout << endl;
}
void SpeechManager::exitSystem()//�˳�����
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	system("cls");
	exit(0);
}
void SpeechManager::initSpeecch()//��ʼ������
{
	this->v1.clear();
	this->v2.clear();
	this->victory.clear();
	this->m_index = 1;
	this->m_record.clear();
}
void SpeechManager::creatSpeaker()//����ѡ��
{
	string nameseed = "ABCDEFGHIJKL";
	for (int i = 0; i < nameseed.size(); i++)
	{
		string name = "ѡ��";
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
void SpeechManager::startSpeech()//��ʼ������������������
{
	//��һ�ֱ���
	//1.��ǩ
	this->speechdraw();
	//2.����
	this->speechcontest();
	//3.��ʾ�������
	this->showScore();
	//�ڶ��ֱ���
	this->m_index++;
	//1.��ǩ
	 this->speechdraw();
	//2.����
	 this->speechcontest();
	//3.��ʾ���ܽ��
	 this->showScore();
	//4.����
	 this->saverecord();
	 this->initSpeecch();
	 this->creatSpeaker();
	 this->loadrecord();
	 cout << "��" << m_index << "��������" << endl;
	 system("pause");
	 system("cls");
}
void SpeechManager::speechdraw()//��ǩ
{
	cout << "------��" << this->m_index << "��ѡ�����ڳ�ǩ-------------" << endl;
	cout << "��ǩ��˳������" << endl;
	if (m_index == 1)//��һ�ֳ�ǩ
	{
		random_shuffle(v1.begin(), v1.end());
		for (vector<int>::iterator it = v1.begin(); it != v1.end(); it++)
		{
			cout << *it << " ";
		}
		cout << endl; 
	}
	else//�ڶ��ֳ�ǩ
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
void SpeechManager::speechcontest()//����
{
	cout << "-------��" << this->m_index << "����ʽ������ʼ--------" << endl;
	multimap<double, int, greater<double>> grourpScore;
	int num = 0;//��¼������6��Ϊһ��
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
		grourpScore.insert(make_pair(avg, *it));//keyΪ�÷�,valueΪѡ�ֱ��
		if (num % 6 == 0)
		{
			cout << "��" << num / 6 << "С���������" << endl;
			for (multimap<double, int, greater<double>>::iterator it = grourpScore.begin(); it != grourpScore.end(); it++)
			{
				cout << "���" << it->second << "����" << this->m_Speakre[it->second].m_name << "�ɼ�" << this->m_Speakre[it->second].m_score[m_index-1] << endl;
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
void SpeechManager::showScore()//չʾ�ɼ�
{
	cout << "-------��" << m_index << "��ѡ����Ϣ����---------------" << endl;
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
		cout << "ѡ�ֱ��:" << *it << "����" << this->m_Speakre[*it].m_name << "�÷�:" << this->m_Speakre[*it].m_score[m_index - 1] << endl;
	}
	system("pause");
	system("cls");
}
void SpeechManager::saverecord()//�����¼
{
	ofstream ofs;
	ofs.open("speech.csv", ios::out | ios::app);
	for (vector<int>::iterator it = victory.begin(); it != victory.end(); it++)
	{
		ofs << *it << "," << this->m_Speakre[*it].m_score[1] << ",";
	}
	ofs << endl;
	ofs.close();
	cout << "��¼�ѱ���" << endl;
	this->fileisempty = false;
}
void SpeechManager::loadrecord()//��ȡ��¼
{
	ifstream ifs("speech.csv", ios::in);
	if (!ifs.is_open())
	{
		this->fileisempty = true;
		//cout << "�ļ�������" << endl;
		ifs.close();
		return;
	}
	char ch;
	ifs >> ch;
	if (ifs.eof())
	{
		//cout << "�ļ�Ϊ��" << endl;
		this->fileisempty = true;
		ifs.close();
		return;
	}
	this->fileisempty = false;
	ifs.putback(ch);//�������ȡ�ĵ����ַ��ٷŻ���
	string data;
	int index = 0;
	while (ifs >> data)
	{
		vector<string>v;//���6��string�ַ���
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
		cout << it->first << "�ھ���ţ�" << it->second[0] << "����:" << it->second[1] << endl;
	}
}
void SpeechManager::showrecord()//չʾ����ھ�
{
	if (this->fileisempty)
	{
		cout << "�ļ�������" << endl;
	}
	else
	{


		for (int i = 0; i < this->m_record.size(); i++)
		{
			cout << "��" << i + 1 << "��" << "�ھ����:" << this->m_record[i][0] << "�÷�:" << this->m_record[i][1] <<
				"�Ǿ����:" << this->m_record[i][2] << "�÷�:" << this->m_record[i][3] <<
				"�������:" << this->m_record[i][4] << "�÷�:" << this->m_record[i][5] << endl;
		}
	}
	system("pause");
	system("cls");
}
void SpeechManager::clearrecord()//���
{
	cout << "ȷ�����?" << endl;
	cout << "1.ȷ��" << endl;
	cout << "2.����" << endl;
	int choose = -1;
	cin >> choose;
	if (choose == 1)
	{
		ofstream ofs("speech.csv",ios::trunc);
		ofs.close();
		this->initSpeecch();
		this->creatSpeaker();
		this->loadrecord();
		cout << "��ճɹ�" << endl;
	}
	system("pause");
	system("cls");
}

SpeechManager::~SpeechManager()
{

}