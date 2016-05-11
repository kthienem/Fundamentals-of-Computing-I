#include <stdio.h>
#include <math.h>
#include <time.h>
#include "gfx3.h"
#include <string.h>

#define pi 3.14156

void startGame(int, int);
void drawAsteroid(int,int,int,int,int,int);
void drawRocket(float,float,float,int);
void wormhole(float *,float *,int,int);
void accelerate();
void turn();
void brake();
void scoreboard(int);
char *num2str(int);
void fire(float, float, float, int);

int main()
{
	// Print instructions for user
	printf("Asteroid!\nTry to collect as many colored circles as you can.\nThe game is simple. Use the arrow keys to navigate your rocket.\nUp accelerates\nDown brakes immediately\nLeft and Right turn your rocket.\n\nHave fun!!\n");	

	// Define variables
	int xSize=800, ySize=600;
	char c;
	int stillgoing=1;
	float xc=xSize/2, yc=ySize/2, *pxc=&xc, *pyc=&yc;
	float dr=.1;			// rotation increment
	int sign = 1;			// rotation sign
	int r = 15;			// box radius
	int i;				// box counter
	int j;				// triangle counter
	double rotatea=0;		// rotation angle of rocket
	float dx=0, dy=0;		// chane in position of rocket
	float dt=0;			// change in time for acceleration
	float accel=.07;		// acceleration of rocket
	srand(time(NULL));
	int rCir=0;			// radius of circle
	int xCir=xc,yCir=yc;		// position of circle's center
	int rC=255,gC=255,bC=255;	// circle color
	int cirCount=-1;		// number of circles collected(starts at -1 because initial circle is created at center, then random placement begins. Fisrt circle placed at center does not count towards total.
	int isaccel=0;
	double rotatet=rotatea;
	double yRotate=0, xRotate=0;
	float xB, yB;			//  position of fired shot

	gfx_open(xSize,ySize,"Rocketship!");
	
	startGame(xSize, ySize);
	while(stillgoing==1)
	{
		gfx_clear();
		drawAsteroid(xCir,yCir,rCir,rC,gC,bC);	
		drawRocket(xc,yc,rotatet,r);	// uses rotatet, because this will draw the rocket as turning when the left/right arrows are pressed

		scoreboard(cirCount);
		gfx_flush();
		usleep(2000);

		if(gfx_event_waiting()){
			c=gfx_wait();
			switch(c){
				case 'R':	// Accelerate
					dt+=.01;
					dx+=accel*dt;	// increases speed dx by increasing the time and adding to dx
					if(dx>.8) dx=.8;	// this caps dx and dy at 1. Thus the maximum speed is dx=dy=1
					dy=dx;
					isaccel=1;	// the rocket is currently accelerating
					break;
				case 'Q':	// Turn left
					rotatet-=dr;	// decreases angle of rotation
					break;
				case 'S':	// Turn right
//printf("ROTATET: %lf\n",rotatet);
					rotatet+=dr;	// increases angle of rotation
//printf("ROTATET: %lf\n",rotatet);
					break;
				case 'T':	// Brake
					dx=0;		// sets speed dx and dy to 0
					dy=0;
					rotatea=rotatet;
					yRotate=0;
					xRotate=0;
					break;
				case ' ':
					
					fire(rotatet, xc, yc, r);
					break;
				case 'q':	// Quit
					stillgoing=0;
					printf("\nYou collected %i circles!\n",cirCount);
					break;
				default:
					break;
			}
		}
		if(isaccel==1){
		printf("ROTATEA: %lf\n",rotatea);
			if(sin(rotatea)<sin(rotatet)){
				yRotate-=fabs(sin(rotatea+.1));
		printf("check1\n");
			}else if(sin(rotatea)>sin(rotatet)){
				yRotate+=fabs(sin(rotatea-.1));
		printf("check2\n");
			}//else direction of acceleration is equal to direction rocket is facing
			if(cos(rotatea)>cos(rotatet)){
				xRotate-=fabs(cos(rotatea+.1));
		printf("check3\n");
			}else if(cos(rotatea)<cos(rotatet)){
				xRotate+=fabs(cos(rotatea-.1));
		printf("check4\n");
			}
			if(xRotate!=0) rotatea=atan(yRotate/xRotate);
		printf("yRotate: %lf\nxRotate: %lf\nrotatea: %lf\nrotatet: %lf\n",yRotate,xRotate,rotatea,rotatet);
		}

		xc+=dx*cos(rotatea);	// implements x and y speed(dx and dy) by changing position(xc,yc) of rocket at varying rate
		yc+=dy*sin(rotatea);	// why i use rotatea, not rotatet: the rocket will only update the angle of movement, if the rocket is accelerating. This way, you can turn the rocket while it is moving in another direction
		isaccel=0;
		// Transports rocket from one side of screen to other
		wormhole(pxc,pyc,xSize,ySize);
		// Creates new circle if rocket comes too close
		if(sqrt(pow((xc-xCir),2)+pow((yc-yCir),2))<1.6*r+rCir){
			cirCount++;
			rCir=10+rand()%20;
			do{
				xCir=rand()%xSize;
				yCir=rand()%ySize;
				rC=100+rand()%155;
				gC=100+rand()%155;
				bC=100+rand()%155;
			}while(sqrt(pow((xc-xCir),2)+pow((yc-yCir),2))<50);
		}
	}
}

void startGame(int xSize, int ySize)
{
	char c;
	char *intro = "Welcome to Asteroid! Press 'p' to play!";

	gfx_text((xSize/2)-(strlen(intro)/2)*5, ySize/2, intro);
	c = gfx_wait();
	while(c != 'p'){
		c = gfx_wait();
	}
}

void drawRocket(float xc, float yc, float rotatet, int r)
{
	int i, j;
	// Draw Box
	gfx_color(255,255,255);
	for(i=1;i<=7;i+=2){
		gfx_line(xc+r*cos(rotatet+(i*pi)/4), yc+r*sin(rotatet+(i*pi)/4), xc+r*cos(rotatet+((i+2)*pi)/4), yc+r*sin(rotatet+((i+2)*pi)/4));
	}
	// Draw Triangle
	for(j=-1;j<=1;j+=2){
		gfx_line(xc+r*cos(rotatet+(j*pi)/4), yc+r*sin(rotatet+(j*pi)/4), xc+1.6*r*cos(rotatet), yc+1.6*r*sin(rotatet));
	}
}

void wormhole(float *pxc, float *pyc, int xSize, int ySize)
{
		// Transports rocket from one side of screen to other
		if(*pxc>xSize) *pxc=0;
		if(*pxc<0) *pxc=xSize;
		if(*pyc>ySize) *pyc=0;
		if(*pyc<0) *pyc=ySize;
}

void drawAsteroid(int xCir, int yCir, int rCir, int rC, int gC, int bC)
{
	gfx_color(rC,gC,bC);
	gfx_circle(xCir,yCir,rCir);
}

void scoreboard(int cirCount)
{
	gfx_text(20, 20, num2str(cirCount));
}

char *num2str(int n)
{
	static char a[4];
	sprintf(a, "%d", n);
	return (char *)a;
}

void fire(float rotatet, float xc, float xy, int r)
{
	gfx_point
}
