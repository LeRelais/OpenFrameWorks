#pragma once
#define LEFT 'a'
#define RIGHT 'd'
#define UP 'w'
#define DOWN 's'

#include "ofMain.h"
#include "Player.h"
#include "Enemy.h"
#include "Controller.h"
#include "Materials.h"
#include "Bullet.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(float x, float y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
		
		int gamestate;	//프로젝트의 status를 지정하는 int형 변수
		int score;		//미로를 탐색하며 획득하는 점수를 저장하기 위한 int형 변수
		char **stage;   //maze generator로 만들어진 maze.txt파일을 불러와 내용을 담기 위해 사용되는 char형 이차원배열
		int height, width; //maze의 가로, 세로값
		Player player1;  //사용자가 움직이게 될 player의 정보가 담긴 player class
		int amplifier;  //maze의 크기에 따라 변경될 크기값
		float elapsetime;  //프로젝트가 동작된 시간을 저장하기 위한 float형 변수
		vector<Enemy> op;  //프로젝트에서 생성될 적들의 정보를 담기 위한 vector
		vector<Item> item;  //프로젝트에서 생성될 아이템들의 정보를 담기 위한 vector
		vector<Bullet> bullet;  //프로젝트에서 생성될 총알들의 정보를 담기 위한 vector
		ofTrueTypeFont score_f; //저장된 점수의 폰트를 지정하는 변수
		ofTrueTypeFont time;  //저장된 시간의 폰트를 지정하는 변수
		Controller control_e; //흐른 시간에 따라 게임에 영향을 주게 하는 Controller class 변수
		ofImage hp;           //hp를 표현할 그림을 위해 선언한 변수
		ofTrueTypeFont whp; //“HP : ”를 출력하기 위해 선언한 폰트 지정 변수
		ofTrueTypeFont avoidcount; //플레이어가 벽을 넘을 수 있는 횟수를 출력하기 위해 선언한 변수
		int loadflag;         //미로 파일이 제대로 로드 되었는지 확인하기 위해 선언한 변수

		void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult);
		void drawscore();
		void drawtime(float t);
		void limitRange(float *y, float *x, char **stage);
		void checkcollision();
		void checkitem();
		void checkbullet();
		void bulletcollision();
		void drawlife();
		bool isend();
		void drawavoidcount();
};
