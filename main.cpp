#include <bits/stdc++.h>
using namespace std;
class Baduk{
    const int BLACK=1,WHITE=-1,EMPTY=0,INF=1e9;
    map<int,double> score;
    set<int> edge[361],cnt[361], child[361];
    
    int dy[4]={0,-1,0,1}, dx[4]={1,0,-1,0}, 
    board[361], p[361], v[361], color[2]={BLACK,WHITE};
    
    
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
    int turn=BLACK;
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
    int put(int node){
        //돌이 이미 있음
        if(board[node]) return 0;
        bool suicide=true;
        for(int i: linked(node)){
            if(board[i]==turn && cnt[i].size()==1) continue;
            if(board[i]==-turn) continue;
            suicide=false;
        }
        if(suicide) return -1;
        board[node]=turn;
        
        for(int i: linked(node)){
            if(board[i]==turn) link(node,i);
            else if(board[i]==EMPTY) cnt[node].insert(i);
            else{
                cnt[i].erase(node);
                if(cnt[i].empty()){
                    score[turn]=score[turn]+clear(i);
                    clear(i);
                }
            }
        }
        turn*=-1;
        return 1;
    }
    void put(int y, int x){
        int s=put(point_to_node(y,x));
        if(s==0) cout<<"you can't put stone on another stone\n";
        if(s==-1) cout<<"don't suicide...\n";
    }
    void print(){
        for(int i: color) cout<<score[i]<<" ";
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
    void estimate(){
        memset(v,EMPTY,sizeof(v));
        map<int,queue<int>> q;
        q[WHITE]=queue<int>();
        q[BLACK]=queue<int>();
        for(int i=0;i<361;i++){
            if(board[i]!=EMPTY) q[board[i]].push(i);
        }
        int k=2;
        while(!q[BLACK].empty() && !q[WHITE].empty()){
            for(int c:color){
                int size=q[c].size();
                while(size--){
                    int now=q[c].front();
                    q[c].pop();
                    if(v[now]==INF) continue;
                    for(int i:linked(now)){
                        if(v[i]==-k*c){
                            v[i]=INF;
                            continue;
                        }
                        if(v[i]==INF) continue;
                        if(board[i]==EMPTY && v[i]==EMPTY){
                            v[i]=k*c;
                            q[c].push(i);
                        }
                    }
                }
            }
            k++;
        }
        
        map<int,double> score_assume;
        
        for(int i:color){
            score_assume[i]=score[i];
        }
        for(int i=0;i<361;i++){
            if(v[i]==INF) cout<<"+";
            else if(board[i]==BLACK){
                cout<<"B";
            } else if(board[i]==WHITE){
                cout<<"W";
            }
            else{
                score_assume[v[i]/abs(v[i])]+=1;
                if(v[i]/abs(v[i])==BLACK) cout<<"b";
                else cout<<"w";
            }
            if(i%19==1) cout<<endl; 
        }
        cout<<"estimate: ";
        for(int i:color) cout<<score_assume[i]<<" ";
        cout<<endl;
    }
};
int key(map<int,bool>::iterator it){
    return (*it).first;
}
int main() {
    Baduk baduk = Baduk(7);
    map<int,bool> done;
    done[1]=done[-1]=false;
    map<int,string> user;
    user[-1]="White",user[1]="Black";
    while(true){
        cout<<"\x1B[2J\x1B[H";
        cout<<user[baduk.turn]<<" turn\n";
        baduk.print();
        cout<<"put: ";
        int y, x; cin>>y>>x;
        if(y==-1 && x==-1)  done[baduk.turn]=1;
        else{
            for(auto i=done.begin();i!=done.end();i++) done[key(i)]=false;
        }
        bool f=true;
        for(auto i=done.begin();i!=done.end();i++) if(done[key(i)]==false) f=false;
        if(f) break;
        baduk.put(y,x);
    }
    baduk.estimate();
}
