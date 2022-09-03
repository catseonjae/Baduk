#include <bits/stdc++.h>
using namespace std;
class Baduk{
    set<set<int>> components;
    //각 노드의 component, 각 컴포넌트의 엣지 및 
    set<set<int>>::iterator p[19][19];
    map< set< set<int> > :: iterator, set<set< set<int> > :: iterator> > edge;
    map< set< set<int> > :: iterator, int> color, cnt;
    int dy[4]={0,-1,0,1}, dx[4]={1,0,-1,0}, board[19][19];
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
    inline vector<int> linked(int y, int x){
        vector<int> ret;
        for(int i=0;i<4;i++){
            int ny=y+dy[i],nx=x+dx[i];
            if(!is_in_range(ny,nx)) continue;
            ret.push_back(point_to_node(ny,nx));
        }
        return ret;
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
        void link(set<set<int>>::iterator a, set<set<int>>::iterator b){
            edge[a].insert(b);
            edge[b].insert(a);
        }
        void merge(set<set<int>>::iterator a, set<set<int>>::iterator b){
            (*a).insert((*b).begin(),(*b).end());
            for(auto i:edge[b]){
                edge[i].erase(b);
                link(i,a);
            }
            int c=color[a];
            for(int i: (*b)){
                board[i/19][i%19]=c;
                p[i/19][i%19]=a;
            }
            edge.erase(b);
        }
        void clear(set<set<int>>::iterator group){
            color[group]=0;
            for(auto i: group){
                board[i/19][i%19]=0;
            }
            for(auto i: edge[group]){
                if(color[i]==0) merge(group,i);
            }
        }
        void put(int y, int x){
            if(color[p[y][x]]) return;
            
            components.insert(set<int>(node);
            auto now=components.find(set<int>(node));
            int way=4;
            for(int next: linked(node)){
                auto it=p[next/19][next%19];
                if(color[it]==turn){
                    merge(now,it);
                    way--;
                }
                else{
                    if(color[it]!=0){
                        way--;
                        edge[it].erase(p[y][x]);
                        cnt[it]--;
                        if(cnt[it]==0) clear(it);
                    }
                    link(now, it);
                }
            }
            
            int node=point_to_node(y,x));
            (*p[y][x]).erase(node);
            edge.erase(p[y][x]);
            
            cnt[now]+=way;
            p[y][x]=now;
            color[now]=turn;
            
            board[y][x]=turn;
            turn*=-1;
        }
        
};
int main() {
    
}
