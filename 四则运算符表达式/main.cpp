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
	cout << "请输入要产生的四则运算表达式数量:\n";
	cin >> Expression_Num;
	getchar();
	cout << "请输入你选择的运算符(支持任意输入，只识别有效运算符(+, -,*,/)，以回车键结束)\n";
	getline(cin, Ops);
	Ops = v.Solve_Input_Ops(Ops);
	cout << "请设置最大的运算数\n";
	cin >> MaxV;
	cout << "用户是否要加括号?(yes/no)\n";
	cin >> S1;
	cout << "是否有小数?(yes/no)\n";
	cin >> S2;
	cout << "是否想保存到文件中?(yes/no)\n";
	cin >> S3;
	Is_Bracket = (S1 == "yes") ? 1 : 0;
	Is_Float = (S2 == "yes") ? 1 : 0;
	Is_Need_File = (S3 == "yes") ? 1 : 0;
	vector<string> Expressions = v.Generate_Expression(Expression_Num, Ops, MaxV, Is_Bracket, Is_Float);
	cout << "\n";
	cout << "以下是生成的表达式:\n";
	for (auto h : Expressions)
	{
		cout << h << " = " << v.Calculate_Expression(h) << "\n";
	}
	if (Is_Need_File)
		v.Print_file(Expressions);
    
	cout << "输入1，结束程序. 输入0, 重启程序.";
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