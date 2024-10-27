#include "ofMain.h"
#include "Player.h"

void Player::setup() {
	py = 1;             //�÷��̾��� �ʱ� y ��ǥ
	px = 1;             //�÷��̾��� �ʱ� x ��ǥ 
	lives = 1;          //�÷��̾��� �ʱ� hp
	max_capacity = 1;   //�ѹ��� �߻� ������ �Ѿ� ����
	speed = 0.5;        //�÷��̾��� �ӵ�
	avoidwall = false;  //�÷��̾ ���� ���� �� �ִ��� ��������
	avoidcount = 0;     //�÷��̾ ���� ������ �� �ִ� �ʱⰪ
}

void Player::update(char **stage, int height, int width) {         //�÷��̾��� ��ġ�� �Է¿� ���� ���Ž�Ű�� �Լ�
	if (up) {                                                     //w�� ����Ű ���� �������ٸ�
		float nx = ((px * 2) / 2);
		float ny = ((py * 2 - 1) / 2);
		int x = (int)nx;
		int y = (int)ny;										  //�չ����� �̵����� Ȯ���� �� ������ �����Ѵ�
		if ((stage[y][x] == '-' || stage[y][x] == '+' || stage[y][x] == '|') && avoidwall == true && (y > 1 && x > 1) && (y <= height - 2 && x <= width - 2)) {
			if (stage[y - 1][x] == '+') {                         //���� player�� ���� �Ѿ �� �ִٸ�
				py = py;										  //������ �̵����� Ȯ���� �� �� �̵��� �����Ų��
			}
			else if (stage[y - 1][x] == '-') {
				py = py;
			}
			else if (stage[y - 1][x] == '|') {					 //�������� �ʴٸ� ��ǥ���� �������� �ʰ�, 
				py = py;
			}
			else {
				py = y - 1;                                      //�̵��� �� �ִٸ� ���� �Ѿ ��,
				avoidcount--;                                    //���� ���� �� �ִ� Ƚ���� ������ 
				if(avoidcount == 0)                              //Ƚ���� 0�� �ȴٸ� avoidwall�� false�� �����
					avoidwall = false;
			}
		}
		else if (stage[y][x] == '-' || stage[y][x] == '+' || stage[y][x] == '|' || abs(x - px) == 0.5) {
			up = false;
			py = py;
		}
		else
			py -= speed;
	}
	if (down) {													 //s�� ����Ű �Ʒ��� �������ٸ�
		float nx = ((px * 2) / 2);
		float ny = (((py + 0.5) * 2 + 1) / 2);
		int x = (int)nx;
		int y = (int)ny;										 //�չ����� �̵����� Ȯ���� �� ������ �����Ѵ�
		if ((stage[y][x] == '-' || stage[y][x] == '+' || stage[y][x] == '|') && avoidwall == true && (y > 1 && x > 1) && (y <= height - 2 && x <= width - 2)) {
			if (stage[y + 1][x] == '+') {					     //���� player�� ���� �Ѿ �� �ִٸ�
				py = py;									     //������ �̵����� Ȯ���� �� �� �̵��� �����Ų��
			}
			else if (stage[y + 1][x] == '-') {
				py = py;
			}
			else if (stage[y + 1][x] == '|') {				    //�������� �ʴٸ� ��ǥ���� �������� �ʰ�, 
				py = py;
			}
			else {
				py = y + 1;									    //�̵��� �� �ִٸ� ���� �Ѿ ��,
				avoidcount--;								    //���� ���� �� �ִ� Ƚ���� ������ 
				if (avoidcount == 0)						    //Ƚ���� 0�� �ȴٸ� avoidwall�� false�� �����
					avoidwall = false;
			}
		}
		else if (stage[y][x] == '-' || stage[y][x] == '+' || stage[y][x] == '|' || abs(x-px) == 0.5) {
			py = py;
		}
		else
			py += speed;
	}														   //a�� ����Ű ������ �������ٸ�
	if (left) {
		float nx = ((px * 2 - 1) / 2);
		float ny = ((py * 2) / 2);
		int x = (int)nx;									   //�չ����� �̵����� Ȯ���� �� ������ �����Ѵ�
		int y = (int)ny;
		if ((stage[y][x] == '-' || stage[y][x] == '+' || stage[y][x] == '|') && avoidwall == true && (y > 1 && x > 1) && (y <= height - 2 && x <= width - 2)) {
			if (stage[y][x - 1] == '-')						    //���� player�� ���� �Ѿ �� �ִٸ�
				px = px;									    //������ �̵����� Ȯ���� �� �� �̵��� �����Ų��
			else if (stage[y][x - 1] == '+')
				px = px;
			else if (stage[y][x - 1] == '|')
				px = px;
			else {											   //�������� �ʴٸ� ��ǥ���� �������� �ʰ�, 
				px = x - 1;
				avoidcount--;
				if (avoidcount == 0)
					avoidwall = false;						   //�̵��� �� �ִٸ� ���� �Ѿ ��,
			}												   //���� ���� �� �ִ� Ƚ���� ������ 
		}													   //Ƚ���� 0�� �ȴٸ� avoidwall�� false�� �����
		else if (stage[y][x] == '|' || stage[y][x] == '+' || stage[y][x] == '-' || abs(y-py) == 0.5) {
			left = false;
			px = px;
		}
		else
			px -= speed;
	}															  //d�� ����Ű �������� �������ٸ�
	if (right) {
		float nx = (((px + speed) * 2 + 1) / 2);
		float ny = ((py * 2) / 2);
		int x = (int)nx;										  //�չ����� �̵����� Ȯ���� �� ������ �����Ѵ�
		int y = (int)ny;
		if ((stage[y][x] == '-' || stage[y][x] == '+' || stage[y][x] == '|')  && avoidwall == true && (y > 1 && x > 1) && (y <= height - 2 && x <= width - 2)) {
			if (stage[y][x + 1] == '+')							    //���� player�� ���� �Ѿ �� �ִٸ�
				px = px;										    //������ �̵����� Ȯ���� �� �� �̵��� �����Ų��
			else if (stage[y][x + 1] == '-')
				px = px;
			else if (stage[y][x + 1] == '|')
				px = px;
			else {												   //�������� �ʴٸ� ��ǥ���� �������� �ʰ�, 
				px = x + 1;
				avoidcount--;
				if (avoidcount == 0)
					avoidwall = false;							   //�̵��� �� �ִٸ� ���� �Ѿ ��,
			}													   //���� ���� �� �ִ� Ƚ���� ������ 
		}														   //Ƚ���� 0�� �ȴٸ� avoidwall�� false�� �����
		else if ((stage[y][x] == '|' || stage[y][x] == '+' || stage[y][x] == '-') || abs(y-py) == 0.5) {
			px = px;
		}
		else
			px += speed;
	}
}

void Player::draw() {
	if (avoidwall == true)          //���� ���� �� �ִٸ� �ʷϻ� 
		ofSetColor(0, 255, 0);
	else
		ofSetColor(255, 0, 0);      //�ƴ϶�� ������
	pimg.draw(px*amplifier, py*amplifier, amplifier, amplifier);  //�԰ݿ� ���� ȭ�� �� �׸���
}

