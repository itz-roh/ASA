#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct node{
    vector<int> parents;
    char colour = 'w';
};

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
    node vertex;
    vector<node> nodes(vertices);
    int i = 0;
    while(i<edges){
        if(scanf("%d %d", &parent, &child)!=2)
            return -1;
        
        if(nodes[child-1].parents.size() == 2){
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
    return 0;
}
