class Student{
    public:
        void makeMove(int Record[5][6], int Max[5][6], Color color[5][6], Color inputColor){
            for(int i=0;i<5;i++)
                for(int j=0;j<6;j++){
                    virtual_board[i][j]=Record[i][j];
                    virtural_Max[i][j]=Max[i][j];
                    vitural_color[i][j]=color[i][j];
                }


            for(int i=0;i<5;i++){
                for(int j=0;j<6;j++){
                    if(i==0 && j==0){
                        if(color[0][0]==White)
                    }
                    else if(i==0 && j==5){}
                    else if(i==4 && j==0){}
                    else if(i==4 && j==5){}
                    else if(i==0 && (j==1 || j==2 || j==3 || j==4)){}
                    else if(i==4 && (j==1 || j==2 || j==3 || j==4)){}
                    else if(j==0 && (i==1 || i==2 || i==3 )){}
                    else if(j==5 && (i==1 || i==2 || i==3 )){}
                    else{}
                }
            }
            if(Record[0][0]==0||Record[0][6]==0||Record[5][0]==0||Record[5][6]==0){//下角落
                if(Record[0][0]==0)      {x=0;y=0;}
                else if(Record[0][6]==0) {x=0;y=6;}
                else if(Record[5][0]==0) {x=5;y=0;}
                else                     {x=5;y=6;}
            }
            else{
                if(Record[2][0]==0 && Record[1][0]==0 && Record[3][0]==0)        {x=2;y=0;}
                else if(Record[2][5]==0 && Record[1][5]==0  && Record[3][5]==0 ) {x=2;y=5;}
                else if(Record[0][2]==0 && Record[0][3]==0 &&color[] )
            }
        }
        bool explode_faster_than_neighbor(int x,int y,int Record[5][6],int Max[5][6]){
            if(x==0 && y==0){
                if(Max[0][0]-Record[0][0]<=Max[1][0]-Record[1][0] && Max[0][0]-Record[0][0]<=Max[0][1]-Record[0][1]) return true;
                else return false;
            }
            else if(x==0 && y==5){
                if(Max[0][5]-Record[0][5]<=Max[1][5]-Record[1][5] && Max[0][5]-Record[0][5]<=Max[0][4]-Record[0][4]) return true;
                else return false;
            }
            else if(x==4 && y==0){
                if(Max[4][0]-Record[4][0]<=Max[3][0]-Record[3][0] && Max[4][0]-Record[4][0]<=Max[4][1]-Record[4][1]) return true;
                else return false;
            }
            else if(x==4 && y==5){
                if(Max[4][5]-Record[4][5]<=Max[3][5]-Record[3][5] && Max[4][5]-Record[4][5]<=Max[4][4]-Record[4][4]) return true;
                else return false;
            }
            else{
                if(Max[x][y]-Record[x][y]<=Max[x-1][y]-Record[x-1][y] && Max[x][y]-Record[x][y]<=Max[x+1][y]-Record[x+1][y] && Max[x][y]-Record[x][y]<=Max[x][y-1]-Record[x][y-1] && Max[x][y]-Record[x][y]<=Max[x][y+1]-Record[x][y+1]) return true;
                else return false;
            }
        }
        int evaluate(int Record[5][6], Color color[5][6]){
            int corner_weight=4 ,edge_weight=2, center_weight=1, total_weight=0;
            for(int i=0;i<5;i++)
                for(int j=0;j<6;j++){
                    if(i==0 || i==4)
                        if(j==0 || j==5)
                            total_weight+=Record[i][j]*corner_weight*player_color(color[i][j]);
                        else
                            total_weight+=Record[i][j]*edge_weight*player_color(color[i][j]);
                    else 
                        if(j==0 || j==5)
                            total_weight+=Record[i][j]*edge_weight*player_color(color[i][j]);
                        else
                            total_weight+=Record[i][j]*center_weight*player_color(color[i][j]);
                }
            return total_weight;
        }
        int player_color(Color inputColor){
            if(inputColor==Black)
                return 0;
            else
                return (inputColor==Blue) ? 1:-1 ;
        }
        int minimax(int x, int y, int Record[5][6], int total_weight, int depth, Color inputColor){
            if(depth==0||game_is_over())
                return ;
            if(inputColor==Blue){
                int 
            }
        }
        void explodsion(int x, int y,Color inputColor){          
            virtural_color[x][y]=Black;
            move(x+1,y,inputColor);
            move(x-1,y,inputColor);
            move(x,y-1,inputColor);
            move(x,y+1,inputColor);
            
        }
        void move(int x,int y,Color inputColor){
            if(x<5 && x>-1 && y<6 && y>-1){
                if(virtural_color[x][y]!=Black){
                    virtual_board[x][y]++;
                    virtural_color[x][y]=inputColor;
                    if(virtual_board[x][y]==virtural_Max[x][y]) explodsion(x,y,inputColor);
                } 
            }
        }
        bool is_valid_move(int x,int y,Color inputColor){
            if(x<5 && x>-1 && y<6 && y>-1){
                if((virtural_color[x][y]==inputColor || virtural_color[x][y]==White) && virtual_board[x][y]+1<=virtural_Max[x][y])
                    return true;
            }
            return false;
        }




        int getX(){
            // Your Code
        }
        int getY(){
            // Your Code
        }
    private:
        int x;
        int y;
        int virtual_board[5][6];
        int virtural_Max[5][6];
        Color virtural_color[5][6];
        
    };