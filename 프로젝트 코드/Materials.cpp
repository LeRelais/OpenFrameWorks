#include "Materials.h"

void Item::setup(int height, int width) {
	iy = rand() % ((height-3)/2)*2+1;      //미로 내부의 벽이 아닌 곳의 y좌표를 랜덤으로 설정한다
	ix = rand() % ((width-3)/2)*2+1;       //미로 내부의 벽이 아닌 곳의 x좌표를 랜덤으로 설정한다     
	type = rand() % 5 + 1;           //아이템의 종류를 랜덤으로 설정한다.
	iimg.load("item.png");
}

void Item::draw(int size) {              //아이템의 화면 상에 출력한다
	ofSetColor(255, 255, 255);
	iimg.draw(ix * size, iy * size, size, size);
}