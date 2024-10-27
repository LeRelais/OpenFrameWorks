#include "ofMain.h"
#include "Player.h"

void Player::setup() {
	py = 1;             //플레이어의 초기 y 좌표
	px = 1;             //플레이어의 초기 x 좌표 
	lives = 1;          //플레이어의 초기 hp
	max_capacity = 1;   //한번에 발사 가능한 총알 개수
	speed = 0.5;        //플레이어의 속도
	avoidwall = false;  //플레이어가 벽을 뚫을 수 있는지 참거짓값
	avoidcount = 0;     //플레이어가 벽을 지나갈 수 있는 초기값
}

void Player::update(char **stage, int height, int width) {         //플레이어의 위치를 입력에 따라 갱신시키는 함수
	if (up) {                                                     //w나 방향키 위가 눌려졌다면
		float nx = ((px * 2) / 2);
		float ny = ((py * 2 - 1) / 2);
		int x = (int)nx;
		int y = (int)ny;										  //합법적인 이동인지 확인한 후 동작을 수행한다
		if ((stage[y][x] == '-' || stage[y][x] == '+' || stage[y][x] == '|') && avoidwall == true && (y > 1 && x > 1) && (y <= height - 2 && x <= width - 2)) {
			if (stage[y - 1][x] == '+') {                         //만약 player가 벽을 넘어갈 수 있다면
				py = py;										  //적법한 이동인지 확인을 한 후 이동을 진행시킨다
			}
			else if (stage[y - 1][x] == '-') {
				py = py;
			}
			else if (stage[y - 1][x] == '|') {					 //적법하지 않다면 좌표값을 갱신하지 않고, 
				py = py;
			}
			else {
				py = y - 1;                                      //이동할 수 있다면 벽을 넘어간 후,
				avoidcount--;                                    //벽을 넘을 수 있는 횟수를 차감해 
				if(avoidcount == 0)                              //횟수가 0이 된다면 avoidwall을 false로 만든다
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
	if (down) {													 //s나 방향키 아래가 눌려졌다면
		float nx = ((px * 2) / 2);
		float ny = (((py + 0.5) * 2 + 1) / 2);
		int x = (int)nx;
		int y = (int)ny;										 //합법적인 이동인지 확인한 후 동작을 수행한다
		if ((stage[y][x] == '-' || stage[y][x] == '+' || stage[y][x] == '|') && avoidwall == true && (y > 1 && x > 1) && (y <= height - 2 && x <= width - 2)) {
			if (stage[y + 1][x] == '+') {					     //만약 player가 벽을 넘어갈 수 있다면
				py = py;									     //적법한 이동인지 확인을 한 후 이동을 진행시킨다
			}
			else if (stage[y + 1][x] == '-') {
				py = py;
			}
			else if (stage[y + 1][x] == '|') {				    //적법하지 않다면 좌표값을 갱신하지 않고, 
				py = py;
			}
			else {
				py = y + 1;									    //이동할 수 있다면 벽을 넘어간 후,
				avoidcount--;								    //벽을 넘을 수 있는 횟수를 차감해 
				if (avoidcount == 0)						    //횟수가 0이 된다면 avoidwall을 false로 만든다
					avoidwall = false;
			}
		}
		else if (stage[y][x] == '-' || stage[y][x] == '+' || stage[y][x] == '|' || abs(x-px) == 0.5) {
			py = py;
		}
		else
			py += speed;
	}														   //a나 방향키 왼쪽이 눌려졌다면
	if (left) {
		float nx = ((px * 2 - 1) / 2);
		float ny = ((py * 2) / 2);
		int x = (int)nx;									   //합법적인 이동인지 확인한 후 동작을 수행한다
		int y = (int)ny;
		if ((stage[y][x] == '-' || stage[y][x] == '+' || stage[y][x] == '|') && avoidwall == true && (y > 1 && x > 1) && (y <= height - 2 && x <= width - 2)) {
			if (stage[y][x - 1] == '-')						    //만약 player가 벽을 넘어갈 수 있다면
				px = px;									    //적법한 이동인지 확인을 한 후 이동을 진행시킨다
			else if (stage[y][x - 1] == '+')
				px = px;
			else if (stage[y][x - 1] == '|')
				px = px;
			else {											   //적법하지 않다면 좌표값을 갱신하지 않고, 
				px = x - 1;
				avoidcount--;
				if (avoidcount == 0)
					avoidwall = false;						   //이동할 수 있다면 벽을 넘어간 후,
			}												   //벽을 넘을 수 있는 횟수를 차감해 
		}													   //횟수가 0이 된다면 avoidwall을 false로 만든다
		else if (stage[y][x] == '|' || stage[y][x] == '+' || stage[y][x] == '-' || abs(y-py) == 0.5) {
			left = false;
			px = px;
		}
		else
			px -= speed;
	}															  //d나 방향키 오른쪽이 눌려졌다면
	if (right) {
		float nx = (((px + speed) * 2 + 1) / 2);
		float ny = ((py * 2) / 2);
		int x = (int)nx;										  //합법적인 이동인지 확인한 후 동작을 수행한다
		int y = (int)ny;
		if ((stage[y][x] == '-' || stage[y][x] == '+' || stage[y][x] == '|')  && avoidwall == true && (y > 1 && x > 1) && (y <= height - 2 && x <= width - 2)) {
			if (stage[y][x + 1] == '+')							    //만약 player가 벽을 넘어갈 수 있다면
				px = px;										    //적법한 이동인지 확인을 한 후 이동을 진행시킨다
			else if (stage[y][x + 1] == '-')
				px = px;
			else if (stage[y][x + 1] == '|')
				px = px;
			else {												   //적법하지 않다면 좌표값을 갱신하지 않고, 
				px = x + 1;
				avoidcount--;
				if (avoidcount == 0)
					avoidwall = false;							   //이동할 수 있다면 벽을 넘어간 후,
			}													   //벽을 넘을 수 있는 횟수를 차감해 
		}														   //횟수가 0이 된다면 avoidwall을 false로 만든다
		else if ((stage[y][x] == '|' || stage[y][x] == '+' || stage[y][x] == '-') || abs(y-py) == 0.5) {
			px = px;
		}
		else
			px += speed;
	}
}

void Player::draw() {
	if (avoidwall == true)          //벽을 넘을 수 있다면 초록색 
		ofSetColor(0, 255, 0);
	else
		ofSetColor(255, 0, 0);      //아니라면 빨간색
	pimg.draw(px*amplifier, py*amplifier, amplifier, amplifier);  //규격에 맞춰 화면 상에 그린다
}

