/*
 * PinAssignmentWizard.c
 *
 *  Created on: Jun 27, 2021
 *      Author: vishweshgm
 */

#include "PinAssignmentWizard.h"

void OPT_3_PinAssignmentWizard(void){
	u8 PAW_u8Exit = 0;
	u8 PAW_u8Temp;
	PAW_ucVendor_enum PAW_ucVendor = PAW_RESERVED;
	do{
		cout << "Select Source Vendor\n\r1 : pIC\n\r2 : ST" << endl;
		cin >> PAW_u8Temp;
		PAW_ucVendor = (PAW_ucVendor_enum)PAW_u8Temp;
		/*EXIT CHECK*/
		cout << "\nAnother? Press Enter if Yes, else press any other key" << endl;
		cin.ignore();
		if (cin.get() != '\n'){
			PAW_u8Exit = 1;
			cout << "Something else key was pressed. Exiting to main Menu\n";
		}
		else
			PAW_u8Exit = 0;

	}while(PAW_u8Exit!=1);
}

