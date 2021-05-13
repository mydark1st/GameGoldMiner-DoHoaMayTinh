#include <stdio.h>
#include <conio.h>
#include <iostream>
#include <random>
#include "graphics.h"
#pragma comment(lib, "graphics.lib")
int color = WHITE;
#define MAXSIZE 40
#define ROUND(a) (int)(a+0.5)
int coin = 0;
using namespace std;
struct Point
{
	int x, y;
};
//struct viewporttype viewinfoDay;
Point a[MAXSIZE];
void lineDDA(int x1, int y1, int x2, int y2)
{
	int Dx = x2 - x1, Dy = y2 - y1;
	float x_inc, y_inc;
	float step = max(abs(Dx), abs(Dy));
	x_inc = Dx / step;
	y_inc = Dy / step;
	float x = x1, y = y1;
	putpixel(x, y, color);
	int k = 1;
	while (k <= step)
	{
		k++;
		x += x_inc;
		y += y_inc;
		putpixel(x, y, color);
	}
}
void drawcirclePMidPoint(int x0, int y0, int radius)
{
	int x = radius;
	int y = 0;
	int err = 0;

	while (x >= y)
	{
		putpixel(x0 + x, y0 + y, 7);
		putpixel(x0 + y, y0 + x, 7);
		putpixel(x0 - y, y0 + x, 7);
		putpixel(x0 - x, y0 + y, 7);
		putpixel(x0 - x, y0 - y, 7);
		putpixel(x0 - y, y0 - x, 7);
		putpixel(x0 + y, y0 - x, 7);
		putpixel(x0 + x, y0 - y, 7);

		if (err <= 0)
		{
			y += 1;
			err += 2 * y + 1;
		}

		if (err > 0)
		{
			x -= 1;
			err -= 2 * x + 1;
		}
	}
}

void cong(int xc, int yc, int radius)
{
	int x1 = 0, y1 = radius;
	int p = 1 - radius;
	putpixel(xc + x1, yc - y1, WHITE);
	putpixel(xc - x1, yc - y1, WHITE);

	while (x1 < y1)
	{
		if (p < 0) p += (x1 << 1) + 3;
		else
		{
			y1--;
			p += ((x1 - y1) << 1) + 5;
		}
		x1++;
		putpixel(xc + x1, yc - y1, WHITE);
		putpixel(xc - x1, yc - y1, WHITE);
		delay(1);
	}
}
void drawHCN(Point a, Point b, Point c, Point d)
{
	lineDDA(a.x, a.y, b.x, b.y);
	lineDDA(b.x, b.y, c.x, c.y);
	lineDDA(c.x, c.y, d.x, d.y);
	lineDDA(d.x, d.y, a.x, a.y);
}
void drawHCN2D(int a, int b, int c, int d)
{
	lineDDA(a, b, c, b);
	lineDDA(c, b,c, d);
	lineDDA(c, d, a, d);
	lineDDA(a, d, a, b);
}
double calDis(Point m, Point n)
{
	return sqrt(pow((m.x - n.x)*1.0, 2) + pow((m.y - n.y)*1.0, 2));
}
int calRad(double a, double b, double c)
{
	double rad = (b*b + c*c - a*a) / (2 * b*c);
	rad = acos(rad);
	double goc = (180 * rad) / 3.1415;
	if (goc - int(goc) > 0.5)
		return int(goc) + 1;
	else
		return int(goc);
}
bool checkIn(Point q, Point a, Point b, Point c, Point d)
{
	int sum = 0;

	double qa = calDis(q, a);
	double qb = calDis(q, b);
	double qc = calDis(q, c);
	double qd = calDis(q, d);

	double ab = calDis(a, b);
	double bc = calDis(b, c);
	double cd = calDis(c, d);
	double da = calDis(d, a);

	int aqb = calRad(ab, qa, qb);
	int bqc = calRad(bc, qb, qc);
	int cqd = calRad(cd, qc, qd);
	int dqa = calRad(da, qd, qa);

	sum = aqb + bqc + cqd + dqa;
	if (sum >= 358 && sum <= 362)
		return true;
	else
		return false;
}
void fillPoint(int color, Point a, Point b, Point c, Point d)
{
	int ymin, ymax, xmin, xmax;
	ymin = a.y;
	ymax = d.y;
	xmin = a.x;
	xmax = b.x;
	for (int i = ymin; i <= ymax; i++)
		for (int j = xmin; j <= xmax; j++)
		{
			Point q;
			q.x = j;
			q.y = i;
			if (checkIn(q, a, b, c, d))
				putpixel(q.x, q.y, color);
		}
}



////==============================================
Point v[20], n[20];
void initGold(Point h)
{
	v[0] = h;
	n[0].x = v[0].x + 30;
	n[0].y = v[0].y;
	v[1].x = v[0].x + 30;
	v[1].y = v[0].y + 30;
	n[1].x = v[0].x;
	n[1].y = v[0].y + 30;
}
void testVang(Point h)
{
	initGold(h);
	color = YELLOW;
	fillPoint(YELLOW, v[0], n[0], v[1], n[1]);
	//drawHCN2D(v[0].x, v[0].y, v[1].x, v[1].y);
	color = 15;
}
void tinhTienVang(Point h)
{
	h.x = 742;
	h.y = 102;
	cleardevice();
	initGold(h);
	color = YELLOW;
	fillPoint(YELLOW, v[0], n[0], v[1], n[1]);
	//drawHCN2D(v[0].x, v[0].y, v[1].x, v[1].y);
	color = 15;

}

void initGold1(Point j)
{
	v[2] = j;
	n[2].x = v[2].x + 50;
	n[2].y = v[2].y;
	v[3].x = v[2].x + 50;
	v[3].y = v[2].y + 50;
	n[3].x = v[2].x;
	n[3].y = v[2].y + 50;
}
void testVang1(Point j)
{
	initGold1(j);
	color = YELLOW;
	fillPoint(YELLOW, v[2], n[2], v[3], n[3]);
	//drawHCN2D(v[2].x, v[2].y, v[3].x, v[3].y);
	color = 15;
}
void tinhTienVang1(Point j)
{
	j.x = 731;
	j.y = 118;
	cleardevice();
	initGold1(j);
	color = YELLOW;
	fillPoint(YELLOW, v[2], n[2], v[3], n[3]);
	//drawHCN2D(v[2].x, v[2].y, v[3].x, v[3].y);
	color = 15;

}

void initGold2(Point k)
{
	v[4] = k;
	n[4].x = v[4].x + 40;
	n[4].y = v[4].y;
	v[5].x = v[4].x + 40;
	v[5].y = v[4].y + 40;
	n[5].x = v[4].x;
	n[5].y = v[4].y + 40;
}
void testVang2(Point k)
{
	initGold2(k);
	color = YELLOW;
	fillPoint(YELLOW, v[4], n[4], v[5], n[5]);
	//drawHCN2D(v[4].x, v[4].y, v[5].x, v[5].y);
	color = 15;
}
void tinhTienVang2(Point k)
{
	k.x = 696;
	k.y = 133;
	cleardevice();
	initGold2(k);
	color = YELLOW;
	fillPoint(YELLOW, v[4], n[4], v[5], n[5]);
	//drawHCN2D(v[4].x, v[4].y, v[5].x, v[5].y);
	color = 15;

}

void initGold3(Point l)
{
	v[6] = l;
	n[6].x = v[6].x + 100;
	n[6].y = v[6].y;
	v[7].x = v[6].x + 100;
	v[7].y = v[6].y + 100;
	n[7].x = v[6].x;
	n[7].y = v[6].y + 100;
}
void testVang3(Point l)
{
	initGold3(l);
	color = YELLOW;
	fillPoint(YELLOW, v[6], n[6], v[7], n[7]);
	//drawHCN2D(v[6].x, v[6].y, v[7].x, v[7].y);
	color = 15;
}
void tinhTienVang3(Point l)
{
	l.x = 660;
	l.y = 118;
	cleardevice();
	initGold3(l);
	color = YELLOW;
	fillPoint(YELLOW, v[6], n[6], v[7], n[7]);
	//drawHCN2D(v[6].x, v[6].y, v[7].x, v[7].y);
	color = 15;

}

void initGold4(Point s)
{
	v[8] = s;
	n[8].x = v[8].x + 30;
	n[8].y = v[8].y;
	v[9].x = v[8].x + 30;
	v[9].y = v[8].y + 30;
	n[9].x = v[8].x;
	n[9].y = v[8].y + 30;
}
void testVang4(Point s)
{
	initGold4(s);
	color = YELLOW;
	fillPoint(YELLOW, v[8], n[8], v[9], n[9]);
	//drawHCN2D(v[8].x, v[8].y, v[9].x, v[9].y);
	color = 15;
}
void tinhTienVang4(Point s)
{
	s.x = 649;
	s.y = 101;
	cleardevice();
	initGold4(s);
	color = YELLOW;
	fillPoint(YELLOW, v[8], n[8], v[9], n[9]);
	//drawHCN2D(v[8].x, v[8].y, v[9].x, v[9].y);
	color = 15;

}

void initBom(Point g)
{
	v[10] = g;
	n[10].x = v[10].x + 30;
	n[10].y = v[10].y;
	v[11].x = v[10].x + 30;
	v[11].y = v[10].y + 30;
	n[11].x = v[10].x;
	n[11].y = v[10].y + 30;
}
void testBom(Point g)
{
	initBom(g);
	fillPoint(RED, v[10], n[10], v[11], n[11]);
	color = 15;
}
void tinhTienBom(Point g)
{
	g.x = 649;
	g.y = 101;
	cleardevice();
	initBom(g);
	fillPoint(RED, v[10], n[10], v[11], n[11]);
	color = 15;

}
////==============================================
void gameOver()
{
	setcolor(13);
	settextstyle(10, 0, 9);
	outtextxy(320, 250, "GAME OVER");
}
void sad(int x0, int y0, int radius)
{
	int x = radius;
	int y = 0;
	int err = 0;
	
	while (x >= y)
	{
		putpixel(x0 - x, y0 - y, 0);
		putpixel(x0 - y, y0 - x, 0);
		putpixel(x0 + y, y0 - x, 0);
		putpixel(x0 + x, y0 - y, 0);

		if (err <= 0)
		{
			y += 1;
			err += 2 * y + 1;
		}

		if (err > 0)
		{
			x -= 1;
			err -= 2 * x + 1;
		}
	}
}
void drawCircle_Bre(int xc, int yc, int radius)
{
	int x1 = 0, y1 = radius;
	int p = 3 - 2 * radius;

	putpixel(xc + x1, yc + y1, RED);
	putpixel(xc - x1, yc + y1, RED);
	putpixel(xc + x1, yc - y1, RED);
	putpixel(xc - x1, yc - y1, RED);
	putpixel(xc + y1, yc + x1, RED);
	putpixel(xc - y1, yc + x1, RED);
	putpixel(xc + y1, yc - x1, RED);
	putpixel(xc - y1, yc - x1, RED);

	while(x1 <= y1)
	{
		x1++;
		if(p > 0)
		{
			y1--;
			p+= 4 * (x1 - y1) + 10;
		}
		else
			p += 4 * x1 + 6;

	putpixel(xc + x1, yc + y1, RED);
	putpixel(xc - x1, yc + y1, RED);
	putpixel(xc + x1, yc - y1, RED);
	putpixel(xc - x1, yc - y1, RED);
	putpixel(xc + y1, yc + x1, RED);
	putpixel(xc - y1, yc + x1, RED);
	putpixel(xc + y1, yc - x1, RED);
	putpixel(xc - y1, yc - x1, RED);
	}
}
void plot(int xc, int yc, int x, int y, int color)
{
    putpixel(xc+x, yc+y, color);
    putpixel(xc-x, yc+y, color);
    putpixel(xc+x, yc-y, color);
    putpixel(xc-x, yc-y, color);
}
void elipMidpoint(int xc,int yc, int a, int b, int color)
{
    int x, y, fx, fy, a2, b2, p;
    x = 0;
    y = b;
    a2 = a*a;
    b2 = b*b;
    fx = 0;
    fy = 2 * a2 * y;
    plot(xc, yc, x, y, BLACK);
    p = ROUND(b2 -(a2*b) + (0.25*a2));//p=b2 - a2*b +a2/4
    while(fx<fy)
    {
        x++;
        fx += 2*b2;
        
        if(p<0)
        {
            p += b2*(2*x + 3);//p=p + b2*(2x +3)
        }
        else
        {
            y--;
            p += b2*(2*x +3) + a2*(2- 2*y);//p=p +b2(2x +3) +a2(2-2y)
            fy -= 2*a2;
        }
        plot(xc, yc, x, y, BLACK);
    }
    p = ROUND(b2*(x +0.5)*(x +0.5) + a2*(y-1)*(y-1) - a2*b2);
    //
    while(y>0)
    {
        y--;
        fy -= 2*a2;
        
        if(p >=0)
        {
            p += a2*(3-2*y); //p=p +a2(3-2y)
        }
        else
        {
            x++;
            fx += 2*b2;
            p += b2*(2*x +2) +a2*(3- 2*y);//p=p+ b2(2x +2) + a2(3-2y)
        }
        plot(xc, yc, x, y, BLACK);
    }
}
void tint(int x, int y, int color, int border)
{
	int bGCircle = getpixel(x, y);
	if (bGCircle != color && bGCircle != border)
	{
		putpixel(x, y, color);
		tint(x - 1, y, color, border);
		tint(x + 1, y, color, border);
		tint(x, y - 1, color, border);
		tint(x, y + 1, color, border);
	}
}
void drawGameOver()
{
	drawCircle_Bre(920,300,40);
	tint(920,300,YELLOW,4);
	
	gameOver();
	sad(920,320,10);
	elipMidpoint(900,300,5,7,BLACK);
	elipMidpoint(940,300,5,7,BLACK);
}
void datMucTieu()
{
	setcolor(YELLOW);
	settextstyle(10, 0, 9);
	outtextxy(100, 250, "Hoan Thanh Muc Tieu");
	setcolor(11);
	outtextxy(150, 350, "<<--VERY GOOD-->>");
}
////==============================================
void initNV(Point a[])
{
	a[0].x = 700;
	a[0].y = 10;
	a[1].x = a[0].x + 27;
	a[1].y = a[0].y;
	a[2].x = a[1].x;
	a[2].y = a[1].y + 12;
	a[3].x = a[0].x;
	a[3].y = a[2].y;
	a[4].x = a[3].x + 3;
	a[4].y = a[3].y + 3;
	a[5].x = a[2].x - 3;
	a[5].y = a[2].y + 3;
	a[6].x = a[4].x;
	a[6].y = a[4].y + 3;
	a[7].x = a[5].x;
	a[7].y = a[5].y + 3;
	a[8].x = a[6].x;
	a[8].y = a[6].y + 3;
	a[9].x = a[7].x;
	a[9].y = a[7].y + 3;
	a[10].x = a[8].x + 3;
	a[10].y = a[8].y + 4;
	a[11].x = a[9].x - 3;
	a[11].y = a[9].y + 4;
	a[12].x = a[10].x;
	a[12].y = a[10].y + 3;
	a[13].x = a[11].x;
	a[13].y = a[11].y + 3;
	a[14].x = a[12].x + 5;
	a[14].y = a[12].y + 5;
	a[15].x = a[6].x + 10;
	a[15].y = a[8].y + 1;

	a[16].x = a[8].x - 17;
	a[16].y = a[8].y + 10;
	a[17].x = a[16].x - 3;
	a[17].y = a[16].y + 7;

	a[18].x = a[16].x - 10;
	a[18].y = a[17].y;
	a[19].x = a[18].x + 20;
	a[19].y = a[17].y + 20;
	a[20].x = a[11].x - 5;
	a[20].y = a[18].y;
	a[21].x = a[11].x - 5;
	a[21].y = a[17].y + 35;
	a[22].x = a[18].x;
	a[22].y = a[17].y + 35;

	a[23].x = a[18].x - 10;
	a[23].y = a[17].y + 8;
	a[24].x = a[18].x - 10;
	a[24].y = a[17].y + 35;
	a[25].x = a[18].x - 15;
	a[25].y = a[17].y + 8;
	a[26].x = a[18].x - 15;
	a[26].y = a[17].y + 35;
	a[27].x = a[23].x + 10;
	a[27].y = a[23].y;
	a[28].x = a[27].x;
	a[28].y = a[27].y + 5;
	a[29].x = a[23].x;
	a[29].y = a[23].y + 5;

	a[30].x = a[11].x + 19;
	a[30].y = a[17].y + 5;
	a[31].x = a[30].x + 3;
	a[31].y = a[30].y + 8;
	a[32].x = a[11].x - 5;
	a[32].y = a[31].y;
	a[33].x = a[11].x + 32;
	a[33].y = a[17].y + 35;
	a[34].x = a[11].x + 8;
	a[34].y = a[17].y + 35;
	a[35].x = a[11].x + 6;
	a[35].y = a[17].y + 25;
	a[36].x = a[11].x - 4;
	a[36].y = a[17].y + 35;

	//dây câu
	a[37].x = a[19].x;
	a[37].y = a[17].y + 35;
}
void thongSo()
{
	setcolor(YELLOW);
	settextstyle(5, 0, 2);
	outtextxy(20, 10, "Coin: ");
	outtextxy(20, 45, "Target: 150$");
}
void Countdown()
{
	for (int i = 60; i <= 0; i--)
	{
		setcolor(YELLOW);
		//outtextxy(1200, 30, intoChar(i));
		delay(1000);
	}
}
void drawNV(Point a[])
{
	thongSo();
	//Countdown();
	fillPoint(5, a[0], a[1], a[2], a[3]); //nón

	lineDDA(a[3].x, a[3].y, a[4].x, a[4].y);
	lineDDA(a[2].x, a[2].y, a[5].x, a[5].y);
	lineDDA(a[4].x, a[4].y, a[6].x, a[6].y);
	lineDDA(a[5].x, a[5].y, a[7].x, a[7].y);
	lineDDA(a[7].x, a[7].y, a[9].x, a[9].y);
	lineDDA(a[6].x, a[6].y, a[8].x, a[8].y);
	lineDDA(a[9].x, a[9].y, a[11].x, a[11].y);
	lineDDA(a[8].x, a[8].y, a[10].x, a[10].y); //mặt

	color = 7;
	lineDDA(a[10].x, a[10].y, a[12].x, a[12].y);
	lineDDA(a[11].x, a[11].y, a[13].x, a[13].y);
	lineDDA(a[12].x, a[12].y, a[14].x, a[14].y);
	lineDDA(a[13].x, a[13].y, a[14].x, a[14].y);
	lineDDA(a[10].x, a[10].y, a[15].x - 2, a[15].y + 1);
	lineDDA(a[11].x, a[11].y, a[15].x + 2, a[15].y + 1); //râu

	color = 15;

	drawcirclePMidPoint(a[6].x + 5, a[6].y - 1, 1);
	drawcirclePMidPoint(a[7].x - 5, a[7].y - 1, 1); //mắt

	putpixel(a[15].x, a[15].y, RED);
	putpixel(a[15].x - 1, a[15].y, RED);
	putpixel(a[15].x + 1, a[15].y, RED);
	putpixel(a[15].x, a[15].y + 1, RED);
	putpixel(a[15].x, a[15].y - 1, RED);
	drawcirclePMidPoint(a[15].x, a[15].y, 2);//mũi mỏ

	lineDDA(a[4].x + 4, a[4].y, a[4].x + 7, a[4].y);
	lineDDA(a[5].x - 4, a[5].y, a[5].x - 7, a[5].y); //chân mày

	lineDDA(a[4].x, a[4].y, a[4].x - 3, a[4].y);
	lineDDA(a[4].x - 3, a[4].y, a[6].x - 3, a[6].y);
	lineDDA(a[6].x - 3, a[6].y, a[6].x, a[6].y); //lỗ tay phải

	lineDDA(a[5].x, a[5].y, a[5].x + 3, a[5].y);
	lineDDA(a[5].x + 3, a[5].y, a[7].x + 3, a[7].y);
	lineDDA(a[7].x + 3, a[7].y, a[7].x, a[7].y); //lỗ tay trái

	color = 11;
	lineDDA(a[8].x, a[8].y, a[16].x, a[16].y);
	lineDDA(a[16].x, a[16].y, a[17].x, a[17].y);
	lineDDA(a[16].x + 13, a[16].y + 5, a[17].x + 13, a[17].y); //tay phải


	//drawHCN(a[18], a[20], a[21], a[22]); //thùng kéo
	fillPoint(7, a[18], a[20], a[21], a[22]);

	//drawHCN(a[25], a[23], a[24], a[26]);
	fillPoint(6, a[25], a[23], a[24], a[26]);
	//drawHCN(a[23], a[27], a[28], a[29]);
	fillPoint(6, a[23], a[27], a[28], a[29]); //trụ của thùng kéo

	color = 6;
	lineDDA(a[11].x - 5, a[17].y + 10, a[11].x, a[17].y + 10);
	lineDDA(a[11].x, a[17].y + 10, a[11].x, a[17].y + 4);
	lineDDA(a[11].x, a[17].y + 3, a[11].x + 23, a[17].y + 3);
	lineDDA(a[11].x, a[17].y + 4, a[11].x + 23, a[17].y + 4);
	lineDDA(a[11].x, a[17].y + 5, a[11].x + 23, a[17].y + 5);
	lineDDA(a[11].x + 23, a[17].y + 5, a[11].x + 23, a[17].y + 4); //tay xoay của thùng kéo

	color = 11;
	lineDDA(a[9].x, a[9].y, a[2].x + 17, a[16].y - 2);
	lineDDA(a[2].x + 17, a[16].y - 2, a[11].x + 17, a[17].y + 3);
	lineDDA(a[1].x + 4, a[17].y - 7, a[11].x + 5, a[17].y + 3); //tay trái

	lineDDA(a[30].x, a[30].y, a[31].x, a[31].y);
	//lineDDA(a[32].x, a[32].y, a[31].x, a[31].y); //áo

	//lineDDA(a[11].x + 3, a[17].y + 25, a[34].x, a[34].y);
	fillPoint(1, a[32], a[31], a[33], a[34]);
	//lineDDA(a[35].x, a[35].y, a[36].x, a[36].y);
	fillPoint(1, a[32], a[31], a[35], a[36]);
	//phần thân dưới
	color = 15;
}
void drawRanhGioi()
{
	lineDDA(0, a[37].y,getmaxx(), a[37].y);
}
void veQuayDay();

////==============================================
void title()
{
	setcolor(YELLOW);
	settextstyle(3,0,9);
	outtextxy(390, 100, "DAO VANG");
	
}
void kimcuong()
{
	color = 11;
	lineDDA(850,250,900,250); //x150-850, y200-250, x200-900, y200-250
	lineDDA(850,250,820,270); //x120-820,
	lineDDA(900,250,930,270); //x230-930, y220-270
	//3 canh dau
	lineDDA(820,270,875,340); //x175-875, y280-340
	lineDDA(930,270,875,340); 
	//2 canh duoi
	lineDDA(820,270,860,280); //x160-860, y230-280
	lineDDA(860,280,890,280); //x190-890, 
	lineDDA(890,280,930,270); 
	//3 canh giua
	lineDDA(860,280,875,340);
	lineDDA(890,280,875,340);
	//2 duong duoi
	lineDDA(850,250,860,280);
	lineDDA(860,280,875,250);
	lineDDA(875,250,890,280);
	lineDDA(890,280,900,250);
	// 4 canh chu V
	color = 15;
}
void btnStart()
{
	setcolor(RED);
	settextstyle(10, 0, 7);
	outtextxy(490, 270, "Bat Dau");
	//------
	color = YELLOW;
	lineDDA(470, 264, 775, 264);
	lineDDA(470, 264, 470, 346);
	lineDDA(470, 346, 775, 346);
	lineDDA(775, 346, 775, 264);//vuong trong
	//------
	lineDDA(466, 260, 779, 260);
	lineDDA(466, 260, 466, 350);
	lineDDA(466, 350, 779, 350);
	lineDDA(779, 350, 779, 260);//hinh ngoai
	//-------
	
}
void btnXemDiem()
{
	setcolor(GREEN);
	settextstyle(10, 0, 4);
	outtextxy(540, 400, "Xem Diem");
	color = GREEN;
	lineDDA(480,380,750,380);
	lineDDA(480,380,520,410);
	lineDDA(520,410,460,450); //
	lineDDA(460,450,760,450);
	//dddd
	lineDDA(750,380,710,410);
	lineDDA(710,410,760,450);
	//khung
	color = BLACK;
	lineDDA(459,451,460,379);
	lineDDA(459,379,760,379);
	lineDDA(760,379,760,451);
	lineDDA(760,451,459,451);
	

}
void btnThoat()
{
	settextstyle(10, 0, 4);
	setcolor(BLUE);
	outtextxy(565, 502, "Thoat");
	////------
	color = WHITE;
	lineDDA(520, 520, 610, 472);
	lineDDA(610,472,700,520);
	lineDDA(700,520,612,562);
	lineDDA(612,562,520,520);
	//khung
	color = BLACK;
	lineDDA(519,471,701,471);
	lineDDA(701,471,701,562);
	lineDDA(701,562,519,562);
	lineDDA(519,562,519,471);
}
////==============================================
void drawCucVang(int ax, int ay, int bx, int by, int heSo);
void drawCucDa(int ax, int ay, int bx, int by, int heSo);
void drawKimCuong(int ax, int ay, int bx, int by, int heSo);
void drawVatThe(int manChoi) // Vẽ các vật thể trong vùng
{
	int vang = 0;
	int da;
	int kimcuong;
	//random_device rd; // obtain a random number from hardware
	//mt19937 gen(rd()); // seed the generator
	//uniform_int_distribution<int> distr_y(a[17].y + 240, getmaxy() - 105); // define the range
	//uniform_int_distribution<int> distr_x(10, getmaxx() - 105);

	//do
	//{
		random_device rd; // obtain a random number from hardware
		mt19937 gen(rd()); // seed the generator
		uniform_int_distribution<int> distr_y(a[17].y + 240, getmaxy() - 105); // define the range
		uniform_int_distribution<int> distr_x(10, getmaxx() - 105);

		int positiony = distr_y(gen);//Vùng có thể vẽ 
		int positionx = distr_x(gen);//Vùng có thể vẽ 
		drawCucVang(positionx, positiony, positionx + 100, positiony + 100, manChoi);
		//drawCucDa(positionx, positiony, positionx + 80, positiony + 80, manChoi);
		//drawKimCuong(positionx, positiony, positionx + 30, positiony + 30, manChoi);
	/*} while (vang < 10);*/

	//for (da = 0; da < 10; da++)//Vẽ cục đá
	//{			
	//	int positiony = distr_y(gen);//Vùng có thể vẽ 
	//	int positionx = distr_x(gen);//Vùng có thể vẽ 
	//	/*drawCucVang(positionx, positiony, positionx + 100, positiony + 100, manChoi);*/
	//	drawCucDa(positionx, positiony, positionx + 80, positiony + 80, manChoi);
	//	//drawKimCuong(positionx, positiony, positionx + 30, positiony + 30, manChoi);
	//	
	//}

	//for (kimcuong = 0; kimcuong < 10; kimcuong++)//vẽ kim cương
	//{
	//	int positiony = distr_y(gen);//Vùng có thể vẽ 
	//	int positionx = distr_x(gen);//Vùng có thể vẽ 
	//	/*drawCucVang(positionx, positiony, positionx + 100, positiony + 100, manChoi);*/
	//	//drawCucDa(positionx, positiony, positionx + 80, positiony + 80, manChoi);
	//	drawKimCuong(positionx, positiony, positionx + 30, positiony + 30, manChoi);
	//}
}
void drawCucVang(int ax, int ay, int bx, int by, int heSo)// Vẽ cục vàng
{
	lineDDA(ax, ay, bx, ay);
	lineDDA(bx, ay, bx, by);
	lineDDA(bx, by, ax, by);
	lineDDA(ax, by, ax, ay);
	setfillstyle(SOLID_FILL, YELLOW);
	floodfill(ax + 10, ay + 10, WHITE);
	setviewport(ax, ay, bx, by, 1);
	
}
void drawCucDa(int ax, int ay, int bx, int by, int heSo)// Vẽ cục đá
{
	setcolor(7);
	lineDDA(ax, ay, bx, ay);
	lineDDA(bx, ay, bx, by);
	lineDDA(bx, by, ax, by);
	lineDDA(ax, by, ax, ay);
	setfillstyle(SOLID_FILL, LIGHTGRAY);
	floodfill(ax + 10, ay + 10, WHITE);
	setviewport(ax, ay, bx, by, 1);
}
void drawKimCuong(int ax, int ay, int bx, int by, int heSo)// Vẽ kim cương
{
	setcolor(11);
	lineDDA(ax, ay, bx, ay);
	lineDDA(bx, ay, bx, by);
	lineDDA(bx, by, ax, by);
	lineDDA(ax, by, ax, ay);
	setfillstyle(SOLID_FILL, LIGHTCYAN);
	floodfill(ax + 10, ay + 10, WHITE);
	setviewport(ax, ay, bx, by, 1);
}
//==============================================
void drawDayCau()
{
	setactivepage(0);
	veQuayDay();
	setactivepage(1);
	drawVatThe(1);
	setvisualpage(1);
}
void manHinhGameChinh()
{
	//drawDayCau();
	veQuayDay();
}
////==============================================
void beginLevel()
{
	setcolor(WHITE);
	outtextxy(360, 200, "Muc tieu ban can phai dat duoc");
	setcolor(YELLOW);
	settextstyle(10, 0, 9);
	outtextxy(540, 250, "150$");
}
void manHinhBeginLevel()
{
	beginLevel();
}
////==============================================
void manHinhBatDau()
{
	title();
	kimcuong();
	btnStart();
	btnXemDiem();
	btnThoat();
	//click btnStart
	while (1)
	{
		//Ấn nút start
		if (ismouseclick(WM_LBUTTONDOWN))     //Ấn chuột xuống
		{
			int x, y;
			getmouseclick(WM_LBUTTONUP, x, y); // Lấy tọa độ chuột
			if (x < 775 && x > 470 && y < 346 && y > 264) { //Kiểm tra vị trí chuột so với nút bắt đầu
				cleardevice();
				manHinhBeginLevel();
				delay(3000);
				cleardevice();
				manHinhGameChinh();//Chạy màn hình game chính
				clearmouseclick(WM_LBUTTONUP);
				break;
			}
			else if (x < 701 && x > 519 && y < 562 && y > 471) { //Kiểm tra vị trí chuột so với nút bắt đầu
				cleardevice();
				exit(0);
				clearmouseclick(WM_LBUTTONUP);
			}
			clearmouseclick(WM_LBUTTONDOWN); //Hủy sự kiện leftclick
			
		}
		
		//Ấn nút thoát
		//else if (ismouseclick(WM_LBUTTONDOWN))     //Ấn chuột xuống
		//{
		//	int x, y;
		//	getmouseclick(WM_LBUTTONUP, x, y); // Lấy tọa độ chuột
		//	if (x < 701 && x > 519 && y < 562 && y > 471) { //Kiểm tra vị trí chuột so với nút bắt đầu
		//		cleardevice();
		//		exit(0);
		//		clearmouseclick(WM_LBUTTONUP);
		//	}
		//	clearmouseclick(WM_LBUTTONDOWN); //Hủy sự kiện leftclick
		//}

		//Ấn nút xem điểm
		//else if (ismouseclick(WM_LBUTTONDOWN))     //Ấn chuột xuống
		//{
		//	int x, y;
		//	getmouseclick(WM_LBUTTONUP, x, y); // Lấy tọa độ chuột
		//	if (x < 775 && x > 470 && y < 346 && y > 264) { //Kiểm tra vị trí chuột so với nút bắt đầu
		//		cleardevice();
		//		manHinhGameChinh();//Chạy màn hình game chính
		//		clearmouseclick(WM_LBUTTONUP);
		//	}
		//	clearmouseclick(WM_LBUTTONDOWN); //Hủy sự kiện leftclick
		//}
	}
}
////==============================================
void veQuayDay()
{
	int over = 1;
	int taget = 1;
	int diem = 0;
	int flag = 1;
	int flag1 = 1;
	int flag2 = 1;
	int flag3 = 1;
	int flag4 = 1;
	Point h,j,k,l,s,g, gg;
	h.x = 788;
	h.y = 133;
	j.x = 1066;
	j.y = 466;
	k.x = 676;
	k.y = 383;
	l.x = 186;
	l.y = 576;
	s.x = 494;
	s.y = 103;
	g.x = 480;
	g.y = 500;
	gg.x = 900;
	gg.y = 540;
	initNV(a);
	int dem = 0;
	double goc = 0.0;
	int page = 0;
	int r = 50;
	while (true) {
		while (goc < 180.0 && over == 1 && taget == 1) { // Khi dây chưa tới vị trí kết thúc
			dem ++;
			//Giảm buffering
			setactivepage(page);
			setvisualpage(1 - page);
			//Vẽ
			cleardevice();
			drawNV(a);
			testBom(g);
			testBom(gg);
			if (flag == 1)
				testVang(h);
			if (flag1 == 1)
				testVang1(j);
			if (flag2 == 1)
				testVang2(k);
			if (flag3 == 1)
				testVang3(l);
			if (flag4 == 1)
				testVang4(s);
			
			drawRanhGioi();
			int xo, yo;
			xo = a[37].x;
			yo = a[37].y;
			int xoo, yoo;
			xoo = a[37].x + r;
			yoo = yo;
			int xd, yd;
			xd = (xoo - xo) * cos((goc*3.14159265) / 180) - (yoo - yo) * sin((goc*3.14159265) / 180) + xo;
			yd = (xoo - xo) * sin((goc*3.14159265) / 180) + (yoo - yo) * cos((goc*3.14159265) / 180) + yo;
			//-------------------
			goc += 5.0;//Quay
			lineDDA(xo, yo, xd, yd);//tâm đầu dây -> ví trí mới sau xoay 5 độ
			cong(xd, yd + 25, 25);
			delay(300);

			if (ismouseclick(WM_LBUTTONDOWN))     //Ấn chuột phải xuống
			{
				r = 700;
				if (xd == 741 || xd == 739 || xd == 736 || xd == 734)
				{
					if (flag == 1)
					{
						r = 120; //Không hiện thực
						flag = 0;
						diem += 30;
						tinhTienVang(h);
						drawNV(a);
						if (flag1 == 1)
							testVang1(j);
						if (flag2 == 1)
							testVang2(k);
						if (flag3 == 1)
							testVang3(l);
						if (flag4 == 1)
							testVang4(s);
						drawRanhGioi();
						outtextxy(20, 10, "Coin: +30");
					}
				}
				if (xd == 731)
				{
					if (flag1 == 1)
					{
						r = 225; //Không hiện thực
						flag1 = 0;
						diem += 50;
						tinhTienVang1(j);
						drawNV(a);
						if (flag == 1)
							testVang(h);
						if (flag2 == 1)
							testVang2(k);
						if (flag3 == 1)
							testVang3(l);
						if (flag4 == 1)
							testVang4(s);
						drawRanhGioi();
						outtextxy(20, 10, "Coin: +50");
					}
				}
				if (xd == 696)
				{
					if (flag2 == 1)
					{
						r = 300; //Không hiện thực
						flag2 = 0;
						diem += 40;
						tinhTienVang2(k);
						drawNV(a);
						if (flag == 1)
							testVang(h);
						if (flag1 == 1)
							testVang1(j);
						if (flag3 == 1)
							testVang3(l);
						if (flag4 == 1)
							testVang4(s);
						drawRanhGioi();
						outtextxy(20, 10, "Coin: +40");
					}
				}
				if (xd == 667 || xd == 663 || xd == 660)
				{
					if (flag3 == 1)
					{
						r = 705; //Không hiện thực
						flag3 = 0;
						diem += 100;
						tinhTienVang3(l);
						drawNV(a);
						if (flag == 1)
							testVang(h);
						if (flag1 == 1)
							testVang1(j);
						if (flag2 == 1)
							testVang2(k);
						if (flag4 == 1)
							testVang4(s);
						drawRanhGioi();
						outtextxy(20, 10, "Coin: +100");
					}
				}
				if (xd == 647 || xd == 646)
				{
					if (flag4 == 1)
					{
						r = 200; //Không hiện thực
						flag4 = 0;
						diem += 30;
						tinhTienVang4(s);
						drawNV(a);
						if (flag == 1)
							testVang(h);
						if (flag1 == 1)
							testVang1(j);
						if (flag2 == 1)
							testVang2(k);
						if (flag3 == 1)
							testVang3(l);
						drawRanhGioi();
						outtextxy(20, 10, "Coin: +30");
					}
				}
				if (xd == 674 || xd == 717)
					dem = 49;
				lineDDA(xo, yo, xd, yd);
				cong(xd, yd + 25, 25);
				clearmouseclick(WM_LBUTTONDOWN);
			}
			if (ismouseclick(WM_LBUTTONUP))     //Thả chuột
			{
				color = WHITE;
				r = 50;
				lineDDA(xo, yo, xd, yd);
				cong(xd, yd + 25, 25);
				clearmouseclick(WM_LBUTTONUP);
			}
			if (diem >= 150)
			{
				taget = 0;
				cleardevice();
				datMucTieu();
			}
			page = 1 - page;
			if (dem == 49) //tầm 60s
			{
				over = 0;
				cleardevice();
			}
		}	

		while (goc > 0.0) { //Khi dây chưa quay về vị trí bắt đầu
			//Giảm buffering
			setactivepage(page);
			setvisualpage(1 - page);
			//Vẽ
			cleardevice();
			drawNV(a);
			if (flag == 1)
				testVang(h);
			if (flag1 == 1)
				testVang1(j);
			if (flag2 == 1)
				testVang2(k);
			if (flag3 == 1)
				testVang3(l);
			if (flag4 == 1)
				testVang4(s);
			drawRanhGioi();
			int xo, yo;
			xo = a[37].x;
			yo = a[37].y;
			int xoo, yoo;
			xoo = a[37].x + r;
			yoo = yo;
			int xd, yd;
			xd = (xoo - xo) * cos((goc*3.14159265) / 180) - (yoo - yo) * sin((goc*3.14159265) / 180) + xo;
			yd = (xoo - xo) * sin((goc*3.14159265) / 180) + (yoo - yo) * cos((goc*3.14159265) / 180) + yo;
			//-------------------
			goc -= 5.0;
			lineDDA(xo, yo, xd, yd);//tâm đầu dây
			cong(xd, yd + 25, 25);
			delay(300);

			if (ismouseclick(WM_LBUTTONDOWN))     //Ấn chuột phải xuống
			{
				r = 700;
				if (xd == 741 || xd == 739 || xd == 736 || xd == 734)
				{
					if (flag == 1)
					{
						r = 120; //Không hiện thực
						flag = 0;
						diem += 30;
						tinhTienVang(h);
						drawNV(a);
						if (flag1 == 1)
							testVang1(j);
						if (flag2 == 1)
							testVang2(k);
						if (flag3 == 1)
							testVang3(l);
						if (flag4 == 1)
							testVang4(s);
						drawRanhGioi();
						outtextxy(20, 10, "Coin: +30");
					}
				}
				if (xd == 731)
				{
					if (flag1 == 1)
					{
						r = 225; //Không hiện thực
						flag1 = 0;
						diem += 50;
						tinhTienVang1(j);
						drawNV(a);
						if (flag == 1)
							testVang(h);
						if (flag2 == 1)
							testVang2(k);
						if (flag3 == 1)
							testVang3(l);
						if (flag4 == 1)
							testVang4(s);
						drawRanhGioi();
						outtextxy(20, 10, "Coin: +50");
					}
				}
				if (xd == 696)
				{
					if (flag2 == 1)
					{
						r = 300; //Không hiện thực
						flag2 = 0;
						diem += 40;
						tinhTienVang2(k);
						drawNV(a);
						if (flag == 1)
							testVang(h);
						if (flag1 == 1)
							testVang1(j);
						if (flag3 == 1)
							testVang3(l);
						if (flag4 == 1)
							testVang4(s);
						drawRanhGioi();
						outtextxy(20, 10, "Coin: +40");
					}
				}
				if (xd == 667 || xd == 663 || xd == 660)
				{
					if (flag3 == 1)
					{
						r = 705; //Không hiện thực
						flag3 = 0;
						diem += 100;
						tinhTienVang3(l);
						drawNV(a);
						if (flag == 1)
							testVang(h);
						if (flag1 == 1)
							testVang1(j);
						if (flag2 == 1)
							testVang2(k);
						if (flag4 == 1)
							testVang4(s);
						drawRanhGioi();
						outtextxy(20, 10, "Coin: +100");
					}
				}
				if (xd == 647 || xd == 646)
				{
					if (flag4 == 1)
					{
						r = 200; //Không hiện thực
						flag4 = 0;
						diem += 30;
						tinhTienVang4(s);
						drawNV(a);
						if (flag == 1)
							testVang(h);
						if (flag1 == 1)
							testVang1(j);
						if (flag2 == 1)
							testVang2(k);
						if (flag3 == 1)
							testVang3(l);
						drawRanhGioi();
						outtextxy(20, 10, "Coin: +30");
					}
				}
				lineDDA(xo, yo, xd, yd);
				cong(xd, yd + 25, 25);
				clearmouseclick(WM_LBUTTONDOWN);
			}
			if (ismouseclick(WM_LBUTTONUP))     //Thả chuột
			{
				color = WHITE;
				r = 50;
				lineDDA(xo, yo, xd, yd);
				cong(xd, yd + 25, 25);
				clearmouseclick(WM_LBUTTONUP);
			}
			if (diem >= 150)
			{
				taget = 0;
				cleardevice();
				datMucTieu();
			}
			page = 1 - page;
			if (over == 0)
			{
				cleardevice();
				drawGameOver();
			}
		}
	}

}


int main()
{
	int gd = DETECT, gm;
	//initgraph(&gd, &gm, "c:\\tc\\bgi");
	initwindow(1280, 700);

	//int p = ((2+3)<<3); // <<3: *2^3
	//cout << p;

	manHinhBatDau();
	//drawGameOver();
	getch();
	closegraph();
	return 0;
}