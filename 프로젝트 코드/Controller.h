#include "ofMain.h"

class Controller {
public:
	int start_e;    // ���α׷��� ���� �ð��� �����ϴ� int�� ����
	int start_s;    // ���α׷��� ���� �ð��� �����ϴ� int�� ����
	int start_i;    // ���α׷��� ���� �ð��� �����ϴ� int�� ����
	int interval_addenemy;  // ������ �߰��Ǵ� �ð� ���� �����ϱ� ���� int�� ����
	int interval_addspeed;  // ������ �ӵ��� �ö󰡴� �ð� ���� �����ϱ� ���� int�� ����
	int interval_item;     //�������� �̷� ���ο� �߰��Ǵ� �ð� ���� �����ϱ� ���� int�� ����

	void setup();
	bool addenemy(float timeelapsed);
	bool addspeed(float timeelapsed);
	bool additem(float timeelapsed);
};