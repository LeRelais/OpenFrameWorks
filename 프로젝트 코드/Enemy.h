#include "ofMain.h"

class Enemy {
public:
	float ex, ey;  //���� ��ǥ�� �����ϱ� ���� float�� ����
	float x_dir[4] = { -0.5, 0.5, 0, 0 };  // �̷� ������ ���� ��, �̵� ���⿡ ���� ���� ������ float�� �迭
	float y_dir[4] = { 0, 0, -0.5, 0.5 };  // �̷� ������ ���� ��, �̵� ���⿡ ���� ���� ������ float�� �迭
	int dir;							   // �̵������� �����ϴ� int�� ����
	int type;							   // � ������ ������ �����ϱ� ���� int�� ����
	int amplifier;                         // maze�� ũ�⿡ ���� �����Ǵ� int�� ����                          
	float speed;                           // ������ �ӵ��� �����ϱ� ���� float�� ����
	ofImage eimg;						   // ������ �̹����� �����ϱ� ���� ofImage�� ����
	void setup(int height, int width);
	void draw();
	void update(char **stage, int height, int width);
};

