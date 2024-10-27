#include "Materials.h"

void Item::setup(int height, int width) {
	iy = rand() % ((height-3)/2)*2+1;      //�̷� ������ ���� �ƴ� ���� y��ǥ�� �������� �����Ѵ�
	ix = rand() % ((width-3)/2)*2+1;       //�̷� ������ ���� �ƴ� ���� x��ǥ�� �������� �����Ѵ�     
	type = rand() % 5 + 1;           //�������� ������ �������� �����Ѵ�.
	iimg.load("item.png");
}

void Item::draw(int size) {              //�������� ȭ�� �� ����Ѵ�
	ofSetColor(255, 255, 255);
	iimg.draw(ix * size, iy * size, size, size);
}