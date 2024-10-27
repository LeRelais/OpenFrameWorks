#include "ofMain.h"

class Bullet {
public:
	float bx, by;   // �Ѿ��� ��ǥ�� �����ϱ� ���� float�� ����
	float ori_bx, ori_by;  // �Ѿ��� �̵��� �Ÿ��� max_dist�� �Ѿ����� �˻��ϱ� ���� ���� float�� ����
	int dir;  // �Ѿ��� �̵� ������ ����� int�� ����
	float speed = 0.5;  // �Ѿ��� �ʱ� �ӵ��� �����ϴ� float�� ���� 
	float max_dist;  // �Ѿ��� �̵��� �� �ִ� �ִ� �Ÿ��� �����ϴ� float�� ����
	int b_amp;	    //maze�� ũ�⿡ ���� �����Ǵ� int�� ����
	ofImage bimg;  //�Ѿ��� �̹����� �����ϱ� ���� ����
	
	void setup(float x, float y, int d, int amplifier);
	void update();
	void draw();
};

