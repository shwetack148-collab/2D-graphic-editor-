#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 30
#define COLS 60

char canvas[ROWS][COLS];

void initializeCanvas()
{
    for(int i=0;i<ROWS;i++)
        for(int j=0;j<COLS;j++)
            canvas[i][j]='_';
}

void displayCanvas()
{
    printf("\n");

    for(int i=0;i<ROWS;i++)
    {
        for(int j=0;j<COLS;j++)
            printf("%c ",canvas[i][j]);

        printf("\n");
    }
}

void plot(int x,int y,char ch)
{
    if(x>=0 && x<ROWS && y>=0 && y<COLS)
        canvas[x][y]=ch;
}

/* ---------- LINE ---------- */

void drawLineGeneric(int x1,int y1,int x2,int y2,char ch)
{
    int dx=abs(x2-x1);
    int dy=abs(y2-y1);

    int sx=(x1<x2)?1:-1;
    int sy=(y1<y2)?1:-1;

    int err=dx-dy;

    while(1)
    {
        plot(x1,y1,ch);

        if(x1==x2 && y1==y2)
            break;

        int e2=2*err;

        if(e2>-dy)
        {
            err-=dy;
            x1+=sx;
        }

        if(e2<dx)
        {
            err+=dx;
            y1+=sy;
        }
    }
}

/* ---------- RECTANGLE ---------- */

void drawRectangleGeneric(int x,int y,int w,int h,char ch)
{
    for(int i=y;i<y+w;i++)
    {
        plot(x,i,ch);
        plot(x+h-1,i,ch);
    }

    for(int i=x;i<x+h;i++)
    {
        plot(i,y,ch);
        plot(i,y+w-1,ch);
    }
}

/* ---------- CIRCLE ---------- */

void drawCircleGeneric(int xc,int yc,int r,char ch)
{
    for(int angle=0;angle<360;angle++)
    {
        double rad=angle*M_PI/180.0;

        int x=xc+(int)(r*cos(rad));
        int y=yc+(int)(r*sin(rad));

        plot(x,y,ch);
    }
}

/* ---------- TRIANGLE ---------- */

void drawTriangleGeneric(
        int x1,int y1,
        int x2,int y2,
        int x3,int y3,
        char ch)
{
    drawLineGeneric(x1,y1,x2,y2,ch);
    drawLineGeneric(x2,y2,x3,y3,ch);
    drawLineGeneric(x3,y3,x1,y1,ch);
}

/* ---------- DRAW FUNCTIONS ---------- */

void drawLine()
{
    int x1,y1,x2,y2;

    printf("Enter x1 y1 x2 y2: ");
    scanf("%d%d%d%d",&x1,&y1,&x2,&y2);

    drawLineGeneric(x1,y1,x2,y2,'*');
}

void drawRectangle()
{
    int x,y,w,h;

    printf("Enter x y width height: ");
    scanf("%d%d%d%d",&x,&y,&w,&h);

    drawRectangleGeneric(x,y,w,h,'*');
}

void drawCircle()
{
    int x,y,r;

    printf("Enter center_x center_y radius: ");
    scanf("%d%d%d",&x,&y,&r);

    drawCircleGeneric(x,y,r,'*');
}

void drawTriangle()
{
    int x1,y1,x2,y2,x3,y3;

    printf("Enter x1 y1 x2 y2 x3 y3: ");
    scanf("%d%d%d%d%d%d",
          &x1,&y1,
          &x2,&y2,
          &x3,&y3);

    drawTriangleGeneric(
        x1,y1,
        x2,y2,
        x3,y3,
        '*');
}

/* ---------- DELETE FUNCTIONS ---------- */

void deleteLine()
{
    int x1,y1,x2,y2;

    printf("Enter line coordinates: ");
    scanf("%d%d%d%d",&x1,&y1,&x2,&y2);

    drawLineGeneric(x1,y1,x2,y2,'_');
}

void deleteRectangle()
{
    int x,y,w,h;

    printf("Enter rectangle data: ");
    scanf("%d%d%d%d",&x,&y,&w,&h);

    drawRectangleGeneric(x,y,w,h,'_');
}

void deleteCircle()
{
    int x,y,r;

    printf("Enter circle data: ");
    scanf("%d%d%d",&x,&y,&r);

    drawCircleGeneric(x,y,r,'_');
}

void deleteTriangle()
{
    int x1,y1,x2,y2,x3,y3;

    printf("Enter triangle coordinates: ");
    scanf("%d%d%d%d%d%d",
          &x1,&y1,
          &x2,&y2,
          &x3,&y3);

    drawTriangleGeneric(
        x1,y1,
        x2,y2,
        x3,y3,
        '_');
}

/* ---------- MODIFY FUNCTIONS ---------- */

void modifyLine()
{
    printf("\nDelete old line\n");
    deleteLine();

    printf("\nDraw new line\n");
    drawLine();
}

void modifyRectangle()
{
    printf("\nDelete old rectangle\n");
    deleteRectangle();

    printf("\nDraw new rectangle\n");
    drawRectangle();
}

void modifyCircle()
{
    printf("\nDelete old circle\n");
    deleteCircle();

    printf("\nDraw new circle\n");
    drawCircle();
}

void modifyTriangle()
{
    printf("\nDelete old triangle\n");
    deleteTriangle();

    printf("\nDraw new triangle\n");
    drawTriangle();
}

/* ---------- MAIN ---------- */

int main()
{
    initializeCanvas();

    int choice;

    while(1)
    {
        printf("\n===== 2D GRAPHICS EDITOR =====\n");

        printf("1. Draw Line\n");
        printf("2. Draw Rectangle\n");
        printf("3. Draw Circle\n");
        printf("4. Draw Triangle\n");

        printf("5. Delete Line\n");
        printf("6. Delete Rectangle\n");
        printf("7. Delete Circle\n");
        printf("8. Delete Triangle\n");

        printf("9. Modify Line\n");
        printf("10. Modify Rectangle\n");
        printf("11. Modify Circle\n");
        printf("12. Modify Triangle\n");

        printf("13. Display Picture\n");
        printf("14. Clear Picture\n");

        printf("0. Exit\n");

        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1: drawLine(); break;
            case 2: drawRectangle(); break;
            case 3: drawCircle(); break;
            case 4: drawTriangle(); break;

            case 5: deleteLine(); break;
            case 6: deleteRectangle(); break;
            case 7: deleteCircle(); break;
            case 8: deleteTriangle(); break;

            case 9: modifyLine(); break;
            case 10: modifyRectangle(); break;
            case 11: modifyCircle(); break;
            case 12: modifyTriangle(); break;

            case 13: displayCanvas(); break;

            case 14:
                initializeCanvas();
                printf("Canvas Cleared.\n");
                break;

            case 0:
                return 0;

            default:
                printf("Invalid Choice.\n");
        }
    }

    return 0;
}