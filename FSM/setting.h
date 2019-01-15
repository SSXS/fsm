#ifndef SETTING_H_
#define SETTING_H_

#define IS_DEBUG 1

#define FEED_EMV_ENABLE 1
#define FEED_EMV_DISABLE 0

#define WATER_EMV_ENABLE 1
#define WATER_EMV_DISABLE 0

#define TOUCH_ENABLE 1
#define TOUCH_DISABLE 0

// ����������õĲ���
unsigned int cycle_period; // ѭ�����ڣ����� + ������ʱ��������λ�룩
unsigned int feed_duration; // ������ʱ������λ�룩
unsigned int feed_total_weight; // ��������������������λ�ˣ�
unsigned int single_feeding_duration; // ��������ʱ������λ�룩
unsigned int single_water_duration; // ������ˮʱ������λ�룩
unsigned int single_pre_water_duration; // ����������ǰ��ˮʱ������λ�룩
unsigned int empty_water_valid_duration; // ������ ��ˮ��Чʱ������λ�룩
unsigned int empty_water_interval; // ������ ��ˮ���ʱ������λ�룩

// �����Ĺ̶�����
const unsigned int FEEDING_WEIGHT_PER_SECOND; // ÿ��������������λ�ˣ�
const unsigned int FREEZE_DURATION; // �������Ͻ�������ʱ������λ�룩
const unsigned int EXIT_FEED_FULL_DELAY; // �˳�����״̬�ӳ�ʱ������λ�룩
const unsigned int EXIT_FULL_WATER_DELAY; // ������ �˳�ˮ��״̬�ӳ٣���λ�룩
const unsigned int POWER_OFF_TIME; // �ػ�ʱ��
const unsigned int POWER_ON_TIME; // ����ʱ��

// ͨ�����õĲ�������������Ĳ���
unsigned int empty_duration; // ������ʱ������λ�룩
unsigned int single_feed_total_time; // ����������ʱ��

// ��Ҫ�������ֵ
unsigned int feeded_weight; // �������������ϵ�����
unsigned int feed_remain_tick; // ������ʣ��ʱ��
unsigned int empty_remain_tick; // ������ʣ��ʱ��
unsigned char state_at_shutdown; // �ػ�ʱ��״̬

// ������״ֵ̬
unsigned char feed_full_status; // ������Ӧ��״ֵ̬
unsigned char water_full_status; // ˮ����Ӧ��״ֵ̬
unsigned char touch_status; // ������״ֵ̬

// ��ŷ�״ֵ̬
unsigned char feed_EMV; // ����
unsigned char water_EMV; // ��ˮ

void init_setting_parms();

void set_feed_EMV(unsigned char val); // �������ϵ�ŷ�״̬
unsigned char get_feed_EMV(); // ��ȡ���ϵ�ŷ�״̬

void set_water_EMV(unsigned char val); // ������ˮ��ŷ�״̬
unsigned char get_water_EMV(); // ��ȡ��ˮ��ŷ�״̬

void set_feed_full_status(unsigned char val); // ����������Ӧ����ֵ
unsigned char get_feed_full_status(); // ��ȡ������Ӧ����ֵ

void set_water_full_status(unsigned char val); // ����ˮ����Ӧ����ֵ
unsigned char get_water_full_status(); // ��ȡˮ����Ӧ����ֵ

void set_touch_status(unsigned char val); // ���ô����˸�Ӧ����ֵ
unsigned char get_touch_status(); // ��ȡ�����˸�Ӧ����ֵ

unsigned char save_data(); // ��ʱ�������� ���60s

#endif