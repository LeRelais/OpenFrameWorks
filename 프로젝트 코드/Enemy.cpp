#include "Enemy.h"
//randomly set the position of enemies as the game start
void Enemy::setup(int height, int width) {
	ey = rand() % ((height - 4)/2)*2 + 1;    //미로내부에 존재하는 y좌표값을 얻어온다.
	ex = rand() % ((width - 4)/2)*2 + 1;     //미로내부에 존재하는 x좌표값을 얻어온다.
	speed = 0.5;                       //적들의 초기 속도
	dir = -1;                          //미로 내부의 적이 아닐시, 초기 이동방향
}

//function that updates enemy's position information 
//type 1 enemy - inside the maze, move along the maze
//type 2 enemy - move horizontally, ignores walls
//type 3 enemy - move vertically, ignore walls
//type 4 enemy - move circurlarly, ignores walls
void Enemy::update(char **stage, int height, int width) {              //적들의 움직임을 갱신한다
	if (type == 1) {                                                 //미로 내부의 적이라면
		int x = (int)ex;                                           
		int y = (int)ey;                                             //얻어온 방향값에 따라 다른 동작을 수행한다
		if (dir == 0) {                                             //위쪽 방향이라면 벽의 존재를 검사하고
			float nx = ((ex * 2) / 2);                              //존재하지 않을 시 위방향으로 움직인다
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
			float ny = (((ey+0.5) * 2 + 1) / 2);                       //아래 방향이라면 벽의 존재를 검사하고
			int x = (int)nx;										   //존재하지 않을 시 아래방향으로 움직인다
			int y = (int)ny;
			if (stage[y][x] == '-' || stage[y][x] == '+' || stage[y][x] == '|' || abs(x - ex) == 0.5) {
				ey = ey;
			}
			else
				ey += speed;
		}
		if (dir == 2) {                                            //왼쪽 방향이라면 벽의 존재를 검사하고
			float nx = ((ex * 2 - 1) / 2);						   //존재하지 않을 시 왼방향으로 움직인다
			float ny = ((ey * 2) / 2);
			int x = (int)nx;
			int y = (int)ny;
			if (stage[y][x] == '|' || stage[y][x] == '+' || stage[y][x] == '-' || abs(y - ey) == 0.5) {
				ex = ex;
			}
			else
				ex -= speed;
		}
		if (dir == 3) {                                            //오른쪽 방향이라면 벽의 존재를 검사하고
			float nx = (((ex + 0.5) * 2 + 1) / 2);				   //존재하지 않을 시 오른쪽방향으로 움직인다
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
	if (type == 2) {                                     //미로 외부의 적 중, 가로방향으로 움직이는 적이라면
		ex += -1*speed * dir;                            //외부벽에 도달할 때까지 이동을 진행하다
		if (ex < 1)                                      //벽과 닿았다면 dir에 -1을 곱해 반대방향으로 전환한다 
			dir *= -1;
		if (ex > width - 2)
			dir *= -1;
		
	}
	if (type == 3) {                                   //미로 외부의 적 중, 세로방향으로 움직이는 적이라면
		ey -= speed * dir;							   //외부벽에 도달할 때까지 이동을 진행하다
		if (ey < 1)									   //벽과 닿았다면 dir에 -1을 곱해 반대방향으로 전환한다 
			dir *= -1;
		if (ey > (height-2))
			dir *= -1;
	}
	if (type == 4) {                                 //미로 외부의 적 중, 원운동을 하는  적이라면
		ey += cos(ofGetElapsedTimef());				 //외부벽에 도달할 때까지 이동을 진행하다
		ex += sin(ofGetElapsedTimef());				 //벽과 닿았다면 벽을 타고 이동한다.  
	}
}

//function that draw enemy's current position
void Enemy::draw() {
	ofSetColor(124, 23, 123);
	eimg.draw(ex*amplifier, ey*amplifier, amplifier, amplifier);     //지정된 이미지와 규격에 맞춰 화면 상에 그린다
}
