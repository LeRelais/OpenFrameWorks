#include "Enemy.h"
//randomly set the position of enemies as the game start
void Enemy::setup(int height, int width) {
	ey = rand() % ((height - 4)/2)*2 + 1;    //�̷γ��ο� �����ϴ� y��ǥ���� ���´�.
	ex = rand() % ((width - 4)/2)*2 + 1;     //�̷γ��ο� �����ϴ� x��ǥ���� ���´�.
	speed = 0.5;                       //������ �ʱ� �ӵ�
	dir = -1;                          //�̷� ������ ���� �ƴҽ�, �ʱ� �̵�����
}

//function that updates enemy's position information 
//type 1 enemy - inside the maze, move along the maze
//type 2 enemy - move horizontally, ignores walls
//type 3 enemy - move vertically, ignore walls
//type 4 enemy - move circurlarly, ignores walls
void Enemy::update(char **stage, int height, int width) {              //������ �������� �����Ѵ�
	if (type == 1) {                                                 //�̷� ������ ���̶��
		int x = (int)ex;                                           
		int y = (int)ey;                                             //���� ���Ⱚ�� ���� �ٸ� ������ �����Ѵ�
		if (dir == 0) {                                             //���� �����̶�� ���� ���縦 �˻��ϰ�
			float nx = ((ex * 2) / 2);                              //�������� ���� �� ���������� �����δ�
			float ny = ((ey * 2 - 1) / 2);
			int x = (int)nx;
			int y = (int)ny;
			if (stage[y][x] == '-' || stage[y][x] == '+' || stage[y][x] == '|' || abs(x - ex) == 0.5) {
				ey = ey;
			}
			else
				ey -= speed;
		}
		if (dir == 1) {
			float nx = ((ex * 2) / 2);
			float ny = (((ey+0.5) * 2 + 1) / 2);                       //�Ʒ� �����̶�� ���� ���縦 �˻��ϰ�
			int x = (int)nx;										   //�������� ���� �� �Ʒ��������� �����δ�
			int y = (int)ny;
			if (stage[y][x] == '-' || stage[y][x] == '+' || stage[y][x] == '|' || abs(x - ex) == 0.5) {
				ey = ey;
			}
			else
				ey += speed;
		}
		if (dir == 2) {                                            //���� �����̶�� ���� ���縦 �˻��ϰ�
			float nx = ((ex * 2 - 1) / 2);						   //�������� ���� �� �޹������� �����δ�
			float ny = ((ey * 2) / 2);
			int x = (int)nx;
			int y = (int)ny;
			if (stage[y][x] == '|' || stage[y][x] == '+' || stage[y][x] == '-' || abs(y - ey) == 0.5) {
				ex = ex;
			}
			else
				ex -= speed;
		}
		if (dir == 3) {                                            //������ �����̶�� ���� ���縦 �˻��ϰ�
			float nx = (((ex + 0.5) * 2 + 1) / 2);				   //�������� ���� �� �����ʹ������� �����δ�
			float ny = ((ey * 2) / 2);
			int x = (int)nx;
			int y = (int)ny;
			if (stage[y][x] == '|' || stage[y][x] == '+' || stage[y][x] == '-' || abs(y - ey) == 0.5) {
				ex = ex;
			}
			else
				ex += speed;
		}
	}
	if (type == 2) {                                     //�̷� �ܺ��� �� ��, ���ι������� �����̴� ���̶��
		ex += -1*speed * dir;                            //�ܺκ��� ������ ������ �̵��� �����ϴ�
		if (ex < 1)                                      //���� ��Ҵٸ� dir�� -1�� ���� �ݴ�������� ��ȯ�Ѵ� 
			dir *= -1;
		if (ex > width - 2)
			dir *= -1;
		
	}
	if (type == 3) {                                   //�̷� �ܺ��� �� ��, ���ι������� �����̴� ���̶��
		ey -= speed * dir;							   //�ܺκ��� ������ ������ �̵��� �����ϴ�
		if (ey < 1)									   //���� ��Ҵٸ� dir�� -1�� ���� �ݴ�������� ��ȯ�Ѵ� 
			dir *= -1;
		if (ey > (height-2))
			dir *= -1;
	}
	if (type == 4) {                                 //�̷� �ܺ��� �� ��, ����� �ϴ�  ���̶��
		ey += cos(ofGetElapsedTimef());				 //�ܺκ��� ������ ������ �̵��� �����ϴ�
		ex += sin(ofGetElapsedTimef());				 //���� ��Ҵٸ� ���� Ÿ�� �̵��Ѵ�.  
	}
}

//function that draw enemy's current position
void Enemy::draw() {
	ofSetColor(124, 23, 123);
	eimg.draw(ex*amplifier, ey*amplifier, amplifier, amplifier);     //������ �̹����� �԰ݿ� ���� ȭ�� �� �׸���
}
