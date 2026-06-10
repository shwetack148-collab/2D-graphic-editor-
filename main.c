#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define ROWS 30
#define COLS 60

char canvas[ROWS][COLS];

void initializeCanvas() {
    for(int i=0;i<ROWS;i++) {
        for(int j=0;j<COLS;j++) {
            canvas[i][j] = '_';
        }
    }
}

void displayCanvas() {
    printf("\n");
    for(int i=0;i<ROWS;i++) {
        for(int j=0;j<COLS;j++) {
            printf("%c ", canvas[i][j]);
        }
        printf("\n");
    }
}

void plot(int x, int y) {
    if(x >= 0 && x < ROWS && y >= 0 && y < COLS)
        canvas[x][y] = '*';
}

void erasePoint(int x, int y) {
    if(x >= 0 && x < ROWS && y >= 0 && y < COLS)
        canvas[x][y] = '_';
}

void drawLine(int x1, int y1, int x2, int y2) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while(1) {
        plot(x1,y1);

        if(x1 == x2 && y1 == y2)
            break;

        int e2 = 2 * err;

        if(e2 > -dy) {
            err -= dy;
            x1 += sx;
        }

        if(e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
}

void drawRectangle(int x, int y, int width, int height) {
    for(int i=y;i<y+width;i++) {
        plot(x,i);
        plot(x+height-1,i);
    }

    for(int i=x;i<x+height;i++) {
        plot(i,y);
        plot(i,y+width-1);
    }
}

void drawCircle(int xc, int yc, int r) {
    for(int angle=0; angle<360; angle++) {
        double rad = angle * M_PI / 180.0;

        int x = xc + (int)(r*cos(rad));
        int y = yc + (int)(r*sin(rad));

        plot(x,y);
    }
}

void drawTriangle(
    int x1,int y1,
    int x2,int y2,
    int x3,int y3) {

    drawLine(x1,y1,x2,y2);
    drawLine(x2,y2,x3,y3);
    drawLine(x3,y3,x1,y1);
}

int main() {

    initializeCanvas();

    int choice;

    while(1) {

        printf("\n===== 2D Graphics Editor =====\n");
        printf("1. Draw Line\n");
        printf("2. Draw Rectangle\n");
        printf("3. Draw Circle\n");
        printf("4. Draw Triangle\n");
        printf("5. Delete Point\n");
        printf("6. Display Picture\n");
        printf("7. Clear Picture\n");
        printf("0. Exit\n");

        printf("Enter choice: ");
        scanf("%d",&choice);

        if(choice == 0)
            break;

        switch(choice) {

            case 1: {
                int x1,y1,x2,y2;
                printf("Enter x1 y1 x2 y2: ");
                scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
                drawLine(x1,y1,x2,y2);
                break;
            }

            case 2: {
                int x,y,w,h;
                printf("Enter x y width height: ");
                scanf("%d%d%d%d",&x,&y,&w,&h);
                drawRectangle(x,y,w,h);
                break;
            }

            case 3: {
                int x,y,r;
                printf("Enter center_x center_y radius: ");
                scanf("%d%d%d",&x,&y,&r);
                drawCircle(x,y,r);
                break;
            }

            case 4: {
                int x1,y1,x2,y2,x3,y3;
                printf("Enter x1 y1 x2 y2 x3 y3: ");
                scanf("%d%d%d%d%d%d",
                    &x1,&y1,&x2,&y2,&x3,&y3);
                drawTriangle(
                    x1,y1,
                    x2,y2,
                    x3,y3
                );
                break;
            }

            case 5: {
                int x,y;
                printf("Enter point x y: ");
                scanf("%d%d",&x,&y);
                erasePoint(x,y);
                break;
            }

            case 6:
                displayCanvas();
                break;

            case 7:
                initializeCanvas();
                printf("Canvas cleared.\n");
                break;

            default:
                printf("Invalid choice.\n");
        }
    }

    return 0;
}