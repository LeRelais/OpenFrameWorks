#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	ofSetFrameRate(15);                      //���α׷��� �ʴ� �������� 15�� �����Ѵ�
	ofSetWindowPosition(0, 100);             //���α׷��� ������ ��ġ�� �����Ѵ�
	gamestate = 1;                          //������ ����
	score = 0;                               //���� �ʱ�ȭ
	player1.bulletspeed = 0.1;                //�÷��̾ �߻��ϴ� �Ѿ��� �ӵ� �ʱ�ȭ
	score_f.load("verdana.ttf", 10, true, true);   //������ ����ϱ� ���� ��Ʈ�� �ҷ��´�
	time.load("verdana.ttf", 10, true, true);      //�ð��� ����ϱ� ���� ��Ʈ�� �ҷ��´�
	player1.pimg.load("playerlife1down.png");    //�÷��̾� Ŀ���� �⺻ �̹����� �ҷ��´�
	hp.load("hp.png");                           //hp�� �̹����� �ҷ��´�
	whp.load("verdana.ttf", 10, true, true);       //��HP : ���� ����ϱ� ���� ��Ʈ�� �ҷ��´�
	avoidcount.load("verdana.ttf", 10, true, true);  //���� ���� �� �ִ� Ƚ���� ����ϱ� ���� ��Ʈ�� �ҷ��´�
	loadflag = 0;                                   //�̷��� �ε� ���� �ʱ�ȭ
}

//--------------------------------------------------------------
void ofApp::update(){
	if (gamestate == 1) {            //gamestate�� 1�̶�� �ƹ� ���۵� �������� �ʴ´�
		 
	}
	else if (gamestate == 2) {       //gamestate�� 2��� ���� ������ �����Ѥ�
		elapsetime = ofGetElapsedTimef();   //������Ʈ�� ���۰� ���ÿ� ���۵ǰ� �ִ� ������ �ð��� ����Ѵ�
		limitRange(&player1.py, &player1.px, stage);  //�÷��̾ �̵��� �� ���� ���� ��ġ�Ѵٸ� �� �� ������ �����Ѵ�
		for (int i = 0; i < op.size(); i++) {        //vector�� ����� ������ ������ ����
			if (op[i].type == 1) {                   //�̷� ������ ���̶��
				for(int j = 0; j < 10; j++)
					op[i].dir = rand() % 4;          //�̵� ������ ���� update�� �̿��� ���Ž����ְ� �ٸ� type�� ���̶��
			}
			op[i].update(stage, height, width);      //Enemy.cpp�� ����� ���ۿ� ���� ���� �������� ���Ž�Ų��
			limitRange(&op[i].ey, &op[i].ex, stage); //�÷��̾�� ���������� �̵��� �� ���� ���� ��ġ�Ѵٸ� �� �� ������ �����Ѵ�
		}
		for (int i = 0; i < bullet.size(); i++)      //vector�� ����� �Ѿ˿� ���� �������� �����Ѵ�.
			bullet[i].update();
		if (control_e.addenemy(elapsetime)) {        //Controller�� ����� ��ɿ� ���� ���� �߰��ؾ� �Ѵٸ� ���� �߰��Ѵ�
			Enemy add;                 
			for (int i = 0; i < 3; i++) {
				add.setup(height, width);
				add.amplifier = player1.amplifier;
				add.type = rand() % 4 + 1;
				op.push_back(add);
			}
		}
		if (control_e.addspeed(elapsetime)) {       //Controller�� ����� ��ɿ� ���� ���� �ӵ��� �������Ѿ� �Ѵٸ� ���� �ӵ��� �÷��ش�
			for (int i = 0; i < op.size(); i++) {
				if(op[i].type != 1 && op[i].speed < 2.5)   //��, ���� ���� �̻����� �ø����� �ʴ´�
					op[i].speed += 0.5;
			}
		}
		if (control_e.additem(elapsetime)) {         //Controller�� ����� ��ɿ� ���� �������� �����ؾ� �Ѵٸ� �������� �����Ѵ�
			Item i;
			i.setup(height, width);
			item.push_back(i);
		}
		if (isend()) {                                  //�÷��̾ �ⱸ�� �����ߴٸ� 
			gamestate = 1;              //���ӻ��¸� �ʱ�ȭ�ϰ�
			player1.setup();             //�÷��̾��� ��ġ�� �ʱ�ȭ�Ѵ�
		}
	}
}

void ofApp::limitRange(float *y, float *x, char **stage) {       //�̵� ���� ��ǥ�� maze�� �ܺκ��̶�� �������� �����Ѵ�.
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
	if (gamestate == 1) {                  //gamestate�� 1�̶�� �ƹ��� ���۵� �������� �ʴ´�

	}
	else if (gamestate == 2) {            //���������� �۵����̶�� ���� ������ �����Ѵ�
		for (int i = 0; i < height; i++) {       //**stage�� ����� �̷θ� �԰ݿ� ���� �׸��� 
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
		player1.draw();        //����� �÷��̾��� ��ġ�� �÷��̾ �׸���

		drawtime(elapsetime);  //����� �ð��� ����ϴ� �Լ��� �ҷ��´�
		checkcollision();  // �÷��̾�� ���� �浹�ѵ� ����� ������ �����ϴ� �Լ��� �ҷ��´�
		checkitem();  // �÷��̾ �������� ȹ���� �� ����� ������ �����ϴ� �Լ��� �ҷ��´�
		bulletcollision();  // �Ѿ��� ���� �浹�� �� ����� ������ �����ϴ� �Լ��� �ҷ��´�
		checkbullet();  //�Ѿ��� ���� �浹�� �� ����� ������ �����ϴ� �Լ��� �ҷ��´�
		drawlife();
		drawavoidcount();
		for (int i = 0; i < bullet.size(); i++) {   //�Ѿ��� ���� ���� �Ѿ��� ȭ�� �� �׸���
			if (bullet[i].dir == 0 || bullet[i].dir == 1)
				bullet[i].bimg.load("bulletupdown.png");
			else
				bullet[i].bimg.load("bulletrightleft.png");
			bullet[i].draw();
		}

		for (int i = 0; i < op.size(); i++) {   //������ ���� ���� ������ ȭ�� �� �׸��� 
			if (op[i].type == 1) {              //vector�� ����� ���� type�� ���� �̹����� �ε��ϰ�
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
			op[i].draw();                          //�׸���.
		}
		for (int i = 0; i < item.size(); i++) {    //�������� ���� ���� �����۵��� ȭ�� �� �׸���
			item[i].draw(player1.amplifier);
		}
	}
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (gamestate == 1 && key == ' ' && loadflag == 1) {  //���α׷��� ����ǰ� ���� ������ ���۵��� �ʾҴٸ� ���� ������ �����Ѵ�
		ofResetElapsedTimeCounter();     //�ð��� 0���� �ʱ�ȭ�Ѵ�
		ofSetWindowShape(width * player1.amplifier, (height+4) * player1.amplifier); //��µǴ� �������� ũ�⸦ �԰ݿ� ���� �����Ѵ�
		gamestate = 2;     //������ �����ߴٴ� ������ ��ȯ�Ѵ�
		Enemy a;
		if (height*width > 400) {
			for (int i = 0; i < height*width / 50; i++) {
				a.setup(height, width);
				a.type = (rand() % 4) + 1;
				a.amplifier = player1.amplifier;
				op.push_back(a);
			}
		}
		control_e.setup();      //������ ���۵Ǿ��� ��, �帥 �ð��� ���� ������ �����ϴ� Controller class ������ �ʱ�ȭ�Ѵ�.
	}

	if (gamestate == 2) {       //������ ����� ���¶��
		if (key == UP || key == OF_KEY_UP) {  //input���� �޴� ���� ���� �÷��̾��� Ŀ���� �����δ�.
			player1.up = true;                //����Ű ��, w    ��
			player1.update(stage, height, width);
			if (player1.lives <= 1)
				player1.pimg.load("playerlife1up.png");
			else
				player1.pimg.load("playerup.png");
		}
		if (key == DOWN||key == OF_KEY_DOWN) {        //����Ű �Ʒ�, s �Ʒ�
			player1.down = true;
			player1.update(stage, height, width);
			if (player1.lives <= 1)
				player1.pimg.load("playerlife1down.png");
			else
				player1.pimg.load("playerdown.png");
		}
		if (key == LEFT || key == OF_KEY_LEFT) {       //����Ű ����, a ����
			player1.left = true;
			player1.update(stage, height, width);
			if (player1.lives <= 1)
				player1.pimg.load("playerlife1left.png");
			else
				player1.pimg.load("playerleft.png");
		}
		if (key == RIGHT || key == OF_KEY_RIGHT) {     //����Ű ������, d ������ 
			player1.right = true;
			player1.update(stage, height, width);
			if (player1.lives <= 1)
				player1.pimg.load("playerlife1right.png");
			else
				player1.pimg.load("playerright.png");
		}
		
	}

	if (key == 'i' && gamestate == 2) {   //������ ����� ���¶��
		if (bullet.size() < player1.max_capacity) {   //input���� �޴� ���� ���� �Ѿ��� �����Ѵ�
			Bullet b;                                // i        ������
			float x = player1.px;
			float y = player1.py;
			b.setup(x, y, 0, player1.amplifier);
			bullet.push_back(b);
		}
		else
			return;
	}
	if (key == 'k' && gamestate == 2) {          // k      �Ʒ�����
		if (bullet.size() < player1.max_capacity) {  
			Bullet b;                                
			float x = player1.px;
			float y = player1.py;
			b.setup(x, y, 1, player1.amplifier);
			bullet.push_back(b);
		}
		else return;
	}
	if (key == 'j' && gamestate == 2) {             //j     ���ʹ���
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
	if (key == 'l' && gamestate == 2) {            //��    �����ʹ���
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

	if (key == 'q' && gamestate == 1) {              //������ ������� �ʾҰ� q�� �Է����� �־����ٸ�
		for (int i = 0; i < height; i++) {
			delete[] stage[i];
		}
		delete[] stage;                             //���α׷����� ���� �޸��� �Ҵ��� �����ϰ�
		while (!op.empty())
			op.pop_back();
		while (!item.empty())
			item.pop_back();
		while (!op.empty())
			op.pop_back();
		_Exit(0);                                 //�����Ѵ�
	}
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
	if (key == 'l' && gamestate == 1) {        //���α׷��� ������ maze.txt�� load���� �ʾ��� ���
		ofFileDialogResult openFileResult = ofSystemLoadDialog("Select a only txt");  //�˾� �����츦 �����

		if (openFileResult.bSuccess) {                                                 //.txtȮ������ ������ �����ϰ� �Ѵ� 
			ofLogVerbose("User selected a file");

			processOpenFileSelection(openFileResult);
			
		}
	}
	if (gamestate == 2) {           //����Ű Ȥ�� wsad Ű�� �Է��� ����ٸ� 
		if (key == UP || OF_KEY_UP) {            //�÷��̾� Ŀ���� �������� ������Ų��.
			player1.up = false;
			if (player1.lives <= 1)            //�÷��̾��� �̵� ����� HP ���� ���¿� ����
				player1.pimg.load("playerlife1up.png");    //�ٸ� ����� Ŀ����
			else                                              //�ε��Ѵ�.
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

	if (key == 'q' && gamestate == 2) {                       //������ ����Ǿ� ���� �� q�� input���� �޴´ٸ�
		gamestate = 1;                                        //������ �����ϰ� ����� ������ ����, �������� ������ �����ϰ�
		player1.setup();                                      //�÷��̾��� ��ġ�� �ʱⰪ���� ������ ��
		if (op.size() > 0) {
			while (!op.empty())
				op.pop_back();
		}
		if (item.size() > 0) {
			while (!item.empty())
				item.pop_back();
		}
		ofResetElapsedTimeCounter();                          //�ð��� 0���� �ʱ�ȭ�Ѵ�
		score = 0;                                       //������ 0���� �ʱ�ȭ�Ѵ�
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

	string fileName = openFileResult.getName();              //�˾� �����쿡�� ���������� .txt������ �������� ��
	ofFile file(fileName);                                   //�� �̸��� ���� .txt������ ���� ���� ������ �����Ѵ�

	if (!file.exists()) {                                    //bin/data ���� ���ο� ���� �̸��� ������ ���ٸ� 
		cout << "Target file does not exists." << endl;      //���� �޼����� ����ϰ� 
	}
	else {
		cout << "We found the target file." << endl;         //�ƴ϶�� ���� ������ �����Ѵ�
	}

	ofBuffer buffer(file);                                   //������ ����

	int col = 0, row = 0;
	loadflag = 1;
	vector<string> f;
	for (auto line : buffer.getLines()) {   //vector��  .txt�� ������ �����ϰ� 
		f.push_back(line);
		row = line.size();              //�� ���� ����ũ���
		col++;                        //����ũ�⸦ ������ ������ �����ϸ� Ž���Ѵ�
	}
	height = col;             //�̷��� ����ũ��
	width = row;              //�̷��� ����ũ��

	player1.setup();         //�÷��̾��� ��ġ�� �ʱ�ȭ��Ű�� maze�� ũ�⿡ ���� �԰��� ���Ѵ�. 
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

	stage = new char*[col];             //ofApp.h�� ����� **stage�� �������� �Ҵ����ְ�
	for (int i = 0; i < col; i++)
		stage[i] = new char[row];

	for (int i = col - 1; i >= 0; i--) {      //vector�� ��� maze�� ������ **stage�� �����Ѵ�
		string a = f.back();
		f.pop_back();
		for (int j = 0; j < row; j++) {
			stage[i][j] = a[j];
		}
	}
}

void ofApp::checkcollision() {               //�÷��̾�� ���� �浹�� Ȯ���ϴ� �Լ�
	if (gamestate == 2) {
		for (int i = 0; i < op.size(); i++) {     //�÷��̾�� ���� �浹�ߴٸ�
			if (sqrt(((op[i].ex - player1.px)*(op[i].ex - player1.px)) + (op[i].ey - player1.py)*(op[i].ey - player1.py)) < 0.5) {
				player1.lives -= 1;               //�÷��̾��� ü���� 1 ���
			}
			if (player1.lives < 0) {             //���� ���� ü���� 0���� �۰� �ȴٸ� ����ȭ���� �׸���
				gamestate = 1;                   //���ӿ��� ���� ������ �ʱ�ȭ�Ѵ�
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

void ofApp::checkitem() {        //�÷��̾ �̷� ���� �������� �Ծ��� ���
	if (gamestate == 2) {        //������ ���� ȿ���� �ߵ��ϰ� �Ѵ�
		for (int i = 0; i < item.size(); i++) {
			if (item[i].ix == (int)player1.px && item[i].iy == (int)player1.py) {
				if (item[i].type == 1) {
					player1.max_capacity++;           //1�� ������. �÷��̾��� ź�� ���� �ø���
				}
				if (item[i].type == 2) {              //2�� ������, ������ �ӵ��� ����� 
					for (int i = 0; i < op.size(); i++) {
						if (op[i].type != 1 && op[i].speed >= 0.5)
							op[i].speed -= 1;
						if (op[i].speed <= 0)
							op[i].speed = 0.5;
					}
				}
				if (item[i].type == 3) {              //3�� ������, �÷��̾ ���� �հ� ������ �� �ְ� �Ѵ�
					player1.avoidwall = true;
					player1.avoidcount++;
				}
				if (item[i].type == 4) {              //4�� ������, �÷��̾��� ü���� 1 �ø���
					if (player1.lives <= 5)
						player1.lives += 1;
				}
				if (item[i].type == 5) {              //5�� ������, �Ѿ��� �ִ��̵��Ÿ��� �ø��� 
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

void ofApp::checkbullet() {    //�Ѿ��� �ִ�Ÿ��� �����ߴ��� Ȯ���ϴ� �Լ��̴�
	for (int i = 0; i < bullet.size(); i++) {
		if (bullet[i].dir == 0 || bullet[i].dir == 1) {   //������ ���� �ִ� �̵��Ÿ��� �̵��ߴٸ�
			if (abs(bullet[i].by - bullet[i].ori_by) > bullet[i].max_dist)
				bullet.erase(bullet.begin() + i);
		}
		else if (bullet[i].dir == 2 || bullet[i].dir == 3) {
			if(abs(bullet[i].bx - bullet[i].ori_bx) > bullet[i].max_dist)
				bullet.erase(bullet.begin()+i);           //vector ����� �Ѿ��� �����Ѵ�
		}
	}
}

void ofApp::bulletcollision() {      //�Ѿ��� ���� �����ϰų� ���� ��Ҵ��� Ȯ���ϴ� �Լ�
	int x, y;
	for (int i = 0; i < bullet.size(); i++) {
		 x = (int)bullet[i].bx;
		 y = (int)bullet[i].by;
		if (stage[y][x] == '+' || stage[y][x] == '-' || stage[y][x] == '|') {
			bullet.erase(bullet.begin() + i);          //���� ��Ҵٸ� �Ѿ��� �����Ѵ� 
		}
		else {
			for (int j = 0; j < op.size(); j++) {          //���� �����ߴٸ�
				if (sqrt((bullet[i].bx - op[j].ex)*(bullet[i].bx - op[j].ex) + (bullet[i].by - op[j].ey)*(bullet[i].by - op[j].ey)) < 0.8) {
					Item x;                     //������ 100 �ø��� �� �ڸ��� �������� ������ ��
					x.setup(height, width);
					x.ix = bullet[i].bx;
					x.iy = bullet[i].by;
					item.push_back(x);
					op.erase(op.begin() + j);       //���� ������ vector���� �����Ѵ�
				}
			}
		}
	}
}

void ofApp::drawlife() {    //�÷��̾��� HP�� ����Ѵ�
	for (int i = 1; i <= player1.lives; i++) {
		hp.draw((width/2+i+1) * player1.amplifier, (height) * player1.amplifier, player1.amplifier, player1.amplifier);
	}
	string s = "HP : ";
	whp.drawString(ofToString(s), (width/2-1)*player1.amplifier, (height + 1)*player1.amplifier);
}

void ofApp::drawtime(float t) {              //����� �ð��� ȭ�� �� �׸���
	ofSetColor(231, 23, 12);
	time.drawString(ofToString(elapsetime), (width/2+3)*player1.amplifier, (height + 2)*player1.amplifier);
	string s = "Time : ";
	time.drawString(ofToString(s), (width/2-1)*player1.amplifier, (height + 2)*player1.amplifier);
}

void ofApp::drawavoidcount() {     //���� ���� �� �ִ� Ƚ���� ����Ѵ�
	string s = "# :";
	avoidcount.drawString(ofToString(s), (width/2-1)*player1.amplifier, (height + 3)*player1.amplifier);
	avoidcount.drawString(ofToString(player1.avoidcount), (width/2+3)*player1.amplifier, (height+3)*player1.amplifier);
}

bool ofApp::isend() {   // �÷��̾ �ⱸ�� �����ߴ��� Ȯ���Ѵ�
	if (player1.px == width - 2 && player1.py == height - 2) {
		return true;
	}
	return false;
}
