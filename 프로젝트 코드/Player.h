#pragma once

#include "ofMain.h"

class Player {
public:
	int lives;  //플레이어의 체력 개수를 저장하기 위한 int형 변수
	int amplifier;  //maze의 크기에 따라 변경될 크기값
	float py, px;  //플레이어의 좌표를 저장하기 위한 float형 변수
	int max_capacity;  //플레이어가 가질 수 있는 최대 탄약의 수
	float speed;  //플레이어가 움직이는 속도를 저장하는 float형 변수
	bool up, down, right, left;  //입력을 받았을 때 어느 방향으로 움직이는지 true false으로 반환하는 bool형 변수
	float bulletspeed;  //플레이어가 쏘는 총알의 속도를 저장하는 float형 변수
	bool avoidwall;  //플레이어가 벽을 넘을 수 있는지 없는지를 판단하는 bool형 변수
	ofImage pimg;  //플레이어의 이미지를 저장하기 위한 ofImage형 변수
	int avoidcount; //플레이어가 벽을 지나갈 수 있는 횟수
	
	void setup();
	void update(char **stage, int height, int width);
	void draw();
};

