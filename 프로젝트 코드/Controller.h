#include "ofMain.h"

class Controller {
public:
	int start_e;    // 프로그램의 시작 시간을 저장하는 int형 변수
	int start_s;    // 프로그램의 시작 시간을 저장하는 int형 변수
	int start_i;    // 프로그램의 시작 시간을 저장하는 int형 변수
	int interval_addenemy;  // 적들이 추가되는 시간 차를 저장하기 위한 int형 변수
	int interval_addspeed;  // 적들의 속도가 올라가는 시간 차를 저장하기 위한 int형 변수
	int interval_item;     //아이템이 미로 내부에 추가되는 시간 차를 저장하기 위한 int형 변수

	void setup();
	bool addenemy(float timeelapsed);
	bool addspeed(float timeelapsed);
	bool additem(float timeelapsed);
};