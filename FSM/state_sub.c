#include "pch.h"
#include "state.h"

#include <stdio.h>

// ************************** 下料期子状态 -- 下料 **************************

void feeding_enter(unsigned int * start_tick)
{
	*start_tick = get_sys_tick();

	if (IS_DEBUG)
	{
		printf("enter feed down sub state: %s\n", time_to_string(*start_tick));
	}
}

// 开始下料的时间点
unsigned int feed_start_tick = 0;

E_SUB_STATE_CODE feeding_update(unsigned int start_tick)
{	
	if (IS_DEBUG)
	{
		printf_interval("feed down update...");
	}

	// 是否到达下料总重量
	if (feeded_weight >= feed_total_weight)
	{
		return SUB_STATE_FEED_IDLE;
	}

	// 是否料满
	if (get_feed_full_status())
	{
		return SUB_STATE_FEED_FULL;
	}

	// 下料是否结束
	double lost_time = diff_cur_time(start_tick);
	if (lost_time >= single_feed_total_time)
	{
		return SUB_STATE_FEED_FREEZE;
	}
	
	if (lost_time >= single_water_duration && lost_time <= single_pre_water_duration + single_feeding_duration)
	{
		set_feed_EMV(FEED_EMV_ENABLE);
		if (!feed_start_tick)
		{
			feed_start_tick = get_sys_tick();
		}
		unsigned int diff_time = diff_cur_time(feed_start_tick);
		if (diff_time >= 1) 
		{
			feed_total_weight += FEEDING_WEIGHT_PER_SECOND; // 保存已下料的重量（每秒记录一次）
			feed_start_tick = get_sys_tick();
		}
	}
	else 
	{
		set_feed_EMV(FEED_EMV_DISABLE);
	}
	
	if (lost_time > single_water_duration + single_pre_water_duration)
	{
		set_water_EMV(WATER_EMV_DISABLE);
	} 
	else
	{
		set_water_EMV(WATER_EMV_ENABLE);
	}
	return SUB_STATE_FEEDING;
}

void feeding_exit(unsigned int * start_tick)
{
	if (IS_DEBUG) 
	{
		printf("exit feed down sub state...\n");
	}

	set_feed_EMV(FEED_EMV_DISABLE);
	set_water_EMV(WATER_EMV_DISABLE);
	feed_start_tick = 0;
}

sub_state_t feeding = {
	SUB_STATE_FEEDING,
	feeding_enter,
	feeding_update,
	feeding_exit,
	0
};


// ************************** 下料期子状态 -- 料满 **************************

unsigned int unfull_tick = 0; // 解除料满的时间点

void feed_full_enter(unsigned int * start_tick)
{
	*start_tick = get_sys_tick();
	if (IS_DEBUG)
	{
		printf("sub state: feed full enter \n");
	}
}

E_SUB_STATE_CODE feed_full_update(unsigned int start_tick)
{
	if (IS_DEBUG) 
	{
		printf_interval("sub state: feed full update...");
	}
		
	if (get_feed_full_status())
	{
		return SUB_STATE_FEED_FULL;
	}
	else
	{
		// 料满解除时 要延迟退出料满状态
		if (!unfull_tick)
		{	
			unfull_tick = get_sys_tick();
		}
		
		if (diff_cur_time(unfull_tick) >= EXIT_FEED_FULL_DELAY)
		{
			return SUB_STATE_FEED_WAIT;
		}
		else
		{
			return SUB_STATE_FEED_FULL;
		}
	}
}

void feed_full_exit()
{
	if (IS_DEBUG)
	{
		printf("exit feed full sub state...\n");
	}
	unfull_tick = 0;
}

sub_state_t feed_full = {
	SUB_STATE_FEED_FULL,
	feed_full_enter,
	feed_full_update,
	feed_full_exit,
	0
};

// ************************** 下料期子状态 -- 锁定 **************************

void feed_freeze_enter(unsigned int * start_tick)
{
	*start_tick = get_sys_tick();
	if (IS_DEBUG)
	{
		printf("enter freeze sub state");
	}
}

E_SUB_STATE_CODE feed_freeze_update(unsigned int start_tick)
{
	if (IS_DEBUG) 
	{
		printf_interval("feed freeze update...");
	}

	if (get_feed_full_status())
	{
		return SUB_STATE_FEED_FULL;
	}

	unsigned int lost_time = diff_cur_time(start_tick);
	return lost_time >= FREEZE_DURATION ? SUB_STATE_FEED_WAIT : SUB_STATE_FEED_FREEZE;
}

void feed_freeze_exit()
{
	if (IS_DEBUG)
	{
		printf("exit freeze sub state\n");
	}
}

sub_state_t feed_freeze = {
	SUB_STATE_FEED_FREEZE,
	feed_freeze_enter,
	feed_freeze_update,
	feed_freeze_exit,
	0
};


// ************************** 下料期子状态 -- 等待下料 **************************
void feed_wait_enter(unsigned int * start_tick)
{
	*start_tick = get_sys_tick();
	if (IS_DEBUG)
	{
		printf("enter feed wait sub state...\n");
	}
}

E_SUB_STATE_CODE feed_wait_update(unsigned int start_tick)
{
	if (IS_DEBUG) 
	{
		printf_interval("feed wait update...");
	}
	if (get_touch_status()) 
	{
		set_touch_status(TOUCH_DISABLE);
		return SUB_STATE_FEEDING;
	}
	else
	{
		return SUB_STATE_FEED_WAIT;
	}
		
}

void feed_wait_exit()
{
	if (IS_DEBUG)
	{
		printf("exit feed wait sub state...\n");
	}
}

sub_state_t feed_wait = {
	SUB_STATE_FEED_WAIT,
	feed_wait_enter,
	feed_wait_update,
	feed_wait_exit,
	0
};

// ************************** 下料期子状态 -- 待机 **************************
void feed_idle_enter(unsigned int * start_tick)
{
	*start_tick = get_sys_tick();
	if (IS_DEBUG)
	{
		printf("enter feed standby sub state...\n");
	}
}

E_SUB_STATE_CODE feed_idle_update(unsigned int start_tick)
{
	if (IS_DEBUG) 
	{
		printf_interval("feed standby update...");
	}
	return SUB_STATE_FEED_IDLE;
}

void feed_idle_exit()
{
	if (IS_DEBUG)
	{
		printf("exit feed standby sub state...\n");
	}
}


sub_state_t feed_idle = {
	SUB_STATE_FEED_IDLE,
	feed_idle_enter,
	feed_idle_update,
	feed_idle_exit,
	0
};

// ************************** 空料期子状态 -- 下水 **************************

void empty_water_enter(unsigned int * start_tick)
{
	*start_tick = get_sys_tick();
	if (IS_DEBUG)
	{
		printf("enter water down sub state...\n");
	}
}

E_SUB_STATE_CODE empty_water_update(unsigned int start_tick)
{
	if (IS_DEBUG)
	{
		printf_interval("empty water down update...");
	}
	// 空料期下水时间是否结束
	unsigned int empty_pass_time = empty_duration - empty_remain_tick;
	if (empty_pass_time >= empty_water_valid_duration)
		return SUB_STATE_EMPTY_IDLE;
	else if (get_water_full_status())
		return SUB_STATE_EMPTY_WAIT;
	else {
		set_water_EMV(WATER_EMV_ENABLE); // 打开下水电磁阀
		return SUB_STATE_EMPTY_WATER;
	}
}

void empty_water_exit()
{
	if (IS_DEBUG)
	{
		printf("exit water down sub state...\n");
	}
		
	set_water_EMV(WATER_EMV_DISABLE); // 关闭下水电磁阀
}

sub_state_t empty_water = {
	SUB_STATE_EMPTY_WATER,
	empty_water_enter,
	empty_water_update,
	empty_water_exit
};

// ************************** 空料期子状态 -- 等待下水 **************************

unsigned int unfull_water_tick = 0; // 解除料满的时间点

void empty_wait_enter(unsigned int * start_tick)
{
	*start_tick = get_sys_tick();
	if (IS_DEBUG)
	{
		printf("enter empty wait sub state...\n");
	}
}

E_SUB_STATE_CODE empty_wait_update(unsigned int start_tick)
{
	if (IS_DEBUG) 
	{
		printf_interval("empty wait update...");
	}
	// 空料期下水时间是否结束
	unsigned int empty_pass_time = empty_duration - empty_remain_tick;
	if (empty_pass_time >= empty_water_valid_duration)
	{
		return SUB_STATE_EMPTY_IDLE;
	}
	
	if (!get_water_full_status())
	{
		if (!unfull_water_tick)
		{
			unfull_water_tick = get_sys_tick();
		}
		unsigned int diff_time_unfull = diff_cur_time(unfull_water_tick);
		unsigned int diff_time_start = diff_cur_time(start_tick);
		if (diff_time_unfull >= EXIT_FULL_WATER_DELAY && diff_time_start >= empty_water_interval)
		{
			return SUB_STATE_EMPTY_WATER;
		}
	}
	return SUB_STATE_EMPTY_WAIT;
}

void empty_wait_exit()
{
	if (IS_DEBUG)
	{
		printf("exit empty wait sub state...\n");
	}
	unfull_water_tick = 0;
}

sub_state_t empty_wait = {
	SUB_STATE_EMPTY_WAIT,
	empty_wait_enter,
	empty_wait_update,
	empty_wait_exit,
	0
};

// ************************** 空料期子状态 -- 待机 **************************

void empty_idle_enter(unsigned int * start_tick)
{
	*start_tick = get_sys_tick();
	if (IS_DEBUG)
	{
		printf("enter empty standby sub state...\n");
	}
}

E_SUB_STATE_CODE empty_idle_update(unsigned int start_tick)
{
	if (IS_DEBUG) {
		printf_interval("empty standby update...");
	}
	return SUB_STATE_EMPTY_IDLE;
}

void empty_idle_exit()
{
	if (IS_DEBUG)
	{
		printf("exit empty standby sub state...\n");
	}
}


sub_state_t empty_idle = {
	SUB_STATE_EMPTY_IDLE,
	empty_idle_enter,
	empty_idle_update,
	empty_idle_exit,
	0
};

// 子状态初始化
void init_sub_state(p_sub_state_t * sub_state_arr)
{
	*(sub_state_arr + feeding.state_code) = &feeding;
	*(sub_state_arr + feed_full.state_code) = &feed_full;
	*(sub_state_arr + feed_freeze.state_code) = &feed_freeze;
	*(sub_state_arr + feed_wait.state_code) = &feed_wait;
	*(sub_state_arr + feed_idle.state_code) = &feed_idle;
	*(sub_state_arr + empty_water.state_code) = &empty_water;
	*(sub_state_arr + empty_wait.state_code) = &empty_wait;
	*(sub_state_arr + empty_idle.state_code) = &empty_idle;
}