#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

const string SRC = "D:\\WCs\\Lab2\\Lab2\\input.txt";	//������Դ
int color[128];		//��ɫ��������

bool ok(int k, int c[][128])	//�ж϶���k����ɫ�Ƿ�����ͻ
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
	for (i = 1; i <= n; i++)	//��ʼ����ɫ��������
		color[i] = -1;
	k = 1;
	while (k >= 1)
	{
		color[k] = color[k] + 1;
		while (color[k] <= 1)
			if (ok(k, c))
				break;
			else
				color[k] = color[k] + 1;	//������һ����ɫ
		if (color[k] <= 1&&k == n)		//���һ�ֿ��ܵ���ɫ����
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
			k = k + 1;	//������һ������
		else
		{
			color[k] = -1;
			k = k - 1;	//����
		}
	}
	if (flag == false) {
		SaveFile << "No";
	}
	SaveFile.close();
}

int main()
{
	//���ı��ж�ȡ����
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
	int c[128][128];//�洢n�����������ͼ������
	n = vts[0];
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			c[i][j] = 0;
	for (int k = 1; k <= vts[1]; k++) {		//��ʼ������ͼ���ڽӾ���
		c[vts[2*k]][vts[2 * k+1]] = 1;
		c[vts[2 * k+1]][vts[2 * k]] = 1;
	}
	graphcolor(n, c);		//���ú����㷨

	return 0;
}