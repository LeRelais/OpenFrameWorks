#include "ofMain.h"

class Item {
public:
	int ix, iy;			//�������� ��ǥ�� �����ϱ� ���� float�� ����
	int type;			//�������� ������ �����ϱ� ���� int�� ����
	ofImage iimg;		//�������� �̹����� �ε��ϱ� ���� ofImage ����

	void setup(int height, int width);	//�������� ��ġ�� ���ϴ� �Լ�
	void draw(int size);			//�������� ȭ�� �� �׸��� �Լ�
};

