```cpp
#include <iostream>
#include <algorithm>

using namespace std;

class Student
{
private:
	int score[3];
public:
	Student(int score1,int score2,int score3)
	{
		score[0] = score1;
		score[1] = score2;
		score[2] = score3;
	}
	double GetAvg()
	{
		return (score[0] + score[1] + score[2])*1.0 / 3;
	}
	int Sum()
	{
		return (score[0] + score[1] + score[2]);
	}
	int HigestScore()
	{
		return max(max(score[0],score[1]),score[2]);
	}
	int LowestScore()
	{
		return min(min(score[0],score[1]),score[2]);
	}
	void PrintScore()
	{
		cout << "平均乘积：" << GetAvg() << endl;
		cout << "总成绩：" << Sum() << endl;
		cout << "最高分：" << HigestScore() << endl;
		cout << "最低分：" << LowestScore() << endl;
	}
};

int main()
{
	Student A(99,97,93);
	Student B(87,76,89);
	cout << "学生A的成绩信息：" << endl;
	A.PrintScore();
	cout << "学生B的成绩信息：" << endl;
	B.PrintScore();
	
	return 0;
}
```