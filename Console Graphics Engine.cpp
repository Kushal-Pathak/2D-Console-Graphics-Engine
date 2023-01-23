// Developed by Kushal Pathak
#include <iostream>
#include <conio.h>
#include <math.h>
#include <stdlib.h>
#include <windows.h>
#define pixel 'X'
#define height 49
#define width 105
#define pi 3.14159
using namespace std;

struct Point
{
    int x, y, z;
};

char matrix[height][width];

void maximizeWindow();                                          // mazimizes console window
void init();                                                    // initializes matrix with whitespace character
void display();                                                 // displays matrix content in the console window
void putpixel(int, int);                                        // puts a pixel in the matrix
void line(int, int, int, int);                                  // puts pixels of a line in the matrix
void circle(int, int, int);                                     // puts pixels of a circle in the matrix
void rectangle(int, int, int, int);                             // puts pixels of a rectangle in the matrix
void triangle(int, int, int, int, int, int);                    // puts pixels of a triangle in the matrix
Point rotate(int, int, int, int, float);                        // rotates (x,y) about (h,k) by a given angle
void delay(float);                                              // to create time delay in the algorithm
void rotating_line(int, int, int, int, int, int);               // rotating line animation (Bresenham's)
void rotating_rectangle(int, int, int, int, int, int);          // rotating rectangle animation
void rotating_triangle(int, int, int, int, int, int, int, int); // rotating triangle animation
void menu();

int main()
{
    maximizeWindow();
    init();
    menu();
    display();
    getch();
    return 0;
}

void rotating_triangle(int x1, int y1, int x2, int y2, int x3, int y3, int h, int k)
{
    Point p1, p2, p3;
    p1.x = x1;
    p1.y = y1;
    p2.x = x2;
    p2.y = y2;
    p3.x = x3;
    p3.y = y3;
    int angle = 0;
    while (1)
    {
        angle += 5;
        init();
        // putpixel(h, k);
        triangle(p1.x, p1.y, p2.x, p2.y, p3.x, p3.y);
        display();
        p1 = rotate(x1, y1, h, k, angle);
        p2 = rotate(x2, y2, h, k, angle);
        p3 = rotate(x3, y3, h, k, angle);
    }
}

void rotating_line(int x1, int y1, int x2, int y2, int h, int k)
{
    Point p1, p2;
    p1.x = x1;
    p1.y = y1;
    p2.x = x2;
    p2.y = y2;
    int angle = 0;
    while (1)
    {
        angle += 6;
        init();
        // putpixel(h, k);
        line(p1.x, p1.y, p2.x, p2.y);
        display();
        p1 = rotate(x1, y1, h, k, angle);
        p2 = rotate(x2, y2, h, k, angle);
    }
}

void rotating_rectangle(int x1, int y1, int l, int b, int h, int k)
{
    Point p1, p2, p3, p4;
    p1.x = x1;
    p1.y = y1;
    p2.x = x1 + l;
    p2.y = y1;
    p3.x = p2.x;
    p3.y = y1 + b;
    p4.x = p1.x;
    p4.y = p3.y;
    int angle = 5;
    while (1)
    {
        init();
        triangle(p1.x, p1.y, p2.x, p2.y, p4.x, p4.y);
        triangle(p2.x, p2.y, p3.x, p3.y, p4.x, p4.y);
        display();
        p1 = rotate(p1.x, p1.y, h, k, angle);
        p2 = rotate(p2.x, p2.y, h, k, angle);
        p3 = rotate(p3.x, p3.y, h, k, angle);
        p4 = rotate(p4.x, p4.y, h, k, angle);
    }
}

void init()
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            matrix[i][j] = ' ';
    }
}
void display()
{
    system("cls");
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
            cout << matrix[i][j] << " ";
        cout << "\n";
    }
}

void putpixel(int x, int y)
{
    if (x > width - 1)
        x = x % width;
    if (x < 0)
        x = (x % width) + width;
    if (y > height - 1)
        y = y % height;
    if (y < 0)
        y = (y % height) + height;
    matrix[y][x] = pixel;
}
void line(int x1, int y1, int x2, int y2) // Bresenham's line drawing algorithm
{
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);
    int sx = x1 < x2 ? 1 : -1;
    int sy = y1 < y2 ? 1 : -1;
    int e1 = dx - dy;
    while (true)
    {
        putpixel(x1, y1);
        if (x1 == x2 && y1 == y2)
            break;
        int e2 = 2 * e1;
        if (e2 > -dy)
        {
            e1 -= dy;
            x1 += sx;
        }
        if (e2 < dx)
        {
            e1 += dx;
            y1 += sy;
        }
    }
}
void circle(int h, int k, int r)
{
    int x = r, y = 0, xe, dp, dn, i, dx, dy;
    putpixel(x + h, y + k);
    putpixel(y + h, x + k);
    putpixel(y + h, -x + k);
    putpixel(-x + h, y + k);
    while (x > y)
    {
        y++;
        xe = r * r - y * y;
        dp = abs(xe - x * x);
        dn = abs(xe - (x - 1) * (x - 1));
        if (dn < dp)
            x--;
        putpixel(x + h, y + k);
        putpixel(x + h, -y + k);
        putpixel(-x + h, y + k);
        putpixel(-x + h, -y + k);
        putpixel(y + h, x + k);
        putpixel(y + h, -x + k);
        putpixel(-y + h, x + k);
        putpixel(-y + h, -x + k);
    }
}

void rectangle(int x1, int y1, int l, int b)
{
    line(x1, y1, x1 + l, y1);
    line(x1, y1, x1, y1 + b);
    line(x1, y1 + b, x1 + l, y1 + b);
    line(x1 + l, y1 + b, x1 + l, y1);
}

void delay(float n)
{
    for (int i = 0; i < 1000; i++)
    {
        for (int j = 0; j < 1000; j++)
            for (int k = 0; k < n * 100; k++)
                ;
    }
}
void triangle(int x1, int y1, int x2, int y2, int x3, int y3)
{
    line(x1, y1, x2, y2);
    line(x2, y2, x3, y3);
    line(x3, y3, x1, y1);
}

void maximizeWindow()
{
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_SHOWMAXIMIZED);
}

void menu()
{
    system("cls");
    cout << "_Graphics Engine By Kushal Pathak_\n";
    cout << "1-Draw a pixel\n2-Draw a line\n3-Draw a circle\n4-Draw a triangle\n5-Draw a rectangle\n";
    cout << "6-Rotating line animation\n7-Rotating triangle animation\n8-Rotating rectangle animation\n";
    cout << "9-Line Animation(auto)\n10-Rectangle Animation(auto)\n11-Triangle Animation(auto)\nChoose one: ";
    int n;
    cin >> n;
    switch (n)
    {
        int x, y, x1, y1, x2, y2, x3, y3, l, b, h, k, r;
    case 1:
        cout << "\n(1) Draw a pixel\n";
        cout << "Enter X Y (eg:- 52 24):";
        cin >> x >> y;
        putpixel(x, y);
        break;
    case 2:
        cout << "\n(2) Draw a line\n";
        cout << "Enter X1 Y1 X2 Y2 (eg:- 15 10 72 42): ";
        cin >> x1 >> y1 >> x2 >> y2;
        line(x1, y1, x2, y2);
        break;
    case 3:
        cout << "\n(3) Draw a circle\n";
        cout << "Enter X Y R (eg:- 52 24 10): ";
        cin >> x >> y >> r;
        circle(x, y, r);
        break;
    case 4:
        cout << "\n(4) Draw a triangle\n";
        cout << "Enter X1 Y1 X2 Y2 X3 Y3 (eg:- 52 14 32 34 72 34):";
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        triangle(x1, y1, x2, y2, x3, y3);
        break;
    case 5:
        cout << "\n(5) Draw a rectangle\n";
        cout << "Enter X1 Y1 Length Breadth (eg:- 32 14 40 20):";
        cin >> x1 >> y1 >> l >> b;
        rectangle(x1, y1, l, b);
        break;
    case 6:
        cout << "\n(6) Rotating line animation\n";
        cout << "Enter X1 Y1 X2 Y2 (eg:- 35, 24, 69, 24, 52, 24): ";
        cin >> x1 >> y1 >> x2 >> y2;
        h = round((x1 + x2) / 2);
        k = round((y1 + y2) / 2);
        rotating_line(x1, y1, x2, y2, h, k);
        break;
    case 7:
        cout << "\n(7) Rotating triangle animation\n";
        cout << "Enter X1 Y1 X2 Y2 X3 Y3 (eg:- 50 5 35 35 70 35): ";
        cin >> x1 >> y1 >> x2 >> y2 >> x3 >> y3;
        h = round((x1 + x2 + x3) / 3);
        k = round((y1 + y2 + y3) / 3);
        rotating_triangle(x1, y1, x2, y2, x3, y3, h, k);
        break;
    case 8:
        cout << "\n(8) Rotating rectangle animation\n";
        cout << "Enter X1 Y1 Length Breadth (eg:- 44 16 16 16): ";
        cin >> x1 >> y1 >> l >> b;
        h = round((x1 + x1 + l) / 2);
        k = round((y1 + y1 + b) / 2);
        rotating_rectangle(x1, y1, l, b, h, k);
        break;
    case 9:
        rotating_line(35, 24, 69, 24, 52, 24);
        break;
    case 10:
        rotating_rectangle(44, 16, 16, 16, 52, 24);
        break;
    case 11:
        rotating_triangle(50, 5, 35, 35, 70, 35, 52, 25);
        break;

    default:
        menu();
    }
}
Point rotate(int x, int y, int h, int k, float a)
{
    Point p;
    int dx = x - h, dy = y - k;
    a = (pi / 180) * a;
    p.x = round(dx * cos(a) - dy * sin(a)) + h;
    p.y = round(dx * sin(a) + dy * cos(a)) + k;
    p.z = 0;
    return p;
}