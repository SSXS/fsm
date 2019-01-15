#ifndef SETTING_H_
#define SETTING_H_

#define IS_DEBUG 1

#define FEED_EMV_ENABLE 1
#define FEED_EMV_DISABLE 0

#define WATER_EMV_ENABLE 1
#define WATER_EMV_DISABLE 0

#define TOUCH_ENABLE 1
#define TOUCH_DISABLE 0

// 设置面板设置的参数
unsigned int cycle_period; // 循环周期（下料 + 空料总时长）（单位秒）
unsigned int feed_duration; // 下料期时长（单位秒）
unsigned int feed_total_weight; // 下料期下料总重量（单位克）
unsigned int single_feeding_duration; // 单次下料时长（单位秒）
unsigned int single_water_duration; // 单次下水时长（单位秒）
unsigned int single_pre_water_duration; // 单次下料提前下水时长（单位秒）
unsigned int empty_water_valid_duration; // 空料期 下水有效时长（单位秒）
unsigned int empty_water_interval; // 空料期 下水间隔时长（单位秒）

// 机器的固定参数
const unsigned int FEEDING_WEIGHT_PER_SECOND; // 每秒下料重量（单位克）
const unsigned int FREEZE_DURATION; // 单次下料结束锁定时长（单位秒）
const unsigned int EXIT_FEED_FULL_DELAY; // 退出料满状态延迟时长（单位秒）
const unsigned int EXIT_FULL_WATER_DELAY; // 空料期 退出水满状态延迟（单位秒）
const unsigned int POWER_OFF_TIME; // 关机时间
const unsigned int POWER_ON_TIME; // 开机时间

// 通过设置的参数，计算出来的参数
unsigned int empty_duration; // 空料期时长（单位秒）
unsigned int single_feed_total_time; // 单次下料总时长

// 需要保存的数值
unsigned int feeded_weight; // 下料期已下饲料的重量
unsigned int feed_remain_tick; // 下料期剩余时长
unsigned int empty_remain_tick; // 空料期剩余时长
unsigned char state_at_shutdown; // 关机时的状态

// 传感器状态值
unsigned char feed_full_status; // 料满感应器状态值
unsigned char water_full_status; // 水满感应器状态值
unsigned char touch_status; // 触碰杆状态值

// 电磁阀状态值
unsigned char feed_EMV; // 下料
unsigned char water_EMV; // 下水

void init_setting_parms();

void set_feed_EMV(unsigned char val); // 设置下料电磁阀状态
unsigned char get_feed_EMV(); // 获取下料电磁阀状态

void set_water_EMV(unsigned char val); // 设置下水电磁阀状态
unsigned char get_water_EMV(); // 获取下水电磁阀状态

void set_feed_full_status(unsigned char val); // 设置料满感应器的值
unsigned char get_feed_full_status(); // 获取料满感应器的值

void set_water_full_status(unsigned char val); // 设置水满感应器的值
unsigned char get_water_full_status(); // 获取水满感应器的值

void set_touch_status(unsigned char val); // 设置触碰杆感应器的值
unsigned char get_touch_status(); // 获取触碰杆感应器的值

unsigned char save_data(); // 定时保存数据 间隔60s

#endif