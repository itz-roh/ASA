#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct node{
    vector<int> parents;
    char colour = 'w';
};

vector<int> find_all_parents(vector<node> nodes, vector<int> vertices, int vertex){
    if(nodes[vertex-1].parents.empty())
        return vertices;
    for(auto iter: nodes[vertex-1].parents){
        vertices.push_back(iter);
        
        vertices = find_all_parents(nodes, vertices, iter);
    }
    return vertices;
}

int is_parent(vector<node> nodes, int u, int v){
    for(auto iter: nodes[u-1].parents)
        if(iter == v)
            return 0;
    return -1;
}

void LCA(vector<node> nodes, int u, int v){
    vector<int> aux1 = {u};
    vector<int> aux2 = {v};
    vector<int> result;
    aux1 = find_all_parents(nodes, aux1, u);
    aux2 = find_all_parents(nodes, aux2, v);
    
    for (auto i: aux2){
        for(auto e: aux1)
            if(i == e)
                result.push_back(i);
    }
    aux1.clear();
    aux1.push_back(result[0]);
    int size = (int)result.size();
    for(int i=1; i < size; i++)
        if(is_parent(nodes, result[i-1], result[i]) == -1)
            aux1.push_back(result[i]);

    for(auto iter: aux1)
        cout << iter << ' ';
    cout << endl;
}


int dfs_visit(vector<node> nodes, int vertex){ 
    
    nodes[vertex].colour = 'g';
    for (auto iter: nodes[vertex].parents){
        if(nodes[iter-1].colour == 'w'){
            if(dfs_visit(nodes, iter-1) == -1)
                return -1;
            }
        else if(nodes[iter-1].colour == 'g'){
            cout << "0" << endl;
            return -1;
        }
    }
    nodes[vertex].colour = 'b';
    
    return 0;
}

void dfs(vector<node> nodes, int size){
    for (int i=0; i < size; i++){
        if(nodes[i].colour == 'w'){
            if (dfs_visit(nodes, i) == -1){
                break;
            }
        }
    }
}

int main()
{
    int u, v, vertices, edges, parent, child;
    if(scanf("%d %d", &u, &v)!=2)
        return -1;
    if(scanf("%d %d", &vertices, &edges)!=2)
        return -1;
    vector<node> nodes(vertices);
    int i = 0;
    while(i<edges){
        if(scanf("%d %d", &parent, &child)!=2)
            return -1;
        
        if(nodes[child-1].parents.size() == 2){
            printf("HERE 2");
            cout << "0" << endl;
            return 0;
        }
        nodes[child-1].parents.push_back(parent);
        i++;
    }
    if(nodes[u-1].parents.empty() && nodes[v-1].parents.empty()){
        cout << "-" << endl;
        return 0;
    }    
    dfs(nodes, vertices);
    LCA(nodes, u, v);
    return 0;
}
