#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(15);                      //프로그램의 초당 프레임을 15로 제한한다
	ofSetWindowPosition(0, 100);             //프로그램의 윈도우 위치를 조정한다
	gamestate = 1;                          //게임의 상태
	score = 0;                               //점수 초기화
	player1.bulletspeed = 0.1;                //플레이어가 발사하는 총알의 속도 초기화
	score_f.load("verdana.ttf", 10, true, true);   //점수를 출력하기 위해 폰트를 불러온다
	time.load("verdana.ttf", 10, true, true);      //시간을 출력하기 위해 폰트를 불러온다
	player1.pimg.load("playerlife1down.png");    //플레이어 커서의 기본 이미지를 불러온다
	hp.load("hp.png");                           //hp의 이미지를 불러온다
	whp.load("verdana.ttf", 10, true, true);       //“HP : ”를 출력하기 위해 폰트를 불러온다
	avoidcount.load("verdana.ttf", 10, true, true);  //벽을 넘을 수 있는 횟수를 출력하기 위해 폰트를 불러온다
	loadflag = 0;                                   //미로의 로드 상태 초기화
}

//--------------------------------------------------------------
void ofApp::update(){
	if (gamestate == 1) {            //gamestate가 1이라면 아무 동작도 수행하지 않는다
		 
	}
	else if (gamestate == 2) {       //gamestate가 2라면 다음 동작을 수행한ㄷ
		elapsetime = ofGetElapsedTimef();   //프로젝트의 시작과 동시에 동작되고 있는 동안의 시간을 기록한다
		limitRange(&player1.py, &player1.px, stage);  //플레이어가 이동할 수 없는 곳에 위치한다면 갈 수 없도록 제한한다
		for (int i = 0; i < op.size(); i++) {        //vector에 저장된 적들의 정보에 대해
			if (op[i].type == 1) {                   //미로 내부의 적이라면
				for(int j = 0; j < 10; j++)
					op[i].dir = rand() % 4;          //이동 방향을 정해 update를 이용해 갱신시켜주고 다른 type의 적이라면
			}
			op[i].update(stage, height, width);      //Enemy.cpp에 저장된 동작에 따라 적의 움직임을 갱신시킨다
			limitRange(&op[i].ey, &op[i].ex, stage); //플레이어와 마찬가지로 이동할 수 없는 곳에 위치한다면 갈 수 없도록 제한한다
		}
		for (int i = 0; i < bullet.size(); i++)      //vector에 저장된 총알에 대해 움직임을 갱신한다.
			bullet[i].update();
		if (control_e.addenemy(elapsetime)) {        //Controller에 저장된 기능에 따라 적을 추가해야 한다면 적을 추가한다
			Enemy add;                 
			for (int i = 0; i < 3; i++) {
				add.setup(height, width);
				add.amplifier = player1.amplifier;
				add.type = rand() % 4 + 1;
				op.push_back(add);
			}
		}
		if (control_e.addspeed(elapsetime)) {       //Controller에 저장된 기능에 따라 적의 속도를 증가시켜야 한다면 적의 속도를 올려준다
			for (int i = 0; i < op.size(); i++) {
				if(op[i].type != 1 && op[i].speed < 2.5)   //단, 일정 수준 이상으로 올리지는 않는다
					op[i].speed += 0.5;
			}
		}
		if (control_e.additem(elapsetime)) {         //Controller에 저장된 기능에 따라 아이템을 생성해야 한다면 아이템을 생성한다
			Item i;
			i.setup(height, width);
			item.push_back(i);
		}
		if (isend()) {                                  //플레이어가 출구에 도달했다면 
			gamestate = 1;              //게임상태를 초기화하고
			player1.setup();             //플레이어의 위치를 초기화한다
		}
	}
}

void ofApp::limitRange(float *y, float *x, char **stage) {       //이동 후의 좌표가 maze의 외부벽이라면 움직임을 제한한다.
	if (*y < 1)
		*y = 1;
	if (*x < 1)
		*x = 1;
	if (*y > height-2)
		*y = height-2;
	if (*x >width-2)
		*x =width-2;

}
//--------------------------------------------------------------
void ofApp::draw(){
	if (gamestate == 1) {                  //gamestate가 1이라면 아무런 동작도 수행하지 않는다

	}
	else if (gamestate == 2) {            //정상적으로 작동중이라면 다음 동작을 수행한다
		for (int i = 0; i < height; i++) {       //**stage에 저장된 미로를 규격에 맞춰 그린다 
			for (int j = 0; j < width; j++) {
				if (stage[i][j] == '+' || stage[i][j] == '-' || stage[i][j] == '|') {
					ofSetColor(0, 0, 0);
					ofDrawRectangle(j * player1.amplifier, i * player1.amplifier, player1.amplifier, player1.amplifier);
				}
			}
			for (int j = 0; j < width; j++) {
				if (stage[i][j] == ' ') {
					ofSetColor(255, 255, 255);
					ofDrawRectangle(j * player1.amplifier, i * player1.amplifier, player1.amplifier, player1.amplifier);
					if (j == width - 2 && i == height - 2) {
						ofSetColor(0, 230, 0);
						ofDrawRectangle(j * player1.amplifier, i * player1.amplifier, player1.amplifier, player1.amplifier);
					}
				}
			}
		}
		player1.draw();        //저장된 플레이어의 위치에 플레이어를 그린다

		drawtime(elapsetime);  //저장된 시간을 출력하는 함수를 불러온다
		checkcollision();  // 플레이어와 적이 충돌한뒤 생기는 동작을 수행하는 함수를 불러온다
		checkitem();  // 플레이어가 아이템을 획득한 후 생기는 동작을 수행하는 함수를 불러온다
		bulletcollision();  // 총알이 적과 충돌한 뒤 생기는 동작을 수행하는 함수를 불러온다
		checkbullet();  //총알이 벽과 충돌한 뒤 생기는 동작을 수행하는 함수를 불러온다
		drawlife();
		drawavoidcount();
		for (int i = 0; i < bullet.size(); i++) {   //총알의 수에 맞춰 총알을 화면 상에 그린다
			if (bullet[i].dir == 0 || bullet[i].dir == 1)
				bullet[i].bimg.load("bulletupdown.png");
			else
				bullet[i].bimg.load("bulletrightleft.png");
			bullet[i].draw();
		}

		for (int i = 0; i < op.size(); i++) {   //적들의 수에 맞춰 적들의 화면 상에 그린다 
			if (op[i].type == 1) {              //vector에 저장된 적의 type에 맞춰 이미지를 로드하고
				op[i].eimg.load("enemy1.png");
			}
			if (op[i].type == 2) {
				op[i].eimg.load("enemy2.png");
			}
			if (op[i].type == 3) {
				op[i].eimg.load("enemy3.png");
			}
			if (op[i].type == 4) {
				op[i].eimg.load("enemy4.png");
			}
			op[i].draw();                          //그린다.
		}
		for (int i = 0; i < item.size(); i++) {    //아이템의 수에 맞춰 아이템들을 화면 상에 그린다
			item[i].draw(player1.amplifier);
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (gamestate == 1 && key == ' ' && loadflag == 1) {  //프로그램이 실행되고 아직 게임이 시작되지 않았다면 다음 동작을 수행한다
		ofResetElapsedTimeCounter();     //시간을 0으로 초기화한다
		ofSetWindowShape(width * player1.amplifier, (height+4) * player1.amplifier); //출력되는 윈도우의 크기를 규격에 맞춰 제한한다
		gamestate = 2;     //게임을 실행했다는 값으로 변환한다
		Enemy a;
		if (height*width > 400) {
			for (int i = 0; i < height*width / 50; i++) {
				a.setup(height, width);
				a.type = (rand() % 4) + 1;
				a.amplifier = player1.amplifier;
				op.push_back(a);
			}
		}
		control_e.setup();      //게임이 시작되었을 때, 흐른 시간에 따라 동작을 수행하는 Controller class 변수를 초기화한다.
	}

	if (gamestate == 2) {       //게임이 실행된 상태라면
		if (key == UP || key == OF_KEY_UP) {  //input으로 받는 값에 따라 플레이어의 커서를 움직인다.
			player1.up = true;                //방향키 위, w    위
			player1.update(stage, height, width);
			if (player1.lives <= 1)
				player1.pimg.load("playerlife1up.png");
			else
				player1.pimg.load("playerup.png");
		}
		if (key == DOWN||key == OF_KEY_DOWN) {        //방향키 아래, s 아래
			player1.down = true;
			player1.update(stage, height, width);
			if (player1.lives <= 1)
				player1.pimg.load("playerlife1down.png");
			else
				player1.pimg.load("playerdown.png");
		}
		if (key == LEFT || key == OF_KEY_LEFT) {       //방향키 왼쪽, a 왼쪽
			player1.left = true;
			player1.update(stage, height, width);
			if (player1.lives <= 1)
				player1.pimg.load("playerlife1left.png");
			else
				player1.pimg.load("playerleft.png");
		}
		if (key == RIGHT || key == OF_KEY_RIGHT) {     //방향키 오른쪽, d 오른쪽 
			player1.right = true;
			player1.update(stage, height, width);
			if (player1.lives <= 1)
				player1.pimg.load("playerlife1right.png");
			else
				player1.pimg.load("playerright.png");
		}
		
	}

	if (key == 'i' && gamestate == 2) {   //게임이 실행된 상태라면
		if (bullet.size() < player1.max_capacity) {   //input으로 받는 값에 따라 총알을 생성한다
			Bullet b;                                // i        윗방향
			float x = player1.px;
			float y = player1.py;
			b.setup(x, y, 0, player1.amplifier);
			bullet.push_back(b);
		}
		else
			return;
	}
	if (key == 'k' && gamestate == 2) {          // k      아래방향
		if (bullet.size() < player1.max_capacity) {  
			Bullet b;                                
			float x = player1.px;
			float y = player1.py;
			b.setup(x, y, 1, player1.amplifier);
			bullet.push_back(b);
		}
		else return;
	}
	if (key == 'j' && gamestate == 2) {             //j     왼쪽방향
		if (bullet.size() < player1.max_capacity) {
			Bullet b;
			float x = player1.px;
			float y = player1.py;
			b.setup(x, y, 2, player1.amplifier);
			bullet.push_back(b);
		}
		else
			return;
	} 
	if (key == 'l' && gamestate == 2) {            //ㅣ    오른쪽방향
		if (bullet.size() < player1.max_capacity) {
			Bullet b;
			float x = player1.px;
			float y = player1.py;
			b.setup(x, y, 3, player1.amplifier);
			bullet.push_back(b);
		}
		else
			return;
	}

	if (key == 'q' && gamestate == 1) {              //게임이 실행되지 않았고 q가 입력으로 주어졌다면
		for (int i = 0; i < height; i++) {
			delete[] stage[i];
		}
		delete[] stage;                             //프로그램에서 사용된 메모리의 할당을 해제하고
		while (!op.empty())
			op.pop_back();
		while (!item.empty())
			item.pop_back();
		while (!op.empty())
			op.pop_back();
		_Exit(0);                                 //종료한다
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == 'l' && gamestate == 1) {        //프로그램이 켜졌고 maze.txt가 load되지 않았을 경우
		ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a only txt");  //팝업 윈도우를 출력해

		if (openFileResult.bSuccess) {                                                 //.txt확장자의 파일을 선택하게 한다 
			ofLogVerbose("User selected a file");

			processOpenFileSelection(openFileResult);
			
		}
	}
	if (gamestate == 2) {           //방향키 혹은 wsad 키의 입력이 멈췄다면 
		if (key == UP || OF_KEY_UP) {            //플레이어 커서의 움직임을 정지시킨다.
			player1.up = false;
			if (player1.lives <= 1)            //플레이어의 이동 방향과 HP 보유 상태에 따라
				player1.pimg.load("playerlife1up.png");    //다른 모양의 커서를
			else                                              //로드한다.
				player1.pimg.load("playerup.png");
		}
		if (key == DOWN || OF_KEY_DOWN) {
			player1.down = false;
			if (player1.lives <= 1)
				player1.pimg.load("playerlife1down.png");
			else
				player1.pimg.load("playerdown.png");
		}
		if (key == LEFT || key == OF_KEY_LEFT) {
			player1.left = false;
			if (player1.lives <= 1)
				player1.pimg.load("playerlife1down.png");
			else
				player1.pimg.load("playerdown.png");
		}
		if (key == RIGHT || key == OF_KEY_RIGHT) {
			player1.right = false;
			if (player1.lives <= 1)
				player1.pimg.load("playerlife1down.png");
			else
				player1.pimg.load("playerdown.png");
		}
	}

	if (key == 'q' && gamestate == 2) {                       //게임이 실행되어 있을 때 q를 input으로 받는다면
		gamestate = 1;                                        //게임을 종료하고 저장된 적들의 정보, 아이템의 정보를 삭제하고
		player1.setup();                                      //플레이어의 위치를 초기값으로 설정한 뒤
		if (op.size() > 0) {
			while (!op.empty())
				op.pop_back();
		}
		if (item.size() > 0) {
			while (!item.empty())
				item.pop_back();
		}
		ofResetElapsedTimeCounter();                          //시간을 0으로 초기화한다
		score = 0;                                       //점수를 0으로 초기화한다
	}
}


//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(float x, float y, int button){
	
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}

void ofApp::processOpenFileSelection(ofFileDialogResult openFileResult) {

	string fileName = openFileResult.getName();              //팝업 윈도우에서 선택적으로 .txt파일을 선택했을 시
	ofFile file(fileName);                                   //그 이름을 가진 .txt파일을 열어 다음 동작을 수행한다

	if (!file.exists()) {                                    //bin/data 폴더 내부에 같은 이름의 파일이 없다면 
		cout << "Target file does not exists." << endl;      //에러 메세지를 출력하고 
	}
	else {
		cout << "We found the target file." << endl;         //아니라면 밑의 동작을 수행한다
	}

	ofBuffer buffer(file);                                   //파일을 열어

	int col = 0, row = 0;
	loadflag = 1;
	vector<string> f;
	for (auto line : buffer.getLines()) {   //vector에  .txt의 내용을 저장하고 
		f.push_back(line);
		row = line.size();              //그 때의 가로크기와
		col++;                        //세로크기를 파일의 끝까지 갱신하며 탐색한다
	}
	height = col;             //미로의 세로크기
	width = row;              //미로의 가로크기

	player1.setup();         //플레이어의 위치를 초기화시키고 maze의 크기에 따라 규격을 정한다. 
	if (height * width < 800) {    
		player1.amplifier = 33;
	}
	else if (height*width >= 800 && height * width < 1600) {
		player1.amplifier = 25;
	}
	else if (height*width >= 1600 && height * width < 2400) {
		player1.amplifier = 15;
	}
	else {
		player1.amplifier = 10;
	}

	stage = new char*[col];             //ofApp.h에 선언된 **stage를 동적으로 할당해주고
	for (int i = 0; i < col; i++)
		stage[i] = new char[row];

	for (int i = col - 1; i >= 0; i--) {      //vector에 담긴 maze의 정보를 **stage에 저장한다
		string a = f.back();
		f.pop_back();
		for (int j = 0; j < row; j++) {
			stage[i][j] = a[j];
		}
	}
}

void ofApp::checkcollision() {               //플레이어와 적의 충돌을 확인하는 함수
	if (gamestate == 2) {
		for (int i = 0; i < op.size(); i++) {     //플레이어와 적이 충돌했다면
			if (sqrt(((op[i].ex - player1.px)*(op[i].ex - player1.px)) + (op[i].ey - player1.py)*(op[i].ey - player1.py)) < 0.5) {
				player1.lives -= 1;               //플레이어의 체력을 1 깎고
			}
			if (player1.lives < 0) {             //깎였을 때의 체력이 0보다 작게 된다면 엔딩화면을 그리고
				gamestate = 1;                   //게임에서 사용된 값들을 초기화한다
				player1.setup();
				while (!op.empty())
					op.pop_back();
				while (!item.empty())
					item.pop_back();
				ofResetElapsedTimeCounter();
				score = 0;
			}
		}
	}
}

void ofApp::checkitem() {        //플레이어가 미로 상의 아이템을 먹었을 경우
	if (gamestate == 2) {        //종류에 따라 효과를 발동하게 한다
		for (int i = 0; i < item.size(); i++) {
			if (item[i].ix == (int)player1.px && item[i].iy == (int)player1.py) {
				if (item[i].type == 1) {
					player1.max_capacity++;           //1번 아이템. 플레이어의 탄약 수를 늘린다
				}
				if (item[i].type == 2) {              //2번 아이템, 적들의 속도를 낮춘다 
					for (int i = 0; i < op.size(); i++) {
						if (op[i].type != 1 && op[i].speed >= 0.5)
							op[i].speed -= 1;
						if (op[i].speed <= 0)
							op[i].speed = 0.5;
					}
				}
				if (item[i].type == 3) {              //3번 아이템, 플레이어가 벽을 뚫고 지나갈 수 있게 한다
					player1.avoidwall = true;
					player1.avoidcount++;
				}
				if (item[i].type == 4) {              //4번 아이템, 플레이어의 체력을 1 늘린다
					if (player1.lives <= 5)
						player1.lives += 1;
				}
				if (item[i].type == 5) {              //5번 아이템, 총알의 최대이동거리를 늘린다 
					for (int i = 0; i < bullet.size(); i++) {
						if(bullet[i].max_dist < 3.5)
							bullet[i].max_dist += 0.5;
					}
				}
				item.erase(item.begin() + i);
			}
		}
	}
}

void ofApp::checkbullet() {    //총알이 최대거리에 도달했는지 확인하는 함수이다
	for (int i = 0; i < bullet.size(); i++) {
		if (bullet[i].dir == 0 || bullet[i].dir == 1) {   //종류에 따라 최대 이동거리를 이동했다면
			if (abs(bullet[i].by - bullet[i].ori_by) > bullet[i].max_dist)
				bullet.erase(bullet.begin() + i);
		}
		else if (bullet[i].dir == 2 || bullet[i].dir == 3) {
			if(abs(bullet[i].bx - bullet[i].ori_bx) > bullet[i].max_dist)
				bullet.erase(bullet.begin()+i);           //vector 저장된 총알을 삭제한다
		}
	}
}

void ofApp::bulletcollision() {      //총알이 적을 관통하거나 벽에 닿았는지 확인하는 함수
	int x, y;
	for (int i = 0; i < bullet.size(); i++) {
		 x = (int)bullet[i].bx;
		 y = (int)bullet[i].by;
		if (stage[y][x] == '+' || stage[y][x] == '-' || stage[y][x] == '|') {
			bullet.erase(bullet.begin() + i);          //벽에 닿았다면 총알을 삭제한다 
		}
		else {
			for (int j = 0; j < op.size(); j++) {          //적을 관통했다면
				if (sqrt((bullet[i].bx - op[j].ex)*(bullet[i].bx - op[j].ex) + (bullet[i].by - op[j].ey)*(bullet[i].by - op[j].ey)) < 0.8) {
					Item x;                     //점수를 100 올리고 그 자리에 아이템을 생성한 뒤
					x.setup(height, width);
					x.ix = bullet[i].bx;
					x.iy = bullet[i].by;
					item.push_back(x);
					op.erase(op.begin() + j);       //적의 정보를 vector에서 삭제한다
				}
			}
		}
	}
}

void ofApp::drawlife() {    //플레이어의 HP를 출력한다
	for (int i = 1; i <= player1.lives; i++) {
		hp.draw((width/2+i+1) * player1.amplifier, (height) * player1.amplifier, player1.amplifier, player1.amplifier);
	}
	string s = "HP : ";
	whp.drawString(ofToString(s), (width/2-1)*player1.amplifier, (height + 1)*player1.amplifier);
}

void ofApp::drawtime(float t) {              //저장된 시간을 화면 상에 그린다
	ofSetColor(231, 23, 12);
	time.drawString(ofToString(elapsetime), (width/2+3)*player1.amplifier, (height + 2)*player1.amplifier);
	string s = "Time : ";
	time.drawString(ofToString(s), (width/2-1)*player1.amplifier, (height + 2)*player1.amplifier);
}

void ofApp::drawavoidcount() {     //벽을 넘을 수 있는 횟수를 출력한다
	string s = "# :";
	avoidcount.drawString(ofToString(s), (width/2-1)*player1.amplifier, (height + 3)*player1.amplifier);
	avoidcount.drawString(ofToString(player1.avoidcount), (width/2+3)*player1.amplifier, (height+3)*player1.amplifier);
}

bool ofApp::isend() {   // 플레이어가 출구에 도달했는지 확인한다
	if (player1.px == width - 2 && player1.py == height - 2) {
		return true;
	}
	return false;
}
