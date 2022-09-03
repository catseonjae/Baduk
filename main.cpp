#include <bits/stdc++.h>
using namespace std;
class Baduk{
    set<set<int>> components;
    //각 노드의 component, 각 컴포넌트의 엣지 및 
    set<set<int>>::iterator p[19][19];
    map< set< set<int> > :: iterator, set<set< set<int> > :: iterator> > edge;
    map< set< set<int> > :: iterator, int> color;
    
    int dy[4]={0,-1,0,1}, dx[4]={1,0,-1,0};
    map<int,double> score;
    
    const int BLACK=1,WHITE=-1,EMPTY=0;
    int turn=BLACK;
    
    int point_to_node(int y, int x){
        return 19*y+x;
    }
    bool is_in_range(int x){
        return 0<=x && x<19 && 0<=y && y<19;
    }
    bool is_in_range(int y, int x){
        return is_in_range(y) && is_in_range(x);
    }
    
    public:
        Baduk(double rule){
            score[WHITE]=rule;
            score[BLACK]=0;
            set<int> st;
            for(int i=0;i<19;i++){
                for(int j=0;j<19;j++){
                    st.insert(point_to_node(i,j));
                }
            }
            components.insert(st);
            auto empty_set=set<set<set<int>>::iterator>();
            edge[components.begin()]=*empty_set;
            color[components.begin()]=0;
            for(int i=0;i<19;i++){
                for(int j=0;j<19;j++){
                    p[i][j]=components.begin();
                }
            }
        }
        
        void merge(set<set<int>>::iterator a, set<set<int>>::iterator b){
            (*a).insert((*b).begin(),(*b).end());
            for(auto i:edge[b]){
                edge[i].erase(b);
                edge[i].insert(a);
                edge[a].insert(i);
            }
            for(int i: (*b)){
                p[i/19][i%19]=a;
            }
            edge.erase(b);
        }
        void clear(set<set<int>>::iterator group){
            color[group]=0;
            for(auto i: edge[group]){
                if(color[i]==0) merge(group,i);
            }
        }
        void put(int y, int x){
            if(p[y][x]) return;
            for(int i=0;i<4;i++){
                int ny=y+dy[i],nx=x+dx[i];
                if(!is_in_range(ny,nx)) continue;
            }
        }
};
int main() {
    
}
