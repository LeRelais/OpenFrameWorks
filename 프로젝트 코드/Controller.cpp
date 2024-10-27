#include "Controller.h"

void Controller::setup() {
	start_e = 0;                     //적 생성을 위한 변수 초기화
	start_s = 0;                     //적 속도증가를 위한 변수 초기화
	start_i = 0;                     //아이템 생성을 위한 변수 초기화
	interval_addenemy = 30;          //적 생성 간격 정의
	interval_addspeed = 45;          //적 속도증가 간격 정의
	interval_item = 20;              //아이템 생성 간격 정의
}

bool Controller::addenemy(float timeelapsed) {               //적의 생성여부를 반환한다
	if (timeelapsed - start_e > interval_addenemy) {        //경과된 시간이 간격보다 커졌다면
		start_e = timeelapsed;                              //생성여부를 참으로 한다
		return true;
	}
	return false;                                         //아니라면 생성여부를 거짓으로 한다
}

bool Controller::addspeed(float timeelapsed) {          //적의 속도증가여부를 반환한다
	if (timeelapsed - start_s > interval_addspeed) {     //경과된 시간이 간격보다 커졌다면
		start_s = timeelapsed;                          //증가여부를 참으로 한다
		return true;
	}
	return false;                                       //아니라면 거짓으로 한다
}

bool Controller::additem(float timeelapsed) {          //아이템의 생성여부를 반환한다
	if (timeelapsed - start_i > interval_item) {       //경과된 시간이 간격보다 크다면
		start_i = timeelapsed;                         //아이템을 생성하게 한다
		return true;
	}
	return false;                                      //아니라면 거짓으로 한다
}
