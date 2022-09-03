#include <bits/stdc++.h>
using namespace std;
class Baduk{
    set<set<int>> components;
    //각 노드의 component, 각 컴포넌트의 엣지 및 색
    set<set<int>>::iterator p[19][19];
    map< set< set<int> > :: iterator, set< set<int> > :: iterator > edge;
    map< set< set<int> > :: iterator, int> color;
    
    int dy[4]={0,-1,0,1}, dx[4]={1,0,-1,0};
    map<int,int> score;
    
    const int BLACK=1,WHITE=-1,EMPTY=0;
    int turn=BLACK;
    
    int point_to_node(Stone stone){
        return (19*stone.y+stone.x)*stone.color;
    }
    
    public:
        Baduk(double rule){
            edge.insert(set<int>());
            color[edge.begin()]=0;
            for(int i=0;i<19;i++){
                for(int j=0;j<19;j++){
                    p[i][j]=edge.begin();
                }
            }
            score[WHITE]=rule;
            score[BLACK]=0;
            set<int> st;
            for(int i=0;i<19;i++){
                for(int j=0;j<19;j++){
                    
                }
            }
        }
        
};
int main() {
    
}
