#pragma once

#include "ofMain.h"

class Player {
public:
	int lives;  //�÷��̾��� ü�� ������ �����ϱ� ���� int�� ����
	int amplifier;  //maze�� ũ�⿡ ���� ����� ũ�Ⱚ
	float py, px;  //�÷��̾��� ��ǥ�� �����ϱ� ���� float�� ����
	int max_capacity;  //�÷��̾ ���� �� �ִ� �ִ� ź���� ��
	float speed;  //�÷��̾ �����̴� �ӵ��� �����ϴ� float�� ����
	bool up, down, right, left;  //�Է��� �޾��� �� ��� �������� �����̴��� true false���� ��ȯ�ϴ� bool�� ����
	float bulletspeed;  //�÷��̾ ��� �Ѿ��� �ӵ��� �����ϴ� float�� ����
	bool avoidwall;  //�÷��̾ ���� ���� �� �ִ��� �������� �Ǵ��ϴ� bool�� ����
	ofImage pimg;  //�÷��̾��� �̹����� �����ϱ� ���� ofImage�� ����
	int avoidcount; //�÷��̾ ���� ������ �� �ִ� Ƚ��
	
	void setup();
	void update(char **stage, int height, int width);
	void draw();
};

