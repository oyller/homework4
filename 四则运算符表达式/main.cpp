#include <iostream>
#include "Expression.h"

using namespace std;

void Show_Menu()
{
	Expression v;
	int Expression_Num, key;
	bool Is_Float, Is_Bracket, Is_Need_File;
	string S1, S2, S3, Ops;
	int MaxV;
	cout << "������Ҫ����������������ʽ����:\n";
	cin >> Expression_Num;
	getchar();
	cout << "��������ѡ��������(֧���������룬ֻʶ����Ч�����(+, -,*,/)���Իس�������)\n";
	getline(cin, Ops);
	Ops = v.Solve_Input_Ops(Ops);
	cout << "����������������\n";
	cin >> MaxV;
	cout << "�û��Ƿ�Ҫ������?(yes/no)\n";
	cin >> S1;
	cout << "�Ƿ���С��?(yes/no)\n";
	cin >> S2;
	cout << "�Ƿ��뱣�浽�ļ���?(yes/no)\n";
	cin >> S3;
	Is_Bracket = (S1 == "yes") ? 1 : 0;
	Is_Float = (S2 == "yes") ? 1 : 0;
	Is_Need_File = (S3 == "yes") ? 1 : 0;
	vector<string> Expressions = v.Generate_Expression(Expression_Num, Ops, MaxV, Is_Bracket, Is_Float);
	cout << "\n";
	cout << "���������ɵı��ʽ:\n";
	for (auto h : Expressions)
	{
		cout << h << " = " << v.Calculate_Expression(h) << "\n";
	}
	if (Is_Need_File)
		v.Print_file(Expressions);
    
	cout << "����1����������. ����0, ��������.";
	cin >> key;
	if (key)
	{
		exit(0);
	}
	system("cls");
}

int main()
{
	srand((unsigned)time(NULL));
	while (1)
	{
		Show_Menu();
	}
	return 0;
}