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
		
		int gamestate;	//������Ʈ�� status�� �����ϴ� int�� ����
		int score;		//�̷θ� Ž���ϸ� ȹ���ϴ� ������ �����ϱ� ���� int�� ����
		char **stage;   //maze generator�� ������� maze.txt������ �ҷ��� ������ ��� ���� ���Ǵ� char�� �������迭
		int height, width; //maze�� ����, ���ΰ�
		Player player1;  //����ڰ� �����̰� �� player�� ������ ��� player class
		int amplifier;  //maze�� ũ�⿡ ���� ����� ũ�Ⱚ
		float elapsetime;  //������Ʈ�� ���۵� �ð��� �����ϱ� ���� float�� ����
		vector<Enemy> op;  //������Ʈ���� ������ ������ ������ ��� ���� vector
		vector<Item> item;  //������Ʈ���� ������ �����۵��� ������ ��� ���� vector
		vector<Bullet> bullet;  //������Ʈ���� ������ �Ѿ˵��� ������ ��� ���� vector
		ofTrueTypeFont score_f; //����� ������ ��Ʈ�� �����ϴ� ����
		ofTrueTypeFont time;  //����� �ð��� ��Ʈ�� �����ϴ� ����
		Controller control_e; //�帥 �ð��� ���� ���ӿ� ������ �ְ� �ϴ� Controller class ����
		ofImage hp;           //hp�� ǥ���� �׸��� ���� ������ ����
		ofTrueTypeFont whp; //��HP : ���� ����ϱ� ���� ������ ��Ʈ ���� ����
		ofTrueTypeFont avoidcount; //�÷��̾ ���� ���� �� �ִ� Ƚ���� ����ϱ� ���� ������ ����
		int loadflag;         //�̷� ������ ����� �ε� �Ǿ����� Ȯ���ϱ� ���� ������ ����

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
