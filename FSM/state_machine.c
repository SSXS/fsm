#include "pch.h"
#include "state_machine.h"

#include <stdio.h>

void set_sub_state(E_SUB_STATE_CODE sub_state_code);
void set_cur_state(E_STATE_CODE state_code);

void set_cur_state(E_STATE_CODE state_code)
{
	if (cur_state)
	{
		cur_state->exit_action(cur_state);
	}
	
	state_at_shutdown = state_code;

	cur_state = state_list[state_code];
	E_SUB_STATE_CODE sub_state_code = cur_state->enter_action(&cur_state->start_tick);
	set_sub_state(sub_state_code);
}

void set_sub_state(E_SUB_STATE_CODE sub_state_code)
{
	if (cur_state->p_sub_state) 
	{
		cur_state->p_sub_state->exit_action();
	}	

	cur_state->p_sub_state = sub_state_list[sub_state_code];
	cur_state->p_sub_state->enter_action(&cur_state->p_sub_state->start_tick);
}

void init_state_machine()
{
	init_state(state_list);
	init_sub_state(sub_state_list);

	E_STATE_CODE init_state_code = state_at_shutdown == STATE_FEED ? STATE_FEED : STATE_EMPTY;
	set_cur_state(init_state_code);
}

void update_state_machine()
{
	E_STATE_CODE next_state_code = cur_state->update_action(cur_state->start_tick);
	if (next_state_code != cur_state->state_code)
	{
		set_cur_state(next_state_code);
	}
	else 
	{
		p_sub_state_t cur_sub_state = cur_state->p_sub_state;
		if (cur_sub_state) 
		{
			E_SUB_STATE_CODE netx_sub_state_code = cur_sub_state->update_action(cur_sub_state->start_tick);
			if (netx_sub_state_code != cur_sub_state->state_code)
			{
				set_sub_state(netx_sub_state_code);
			}
		}
	}
}


void pause_state_machine()
{

}