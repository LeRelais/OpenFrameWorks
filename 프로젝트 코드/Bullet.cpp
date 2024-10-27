#include "Bullet.h"

void Bullet::setup(float x, float y, int d, int amplifier) {
	bx = ori_bx = x;                  //총알이 발사된 x좌표를 저장한다
	by = ori_by = y;                  //총알이 발사된 y좌표를 저장한다
	max_dist = 1;                     //총알의 최대 이동거리를 저장한다
	dir = d;                          //총알의 이동방향을 저장한다
	b_amp = amplifier;                //총알의 규격을 저장한다
}

void Bullet::update() {           //총알의 이동방향에 따라 이동을 진행하게 한다
	if (dir == 0) {               //위 방향이라면 위로,
		by -= speed;             
	}
	if (dir == 1) {               //아래 방향이라면 밑으로
		by += speed;
	}
	if (dir == 2) {               //왼쪽이라면 왼쪽으로
		bx -= speed;
	}
	if (dir == 3)                 //오른쪽이라면 오른쪽으로
		bx += speed;              //계속 x,y 좌표를 갱신한다
}

void Bullet::draw() {
	ofSetColor(40, 40, 44);         //총알의 색을 지정한다
	bimg.draw(bx*b_amp, by*b_amp, b_amp, b_amp);     //저장된 총알의 이미지를 규격에 맞춰 화면 상에 그린다
}