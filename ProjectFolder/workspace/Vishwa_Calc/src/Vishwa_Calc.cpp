//============================================================================
// Name        : Vishwa_Calc.cpp
// Author      : vishweshgm
// Version     :
// Copyright   : Please copy
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "Vishwa_Calc.h"
u8 Main_u8ExitAppl = 0;
int main() {
	string Appl_strUserInput;
	u8 Appl_u8UsrIpChoice;

	while(Main_u8ExitAppl != 1){
		Main_u8ExitAppl = 0;
		system("cls");
//		freopen( "output.log", "w", stdout);
		cout << "!!!Welcome to VISHWA_CALCULATOR!!\r\n" << endl;

		do{
			cout << "Choose Action you want to perform : " << endl;
			cout << "1. Calculate Address Range/End address from size and Start Point"<<endl;
			cout << "2. Calculate size between 2 hex address." << endl;
			cout << "3. Pin Assignment Wizard of Microcontrollers." << endl;
			cin >> Appl_u8UsrIpChoice;

		}while((Appl_u8UsrIpChoice == 0) && (Appl_u8UsrIpChoice > APPL_USER_INPUT_INST1_CHOICE_MAX));

#ifdef DEBUG_MESSAGES
		cout << Appl_u8UsrIpChoice << endl;
#endif

		switch(Appl_u8UsrIpChoice){
		case '1' : OPT_1_AddressRangeCalculator();break;
		case '2' : OPT_2_SizeInBetweenCalculator();break;
		case '3' : OPT_3_PinAssignmentWizard();break;;
		default : cout << "Sorry, Still Under Development" << endl; break;
		}
		cout << endl <<"\nThanks for using the Calculator. Press ENTER to Continue OR press N to stop" << endl;
		cin.ignore();
		if (cin.get() != '\n'){
			cout << "N Pressed\n";
			Main_u8ExitAppl = 1;
		}
		else
			Main_u8ExitAppl = 0;
	}
}

void OPT_1_AddressRangeCalculator(void){
	u8 ARC_u8Exit = 0;
	string ARC_strUserInput,ARC_strSize;
	s32 ARC_s32Startingaddress, ARC_s32size;
	s64 ARC_s64endAddress, ARC_s64size = 0;
	u32 ARC_u32BigSizeCarry = 0;
	do{
		/* STARTING ADDRESS PARSE*/
		ARC_u32BigSizeCarry = 0;
		ARC_s64size = 0;
		cout << "Enter the starting address(prefix '0x' for hex numbers) : "<< endl;
		cin >> ARC_strUserInput;
		if(ARC_strUserInput[0] == '0' &&
				((ARC_strUserInput[1] == 'x') || (ARC_strUserInput[1] == 'X'))){
			ARC_s32Startingaddress = ConvertHexStringtoNumber(ARC_strUserInput);
#ifdef DEBUG_MESSAGES
			cout << "ARC_Startingaddress = " << std::hex << ARC_s32Startingaddress << endl;
#endif
		}
		else{
			ARC_s32Startingaddress = ConvertDecStringtoNumber(ARC_strUserInput);
#ifdef DEBUG_MESSAGES
			cout << "ARC_Startingaddress = " << std::dec << ARC_s32Startingaddress << endl;
#endif
		}

		/* ADDRESS SIZE PARSE*/
		cout << "Enter the size(prefix '0x' for hex numbers) : "<< endl;
		cin >> ARC_strSize;

		if(ARC_strSize[0] == '0' &&
				((ARC_strSize[1] == 'x') || (ARC_strSize[1] == 'X'))){
			ARC_s32size = ConvertHexStringtoNumber(ARC_strSize);
			ARC_s64size = ARC_s32size;
		}
		else if((ARC_strSize[ARC_strSize.length()-1] == 'b') ||
				(ARC_strSize[ARC_strSize.length()-1] == 'B')){
			ARC_s32size = ConvertPostfixAbbrevToNumber(ARC_strSize, &ARC_u32BigSizeCarry);
			if(ARC_u32BigSizeCarry != 0){
				if(ARC_u32BigSizeCarry<= 255){
					for(unsigned int i = 0; i<4 ; i++){
						ARC_s64size+=ARC_u32BigSizeCarry*1073741824;
					}
					ARC_s64size += ARC_s32size;
				}
			}
			else
			{
				ARC_s64size = ARC_s32size;
			}
			cout << "ARC_s64size (HEX) = " << std::hex << ARC_s64size << endl;
			cout << "ARC_s64size (DEC) = " << std::dec << (u64)ARC_s64size << endl;
		}
		else{
			ARC_s32size = ConvertDecStringtoNumber(ARC_strSize);
			ARC_s64size = ARC_s32size;
		}


		/*Main Calculation*/
		ARC_s64endAddress = ARC_s32Startingaddress + ARC_s64size - 1;
		cout << endl << "Address Range is : " << endl;
		cout << "(In HEX) : " << std::hex << ARC_s32Startingaddress << " to " << flush;
		cout << std::hex << ARC_s64endAddress << endl;

		cout << "(In DEC) : " << std::dec << ARC_s32Startingaddress << " to " << flush;
		cout << ARC_s64endAddress << endl;

		/*EXIT CHECK*/
		cout << "Another? Press Enter if Yes, else press any other key" << endl;
		cin.ignore();
		if (cin.get() != '\n'){
			ARC_u8Exit = 0;
			cout << "Something else key was pressed. Exiting to main Menu\n";
		}
		else
			ARC_u8Exit = 1;
	}while(ARC_u8Exit!=0);



}

void OPT_2_SizeInBetweenCalculator(void){
	u8 SIB_u8Exit = 0;
	string SIB_strAddress1,SIB_strAddress2;
	s64 SIB_s64Address1 = 0, SIB_s64Address2 = 0;
	s32 SIB_s32ParsedNumber, SIB_s32SizeinBetween;

	do{
		/*FIRST ADDRESS PARSE*/
		cout << "Enter first address in hex : " << endl;
		cin >> SIB_strAddress1;

		if(SIB_strAddress1[0] == '0' &&
				((SIB_strAddress1[1] == 'x') || (SIB_strAddress1[1] == 'X'))){
			SIB_s32ParsedNumber = ConvertHexStringtoNumber(SIB_strAddress1);
		}
		else{
			SIB_s32ParsedNumber = ConvertDecStringtoNumber(SIB_strAddress1);
		}
		SIB_s64Address1 = SIB_s32ParsedNumber;

		/*SECOND ADDRESS PARSE*/
		cout << "Enter second address in hex : " << endl;
		cin >> SIB_strAddress2;

		if(SIB_strAddress2[0] == '0' &&
				((SIB_strAddress2[1] == 'x') || (SIB_strAddress2[1] == 'X'))){
			SIB_s32ParsedNumber = ConvertHexStringtoNumber(SIB_strAddress2);
		}
		else{
			SIB_s32ParsedNumber = ConvertDecStringtoNumber(SIB_strAddress2);
		}
		SIB_s64Address2 = SIB_s32ParsedNumber;

		/*MAIN CALCULATION*/
		if(SIB_s64Address2>SIB_s64Address1){
			SIB_s32SizeinBetween = SIB_s64Address2 - SIB_s64Address1+1;
		}
		else{
			SIB_s32SizeinBetween = SIB_s64Address1 - SIB_s64Address2+1;
		}

		cout << "difference is (in hex) :" << std::hex << SIB_s32SizeinBetween << endl;
		cout << "difference is (in dec) :" << std::dec << SIB_s32SizeinBetween << "Bytes --> " <<flush;
		cout << (SIB_s32SizeinBetween/1024.0) << "KBytes --> " <<flush;
		cout << (SIB_s32SizeinBetween/1048576.0) << "MBytes" <<flush;
		/*EXIT CHECK*/
		cout << "\nAnother? Press Enter if Yes, else press any other key" << endl;
		cin.ignore();
		if (cin.get() != '\n'){
			SIB_u8Exit = 1;
			cout << "Something else key was pressed. Exiting to main Menu\n";
		}
		else
			SIB_u8Exit = 0;
	}while(SIB_u8Exit!=1);
}

s32 ConvertHexStringtoNumber(string str){
	char charArray[100];
	strcpy(charArray, str.c_str());
	return (s32)strtol(&charArray[2], NULL, 16);
}

s32 ConvertDecStringtoNumber(string str){
	char charArray[100];
	strcpy(charArray, str.c_str());
	return (s32)strtol(charArray, NULL, 10);
}

s32 ConvertPostfixAbbrevToNumber(string str, u32 *Carry){
	char charArray[100];
	char *CPATN_charpostfixArray;
	s32 CPATN_s32tempSize;
	strcpy(charArray, str.c_str());
	CPATN_s32tempSize = (s32)strtol(charArray, &CPATN_charpostfixArray, 10);
#ifdef DEBUG_MESSAGES
	cout << "CPATN_s32tempSize = " << CPATN_s32tempSize << endl;
	cout << "CPATN_charpostfixArray = " << CPATN_charpostfixArray[0] << endl;
#endif
	/*GB*/
	if(((CPATN_charpostfixArray[0] == 'G' || CPATN_charpostfixArray[0] == 'g')) &&
			((CPATN_charpostfixArray[1] == 'B') || (CPATN_charpostfixArray[1] == 'b'))){
		if(CPATN_s32tempSize >= 4){
			/*In this case, above result is 4294967296 which is 1 higher than 2^32-1*/
			*Carry = CPATN_s32tempSize/4;
			CPATN_s32tempSize = CPATN_s32tempSize%4;
		}
		CPATN_s32tempSize = CPATN_s32tempSize * 1024 * 1024 * 1024;
	}
	/*MB*/
	else if(((CPATN_charpostfixArray[0] == 'M' || CPATN_charpostfixArray[0] == 'm')) &&
			((CPATN_charpostfixArray[1] == 'B') || (CPATN_charpostfixArray[1] == 'b'))){
		CPATN_s32tempSize = CPATN_s32tempSize * 1024 * 1024 * 1;
	}
	/*KB*/
	else if(((CPATN_charpostfixArray[0] == 'K' || CPATN_charpostfixArray[0] == 'k')) &&
			((CPATN_charpostfixArray[1] == 'B') || (CPATN_charpostfixArray[1] == 'b'))){
		CPATN_s32tempSize = CPATN_s32tempSize * 1024 * 1 * 1;
	}
	else
	{
		CPATN_s32tempSize = 0xDEADBEEF;
	}
	return CPATN_s32tempSize;
}
