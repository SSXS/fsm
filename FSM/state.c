#include "pch.h"
#include "state.h"

#include <stdio.h>

// ************************** 下料期 **************************

E_SUB_STATE_CODE feed_enter(unsigned int * start_tick)
{
	*start_tick = get_sys_tick();

	if (IS_DEBUG)
	{
		printf("enter feed state time: %s", time_to_string(*start_tick));
	}
		

	if (feeded_weight >= feed_total_weight)
	{
		return SUB_STATE_FEED_IDLE;
	}
	else if (get_feed_full_status())
	{
		return SUB_STATE_FEED_FULL;
	}
	else
	{
		return SUB_STATE_FEEDING;
	}
}

E_STATE_CODE feed_update(unsigned int start_tick)
{
	unsigned int lost_time = diff_cur_time(start_tick);
	feed_remain_tick = feed_duration - lost_time;
	if (lost_time >= feed_duration)
	{
		return STATE_EMPTY;
	} 
	else
	{
		return STATE_FEED;
	}	
}

void feed_exit(p_state_t state)
{	
	if (state->p_sub_state) 
	{
		state->p_sub_state->exit_action();
		state->p_sub_state = NULL;
	}

	if (IS_DEBUG) 
	{
		printf("exit feed state...\n");
	}
}

state_t feed_state = {
	STATE_FEED,
	feed_enter,
	feed_update,
	feed_exit,
	NULL,
	0
};


// ************************** 空料期状态 **************************

E_SUB_STATE_CODE empty_enter(unsigned int * start_tick)
{
	*start_tick = get_sys_tick();

	if (IS_DEBUG)
	{
		printf("enter empty state time: %s", time_to_string(*start_tick));
	}
	
	unsigned int lost_time = empty_duration - empty_remain_tick;
	if (lost_time >= empty_water_valid_duration)
	{
		return SUB_STATE_EMPTY_IDLE;
	}
	else if (get_water_full_status())
	{
		return SUB_STATE_EMPTY_WAIT;
	}
	else
	{
		return SUB_STATE_EMPTY_WATER;
	}
}

E_STATE_CODE empty_update(unsigned int start_tick)
{
	unsigned int lost_time = diff_cur_time(start_tick);
	empty_remain_tick = empty_duration - lost_time;
	if (lost_time >= empty_duration)
	{
		return STATE_FEED;
	}
	else
	{
		return STATE_EMPTY;
	}
}

void empty_exit(p_state_t state)
{	
	if (state->p_sub_state)
	{
		state->p_sub_state->exit_action();
		state->p_sub_state = NULL;
	}

	if (IS_DEBUG)
	{
		printf("exit empty state...\n");
	}
}

state_t empty_state = {
	STATE_EMPTY,
	empty_enter,
	empty_update,
	empty_exit,
	NULL,
	0
};

// 主状态初始化
void init_state(p_state_t * state_arr)
{
	*(state_arr + feed_state.state_code) = &feed_state;
	*(state_arr + empty_state.state_code) = &empty_state;
}

void printf_interval(char *content) {
	static unsigned int last_tick = 0;
	unsigned int interval_time = 1;
	unsigned int cur_tick = get_sys_tick();
	if (diff_time(cur_tick, last_tick) >= interval_time)
	{
		printf("%s\n", content);
		last_tick = cur_tick;
	}
}