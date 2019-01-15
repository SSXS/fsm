#include "pch.h"
#include "setting.h"
#include "sys_time.h"

#include <stdio.h>
#include <time.h>

// �����Ĺ̶�����
const unsigned int FEEDING_WEIGHT_PER_SECOND = 20; // ÿ��������������λ�ˣ�
const unsigned int FREEZE_DURATION = 5; // �������Ͻ�������ʱ������λ�룩
const unsigned int EXIT_FEED_FULL_DELAY = 5; // �˳�����״̬�ӳ�ʱ������λ�룩
const unsigned int EXIT_FULL_WATER_DELAY = 10; // ������ �˳�ˮ��״̬�ӳ٣���λ�룩
const unsigned int POWER_OFF_TIME = 23; // �ػ�ʱ��
const unsigned int POWER_ON_TIME = 6; // ����ʱ��

void init_setting_parms()
{
	// ��ȡ���õĲ���
	cycle_period = 180;
	feed_duration = 60;
	feed_total_weight = 300;
	single_feeding_duration = 10;
	single_water_duration = 5;
	single_pre_water_duration = 3;
	empty_water_valid_duration = 30;
	empty_water_interval = 5;

	// �������õĲ���������ز���
	empty_duration = cycle_period - feed_duration; // ������ʱ������λ�룩
	unsigned int water_total_time = single_water_duration + single_pre_water_duration;
	single_feed_total_time = water_total_time > single_feeding_duration ? water_total_time : single_feeding_duration;

	// ��ȡ����Ĳ���
	feeded_weight = 0;
	feed_remain_tick = feed_duration;
	empty_remain_tick = empty_duration;
	state_at_shutdown = 1;

	// ģ���״ֵ̬
	feed_EMV = 0;
	water_EMV = 0;

	feed_full_status = 0;
	water_full_status = 0;
	touch_status = 0;
}

unsigned char get_feed_EMV()
{
	return feed_EMV;
}

void set_feed_EMV(unsigned char val)
{
	unsigned char _feed_EMV = get_feed_EMV();
	if (_feed_EMV == val)
		return;
	feed_EMV = val;
	time_t curTime;
	time(&curTime);
	printf("feed down EMV: %d, %s", feed_EMV, ctime(&curTime));
}

unsigned char get_water_EMV()
{
	return water_EMV;
}

void set_water_EMV(unsigned char val)
{
	unsigned char _water_EMV = get_water_EMV();
	if (_water_EMV == val)
		return;
	water_EMV = val;
	time_t curTime;
	time(&curTime);
	printf("water down EMV: %d, %s", water_EMV, ctime(&curTime));
}

unsigned char get_feed_full_status()
{
	return feed_full_status;
}

void set_feed_full_status(unsigned char val)
{
	unsigned char _feed_full_status = get_feed_full_status();
	if (_feed_full_status == val)
		return;
	feed_full_status = val;
	time_t curTime;
	time(&curTime);
	printf("feed full senor: %d, %s", feed_full_status, ctime(&curTime));
}

unsigned char get_water_full_status()
{
	return water_full_status;
}

void set_water_full_status(unsigned char val)
{
	unsigned char _water_full_status = get_water_full_status();
	if (_water_full_status == val)
		return;
	water_full_status = val;
	time_t curTime;
	time(&curTime);
	printf("water full senor: %d, %s", water_full_status, ctime(&curTime));
}

unsigned char get_touch_status()
{
	return touch_status;
}

void set_touch_status(unsigned char val)
{
	unsigned char _touch_status = get_touch_status();
	if (_touch_status == val)
		return;
	touch_status = val;
	time_t curTime;
	time(&curTime);
	printf("touch senor: %d, %s", touch_status, ctime(&curTime));
}



unsigned char save_data()
{
	unsigned int interval_tick = 60000;
	static unsigned int cur_tick = 0;
	
	unsigned int diff_time = diff_cur_time(cur_tick);
	if (diff_time >= interval_tick)
	{
		cur_tick = get_sys_tick();
		// feeded_weight
		// feed_remain_tick
		// empty_remain_tick
		// state_at_shutdown
	}
	return 0;
}