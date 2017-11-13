#include <stdio.h>
#include <stdlib.h>


typedef struct
{int x,y;}points;           // This structure stores x and y coordinates.

/* 1)This is a linked stack with a header node (initially)
   2)The value pointed to by the top is not within the stack.
   3)Every element is pushed between the top and its next element.
   4)The empty condition is when top is null
*/

typedef struct st
{
 points a;            // Stores an element of points
 struct st* next;    //link points to next element
}stack;


typedef stack* stkptr;             // stack* will henceforth be referred to as stkptr
typedef points* pptr;         //points* will be referred to as pptr


stkptr getnode()                               //function that allocates memory and returns the pointer
{
  stkptr s = (stkptr) malloc(sizeof(stack));
  s->next = NULL;
  return s;
}


void push(stkptr f,points ele)        //function that accepts the front pointer and element to be pushed
{
   stkptr s = getnode();

   if(s)                             //malloc returns Null if heap is full.
   {
     s->next = f->next;
     f->next = s;
     s->a = ele;
   }

   else{printf("memory is full\n");}   // if heap is full (We have assumed this won't occur; a limitation.)

}//push



stkptr pop(stkptr f)            //function that pops an element from the stack
{
    if(f!=NULL)                           // if front is null then stack is empty
    {
      stkptr temp = f;
      f = f->next;
      free(temp);                     //freeing the element previously pointed to by front
      return f;                       //since value of f has changed we return f to calling funtion
    }

    else
    {
      printf("stack is empty\n");     //Since we have already handled filled condition in flood fill we aren't
      printf("\n");                  //handling it here
    }

}//pop


int checkValidity(int a[][20],int x, int y)
{
if(x>=15 || y>=20)       //if the points' coordinates exceed the array's limits they are not valid
 return 0;               //We have assumed a 15*20 array

else if(x<0 || y<0)      //if the points' coordinates are negative they are not valid
return 0;

else if(a[x][y]==0)      // if the point's value is 0 it is valid
return 1;

else if(a[x][y]==1)     
 return 0;

}//checkValidity

void display(int a[][20])     //function that displays the array
{
  int i,j;

  for(i=0; i<15; i++)
  {
    for(j=0; j<20; j++)
    {
      printf("%d ", a[i][j]);
    }
    printf("\n");
  }
}//display


void floodFill(int a[][20], points p)   // The function that accepts the array and initial point of filling.
{
  stkptr f;                   //here f is the front of the stack
  f = getnode();
  pptr r = (pptr)malloc(sizeof(points));  //a variable that will store points(coordinates)

  push(f,p);

  int g,h;

   while(f->next!=NULL)                          //while stack not empty
   {
      f = pop(f);                    //update front after deletion
      *r = f->a;
      a[r->x][r->y] = 1;                  //set value of popped el = 1


// Here we have used the 8 neighbour system
//The neighbours are checked for validity before pushing into stack

      if(checkValidity(a,g=r->x-1,h=r->y+1))
      {
        pptr t = (pptr)malloc(sizeof(points));
        t->x = g; t->y = h;
        push(f,*t);
      }

       if(checkValidity(a,g=r->x-1,h=r->y))
      {
        pptr t = (pptr)malloc(sizeof(points));
        t->x = g; t->y = h;
        push(f,*t);
      }

       if(checkValidity(a,g=r->x-1,h=r->y-1))
      {
        pptr t = (pptr)malloc(sizeof(points));
        t->x = g; t->y = h;
        push(f,*t);
      }

      if(checkValidity(a,g=r->x,h=r->y+1))
      {
        pptr t = (pptr)malloc(sizeof(points));
        t->x = g; t->y = h;
        push(f,*t);
      }

      if(checkValidity(a,g=r->x,h=r->y-1))
      {
        pptr t = (pptr)malloc(sizeof(points));
        t->x = g; t->y = h;
        push(f,*t);
      }

       if(checkValidity(a,g=r->x+1,h=r->y+1))
      {
        pptr t = (pptr)malloc(sizeof(points));
        t->x = g; t->y = h;
        push(f,*t);
      }

      if(checkValidity(a,g=r->x+1,h=r->y))
      {
        pptr t = (pptr)malloc(sizeof(points));
        t->x = g; t->y = h;
        push(f,*t);
      }

      if(checkValidity(a,g=r->x+1,h=r->y-1))
      {
        pptr t = (pptr)malloc(sizeof(points));
        t->x = g; t->y = h;
         push(f,*t);
      }

   }//while

  display(a);   // display the array after the filling

}//floodFill


int main()
{
  //We have taken a 15*20 array

   int a[15][20] = {{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0 },
                    { 0, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
                    { 0, 0, 1, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
                    { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 },
                    { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
                    { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
                    { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
                    { 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0 },
                    { 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },
                    { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
                    { 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
                    { 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0 },
                    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 }};


    pptr p = (pptr)malloc(sizeof(points));
    int x1; int y1;

    printf("Enter the source point where the filling should start\n");
    scanf("%d",&x1);
    scanf("%d",&y1);

    p->x = x1; p->y = y1;

    if(checkValidity(a,x1,y1))   //pushed point is checked for validity
    floodFill(a,*p);

    else                        //if not valid no changes are made
      display(a);

    return 0;
} //main
