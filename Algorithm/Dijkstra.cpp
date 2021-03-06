/* Ref by https://zh.wikipedia.org/wiki/戴克斯特拉算法 */
#include <iostream>
#include <queue>
#include <set>
using namespace std;

typedef vector<vector<int> > Array2D;
int Dijkstra(Array2D&,int,int);

vector<int> roots;
vector<int> road;

int main(){
    int N; //number of dots
    cin >> N;
    Array2D vec(N);
    for(int i=0;i<N;i++){
        roots.push_back(-1);
        for(int j=0;j<N;j++){
            vec[i].push_back(0);
        }
    }
    int start , end; 
    cin >> start >> end;
    start -= 1;
    end -= 1;
    int x,y,weight;
    while(cin >> x >> y >> weight){
        vec[x-1][y-1] = weight;
        vec[y-1][x-1] = weight;
    }
    Dijkstra(vec,start,end);
    return 0;
}


int Dijkstra(Array2D& v,int src=0,int dst=0){
    int N = v.size();
    vector<int> dis(N,0); // the distance from source to destination
    vector<bool> dot(N,false);
    queue<int> q;
    // initial algorithm status
    q.push(src);
    dot[src] = true;
    roots[src] = src;
    // start travel by BFS
    int cur , tmp;
    while(!q.empty()){
        cur = q.front();
        q.pop();
        for(int i=0;i<v[cur].size();i++){
            if(v[cur][i]==0)continue;
            if(dot[i]==false){
                q.push(i);
                dot[i] = true;
                dis[i] = dis[cur] + v[cur][i];
                roots[i] = cur; // where I come from
            }else{ // check which path is shorter
                tmp = dis[cur] + v[cur][i];
                if(dis[i]>tmp){
                    dis[i] = tmp;
                    roots[i] = cur;
                }
            }
        }
    }
    cout << "from " << src+1 << " to " << dst+1 << " : " << dis[dst] << endl;
    cur = dst;
    while(cur!=src){
        if(dot[cur]==false) 
            break;
        road.push_back(cur+1);
        cur = roots[cur];
    }
    road.push_back(src+1);
    for(int i=0;i<road.size();i++)
        cout << road[i] << " -> ";
    cout << endl;
    return dis[dst];
}

/* test data 
6 1 5
1 2 7
1 3 9
1 6 14
2 3 10
2 4 15
3 4 11
3 6 2
5 6 9
4 5 6
*/