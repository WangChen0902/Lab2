#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const string SRC = "D:\\WCs\\Lab2\\Lab2\\input.txt";	//数据来源
int color[128];		//着色方案数组

bool ok(int k, int c[][128])	//判断顶点k的着色是否发生冲突
{
	int i;
	for (i = 1; i<k; i++)
	{
		if (c[k][i] == 1 && color[i] == color[k])
			return false;
	}
	return true;
}

void graphcolor(int n, int c[][128])
{
	ofstream SaveFile("D:\\WCs\\Lab2\\Lab2\\output.txt");
	bool flag = false;
	int i, k;
	for (i = 1; i <= n; i++)	//初始化着色方案数组
		color[i] = -1;
	k = 1;
	while (k >= 1)
	{
		color[k] = color[k] + 1;
		while (color[k] <= 1)
			if (ok(k, c))
				break;
			else
				color[k] = color[k] + 1;	//搜索下一个颜色
		if (color[k] <= 1&&k == n)		//输出一种可能的着色方案
		{
			flag = true;
			if (flag == true) {
				//cout << "Yes" << endl;
				SaveFile << "Yes" << '\n';
			}
			for (i = 1; i <= n; i++) {
				//cout << color[i];
				SaveFile << color[i];
			}
			//cout << endl;
			break;
		}
		else if (color[k] <= 1&&k<n)
			k = k + 1;	//处理下一个顶点
		else
		{
			color[k] = -1;
			k = k - 1;	//回溯
		}
	}
	if (flag == false) {
		SaveFile << "No";
	}
	SaveFile.close();
}

int main()
{
	//从文本中读取数据
	vector<int> vts;
	ifstream inf(SRC);
	int num;
	int i = 0;
	while (inf >> num) {
		i++;
		vts.push_back(num);
	}
	inf.close();

	int n;
	int c[128][128];//存储n个顶点的无向图的数组
	n = vts[0];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			c[i][j] = 0;
	for (int k = 1; k <= vts[1]; k++) {		//初始化无向图的邻接矩阵
		c[vts[2*k]][vts[2 * k+1]] = 1;
		c[vts[2 * k+1]][vts[2 * k]] = 1;
	}
	graphcolor(n, c);		//调用核心算法

	return 0;
}