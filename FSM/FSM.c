// FSM.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

// 命名规则
// 变量命名统一用全小写"_"作分隔符--> xxx_xxx
// 常量命名统一用全大写"_"作分隔符--> XXX_XXX
// 指针变量统一用p_开头--> p_xxx
// 自定义类型变量命名
// 1、结构体：声明(下划线开头)--> _xxx_t、定义--> xxx_t、结构体指针--> p_xxx_t
// 2、枚举：声明(下划线开头)--> _XXX、定义--> E_XXX
// 3、函数指针：声明--> p_xxx_func

#include "pch.h"
#include "state_machine.h"
#include "setting.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>

int main()
{
	//char ch;
	//
	//init_setting_parms();
	//init_state_machine();

	//while (1)
	//{
	//	if (_kbhit()) {
	//		ch = _getch();
	//		switch (ch)
	//		{
	//		case 'f':
	//			set_feed_full_status(1);
	//			break;
	//		case 'w':
	//			set_water_full_status(1);
	//			break;
	//		case 'g':
	//			set_feed_full_status(0);
	//			break;
	//		case 'e':
	//			set_water_full_status(0);
	//			break;
	//		case 't':
	//			set_touch_status(1);
	//			break;
	//		default:
	//			printf("enter an invalid character: %c\n", ch);
	//			break;
	//		}
	//	}
	//	update_state_machine();
	//}

	print_cur_time();
	return 0;
}