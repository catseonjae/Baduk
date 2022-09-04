#include <bits/stdc++.h>
using namespace std;
class Baduk{
    const int BLACK=1,WHITE=-1,EMPTY=0,INF=1e9;
    const int STONE_EXIST=-2,SUICIDE=-1,INVALID_COORD=-3;
    
    map<int,double> captured;
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
    map<int,string> user;
    
    Baduk(double rule){
        user[-1]="White",user[1]="Black";
        captured[WHITE]=rule;
        captured[BLACK]=0;
        for(int i=0;i<19;i++){
            for(int j=0;j<19;j++){
                int now=point_to_node(i,j);
                board[now]=0;
                p[now]=now;
            }
        }
    }
    
    //link component of a and component of b
    void link(int a, int b){
        b=find(b);
        cnt[b].erase(a);
        a=find(a);
        if(a==b) return;
        p[b]=a;
        child[a].insert(b);
        cnt[a].insert(cnt[b].begin(),cnt[b].end());
        cnt[b].clear();
    }
    
    //clear component stones
    int clear(int component){
        int ret=1;
        component=find(component);
        board[component]=EMPTY;
        for(int i: child[component]){
            p[i]=i;
            board[i]=EMPTY;
            ret+=clear(i);
        }
        child[component].clear();
        return ret;
    }
    
    //put stone on node or catch exception
    int put(int node){
        if(node<0 || node>=361) return -3;
        //돌이 이미 있음
        if(board[node]!=EMPTY) return -2;
        bool eat=false;
        for(int i:linked(node)){
            if(board[i]==-turn && cnt[i].size()==1){
                eat=true;
            }
        }
        
        if(!eat){
            bool suicide=true;
            for(int i: linked(node)){
                if(board[i]==turn && cnt[i].size()==1) continue;
                if(board[i]==-turn) continue;
                suicide=false;
            }
            if(suicide) return -1;
        }
        
        board[node]=turn;
        int ret=0;
        for(int i: linked(node)){
            if(board[i]==turn) link(node,i);
            else if(board[i]==EMPTY) cnt[node].insert(i);
            else{
                cnt[i].erase(node);
                if(i==1){
                    for(auto j:cnt[i]){
                        cout<<j/19<<" "<<j%19<<endl;
                    }
                }
                if(cnt[i].empty()){
                    int get=clear(i);
                    captured[turn]=captured[turn]+get;
                    ret+=get;
                }
            }
        }
        turn*=-1;
        return ret;
    }
    //put stone on (y,x) or try to do so.
    void put(int y, int x){
        int s=put(point_to_node(y,x));
        if(s==STONE_EXIST) cout<<"you can't put stone on another stone\n";
        if(s==SUICIDE) cout<<"don't suicide...\n";
        if(s==INVALID_COORD) cout<<"the coordinate is not valid\n";
        if(s==1) cout<<user[-turn]<<" captured stone!\n";
        if(s>1) cout<<user[-turn]<<" captured "<<s<<" stones!\n";
    }
    
    //print turn, captured stone and board on console
    void print(){
        cout<<user[turn]<<" turn.\n";
        for(int i: color) cout<<user[i]<<":"<<captured[i]<<" ";
        cout<<endl;
        for(int i=0;i<19;i++){
            for(int j=0;j<19;j++){
                int node=point_to_node(i,j);
                if(board[node]==0){
                    if(i%6==3 && j%6==3) cout<<"0";
                    else cout<<"+";
                }
                else if (board[node]==1) cout<<"B";
                else cout<<"W";
            }
            cout<<endl;
        }
        cout<<endl;
    }
    //estimate score
    void estimate(){
        memset(v,EMPTY,sizeof(v));
        map<int,queue<int>> q;
        q[WHITE]=queue<int>();
        q[BLACK]=queue<int>();
        for(int i=0;i<361;i++){
            if(board[i]!=EMPTY) q[board[i]].push(i);
        }
        int k=2;
        while(!q[BLACK].empty() || !q[WHITE].empty()){
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
    }
    void result(){
        estimate();
        map<int,double> score;
        
        for(int i:color){
            score[i]=captured[i];
        }
        for(int i=0;i<361;i++){
            if(v[i]==INF || (board[i]==EMPTY && v[i]==0)){
                if((i/19)%6==3 && (i%19)%6==3) cout<<"O";
                else cout<<"+";
            }
            else if(board[i]==BLACK){
                cout<<"B";
            } else if(board[i]==WHITE){
                cout<<"W";
            }
            else{
                score[v[i]/abs(v[i])]+=1;
                if(v[i]/abs(v[i])==BLACK) cout<<"b";
                else cout<<"w";
            }
            if(i%19==18) cout<<endl; 
        }
        for(int i:color) cout<<user[i]<<":"<<score[i]<<" ";
        cout<<endl;
        if(user[BLACK]>user[WHITE]) cout<<"Black wins!";
        else if(user[BLACK]==user[WHITE]) cout<<"draw.";
        else cout<<"White wins!";
    }
};

int key(map<int,bool>::iterator it){
    return (*it).first;
}
int main() {
    Baduk baduk = Baduk(7);
    map<int,bool> done;
    done[1]=done[-1]=false;
    bool running=true;
    while(running){
        baduk.print();
        cout<<"put: ";
        int y, x; cin>>y>>x;
        
        if(y==-1 && x==-1)  {
            done[baduk.turn]=true;
            if(done[-baduk.turn]) running=false;
            baduk.turn*=-1;
        }
        if(y==100 && x==100){
            cout<<baduk.user[-baduk.turn]<<" wins by resignation";
            return 0;
        }
        else{
            for(auto i=done.begin();i!=done.end();i++) done[key(i)]=false;
            baduk.put(y,x);
        }
    }
    baduk.result();
}
