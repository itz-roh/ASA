#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;

struct node
{
    vector<int> parents;
    char colour = 'w';
};

vector<node> nodes;

int color_parents(int vertex)
{
    for (auto iter : nodes[vertex - 1].parents)
    {
        nodes[iter - 1].colour = 'r';
        color_parents(iter);
    }
    return 0;
}

void LCA(vector<int> &vertices, int vertex)
{
    if (nodes[vertex - 1].parents.empty())
    {
        if (nodes[vertex - 1].colour == 'r')
        {
            nodes[vertex - 1].colour = 'y';
            vertices.push_back(vertex);
        }
        return;
    }

    for (auto iter : nodes[vertex - 1].parents)
    {

        if (nodes[vertex - 1].colour == 'y')
            nodes[iter - 1].colour = 'o';

        else if (nodes[vertex - 1].colour == 'o')
            nodes[iter - 1].colour = 'o';

        else if (nodes[iter - 1].colour == 'r')
        {
            nodes[iter - 1].colour = 'y';

            vertices.push_back(iter);
        }
        LCA(vertices, iter);
    }

    return;
}

vector<int> pre_processing(int u, int v)
{
    vector<int> aux;
    vector<int> result;
    nodes[u - 1].colour = 'r';
    color_parents(u);
    if (nodes[v - 1].colour == 'r')
    {
        nodes[v - 1].colour = 'y';
        aux.push_back(v);
    }
    LCA(aux, v);

    for (auto iter : aux)
        if (nodes[iter - 1].colour == 'y')
            result.push_back(iter);

    sort(result.begin(), result.end());

    return result;
}

int dfs_visit(int vertex)
{

    nodes[vertex].colour = 'g';
    for (auto iter : nodes[vertex].parents)
    {
        if (nodes[iter - 1].colour == 'w')
        {
            if (dfs_visit(iter - 1) == -1)
                return -1;
        }
        else if (nodes[iter - 1].colour == 'g')
        {
            return -1;
        }
    }
    nodes[vertex].colour = 'b';
    return 0;
}

int dfs(int size)
{
    for (int i = 0; i < size; i++)
    {
        if (nodes[i].colour == 'w')
        {
            if (dfs_visit(i) == -1)
            {
                return -1;
            }
        }
    }
    return 0;
}


int main(){
    std::chrono::time_point<std::chrono::system_clock> start, end;
  
    start = std::chrono::system_clock::now();

    int u, v, vertices, edges, parent, child;
    vector<int> res;
    if (scanf("%d %d", &u, &v) != 2)
        return -1;
    if (scanf("%d %d", &vertices, &edges) != 2)
        return -1;
    node vertex;
    for (int i = 0; i < vertices; i++)
        nodes.push_back(vertex);
    int i = 0;
    while (i < edges)
    {
        if (scanf("%d %d", &parent, &child) != 2)
        {
            cout << "0" << endl;
            return -1;
        }

        if (nodes[child - 1].parents.size() == 2)
        {
            cout << "0" << endl;
            return 0;
        }
        nodes[child - 1].parents.push_back(parent);
        i++;
    }
    if (dfs(vertices) == -1)
    {
        cout << "0" << endl;
        return 0;
    }

    res = pre_processing(u, v);

    if (res.empty())
        cout << "-";
    else
        for (auto iter : res)
            cout << iter << ' ';

    cout << endl;

    end = std::chrono::system_clock::now();
  
    std::chrono::duration<double> elapsed_seconds = end - start;
  
    std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    return 0;
}