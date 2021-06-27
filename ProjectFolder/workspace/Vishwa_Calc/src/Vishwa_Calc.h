/*
 * Vishwa_Calc.h
 *
 *  Created on: Jun 21, 2021
 *      Author: vishweshgm
 */

#ifndef VISHWA_CALC_H_
#define VISHWA_CALC_H_

#include <iostream>
#include <cstdio>
#include <conio.h>
#include "vartypes.h"
#include "string.h"
#include <stdlib.h>

using namespace std;
//#define DEBUG_MESSAGES

#define APPL_USER_INPUT_INST1_CHOICE_MAX	(1)

void OPT_1_AddressRangeCalculator(void);
void OPT_2_SizeInBetweenCalculator(void);
void OPT_3_PinAssignmentWizard(void);

s32 ConvertHexStringtoNumber(string str);
s32 ConvertDecStringtoNumber(string str);
s32 ConvertPostfixAbbrevToNumber(string str, u32 *Carry);
#endif /* VISHWA_CALC_H_ */
