#ifndef _STATE_MACHINE_H_
#define _STATE_MACHINE_H_

#include "state.h"
#include "setting.h"

// ��״̬�б�
p_state_t state_list[2];

// ��״̬�б�
p_sub_state_t sub_state_list[8];

// ��ǰ��״̬
p_state_t cur_state;

// ��ʼ��״̬��
void init_state_machine();

// ˢ��״̬
void update_state_machine();

// ��ͣ״̬��
void pause_state_machine();

#endif // !_STATE_MACHINE_H_
