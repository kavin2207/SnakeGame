#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

#define N 20
#define M 40
int Field[N][M],x,y,gy,head,tail,gameOver,food,a,b,var,dir = 'd',score=0;

void snakeInitialization(){

    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            Field[i][j]=0;
        }
    }

    x=N/2;
    y=M/2;
    gy=y;
    head = 5;
    tail = 1;
    gameOver = 0;
    food=0;

    for(int i=0;i<head;i++){
        gy++;
        Field[x][gy-head] = i+1;
    }

}

void draw(){

    for(int i = 0;i<=M+1;i++){
        if(i==0){
            printf("%c",201);
        }
        else if(i==M+1){
            printf("%c",187);
        }
        else{
            printf("%c",205);
        }
    }
    printf("\n");

    for(int i=0;i<=N;i++){
        printf("%c",186);
        for(int j=0;j<M;j++){
            if(Field[i][j]==0){
                printf(" ");
            }
            if(Field[i][j]>0 &&Field[i][j]!=head){
                printf("%c",176);
            }
            if(Field[i][j]==head){
                printf("%c",178);
            }
            if(Field[i][j]==-1){
                printf("%c",15);
            }
            if(j==M-1){
                printf("%c\n",186);
            }
        }
    }

    for(int i = 0;i<=M+1;i++){
        if(i==0){
            printf("%c",200);
        }
        else if(i==M+1){
            printf("%c",188);
        }
        else{
            printf("%c",205);
        }
    }

}

void resetScreenPosition(){

    HANDLE hout;
    COORD position;
    hout = GetStdHandle(STD_OUTPUT_HANDLE);
    position.X=0;
    position.Y=0;
    SetConsoleCursorPosition(hout,position);

}
void tailmove(){

    for(int i=0;i<N;i++){
        for(int j=0;j<M;j++){
            if(Field[i][j]==tail){
                Field[i][j]=0;
            }

        }
    }
    tail++;

}
void gameEnd(){

    printf("\a");
    sleep(1000);
    system("cls");

    printf("\n\n                Game Over");

    gameOver = 1;
}

void Random(){

    srand(time(0));
    a = 1+rand()%18;
    b = 1+rand()%38;

    if(food==0&&Field[a][b]==0){
        Field[a][b] = -1;
        food = 1;
    }
    //printf("Score : ",score);

}

int getch_noblock(){

    if(_kbhit()){
        return _getch();
    }
    else{
        return -1;
    }
}

void movement(){

    var = getch_noblock();
    var = tolower(var);

    if(var=='d' ||var=='w' ||var=='a' ||var=='s'){
        dir=var;
    }
    if(dir == 'd'){
        y++;
        if(Field[x][y]!=0&&Field[x][y]!=-1){
            gameEnd();
        }
        if(Field[x][y]==-1){
            food=0;
            tail-=4;
            score +=10;
        }
        head++;
        Field[x][y]=head;
    }

    if(dir == 'a'){
        y--;
        if(Field[x][y]!=0&&Field[x][y]!=-1){
            gameEnd();
        }
        if(Field[x][y]==-1){
            food=0;
            tail-=4;
            score +=10;
        }
        head++;
        Field[x][y]=head;
    }
    if(dir == 'w'){
        x--;
        if(Field[x][y]!=0&&Field[x][y]!=-1){
            gameEnd();
        }
        if(Field[x][y]==-1){
            food=0;
            tail-=4;
            score +=10;
        }
        head++;
        Field[x][y]=head;
    }
    if(dir == 's'){
        x++;
        if(Field[x][y]!=0&&Field[x][y]!=-1){
            gameEnd();
        }
        if(Field[x][y]==-1){
            food=0;
            tail-=4;
            score +=10;
        }
        head++;
        Field[x][y]=head;
    }
}



int main()
{
    snakeInitialization();
    while(gameOver == 0){
        draw();
        resetScreenPosition();
        Random();
        movement();
        tailmove();
    }
    return 0;
}
