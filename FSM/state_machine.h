#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

#include "state.h"
#include "setting.h"

// 主状态列表
p_state_t state_list[2];

// 子状态列表
p_sub_state_t sub_state_list[8];

// 当前主状态
p_state_t cur_state;

// 初始化状态机
void init_state_machine();

// 刷新状态
void update_state_machine();

// 暂停状态机
void pause_state_machine();

#endif // !_STATE_MACHINE_H_
