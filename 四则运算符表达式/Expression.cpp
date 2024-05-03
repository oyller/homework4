#include "Expression.h"


// 隐藏对生成具体对应的表达式的细节
int Expression::Judge_Priority(char ch1, char ch2) // 判断运算符ch1, ch2优先级
{
	if (ch1 == '+' || ch1 == '-')
	{
		if (ch2 == '*' || ch2 == '/' || ch2 == '(')
		{
			return -1;
		}
		    return 2;
	}
	else if (ch1 == '*' || ch1 == '/')
	{
		if (ch2 == '(')
		{
			return -1;
		}
		    return 2;
	}
	else if (ch1 == '(' || ch1 == ')')
	{
		if (ch1 == ')')
		{
			return 2;
		}
		if (ch2 == ')')
		{
			return 0;
		}
		    return -1;
	}
	if (ch2 != '#')
	{
		return -1;
	}
	    return 0;
}

float Expression::Cal(float x, float y, char op) // 处理简单运算式x op y的运算
{
	float value = 0;
	switch (op)
	{
	case '+':
		value = x + y;
		break;
	case '-':
		value = y - x;
		break;
	case '*':
		value = y * x * 1.0;
		break;
	default:
		value = y * 1.0 / x;
		break;
	}
	return value;
}

string Expression::Solve_Bracket(string s) // 给字符串随机加格式匹配的括号
{
	map<char, int> mp;
	string Result = "";
	int num = 0, tag = 0;
	mp['+'] = mp['-'] = mp['*'] = mp['/'] = 1;
	for (int i = 0; i < s.size(); i++)
	{
		Result += s[i];
		if (mp.count(s[i]))
		{
			num++;
		}
		if (num >= 1 && (i + 1 < s.size() && mp.count(s[i + 1]) || (i == s.size() - 1)))
		{
			int l = Result.size() - 1, op = 0, num1 = 0;
			vector<int> path;
			while (l >= 0)
			{
				if (Result[l] == ')')
				{
					op++;
				}
				if (Result[l] == '(')
				{
					op--;
				}
				if (l == 0 || l > 0 && mp.count(Result[l - 1]))
				{
					int randomNumber = rand() % 100;
					if (!op && num1 && randomNumber >= 50)
					{
						int r = rand() % 100;
						if (!tag || (!l && r <= 20) || l)
						{
							tag = 1;
							path.push_back(l);
						}
					}
				}
				if (mp.count(Result[l]))
				{
					num1++;
				}
				    l--;
			}
			int num = path.size();
			for (int j = 0; j < path.size(); j++)
			{
				Result.insert(path[j], "(");
				Result.insert(Result.size(), ")");
			}
		}
	}
	return Result;
}

int Expression::Random_Num(int n) // 产生0~n的随机数
{
	return rand() % (1 + abs(n));
}

string Expression::Solve_Float(float X, int Is_Float) // 处理数据是否为小数
{
	string tmp = "", ops;
	if (Is_Float)
	{
		ops = to_string(X);
	}
	else
		ops = to_string((int)X);
	int num = 0, Is_Point = 0;
	for (int i = 0; i < ops.size(); i++)
	{
		tmp += ops[i];
		if (ops[i] == '.')
		{
			Is_Point = 1;
			continue;
		}
		if (Is_Point)
		{
			num++;
		}
		if (num >= 2)
		{
			break;
		}
	}
	return tmp;
}

string Expression::Solve_Complex( string s, int MaxV, int Is_Float) // 生成复杂运算式
{
	string ans = "";
	int op = Random_Num(4) + 5;
	if (op > 5) op = 5;
	vector<float> Op;
	map<int, int> mp;
	if (s == "")
	{
		s = "+-*/";
	}
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '/')
		{
			swap(s[i], s[s.size() - 1]);
		}
	}
	for (int i = 0; i < op; i++)
	{
		int Num = Random_Num(MaxV);
		int left = 0;
		if (Is_Float)
		{
			left = Random_Num(99);
		}
		Op.push_back(Num + left * 1.0 / 100);
	}
	for (int i = 0; i < Op.size() - 1; i++)
	{
		int cnt = s.size() - 1;
		if (Op[i + 1] == 0 )
		{
			cnt = s.size() - 2;
		}
		int Ope = Random_Num(cnt);
		if (mp.count(Ope))
		{
			for (int i = 0; i <= cnt; i++)
			{
				if (!mp.count(i))
				{
					Ope = i;
					break;
				}
			}
		}
		mp[Ope] = 1;
		ans += Solve_Float(Op[i], Is_Float);
		ans += s[Ope];
	}
	ans += Solve_Float(Op[Op.size() - 1], Is_Float);
	return ans;
}

string Expression::Procced_Expression(string s, int MaxV, int Is_Bracket, int Is_Float) // 加工运算式
{
	string ans;
	float v, Max_Num = 1000000;
	while (1)
	{
		ans = Solve_Complex(s, MaxV, Is_Float);
		if (Is_Bracket)
		{
			ans = Solve_Bracket(ans);
		}
		v = Calculate_Expression(ans);
		if (v >= 0 && v <= Max_Num)
		{
			return ans;
		}
	}
	return "*";
}


vector<string> Expression::Generate_Expression(int num, string s, int MaxV, int Is_Bracket, int Is_Float) // 生成满足num数量，运算符ops, 最大数MaxV, Is_Float是否小数，Is_Bracket是否加括号
{
	vector<string> path;
	for (int i = 0; i < num; i++)
	{
		path.push_back(Procced_Expression(s, MaxV, Is_Bracket, Is_Float));
	}
	return path;
}

float Expression::Calculate_Expression(string s) // 对表达式的值进行计算
{
	s.push_back('#');
	int cnt = 0, len = s.size(), i = -1;
	stack<char> OPTR;
	OPTR.push('#');
	stack<float> OPND;
	while (i < len || OPTR.top() != '#')
	{
		i++;
		if (i >= len)
		{
			float x = OPND.top();
			OPND.pop();
			float y = OPND.top();
			OPND.pop();
			char op = OPTR.top();
			OPTR.pop();
			OPND.push(1.0 * Cal(y, x, op));
			continue;
		}
		if (s[i] >= '0' && s[i] <= '9')
		{
			int tag = 0;
			int j = i;
			float low = 0, k = 0.1;
			while (j < len && s[j] >= '0' && s[j] <= '9' || s[j] == '.')
			{
				if (s[j] == '.')
				{
					tag = 1;
					j++;
					continue;
				}
				if (tag)
				{
					low += (k * (s[j] - '0'));
					k *= 0.1;
				}
				else
				{
					cnt = cnt * 10 + (s[j] - '0');
				}
				j++;
			}
			OPND.push(cnt * 1.0 + low);
			cnt = 0;
			i = j - 1;
			continue;
		}
		if (!(s[i] >= '0' && s[i] <= '9'))
		{
		INIT:

			char op1 = OPTR.top(), op2 = s[i];
			int tag = Judge_Priority(op1, op2);
			if (tag == -1)
			{
				OPTR.push(op2);
				continue;
			}
			else if (tag == 0)
			{
				if (op2 == ')')
				{
					OPTR.pop();
				}
				else
					break;
			}
			else
			{
				float x = OPND.top();
				OPND.pop();
				float y = OPND.top();
				OPND.pop();
				OPTR.pop();
				float ans = 0;
				ans = Cal(x, y, op1);
				OPND.push(ans);
				goto INIT;
			}
		}
	}
	return OPND.top();
}
string Expression::Solve_Input_Ops(string s) // 处理输入的运算符
{
	map<char, int> mp;
	string ans = "";
	for (int i = 0; i < s.size(); i++)
	{
		if (s[i] == '+' || s[i] == '-' || s[i] == '/' || s[i] == '*')
		{
			if (!mp.count(s[i]))
			{
				ans += s[i];
				mp[s[i]] = 1;
			}
		}
	}
	return ans;
}


void Expression::Print_file(vector<string> p)
{
	ofstream file("output.txt");

	if (file.is_open())
	{
		for (const std::string& str : p)
		{
			file << str << std::endl;
		}
		file.close();
		std::cout << "文件已创建并写入成功" << std::endl;
	}
	else
	{
		std::cout << "无法打开文件" << std::endl;
	}
}
