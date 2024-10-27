#include "ofMain.h"

class Enemy {
public:
	float ex, ey;  //적의 좌표를 저장하기 위한 float형 변수
	float x_dir[4] = { -0.5, 0.5, 0, 0 };  // 미로 내부의 적일 때, 이동 방향에 대한 값을 저장한 float형 배열
	float y_dir[4] = { 0, 0, -0.5, 0.5 };  // 미로 내부의 적일 때, 이동 방향에 대한 값을 저장한 float형 배열
	int dir;							   // 이동방향을 저장하는 int형 변수
	int type;							   // 어떤 종류의 적인지 저장하기 위한 int형 변수
	int amplifier;                         // maze의 크기에 따라 변동되는 int형 변수                          
	float speed;                           // 적들의 속도를 저장하기 위한 float형 변수
	ofImage eimg;						   // 적들의 이미지를 저장하기 위한 ofImage형 변수
	void setup(int height, int width);
	void draw();
	void update(char **stage, int height, int width);
};

