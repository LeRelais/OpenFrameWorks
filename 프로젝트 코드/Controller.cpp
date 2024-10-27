#include "Controller.h"

void Controller::setup() {
	start_e = 0;                     //�� ������ ���� ���� �ʱ�ȭ
	start_s = 0;                     //�� �ӵ������� ���� ���� �ʱ�ȭ
	start_i = 0;                     //������ ������ ���� ���� �ʱ�ȭ
	interval_addenemy = 30;          //�� ���� ���� ����
	interval_addspeed = 45;          //�� �ӵ����� ���� ����
	interval_item = 20;              //������ ���� ���� ����
}

bool Controller::addenemy(float timeelapsed) {               //���� �������θ� ��ȯ�Ѵ�
	if (timeelapsed - start_e > interval_addenemy) {        //����� �ð��� ���ݺ��� Ŀ���ٸ�
		start_e = timeelapsed;                              //�������θ� ������ �Ѵ�
		return true;
	}
	return false;                                         //�ƴ϶�� �������θ� �������� �Ѵ�
}

bool Controller::addspeed(float timeelapsed) {          //���� �ӵ��������θ� ��ȯ�Ѵ�
	if (timeelapsed - start_s > interval_addspeed) {     //����� �ð��� ���ݺ��� Ŀ���ٸ�
		start_s = timeelapsed;                          //�������θ� ������ �Ѵ�
		return true;
	}
	return false;                                       //�ƴ϶�� �������� �Ѵ�
}

bool Controller::additem(float timeelapsed) {          //�������� �������θ� ��ȯ�Ѵ�
	if (timeelapsed - start_i > interval_item) {       //����� �ð��� ���ݺ��� ũ�ٸ�
		start_i = timeelapsed;                         //�������� �����ϰ� �Ѵ�
		return true;
	}
	return false;                                      //�ƴ϶�� �������� �Ѵ�
}
