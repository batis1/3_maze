#include<stdio.h>
#define MaxSize 30
#define max 100
#define ROW 50
#define COL 50
#define REAL_ROW 6
#define REAL_COL 7
typedef struct point
{
	int x;
	int y;
}POINT;

typedef POINT DataType;

typedef struct {
      DataType elem[MaxSize];
      int top;
}SeqStack;

void initStack(SeqStack *S);
int push(SeqStack *, DataType x);
int pop(SeqStack *S, DataType *e);
int getTop(SeqStack *S, DataType *e);
int isEmpty(SeqStack *S);
int isFull(SeqStack *S);
int reverse(int list1[], int list2[]);
void printStack(SeqStack S);
int isPositionEqual(POINT,POINT);
void setPosBlock(int m[ROW][COL],POINT);
int FindNextPos(int m[ROW][COL],POINT,POINT*);
void moveTo(POINT *CurPos, POINT NextPos);
void setMazePath(int m[ROW][COL],int row,int col,SeqStack s);


void main(){
      int m[ROW][COL]=
	{
	{1,1,1,1,1,1,1}, //first row
	{0,0,0,0,0,0,1},
	{1,0,1,0,1,0,1},
	{1,0,1,1,1,1,1},
	{1,0,0,0,0,0,1},  //second row
	{1,1,1,1,1,1,1}, //third row
	 };
      printMaze(m);
      printf("============================\n");
      if(walkMaze(m,REAL_ROW, REAL_COL))
         printf("**found path like you see in above maze.**\n");
      else
          printf("**Sorry path not found it.**\n");
}
// to make the mouse start to move.
int walkMaze(int maze[ROW][COL],int row,int col){
	SeqStack s;
	initStack(&s);
	POINT enter = {1,0};//entry position
	POINT Exit  = {5,3};//exit positin
	// I know the following code is not good for big maze
	// but I can't find another solution.
      int original[ROW][COL];
      for(int i = 0 ;i<REAL_ROW;i++)
            for(int j = 0 ;j<REAL_COL;j++)
                  original[i][j] = maze[i][j];
	POINT CurPos = enter;//current position
	POINT NextPos;//next position
      while(1){
            if(isPositionEqual(CurPos,Exit)){
            // if current position is the exit postion, the mouse come the exit, don't do any more, so stop the loop
			break;
            }
		setPosBlock(maze,CurPos);// else set the current posision as blocked
		if(FindNextPos(maze,CurPos,&NextPos)){ // find the next cell,if find
			push(&s,CurPos); // push the current position
			moveTo(&CurPos,NextPos);// move to next position
		}
		else if(isEmpty(&s)){// if not find , is the stack is empty, it means can not find a path

			break;
		}
		else{ // pop a place from stack as the next current position
			pop(&s,&CurPos);
			if(isEmpty(&s))
				break;
		}
	}
	if(!isEmpty(&s)){ // if stack is not empty, it means find a path,
		setMazePath(original,row,col,s);  // set path  and return 1 for successs
		return 1;
	}
	else
		return 0; // return false, mean can not find a path.
}

// initialize the Stack, set its top to -1;
void initStack(SeqStack *S){
      S->top = -1;
}

int push(SeqStack *S, DataType x){
      if(isFull(S))
            return 0;
      S->elem[++S->top] = x;
      return 1;
}
int  pop(SeqStack *S, DataType *e)
{
      if(isEmpty(S))
            return 0; //underflow
      *e= S->elem [S->top--];
      return 1;
}

int  getTop(SeqStack *S, DataType *e)
{
      if(isEmpty(S))
            return 0; //underflow
      *e= S->elem[S->top];
      return 1;
}
int isFull(SeqStack *S)
{
      return S->top==MaxSize-1;
}
int isEmpty(SeqStack *S)
{
    return S->top==-1;
}
void printStack(SeqStack S){
      DataType e;
      printf("print the stack form top to bottom\n");
      while(S.top != -1){
            pop(&S, &e);
            printf("%d    ",e);
      }
      printf("\n");

}
// to check if the current position is exit or not.
int isPositionEqual(POINT p1,POINT p2){
      return (p1.x == p2.x) && (p1.y == p2.y);
}
// set the specific position to 1, which means block.
void setPosBlock(int m[ROW][COL],POINT p){
      m[p.x][p.y] = 1;
}
// find next position.
int FindNextPos(int m[ROW][COL],POINT curP,POINT*nextP){
      // holding current position.
      POINT move = curP;
      // check for (right). the second condition if move across the maze limit.
      if((!m[move.x][++move.y]) && (move.y< REAL_COL)){
            (*nextP) = move;return 1;
      }
      move = curP;
      // check for (left). the second condition if move across the maze limit.
      if(!m[move.x][--move.y] && (move.y>= 0)) {
            (*nextP) = move;return 1;

      }
      move = curP;
      // check for (up). the second condition if move across the maze limit.
      if(!m[--move.x][move.y] && (move.x>= 0)){

            (*nextP) = move;return 1;
      }
      move = curP;
      // check for (down). the second condition if move across the maze limit.
      if(!m[++move.x][move.y] && (move.x < REAL_COL)){
            (*nextP) = move;return 1;
      }
      return 0;
}
// move the mouse.
void moveTo(POINT *CurPos,POINT NextPos){
      *CurPos = NextPos;
}
void setMazePath(int m[ROW][COL],int row,int col,SeqStack s){
      SeqStack tempS;
      initStack(&tempS);
      POINT movePoints;
      // for reversing to print from enter to exit not the opposite.
      while(!isEmpty(&s)){
            pop(&s,&movePoints);
            push(&tempS,movePoints);
      }
      // create the path found in maze
      int count =1;
      while(!isEmpty(&tempS)){
            pop(&tempS,&movePoints);
            m[movePoints.x][movePoints.y] = count++;
      }
      // print maze with the found path.
      printMaze(m);
}
// print maze.
void printMaze(int maze[ROW][COL]){
      for(int i =0; i<REAL_ROW ;i++){
            for(int j=0; j<REAL_COL;j++)
                  printf(" %d ",maze[i][j]);
            printf("\n");
      }
}

