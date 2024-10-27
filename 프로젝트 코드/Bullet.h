#include "ofMain.h"

class Bullet {
public:
	float bx, by;   // 총알의 좌표를 저장하기 위한 float형 변수
	float ori_bx, ori_by;  // 총알이 이동한 거리가 max_dist를 넘었는지 검사하기 위해 사용될 float형 변수
	int dir;  // 총알의 이동 방향이 저장될 int형 변수
	float speed = 0.5;  // 총알의 초기 속도를 저장하는 float형 변수 
	float max_dist;  // 총알이 이동할 수 있는 최대 거리를 저장하는 float형 변수
	int b_amp;	    //maze의 크기에 따라 변동되는 int형 변수
	ofImage bimg;  //총알의 이미지를 저장하기 위한 변수
	
	void setup(float x, float y, int d, int amplifier);
	void update();
	void draw();
};

