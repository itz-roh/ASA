#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct node{
    vector<node> parents;
    string colour;
};

int dfs_visit(vector<node> nodes, node node){
    node.colour = "grey";
    for (auto iter: node.parents)
        if(iter.colour.compare("white") == 0)
            dfs_visit(nodes, iter);
        else if(iter.colour.compare("grey")==0)
            return -1;
    node.colour = "black";
    return 0;
}

void dfs(vector<node> nodes){
    for (auto iter: nodes){
        iter.colour = "white";
    }
    for (auto iter: nodes){
        if(iter.colour.compare("white") == 0)
            dfs_visit(nodes, iter);
    }
}

int main()
{
    int u, v, vertices, edges, parent, child;
    scanf("%d %d", &u, &v);
    scanf("%d %d", &vertices, &edges);
    vector<node> nodes(vertices, node);
    int i = 0;
    while(i<edges){
        scanf("%d %d", &parent, &child);
        if(nodes[child-1].parents.size() == 2){
            cout << "0" << endl;
            return 0;
        }
        nodes[child-1].parents.push_back(parent);
        i++;
    }
    if(nodes[u].parents.empty() && nodes[v].parents.empty()){
        cout << "-" << endl;
        return 0;
    }


    return 0;
}
