class Student{
    public:
        void makeMove(int Record[5][6], int Max[5][6], Color color[5][6], Color inputColor){
            //將整個棋盤複製一個到virtual_board上
            for(int i=0;i<5;i++)
                for(int j=0;j<6;j++){
                    virtual_board[i][j]=Record[i][j];
                    virtual_Max[i][j]=Max[i][j];
                    vitual_color[i][j]=color[i][j];
                }
            //使用minimax更改private的x,y值 
            int a=minimax(Record, color, 4, inputColor);    
        }
        int evaluate(int virtual_board[5][6], Color color[5][6]){//角落分數最高,再來邊上,再來中央,分數為該格子顏色乘以該格子的權重再乘以該格子的棋子數目,顏色定義為藍色1,紅色-1 藍色希望越高越好,紅色希望越低越好
            int corner_weight=4 ,edge_weight=2, center_weight=1, total_weight=0;
            for(int i=0;i<5;i++)
                for(int j=0;j<6;j++){
                    if(i==0 || i==4){
                        if(j==0 || j==5)
                            total_weight+=virtual_board[i][j]*corner_weight*player_color(color[i][j]);
                        else
                            total_weight+=virtual_board[i][j]*edge_weight*player_color(color[i][j]);
                    }
                    else{ 
                        if(j==0 || j==5)
                            total_weight+=virtual_board[i][j]*edge_weight*player_color(color[i][j]);
                        else
                            total_weight+=virtual_board[i][j]*center_weight*player_color(color[i][j]);
                    }
                }
            return total_weight;
        }
        int player_color(Color inputColor){ //return玩家顏色的數字以方便計算分數,藍色為1紅色為-1 黑色或白色為0
            if(inputColor==Black || inputColor==White)
                return 0;
            else
                return (inputColor==Blue) ? 1:-1 ;
        }
        int minimax(int board[5][6], Color board_color[5][6], int depth, Color inputColor){
            int value; //目前檯面的評分值,希望能找到比這值更好的
            int best_value= -10000*player_color(inputColor);//對藍色玩家來說希望越大越好,對紅色玩家來說希望越小越好 目前初始值為藍色：-10000 紅色：10000 
            int illegal_value= -10001*player_color(inputColor);//當棋子下在virtual_board上,遇到已經爆炸(黑色),或敵對顏色時,return一個很差的值,使得minimax選值的時候不會選到他們,對Blue來說會是-10001,對Red來說是10001
            int killing_value=10000*player_color(inputColor);//每當有一步能直接清空對面所有棋子時,給出一個最好的值,對Blue來說是10000,對Red來說是-10000
            if(depth==0 || game_is_over(board, board_color, inputColor)){  //終止條件,如果檯面遊戲已經結束,return最好的值,或因為minimax深度到0了直接對檯面評分
                if(game_is_over(board, inputColor)) return killing_value; 
                else return evaluate(virtual_board, virtual_color);
            }
            //對virtual_board上每個點下一次,先判斷我們是藍色還是紅色,在判斷這步是不是合法的,若否則得到很差的值,若是則從此節點繼續minimax直到深度為零或遊戲結束,藍色方則會從所有可能中挑分數最高的走,紅色方會挑所有可能中分數最低的走
            for(int i=0;i<5;i++)
                for(int j=0;j<6;j++){                   
                    if(inputColor==Blue){
                        if(is_valid_move(i, j, inputColor)){                           
                            move(i, j, Blue);
                            value=minimax(virtual_board, virtual_color, depth-1, Red);
                            reset_board(board, board_color);
                        }
                        else
                            value=illegal_value;
                        best_value=max(best_value,value);                               
                    }
                    else{
                        if(is_valid_move(i, j, inputColor)){                           
                            move(i, j, Red);
                            value=minimax(virtual_board, virtual_color, depth-1, Blue);
                            reset_board(board, board_color);
                        }
                        else
                            value=illegal_value;
                        best_value=min(best_value,value);                               
                    }
                    if(value==best_value){ x=i; y=j; } 
                }
            return best_value;
        }
        void explodsion(int x, int y,Color inputColor){   //當x,y點發生爆炸,此點變為黑色,且上下左右各走一步該顏色       
            virtual_color[x][y]=Black;
            move(x+1,y,inputColor);
            move(x-1,y,inputColor);
            move(x,y-1,inputColor);
            move(x,y+1,inputColor);
            
        }
        void move(int x,int y,Color inputColor){//呼叫move時該點不能為對手顏色,因為此函式為了和explodsion互相呼叫,會在move該點時自動更新該點顏色為input的顏色
            if(x<5 && x>-1 && y<6 && y>-1){
                if(virtual_color[x][y]!=Black){
                    virtual_board[x][y]++;
                    virtual_color[x][y]=inputColor;
                    if(virtual_board[x][y]==virtual_Max[x][y]) explodsion(x,y,inputColor);
                } 
            }
        }
        bool is_valid_move(int x,int y,Color inputColor){//確認此步是否合法,非法情況有：1.下在格子外 2.下在黑色(已爆炸)格子上 3.下在對手顏色上 合法return true若非法則false
            if(x<5 && x>-1 && y<6 && y>-1){
                if((virtual_color[x][y]==inputColor || virtual_color[x][y]==White) && virtual_board[x][y]+1<=virtual_Max[x][y])
                    return true;
            }
            return false;
        }
        void reset_board(int board[5][6], int board_color[5][6]){//minimax會將所有情況下過一遍,故每下了一種情況要將virtual_board回復到真正的Record的情況才能繼續往下minimax
            for(int i=0; i<5; i++)
                for(int j=0; j<6; j++){
                    virtual_board[i][j]=board[i][j];
                    virtual_color[i][j]=board_color[i][j];
                }
        }
        bool game_is_over(int board[5][6], Color board_color[5][6], Color inputColor){//兩個條件遊戲結束, 1.檯面上不存在inputcolor對手的顏色 2.檯面全部的棋子總和必須至少有兩顆 另一個條件應該用不到：inputcolor對手沒地方下了
            int counter=0;
            bool whip_out= true;
            for(int i=0; i<5; i++){
                for(int j=0; j<6; j++){
                    counter+=board[i][j];
                    if(board_color[i][j]== opponent_color(inputColor)) whip_out=false;
                }
            }
            if(counter>2 && whip_out==true) return true;
            else return false;
        }
        Color opponent_color(Color inputColor){ //return inputcolor 對手的顏色
            return(inputColor==Blue) ? Red : Blue;
        }


        int getX(){
            return x;
        }
        int getY(){
            return y;
        }
    private:
        int x;
        int y;
        int virtual_board[5][6];
        int virtual_Max[5][6];
        Color virtual_color[5][6];  
    };
