#ifndef STATE_H_
#define STATE_H_

#include "setting.h"
#include "sys_time.h"

typedef enum
{
	SUB_STATE_FEEDING,
	SUB_STATE_FEED_FULL,
	SUB_STATE_FEED_FREEZE,
	SUB_STATE_FEED_WAIT,
	SUB_STATE_FEED_IDLE,
	SUB_STATE_EMPTY_WATER,
	SUB_STATE_EMPTY_WAIT,
	SUB_STATE_EMPTY_IDLE
} E_SUB_STATE_CODE;

typedef enum
{
	STATE_FEED,
	STATE_EMPTY
} E_STATE_CODE;

typedef void(*p_sub_state_enter_func)(unsigned int *);
typedef E_SUB_STATE_CODE(*p_sub_state_update_func)(unsigned int);
typedef void(*p_sub_state_exit_func)();

typedef E_SUB_STATE_CODE(*p_state_enter_func)(unsigned int *);
typedef E_STATE_CODE(*p_state_update_func)(unsigned int);
typedef void(*p_state_exit_func)(void *);

struct _sub_state_t
{
	E_SUB_STATE_CODE			state_code;
	p_sub_state_enter_func		enter_action;
	p_sub_state_update_func		update_action;
	p_sub_state_exit_func		exit_action;
	unsigned int				start_tick;
};
typedef struct _sub_state_t sub_state_t;
typedef struct _sub_state_t * p_sub_state_t;


struct _state_t {
	E_STATE_CODE			state_code;
	p_state_enter_func		enter_action;
	p_state_update_func		update_action;
	p_state_exit_func		exit_action;
	p_sub_state_t			p_sub_state;
	unsigned int			start_tick;
};
typedef struct _state_t state_t;
typedef struct _state_t * p_state_t;

void init_state(p_state_t *);
void init_sub_state(p_sub_state_t *);

void printf_interval(char *);

#endif // !STATE_H_