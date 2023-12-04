#include "OrGraphInteraction.h"

OrGraphInteraction::OrGraphInteraction()
{

}

void OrGraphInteraction::printQuit()
{
	cout << endl << endl << "Backspace - возврат в меню";

	int answ = _getch();
	bool press = false;

	while (!press)
	{
		if (answ == 8)
		{
			press = true;
			break;
		}
		else
		{
			answ = _getch();
		}
	}

	system("cls");
}

void OrGraphInteraction::Read_g()
{
	adjacencyM.resize(MAXV, vector<bool>(MAXV));

	ifstream ifs("data.txt");
	if (ifs.is_open())
	{
		ifs >> verts;
		ifs >> edges;
		while (!ifs.eof())
		{
			int v, u;
			ifs >> v;
			ifs >> u;
			adjacencyM[v][u] = true;
		}
		cout << "Данные успешно считаны";
	}
	else
	{
		cerr << "Ошибка открытия файла";
	}
	ifs.close();
}

void OrGraphInteraction::Print_g()
{
	for (int i = 1; i <= verts; i++)
	{
		cout << i << " вершина: ";
		vector<int> temp;
		for (int j = 1; j <= verts; j++)
		{
			if (adjacencyM[i][j])
			{
				temp.push_back(j);
				cout << j << " ";
			}
		}
		if (temp.empty())
		{
			cout << "<нет исходящих ребер>";
		}
		cout << endl;
	}
}

int OrGraphInteraction::edgeClass(int first, int second, vector<int>& parents, vector<int>& visited, vector<int>& entryTimes)
{
	if (parents[second] == first) return TREE;
	if (visited[second] == 0) return BACK;
	if (visited[second] == 1 && entryTimes[second] > entryTimes[first]) return FORWARD;
	if (visited[second] == 1 && entryTimes[second] < entryTimes[first]) return CROSS;

	throw exception("Невозможно определить тип ребра");
}

void OrGraphInteraction::DFSComps(stack<int> st, vector<int>& comp, vector<bool>& status, int curVert)
{
	status[curVert] = 0;
	comp.push_back(curVert);

	for (int i = 1; i <= verts; i++)
	{
		if (adjacencyM[curVert][i] && status[i] == -1)
		{
			DFSComps(st, comp, status, i);
		}
	}


}

vector<vector<int>> OrGraphInteraction::FindCompsDFS()
{
	vector<vector<int>> result;
	vector<bool> visited(verts + 1, -1); // -1 = не посещена    0 = посещена     1 = обработана
	vector<bool> earliestVerts(verts + 1, -1);
	stack<int> st;

	for (int i = 1; i <= verts; i++)
	{
		earliestVerts[i] = i;
	}

	for (int i = 1; i <= verts; i++)
	{
		if (visited[i] == -1)
		{
			vector<int> component;
			DFSComps(st, component, visited, i);
			result.push_back(component);
		}
	}

	return result;
}