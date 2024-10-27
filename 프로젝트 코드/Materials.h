#include "ofMain.h"

class Item {
public:
	int ix, iy;			//아이템의 좌표를 저장하기 위한 float형 변수
	int type;			//아이템의 종류를 지정하기 위한 int형 변수
	ofImage iimg;		//아이템의 이미지를 로드하기 위한 ofImage 변수

	void setup(int height, int width);	//아이템의 위치를 정하는 함수
	void draw(int size);			//아이템의 화면 상에 그리는 함수
};

