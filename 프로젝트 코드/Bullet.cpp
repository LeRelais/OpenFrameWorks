#include "Bullet.h"

void Bullet::setup(float x, float y, int d, int amplifier) {
	bx = ori_bx = x;                  //�Ѿ��� �߻�� x��ǥ�� �����Ѵ�
	by = ori_by = y;                  //�Ѿ��� �߻�� y��ǥ�� �����Ѵ�
	max_dist = 1;                     //�Ѿ��� �ִ� �̵��Ÿ��� �����Ѵ�
	dir = d;                          //�Ѿ��� �̵������� �����Ѵ�
	b_amp = amplifier;                //�Ѿ��� �԰��� �����Ѵ�
}

void Bullet::update() {           //�Ѿ��� �̵����⿡ ���� �̵��� �����ϰ� �Ѵ�
	if (dir == 0) {               //�� �����̶�� ����,
		by -= speed;             
	}
	if (dir == 1) {               //�Ʒ� �����̶�� ������
		by += speed;
	}
	if (dir == 2) {               //�����̶�� ��������
		bx -= speed;
	}
	if (dir == 3)                 //�������̶�� ����������
		bx += speed;              //��� x,y ��ǥ�� �����Ѵ�
}

void Bullet::draw() {
	ofSetColor(40, 40, 44);         //�Ѿ��� ���� �����Ѵ�
	bimg.draw(bx*b_amp, by*b_amp, b_amp, b_amp);     //����� �Ѿ��� �̹����� �԰ݿ� ���� ȭ�� �� �׸���
}