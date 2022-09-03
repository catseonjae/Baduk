#include <bits/stdc++.h>
using namespace std;
class Baduk{
    set<int> edge[361],cnt[361], child[361];
    int dy[4]={0,-1,0,1}, dx[4]={1,0,-1,0}, 
    board[361], p[361];
    map<int,double> score;
    
    const int BLACK=1,WHITE=-1,EMPTY=0;
    
    int turn=BLACK;
    
    int point_to_node(int y, int x){
        return 19*y+x;
    }
    bool is_in_range(int x){
        return 0<=x && x<19;
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
    inline vector<int> linked(int node){
        return linked(node/19,node%19);
    }
    int find(int a){
        if(p[a]==a) return a;
        child[p[a]].erase(a);
        p[a]=find(p[a]);
        child[p[a]].insert(a);
        return p[a];
    }
    
public:
    Baduk(double rule){
        score[WHITE]=rule;
        score[BLACK]=0;
        for(int i=0;i<19;i++){
            for(int j=0;j<19;j++){
                int now=point_to_node(i,j);
                board[now]=0;
                p[now]=now;
            }
        }
    }
    
    void link(int a, int b){
        a=find(a);
        b=find(b);
        if(a==b) return;
        cnt[a].erase(b);
        p[b]=a;
        cnt[a].insert(cnt[b].begin(),cnt[b].end());
        cnt[b].clear();
    }
    int clear(int component){
        int ret=1;
        component=find(component);
        board[component]=0;
        for(int i: child[component]){
            p[i]=i;
            ret+=clear(i);
        }
        child[component].clear();
        return ret;
    }
    void put(int node){
        //돌이 이미 있음
        if(board[node]) return;
        board[node]=turn;
        bool suicide=true;
        for(int i: linked(node)){
            if(board[i]==turn && cnt[i].size()==1) continue;
            if(board[i]!=turn) continue;
            suicide=false;
        }
        if(suicide) return;
        
        for(int i: linked(node)){
            if(board[i]==turn) link(node,i);
            else if(board[i]==0) cnt[node].insert(i);
            else{
                cnt[i].erase(node);
                if(cnt[i].empty()) score[turn]=score[turn]+clear(i);
            }
        }
        turn*=-1;
    }
    void put(int y, int x){
        put(point_to_node(y,x));
    }
    void print(){
        cout<<score[-1]<<" "<<score[1];
        cout<<endl;
        for(int i=0;i<19;i++){
            for(int j=0;j<19;j++){
                int node=point_to_node(i,j);
                if(board[node]==0){
                    if(i%6==3 && j%6==3) cout<<"0";
                    else cout<<"+";
                }
                else if (board[node]==1) cout<<"b";
                else cout<<"w";
            }
            cout<<endl;
        }
        cout<<endl;
        cout<<endl;
    }
};

int main() {
    Baduk baduk = Baduk(7);
    baduk.print();
    
    baduk.put(0,0);
    baduk.print();
    
    baduk.put(1,0);
    baduk.print();
    
    baduk.put(1,1);
    baduk.print();
    
    baduk.put(0,1);
    baduk.print();
}
