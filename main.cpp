#include <vector>
#include <random>
#include <iostream>
#include <ctime>
#include<locale.h>  
#include <omp.h>
#include <stack>
#include <chrono>
#include <fstream>
using namespace std;
using namespace chrono;


void inputMatrix(vector<vector<int>>& matrix, int& n)//���������� ������� �������
{
	for (int i = 1, size = matrix.size(); i < size; ++i)//���������� ���������������� �������
		for (int j = 0; j < i; ++j)
		{
			if (i > j)//���� ��������� ���� ���������, �� ������
				cin >> matrix[i][j];
			if (i - j == 1)
			{
				for (int i = 0, size = matrix.size(); i < size; ++i)
					for (int j = 0; j < n; ++j)
					{
						if (i == j)
							matrix[i][j] = 0;
						else
							matrix[i][j] = matrix[j][i];
					}
			}
		}
}

void printMatrix(vector<vector<int>>& matrix)//����� �������
{
	for (int i = 0, size = matrix.size(); i < size; ++i)
	{
		for (int j = 0; j < matrix.size(); ++j)//��� ������ matrix.size() ��������� n?
			cout << matrix[i][j] << " ";
		cout << endl;
	}
}

void randMatrix(vector<vector<int>>& matrix, int& n)//���������� ������� �������������
{
	for (int i = 0, size = matrix.size(); i < size; ++i)
		for (int j = 0; j < n; ++j)
		{
			if (i < j)
				matrix[i][j] = rand() % 2;
			else if (i == j)
				matrix[i][j] = 0;
			else
				matrix[i][j] = matrix[j][i];
		}
}

void randMatrixProbability(vector<vector<int>>& vec, int& n)
{
	int ver;
	cout << "������� ����������� ��������� ����� (�� 0 �� 100): ";
	cin >> ver;
	int veroyatn;
	for (int i = 0, size = vec.size(); i < size; ++i)
		for (int j = 0; j < n; ++j)
		{
			if (i < j)
			{
				veroyatn = rand() % 100 + 1;
				if (veroyatn <= ver)
					vec[i][j] = 1;
				else
					vec[i][j] = 0;
			}
			else if (i == j)
				vec[i][j] = 0;
			else
				vec[i][j] = vec[j][i];
		}
}


bool add_Edge(vector<vector<int>>& vec, int* num, int n, int& index)//���������� �����
{
	bool flag = true;
	int index1;
	int index2;
	while (flag)
	{
		index1 = rand() % 4;
		index2 = rand() % 4;

		if ((index1 != index2) & (index1 != index) & (index2 != index))
		{
			vec[num[index1]][num[index2]] = 1; vec[num[index2]][num[index1]] = 1;
			flag = false;
		}
	}


	return false;
}


void delete_Edge(vector<vector<int>>& vec, int* num, int n, int& index)//�������� �����
{
	bool flag = true;
	int index2;
	while (flag)
	{
		index2 = rand() % 4;
		if (index != index2) flag = false;
	}

	vec[num[index]][num[index2]] = 0;
	vec[num[index2]][num[index]] = 0;
}

void checking(vector<vector<int>>& vec)//�������� �����
{
	int num[] = { 0,1,2,3 }; //������ ������� ������
	bool flag = false;//����� ���� �� ���� ������� � ������, �� �� ��� �������
	bool flagStr = false;//����� ��� ������� � ������ - true
	int count = 0;//���������� ������
	int index;


	////����� 4 ������, 4 �������. ������������ ���������� while ��������
	while (num[0] < vec.size() - 3)
	{
		while (num[1] < vec.size() - 2)
		{
			while (num[2] < vec.size() - 1)
			{
				while (num[3] < vec.size())
				{
					for (int i = 0; i < 4; ++i)//�������� ����������
					{
						//if ((flag == true) & (flagStr == true)) break;

						for (int j = 0; j < 4; ++j)
						{
							if (vec[num[i]][num[j]]) ++count;//���� ����� 1
						}
						//if (((count > 0) & (count != 3)) || ((count == 3)) & (flagStr == true))//���� ����� ���� �� 1 �������
							//flag = true;
						//else if (count == 3) flagStr = true;//������ 111
						if ((count == 2) || ((flagStr == true) & (count == 3)))
						{
							flag = true;
							count = 0;
							break;
						}

						else if (count == 3)
						{
							index = i;
							flagStr = true;
						}

						count = 0;
					}
					if ((flag == false) & (flagStr == true))
					{
						///////������ �������
						//cout << "1";

						//if (rand() % 2)
						//add_Edge(vec, num, vec.size(), index);

						//else 
						delete_Edge(vec, num, vec.size(), index);

						//cout << endl;
						//printMatrix(vec);

						//////
						flag = false;
						flagStr = false;
						num[0] = 0;
						num[1] = 1;
						num[2] = 2;
						num[3] = 3;
					}
					else
					{
						flag = false;
						flagStr = false;
						++num[3];
					}
				}
				++num[2]; num[3] = num[2] + 1;
			}
			++num[1]; num[2] = num[1] + 1; num[3] = num[2] + 1;
		}
		++num[0]; num[1] = num[0] + 1; num[2] = num[1] + 1; num[3] = num[2] + 1;
	}
}


void alg(vector<vector<int>>& vec, vector<int> set, vector<int> unsaturated, vector<int> path, int& size_set,
	int last_white, int last_black, stack<int> s_last_white, stack<int> s_last_black, bool black_flag)
{
	bool find_max_set = true;
	int last_unsaturated = 0;

	while (find_max_set)
	{
		if (black_flag == false)
		{
			for (int i = 0; i < set.size(); ++i)
			{
				if (vec[path[0]][set[i]])
				{
					path.push_back(set[i]);
					s_last_white.push(set[i]);
					break;
				}
			}

			bool flag_unsaturated = false;
			for (int i = 0; i < unsaturated.size(); ++i)
			{
				flag_unsaturated = false;
				for (int check = 0; check < path.size(); check += 2)
				{
					if (vec[unsaturated[i]][path[check]])
					{
						flag_unsaturated = true;
						break;
					}
				}

				if ((vec[path[path.size() - 1]][unsaturated[i]]) & (unsaturated[i] != path[0]) & (flag_unsaturated == false))
				{
					path.push_back(unsaturated[i]);
					vector<int> tmp_set;
					for (int i = 0; i < set.size(); ++i)
					{
						bool flag_set_ = false;
						for (int j = 1; j < path.size(); j += 2)
						{
							if (set[i] == path[j])
							{
								flag_set_ = true;
								break;
							}
						}
						if (flag_set_ == false)
						{
							tmp_set.push_back(set[i]);
						}
					}

					tmp_set.push_back(path[0]);
					for (int i = 2; i < path.size(); i += 2)
					{
						tmp_set.push_back(path[i]);
					}

					if (size_set < tmp_set.size())
					{
						size_set = tmp_set.size();
					}

					stack<int> tmp_s_last_white;
					stack<int> tmp_s_last_black;
					vector<int> tmp_unsaturated;

					int tmp_count = 0;

					for (int i = 0; i < vec.size(); ++i)
					{
						for (int j = 0; j < tmp_set.size(); ++j)
						{
							if (vec[i][tmp_set[j]]) ++tmp_count;
						}

						if (tmp_count == 1) tmp_unsaturated.push_back(i);
						tmp_count = 0;
					}

					if (tmp_unsaturated.size() < 2)
					{
						path.pop_back();
						continue;
					}

					int num_unsaturated = 0;
					while (num_unsaturated < tmp_unsaturated.size())
					{
						vector<int> tmp_path;
						tmp_path.push_back(tmp_unsaturated[num_unsaturated]);
						tmp_s_last_black.push(tmp_unsaturated[num_unsaturated]);

						alg(vec, tmp_set, tmp_unsaturated, tmp_path, size_set, 0, 0, tmp_s_last_white, tmp_s_last_black, false);
						++num_unsaturated;
					}
					path.pop_back();
				}
			}
		}
		while (1)
		{
			bool add_white = false;
			bool add_black = false;
			bool flag4 = false;

			for (last_black; last_black < vec.size(); ++last_black)
			{
				for (int j = 0; j < path.size(); ++j)
				{
					if (last_black == path[j])
					{
						flag4 = true;
						break;
					}
				}

				if (flag4 == false)
				{
					for (int check = 0; check < unsaturated.size(); ++check)
					{
						if (last_black == unsaturated[check])
						{
							flag4 = true;
							break;
						}
					}
				}

				if (flag4 == false)
				{
					for (int i = 0; i < path.size(); i += 2)
					{
						if (vec[last_black][path[i]])
						{
							flag4 = true;
							break;
						}
					}
				}

				if ((flag4 == false) & (vec[last_black][path[path.size() - 1]]))
				{
					path.push_back(last_black);
					add_black = true;
					s_last_white.push(last_white);
					last_white = 0;
					break;
				}
				flag4 = false;
			}

			if ((add_black == false) & (s_last_white.size() != 0))
			{
				path.pop_back();
				path.pop_back();
				last_white = s_last_white.top();
				s_last_white.pop();
				last_black = s_last_black.top() + 1;
				s_last_black.pop();

				if (path.size() < 2)
				{
					find_max_set = false;
					break;
				}
				continue;
			}

			bool flag6 = false;
			for (last_white; last_white < set.size(); ++last_white)
			{
				for (int check = 0; check < path.size(); ++check)
				{
					if (set[last_white] == path[check])
					{
						flag6 = true;
						break;
					}
				}

				if ((flag6 == false) & (vec[set[last_white]][path[path.size() - 1]]))
				{
					path.push_back(set[last_white]);

					bool flag_unsaturated = false;
					for (int i = 0; i < unsaturated.size(); ++i)
					{
						flag_unsaturated = false;
						for (int check = 0; check < path.size(); check += 2)
						{
							if (vec[unsaturated[i]][path[check]])
							{
								flag_unsaturated = true;
								break;
							}
						}

						if ((vec[path[path.size() - 1]][unsaturated[i]]) & (unsaturated[i] != path[0]) & (flag_unsaturated == false))
						{
							path.push_back(unsaturated[i]);
							vector<int> tmp_set;
							for (int i = 0; i < set.size(); ++i)
							{
								bool flag_set_ = false;
								for (int j = 1; j < path.size(); j += 2)
								{
									if (set[i] == path[j])
									{
										flag_set_ = true;
										break;
									}
								}
								if (flag_set_ == false)
								{
									tmp_set.push_back(set[i]);
								}
							}

							tmp_set.push_back(path[0]);
							for (int i = 2; i < path.size(); i += 2)
							{
								tmp_set.push_back(path[i]);
							}

							if (size_set < tmp_set.size())
							{
								size_set = tmp_set.size();
							}

							stack<int> tmp_s_last_white;
							stack<int> tmp_s_last_black;
							vector<int> tmp_unsaturated;
							int tmp_count = 0;

							for (int i = 0; i < vec.size(); ++i)
							{
								for (int j = 0; j < tmp_set.size(); ++j)
								{
									if (vec[i][tmp_set[j]]) ++tmp_count;
								}

								if (tmp_count == 1) tmp_unsaturated.push_back(i);
								tmp_count = 0;
							}

							if (tmp_unsaturated.size() < 2)
							{
								path.pop_back();
								continue;
							}

							int num_unsaturated = 0;
							while (num_unsaturated < tmp_unsaturated.size())
							{
								vector<int> tmp_path;
								tmp_path.push_back(tmp_unsaturated[num_unsaturated]);
								tmp_s_last_black.push(tmp_unsaturated[num_unsaturated]);

								alg(vec, tmp_set, tmp_unsaturated, tmp_path, size_set, 0, 0, tmp_s_last_white, tmp_s_last_black, false);
								++num_unsaturated;
							}
							path.pop_back();
						}
						add_white = true;
						s_last_black.push(last_black);
						last_black = 0;
						break;
					}
				}
				flag6 = false;
			}

			if ((add_white == false) & (s_last_white.size() != 0))
			{
				path.pop_back();
				++last_black;
				last_white = s_last_white.top();
				s_last_white.pop();

				if (path.size() <= 2)
				{
					find_max_set = false;
					break;
				}
			}
		}
		if (path.size() < 2)
		{
			break;
		}
	}
}


void Prufer(vector<vector<int>>& vec)
{
	srand(time(NULL));
	size_t N = vec.size() - 2;//���������� ���� � ���� �������

	vector<int> code;
	code.resize(N);

	random_device rnd_device; // First create an instance of an engine.
	mt19937 mersenne_engine{ rnd_device() };  // Generates random integers
	uniform_int_distribution<int> dist{ 0, int(vec.size() - 1) };//�������� ��������

	auto gen = [&dist, &mersenne_engine]() {//������
		return dist(mersenne_engine);
	};

	generate(begin(code), end(code), gen);//���������

	//����������, ��, ������ ������ ��������
	vector<int> deg;//������ �������� ������
	deg.resize(vec.size());

	
	for (int i = 0; i < deg.size(); ++i)//����� �������
	{
		int count = 0;

		for (int j = 0; j < code.size(); ++j)//�������, ������� ��� �� �����������
		{
			if (i == code[j]) ++count;
		}
		deg[i] = count + 1;
	}

	vector<vector<int>> stars;//������
	vector<int> leaf;//������
	int vec_indx = 0;

	for (int i = 0; i < deg.size(); ++i)
	{
		if (deg[i] > 2)
		{
			stars.push_back(vector<int>(1));//��������� ������ ������� 1
			stars[vec_indx][0] = i;//��������� ����� �������
			++vec_indx;
		}
		else if (deg[i] == 1)
		{
			leaf.push_back(i);//��������� ����� �������
		}
	}

	//�����������
	int indx = 0;//������, ��� ������ ������ ��������� �� ������� code
	while (indx < N)//���� �� ����� �� ����� ����
	{
		for (int i = 0; i < deg.size(); ++i)
		{
			if (deg[i] == 1)
			{
				vec[i][code[indx]] = 1;
				vec[code[indx]][i] = 1;
				--deg[i];
				--deg[code[indx]];
				++indx;
				break;
			}
		}
	}

	//��������� ��������� �����
	for (int i = 0; i < deg.size(); ++i)//���� �������
	{
		if (deg[i] == 1)
		{
			for (int j = i + 1; j < deg.size(); ++j)//���� ������ ������� � ��������� �����
			{
				if (deg[j] == 1)
				{
					vec[i][j] = 1;
					vec[j][i] = 1;
					break;
				}
			}
			break;
		}
	}


	for (int i = 0; i < stars.size(); ++i)//�������� �� stars, ���� ����������� ������
	{
		for (int j = 0; j < vec.size(); ++j)//��������� ���������
		{
			if (vec[stars[i][0]][j])//���� ������
			{
				stars[i].push_back(j);//��������� �������
			}
		}
	}


	//��������� �����, �������� ������
	int max_edge = leaf.size() / 2;
	int r_num = rand() % (max_edge + 1);
	for (int i = 0; i < r_num; ++i)
	{
		int num1 = 0;
		int num2 = 0;
		while (num1 == num2)
		{
			num1 = rand() % leaf.size();
			num2 = rand() % leaf.size();
		}
		vec[leaf[num1]][leaf[num2]] = 1;
		vec[leaf[num2]][leaf[num1]] = 1;
		swap(leaf[num1], leaf[leaf.size() - 1]);
		swap(leaf[num2], leaf[leaf.size() - 2]);
		leaf.pop_back();
		leaf.pop_back();
	}


	for (int vec_indx = 0; vec_indx < stars.size(); ++vec_indx)//�������� �� �������
	{
		int separate = rand() % (stars[vec_indx].size() - 1) + 1;//���������� ����������� + 1 �.�. ������ ������� ������� � �� ������.

		int pointer = 1;//������� ��������� �� ������ �������, �� ����� ��������� � �������, � 1 �.�. � 0 ������� �������
		while (pointer < separate)//��������� ��������� �� �����������
		{
			for (int j = pointer; j < separate - 1; ++j)//���� ����� ���������, separate - 1 �.�. j+1 ����� ��������� � ������ ������
			{
				vec[stars[vec_indx][pointer]][stars[vec_indx][j + 1]] = 1;
				vec[stars[vec_indx][j + 1]][stars[vec_indx][pointer]] = 1;
			}
			++pointer;
		}

		pointer = separate;
		while (pointer < stars[vec_indx].size())
		{
			for (int j = pointer; j < stars[vec_indx].size() - 1; ++j)//������
			{
				vec[stars[vec_indx][pointer]][stars[vec_indx][j + 1]] = 1;
				vec[stars[vec_indx][j + 1]][stars[vec_indx][pointer]] = 1;
			}
			++pointer;
		}
	}

}

int m_set = 0;
bool check(vector<vector<int>> vec)//�������� ������� �� ���������
{
	for (int i = 0; i < vec.size(); ++i)
	{
		for (int j = 0; j < vec.size(); ++j)
		{
			if (vec[i][j] > 0)
				return true;//���� ����� 1, ���������� true
		}
	}

	return false;//���� �� �����, ���������� false
}

bool check_zero(vector<int> vec)//������� �� �����������?
{
	for (int i = 0; i < vec.size(); ++i)
	{
		if (vec[i] > 0)//�����
			return true;
	}
	return false;
}

#pragma comment(linker, "/STACK:16777216")//���������� ������� �����

void enumeration(vector<vector<int>> vec, vector<unsigned int > nodes, bool del)//����� ��������
{
	for (int i = 0; i < nodes.size(); ++i)
	{
		if ((check_zero(vec[i]) == 0) & (check(vec) == 1))
			continue;

		if ((del == 0) & check_zero(vec[i]))
		{	//������� �������
			vec[i] = vec[vec.size() - 1];
			vec.pop_back();
			nodes.pop_back();

			for (int j = 0; j < vec.size(); ++j)//�������� �� �������, ������� vec.size(), ���� vec.size() + 1, �� ����� �� �������
			{
				vec[j][i] = vec[j][vec.size()];//������ ������� � ���������
				vec[j].pop_back();//������� ��������� �������
			}
		}

		else if (check_zero(vec[i]) == 1)//���� del == 1
		{
			for (int col = 0; col < vec.size(); ++col)//���������� �� ������ � ������� ������� � ��� �������
			{
				if (vec[i][col] > 0)
				{
					for (int row = 0; row < vec.size(); ++row)
					{
						vec[row][col] = vec[row][vec.size() - 1];//������ ������� � ���������
						vec[row].pop_back();//������� ��������� �������
					}
					vec[col] = vec[vec.size() - 1];
					vec.pop_back();
					nodes.pop_back();
					--col;//��� ��������, ���� �� �������� � ���������, � �� �������� �������, ����� ��������� ���
				}
			}
		}

		if (check(vec) == 1)
		{
			enumeration(vec, nodes, 0);//������� �������
			enumeration(vec, nodes, 1);//������� �����������
		}
		else//���� � ������� ������ ����
		{
			if (vec.size() > m_set)
				m_set = vec.size();
		}
	}
}

int main()
{
	setlocale(LC_ALL, "RUS");
	int n;//����������� �����
	cout << endl << "����������� �����: " << endl;
	cin >> n;
	ofstream file1("old_alg.txt");/*��� �������*/ // ������ ������ ofstream
	ofstream file2("new_alg.txt");/*��� �������*/ // ������ ������ ofstream
	
	int mean = 0;
	//double mean_time_old = 0;
	double mean_time_new = 0;
	//int mean_max_set_old = 0;
	int mean_max_set_new = 0;

	//double sum_time_old = 0;
	double sum_time_new = 0;

	//int sum_max_set_old = 0;
	int sum_max_set_new = 0;

	double start;
	double end;

	vector<vector<int>> vec;
	vec.resize(n);
	for (int i = 0, size = vec.size(); i < size; ++i)//������� ������ ��������
		vec[i].resize(n);

	Prufer(vec);


	cout << "��" << endl;
	

	cout << "�����" << endl;
	
	int size_set = 0;

	///////������� set
	start = omp_get_wtime();
	bool flag_tmp = false;
	vector<int> tmp_set;
	tmp_set.push_back(0);

	for (int i = 1; i < vec.size(); ++i)//����� �������� �������
	{
		flag_tmp = false;
		for (int j = 0; j < tmp_set.size(); ++j)//��������� �� � tmp_set
		{
			if (vec[i][tmp_set[j]])//���� ������ ������ � �����
			{
				flag_tmp = true;
				break;
			}
		}

		if (flag_tmp == false)//�� ������
		{
			tmp_set.push_back(i);
			//ins_tmp = true;
		}
	}

	size_set = tmp_set.size();


	vector<int> old_set = tmp_set;//{ num_set };
	bool flag1 = false;//���������
	vector<int> set = old_set;

	int old_size_set;

	///////���� ��������� ������������ ������
	vector<int> main_unsaturated;
	int count1 = 0;

	for (int i = 0; i < vec.size(); ++i)
	{
		for (int j = 0; j < set.size(); ++j)
		{
			if (vec[i][set[j]]) ++count1;
		}

		if (count1 == 1) main_unsaturated.push_back(i);

		count1 = 0;
	}
	vector<int> unsaturated = main_unsaturated;//���� ������� unseturated
				//??//������ ���� find_max_set, � ����� ���� ������ ����� unsaturated, �� ������ ������ set
	end = omp_get_wtime();
	sum_time_new += end - start;
	//cout << "Size unsaturated: " << unsaturated.size() << endl;

	if (unsaturated.size() < 2)
	{
		cout << "Max set: " << size_set << endl;
		cout << "Unsaturated < 2" << endl;
		return 0;
		sum_max_set_new += size_set;

		if (mean == 2)//3 ���� ��������
		{
			//file1 << "N = " << n << " " << (sum_time_old / 3) << "\t" << (sum_max_set_old / 3) << endl;
			file2 << "N = " << n << "\t" << (sum_time_new / 3) << "\t" << (sum_max_set_new / 3) << endl;
			//sum_time_old = 0;
			sum_time_new = 0;
			//sum_max_set_old = 0;
			sum_max_set_new = 0;

			//break;
		}
	}


	int num_unsaturated = 0;
	start = omp_get_wtime();


	while (num_unsaturated < unsaturated.size())
	{
		////////////////////////////////////////////////////////////////////////////////////////
		stack<int> s_last_white;
		stack<int> s_last_black;

		vector<int> path;
		path.push_back(unsaturated[num_unsaturated]);
		s_last_black.push(unsaturated[num_unsaturated]);

		///////�������
		alg(vec, set, unsaturated, path, size_set, 0, 0, s_last_white, s_last_black, false);
		///////

		set = old_set;
		unsaturated = main_unsaturated;
		++num_unsaturated;

	}
	end = omp_get_wtime();
	sum_time_new += end - start;
	sum_max_set_new += size_set;
	//printf_s("Time = %.16g", end - start);
	cout << "Time: " << end - start << endl;
	cout << "Max set: " << size_set << endl;
		if (mean == 2)
		{
			//file1 << "N = " << n << " " << (sum_time_old / 3) << "\t" << (sum_max_set_old / 3) << endl;
			file2 << "N = " << n << "\t" << (sum_time_new / 3) << "\t" << (sum_max_set_new / 3) << endl;
			//sum_time_old = 0;
			sum_time_new = 0;
			//sum_max_set_old = 0;
			sum_max_set_new = 0;


			//break;
		}
		++mean;
		cout << "Max set: " << size_set << endl;
		//cout << "Max set2: " << m_set << endl;

		cout << "N = " << n << endl;

		file1.close();
		file2.close();


		return 0;
}