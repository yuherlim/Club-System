#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>
#pragma warning (disable:4996)
#pragma warning (disable:6031)

//global variables to check start and next action
char startYOrNo, nextYOrNo;

struct Date {
	int day, month, year;
};

//Structure declaration of staff details
struct Account {
	char id[7], password[30], recoveryQues[80], recoveryAns[80];
};

struct Staff {
	struct Account sAccount;
	char name[46], icNum[13], gender, contactNum[12];
	struct Date dateJoined, birthDate;
	char position[20], status[9];
};

//Structure declaration of facility details
typedef struct {
	char staffID[8], facilityID[5], types[11], description[21], venue[11];
	int maximumUsers;
	float normalPrice, vipPrice;
	struct Date d;
}Facility;

/*Booking module structure*/
//Structure to store booking details.
typedef struct {
	char bookingId[6], memberId[10], facilityId[5], staffId[7];
	struct Date bookedDate, transactionDate, refundDate;
	char bookedTime[12];
	int duration;
	char bookedFacility[11], remarks[22];
	float bookingPrice;
	char memType[7];
} Booking;

//Structure to store specific booking details for comparison.
typedef struct {
	char facilityId[5];
	int timeSlotNo, duration;
	char bookedTime[12];
} BookingComparison;

//Structure declaration of member details
//Member infomation structure
struct MemberInfo {
	char memID[10], memIC[13], memName[41], memGender, memAdd[101], memPhoneNo[12];
	struct Date memBirthDate;
	char memType[7];
	struct Date memExpiry;
	char memstatus[9];
	char staffID[7];
	struct Date memRegister;
	int vipDuration;
	int normalDuration;
};

//Facility Module structure
typedef struct {
	char facUseID[5], memberID[10], memberIC[13], facEvent[11], facID[5], staffID[7], usageType[8], remarks[99];
	char walkInTime[12];
	struct Date walkInDate;
	int walkInDuration;
	char memberType[7];
	float walkInPrice;
} facilityUsage;


/*Genaral Function*/
void StringInput(char passedString[], int lengthOfArray);
char CharInput();
int IntInput();
char YesNoValidation(char yesNoChar);
void MonthInput(int* month);
void TimeInput(char* tInput);

int FacilityIDValidation(char facilityID[]);
int FacilityIdAndDesc(char facilityID[], char description[]);
int AlphabetCheck(char string[]);
void UppercaseFunction(char string[]);
float FloatInput();

int DateInput(int* day, int* month, int* year, char selection[]);
int CurrentDate(char selection[]);
void DateExtract(char passedString[], char dateFormat[], int startPosition, int* passedDay, int* passedMonth, int* passedYear);
int AgeCalc(int day, int month, int year);
char IcInfo(char icNum[], char selection[]);
void staffIDInput(char staffID[]);

int MemberSearching(struct MemberInfo* member);
int MemberModuleMenu(char staffID[]);
int MemberReportMenu(char staffID[]);
int MemberStatusReportMenu(char staffID[]);
int MemberLoyaltyReportMenu(char staffID[]);
void MemberInputSelection(struct MemberInfo* memberInput, char staffID[]);
void MemberICInput(char memIC[]);
void MemberNameInput(char memName[]);
void MemberGenderInput(char* gender, char memIC[]);
void MemberAddressInput(char memAdd[]);
void MemberPhoneInput(char memPhoneNo[]);
int MemberBirthDateInput(int* day, int* month, int* year, char memIC[]);
void MemberTypeInput(char memType[], double* memberPrice, double normalMemPrice, double vipMemPrice);
void MembershipDurationInput(int* membershipDuration, int* memExpiryDay, int* memExpiryMonth, int* memExpiryYear, char selection[]);
void MemberLoyaltyReport(char selection[]);
void MemberStatusReport(char selection[]);
void MemberDurationReport();
void MemberInfoDisplay(struct MemberInfo memberDisplay);
void MemberInvoice(struct MemberInfo memberInvoice, int membershipDuration, double membershipPrice, double refund);
void UpdateMemberDetails(struct MemberInfo updateMember, char selection[]);
void DurationCalc(int startDay, int startMonth, int startYear, int endDay, int endMonth, int endYear, int* durationDay, int* durationMonth, int* durationYear, int* totalDurationDay, char selection[]);

void BookingIDInput(char bookingId[]);
void BookingIDInput(char bookingId[]);
void CreateTimeObj(int day, int month, int year, time_t* timeObj);

int BookingMenu(char* staffId, char* staffName);
void BookingHeader(char* staffId, char* staffName, int currentSelection);
int BookingCount();
void ReadBookingList(Booking bk[], int size, int* bCount);
void SelectBookingFacility(char* facilityName);
int SelectTimeSlot(Booking* uInput);
void RemarksInput(char remarks[]);
void BookingDateInput(int* day, int* month, int* year);
void SearchForBookedTimeInput(char* timeString);
void PrintfBookingRecord(char searchStr[], char selection, Booking bkPrinted[], int* printCount);
void BookingTableHeader();
void PrintSingleRecord(Booking bk);
void RefundTableHeader();
void PrintSingleRefundRecord(Booking refundRecord);
void FprintBookingTableHeader(FILE* fp);
void FprintSingleRecord(Booking bk, FILE* fp);
void FprintRefundTableHeader(FILE* fp);
void FprintSingleRefundRecord(Booking refundRecord, FILE* fp);

void YearlyFacUseSummary();
void DailyFacUseSummary();
void MonthlyFacUseSummary();
int WalkInCount();
int SelectWalkInTimeSlot(facilityUsage* uInput);
void SelectWalkInFacilityName(char* facilityName);
int LastFacilityUseID();


/*Out of Module Function declarations*/
int MainMenu();
void StaffLogin(char staffID[]);
void CreatePassword(char password[]);
void CreateQnA(char recoveryQues[], char recoveryAns[]);
char RecoveryPassword(char password[], char recoveryQues[], char recoveryAns[]);

/*Staff Information Module Function declarations*/
void StaffModule(char staffIDLogin[]);
int StaffMenu();
void AddStaff(int staffCount);
void SearchStaff();
void ModifyStaff(char staffID[]);
void DisplayStaff();
void ResignStaff(char staffID[]);
void StaffReport();

/*Facility Module Function declarations*/
void FacilityModule(char staffId[]);
void AddFacilities(char staffID[]);
void SearchFacilities();
void ModifyFacilities();
void DisplayFacilities();
void DeleteFacilities();
void FacilitiesReport();

/*Member Information Module Functions declarations*/
void MemberModule(char staffID[]);
void AddMember(int* memberNo, double normalMemPrice, double vipMemPrice, char staffID[]);
void SearchMember(char staffId[]);
void ModifyMember(char staffID[]);
void DisplayMember(char staffID[]);
void MembershipManagement(double normalMemPrice, double vipMemPrice, char staffID[]);
void MembershipReport(char staffID[]);

/*Booking Module Function declarations*/
void BookingModule(char staffIDLogin[]);
void AddBooking(char* staffId, char* staffName);
char SearchBooking(char* staffId, char* staffName, char funcName[], Booking bkPrinted[], int* printCount);
void ModifyBooking(char* staffId, char* staffName);
void DisplayBooking(char* staffId, char* staffName, char* selection);
void CancelBooking(char* staffId, char* staffName);
void MonthlyBookingSummary(char* staffId, char* staffName);

/*Facility Usage Module Functions declarations*/
void FacilityUsageModule(char* staffIDLogin);
void AddFacilityUsage(char* staffIDLogin);
void DisplayFacilityUsageHistory(char* staffIDLogin);
void SearchFacilityUsageHistory(char* staffIDLogin);
void ModifyFacilityUsageHistory(char* staffIDLogin);
void DeleteFacilityUsageHistory(char* staffIDLogin);
void FacilityUsageSummary(char* staffIDLogin);

void main() {
	char staffIDLogin[8];
	int selectionMain, selection;
	struct MemberInfo member = { 0 };

	do {
		//Update member status
		UpdateMemberDetails(member, "expiry");

		//company header
		printf("\t\t-------------\n");
		printf("\t\t | Clubruh |\n");
		printf("\t\t-------------\n");
		printf("\n");

		//exit program or login
		printf("\t1 - Login\n");
		printf("\t2 - Exit\n");
		printf("\t-------------\n");
		printf("\tSelection : ");
		selection = IntInput();

		//range validation
		while (selection != 1 && selection != 2) {
			printf("\tPlease ensure your selection is (1 or 2).\n");
			printf("\tSelection : ");
			selection = IntInput();
		}

		if (selection == 1) {
			//staff login
			StaffLogin(staffIDLogin);
			printf("\n");
			system("\tpause");
			system("cls");
		}
		else
			break;

		do {
			system("cls");
			//main menu to access all 5 modules
			selectionMain = MainMenu();
			switch (selectionMain) {
			case 1:
				StaffModule(staffIDLogin);
				break;
			case 2:
				FacilityModule(staffIDLogin);
				break;
			case 3:
				MemberModule(staffIDLogin);
				break;
			case 4:
				BookingModule(staffIDLogin);
				break;
			case 5:
				FacilityUsageModule(staffIDLogin);

				break;
			case 0:
				printf("\tLogging out now...\n");
				break;
			default:
				printf("\tPlease ensure your selection is (0 - 5).\n");
			}
		} while (selectionMain != 0);

	} while (selection == 1);

	system("\tpause");
}

/*--------------Staff Information Module Function Definitions------------*/
/// <summary>
/// Staff information module
/// </summary>
/// <param name="">Staff ID login</param>
void StaffModule(char staffIDLogin[]) {
	struct Staff clubStaff;

	int selectionMenu, numStaff, numOfRecord;			//get the number of staff from .bin file

	do {
		//get number of staff, record and info all staff from bit file
		FILE* fileStaff;
		fileStaff = fopen("StaffInfo.bin", "rb");

		if (fileStaff == NULL) {			//if first time open, no file
			printf("<Creating \"StaffInfo.bin\">\n");
			fileStaff = fopen("StaffInfo.bin", "wb");
			fclose(fileStaff);
			fileStaff = fopen("StaffInfo.bin", "rb");
		}

		numStaff = 0;
		numOfRecord = 0;

		//get num of record and num of staff
		while (!feof(fileStaff)) {
			fread(&clubStaff, sizeof(clubStaff), 1, fileStaff);
			if (feof(fileStaff))
				break;
			if (strcmp(clubStaff.status, "ACTIVE") == 0 || strcmp(clubStaff.status, "UNACTIVE") == 0 || strcmp(clubStaff.status, "RESIGN") == 0)
				numOfRecord++;
			if (strcmp(clubStaff.status, "ACTIVE") == 0 || strcmp(clubStaff.status, "UNACTIVE") == 0)
				numStaff++;
		}
		fclose(fileStaff);

		//Prompt and get the selection of staff info
		selectionMenu = StaffMenu();
		switch (selectionMenu) {
		case 1:
			AddStaff(numOfRecord);
			break;
		case 2:
			SearchStaff();
			break;
		case 3:
			ModifyStaff(staffIDLogin);
			break;
		case 4:
			DisplayStaff();
			break;
		case 5:
			ResignStaff(staffIDLogin);
			break;
		case 6:
			StaffReport();
			break;
		case 0:
			printf("\tBack to main menu\n");
			break;
		default:
			printf("\tPlease ensure your selection is (0 - 6).\n");
			break;
		}
	} while (selectionMenu != 0);

	system("\tpause");
}

/// <summary>
/// Sub-menu for staff info module
/// </summary>
/// <returns>selection</returns>
int StaffMenu() {
	int selection;

	//Logo

	//Header
	printf("\t----------------\n");
	printf("\t | Staff Info |\n");
	printf("\t----------------\n\n");

	//Prompt menu and get selection
	printf("\t1 - Add a new staff\n");
	printf("\t2 - Search a staff\n");
	printf("\t3 - Edit own info\n");
	printf("\t4 - Display all staff\n");
	printf("\t5 - Delete staff\n");
	printf("\t6 - Staff Report\n\n");

	printf("\t0 - Main Menu\n\n");

	printf("\t--------------------------\n");
	printf("\tEnter selection : ");
	selection = IntInput();

	system("cls");

	return selection;
}

/// <summary>
/// Add a new staff
/// </summary>
/// <param name="staffCount">Number of staff ACTIVE and UNACTIVE</param>
void AddStaff(int staffCount) {
	struct Staff addStaffSave;
	char next;
	int yearNow;

	time_t now;
	time(&now);
	ctime(&now);
	struct tm* timeLocal = localtime(&now);

	//Header
	printf("\t---------------\n");
	printf("\t | Add staff |\n");
	printf("\t---------------\n\n");

	//Prompt and get new staff information
	//Name
	printf("Name (same as IC) : ");
	StringInput(addStaffSave.name, 46);

	//IC Number
	printf("Malaysia IC Number (without -) : ");
	addStaffSave.gender = IcInfo(addStaffSave.icNum, "ic input");

	//Birth date
	printf("Birth date: \n");
	DateInput(&addStaffSave.birthDate.day, &addStaffSave.birthDate.month, &addStaffSave.birthDate.year, "date input");

	//Contact Number
	printf("Contact Number (without -) : ");
	StringInput(addStaffSave.contactNum, 12);

	//Position
	printf("Position : ");
	StringInput(addStaffSave.position, 20);

	//Date Joined
	printf("Date Joined : \n");
	DateInput(&addStaffSave.dateJoined.day, &addStaffSave.dateJoined.month, &addStaffSave.dateJoined.year, "date input");

	//Calculate present year and birth year
	yearNow = timeLocal->tm_year + 1900;

	//Show new staff infomation
	printf("\n----------------------------------------------\n\n");
	sprintf(addStaffSave.sAccount.id, "ST-%03d", staffCount + 1);
	printf("Staff ID : %s\n", addStaffSave.sAccount.id);
	printf("Name : %s\n", addStaffSave.name);
	printf("IC : %s\n", addStaffSave.icNum);
	printf("Gender : %c\n", addStaffSave.gender);
	printf("Birth Date : %02d/%02d/%d\n", addStaffSave.birthDate.day, addStaffSave.birthDate.month, addStaffSave.birthDate.year);
	printf("Age : %d\n", yearNow - addStaffSave.birthDate.year);
	printf("Contact number : %s\n\n", addStaffSave.contactNum);

	printf("Position : %s\n", addStaffSave.position);
	printf("Date Joined : %02d/%02d/%d\n\n", addStaffSave.dateJoined.day, addStaffSave.dateJoined.month, addStaffSave.dateJoined.year);

	printf("\n----------------------------------------------\n\n");
	//Comfirm add staff?
	printf("Comfirm to add new staff <Staff ID> ?\n");
	printf("(Y)es/(N)o : ");
	rewind(stdin);
	scanf("%c", &next);
	next = YesNoValidation(toupper(next));

	if (toupper(next) == 'Y') {
		sprintf(addStaffSave.sAccount.id, "ST-%03d", ++staffCount);					//genrate staff id
		strcpy(addStaffSave.status, "UNACTIVE");

		FILE* staffFile;
		staffFile = fopen("StaffInfo.bin", "ab");

		//write into bit file
		if (staffFile == NULL)
			printf("\t<Unable to open \"StaffInfo.bin\">\n");
		else {
			fwrite(&addStaffSave, sizeof(addStaffSave), 1, staffFile);
			fclose(staffFile);
			printf("\t< Staff created successful >\n\n");
		}
	}
	else
		printf("\t< Staff add failed... >\n\n");

	system("pause");
	system("cls");
}

/// <summary>
/// 
/// </summary>
void SearchStaff() {
	struct Staff searchStaffSave;
	char nameEntered[50], next;
	FILE* fStaff;
	int yearNow;

	//Header
	printf("\t------------------\n");
	printf("\t | Search staff |\n");
	printf("\t------------------\n\n");

	do {
		//Prompt and get name
		printf("Please enter staff name : ");
		StringInput(nameEntered, 50);

		//scan file compare name
		fStaff = fopen("StaffInfo.bin", "rb");

		while (!feof(fStaff)) {
			fread(&searchStaffSave, sizeof(searchStaffSave), 1, fStaff);
			if (strcmp(nameEntered, searchStaffSave.name) == 0)
				break;
		}
		fclose(fStaff);

		time_t now;
		time(&now);
		ctime(&now);
		struct tm* timeLocal = localtime(&now);
		//Calculate present year and birth year
		yearNow = timeLocal->tm_year + 1900;

		//Display
		if (strcmp(nameEntered, searchStaffSave.name) == 0) {
			printf("Staff ID : %s\n", searchStaffSave.sAccount.id);
			printf("Name : %s\n", searchStaffSave.name);
			printf("IC : %s\n", searchStaffSave.icNum);
			printf("Gender : %c\n", searchStaffSave.gender);
			printf("Birth Date : %02d/%02d/%d\n", searchStaffSave.birthDate.day, searchStaffSave.birthDate.month, searchStaffSave.birthDate.year);
			printf("Age : %d\n", yearNow - searchStaffSave.birthDate.year);
			printf("Contact number : %s\n\n", searchStaffSave.contactNum);

			printf("Position : %s\n", searchStaffSave.position);
			printf("Date Joined : %02d/%02d/%d\n\n", searchStaffSave.dateJoined.day, searchStaffSave.dateJoined.month, searchStaffSave.dateJoined.year);
		}
		else
			printf("No record found.\n");

		//continue search?
		printf("Search another staff?\n");
		printf("(Y)es/(N)o : ");
		rewind(stdin);
		scanf("%c", &next);
		next = YesNoValidation(toupper(next));

	} while (next == 'Y');
}

/// <summary>
/// 
/// </summary>
/// <param name="staffID"></param>
void ModifyStaff(char staffID[]) {
	struct Staff modifyStaff;
	struct Staff modifySave;
	FILE* fStaff;

	char next, idEdit[7];
	int selection;

	//scan file get position from staffID
	fStaff = fopen("StaffInfo.bin", "rb");

	while (!feof(fStaff)) {
		fread(&modifyStaff, sizeof(modifyStaff), 1, fStaff);
		if (strcmp(staffID, modifyStaff.sAccount.id) == 0)
			break;
	}
	fclose(fStaff);

	//Human resource staff or normal staff
	if (strcmp(modifyStaff.position, "Human Resource") == 0) {		//Human resource staff change can all staff's info
		printf("Enter Staff ID need to changes : \n");
		staffIDInput(idEdit);
		
		//scan file to get the info for that staff
		fStaff = fopen("StaffInfo.bin", "rb");

		while (!feof(fStaff)) {
			fread(&modifyStaff, sizeof(modifyStaff), 1, fStaff);
			if (strcmp(idEdit, modifyStaff.sAccount.id) == 0)
				break;
		}
		fclose(fStaff);

		printf("\t------------------------\n");
		printf("\t | Edit %s\'s info |\n", idEdit);
		printf("\t------------------------\n\n");
	}
	else {
		strcpy(idEdit, staffID);

		printf("\t-------------------\n");
		printf("\t | Edit own info |\n");
		printf("\t-------------------\n\n");
	}

	do {
		printf("\t1 - Name\n");
		printf("\t2 - IC\n");
		printf("\t3 - Birth Date\n");
		printf("\t4 - Contact Number\n");
		printf("\t5 - Position\n");
		printf("\t6 - Date Joined\n");
		printf("\t7 - Password\n");
		printf("\t8 - Recovery QnA\n\n");

		printf("\t9 - Save edit\n");
		printf("\t0 - Back to previous menu\n");
		printf("\t----------------------------\n\n");

		printf("\tSelection : ");
		selection = IntInput();

		printf("\n\n");

		switch (selection) {
		case 1:
			printf("Edit Name : ");
			StringInput(modifyStaff.name, 50);
			break;
		case 2:
			printf("Edit IC : ");
			IcInfo(modifyStaff.icNum, "ic input");
			break;
		case 3:
			printf("Edit Birth date (DD/MM/YYYY) : ");
			DateInput(&modifyStaff.birthDate.day, &modifyStaff.birthDate.month, &modifyStaff.birthDate.year, "date input");
			break;
		case 4:
			printf("Enter New Contact Number (without -) : ");
			StringInput(modifyStaff.contactNum, 12);
			break;
		case 5:
			printf("Enter New Position : ");
			StringInput(modifyStaff.position, 20);
			break;
		case 6:
			printf("Edit Date Joined (DD/MM/YY) : ");
			DateInput(&modifyStaff.dateJoined.day, &modifyStaff.dateJoined.month, &modifyStaff.dateJoined.year, "date input");
			break;
		case 7:
			CreatePassword(modifyStaff.sAccount.password);
			break;
		case 8:
			CreateQnA(modifyStaff.sAccount.recoveryQues, modifyStaff.sAccount.recoveryAns);
			break;
		case 9:
			printf("Saving...\n");
			break;
		case 0:
			printf("Back to previous menu without changing? (Y)es/(N)o : ");
			scanf("%c", &next);
			next = YesNoValidation(toupper(next));
			break;
		}

		if (selection == 0) {
			printf("Back to previous menu without chages.\n\n");
			return;
		}

		printf("\nChange another edit field? (Y)es/(N)o : ");
		scanf("%c", &next);
		next = YesNoValidation(toupper(next));

	} while (next == 'Y');

	printf("\n----------------------------------------------\n\n");
	//print all field
	printf("Staff ID : %s\n", modifyStaff.sAccount.id);
	printf("Name : %s\n", modifyStaff.name);
	printf("IC : %s\n", modifyStaff.icNum);
	printf("Gender : %c\n", modifyStaff.gender);
	printf("Birth Date : %02d/%02d/%d\n", modifyStaff.birthDate.day, modifyStaff.birthDate.month, modifyStaff.birthDate.year);
	printf("Contact number : %s\n\n", modifyStaff.contactNum);

	printf("Position : %s\n", modifyStaff.position);
	printf("Date Joined : %02d/%02d/%d\n\n", modifyStaff.dateJoined.day, modifyStaff.dateJoined.month, modifyStaff.dateJoined.year);

	printf("Password : %s\n", modifyStaff.sAccount.password);
	printf("Security Question : %s\n", modifyStaff.sAccount.recoveryQues);
	printf("Security Answer : %s\n", modifyStaff.sAccount.recoveryAns);
	printf("\n----------------------------------------------\n\n");

	//Comfirmation edit
	printf("Confirm edit all these field? (Y)es/(N)o : ");
	scanf("%c", &next);
	next = YesNoValidation(toupper(next));

	//if QnA success 'S', write the new password to file
	if (next == 'Y') {
		FILE* fEdit;
		fStaff = fopen("StaffInfo.bin", "rb");									//open file
		fEdit = fopen("StaffInfoTemp.bin", "wb");								//open temp file
		while (!feof(fStaff)) {
			fread(&modifySave, sizeof(modifySave), 1, fStaff);					//read line by line
			if (feof(fStaff))
				break;

			if (strcmp(modifySave.sAccount.id, idEdit) == 0) 					//id selected indicate
				fwrite(&modifyStaff, sizeof(modifyStaff), 1, fEdit);			//assign edited line
			else
				fwrite(&modifySave, sizeof(modifySave), 1, fEdit);				//write line by line until eof
		}
		fclose(fStaff);
		fclose(fEdit);
		//replace temp file to main file
		remove("StaffInfo.bin");
		rename("StaffInfoTemp.bin", "StaffInfo.bin");
	}
	else
		printf("Back to previous menu without chages.\n\n");

	system("pause");
	system("cls");
}

/// <summary>
/// Display all staff or not Resign
/// </summary>
void DisplayStaff() {
	struct Staff displayStaff;
	int selection;

	printf("\t-------------------\n");
	printf("\t | Display staff |\n");
	printf("\t-------------------\n\n");

	printf("\t1 - Show staff only\n");
	printf("\t2 - Show all records (include RESIGNed staff)\n");

	printf("\tSelction : ");
	selection = IntInput();

	FILE* fShow;
	fShow = fopen("StaffInfo.bin", "rb");

	printf("\n\n");

	if (fShow == NULL)
		printf("\t<Unable to open \"StaffInfo.bin\">\n");
	else {
		//printf column header
		printf("Staff ID  Name\t\t\t\t\t\t Gender  Contact Num  Date Joined  Position             Status\n");
		printf("========  ====\t\t\t\t\t\t ======  ===========  ===========  ========             ======\n");

		while (!feof(fShow)) {
			fread(&displayStaff, sizeof(displayStaff), 1, fShow);
			if (feof(fShow))
				break;

			switch (selection) {
			case 1:
				if (strcmp(displayStaff.status, "RESIGN") != 0) {
					printf("%-8s  %-45s  %3c     %-11s  %02d/%02d/%d   %-19s  %-8s\n", displayStaff.sAccount.id, displayStaff.name, displayStaff.gender, displayStaff.contactNum,
						displayStaff.dateJoined.day, displayStaff.dateJoined.month, displayStaff.dateJoined.year, displayStaff.position, displayStaff.status);
				}
				break;
			case 2:
				printf("%-8s  %-45s  %3c     %-11s  %02d/%02d/%d   %-19s  %-8s\n", displayStaff.sAccount.id, displayStaff.name, displayStaff.gender, displayStaff.contactNum,
					displayStaff.dateJoined.day, displayStaff.dateJoined.month, displayStaff.dateJoined.year, displayStaff.position, displayStaff.status);
				break;
			}
		}

		fclose(fShow);
	}
	printf("\n\n");
	system("pause");
	system("cls");
}

/// <summary>
/// 
/// </summary>
/// <param name="staffID"></param>
void ResignStaff(char staffID[]) {
	struct Staff resignStaff;
	struct Staff adminStaff;
	char staffIDResign[8], next;
	FILE* fStaff;

	//scan file get position from staffID
	fStaff = fopen("StaffInfo.bin", "rb");

	while (!feof(fStaff)) {
		fread(&adminStaff, sizeof(adminStaff), 1, fStaff);

		if (feof(fStaff))
			break;
		if (strcmp(staffID, adminStaff.sAccount.id) == 0)
			break;
	}
	fclose(fStaff);

	printf("\t------------------\n");
	printf("\t | Resign Staff |\n");
	printf("\t------------------\n");

	//Human resource staff or normal staff
	if (strcmp(adminStaff.position, "Human Resource") == 0) {		//Human resource staff change can all staff's info
		printf("Enter staff ID : \n");
		staffIDInput(staffIDResign);

		fStaff = fopen("StaffInfo.bin", "rb");
		while (!feof(fStaff)) {
			fread(&resignStaff, sizeof(resignStaff), 1, fStaff);					//read line by line
			if (feof(fStaff)) {
				printf("No ID found.\n");
				break;
			}
			if (strcmp(resignStaff.sAccount.id, staffIDResign) == 0)
				break;
		}
		fclose(fStaff);

		printf("\n");
		printf("Staff ID : %s\n", resignStaff.sAccount.id);
		printf("Name     : %s\n", resignStaff.name);

		printf("Sure resign? (Y)es/(N)o : ");
		scanf("%c", &next);
		next = YesNoValidation(next);

		//if QnA success 'S', write the new status to file
		if (next == 'Y') {
			FILE* fResign;
			fStaff = fopen("StaffInfo.bin", "rb");									//open file
			fResign = fopen("StaffInfoTemp.bin", "wb");								//open temp file
			while (!feof(fStaff)) {
				fread(&resignStaff, sizeof(resignStaff), 1, fStaff);					//read line by line
				if (feof(fStaff))
					break;
				if (strcmp(resignStaff.sAccount.id, staffIDResign) == 0) { 				//id selected indicate
					strcpy(resignStaff.status, "RESIGN");								//change status to resign
					fwrite(&resignStaff, sizeof(resignStaff), 1, fResign);				//assign edited line
				}
				else
					fwrite(&resignStaff, sizeof(resignStaff), 1, fResign);				//write line by line until eof
			}
			fclose(fStaff);
			fclose(fResign);
			//replace temp file to main file
			remove("StaffInfo.bin");
			rename("StaffInfoTemp.bin", "StaffInfo.bin");
		}
		else
			printf("Back to previous menu without chages.\n\n");
	}
	else
		printf("Only \"Human Resource\" have the permission to change status.\n");

	system("pause");
	system("cls");
}

/// <summary>
/// 
/// </summary>
void StaffReport() {
	struct Staff reportStaff;
	int selection;

	printf("\t------------------\n");
	printf("\t | Staff Report |\n");
	printf("\t------------------\n\n");

	printf("\t1 - Staff Reports only\n");
	printf("\t2 - All Records Report (include resigned staff)\n");

	printf("\tSelction > ");
	selection = IntInput();

	FILE* fShow;
	FILE* fReport;
	fShow = fopen("StaffInfo.bin", "rb");
	fReport = fopen("StaffReport.txt", "w");

	printf("\n\n");

	if (fShow == NULL)
		printf("\t<Unable to open \"StaffInfo.bin\">\n");
	else {
		//printf column header
		fprintf(fReport, "==================\n");
		fprintf(fReport, " | Staff Report |\n");
		fprintf(fReport, "==================\n");
		fprintf(fReport, "Staff ID  Name\t\t\t\t\t\t Gender  Contact Num  Date Joined  Position             Status\n");
		fprintf(fReport, "========  ====\t\t\t\t\t\t ======  ===========  ===========  ========             ======\n");

		while (!feof(fShow)) {
			fread(&reportStaff, sizeof(reportStaff), 1, fShow);
			if (feof(fShow))
				break;

			switch (selection) {
			case 1:
				if (strcmp(reportStaff.status, "RESIGN") != 0) {
					fprintf(fReport, "%-8s  %-45s  %3c     %-11s  %02d/%02d/%d   %-19s  %-8s\n", reportStaff.sAccount.id, reportStaff.name, reportStaff.gender, reportStaff.contactNum,
						reportStaff.dateJoined.day, reportStaff.dateJoined.month, reportStaff.dateJoined.year, reportStaff.position, reportStaff.status);
				}
				break;
			case 2:
				fprintf(fReport, "%-8s  %-45s  %3c     %-11s  %02d/%02d/%d   %-19s  %-8s\n", reportStaff.sAccount.id, reportStaff.name, reportStaff.gender, reportStaff.contactNum,
					reportStaff.dateJoined.day, reportStaff.dateJoined.month, reportStaff.dateJoined.year, reportStaff.position, reportStaff.status);
				break;
			}
		}

		fclose(fShow);
		fclose(fReport);
	}
	printf("\t==========================================================================================================================\n");
	printf("\t<Report \"StaffReport.txt\" Generated >...\n\n");
	printf("\n\n");
	system("\tpause");
	system("cls");
}

/*------------------Facility Module Function Definitions------------------*/
/// <summary>
/// Function that do all the facilities things
/// </summary>
void FacilityModule(char staffId[]) {
	//Variable for menu selection declaration
	int menuSelection;

	//Do-while loop to exit when user enter 0
	do {

		//Header
		printf("\t-------------------------\n");
		printf("\t|   Facilities Module   |\n");
		printf("\t-------------------------\n");
		printf("\t------------------------\n");
		printf("\t|         Menu         |\n");
		printf("\t------------------------\n");

		//Show menu
		printf("\t1 - Add Facilities\n");
		printf("\t2 - Search Facilities\n");
		printf("\t3 - Modify Facilities\n");
		printf("\t4 - Display Facilities\n");
		printf("\t5 - Delete Facilities\n");
		printf("\t6 - Facilities Report\n");
		printf("\t0 - Exit\n");
		printf("\t--------------------------\n");

		//Prompt and get the user selection
		printf("\tEnter Selection : ");
		menuSelection = IntInput();

		//Get the integer that user enter and enter the condition
		switch (menuSelection) {
		case 0: //If user enter 0
			//Display end message
			printf("\t\tThank You...Exit...\n");
			break;
		case 1: //If user enter 1
			system("cls");
			//Call add facilities function
			//staffID
			AddFacilities(staffId);
			break;
		case 2: //If user enter 2
			system("cls");
			//call search facilities function
			SearchFacilities();
			break;
		case 3: //if user enter 3
			system("cls");
			//call modify facilities function
			ModifyFacilities();
			break;
		case 4: //if user enter 4
			system("cls");
			//call display facilities function
			DisplayFacilities();
			break;
		case 5: //if user enter 5
			system("cls");
			//call delete facilities function
			DeleteFacilities();
			break;
		case 6: //if user enter 6
			system("cls");
			//call facilities report function
			FacilitiesReport();
			break;
		default: //if user enter number beside(1-6)
			system("cls");
			//display error message
			printf("\t\tWrong input.Please Reenter your selection.\n");
		}
	} while (menuSelection != 0); //repeat the loop if user selection is not 0
	system("\tpause");
	system("cls");
}

/// <summary>
/// Function that add the facilities
/// </summary>
void AddFacilities(char staffID[]) {

	//Display header
	printf("\t----------------------\n");
	printf("\t|   Add Facilities   |\n");
	printf("\t----------------------\n");

	rewind(stdin);

	//Prompt and get whether user want to start to add facilities or not
	printf("\tEnter 'Y' to add facilities : ");
	scanf("%c", &startYOrNo);

	startYOrNo = toupper(startYOrNo);

	//Do the validation to check whether the user input is correct or not
	startYOrNo = YesNoValidation(startYOrNo);
	printf("\n");

	//Enter loop when user enter 'Y'
	while (startYOrNo == 'Y') {

		//Do-while loop to continue add facility if user input 'Y'
		do {

			//Variable declaration for structure
			Facility addFac;
			Facility fac;
			int idVal, typeVal, descVal, venueVal;

			//If the user enter 'Y' when ask to add next facility
			if (nextYOrNo == 'Y') {

				//Display header
				printf("\t----------------------\n");
				printf("\t|   Add Facilities   |\n");
				printf("\t----------------------\n");

			}
			strcpy(addFac.staffID, staffID);

			//Do-while loop to check whether the facility ID is duplicate or not
			do {

				//Do-while loop to check whether the input is correct or not
				do {

					//initialize the idVal to 0;
					idVal = 0;

					//prompt and get the facility ID
					printf("\tFacility ID : ");
					StringInput(addFac.facilityID, 10);

					//do validation for facility ID
					idVal = FacilityIDValidation(addFac.facilityID);

				} while (idVal == 1);

				idVal = 0;

				FILE* readFile;
				//open Facilities.txt file for reading
				readFile = fopen("Facilities.txt", "r");

				//validate file opening
				if (readFile == NULL) {
					printf("\t\tCan't Open File.\n");
					system("\tpause");
					system("cls");
					return;
				}

				//real all the facility records inside the file
				while (fscanf(readFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", &fac.staffID, &fac.facilityID, &fac.types, &fac.description, &fac.venue, &fac.maximumUsers, &fac.normalPrice, &fac.vipPrice, &fac.d.day, &fac.d.month, &fac.d.year) != EOF) {

					//if there is an facility ID duplicate
					if (strcmp(addFac.facilityID, fac.facilityID) == 0) {
						//display error message
						printf("\t\tThis Facility ID already inside the file.\n");
						idVal = 1;
						break;
					}
				}

				fclose(readFile);

			} while (idVal == 1);

			//do-while loop to check whether the facility type is correct or not
			do {
				typeVal = 0;
				//prompt and get facility type
				printf("\tFacility Type : ");
				StringInput(addFac.types, 11);
				addFac.types[0] = toupper(addFac.types[0]);

				//check there are all alphabet inside the facility type
				typeVal = AlphabetCheck(addFac.types);
			} while (typeVal == 1);

			//do-while loop to check whether the facility description is correct or not
			do {
				descVal = 0;
				//prompt and get facility description
				printf("\tFacility description : ");
				StringInput(addFac.description, 21);
				addFac.description[0] = toupper(addFac.description[0]);

				//check the digit inside the facility description is match to the digit inside the facility ID
				descVal = FacilityIdAndDesc(addFac.facilityID, addFac.description);
			} while (descVal == 1);

			//set the first character and the character after the blank to uppercase and set the other to lowercase
			UppercaseFunction(addFac.description);

			//do-while loop to check whether the facility venue is correct or not
			do {
				venueVal = 0;
				//prompt and get facility venue
				printf("\tFacility Venue : ");
				StringInput(addFac.venue, 11);
				addFac.venue[0] = toupper(addFac.venue[0]);

				//check there are all alphabet inside the facility type
				venueVal = AlphabetCheck(addFac.venue);
			} while (venueVal == 1);

			//set the first character and the character after the blank to uppercase and set the other to lowercase
			UppercaseFunction(addFac.venue);

			//prompt and get the facility maximum allowable users and validate the input is integer
			printf("\tFacility maximum allowable users : ");
			addFac.maximumUsers = IntInput();

			//prompt and get the normal price per hour of facility and validate the input is float
			printf("\tNormal Price : ");
			addFac.normalPrice = FloatInput();

			//prompt and get the VIP price per hour of facility and validate the input is float
			printf("\tVIP Price : ");
			addFac.vipPrice = FloatInput();

			//set the default value of maintenance day, month, and year to 0
			addFac.d.day = 0;
			addFac.d.month = 0;
			addFac.d.year = 0;

			FILE* writeFile;
			//Open Facilities.txt file for appending
			writeFile = fopen("Facilities.txt", "a");

			//validate file opening
			if (writeFile == NULL) {
				printf("\t\tCan't Open File.\n");
				system("\tpause");
				system("cls");
				return;
			}

			//write all the facility details into the file
			fprintf(writeFile, "%s|%s|%s|%s|%s|%d|%.2f|%.2f|%d|%d|%d\n", addFac.staffID, addFac.facilityID, addFac.types, addFac.description, addFac.venue, addFac.maximumUsers, addFac.normalPrice, addFac.vipPrice, addFac.d.day, addFac.d.month, addFac.d.year);
			//display successful message
			printf("\tAdd Facility Successful.\n");

			//close the file
			fclose(writeFile);

			rewind(stdin);
			//prompt and get whether user want to add next facility or not
			printf("\tNext facility('Y' or 'N') : ");
			scanf("%c", &nextYOrNo);

			nextYOrNo = toupper(nextYOrNo);
			nextYOrNo = YesNoValidation(nextYOrNo);

			printf("\n");
			system("\tpause");
			system("cls");

		} while (nextYOrNo == 'Y');
		break;
	}
}

/// <summary>
/// Function that use to search facility details
/// </summary>
void SearchFacilities() {

	//variable declaration
	char searchFacilityType[11] = " ";
	char searchFacilityVenue[11] = " ";
	char searchFacilityID[10] = " ";
	int searchSelection;

	printf("\t-------------------------\n");
	printf("\t|   Search Facilities   |\n");
	printf("\t-------------------------\n");

	rewind(stdin);
	//prompt and get whether user want start to search facility or not
	printf("\tEnter 'Y' to search facilities : ");
	scanf("%c", &startYOrNo);

	startYOrNo = toupper(startYOrNo);
	startYOrNo = YesNoValidation(startYOrNo);

	while (startYOrNo == 'Y') {

		do {

			Facility fac;
			int selectionVal = 0, dataOrnot = 0, idVal, typeVal, venueVal;
			FILE* readFile;

			if (nextYOrNo == 'Y') {
				printf("\t-------------------------\n");
				printf("\t|   Search Facilities   |\n");
				printf("\t-------------------------\n");
			}

			//display search menu for user to choose search facility by which item
			printf("\t-------------------\n");
			printf("\t|   Search Menu   |\n");
			printf("\t-------------------\n");
			printf("\t 1. Facility ID\n");
			printf("\t 2. Facility Type\n");
			printf("\t 3. Facility Venue\n");
			printf("\t 0. Exit\n");
			printf("\t-------------------\n");
			printf("\tPlease select the method to search facility : ");
			searchSelection = IntInput();

			switch (searchSelection) {
			case 1:
				do {
					idVal = 0;
					//prompt and get the facility ID that user want to search
					printf("\tPlease enter the facility ID that you want to search : ");
					StringInput(searchFacilityID, 10);
					idVal = FacilityIDValidation(searchFacilityID);
				} while (idVal == 1);

				readFile = fopen("Facilities.txt", "r");

				//validate file opening
				if (readFile == NULL) {
					printf("\t\tCan't Open File.\n");
					system("\tpause");
					system("cls");
					return;
				}

				//read all the facility details from the file
				while (fscanf(readFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", &fac.staffID, &fac.facilityID, &fac.types, &fac.description, &fac.venue, &fac.maximumUsers, &fac.normalPrice, &fac.vipPrice, &fac.d.day, &fac.d.month, &fac.d.year) != EOF) {
					//if there is a record of facility ID match to the facility ID that user want to search
					if (strcmp(searchFacilityID, fac.facilityID) == 0) {
						dataOrnot = 1;
					}
				}

				fclose(readFile);

				//if dont have any record match
				if (dataOrnot == 0) {
					printf("\n\t--------------------------------------------------------\n");
					printf("\t| Didn't have this Facility ID record inside the file. |\n");
					printf("\t--------------------------------------------------------\n\n");
				}
				//if there is a record that facility ID match to the facility ID that user want to search
				else {
					readFile = fopen("Facilities.txt", "r");

					//validate file opening
					if (readFile == NULL) {
						printf("\t\tCan't Open File.\n");
						system("\tpause");
						system("cls");
						return;
					}

					//read all the facility record
					while (fscanf(readFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", &fac.staffID, &fac.facilityID, &fac.types, &fac.description, &fac.venue, &fac.maximumUsers, &fac.normalPrice, &fac.vipPrice, &fac.d.day, &fac.d.month, &fac.d.year) != EOF) {

						//if there is a record of facility ID match to the facility ID that user want to search
						if (strcmp(searchFacilityID, fac.facilityID) == 0) {
							//display all the facility details about that facility ID
							printf("\t----------------------\n");
							printf("\t|Facility ID : %-5s  |\n", fac.facilityID);
							printf("\t----------------------\n\n");

							printf("\t Add by %s\n", fac.staffID);
							printf("\t----------------------\n");
							printf("\t Type                       : %s\n", fac.types);
							printf("\t Description                : %s\n", fac.description);
							printf("\t Venue                      : %s\n", fac.venue);
							printf("\t Maximum allowable users    : %d\n", fac.maximumUsers);
							printf("\t Normal price per hour      : %.2f\n", fac.normalPrice);
							printf("\t VIP price per hour         : %.2f\n", fac.vipPrice);
							printf("\t maintenance Date          : ");
							if (fac.d.day == 0 && fac.d.month == 0 && fac.d.year == 0) {
								printf("None\n");
							}
							else {
								printf("%02d-%02d-%d", fac.d.day, fac.d.month, fac.d.year);
							}
							break;
						}
					}
					fclose(readFile);
				}
				break;
			case 2:
				do {
					typeVal = 0;
					//prompt and get the facility type that user want to search
					printf("\tPlease enter the facility type that you want to search : ");
					StringInput(searchFacilityType, 11);
					searchFacilityType[0] = toupper(searchFacilityType[0]);
					typeVal = AlphabetCheck(searchFacilityType);
				} while (typeVal == 1);

				//open Facilities.txt file for reading
				readFile = fopen("Facilities.txt", "r");

				//validate file opening
				if (readFile == NULL) {
					printf("\t\tCan't Open File.\n");
					system("\tpause");
					system("cls");
					return;
				}
				//read all the facility details from file
				while (fscanf(readFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", &fac.staffID, &fac.facilityID, &fac.types, &fac.description, &fac.venue, &fac.maximumUsers, &fac.normalPrice, &fac.vipPrice, &fac.d.day, &fac.d.month, &fac.d.year) != EOF) {
					//if there is a record of facility type match to the facility type that user want to search
					if (strcmp(searchFacilityType, fac.types) == 0) {
						dataOrnot = 1;
					}
				}
				fclose(readFile);

				//if dont have any record match
				if (dataOrnot == 0) {
					printf("\t\tDidn't have this facility type record inside the file.\n");
				}
				else {
					readFile = fopen("Facilities.txt", "r");

					//validate file opening
					if (readFile == NULL) {
						printf("\t\tCan't Open File.\n");
						system("\tpause");
						system("cls");
						return;
					}

					//display facility type that want to show
					printf("\n\n\t------------------------------\n");
					printf("\t| Facility Type : %-11s|\n", searchFacilityType);
					printf("\t------------------------------\n\n");

					//display header for the records
					printf("\t--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
					printf("\t|Staff ID     | Facility ID       | Desciption                | Venue         | Maximum Users  | Normal Price / Hour    | VIP Price / Hour   | Maintenance Date    |\n");
					printf("\t--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

					//display all the records that facility type match to the facility type user search
					while (fscanf(readFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", &fac.staffID, &fac.facilityID, &fac.types, &fac.description, &fac.venue, &fac.maximumUsers, &fac.normalPrice, &fac.vipPrice, &fac.d.day, &fac.d.month, &fac.d.year) != EOF) {
						if (strcmp(searchFacilityType, fac.types) == 0) {
							if (fac.d.day == 0 && fac.d.month == 0 && fac.d.year == 0) {
								printf("\t|%-13s| %-18s| %-26s| %-14s| %-15d| %-23.2f| %-19.2f| None                |\n", fac.staffID, fac.facilityID, fac.description, fac.venue, fac.maximumUsers, fac.normalPrice, fac.vipPrice);
							}
							else {
								printf("\t|%-13s| %-18s| %-26s| %-14s| %-15d| %-23.2f| %-19.2f| %02d-%02d-%d          |\n", fac.staffID, fac.facilityID, fac.description, fac.venue, fac.maximumUsers, fac.normalPrice, fac.vipPrice, fac.d.day, fac.d.month, fac.d.year);
							}
						}
					}
					printf("\t--------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
				}
				fclose(readFile);
				break;
			case 3:
				do {
					venueVal = 0;
					//prompt and get the facility venue that user want to search
					printf("\tPlease enter the facility venue that you want to search : ");
					StringInput(searchFacilityVenue, 11);
					venueVal = AlphabetCheck(searchFacilityVenue);
				} while (venueVal == 1);

				UppercaseFunction(searchFacilityVenue);

				readFile = fopen("Facilities.txt", "r");

				//validate file opening
				if (readFile == NULL) {
					printf("\t\tCan't Open File.\n");
					system("\tpause");
					system("cls");
					return;
				}
				//read all the facility details from file
				while (fscanf(readFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", &fac.staffID, &fac.facilityID, &fac.types, &fac.description, &fac.venue, &fac.maximumUsers, &fac.normalPrice, &fac.vipPrice, &fac.d.day, &fac.d.month, &fac.d.year) != EOF) {
					//if there is a record of facility venue match to the facility venue that user want to search
					if (strcmp(searchFacilityVenue, fac.venue) == 0) {
						dataOrnot = 1;
					}
				}
				fclose(readFile);

				//if dont have any record match
				if (dataOrnot == 0) {
					printf("\t\tDidn't have this facility venue record inside the file.\n");
				}
				else {
					readFile = fopen("Facilities.txt", "r");

					//validate file opening
					if (readFile == NULL) {
						printf("\t\tCan't Open File.\n");
						system("\tpause");
						system("cls");
						return;
					}
					//display the facility venue that user search
					printf("\n\n\tVenue : %s\n\n", searchFacilityVenue);

					//display header for the records
					printf("\t--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
					printf("\t|Staff ID      | Facility ID       | Type           | Desciption                   | Maximum Users       | Normal Price / Hour      | VIP Price / Hour        | Maintenance Date     |\n");
					printf("\t--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

					//display all the records that facility venue match to the facility venue user search
					while (fscanf(readFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", &fac.staffID, &fac.facilityID, &fac.types, &fac.description, &fac.venue, &fac.maximumUsers, &fac.normalPrice, &fac.vipPrice, &fac.d.day, &fac.d.month, &fac.d.year) != EOF) {
						if (strcmp(searchFacilityVenue, fac.venue) == 0) {
							if (fac.d.day == 0 && fac.d.month == 0 && fac.d.year == 0) {
								printf("\t|%-14s| %-18s| %-15s| %-29s| %-20d| %-25.2f| %-24.2f| None                 |\n", fac.staffID, fac.facilityID, fac.types, fac.description, fac.maximumUsers, fac.normalPrice, fac.vipPrice);
							}
							else {
								printf("\t|%-14s| %-18s| %-15s| %-29s| %-20d| %-25.2f| %-24.2f| %02d-%02d-%d           |\n", fac.staffID, fac.facilityID, fac.types, fac.description, fac.maximumUsers, fac.normalPrice, fac.vipPrice, fac.d.day, fac.d.month, fac.d.year);
							}
						}
					}
					printf("\t--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
				}
				fclose(readFile);
				break;
			case 0:
				//display exit message
				printf("\tExit...\n");
				break;
			default:
				//display error message when user enter number besides (1-3)
				printf("\t\tPlease enter correct input (1-3). Try again.\n");
			}
			rewind(stdin);
			//prompt and get whether user want to search next facility or not
			printf("\n\tNext facility('Y' or 'N') : ");
			scanf("%c", &nextYOrNo);

			nextYOrNo = toupper(nextYOrNo);
			nextYOrNo = YesNoValidation(nextYOrNo);

			system("\tpause");
			system("cls");

		} while (nextYOrNo == 'Y');
		break;
	}
}

/// <summary>
/// Function that use to modify the facility details
/// </summary>
void ModifyFacilities() {

	//display header
	printf("\n\t-----------------------\n");
	printf("\t|  Modify Facilities  |\n");
	printf("\t-----------------------\n");

	rewind(stdin);
	//prompt and get whether user want start to modify facility or not
	printf("\tEnter 'Y' to modify facilities : ");
	scanf("%c", &startYOrNo);

	startYOrNo = toupper(startYOrNo);
	startYOrNo = YesNoValidation(startYOrNo);

	while (startYOrNo == 'Y') {

		do {

			if (nextYOrNo == 'Y') {
				printf("\n\t-----------------------\n");
				printf("\t|  Modify Facilities  |\n ");
				printf("\t-----------------------\n");
			}
			//declare variable for structure array
			Facility fac[99], fac2;

			//declare variable for facilityID that user want to modify
			char facilityModify[10] = " ";

			//variable declaration
			int modifySelection, number, idVal, descVal, typeVal, venueVal, validData = 0, doneModify = 0, x, selectionVal = 0;

			FILE* readFile, * writeFile;
			//open Facilities.txt file for reading
			readFile = fopen("Facilities.txt", "r");

			//validate file opening
			if (readFile == NULL) {
				printf("\t\tCan't Open File.\n");
				system("\tpause");
				system("cls");
				return;
			}
			//display all the facility records and store into fac[]
			printf("\t-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			printf("\t|Staff ID      | Facility ID       | Types         | Desciption                | Venue        | Maximum Users       | Normal Price / Hour      | VIP Price / Hour        | Maintenance Date     |\n");
			printf("\t-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

			for (number = 0; fscanf(readFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", &fac[number].staffID, &fac[number].facilityID, &fac[number].types, &fac[number].description, &fac[number].venue, &fac[number].maximumUsers, &fac[number].normalPrice, &fac[number].vipPrice, &fac[number].d.day, &fac[number].d.month, &fac[number].d.year) != EOF; number++) {
				if (fac[number].d.day == 0 && fac[number].d.month == 0 && fac[number].d.year == 0) {
					printf("\t|%-14s| %-18s| %-14s| %-26s| %-13s| %-20d| %-25.2f| %-24.2f| None                 |\n", fac[number].staffID, fac[number].facilityID, fac[number].types, fac[number].description, fac[number].venue, fac[number].maximumUsers, fac[number].normalPrice, fac[number].vipPrice);
				}
				else {
					printf("\t|%-14s| %-18s| %-14s| %-26s| %-13s| %-20d| %-25.2f| %-24.2f| %02d-%02d-%d           |\n", fac[number].staffID, fac[number].facilityID, fac[number].types, fac[number].description, fac[number].venue, fac[number].maximumUsers, fac[number].normalPrice, fac[number].vipPrice, fac[number].d.day, fac[number].d.month, fac[number].d.year);
				}
			}
			printf("\t-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

			//close file
			fclose(readFile);

			do {
				idVal = 0;

				//prompt and get the facility ID that user want to modify
				printf("\tWhich one facility you want to modify (Facility ID) : ");
				StringInput(facilityModify, 10);

				//validate for Facility ID
				idVal = FacilityIDValidation(facilityModify);
			} while (idVal == 1);

			//loop to check got any record of facility ID is match
			for (x = 0; x < number; x++) {
				if (strcmp(facilityModify, fac[x].facilityID) == 0) {
					validData = 1;
					break;
				}
			}
			//if there is an record of that facility ID
			if (validData == 1) {
				do {
					//display the menu for user to select which one want to modify
					printf("\t----------------------------------------\n");
					printf("\t|           Modify Selection           |\n");
					printf("\t----------------------------------------\n");
					printf("\t1. Facility ID, Type And Description\n");
					printf("\t2. Facility Venue\n");
					printf("\t3. Maximum Allow Users\n");
					printf("\t4. Normal Price Per Hours\n");
					printf("\t5. VIP Price Per Hours\n");
					printf("\t6. Maintenance Date\n");
					printf("\t0. Exit\n");
					printf("\t----------------------------------------\n");

					//prompt and get which item want to modify
					printf("\tWhich one details you want to modify : ");
					//validate the input is integer
					modifySelection = IntInput();

					switch (modifySelection) {
					case 1:
						do {

							//Do-while loop to check whether the input is correct or not
							do {

								//initialize the idVal to 0;
								idVal = 0;

								//prompt and get the new facility ID
								printf("\tFacility ID : ");
								StringInput(fac[x].facilityID, 10);
								idVal = FacilityIDValidation(fac[x].facilityID);

							} while (idVal == 1);

							idVal = 0;

							FILE* readFile;
							//Open Facilities.txt file for reading
							readFile = fopen("Facilities.txt", "r");

							//validate file opening
							if (readFile == NULL) {
								printf("\t\tCan't Open File.\n");
								system("\tpause");
								system("cls");
								return;
							}
							//read all the facility records from file
							while (fscanf(readFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", &fac2.staffID, &fac2.facilityID, &fac2.types, &fac2.description, &fac2.venue, &fac2.maximumUsers, &fac2.normalPrice, &fac2.vipPrice, &fac2.d.day, &fac2.d.month, &fac2.d.year) != EOF) {

								//if the new facility ID duplicate with the other records inside the file
								if (strcmp(fac[x].facilityID, fac2.facilityID) == 0) {
									//display error message
									printf("\n\t---------------------------------------------\n");
									printf("\t| This Facility ID already inside the file. |\n");
									printf("\t---------------------------------------------\n\n");
									idVal = 1;
									break;
								}
							}
							//close file
							fclose(readFile);

						} while (idVal == 1);

						do {
							typeVal = 0;
							//prompt and get new facility type
							printf("\tFacility Type : ");
							StringInput(fac[x].types, 11);
							fac[x].types[0] = toupper(fac[x].types[0]);
							//validate there is all alphabet inside the facility type
							typeVal = AlphabetCheck(fac[x].types);
						} while (typeVal == 1);

						do {
							descVal = 0;
							//prompt and get new facility description
							printf("\tFacility description : ");
							StringInput(fac[x].description, 21);
							//validate the digit inside the facility desciptionn is match to facility ID
							descVal = FacilityIdAndDesc(fac[x].facilityID, fac[x].description);
						} while (descVal == 1);

						UppercaseFunction(fac[x].description);
						break;
					case 2:
						do {
							venueVal = 0;
							//prompt and get the new facility venue
							printf("\tFacility Venue : ");
							StringInput(fac[x].venue, 11);
							//validate there is all alphabet inside the facility venue
							venueVal = AlphabetCheck(fac[x].venue);
						} while (venueVal == 1);

						UppercaseFunction(fac[x].venue);
						break;
					case 3:
						//prompt and get the new maximum allowable users of facility
						printf("\tMaximum Allow Users : ");
						fac[x].maximumUsers = IntInput();
						break;
					case 4:
						//prompt and get the new normal price per hour of facility
						printf("\tNormal Price : ");
						fac[x].normalPrice = FloatInput();
						break;
					case 5:
						//prompt and get the new VIP price per hour of facility
						printf("\tVIP Price : ");
						fac[x].vipPrice = FloatInput();
						break;
					case 6:
						//prompt and get the maintainancce date of facility
						printf("\tMaintenance date : \n");
						DateInput(&fac[x].d.day, &fac[x].d.month, &fac[x].d.year, "date input");
						break;
					case 0:
						//display exit message
						printf("\t\tExit. Your facility details modified will shown at below.\n");
						break;
					default:
						//display error message
						printf("\t\tError. Please enter number(0-6).\n");
					}
				} while (modifySelection != 0);

				//display modified facility details
				printf("\t-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
				printf("\t|Staff ID      | Facility ID       | Types         | Desciption                | Venue        | Maximum Users       | Normal Price / Hour      | VIP Price / Hour        | Maintenance Date     |\n");
				printf("\t-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
				if (fac[x].d.day == 0 && fac[x].d.month == 0 && fac[x].d.year == 0) {
					printf("\t|%-14s| %-18s| %-14s| %-26s| %-13s| %-20d| %-25.2f| %-24.2f| None                 |\n", fac[x].staffID, fac[x].facilityID, fac[x].types, fac[x].description, fac[x].venue, fac[x].maximumUsers, fac[x].normalPrice, fac[x].vipPrice);
				}
				else {
					printf("\t|%-14s| %-18s| %-14s| %-26s| %-13s| %-20d| %-25.2f| %-24.2f| %02d-%02d-%d           |\n", fac[x].staffID, fac[x].facilityID, fac[x].types, fac[x].description, fac[x].venue, fac[x].maximumUsers, fac[x].normalPrice, fac[x].vipPrice, fac[x].d.day, fac[x].d.month, fac[x].d.year);
				}
				printf("\t-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
				doneModify = 1;

				//done modify
				if (doneModify == 1) {
					//open Facilities.txt file for writing
					writeFile = fopen("Facilities.txt", "w");

					//validate file opening
					if (writeFile == NULL) {
						printf("\t\tCan't Open File.\n");
						system("\tpause");
						system("cls");
						return;
					}

					//write all the facility records to the Facilities.txt file.
					for (int x = 0; x < number; x++) {
						fprintf(writeFile, "%s|%s|%s|%s|%s|%d|%.2f|%.2f|%d|%d|%d\n", fac[x].staffID, fac[x].facilityID, fac[x].types, fac[x].description, fac[x].venue, fac[x].maximumUsers, fac[x].normalPrice, fac[x].vipPrice, fac[x].d.day, fac[x].d.month, fac[x].d.year);
					}

					//close file
					fclose(writeFile);
				}
			}
			else {
				printf("\t\tDidn't have this facility ID inside the data.\n");
			}

			rewind(stdin);
			//prompt and get whether user want to modify next facility or not
			printf("\n\tNext facility('Y' or 'N') : ");
			scanf("%c", &nextYOrNo);

			nextYOrNo = toupper(nextYOrNo);
			nextYOrNo = YesNoValidation(nextYOrNo);

			system("\tpause");
			system("cls");
		} while (nextYOrNo == 'Y');
		break;
	}
}

/// <summary>
/// Function that display all the facilities
/// </summary>
/// <param name="readFile"></param>
void DisplayFacilities() {

	int number = 0;

	printf("\t------------------------\n");
	printf("\t|  Display Facilities  |\n");
	printf("\t------------------------\n");

	rewind(stdin);
	//prompt and get whether user want start to display facility or not
	printf("\tEnter 'Y' to display facilities : ");
	scanf("%c", &startYOrNo);

	startYOrNo = toupper(startYOrNo);
	startYOrNo = YesNoValidation(startYOrNo);

	while (startYOrNo == 'Y') {

		Facility fac;

		FILE* readFile;
		//open Facilities.txt file for reading
		readFile = fopen("Facilities.txt", "r");

		//validate file opening
		if (readFile == NULL) {
			printf("\t\tCan't Open File.\n");
			system("\tpause");
			system("cls");
			return;
		}
		//read all the facility from the file
		while (fscanf(readFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", &fac.staffID, &fac.facilityID, &fac.types, &fac.description, &fac.venue, &fac.maximumUsers, &fac.normalPrice, &fac.vipPrice, &fac.d.day, &fac.d.month, &fac.d.year) != EOF) {
			number++;
		}
		//close file
		fclose(readFile);

		//if there is not any records inside the file
		if (number == 0) {
			printf("\t\tThere is not any facility records inside the file.\n");
		}
		else {
			readFile = fopen("Facilities.txt", "r");

			//validate file opening
			if (readFile == NULL) {
				printf("\t\tCan't Open File.\n");
				system("\tpause");
				system("cls");
				return;
			}
			//display header
			printf("\n");
			printf("                                                                             ------------------------\n");
			printf("                                                                             |  All The Facilities  |\n");
			printf("                                                                             ------------------------\n\n");

			printf("\t-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			printf("\t|Staff ID      | Facility ID       | Types         | Desciption                | Venue        | Maximum Users       | Normal Price / Hour      | VIP Price / Hour        | Maintenance Date     |\n");
			printf("\t-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			//display all the facility details inside the file
			while (fscanf(readFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", &fac.staffID, &fac.facilityID, &fac.types, &fac.description, &fac.venue, &fac.maximumUsers, &fac.normalPrice, &fac.vipPrice, &fac.d.day, &fac.d.month, &fac.d.year) != EOF) {

				if (fac.d.day == 0 && fac.d.month == 0 && fac.d.year == 0) {
					printf("\t|%-14s| %-18s| %-14s| %-26s| %-13s| %-20d| %-25.2f| %-24.2f| None                 |\n", fac.staffID, fac.facilityID, fac.types, fac.description, fac.venue, fac.maximumUsers, fac.normalPrice, fac.vipPrice);
				}
				else {
					printf("\t|%-14s| %-18s| %-14s| %-26s| %-13s| %-20d| %-25.2f| %-24.2f| %02d-%02d-%d           |\n", fac.staffID, fac.facilityID, fac.types, fac.description, fac.venue, fac.maximumUsers, fac.normalPrice, fac.vipPrice, fac.d.day, fac.d.month, fac.d.year);
				}
			}
			printf("\t-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		}
		//close file
		fclose(readFile);
		system("\tpause");
		system("cls");
		break;
	}
}

/// <summary>
/// Function that use to delete the facility
/// </summary>
void DeleteFacilities() {

	printf("\t-----------------------\n");
	printf("\t|  Delete Facilities  |\n");
	printf("\t-----------------------\n");

	rewind(stdin);
	//prompt and get whether user want start to delete facility or not
	printf("\tEnter 'Y' to delete facilities : ");
	scanf("%c", &startYOrNo);

	startYOrNo = toupper(startYOrNo);
	startYOrNo = YesNoValidation(startYOrNo);

	while (startYOrNo == 'Y') {

		do {

			if (nextYOrNo == 'Y') {
				printf("\t-----------------------\n");
				printf("\t|  Delete Facilities  |\n");
				printf("\t-----------------------\n");
			}

			Facility fac[99], fac1;

			int number, dataOrnot = 0, idVal = 0;
			char deleteFacility[10] = "";

			FILE* readFile;
			//Open Facilities.txt file for reading
			readFile = fopen("Facilities.txt", "r");

			//validate file opening
			if (readFile == NULL) {
				printf("\t\tCan't Open File.\n");
				system("\tpause");
				system("cls");
				return;
			}

			//display header for facilities details
			printf("\t-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
			printf("\t|Staff ID      | Facility ID       | Types         | Desciption                | Venue        | Maximum Users       | Normal Price / Hour      | VIP Price / Hour        | Maintenance Date     |\n");
			printf("\t-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

			//read all the facilities details from the file
			for (number = 0; fscanf(readFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", &fac[number].staffID, &fac[number].facilityID, &fac[number].types, &fac[number].description, &fac[number].venue, &fac[number].maximumUsers, &fac[number].normalPrice, &fac[number].vipPrice, &fac[number].d.day, &fac[number].d.month, &fac[number].d.year) != EOF; number++) {

				//display all the facilties details
				if (fac[number].d.day == 0 && fac[number].d.month == 0 && fac[number].d.year == 0) {
					printf("\t|%-14s| %-18s| %-14s| %-26s| %-13s| %-20d| %-25.2f| %-24.2f| None                 |\n", fac[number].staffID, fac[number].facilityID, fac[number].types, fac[number].description, fac[number].venue, fac[number].maximumUsers, fac[number].normalPrice, fac[number].vipPrice);
				}
				else {
					printf("\t|%-14s| %-18s| %-14s| %-26s| %-13s| %-20d| %-25.2f| %-24.2f| %02d-%02d-%d           |\n", fac[number].staffID, fac[number].facilityID, fac[number].types, fac[number].description, fac[number].venue, fac[number].maximumUsers, fac[number].normalPrice, fac[number].vipPrice, fac[number].d.day, fac[number].d.month, fac[number].d.year);
				}
			}
			printf("\t-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

			fclose(readFile);
			rewind(stdin);
			//prompt and get the facility ID of the facility that user want to delete
			do {
				idVal = 0;

				//prompt and get the facility ID that user want to delete
				printf("\tWhich one facility you want to delete (Facility ID) : ");
				StringInput(deleteFacility, 10);

				//validate for Facility ID
				idVal = FacilityIDValidation(deleteFacility);
			} while (idVal == 1);

			//open Facilities.txt file for reading
			readFile = fopen("Facilities.txt", "r");

			//validate file opening
			if (readFile == NULL) {
				printf("\t\tCan't Open File.\n");
				system("\tpause");
				system("cls");
				return;
			}

			//read all the facility details from the file
			while (fscanf(readFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", &fac1.staffID, &fac1.facilityID, &fac1.types, &fac1.description, &fac1.venue, &fac1.maximumUsers, &fac1.normalPrice, &fac1.vipPrice, &fac1.d.day, &fac1.d.month, &fac1.d.year) != EOF) {
				//if the facility ID that user want to delete exists in the file
				if (strcmp(deleteFacility, fac1.facilityID) == 0) {
					dataOrnot = 1;
					break;
				}
			}
			fclose(readFile);

			//if the facility ID that user want to delete not exists in the file
			if (dataOrnot == 0) {
				printf("\t\tPlease enter the exist facility ID.\n");
			}
			else {
				FILE* writeFile;
				//open Facilities.txt file for writing
				writeFile = fopen("Facilities.txt", "w");

				//validate file opening
				if (writeFile == NULL) {
					printf("\t\tCan't Open File.\n");
					system("\tpause");
					system("cls");
					return;
				}

				//write all the facility details back to the file
				for (int x = 0; x < number; x++) {
					if (strcmp(deleteFacility, fac[x].facilityID) == 0) {
						continue;
					}
					else {
						fprintf(writeFile, "%s|%s|%s|%s|%s|%d|%.2f|%.2f|%d|%d|%d\n", fac[x].staffID, fac[x].facilityID, fac[x].types, fac[x].description, fac[x].venue, fac[x].maximumUsers, fac[x].normalPrice, fac[x].vipPrice, fac[x].d.day, fac[x].d.month, fac[x].d.year);
					}
				}
				printf("\t%-4s deleted.\n", deleteFacility);
				fclose(writeFile);
			}
			rewind(stdin);
			//prompt and get whether user want to delete next facility or not
			printf("\tNext facility('Y' or 'N') : ");
			scanf("%c", &nextYOrNo);

			nextYOrNo = toupper(nextYOrNo);
			nextYOrNo = YesNoValidation(nextYOrNo);

			system("\tpause");
			system("cls");

		} while (nextYOrNo == 'Y');

		break;
	}
}

/// <summary>
/// Function that use to generate report for maintenance
/// </summary>
void FacilitiesReport() {

	//variable declaration for validation
	int reportselection, validData = 0;
	int validMonth = 0, validYear = 0;

	//variable declaration to store the current date, month, and year
	int currentDate, currentMonth, currentYear;

	printf("\t-----------------------\n");
	printf("\t|  Facilities Report  |\n");
	printf("\t-----------------------\n\n");

	rewind(stdin);
	//prompt and get whether user want start to generate facility report or not
	printf("\tEnter 'Y' to generate facilities report : ");
	scanf("%c", &startYOrNo);

	startYOrNo = toupper(startYOrNo);
	startYOrNo = YesNoValidation(startYOrNo);

	while (startYOrNo == 'Y') {

		do {

			if (nextYOrNo == 'Y') {
				printf("\t-----------------------\n");
				printf("\t|  Facilities Report  |\n");
				printf("\t-----------------------\n\n");
			}
			char filename1[50] = " ", filename2[30] = " ", filename3[30] = " ", generateYorNo;
			Facility fac, f;

			//display menu to let user select the type of maintenance report
			printf("\n\t---------------------------\n");
			printf("\t|   Maintenance report    |\n");
			printf("\t---------------------------\n");
			printf("\t1. Day\n");
			printf("\t2. Month\n");
			printf("\t3. Year\n");
			printf("\t4. All\n");
			printf("\t0. Exit\n");
			printf("\t---------------------------\n");
			//prompt and get the selection for the maintenance report
			printf("\tPlease enter your selection : ");
			reportselection = IntInput();

			//Create file pointer for the report
			FILE* readFile, * dayReport, * monthReport, * yearReport, * allReport;

			//get ther current date, month, and year
			currentDate = CurrentDate("DD");
			currentMonth = CurrentDate("MM");
			currentYear = CurrentDate("YYYY");

			switch (reportselection) {
			case 0:
				printf("\tThank you...Exit...\n");
				break;
			case 1:
				validData = 0;
				//prompt and get the date of the maintenance to generate the report
				printf("\tPlease enter date : \n");
				DateInput(&f.d.day, &f.d.month, &f.d.year, "date input");

				//open Facilities.txt for reading
				readFile = fopen("Facilities.txt", "r");

				//validate file opening
				if (readFile == NULL) {
					printf("\t\tCan't Open File.\n");
					system("\tpause");
					system("cls");
					return;
				}
				//read all the facility details from the file
				while (fscanf(readFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", &fac.staffID, &fac.facilityID, &fac.types, &fac.description, &fac.venue, &fac.maximumUsers, &fac.normalPrice, &fac.vipPrice, &fac.d.day, &fac.d.month, &fac.d.year) != EOF) {
					//if the day, month, and year that user input is match to the records inside the file
					if ((f.d.day == fac.d.day) && (f.d.month == fac.d.month) && (f.d.year == fac.d.year)) {
						validData = 1;
					}
				}
				//close file
				fclose(readFile);

				//if there is not any records
				if (validData == 0) {
					printf("\t\tDidn't have any maintenance on this day.\n");
				}
				else {
					//open Facilities.txt file for reading
					readFile = fopen("Facilities.txt", "r");

					//validate file opening
					if (readFile == NULL) {
						printf("\t\tCan't Open File.\n");
						system("\tpause");
						system("cls");
						return;
					}

					printf("\t                                                                                                                                              Generate date : %02d-%02d-%d\n", currentDate, currentMonth, currentYear);
					printf("\t                                                                 ----------------------------\n");
					printf("\t                                                                 | Daily Maintenance Report |\n");
					printf("\t                                                                 ----------------------------\n\n");
					//display the date of the maintenance
					printf("\tDate : %02d-%02d-%d\n", f.d.day, f.d.month, f.d.year);
					printf("\t--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
					printf("\t|Staff ID      | Facility ID       | Types         | Desciption                | Venue        | Maximum Users       | Normal Price / Hour      | VIP Price / Hour        |\n");
					printf("\t--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

					//read all the facility details from the file and write the maintenance date match to the user input to the file
					while (fscanf(readFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", &fac.staffID, &fac.facilityID, &fac.types, &fac.description, &fac.venue, &fac.maximumUsers, &fac.normalPrice, &fac.vipPrice, &fac.d.day, &fac.d.month, &fac.d.year) != EOF) {
						//display the facility details that match the day, month, and year
						if ((f.d.day == fac.d.day) && (f.d.month == fac.d.month) && (f.d.year == fac.d.year)) {
							printf("\t|%-14s| %-18s| %-14s| %-26s| %-13s| %-20d| %-25.2f| %-24.2f|\n", fac.staffID, fac.facilityID, fac.types, fac.description, fac.venue, fac.maximumUsers, fac.normalPrice, fac.vipPrice);
						}
					}
					printf("\t--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

					fclose(readFile);

					rewind(stdin);
					printf("\tDo you want to generate this report ( 'Y' or 'N' ) : ");
					scanf("%c", &generateYorNo);

					generateYorNo = toupper(generateYorNo);
					generateYorNo = YesNoValidation(generateYorNo);

					if (generateYorNo == 'Y') {

						//open Facilities.txt file for reading
						readFile = fopen("Facilities.txt", "r");

						//validate file opening
						if (readFile == NULL) {
							printf("\t\tCan't Open File.\n");
							system("\tpause");
							system("cls");
							return;
						}

						//convert the day, month, and year to string data type
						itoa(f.d.day, filename1, 10);
						itoa(f.d.month, filename2, 10);
						itoa(f.d.year, filename3, 10);
						strcat(strcat(filename1, "-"), strcat(strcat(filename2, "-"), strcat(filename3, " Daily Report.txt")));

						//Open file for writing
						dayReport = fopen(filename1, "w");

						//validate file opening
						if (dayReport == NULL) {
							printf("\t\tCan't Open File.\n");
							system("\tpause");
							system("cls");
							return;
						}

						//write the date when generate the report and header
						fprintf(dayReport, "                                                                                                                               Generate date : %02d-%02d-%d\n", currentDate, currentMonth, currentYear);
						fprintf(dayReport, "                                                     ----------------------------\n");
						fprintf(dayReport, "                                                     | Daily Maintenance Report |\n");
						fprintf(dayReport, "                                                     ----------------------------\n\n");
						//write the date of the maintenance
						fprintf(dayReport, "Date : %02d-%02d-%d\n", f.d.day, f.d.month, f.d.year);
						fprintf(dayReport, "----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
						fprintf(dayReport, "|Staff ID      Facility ID       Types         Desciption                Venue         Maximum Users       Normal Price / Hour      VIP Price / Hour     |\n");
						fprintf(dayReport, "----------------------------------------------------------------------------------------------------------------------------------------------------------\n");

						//read all the facility details from the file and write the maintenance date match to the user input to the file
						while (fscanf(readFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", &fac.staffID, &fac.facilityID, &fac.types, &fac.description, &fac.venue, &fac.maximumUsers, &fac.normalPrice, &fac.vipPrice, &fac.d.day, &fac.d.month, &fac.d.year) != EOF) {
							if ((f.d.day == fac.d.day) && (f.d.month == fac.d.month) && (f.d.year == fac.d.year)) {
								fprintf(dayReport, "|%-14s%-18s%-14s%-26s%-19s%-21d%-25.2f%-15.2f|\n", fac.staffID, fac.facilityID, fac.types, fac.description, fac.venue, fac.maximumUsers, fac.normalPrice, fac.vipPrice);
							}
						}
						fprintf(dayReport, "----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
						printf("\tReport generated.\n");
						fclose(readFile);
						fclose(dayReport);
					}
					else {
						printf("\tThank You...\n");
					}
				}
				break;
			case 2:
				do {
					validMonth = 0;
					validData = 0;
					printf("\tPlease enter month : \n");
					//prompt and get the year to generate the report
					printf("\tYear : ");
					f.d.year = IntInput();

					//prompt and get the month to generate the report
					printf("\tmonth : ");
					f.d.month = IntInput();

					if ((f.d.month < 0 || f.d.month >12) || (f.d.year < 1950 || f.d.year>2022)) {
						validMonth = 1;
					}
				} while (validMonth == 1);

				//open Facilities.txt file for reading
				readFile = fopen("Facilities.txt", "r");

				//validate file opening
				if (readFile == NULL) {
					printf("\t\tCan't Open File.\n");
					system("\tpause");
					system("cls");
					return;
				}
				//read all the facility details from the file
				while (fscanf(readFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", &fac.staffID, &fac.facilityID, &fac.types, &fac.description, &fac.venue, &fac.maximumUsers, &fac.normalPrice, &fac.vipPrice, &fac.d.day, &fac.d.month, &fac.d.year) != EOF) {
					//if the month and year that user input is match to the records inside the file
					if ((f.d.month == fac.d.month) && (f.d.year == fac.d.year)) {
						validData = 1;
					}
				}
				//close file
				fclose(readFile);

				if (validData == 0) {
					printf("\t\tDidn't have any maintenance record on this month.\n");
				}
				else {
					readFile = fopen("Facilities.txt", "r");

					//validate file opening
					if (readFile == NULL) {
						printf("\t\tCan't Open File.\n");
						system("\tpause");
						system("cls");
						return;
					}
					printf("\t                                                                                                                                                                     Generate date : %02d-%02d-%d\n", currentDate, currentMonth, currentYear);
					printf("\t                                                                             ------------------------------\n");
					printf("\t                                                                             | Monthly Maintenance Report |\n");
					printf("\t                                                                             ------------------------------\n\n");
					//display the month of the maintenance
					printf("\tMonth : %02d-%d\n", f.d.month, f.d.year);
					printf("\t-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
					printf("\t|Staff ID      | Facility ID       | Types         | Desciption                | Venue        | Maximum Users       | Normal Price / Hour      | VIP Price / Hour        | Maintenance Date     |\n");
					printf("\t-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
					//read all the facility details from the file and write the maintenance date match to the user input to the file
					while (fscanf(readFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", &fac.staffID, &fac.facilityID, &fac.types, &fac.description, &fac.venue, &fac.maximumUsers, &fac.normalPrice, &fac.vipPrice, &fac.d.day, &fac.d.month, &fac.d.year) != EOF) {
						//display the facility details that match the month and year
						if ((f.d.month == fac.d.month) && (f.d.year == fac.d.year)) {
							printf("\t|%-14s| %-18s| %-14s| %-26s| %-13s| %-20d| %-25.2f| %-24.2f| %02d-%02d-%d           |\n", fac.staffID, fac.facilityID, fac.types, fac.description, fac.venue, fac.maximumUsers, fac.normalPrice, fac.vipPrice, fac.d.day, fac.d.month, fac.d.year);
						}
					}
					printf("\t-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

					fclose(readFile);

					rewind(stdin);
					printf("\tDo you want to generate this report ( 'Y' or 'N' ) : ");
					scanf("%c", &generateYorNo);

					generateYorNo = toupper(generateYorNo);
					generateYorNo = YesNoValidation(generateYorNo);

					if (generateYorNo == 'Y') {

						//open Facilities.txt file for reading
						readFile = fopen("Facilities.txt", "r");

						//validate file opening
						if (readFile == NULL) {
							printf("\t\tCan't Open File.\n");
							system("\tpause");
							system("cls");
							return;
						}

						//convert the month and year to string data type
						itoa(f.d.month, filename2, 10);
						itoa(f.d.year, filename3, 10);
						strcat(strcat(filename2, "-"), strcat(filename3, " Monthly Report.txt"));

						//open file for writing
						monthReport = fopen(filename2, "w");
						//validate file opening
						if (monthReport == NULL) {
							printf("\t\tCan't Open File.\n");
							system("\tpause");
							system("cls");
							return;
						}

						//write the date when generate the report and header
						fprintf(monthReport, "                                                                                                                                                       Generate date : %02d-%02d-%d\n", currentDate, currentMonth, currentYear);
						fprintf(monthReport, "                                                               ------------------------------\n");
						fprintf(monthReport, "                                                               | Monthly Maintenance Report |\n");
						fprintf(monthReport, "                                                               ------------------------------\n\n");
						//write the month of the maintenance
						fprintf(monthReport, "Month : %02d-%d\n", f.d.month, f.d.year);
						fprintf(monthReport, "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
						fprintf(monthReport, "|Staff ID      Facility ID       Types         Desciption                Venue         Maximum Users       Normal Price / Hour      VIP Price / Hour        Maintenance Date     |\n");
						fprintf(monthReport, "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
						//read all the facility details from the file and write the maintenance date match to the user input to the file
						while (fscanf(readFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", &fac.staffID, &fac.facilityID, &fac.types, &fac.description, &fac.venue, &fac.maximumUsers, &fac.normalPrice, &fac.vipPrice, &fac.d.day, &fac.d.month, &fac.d.year) != EOF) {
							if ((f.d.month == fac.d.month) && (f.d.year == fac.d.year)) {
								fprintf(monthReport, "|%-14s%-18s%-14s%-25s%-18s%-22d%-24.2f%-22.2f%02d-%02d-%02d         |\n", fac.staffID, fac.facilityID, fac.types, fac.description, fac.venue, fac.maximumUsers, fac.normalPrice, fac.vipPrice, fac.d.day, fac.d.month, fac.d.year);
							}
						}
						fprintf(monthReport, "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
						printf("\tReport generated.\n");
						fclose(readFile);
						fclose(monthReport);
					}
					else {
						printf("\tThank You...\n");
					}
				}
				break;
			case 3:
				do {
					validYear = 0;
					validData = 0;
					//prompt and get the year to generate the maintenance report
					printf("\tPlease enter year (YYYY) : ");
					f.d.year = IntInput();
					//if the year less than 1950 or bigger than 2022
					if (f.d.year < 1950 || f.d.year>2022) {
						validYear = 1;
						printf("\t\tPlease enter a valid year (1950-2022).\n");
					}
				} while (validYear == 1);

				//open Facilities.txt file for reading
				readFile = fopen("Facilities.txt", "r");

				//validate file opening
				if (readFile == NULL) {
					printf("\t\tCan't Open File.\n");
					system("\tpause");
					system("cls");
					return;
				}

				while (fscanf(readFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", &fac.staffID, &fac.facilityID, &fac.types, &fac.description, &fac.venue, &fac.maximumUsers, &fac.normalPrice, &fac.vipPrice, &fac.d.day, &fac.d.month, &fac.d.year) != EOF) {
					if (f.d.year == fac.d.year) {
						validData = 1;
					}
				}
				//close file
				fclose(readFile);

				if (validData == 0) {
					printf("\t\tDidn't have any maintenance record in this year.\n");
				}
				else {
					readFile = fopen("Facilities.txt", "r");

					//validate file opening
					if (readFile == NULL) {
						printf("\t\tCan't Open File.\n");
						system("\tpause");
						system("cls");
						return;
					}

					//write the date when generate the report and header
					printf("\t                                                                                                                                                                      Generate date : %02d-%02d-%d\n", currentDate, currentMonth, currentYear);
					printf("\t                                                                        -------------------------------\n");
					printf("\t                                                                        |  Yearly Maintenance Report  |\n");
					printf("\t                                                                        -------------------------------\n\n");
					//write the month of the maintenance
					printf("\tYear : %d\n", f.d.year);
					printf("\t-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
					printf("\t|Staff ID      | Facility ID       | Types         | Desciption                | Venue        | Maximum Users       | Normal Price / Hour      | VIP Price / Hour        | Maintenance Date     |\n");
					printf("\t-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
					//read all the facility details from the file and write the maintenance date match to the user input to the file
					while (fscanf(readFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", &fac.staffID, &fac.facilityID, &fac.types, &fac.description, &fac.venue, &fac.maximumUsers, &fac.normalPrice, &fac.vipPrice, &fac.d.day, &fac.d.month, &fac.d.year) != EOF) {
						if (f.d.year == fac.d.year) {
							printf("\t|%-14s| %-18s| %-14s| %-26s| %-13s| %-20d| %-25.2f| %-24.2f| %02d-%02d-%d           |\n", fac.staffID, fac.facilityID, fac.types, fac.description, fac.venue, fac.maximumUsers, fac.normalPrice, fac.vipPrice, fac.d.day, fac.d.month, fac.d.year);
						}
					}
					printf("\t-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

					fclose(readFile);

					rewind(stdin);
					printf("\tDo you want to generate this report ( 'Y' or 'N' ) : ");
					scanf("%c", &generateYorNo);

					generateYorNo = toupper(generateYorNo);
					generateYorNo = YesNoValidation(generateYorNo);

					if (generateYorNo == 'Y') {

						//open Facilities.txt file for reading
						readFile = fopen("Facilities.txt", "r");

						//validate file opening
						if (readFile == NULL) {
							printf("\t\tCan't Open File.\n");
							system("\tpause");
							system("cls");
							return;
						}

						//convert the year to string data type
						itoa(f.d.year, filename3, 10);
						strcat(filename3, " Yearly Report.txt");

						//open file for writing
						yearReport = fopen(filename3, "w");

						//validate file opening
						if (yearReport == NULL) {
							printf("\t\tCan't Open File.\n");
							system("\tpause");
							system("cls");
							return;
						}
						//write the date when generate the report and header
						fprintf(yearReport, "                                                                                                                                                        Generate date : %02d-%02d-%d\n", currentDate, currentMonth, currentYear);
						fprintf(yearReport, "                                                                     -------------------------------\n");
						fprintf(yearReport, "                                                                     |  Yearly Maintenance Report  |\n");
						fprintf(yearReport, "                                                                     -------------------------------\n\n");
						//write the month of the maintenance 
						fprintf(yearReport, "Year : %d\n", f.d.year);
						fprintf(yearReport, "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
						fprintf(yearReport, "|Staff ID      Facility ID       Types         Desciption                Venue         Maximum Users       Normal Price / Hour      VIP Price / Hour        Maintenance Date     |\n");
						fprintf(yearReport, "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
						//read all the facility details from the file and write the maintenance date match to the user input to the file
						while (fscanf(readFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", &fac.staffID, &fac.facilityID, &fac.types, &fac.description, &fac.venue, &fac.maximumUsers, &fac.normalPrice, &fac.vipPrice, &fac.d.day, &fac.d.month, &fac.d.year) != EOF) {
							if (f.d.year == fac.d.year) {
								fprintf(yearReport, "|%-14s%-18s%-14s%-25s%-18s%-22d%-24.2f%-22.2f%02d-%02d-%02d         |\n", fac.staffID, fac.facilityID, fac.types, fac.description, fac.venue, fac.maximumUsers, fac.normalPrice, fac.vipPrice, fac.d.day, fac.d.month, fac.d.year);
							}
						}
						fprintf(yearReport, "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
						printf("\tReport generated.\n");
						fclose(readFile);
						fclose(yearReport);
					}
					else {
						printf("\tThank You...\n");
					}
				}
				break;
			case 4:
				//open file for writing
				readFile = fopen("Facilities.txt", "r");

				//validate file opening
				if (readFile == NULL) {
					printf("\t\tCan't Open File.\n");
					system("\tpause");
					system("cls");
					return;
				}

				while (fscanf(readFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", &fac.staffID, &fac.facilityID, &fac.types, &fac.description, &fac.venue, &fac.maximumUsers, &fac.normalPrice, &fac.vipPrice, &fac.d.day, &fac.d.month, &fac.d.year) != EOF) {
					if ((fac.d.day != 0) && (fac.d.month != 0) && (fac.d.year != 0)) {
						validData = 1;
					}
				}
				//close file
				fclose(readFile);

				if (validData == 0) {
					printf("\t\tDidn't have any maintenance record.\n");
				}
				else {
					//open Facilities.txt file for reading
					readFile = fopen("Facilities.txt", "r");

					//validate file opening
					if (readFile == NULL) {
						printf("\t\tCan't Open File.\n");
						system("\tpause");
						system("cls");
						return;
					}

					//display the date when generate the report and header
					printf("\t                                                                                                                                                                     Generate date : %02d-%02d-%d\n", currentDate, currentMonth, currentYear);
					printf("\t                                                                       ----------------------------------\n");
					printf("\t                                                                       |       Maintenance Report       |\n");
					printf("\t                                                                       ----------------------------------\n\n");

					printf("\t-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
					printf("\t|Staff ID      | Facility ID       | Types         | Desciption                | Venue        | Maximum Users       | Normal Price / Hour      | VIP Price / Hour        | Maintenance Date     |\n");
					printf("\t-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
					//display all the facility details to the file
					while (fscanf(readFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", &fac.staffID, &fac.facilityID, &fac.types, &fac.description, &fac.venue, &fac.maximumUsers, &fac.normalPrice, &fac.vipPrice, &fac.d.day, &fac.d.month, &fac.d.year) != EOF) {
						if ((fac.d.day != 0) && (fac.d.month != 0) && (fac.d.year != 0)) {
							printf("\t|%-14s| %-18s| %-14s| %-26s| %-13s| %-20d| %-25.2f| %-24.2f| %02d-%02d-%d           |\n", fac.staffID, fac.facilityID, fac.types, fac.description, fac.venue, fac.maximumUsers, fac.normalPrice, fac.vipPrice, fac.d.day, fac.d.month, fac.d.year);
						}
					}
					printf("\t-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

					fclose(readFile);

					rewind(stdin);
					printf("\tDo you want to generate this report ( 'Y' or 'N' ) : ");
					scanf("%c", &generateYorNo);

					generateYorNo = toupper(generateYorNo);
					generateYorNo = YesNoValidation(generateYorNo);

					if (generateYorNo == 'Y') {

						//open Facilities.txt file for reading
						readFile = fopen("Facilities.txt", "r");

						//validate file opening
						if (readFile == NULL) {
							printf("\t\tCan't Open File.\n");
							system("\tpause");
							system("cls");
							return;
						}
						//open file for writing
						allReport = fopen("Maintenance Report.txt", "w");

						//validate file opening
						if (allReport == NULL) {
							printf("\t\tCan't Open File.\n");
							system("\tpause");
							system("cls");
							return;
						}
						//write the date when generate the report and header
						fprintf(allReport, "                                                                                                                                                       Generate date : %02d-%02d-%d\n", currentDate, currentMonth, currentYear);
						fprintf(allReport, "                                                            ----------------------------------\n");
						fprintf(allReport, "                                                            |       Maintenance Report       |\n");
						fprintf(allReport, "                                                            ----------------------------------\n\n");

						fprintf(allReport, "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
						fprintf(allReport, "|Staff ID      Facility ID       Types         Desciption                Venue         Maximum Users       Normal Price / Hour      VIP Price / Hour        Maintenance Date     |\n");
						fprintf(allReport, "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
						//write all the facility details to the file
						while (fscanf(readFile, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", &fac.staffID, &fac.facilityID, &fac.types, &fac.description, &fac.venue, &fac.maximumUsers, &fac.normalPrice, &fac.vipPrice, &fac.d.day, &fac.d.month, &fac.d.year) != EOF) {
							if ((fac.d.day != 0) && (fac.d.month != 0) && (fac.d.year != 0)) {
								fprintf(allReport, "|%-14s%-18s%-14s%-25s%-18s%-22d%-24.2f%-22.2f%02d-%02d-%02d         |\n", fac.staffID, fac.facilityID, fac.types, fac.description, fac.venue, fac.maximumUsers, fac.normalPrice, fac.vipPrice, fac.d.day, fac.d.month, fac.d.year);
							}
						}
						fprintf(allReport, "----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
						printf("\tReport generated.\n");
						fclose(readFile);
						fclose(allReport);
					}
					else {
						printf("\tThank You...\n");
					}
				}
				break;
			default:
				//display error message
				printf("\t\tPlease enter selection (0-4).\n");
			}
			system("\tpause");
			system("cls");
		} while (reportselection != 0);
		break;
	}
}

/*------------------Member Information Function Definitions------------------*/

/// <summary>
/// Function for member module
/// </summary>
void MemberModule(char staffID[]) {
	FILE* fptr;
	double normalMemPrice = 50.00, vipMemPrice = 99.00;
	int selection, totalMember = 0, memberThisMonth = 0, memberIdMonth, memberIdYear;
	struct MemberInfo member;
	fptr = fopen("Member information.bin", "rb");

	//Check number of member created in current month
	if (fptr == NULL) {
		printf("\t\tMember information.bin cant open.\n");
		system("\tpause");
		return;
	}
	else {
		while (!feof(fptr)) {
			int freadReturn = fread(&member, sizeof(struct MemberInfo), 1, fptr);

			if (freadReturn == 1) {
				totalMember++;
				DateExtract(member.memID, "YYMM", 0, 0, &memberIdMonth, &memberIdYear);

				if (memberIdMonth == CurrentDate("MM") && memberIdYear == CurrentDate("YY")) {
					memberThisMonth++;
				}
			}
		}
		fclose(fptr);
	}

	//Display menu
	do {

		system("cls");

		selection = MemberModuleMenu(staffID);
		switch (selection) {
		case 1:
			AddMember(&memberThisMonth, normalMemPrice, vipMemPrice, staffID);
			break;
		case 2:
			SearchMember(staffID);
			break;
		case 3:
			ModifyMember(staffID);
			break;
		case 4:
			DisplayMember(staffID);
			break;
		case 5:
			MembershipManagement(normalMemPrice, vipMemPrice, staffID);
			break;
		case 6:
			MembershipReport(staffID);
			break;
		default:
			break;
		}
	} while (selection != 0);

}

/// <summary>
/// Function that add member
/// </summary>
void AddMember(int* memberNo, double normalMemPrice, double vipMemPrice, char staffID[]) {
	struct MemberInfo addMember;
	char nextMember, confirm, selection, currentMonth[3], currentYear[3], memberNum[5];
	int validation, membershipDuration, totalDurationDays;
	double membershipPrice;


	do {
		system("cls");

		FILE* writeFptr;
		writeFptr = fopen("Member information.bin", "ab");

		//Header
		printf("\t----------------\n");
		printf("\t|  Member Info |\n");
		printf("\t----------------\n");
		printf("\tstaff ID : %s \n\n", staffID);

		//Generate Member ID
		sprintf(currentMonth, "%02d", CurrentDate("MM"));
		sprintf(currentYear, "%02d", CurrentDate("YY"));
		sprintf(memberNum, "%04d", *memberNo + 1);
		strcpy(addMember.memID, currentYear);
		strcat(strcat(strcat(addMember.memID, currentMonth), "-"), memberNum);

		printf("\tMember ID : %s\n", addMember.memID);

		//Member information input
		MemberICInput(addMember.memIC);

		MemberNameInput(addMember.memName);

		MemberGenderInput(&addMember.memGender, addMember.memIC);

		MemberAddressInput(addMember.memAdd);

		MemberPhoneInput(addMember.memPhoneNo);

		validation = MemberBirthDateInput(&(addMember.memBirthDate.day), &(addMember.memBirthDate.month), &(addMember.memBirthDate.year), addMember.memIC);

		//Skip the below statement if the age didnt meet minimum requirement
		if (validation == -1) {
			printf("\nAdd another member (Y/N) ? :");
			nextMember = CharInput();
			nextMember = toupper(nextMember);
			nextMember = YesNoValidation(nextMember);
			continue;
		}

		//Membership info input
		MemberTypeInput(addMember.memType, &membershipPrice, normalMemPrice, vipMemPrice);

		MembershipDurationInput(&membershipDuration, &(addMember.memExpiry.day), &(addMember.memExpiry.month), &(addMember.memExpiry.year), "add");

		system("cls");

		do {
			//Let user to edit the member infomation and membership infomation if they want to change it
			validation = 1;
			MemberInfoDisplay(addMember);
			printf("\tMember duration        : %dyears\n", membershipDuration);
			printf("\tConfirm (Y/N) : ");
			confirm = CharInput();
			confirm = toupper(confirm);
			confirm = YesNoValidation(confirm);

			if (confirm == 'N') {
				do {
					printf("\tA - Member Info\n");
					printf("\tB - Member Type\n");
					printf("\tSelection : ");
					selection = CharInput();
					selection = toupper(selection);

					switch (selection) {
					case 'A':
						MemberInputSelection(&addMember, staffID);
						break;

					case 'B':
						MemberTypeInput(addMember.memType, &membershipPrice, normalMemPrice, vipMemPrice);

						MembershipDurationInput(&membershipDuration, &(addMember.memExpiry.day), &(addMember.memExpiry.month), &(addMember.memExpiry.year), "add");
						break;

					default:
						validation = 0;
						break;
					}
				} while (validation == 0);
			}
		} while (confirm == 'N');

		system("cls");

		//Print Invoice
		MemberInvoice(addMember, membershipDuration, membershipPrice, 0);

		//Update membership duration
		DurationCalc(CurrentDate("DD"), CurrentDate("MM"), CurrentDate("YYYY"), addMember.memExpiry.day, addMember.memExpiry.month, addMember.memExpiry.year, 0, 0, 0, &totalDurationDays, "day");

		if (strcmp(addMember.memType, "Normal") == 0) {
			addMember.normalDuration = totalDurationDays;
			addMember.vipDuration = 0;
		}
		else {
			addMember.vipDuration = totalDurationDays;
			addMember.normalDuration = 0;
		}

		//Set member register date
		addMember.memRegister.day = CurrentDate("DD");
		addMember.memRegister.month = CurrentDate("MM");
		addMember.memRegister.year = CurrentDate("YYYY");

		//Set member status to active
		strcpy(addMember.memstatus, "Active");

		//Set staff who create this member
		strcpy(addMember.staffID, staffID);

		//Update number of customer
		(*memberNo)++;

		//Ask user whether to continue to add member
		printf("\n\tAdd another member (Y/N) ? :");
		nextMember = CharInput();
		nextMember = toupper(nextMember);
		nextMember = YesNoValidation(nextMember);

		//Write into binary file
		fwrite(&addMember, sizeof(struct MemberInfo), 1, writeFptr);

		fclose(writeFptr);

	} while (nextMember == 'Y');
}

/// <summary>
/// Function that search member and display his booking history
/// </summary>
void SearchMember(char staffId[]) {
	FILE* fptr;
	struct MemberInfo memberSearch, member[99];
	Booking bkPrinted[99];
	int validation, selection, dummy;
	char staffID[8], memID[11], nextSearch, displayRecord;

	do {
		do {
			system("cls");

			validation = 1;
			printf("\t----------------\n");
			printf("\t|  Member Info |\n");
			printf("\t----------------\n");
			printf("\tstaff ID : %s \n\n", staffId);

			printf("\tSearch Member\n");
			printf("\t-------------------\n");
			printf("\tSearch by\n");
			printf("\t1 - Member info\n");
			printf("\t2 - Staff\n");

			printf("\n\tEnter selection : ");
			//Input type validation
			selection = IntInput();

			//Input range validation
			if (selection != 1 && selection != 2 && selection != 0) {
				printf("\tInvalid input detected, Enter the selection stated above.\n");
				printf("\tTry again : ");
				validation = 0;
			}

		} while (validation == 0);

		if (selection == 0) {
			break;
		}

		switch (selection) {
		case 1:
			do {
				//Member searching
				printf("\n");
				validation = MemberSearching(&memberSearch);

				if (validation == 0) {
					break;
				}

				//DIsplay searched member information
				MemberInfoDisplay(memberSearch);

				//Ask user whether to print booking history
				printf("\n\tDisplay booking history (Y/N) ? : ");
				displayRecord = CharInput();
				displayRecord = toupper(displayRecord);
				displayRecord = YesNoValidation(displayRecord);

				if (displayRecord == 'Y') {
					PrintfBookingRecord(memberSearch.memID, 'M', bkPrinted, &dummy);
				}

				//Ask user whether to search another member
				printf("\n\tSearch another member (Y/N) ? : ");
				nextSearch = CharInput();
				nextSearch = toupper(nextSearch);
				nextSearch = YesNoValidation(nextSearch);
			} while (nextSearch == 'Y');
			break;

		case 2:

			do {
				fptr = fopen("Member information.bin", "rb");

				system("cls");
				//Search staff id
				printf("\tMember searching by staff id\n");
				printf("\t-------------------------------------\n");
				staffIDInput(staffID);
				strupr(staffID);

				printf("\n\n\t-----------------------------------\n");
				printf("\tMember added by staff %s\n", staffID);
				printf("\t-----------------------------------\n\n");

				//Display member record created by that particular staff
				printf("\t--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
				printf("\t| %-9s | %-41s | %-12s | %-6s | %-10s | %-12s | %-11s | %-11s | %-12s | %-15s |\n", "Member ID", "Member Name",
					"Member IC", "Gender", "Birth date", "Phone number", "Member Type", "Expiry Date", "VIP duration", "Normal duration");
				printf("\t--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

				int numRecord = 0;
				while (!feof(fptr)) {
					int freadReturn = fread(&memberSearch, sizeof(struct MemberInfo), 1, fptr);

					if (freadReturn == 1) {
						if (strcmp(memberSearch.staffID, staffID) == 0) {
							member[numRecord] = memberSearch;

							int vipDurationDay, vipDurationMonth, vipDurationYear, normalDurationDay, normalDurationMonth, normalDurationYear;
							DurationCalc(0, 0, 0, 0, 0, 0, &vipDurationDay, &vipDurationMonth, &vipDurationYear, &memberSearch.vipDuration, "duration");
							DurationCalc(0, 0, 0, 0, 0, 0, &normalDurationDay, &normalDurationMonth, &normalDurationYear, &memberSearch.normalDuration, "duration");

							printf("\t| %-9s | %-41s | %-12s |    %c   | %02d-%02d-%4d |  %-11s |    %-6s   | %02d-%02d-%4d  |   %2dY %2dM    |     %2dY %2dM     |\n",
								memberSearch.memID, memberSearch.memName, memberSearch.memIC, memberSearch.memGender, memberSearch.memBirthDate.day,
								memberSearch.memBirthDate.month, memberSearch.memBirthDate.year, memberSearch.memPhoneNo, memberSearch.memType, memberSearch.memExpiry.day,
								memberSearch.memExpiry.month, memberSearch.memExpiry.year, vipDurationYear, vipDurationMonth, normalDurationYear, normalDurationMonth);
							numRecord++;
						}
					}
				}

				printf("\t--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

				//Quit the loop if staff id not found
				if (numRecord == 0) {
					system("cls");
					printf("\n\tStaff id not found\n");
					break;

				}
				//prompt and get member id and validate whether it created by the staff searched
				printf("\n\tEnter member id listed in the table above\n");
				printf("\tMember ID : ");
				do {

					do {
						validation = 1;
						StringInput(memID, 11);

						if (memID[4] != '-' || strlen(memID) != 9) {
							printf("\t\tInvalid member id format.\n");
							printf("\t\tTry again : ");
							validation = 0;
							continue;
						}

						for (int i = 0; i < 9; i++) {

							if (isdigit(memID[i]) == 0 && i != 4) {
								printf("\t\tInvalid member id format \n");
								printf("\t\tTry again : ");
								validation = 0;
							}
						}

					} while (validation == 0);

					validation = 0;
					for (int i = 0; i < numRecord; i++) {
						if (strcmp(member[i].memID, memID) == 0) {
							memberSearch = member[i];
							validation = 1;
							break;
						}
					}

					//Prompt message if member is not created by the member searched
					if (validation == 0) {
						printf("\t\tMember id entered not within the table.\n");
						printf("\t\tTry again : ");
					}

				} while (validation == 0);

				//Display member information
				MemberInfoDisplay(memberSearch);

				//Ask member whether display booking history
				printf("\n\tDisplay booking history (Y/N) ? : ");
				displayRecord = CharInput();
				displayRecord = toupper(displayRecord);
				displayRecord = YesNoValidation(displayRecord);

				if (displayRecord == 'Y') {
					PrintfBookingRecord(memberSearch.memID, 'M', bkPrinted, &dummy);
				}

				//Ask member whether search another staff
				printf("\n\tSearch another staff (Y/N) ? : ");
				nextSearch = CharInput();
				nextSearch = toupper(nextSearch);
				nextSearch = YesNoValidation(nextSearch);
				fclose(fptr);

			} while (nextSearch == 'Y');
			break;

		default:
			break;
		}

		//Ask member whether search again
		printf("\n\tSearch again (Y/N) ? : ");
		nextSearch = CharInput();
		nextSearch = toupper(nextSearch);
		nextSearch = YesNoValidation(nextSearch);

	} while (nextSearch == 'Y');
}

/// <summary>
/// Function that modify member information
/// </summary>
void ModifyMember(char staffID[]) {
	struct MemberInfo memberModify;
	int validation;
	char nextMember;

	do {
		system("cls");

		validation = 1;
		printf("\t----------------\n");
		printf("\t|  Member Info |\n");
		printf("\t----------------\n");
		printf("\tstaff ID : %s \n\n", staffID);

		//Member searching
		printf("\tModify Member infomation\n");
		printf("\t-------------------------\n\n");

		printf("\tSearch Member\n");
		printf("\t-------------\n");

		validation = MemberSearching(&memberModify);


		//Let user to choose which field to modify
		MemberInputSelection(&memberModify, staffID);

		system("cls");

		//Display member infomation after modified
		printf("\tModify Member infomation\n");
		printf("\t-------------------------\n");
		MemberInfoDisplay(memberModify);

		//Ask user whether to modify another member
		printf("\n\tModify next member information (Y/N) : ");
		nextMember = CharInput();
		nextMember = toupper(nextMember);
		nextMember = YesNoValidation(nextMember);

		//Update that member record in binary file
		UpdateMemberDetails(memberModify, "update");

	} while (nextMember == 'Y');
}

/// <summary>
/// Function that display all member
/// </summary
void DisplayMember(char staffID[]) {
	FILE* fptr = fopen("Member information.bin", "rb");

	struct MemberInfo memberDisplay;
	system("cls");

	printf("\t----------------\n");
	printf("\t|  Member Info |\n");
	printf("\t----------------\n");
	printf("\tstaff ID : %s \n\n", staffID);

	//Display all member
	printf("\n\tDisplay Staff\n");
	printf("\t-------------------\n\n\n");
	printf("\t--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("\t| %-9s | %-41s | %-12s | %-6s | %-10s | %-12s | %-11s | %-11s | %-12s | %-15s |\n", "Member ID", "Member Name",
		"Member IC", "Gender", "Birth date", "Phone number", "Member Type", "Expiry Date", "VIP duration", "Normal duration");
	printf("\t--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");


	while (!feof(fptr)) {
		int freadReturn = fread(&memberDisplay, sizeof(struct MemberInfo), 1, fptr);

		if (freadReturn == 1) {

			int vipDurationDay, vipDurationMonth, vipDurationYear, normalDurationDay, normalDurationMonth, normalDurationYear;
			DurationCalc(0, 0, 0, 0, 0, 0, &vipDurationDay, &vipDurationMonth, &vipDurationYear, &memberDisplay.vipDuration, "duration");
			DurationCalc(0, 0, 0, 0, 0, 0, &normalDurationDay, &normalDurationMonth, &normalDurationYear, &memberDisplay.normalDuration, "duration");

			printf("\t| %-9s | %-41s | %-12s |    %c   | %02d-%02d-%4d |  %-11s |    %-6s   | %02d-%02d-%4d  |   %2dY %2dM    |     %2dY %2dM     |\n",
				memberDisplay.memID, memberDisplay.memName, memberDisplay.memIC, memberDisplay.memGender, memberDisplay.memBirthDate.day,
				memberDisplay.memBirthDate.month, memberDisplay.memBirthDate.year, memberDisplay.memPhoneNo, memberDisplay.memType, memberDisplay.memExpiry.day,
				memberDisplay.memExpiry.month, memberDisplay.memExpiry.year, vipDurationYear, vipDurationMonth, normalDurationYear, normalDurationMonth);
		}
	}
	printf("\t--------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

	fclose(fptr);

	system("\tpause");
}

/// <summary>
/// Function that manage membership
/// </summary
void MembershipManagement(double normalMemPrice, double vipMemPrice, char staffID[]) {
	struct MemberInfo memberModify;
	int validation, membershipDuration, durationDay, durationMonth, durationYear, totalDurationDays;
	char nextMember, membertype[7];
	double lastMemberPrice, memberPrice, refund;


	do {
		system("cls");
		printf("\t----------------\n");
		printf("\t|  Member Info |\n");
		printf("\t----------------\n");
		printf("\tstaff ID : %s \n\n", staffID);

		//Search member
		printf("\tMembership Management\n");
		printf("\t------------------------\n\n");


		validation = MemberSearching(&memberModify);

		if (validation == 0) {
			printf("\n\tManage next membership (Y/N) ? : ");
			nextMember = CharInput();
			nextMember = toupper(nextMember);
			nextMember = YesNoValidation(nextMember);
			continue;
		}

		//Display member information
		MemberInfoDisplay(memberModify);

		//Store membership information to temporary buffer for calculation purpose
		strcpy(membertype, memberModify.memType);

		if (strcmp(membertype, "Normal") == 0) {
			lastMemberPrice = normalMemPrice;
		}
		else {
			lastMemberPrice = vipMemPrice;
		}

		refund = 0;

		//Prompt and get member type 
		MemberTypeInput(memberModify.memType, &memberPrice, normalMemPrice, vipMemPrice);

		//Determine the refund and membership duration based the member type before and after modify
		if ((strcmp(membertype, "Normal") == 0 && strcmp(memberModify.memType, "Normal") == 0) || (strcmp(membertype, "VIP") == 0 && strcmp(memberModify.memType, "VIP") == 0)) {

			MembershipDurationInput(&membershipDuration, &(memberModify.memExpiry.day), &(memberModify.memExpiry.month), &(memberModify.memExpiry.year), "update");
			DurationCalc(CurrentDate("DD"), CurrentDate("MM"), CurrentDate("YYYY"), memberModify.memExpiry.day, memberModify.memExpiry.month, memberModify.memExpiry.year, &durationDay, &durationMonth, &durationYear, &totalDurationDays, "day");

			if (strcmp(membertype, "Normal") == 0) {
				memberModify.normalDuration += totalDurationDays;
			}
			else {
				memberModify.vipDuration += totalDurationDays;
			}

		}
		else {
			DurationCalc(CurrentDate("DD"), CurrentDate("MM"), CurrentDate("YYYY"), memberModify.memExpiry.day, memberModify.memExpiry.month, memberModify.memExpiry.year, &durationDay, &durationMonth, &durationYear, &totalDurationDays, "day");
			DurationCalc(CurrentDate("DD"), CurrentDate("MM"), CurrentDate("YYYY"), memberModify.memExpiry.day, memberModify.memExpiry.month, memberModify.memExpiry.year, &durationDay, &durationMonth, &durationYear, &totalDurationDays, "duration");

			if (strcmp(memberModify.memstatus, "Active") == 0) {
				if (durationYear > 0) {
					refund = (durationYear * lastMemberPrice / 2);
				}

				if (durationMonth >= 6) {
					refund = refund + (lastMemberPrice / 4);
				}
			}

			//Enter the membership duration
			MembershipDurationInput(&membershipDuration, &(memberModify.memExpiry.day), &(memberModify.memExpiry.month), &(memberModify.memExpiry.year), "add");

			//Update membership duration
			if (strcmp(membertype, "Normal") == 0) {
				memberModify.normalDuration -= totalDurationDays;
				DurationCalc(CurrentDate("DD"), CurrentDate("MM"), CurrentDate("YYYY"), memberModify.memExpiry.day, memberModify.memExpiry.month, memberModify.memExpiry.year, &durationDay, &durationMonth, &durationYear, &totalDurationDays, "day");
				memberModify.vipDuration += totalDurationDays;

			}
			else {
				memberModify.vipDuration -= totalDurationDays;
				DurationCalc(CurrentDate("DD"), CurrentDate("MM"), CurrentDate("YYYY"), memberModify.memExpiry.day, memberModify.memExpiry.month, memberModify.memExpiry.year, &durationDay, &durationMonth, &durationYear, &totalDurationDays, "day");
				memberModify.normalDuration += totalDurationDays;
			}
		}

		system("cls");

		printf("\t----------------\n");
		printf("\t|  Member Info |\n");
		printf("\t----------------\n");
		printf("\tstaff ID : %s \n\n", staffID);

		printf("\tMembership Management\n");
		printf("\t-------------------------\n");

		//Print invoice
		MemberInvoice(memberModify, membershipDuration, memberPrice, refund);

		//Ask user whether want to manage next membership
		printf("\n\tManage next membership (Y/N) ? : ");
		nextMember = CharInput();
		nextMember = toupper(nextMember);
		nextMember = YesNoValidation(nextMember);

		//Update member record to binary file
		UpdateMemberDetails(memberModify, "update");

	} while (nextMember == 'Y');
}

/// <summary>
/// Function that display membership report
/// </summary
void MembershipReport(char staffID[]) {
	struct MemberInfo;
	int selection;
	int validation;

	do {
		system("cls");

		//Display report menu 
		selection = MemberReportMenu(staffID);
		switch (selection) {
		case 1:
			do {
				validation = 1;
				//Display member loyalty report menu
				selection = MemberLoyaltyReportMenu(staffID);
				switch (selection) {
				case 1:
					//Display all Member Loyalty Report
					MemberLoyaltyReport("all");
					break;

				case 2:
					//Display VIP Member Loyalty Report
					MemberLoyaltyReport("vip");
					break;

				case 3:
					//Display Normal Member Loyalty Report
					MemberLoyaltyReport("normal");
					break;

				default:
					validation = 0;
					break;
				}


			} while (validation == 0);

			break;
		case 2:
			//Display Member Duration Report
			MemberDurationReport();
			break;

		case 3:
			do {
				validation = 1;

				selection = MemberStatusReportMenu(staffID);
				switch (selection) {
				case 1:
					//Display Active Member Report
					MemberStatusReport("active");
					break;

				case 2:
					//Display Inactive Member Duration Report
					MemberStatusReport("inactive");
					break;

				default:
					validation = 0;
					break;
				}


			} while (validation == 0);
			break;

		default:
			break;
		}
	} while (selection != 0);
}

/*------------------Booking Module Function Definitions------------------*/

/// <summary>
/// The booking module.
/// </summary>
/// <param name="staffIDLogin">Stores the current staff ID logged in to the program.</param>
void BookingModule(char staffIDLogin[]) {
	system("cls");
	//Used to store the staff name of the staff logged in.
	char staffName[46] = "";

	//Used to store the staff details from reading the StaffInfo.bin
	struct Staff staffInfo;

	//Used to store the output of SearchBooking
	Booking bkSearchResults[99];

	//Used to store the output of SearchBooking
	int searchResultCount;

	//Used to store the staff ID to be passed on to other functions
	Booking bk;

	//strcpy(bk.staffId, "ST-001");
	//strcpy(staffName, "LIM YU HER");

	//Store the staff ID of the current staff logged in.
	strcpy(bk.staffId, staffIDLogin);

	//Finding and storing the staff name.
	FILE* staffFp = fopen("StaffInfo.bin", "rb");

	if (!staffFp) {
		printf("\t\tCould not open StaffInfo.bin\n");
		system("\tpause");
		return;
	}

	while (fread(&staffInfo, sizeof(struct Staff), 1, staffFp) != 0) {
		if (strcmp(staffIDLogin, staffInfo.sAccount.id) == 0) {
			strcpy(staffName, staffInfo.name);
		}
	}

	fclose(staffFp);

	int selection;
	do {
		system("cls");
		//submenu for booking module.
		selection = BookingMenu(bk.staffId, staffName);
		switch (selection)
		{
		case 0:
			printf("\tReturning to main menu...\n");
			break;
		case 1:
			DisplayBooking(bk.staffId, staffName, "displayFunc");
			break;
		case 2:
			SearchBooking(bk.staffId, staffName, "searchFunc", bkSearchResults, &searchResultCount);
			break;
		case 3:
			AddBooking(bk.staffId, staffName);
			break;
		case 4:
			ModifyBooking(bk.staffId, staffName);
			break;
		case 5:
			CancelBooking(bk.staffId, staffName);
			break;
		case 6:
			MonthlyBookingSummary(bk.staffId, staffName);
			break;
		default:
			system("cls");
			printf("\t\tPlease choose one from the selection (0-6).\n");
			system("\tpause");
			system("cls");
		}
	} while (selection != 0);


	system("\tpause");
}

/// <summary>
/// Function to add a new booking.
/// </summary>
/// <param name="staffId">Used to print the currently working staff ID</param>
/// <param name="staffName">Used to print the currently working staff name</param>
void AddBooking(char* staffId, char* staffName) {
	system("cls");
	//Used to store the member ID for validation.
	struct MemberInfo mInfo;

	//Used to store the input details for current booking record.
	Booking bk;

	//Used to store the number of booking details available.
	int bCount;
	//Used to confirm booking.
	char bConfirmation;
	//Figure out the current number of booking records.
	bCount = BookingCount();

	//Used to store user's choice on starting the process of adding booking.
	int addConfirmation;

	//Loop control variable
	char cont;
	do {
		system("cls");
		//open bookingList.bin
		FILE* addBooking;

		addBooking = fopen("bookingList.bin", "ab");

		//validate file opening.
		if (!addBooking) {
			printf("\t\tError! Unable to open bookingList.bin\n");
			system("\tpause");
			system("cls");
			return;
		}

		BookingHeader(staffId, staffName, 3);

		//Store the current staffId into structure, bk.
		sprintf(bk.staffId, staffId);
		//increment the booking count to reflect adding a new record.
		bCount++;
		sprintf(bk.bookingId, "BK%03d", bCount);
		printf("\tCurrent booking ID: %s\n\n", bk.bookingId);


		//Entering booking details.
		int validation;
		//Member ID input with validation.
		do {
			printf("\tMember ID Input: \n");
			printf("\tPress '1' to continue, '0' to return to booking menu : ");
			addConfirmation = IntInput();
			if (addConfirmation == 0) {
				break;
			}
			validation = MemberSearching(&mInfo);
			if (validation == 0) {
				printf("\t\tMember ID record not found.\n\n");
			}
			else {
				if (strcmp("Inactive", mInfo.memstatus) == 0) {
					validation = 0;
					printf("\t\tMember is inactive, cannot make booking.\n\n");
				}
			}
		} while (validation == 0);

		if (addConfirmation == 0) {
			break;
		}

		//Store valid member ID and their member type.
		if (validation == 1) {
			strcpy(bk.memberId, mInfo.memID);
			strcpy(bk.memType, mInfo.memType);
		}


		printf("\n");

		//facility type selection
		printf("\tChoose the facility type that you want to book : \n");
		SelectBookingFacility(bk.bookedFacility);

		system("cls");

		BookingHeader(staffId, staffName, 3);

		//Booking date input
		BookingDateInput(&bk.bookedDate.day, &bk.bookedDate.month, &bk.bookedDate.year);


		//Booking time selection
		if (SelectTimeSlot(&bk) == 0) {
			bCount--;
			printf("\t\tCustomer cancelled booking.\n");
			//Ask whether user want to continue adding new bookings.
			printf("\tAdd more bookings? (Y/N): ");
			cont = YesNoValidation(toupper(CharInput()));
			if (cont == 'Y') {
				continue;
			}
			else {
				break;
			}
		}

		//Remarks input.
		RemarksInput(bk.remarks);

		//Update transaction date with current date.
		bk.transactionDate.day = CurrentDate("DD");
		bk.transactionDate.month = CurrentDate("MM");
		bk.transactionDate.year = CurrentDate("YYYY");

		//Write to bookingList.bin
		printf("\tConfirm booking? (Y/N): ");
		bConfirmation = YesNoValidation(toupper(CharInput()));
		if (bConfirmation == 'Y')
			fwrite(&bk, sizeof(bk), 1, addBooking);
		else {
			printf("\tCancelling booking...\n");
			bCount--;
		}

		//close the bookingList.bin to save the record.
		fclose(addBooking);

		//Ask whether user want to continue adding new bookings.
		printf("\tAdd more bookings? (Y/N): ");
		cont = YesNoValidation(toupper(CharInput()));
		system("cls");
	} while (cont == 'Y');


	printf("\tReturning to booking menu...\n");
	system("\tpause");
	system("cls");
}

/// <summary>
/// Function to search for existing bookings.
/// </summary>
/// <param name="staffId">current staff ID</param>
/// <param name="staffName">current staff name</param>
/// <param name="funcName">
/// Function name of the function that called this function.
/// SearchBooking - "searchFunc", ModifyBooking - "modifyFunc", CancelBooking - "cancelFunc"
/// </param>
/// <param name="bkPrinted">structure array: Used to store the booking records that are printed</param>
/// <param name="printCount">output parameter: Used to store the number of booking records that are printed</param>
/// <returns>the value in selection, to be used in ModifyBooking() and CancelBooking()</returns>
char SearchBooking(char* staffId, char* staffName, char funcName[], Booking bkPrinted[], int* printCount) {
	

	//Used to store the member info data
	struct MemberInfo mInfo;

	//Used to store the search data
	Booking bk;

	//Used to store the field selection that user want to search: (M, S, F, T, D, R)
	char selection;

	//Used to store the string form of the date
	char dateString[11];

	//Used to store decision on whether user want to search by month
	char monthSearch;

	//Used to store the condition on whether the record searched can be modified.
	int canBeModifiedCheck;

	//Used to store the condition on whether the record searched can be cancelled.
	int canBeCancelledCheck;

	do {
		system("cls");
		canBeModifiedCheck = 1;
		canBeCancelledCheck = 1;

		//Ensure printCount is reset to zero for every new search query.
		*printCount = 0;

		//Display booking header
		if (strcmp(funcName, "searchFunc") == 0) {
			BookingHeader(staffId, staffName, 2);
		}
		else if (strcmp(funcName, "modifyFunc") == 0) {
			BookingHeader(staffId, staffName, 4);
		}
		else if (strcmp(funcName, "cancelFunc") == 0) {
			BookingHeader(staffId, staffName, 5);
		}


		//ask user for the field to search for
		printf("\tWhich field do you want to search?\n");
		printf("\tAvailable choices:\n");
		if (strcmp(funcName, "modifyFunc") == 0 || strcmp(funcName, "cancelFunc") == 0) {
			printf("\t| Booking ID (B) | Member ID (M) | Staff ID (S) | Facility (F) | Transaction Date (T) | Booking Date (D) | Remarks (R) |\n");
			printf("\tPlease choose one (B, M, S, F, T, D, R) (0 - exit) : ");
		}
		else {
			printf("\t| Member ID (M) | Staff ID (S) | Facility (F) | Transaction Date (T) | Booking Date (D) | Remarks (R) |\n");
			printf("\tPlease choose one (M, S, F, T, D, R) (0 - exit) : ");
		}

		selection = toupper(CharInput());

		switch (selection)
		{
		case 'B':
			//Only allow search with booking ID when modifying records or cancelling records.
			if (strcmp(funcName, "modifyFunc") == 0 || strcmp(funcName, "cancelFunc") == 0) {
				BookingIDInput(bk.bookingId);
				PrintfBookingRecord(bk.bookingId, selection, bkPrinted, printCount);
			}
			else {
				printf("\t\tInvalid selection, try again.\n");
				system("\tpause");
			}
			break;
		case 'M':
			MemberSearching(&mInfo);
			PrintfBookingRecord(mInfo.memID, selection, bkPrinted, printCount);
			break;
		case 'S':
			staffIDInput(bk.staffId);
			PrintfBookingRecord(bk.staffId, selection, bkPrinted, printCount);
			break;
		case 'F':
			printf("\n\tEnter the facility type that you want to search for : \n");
			SelectBookingFacility(bk.bookedFacility);
			PrintfBookingRecord(bk.bookedFacility, selection, bkPrinted, printCount);
			break;
		case 'T':
			printf("\tTransaction Date :\n\n");
			DateInput(&bk.transactionDate.day, &bk.transactionDate.month, &bk.transactionDate.year, "date input");
			sprintf(dateString, "%02d/%02d/%04d", bk.transactionDate.day, bk.transactionDate.month, bk.transactionDate.year);
			PrintfBookingRecord(dateString, selection, bkPrinted, printCount);
			break;
		case 'D':
			printf("\tBooking Date :\n\n");
			printf("\tDo you want to search by month? (for current year) (Y/N) : ");
			monthSearch = YesNoValidation(toupper(CharInput()));

			if (monthSearch == 'Y') {
				MonthInput(&bk.bookedDate.month);
				sprintf(dateString, "%02d/%04d", bk.bookedDate.month, CurrentDate("YYYY"));
			}
			else {
				DateInput(&bk.bookedDate.day, &bk.bookedDate.month, &bk.bookedDate.year, "date input");
				sprintf(dateString, "%02d/%02d/%04d", bk.bookedDate.day, bk.bookedDate.month, bk.bookedDate.year);
			}

			PrintfBookingRecord(dateString, selection, bkPrinted, printCount);
			break;
		case 'R':
			printf("\tEnter remarks to be searched for : ");
			StringInput(bk.remarks, 22);
			PrintfBookingRecord(bk.remarks, selection, bkPrinted, printCount);
			break;
		case '0':
			printf("\n\tReturning to booking menu...\n");
			break;
		default:
			printf("\t\tInvalid selection, try again.\n");
			canBeModifiedCheck = 0;
			canBeCancelledCheck = 0;
			system("\tpause");
		}

		//return selection only if the calling function is modifyFunc or cancelFunc
		if (strcmp(funcName, "modifyFunc") == 0 && canBeModifiedCheck == 1 || strcmp(funcName, "cancelFunc") == 0 && canBeCancelledCheck == 1) {
			return selection;
		}

	} while (selection != '0');


	system("\tpause");
}

/// <summary>
/// Function to modify booking details.
/// </summary>
/// <param name="staffId">Current staff ID</param>
/// <param name="staffName">Current staff name</param>
void ModifyBooking(char* staffId, char* staffName) {
	//Used to store the all the booking records
	Booking bk[99];
	int bkSize = 99, bCount;

	//Used to store user input to be compared with during modification.
	Booking bkUserInput;

	//Used to store the searched results
	Booking bkSearchResult[99];

	//Used to store the number of search results
	int searchResultCount;

	//Used to store the field that user choose to modify (F, D, T, R).
	char selection;

	//Used to store the status of searching, if 0 means user wants to return to main menu.
	char searchStatus;

	//Used to store the confirmation of user to modify record.
	char confirmation;

	//Used to determine if a record was modified.
	int modifiedCheck;

	//Used to store the condition on whether to restart the search again.
	int searchAgainCheck;

	//Used to store the condition on whether if the booking ID selected for modification matches the search results.
	int bkIdMatchCheck;

	//Used to store the condition on whether or not the booking record chosen is allowed to be modified.
	int modifiableCheck;

	//Time object to store the current date.
	time_t currentDateTimeObj;

	//Time object to store the booking date.
	time_t bookingDateTimeObj;

	//Used to store the time difference in days between booking date and current date.
	double dayDifferenceBkDate;


	do {
		//Read the booking list and store all the records in bk.
		ReadBookingList(bk, bkSize, &bCount);

		modifiedCheck = 1;

		modifiableCheck = 1;

		searchStatus = SearchBooking(staffId, staffName, "modifyFunc", bkSearchResult, &searchResultCount);

		if (searchStatus == '0') {
			break;
		}

		printf("\n\tEditing conditions: \n");
		printf("\t\t- The transaction of the booking edited was performed today OR\n");
		printf("\t\t- There is at least 7 days before the booking date for the record to be edited.\n");

		printf("\n\tIf not one of the above conditions are satisfied, booking record cannot be edited.\n\n");

		//Ask user to choose the booking ID they want to modify only if there are search results.
		if (searchStatus != 'B' && searchResultCount != 0) {
			do {
				bkIdMatchCheck = 0;

				printf("\n\tEnter the booking ID of the booking record that you want to edit : \n");
				BookingIDInput(bkUserInput.bookingId);

				//Displaying the table headers.
				BookingTableHeader();


				for (int i = 0; i < searchResultCount; i++) {
					if (strcmp(bkUserInput.bookingId, bkSearchResult[i].bookingId) == 0) {
						PrintSingleRecord(bkSearchResult[i]);
						bkIdMatchCheck = 1;
						break;
					}
				}
				printf("\t---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");


				//Restart the loop if no matching booking IDs are found.
				if (bkIdMatchCheck == 1) {
					break;
				}
				else {
					printf("\t\tNo matching booking ID, try again.\n");
					continue;
				}

			} while (1);

		}
		//User chose to search by booking ID
		else {
			if (searchResultCount != 0)
				strcpy(bkUserInput.bookingId, bkSearchResult[0].bookingId);
			else {
				//give selection empty input to restart the loop.
				selection = ' ';
				continue;
			}
		}

		/*CHECK WHETHER THE BOOKING ID INPUTTED CAN BE MODIFIED OR NOT*/
		/*------------------------------------------------------------------------*/

		for (int i = 0; i < bCount; i++) {
			if (strcmp(bkUserInput.bookingId, bk[i].bookingId) == 0) {

				//Create time objects for the booking date and current date.
				//This is used to get the difference in days between dates.
				CreateTimeObj(bk[i].bookedDate.day, bk[i].bookedDate.month, bk[i].bookedDate.year, &bookingDateTimeObj);

				CreateTimeObj(CurrentDate("DD"), CurrentDate("MM"), CurrentDate("YYYY"), &currentDateTimeObj);

				//Calculate the difference between booking date and current date in days.
				dayDifferenceBkDate = difftime(bookingDateTimeObj, currentDateTimeObj) / 86400;

				//Allow modification if transaction date is the same with current date OR there is still at least seven days before the booking date for that record.
				if (bk[i].transactionDate.day == CurrentDate("DD") && bk[i].transactionDate.month == CurrentDate("MM") && bk[i].transactionDate.year == CurrentDate("YYYY")) {
					modifiableCheck = 1;
				}
				else if (dayDifferenceBkDate >= 7) {
					modifiableCheck = 1;
				}
				else {
					modifiableCheck = 0;
				}

				break;

			}
		}

		if (modifiableCheck == 0) {
			printf("\n\tThe record chosen cannot be modified.\n");
			printf("\tReason:\n");
			printf("\t\t- The transaction for this booking is not done today OR\n");
			printf("\t\t- There is less than 7 days before the booking date for this record.\n\n");

			//Restart the loop since this booking ID cannot be modified.
			selection = ' ';

			system("\tpause");
			continue;
		}

		/*------------------------------------------------------------------------*/

		do {

			searchAgainCheck = 0;

			printf("\n\tWhich field do you want to edit?\n");
			printf("\tAvailable choices:\n");
			printf("\t| Facility (F) | Date (D) | Time (T) | Remarks (R)|\n");
			printf("\tPlease choose one (F, D, T, R) (0 - exit) : ");

			selection = toupper(CharInput());

			switch (selection)
			{
			case 'F':

				for (int i = 0; i < bCount; i++) {
					if (strcmp(bkUserInput.bookingId, bk[i].bookingId) == 0) {
						printf("\n\tEnter the new facility type : \n");
						//Input validation to ensure a different facility is inputted.
						do {
							//store the current facility in bkUserInput.bookedFacility
							strcpy(bkUserInput.bookedFacility, bk[i].bookedFacility);

							SelectBookingFacility(bk[i].bookedFacility);

							if (strcmp(bkUserInput.bookedFacility, bk[i].bookedFacility) == 0) {
								printf("\t\tYou did not pick another facility type. Try again.\n\n");
							}

						} while (strcmp(bkUserInput.bookedFacility, bk[i].bookedFacility) == 0);

						//If user cannot find suitable time
						if (SelectTimeSlot(&bk[i]) == 0) {
							printf("\tRecord was not modified.\n");
							system("\tpause");
							modifiedCheck = 0;
							searchAgainCheck = 1;
						}
						break;
					}
				}

				break;
			case 'D':

				for (int i = 0; i < bCount; i++) {
					if (strcmp(bkUserInput.bookingId, bk[i].bookingId) == 0) {

						//Input validation to ensure user inputs a different booking date.
						do {
							//store the current booked date
							bkUserInput.bookedDate.day = bk[i].bookedDate.day;
							bkUserInput.bookedDate.month = bk[i].bookedDate.month;
							bkUserInput.bookedDate.year = bk[i].bookedDate.year;

							printf("\n\tEnter the new booking date: \n");
							BookingDateInput(&bk[i].bookedDate.day, &bk[i].bookedDate.month, &bk[i].bookedDate.year);

							if (bk[i].bookedDate.day == bkUserInput.bookedDate.day && bk[i].bookedDate.month == bkUserInput.bookedDate.month && bk[i].bookedDate.year == bkUserInput.bookedDate.year) {
								printf("\t\tYou did not pick a different booking date. Try again.\n\n");
							}

						} while (bk[i].bookedDate.day == bkUserInput.bookedDate.day && bk[i].bookedDate.month == bkUserInput.bookedDate.month && bk[i].bookedDate.year == bkUserInput.bookedDate.year);


						//If user cannot find suitable time
						if (SelectTimeSlot(&bk[i]) == 0) {
							printf("\tRecord was not modified.\n");
							system("\tpause");
							modifiedCheck = 0;
							searchAgainCheck = 1;
						}
						break;
					}
				}

				break;
			case 'T':

				for (int i = 0; i < bCount; i++) {

					if (strcmp(bkUserInput.bookingId, bk[i].bookingId) == 0) {

						//Store the current booking time and facility ID
						strcpy(bkUserInput.bookedTime, bk[i].bookedTime);
						strcpy(bkUserInput.facilityId, bk[i].facilityId);

						//Empty the current booking time and facility ID
						/*------------------------------------------------------------------*/
						FILE* emptyTime = fopen("bookingList.bin", "wb");

						if (!emptyTime) {
							printf("\t\tCould not open bookingList.bin\n");
							return;
						}

						strcpy(bk[i].bookedTime, "");
						strcpy(bk[i].facilityId, "");

						fwrite(&bk, sizeof(Booking), bCount, emptyTime);

						fclose(emptyTime);
						/*------------------------------------------------------------------*/


						//If user cannot find suitable time
						if (SelectTimeSlot(&bk[i]) == 0) {
							printf("\tRecord was not modified.\n");
							system("\tpause");

							//Store back the original booking time and facility ID.
							/*------------------------------------------------------------------*/
							FILE* resetTime = fopen("bookingList.bin", "wb");

							if (!resetTime) {
								printf("\t\tCould not open bookingList.bin\n");
								return;
							}

							strcpy(bk[i].bookedTime, bkUserInput.bookedTime);
							strcpy(bk[i].facilityId, bkUserInput.facilityId);

							fwrite(&bk, sizeof(Booking), bCount, resetTime);

							fclose(resetTime);
							/*------------------------------------------------------------------*/

							modifiedCheck = 0;
							searchAgainCheck = 1;
						}

						break;
					}

				}

				break;
			case 'R':
				for (int i = 0; i < bCount; i++) {
					if (strcmp(bkUserInput.bookingId, bk[i].bookingId) == 0) {
						printf("\n\tEnter the new remark : \n");
						RemarksInput(bk[i].remarks);
						break;
					}
				}
				break;
			case '0':
				modifiedCheck = 0;
				searchAgainCheck = 1;
				printf("\n\tRestarting search...\n");
				system("\tpause");
				break;
			default:
				modifiedCheck = 0;
				printf("\t\tInvalid selection, try again.\n");
				system("\tpause");

			}



			if (selection != '0' && modifiedCheck == 1) {

				printf("\tAre you sure you want to modify this record? (Y/N) : ");
				confirmation = YesNoValidation(toupper(CharInput()));
				if (confirmation == 'Y') {
					//Update bookingList.bin after each changes.
					FILE* modifyBk = fopen("bookingList.bin", "wb");

					if (!modifyBk) {
						printf("\t\tCould not open bookingList.bin\n");
						return;
					}

					fwrite(&bk, sizeof(Booking), bCount, modifyBk);

					//close the bookingList.bin to save the records.
					fclose(modifyBk);

					printf("\tRecord successfuly modified.\n");
				}
				else {
					printf("\tRecord was not modified.\n");
				}
				system("\tpause");

				break;
			}
			else if (searchAgainCheck == 1) {
				break;
			}


		} while (1);

		if (searchAgainCheck == 1) {
			selection = ' ';
			continue;
		}

	} while (selection != '0');


	system("\tpause");
	system("cls");
}

/// <summary>
/// Function to display booking details.
/// </summary>
/// <param name="staffId">accepts the staff ID.</param>
/// <param name="staffName">accepts the staff name.</param>
/// <param name="selection">Displays booking header based on selection EX - "displayFunc" displays the booking header for DisplayBooking()</param>
void DisplayBooking(char* staffId, char* staffName, char* selection) {
	system("cls");
	//Used to read booking record one by one from bookingList.bin
	Booking bk;

	//Used to store the total number of booking records.
	int bCount = 0;

	//Open bookingList.bin
	FILE* fptr;
	fptr = fopen("bookingList.bin", "rb");

	//Validate file opening.
	if (!fptr) {
		printf("\t\tCould not open bookingList.bin\n");
		system("\tpause");
		system("cls");
		return;
	}

	if (strcmp(selection, "displayFunc") == 0) {
		//Display Booking header
		BookingHeader(staffId, staffName, 1);
	}
	else if (strcmp(selection, "modifyFunc") == 0) {
		//Display Edit Booking header
		BookingHeader(staffId, staffName, 4);
	}
	else if (strcmp(selection, "searchFunc") == 0) {
		//Display Search Booking header
		BookingHeader(staffId, staffName, 2);
	}
	else if (strcmp(selection, "cancelFunc") == 0) {
		//Display Cancel Booking header
		BookingHeader(staffId, staffName, 5);
	}

	//Print today's date
	printf("\tToday's date - %02d/%02d/%04d\n\n", CurrentDate("DD"), CurrentDate("MM"), CurrentDate("YYYY"));

	//Printing booking details.
	/*---------------------------------------------------*/
	BookingTableHeader();

	//read from bookingList.bin
	while (fread(&bk, sizeof(bk), 1, fptr) != 0) {
		bCount++;
		//print the booking record read.
		PrintSingleRecord(bk);
	}

	printf("\t---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

	printf("\t< %d booking records >\n", bCount);

	/*---------------------------------------------------*/

	//close bookingList.bin
	fclose(fptr);

	if (strcmp(selection, "displayFunc") == 0) {
		system("\tpause");
		system("cls");
	}

}

/// <summary>
/// Function to delete a booking entry and store it in bookingRefundList.bin
/// </summary>
/// <param name="staffId">Current staff ID</param>
/// <param name="staffName">Current staff Name</param>
void CancelBooking(char* staffId, char* staffName) {
	//Used to store the all the booking records
	Booking bk[99];
	int bkSize = 99;

	//Number of booking records in the bookingList.bin
	int bCount;

	//Used to store user input for comparing when cancelling.
	Booking bkUserInput;

	//Used to store the searched results
	Booking bkSearchResult[99];

	//Used to store the number of search results
	int searchResultCount;

	//Used to store the status of searching, if 0 means user wants to return to main menu.
	char searchStatus;

	//Used to store the confirmation of user to delete record.
	char cancelConfirmation;

	//Used to store the condition on whether if the booking ID selected for cancelling matches the search results.
	int bkIdMatchCheck;

	//Used to store (Y/N) if user want to continue cancelling booking records.
	int cont;

	//Time object to store the current date.
	time_t currentDateTimeObj;

	//Time object to store the booking date.
	time_t bookingDateTimeObj;

	//Used to store the time difference in days between booking date and current date.
	double dayDifferenceBkDate;

	//The refund rate for customers
	const float REFUND_RATE = 0.5;

	//Used to store whether the booking record can be cancelled or not.
	int cancellableCheck;

	//Used to store whether the booking record is deleted or not from bookingList.bin
	int deleteCheck;


	do {
		cont = 'Y';

		cancellableCheck = 0;

		//Read the booking list and store all the records in bk.
		ReadBookingList(bk, bkSize, &bCount);

		searchStatus = SearchBooking(staffId, staffName, "cancelFunc", bkSearchResult, &searchResultCount);

		if (searchStatus == '0') {
			break;
		}

		printf("\n\tCancelling Details: \n");
		printf("\tMember type:\n");
		printf("\t\tVIP: \tcancel 3 days before booking date - 50%% REFUND\n");
		printf("\t\tNormal: cancel 5 days before booking date - 50%% REFUND\n");
		printf("\t\tANY: \tcancel 7 days before booking date - FULL REFUND\n");
		printf("\n\tIf not one of the above conditions are satisfied, NO REFUND will be given.\n\n");

		//Ask user to choose the booking ID they want to cancel only if there are search results.
		if (searchStatus != 'B' && searchResultCount != 0) {
			do {
				bkIdMatchCheck = 0;

				printf("\tEnter the booking ID of the booking record that you want to cancel : \n");
				BookingIDInput(bkUserInput.bookingId);

				//Displaying the table headers.
				BookingTableHeader();

				for (int i = 0; i < searchResultCount; i++) {
					if (strcmp(bkUserInput.bookingId, bkSearchResult[i].bookingId) == 0) {
						PrintSingleRecord(bkSearchResult[i]);
						bkIdMatchCheck = 1;
						break;
					}
				}

				printf("\t---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

				printf("\t< %d booking records >\n", searchResultCount);

				//Restart the loop if no matching booking IDs are found.
				if (bkIdMatchCheck == 1) {
					break;
				}
				else {
					printf("\t\tNo matching booking ID, try again.\n");
					continue;
				}

			} while (1);

		}
		//User chose to search by booking ID
		else {
			if (searchResultCount != 0)
				strcpy(bkUserInput.bookingId, bkSearchResult[0].bookingId);
			else {
				cont = 'Y';
				continue;
			}
		}

		/*CHECKING IF THE RECORD CHOSEN CAN BE CANCELLED*/
		/*------------------------------------------------------------------------------------*/

		for (int i = 0; i < bCount; i++) {
			if (strcmp(bkUserInput.bookingId, bk[i].bookingId) == 0) {

				//Create time objects for the booking date and current date.
				//This is used to get the difference in days between dates.
				CreateTimeObj(bk[i].bookedDate.day, bk[i].bookedDate.month, bk[i].bookedDate.year, &bookingDateTimeObj);

				CreateTimeObj(CurrentDate("DD"), CurrentDate("MM"), CurrentDate("YYYY"), &currentDateTimeObj);

				//Calculate the difference between booking date and current date in days.
				dayDifferenceBkDate = difftime(bookingDateTimeObj, currentDateTimeObj) / 86400;

				//Allow cancellation if current date is before booking date.
				if (dayDifferenceBkDate > 0) {
					cancellableCheck = 1;
				}
			}
		}

		if (cancellableCheck == 0) {
			printf("\n\t\tThis record cannot be cancelled, Reason: \n");
			printf("\t\t\t- Records must be cancelled at least a day before booking date.\n\n");

			//Restart the loop
			cont = 'Y';

			system("\tpause");
			continue;
		}

		/*------------------------------------------------------------------------------------*/


		/*CANCELLING SELECTED RECORD*/
		/*------------------------------------------------------------------------------------*/

		for (int i = 0; i < bCount; i++) {
			if (strcmp(bkUserInput.bookingId, bk[i].bookingId) == 0) {

				//Create time objects for the booking date and current date.
				//This is used to get the difference in days between dates.
				CreateTimeObj(bk[i].bookedDate.day, bk[i].bookedDate.month, bk[i].bookedDate.year, &bookingDateTimeObj);

				CreateTimeObj(CurrentDate("DD"), CurrentDate("MM"), CurrentDate("YYYY"), &currentDateTimeObj);


				//Calculate the difference between booking date and current date in days.
				dayDifferenceBkDate = difftime(bookingDateTimeObj, currentDateTimeObj) / 86400;

				//Allow full refund if cancel at least 7 days before booking date.
				if (dayDifferenceBkDate >= 7) {
					bk[i].bookingPrice = 0.00;
					strcpy(bk[i].remarks, "REFUNDED");

					//Store refund date
					bk[i].refundDate.day = CurrentDate("DD");
					bk[i].refundDate.month = CurrentDate("MM");
					bk[i].refundDate.year = CurrentDate("YYYY");
				}
				else {
					//Allow 50% refund if member is normal type and he cancels at least 5 days before 
					if (strcmp(bk[i].memType, "Normal") == 0) {

						if (dayDifferenceBkDate >= 5) {
							bk[i].bookingPrice *= REFUND_RATE;
							strcpy(bk[i].remarks, "50% REFUNDED");
						}
						//No refund
						else {
							strcpy(bk[i].remarks, "CANCELLED");
						}

					}
					//Allow 50% refund if member is VIP type and he cancels at least 3 days before.
					else {

						if (dayDifferenceBkDate >= 3) {
							bk[i].bookingPrice *= REFUND_RATE;
							strcpy(bk[i].remarks, "50% REFUNDED");
						}
						//No refund
						else {
							strcpy(bk[i].remarks, "CANCELLED");
						}

					}
					//Store refund date
					bk[i].refundDate.day = CurrentDate("DD");
					bk[i].refundDate.month = CurrentDate("MM");
					bk[i].refundDate.year = CurrentDate("YYYY");
				}

				break;

			}
		}


		/*CONFIRM DELETION*/
		/*------------------------------------------------------------*/
		printf("\tAre you sure you want to cancel booking for this record? (Y/N) : ");
		cancelConfirmation = YesNoValidation(toupper(CharInput()));

		if (cancelConfirmation == 'Y') {

			//Update bookingRefundList.bin with the refunded booking record.
			for (int i = 0; i < bCount; i++) {
				if (strcmp(bkUserInput.bookingId, bk[i].bookingId) == 0) {

					FILE* storeCancelBk = fopen("bookingRefundList.bin", "ab");

					if (!storeCancelBk) {
						printf("\t\tCould not open bookingRefundList.bin\n");
						return;
					}

					fwrite(&bk[i], sizeof(Booking), 1, storeCancelBk);

					//close the bookingRefundList.bin to save the records.
					fclose(storeCancelBk);

					break;
				}
			}


			//Update bookingList.bin after each cancellation.
			FILE* cancelBk = fopen("bookingList.bin", "wb");

			if (!cancelBk) {
				printf("\t\tCould not open bookingList.bin\n");
				return;
			}

			deleteCheck = 0;
			for (int i = 0; i < bCount; i++) {
				//Do not write the cancelled record into bookingList.bin
				if (strcmp(bkUserInput.bookingId, bk[i].bookingId) == 0) {

					//Store the member type of the record to be cancelled to be used when displaying cancel status later.
					strcpy(bkUserInput.memType, bk[i].memType);

					deleteCheck = 1;
					continue;
				}

				//After the deleted record onwards, the booking ID that follows will be updated accordingly.
				if (deleteCheck == 1) {
					sprintf(bk[i].bookingId, "BK%03d", i);
				}

				fwrite(&bk[i], sizeof(Booking), 1, cancelBk);
			}


			//close the bookingList.bin to save the records.
			fclose(cancelBk);

			if (dayDifferenceBkDate >= 7) {
				printf("\tRecord successfuly cancelled: FULL REFUND\n");
			}
			else if (dayDifferenceBkDate >= 5 && strcmp(bkUserInput.memType, "Normal") == 0) {
				printf("\tRecord successfuly cancelled: 50%% REFUND\n");
			}
			else if (dayDifferenceBkDate >= 3 && strcmp(bkUserInput.memType, "VIP") == 0) {
				printf("\tRecord successfuly cancelled: 50%% REFUND\n");
			}
			else {
				printf("\tRecord successfuly cancelled: NO REFUND\n");
			}

		}
		else {
			printf("\tRecord not cancelled.\n");
		}
		/*------------------------------------------------------------*/

		/*------------------------------------------------------------------------------------*/

		printf("\tAnymore records to cancel? (Y/N) : ");
		cont = YesNoValidation(toupper(CharInput()));

	} while (cont == 'Y');

	if (cont == 'N')
		printf("\n\tReturning to booking menu...\n");

	system("\tpause");
	system("cls");
}

/// <summary>
/// Function to view the summary of bookings performed for the month chosen by the user.
/// </summary>
/// <param name="staffId">Current staff ID</param>
/// <param name="staffName">Current staff name</param>
void MonthlyBookingSummary(char* staffId, char* staffName) {
	system("cls");

	//Used to store the all the booking records
	Booking bk[99];
	int bkSize = 99;

	//Used to store the number of booking records read from bookingList.bin
	int bCount;

	//Structure variable to store the facility types provided by our company.
	Facility availableFac[99] = { 0 };

	//Variable used to keep track of the number of facility types stored.
	int facTypeCount = 0;

	//Variable used to store the number of strings that are not equal.
	int notSameCount;

	//Used to store the month selection of user on which month's summary report to see.
	int monthSelection;

	//Used to store the total earned by each facility;
	float totalFacilityEarned;

	//Used to store the total earned through bookings.
	float totalEarned;

	//Used to store the confirmation for generating monthly report.
	char genReportConfirmation;

	//Used to store the filename for the monthly report.
	char reportFilename[51] = "";

	//Used to store the number of booking records printed.
	int printCount;

	//Used to store whether user want to continue to print monthly booking summary.
	int cont;


	//READ ALL THE bookingList.bin data into structure array, bk.
	/*------------------------------------------------------*/

	ReadBookingList(bk, bkSize, &bCount);

	/*------------------------------------------------------*/



	/*STORING ALL THE AVAILABLE FACILITY TYPES*/
	/*------------------------------------------------------------------------------------------------------*/

	/*Read the Facilities.txt and store it into structure array, fac*/
	/*------------------------------------------------------------------*/

	//Read from txt file
	Facility fac[99];

	FILE* facilityPtr = fopen("Facilities.txt", "r");

	if (!facilityPtr) {
		printf("\t\tCould not open Facilities.txt\n");
		return;
	}

	//To keep count of the number of elements in the structure array, fac.
	int fCount = 0;
	//Store it into the structure array, fac
	while (fscanf(facilityPtr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", fac[fCount].staffID, fac[fCount].facilityID, fac[fCount].types, fac[fCount].description, fac[fCount].venue, &fac[fCount].maximumUsers, &fac[fCount].normalPrice, &fac[fCount].vipPrice, &fac[fCount].d.day, &fac[fCount].d.month, &fac[fCount].d.year) != EOF) {
		fCount++;
	}

	fclose(facilityPtr);

	/*------------------------------------------------------------------*/

	/*TAKING ONLY FACILITY TYPES FROM THE ALL THE Facilties.txt DATA*/
	/*------------------------------------------------------------------*/

	//Take the facility type from Facilities.txt and store it into structure array, availableFac
	for (int i = 0; i < fCount; i++) {
		//store the first facility name into structure array, availableFac.
		if (i == 0) {
			strcpy(availableFac[i].types, fac[i].types);
			facTypeCount++;
		}
		//For entries other than the first, check with the current stored facilities 
		//in structure array, availableFac.
		//Add the new facility name if it was not already in 
		//the current stored facilities in structure array, availableFac.
		else {
			notSameCount = 0;
			for (int j = 0; j < facTypeCount; j++) {

				if (strcmp(availableFac[j].types, fac[i].types) == 0) {
					continue;
				}
				else {
					notSameCount++;
					if (notSameCount == facTypeCount) {
						strcpy(availableFac[j + 1].types, fac[i].types);
						facTypeCount++;
					}
					else {
						continue;
					}
				}

			}
		}

	}

	/*------------------------------------------------------------------*/

	/*------------------------------------------------------------------------------------------------------*/


	BookingHeader(staffId, staffName, 6);

	monthSelection = 0;

	printf("\tEnter '1' to continue, '0' to return to booking menu : ");
	cont = IntInput();

	if (cont == 0) {
		return;
	}

	printf("\tEnter the month that you want to print the summary report for (Current year only) : \n");
	MonthInput(&monthSelection);

	//Generate filename for monthly report.
	sprintf(reportFilename, "MonthlySummaryReport%02d-%04d.txt", monthSelection, CurrentDate("YYYY"));

	//Creating the txt file to store the report.
	FILE* reportFp = fopen(reportFilename, "w");

	//Validate file opening.
	if (!reportFp) {
		printf("\t\tCould not open %s.txt\n", reportFilename);
		system("\tpause");
		return;
	}


	printf("\n\tMonthly Summary Report for %02d/%04d : \n\n", monthSelection, CurrentDate("YYYY"));
	fprintf(reportFp, "Monthly Summary Report for %02d/%04d : \n\n", monthSelection, CurrentDate("YYYY"));

	totalEarned = 0.00;

	//For each facility type, print the booking records and their total earned.
	for (int i = 0; i < facTypeCount; i++) {
		printCount = 0;
		totalFacilityEarned = 0.00;

		printf("\t%s : \n", availableFac[i].types);
		fprintf(reportFp, "%s : \n", availableFac[i].types);

		BookingTableHeader();
		FprintBookingTableHeader(reportFp);

		for (int j = 0; j < bCount; j++) {
			if (strcmp(bk[j].bookedFacility, availableFac[i].types) == 0 && bk[j].transactionDate.month == monthSelection && bk[j].transactionDate.year == CurrentDate("YYYY")) {
				PrintSingleRecord(bk[j]);
				FprintSingleRecord(bk[j], reportFp);
				totalFacilityEarned += bk[j].bookingPrice;
				printCount++;
			}
		}

		if (printCount == 0) {
			printf("\tNo booking records found.\n");
			fprintf(reportFp, "No booking records found.\n");
		}

		printf("\t---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		fprintf(reportFp, "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

		printf("\t< %d booking records >\n", printCount);
		fprintf(reportFp, "< %d booking records >\n", printCount);

		//Store the total earned by this faciilty into total earned overall.
		totalEarned += totalFacilityEarned;

		printf("\tTotal earned : RM %.2f\n", totalFacilityEarned);
		printf("\n\n");

		fprintf(reportFp, "Total earned : RM %.2f\n", totalFacilityEarned);
		fprintf(reportFp, "\n\n");
	}

	/*READ bookingRefundList.bin*/
	/*--------------------------------------------------------*/

	Booking refundList[99];
	int refundCount = 0, refundSize = 99;

	do {
		FILE* refundFp = fopen("bookingRefundList.bin", "rb");

		if (!refundFp) {
			//If no file to be read, create one.
			FILE* createRefundFp = fopen("bookingRefundList.bin", "ab");

			if (!createRefundFp) {
				printf("\t\tCould not open bookingRefundList.bin\n");
				system("\tpause");
				return;
			}

			fclose(createRefundFp);
			continue;

		}

		//Read the bookingRefundList.bin and store the number of refunded booking records available.
		refundCount = fread(&refundList, sizeof(Booking), refundSize, refundFp);

	} while (refundCount < 0);


	/*--------------------------------------------------------*/

	printf("\tREFUNDED RECORDS : \n");
	printf("\t==================\n\n");
	fprintf(reportFp, "REFUNDED RECORDS : \n");
	fprintf(reportFp, "==================\n\n");
	//For each facility type, print the refunded booking records and their total earned.
	for (int i = 0; i < facTypeCount; i++) {
		printCount = 0;
		totalFacilityEarned = 0.00;

		printf("\t%s : \n", availableFac[i].types);
		fprintf(reportFp, "%s : \n", availableFac[i].types);

		RefundTableHeader();
		FprintRefundTableHeader(reportFp);

		for (int j = 0; j < refundCount; j++) {
			if (strcmp(refundList[j].bookedFacility, availableFac[i].types) == 0 && refundList[j].transactionDate.month == monthSelection && refundList[j].transactionDate.year == CurrentDate("YYYY")) {
				PrintSingleRefundRecord(refundList[j]);
				FprintSingleRefundRecord(refundList[j], reportFp);
				totalFacilityEarned += refundList[j].bookingPrice;
				printCount++;
			}
		}

		if (printCount == 0) {
			printf("\tNo refund records found.\n");
			fprintf(reportFp, "No refund records found.\n");
		}


		printf("\t-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		fprintf(reportFp, "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

		printf("\t< %d booking records >\n", printCount);
		fprintf(reportFp, "\t< %d booking records >\n", printCount);

		//Store the total earned by this faciilty into total earned overall.
		totalEarned += totalFacilityEarned;

		printf("\tTotal earned : RM %.2f\n", totalFacilityEarned);
		printf("\n\n");

		fprintf(reportFp, "\tTotal earned : RM %.2f\n", totalFacilityEarned);
		fprintf(reportFp, "\n\n");
	}

	printf("\n\tFINAL TOTAL EARNED THROUGH BOOKINGS : RM %.2f\n", totalEarned);
	fprintf(reportFp, "\nFINAL TOTAL EARNED THROUGH BOOKINGS : RM %.2f\n", totalEarned);

	//Save the txt file created.
	fclose(reportFp);

	printf("\n\tDo you want to generate Monthly Summary Report for %02d/%04d ? (Y/N) : ", monthSelection, CurrentDate("YYYY"));
	genReportConfirmation = YesNoValidation(toupper(CharInput()));


	//Print success message.
	if (genReportConfirmation == 'Y') {
		printf("\n\t%s successfully created.\n\n", reportFilename);
	}
	else {
		//Remove the file generated if user says no.
		remove(reportFilename);
	}


	printf("\n\tReturning to booking menu...\n");

	system("\tpause");
	system("cls");
}

/*------------------Facility Usage Module Function Definitions------------------*/

/// <summary>
/// To access all the available functions for the Facility Usage Module
/// </summary>
/// <param name="staffIDLogin"></param>
void FacilityUsageModule(char* staffIDLogin)
{
	int numRec = 0, facSelection;

	do
	{
		numRec = WalkInCount();

		printf("\t-----------------------\n");
		printf("\t  | Facility Usage | \n");
		printf("\t-----------------------\n");

		printf("\t%d 'Walk In' records found\n\n", numRec);

		printf("\t1 - Add Facility Usage Walk In\n");
		printf("\t2 - Display Facility Usage Walk In status\n");
		printf("\t3 - Search Facility Usage Walk In Information\n");
		printf("\t4 - Modify Facility Usage Information\n");
		printf("\t5 - Delete Facility Usage Information\n");
		printf("\t6 - Facility Usage Summary\n");
		printf("\t0 - MAIN MENU\n");

		printf("\tChoose between 0 - 6 > ");


		facSelection = IntInput();

		switch (facSelection)
		{
		case 1:
			system("cls");
			AddFacilityUsage(staffIDLogin);
			break;
		case 2:
			system("cls");
			DisplayFacilityUsageHistory(staffIDLogin);
			break;
		case 3:
			system("cls");
			SearchFacilityUsageHistory(staffIDLogin);
			break;
		case 4:
			system("cls");
			ModifyFacilityUsageHistory(staffIDLogin);
			break;
		case 5:
			system("cls");
			DeleteFacilityUsageHistory(staffIDLogin);
			break;
		case 6:
			system("cls");
			FacilityUsageSummary(staffIDLogin);
			break;
		case 0:
			system("cls");
			printf("Back to main menu");
			break;
		default:
			printf("\t====================================\n");
			printf("\t	        Wrong input\n");
			printf("\t====================================\n");
			system("pause");
		}
		system("cls");
	} while (facSelection != 0);
}

/// <summary>
/// Add Facility Usage records
/// </summary>
/// <param name="staffIDLogin"></param>
void AddFacilityUsage(char* staffIDLogin)
{
	FILE* facFptr;

	facFptr = fopen("facUsageList.txt", "a");

	if (facFptr == NULL)
	{
		printf("\tError! Could not locate facUsageList.txt");
		return;
	}

	//facUse IS NOW THE VARIABLE NAME FOR FACILITY USAGE DETAIL STRUCTURE AND CAN STORE UP TO [99] RECORDS
	facilityUsage facUse;

	//memberInfo -> member FOR THE STORING OF MEMBER INFORMATION TO CHECK IF SUCH A MEMBERID EXISTS 
	struct MemberInfo member;

	//validation TO CHECK AND SEE IF MORE RECORDS WANTS TO BE ADDED
	char cont = 'N';

	//checkSwitch IS FOR USER TO CHECK IF ALL DISPLAYED OUTPUTS ARE CORRECT
	int checkSwitch = 0;

	//numRec TO KEEP TRACK OF CURRENT NUMBER OF facUse ID
	int numRec;

	numRec = LastFacilityUseID();

	strcpy(facUse.memberID, "");
	strcpy(facUse.memberIC, "");
	strcpy(facUse.facEvent, "");
	strcpy(facUse.facID, "");
	strcpy(facUse.walkInTime, "");
	strcpy(facUse.usageType, "");
	strcpy(facUse.memberType, "");
	strcpy(facUse.remarks, "");

	facUse.walkInDate.day = CurrentDate("DD");
	facUse.walkInDate.month = CurrentDate("MM");
	facUse.walkInDate.year = CurrentDate("YYYY");

	do
	{

		do
		{
			system("cls");
			//char facUseIdDupe[5];
			sprintf(facUse.facUseID, "F%03d", numRec + 1);
			//strcpy(facUse.facUseID, facUseIdDupe);
			printf("\tfacility Usage ID > %s\n\n", facUse.facUseID);

			/*-----------------------*/

			printf("\tStaff ID > %s\n\n", staffIDLogin);
			strcpy(facUse.staffID, staffIDLogin);

			/*-----------------------*/

			if (strcmp(facUse.memberID, "") == 0 && strcmp(facUse.memberIC, "") == 0)
			{
				printf("\t1. Member ID and Member IC\n\n");
			}
			else
			{
				printf("\t1. Member ID > %s\n", facUse.memberID);
				printf("\t   Member Type > %s\n\n", facUse.memberType);
			}

			/*-----------------------*/

			if (strcmp(facUse.facEvent, "") == 0) { printf("\t2. Event\n\n"); }
			else { printf("\t2. Event > %s\n\n", facUse.facEvent); }

			/*-----------------------*/

			if (strcmp(facUse.walkInTime, "") == 0) { printf("\t3. Start Time\n\n"); }
			else { printf("\t3. Start Time > %s\n\tfacility ID > %s\n\n", facUse.walkInTime, facUse.facID); }

			/*-----------------------*/

			printf("\tUsage type > Walk In\n\n");
			strcpy(facUse.usageType, "Walk In");

			/*-----------------------*/

			if (strcmp(facUse.remarks, "") == 0) { printf("\t4. Remarks\n\n"); }
			else { printf("\t4. Remarks > %s\n\n", facUse.remarks); }

			/*-----------------------*/

			printf("\t5. Re-confirm your record details\n\n");

			/*-----------------------*/

			printf("\tPlease enter the number which you would like to add (1 - 5) > ");
			scanf("%d", &checkSwitch);

			system("cls");
			switch (checkSwitch)
			{
			case 1:
				MemberSearching(&member);
				strcpy(facUse.memberIC, member.memIC);
				strcpy(facUse.memberID, member.memID);
				strcpy(facUse.memberType, member.memType);
				break;

			case 2:

				printf("\tEvent > ");
				SelectWalkInFacilityName(facUse.facEvent);
				break;

			case 3:
				if (strcmp(facUse.facEvent, "") == 0)
				{
					printf("\tFacility events needs to be filled in.\n\n");
					break;
				}
				else
				{
					printf("\tStart Time");
					if (SelectWalkInTimeSlot(&facUse) == 0)
					{
						printf("\tTry again\n");
					}
					break;
				}
			case 4:
				printf("\tRemarks > ");
				StringInput(facUse.remarks, 99);
				break;

			case 5:

				if (strcmp(facUse.memberID, "") == 0 || strcmp(facUse.facEvent, "") == 0 || strcmp(facUse.walkInTime, "") == 0 || strcmp(facUse.remarks, "") == 0)
				{
					printf("\n\tPlease fill in all of the elements.\n\n");
					system("cls");
					break;
				}
				else
				{
					printf("\n\t| %-17s | %-9s |    %-5s    | %-11s |    %-4s    |  %-9s  | %-11s | %-5s | %-10s | %-5s |          %-17s |\n\n",
						"Facility Usage ID", "Member ID", "Event", "Facility ID", "Date",
						"Time Slot", "Member Type", "Price", "Usage Type", "Staff in Charge", "Remarks");

					printf("\t| %-17s | %-9s | %-11s | %-11s | %02d/%02d/%d | %-9s | %-11s | %-5.2f | %-10s | %-5s          | %-17s          |\n",
						facUse.facUseID, facUse.memberID, facUse.facEvent, facUse.facID, facUse.walkInDate.day,
						facUse.walkInDate.month, facUse.walkInDate.year, facUse.walkInTime, facUse.memberType,
						facUse.walkInPrice, facUse.usageType, facUse.staffID, facUse.remarks);

					printf("\n\tIs the record correct (Y/N) > ");
					cont = YesNoValidation(toupper(CharInput()));
					break;
				}

			default:
				printf("\tWrong input!\n\n");
				system("pause");
				break;
			}

		} while (cont == 'N');

		fprintf(facFptr, "|%s|%s|%s|%s|%d/%d/%d|%s|%s|%.2f|%s|%s|%s|\n",
			facUse.facUseID, facUse.memberID, facUse.facEvent, facUse.facID,
			facUse.walkInDate.day, facUse.walkInDate.month, facUse.walkInDate.year,
			facUse.walkInTime, facUse.memberType, facUse.walkInPrice,
			facUse.usageType, facUse.staffID, facUse.remarks);

		//EVERYTIME THE LOOP IN AddFacilityUsage HAPPENS, numRec IS ADDED BY ONE (TO SHOW HOW MANY RECORDS HAS BEEN ADDED)
		fclose(facFptr);
		printf("\n\n\tAnymore records (Y/N) > ");
		cont = YesNoValidation(toupper(CharInput()));

		system("cls");

	} while (cont == 'Y');
}

/// <summary>
/// Display all records recorded in Facility Usage
/// </summary>
/// <param name="staffIDLogin"></param>
void DisplayFacilityUsageHistory(char* staffIDLogin)
{
	FILE* fptr;
	facilityUsage facUse;
	fptr = fopen("facUsageList.txt", "r");

	if (!fptr) {
		printf("\tError! Unable to open facUsageList.txt\n");
		system("pause");
		system("cls");
		return;
	}

	printf("\t------------------------------\n");
	printf("\t| Display Facility Usage List|\n");
	printf("\t------------------------------\n");

	//Print today's date
	printf("\tToday's date - %02d/%02d/%04d\n\n", CurrentDate("DD"), CurrentDate("MM"), CurrentDate("YYYY"));

	//Printing booking details.
	printf("\t| %-17s | %-9s |    %-5s    | %-11s |    %-4s    |  %-9s  | %-11s | %-5s | %-10s | %-5s |          %-17s |",
		"Facility Usage ID", "Member ID", "Event", "Facility ID", "Date",
		"Time Slot", "Member Type", "Price", "Usage Type", "Staff in Charge", "Remarks");
	//read from bookingList.bin

	while (fscanf(fptr, "|%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%[^|]|%[^|]|%f|%[^|]|%[^|]|%[^|]|\n",
		facUse.facUseID, facUse.memberID, facUse.facEvent, facUse.facID, &facUse.walkInDate.day,
		&facUse.walkInDate.month, &facUse.walkInDate.year, facUse.walkInTime, &facUse.memberType,
		&facUse.walkInPrice, facUse.usageType, facUse.staffID, facUse.remarks) != EOF)
	{
		printf("\n\t| %-17s | %-9s | %-11s | %-11s | %02d/%02d/%d | %-9s | %-11s | %-5.2f | %-10s | %-5s          | %-17s          |",
			facUse.facUseID, facUse.memberID, facUse.facEvent, facUse.facID, facUse.walkInDate.day,
			facUse.walkInDate.month, facUse.walkInDate.year, facUse.walkInTime, facUse.memberType,
			facUse.walkInPrice, facUse.usageType, facUse.staffID, facUse.remarks);
	}

	printf("\n\n\tHere is all the records from walk ins\n");
	printf("\tpress ENTER to exit\n");

	//close bookingList.bin
	fclose(fptr);

	system("pause");
	system("cls");
}

/// <summary>
/// To search for existing records of the Facility Usage
/// </summary>
/// <param name="staffIDLogin"></param>
void SearchFacilityUsageHistory(char* staffIDLogin)
{
	int search, numRec = 0;
	char memberID[10], facilityEvent[11], facilityUsageID[5], staffID[8], cont;

	facilityUsage facUse;

	FILE* fptr = fopen("facUsageList.txt", "r");

	if (!fptr)
	{
		printf("\tERROR! can not open file facUsageList.txt.");
		return;
	}
	do
	{
		while (fscanf(fptr, "|%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%[^|]|%[^|]|%f|%[^|]|%[^|]|%[^|]|\n",
			&facUse.facUseID, &facUse.memberID, &facUse.facEvent, &facUse.facID, &facUse.walkInDate.day,
			&facUse.walkInDate.month, &facUse.walkInDate.year, &facUse.walkInTime, &facUse.memberType,
			&facUse.walkInPrice, &facUse.usageType, facUse.staffID, &facUse.remarks) != EOF)
		{
			numRec++;
		}

		printf("\tSearch...\n");
		printf("\n\t1. Member ID  (eg. 2203-0001, 2203-0002) \n\t2. Facility Event (eg. Karaoke, Badminton) \n\t3. Facility Usage ID (eg. F000, F001) \n\t4. Staff ID (eg. ST-001, ST002)\n");
		printf("\n\tWhat would you like to search in the %d records > ", numRec);
		scanf("%d", &search);

		system("cls");
		if (search > 0 || search < 4)
		{
			switch (search)
			{

			case 1: //MEMBER ID
			{

				FILE* fptr = fopen("facUsageList.txt", "r");

				if (!fptr)
				{
					printf("\tERROR! can not open file facUsageList.txt.");
					return;
				}

				printf("\tMember ID > ");
				StringInput(memberID, 10);

				printf("\n\t| %-17s | %-9s |    %-5s    | %-11s |    %-4s    |  %-9s  | %-11s | %-5s | %-10s | %-5s |          %-17s |",
					"Facility Usage ID", "Member ID", "Event", "Facility ID", "Date",
					"Time Slot", "Member Type", "Price", "Usage Type", "Staff in Charge", "Remarks");

				while (fscanf(fptr, "|%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%[^|]|%[^|]|%f|%[^|]|%[^|]|%[^|]|\n",
					facUse.facUseID, facUse.memberID, facUse.facEvent, facUse.facID, &facUse.walkInDate.day,
					&facUse.walkInDate.month, &facUse.walkInDate.year, facUse.walkInTime, &facUse.memberType,
					&facUse.walkInPrice, facUse.usageType, facUse.staffID, facUse.remarks) != EOF)
				{

					if (strcmp(memberID, facUse.memberID) == 0)
					{
						printf("\n\t| %-17s | %-9s | %-11s | %-11s | %02d/%02d/%d | %-9s | %-11s | %-5.2f | %-10s | %-5s          | %-17s          |",
							facUse.facUseID, facUse.memberID, facUse.facEvent, facUse.facID, facUse.walkInDate.day,
							facUse.walkInDate.month, facUse.walkInDate.year, facUse.walkInTime, facUse.memberType,
							facUse.walkInPrice, facUse.usageType, facUse.staffID, facUse.remarks);
					}

				}
				fclose(fptr);
				printf("\n\n\tWant to search for other elements (Y/N) > ");
				cont = YesNoValidation(toupper(CharInput()));

				system("cls");
				break;
			}

			case 2: //FACILITY EVENT
			{
				FILE* fptr = fopen("facUsageList.txt", "r");

				if (!fptr)
				{
					printf("\tERROR! can not open file facUsageList.txt.");
					return;
				}

				printf("\tFacility Event > ");
				StringInput(facilityEvent, 11);
				UppercaseFunction(facilityEvent);

				printf("\n\t| %-17s | %-9s |    %-5s    | %-11s |    %-4s    |  %-9s  | %-11s | %-5s | %-10s | %-5s |          %-17s |",
					"Facility Usage ID", "Member ID", "Event", "Facility ID", "Date",
					"Time Slot", "Member Type", "Price", "Usage Type", "Staff in Charge", "Remarks");

				while (fscanf(fptr, "|%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%[^|]|%[^|]|%f|%[^|]|%[^|]|%[^|]|\n",
					facUse.facUseID, facUse.memberID, facUse.facEvent, facUse.facID, &facUse.walkInDate.day,
					&facUse.walkInDate.month, &facUse.walkInDate.year, facUse.walkInTime, &facUse.memberType,
					&facUse.walkInPrice, facUse.usageType, facUse.staffID, facUse.remarks) != EOF)
				{
					if (strlen(facilityEvent) <= 11)
					{
						if (strcmp(facilityEvent, facUse.facEvent) == 0)
						{
							printf("\n\t| %-17s | %-9s | %-11s | %-11s | %02d/%02d/%d | %-9s | %-11s | %-5.2f | %-10s | %-5s          | %-17s          |",
								facUse.facUseID, facUse.memberID, facUse.facEvent, facUse.facID, facUse.walkInDate.day,
								facUse.walkInDate.month, facUse.walkInDate.year, facUse.walkInTime, facUse.memberType,
								facUse.walkInPrice, facUse.usageType, facUse.staffID, facUse.remarks);
						}
					}
					else
					{
						printf("\tEntered wrong value");
						break;
					}
				}

				fclose(fptr);
				printf("\n\n\tWant to search for other elements (Y/N) > ");
				cont = YesNoValidation(toupper(CharInput()));

				system("cls");
				break;
			}
			case 3: //FACILITY USAGE ID
			{

				FILE* fptr = fopen("facUsageList.txt", "r");

				if (!fptr)
				{
					printf("\tERROR! can not open file facUsageList.txt.");
					return;
				}

				printf("\tFacility ID (eg. F001, F002)> ");
				StringInput(facilityUsageID, 5);

				printf("\n\t| %-17s | %-9s |    %-5s    | %-11s |    %-4s    |  %-9s  | %-11s | %-5s | %-10s | %-5s |          %-17s |",
					"Facility Usage ID", "Member ID", "Event", "Facility ID", "Date",
					"Time Slot", "Member Type", "Price", "Usage Type", "Staff in Charge", "Remarks");

				while (fscanf(fptr, "|%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%[^|]|%[^|]|%f|%[^|]|%[^|]|%[^|]|\n",
					facUse.facUseID, facUse.memberID, facUse.facEvent, facUse.facID, &facUse.walkInDate.day,
					&facUse.walkInDate.month, &facUse.walkInDate.year, facUse.walkInTime, &facUse.memberType,
					&facUse.walkInPrice, facUse.usageType, facUse.staffID, facUse.remarks) != EOF)
				{
					if (strcmp(facilityUsageID, facUse.facUseID) == 0)
					{
						printf("\n\t| %-17s | %-9s | %-11s | %-11s | %02d/%02d/%d | %-9s | %-11s | %-5.2f | %-10s | %-5s          | %-17s          |",
							facUse.facUseID, facUse.memberID, facUse.facEvent, facUse.facID, facUse.walkInDate.day,
							facUse.walkInDate.month, facUse.walkInDate.year, facUse.walkInTime, facUse.memberType,
							facUse.walkInPrice, facUse.usageType, facUse.staffID, facUse.remarks);
					}
				}

				fclose(fptr);
				printf("\n\n\tWant to search for other elements (Y/N) > ");
				cont = YesNoValidation(toupper(CharInput()));

				system("cls");
				break;
			}
			case 4: //STAFF ID
			{
				FILE* fptr = fopen("facUsageList.txt", "r");

				if (!fptr)
				{
					printf("\tERROR! can not open file facUsageList.txt.");
					return;
				}

				printf("\tStaff ID (eg. ST-001, ST-002)> ");
				staffIDInput(staffID);

				printf("\n\t| %-17s | %-9s |    %-5s    | %-11s |    %-4s    |  %-9s  | %-11s | %-5s | %-10s | %-5s |          %-17s |",
					"Facility Usage ID", "Member ID", "Event", "Facility ID", "Date",
					"Time Slot", "Member Type", "Price", "Usage Type", "Staff in Charge", "Remarks");

				while (fscanf(fptr, "|%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%[^|]|%[^|]|%f|%[^|]|%[^|]|%[^|]|\n",
					facUse.facUseID, facUse.memberID, facUse.facEvent, facUse.facID, &facUse.walkInDate.day,
					&facUse.walkInDate.month, &facUse.walkInDate.year, facUse.walkInTime, &facUse.memberType,
					&facUse.walkInPrice, facUse.usageType, facUse.staffID, facUse.remarks) != EOF)
				{
					if (strcmp(staffID, facUse.staffID) == 0)
					{
						printf("\n\t| %-17s | %-9s | %-11s | %-11s | %02d/%02d/%d | %-9s | %-11s | %-5.2f | %-10s | %-5s          | %-17s          |",
							facUse.facUseID, facUse.memberID, facUse.facEvent, facUse.facID, facUse.walkInDate.day,
							facUse.walkInDate.month, facUse.walkInDate.year, facUse.walkInTime, facUse.memberType,
							facUse.walkInPrice, facUse.usageType, facUse.staffID, facUse.remarks);
					}

				}

				fclose(fptr);
				printf("\n\n\tWant to search for other elements (Y/N) > ");
				cont = YesNoValidation(toupper(CharInput()));

				system("cls");
				break;
			}
			}
		}
		system("cls");
	} while (cont == 'Y');
}

/// <summary>
/// To modify records of Facility Usage
/// </summary>
/// <param name="staffIDLogin"></param>
void ModifyFacilityUsageHistory(char* staffIDLogin)
{
	struct MemberInfo member;

	facilityUsage facUse[99];

	int i = 0, checkSwitch, numRec = 0;
	char cont = 'Y';

	FILE* fptr = fopen("facUsageList.txt", "r");
	if (!fptr)
	{
		printf("\tError! could not read facUsageList.txt\n");
		return;
	}

	do
	{

		printf("\n\t|     | %-17s | %-9s |    %-5s    | %-11s |    %-4s    |  %-9s  | %-11s | %-5s | %-10s | %-5s |          %-17s |\n\n",
			"Facility Usage ID", "Member ID", "Event", "Facility ID", "Date",
			"Time Slot", "Member Type", "Price", "Usage Type", "Staff in Charge", "Remarks");

		while (fscanf(fptr, "|%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%[^|]|%[^|]|%f|%[^|]|%[^|]|%[^|]|\n",
			&facUse[i].facUseID, &facUse[i].memberID, &facUse[i].facEvent, &facUse[i].facID, &facUse[i].walkInDate.day,
			&facUse[i].walkInDate.month, &facUse[i].walkInDate.year, &facUse[i].walkInTime, &facUse[i].memberType,
			&facUse[i].walkInPrice, &facUse[i].usageType, &facUse[i].staffID, &facUse[i].remarks) != EOF)
		{
			numRec++;

			printf("\t| %02d. | %-17s | %-9s | %-11s | %-11s | %02d/%02d/%d | %-9s | %-11s | %-5.2f | %-10s | %-5s          | %-17s          |\n",
				i + 1, facUse[i].facUseID, facUse[i].memberID, facUse[i].facEvent, facUse[i].facID, facUse[i].walkInDate.day,
				facUse[i].walkInDate.month, facUse[i].walkInDate.year, facUse[i].walkInTime, facUse[i].memberType,
				facUse[i].walkInPrice, facUse[i].usageType, facUse[i].staffID, facUse[i].remarks);

			i++;
		}

		fclose(fptr);

		printf("\n\tWhat record would you like to modify ? (1 - % d)> ", i);
		scanf("%d", &numRec);
		numRec--;
		if (numRec <= i || numRec > 0)
		{
			do
			{
				system("cls");
				printf("\n\t| %-17s | %-9s | %-9s | %-11s | %d/%d/%d | %-9s | %-11s | %-5.2f | %-10s | %-5s          | %-17s          |\n\n",
					facUse[numRec].facUseID,
					facUse[numRec].memberID,
					facUse[numRec].facEvent,
					facUse[numRec].facID,
					facUse[numRec].walkInDate.day,
					facUse[numRec].walkInDate.month,
					facUse[numRec].walkInDate.year,
					facUse[numRec].walkInTime,
					facUse[numRec].memberType,
					facUse[numRec].walkInPrice,
					facUse[numRec].usageType,
					facUse[numRec].staffID,
					facUse[numRec].remarks);

				printf("\tfacility Usage ID > %s\n\n", facUse[numRec].facUseID);

				/*-----------------------*/

				printf("\tStaff ID > %s\n\n", staffIDLogin);

				/*-----------------------*/

				if (strcmp(facUse[numRec].memberID, "") == 0 && strcmp(facUse[numRec].memberIC, "") == 0)
				{
					printf("\t1. Member ID and Member Type\n\n");
				}
				else
				{
					printf("\t1. Member ID > %s\n", facUse[numRec].memberID);
					printf("\t   Member Type > %s\n\n", facUse[numRec].memberType);
				}

				/*-----------------------*/

				if (strcmp(facUse[numRec].facEvent, "") == 0) { printf("\t2. Event\n\n"); }
				else { printf("\t2. Event > %s\n\n", facUse[numRec].facEvent); }

				/*-----------------------*/

				if (strcmp(facUse[numRec].walkInTime, "") == 0) { printf("\t3. Start Time and Duration\n\n"); }
				else { printf("\t3. Start Time > %s\n\t   facility ID > %s\n\n", facUse[numRec].walkInTime, facUse[numRec].facID); }

				/*-----------------------*/

				printf("\tUsage type > Walk In\n\n");
				strcpy(facUse[numRec].usageType, "Walk In");

				/*-----------------------*/

				if (strcmp(facUse[numRec].remarks, "") == 0) { printf("\t4. Remarks\n\n"); }
				else { printf("\t4. Remarks > %s\n\n", facUse[numRec].remarks); }

				/*-----------------------*/

				printf("\t5. Re-confirm your record details\n\n");

				/*-----------------------*/

				printf("\tPlease enter the number which you would like to modify (1 - 5) > ");
				scanf("%d", &checkSwitch);

				cont = 'N';
				system("cls");
				if (checkSwitch < 10 || checkSwitch > 0)
					switch (checkSwitch)
					{
					case 1:

						MemberSearching(&member);
						strcpy(facUse[numRec].memberIC, member.memIC);
						strcpy(facUse[numRec].memberID, member.memID);
						strcpy(facUse[numRec].memberType, member.memType);

						break;
					case 2:

						printf("\tEvent > ");
						SelectWalkInFacilityName(facUse[numRec].facEvent);

						break;
					case 3:

						if (strcmp(facUse[numRec].facEvent, "") == 0)
						{
							printf("facility events needs to be filled in.\n\n");

							break;
						}
						else
						{
							printf("\tStart Time & Duration > ");
							if (SelectWalkInTimeSlot(&facUse[numRec]) == 0)
							{
								printf("Try again\n");
							};

							break;
						}
					case 4:

						printf("\tRemarks > ");
						rewind(stdin);
						scanf("%[^\n]", &facUse[numRec].remarks);

						break;
					case 5:

						if (strcmp(facUse[numRec].memberID, "") == 0 || strcmp(facUse[numRec].facEvent, "") == 0 || strcmp(facUse[numRec].walkInTime, "") == 0)
						{
							printf("\n\tPlease fill in all of the elements.\n\n");

							break;
						}
						else
						{
							printf("\n\t| %-17s | %-9s |    %-5s    | %-11s |    %-4s    |  %-9s  | %-11s | %-5s | %-10s | %-5s |          %-17s |\n",
								"Facility Usage ID", "Member ID", "Event", "Facility ID", "Date",
								"Time Slot", "Member Type", "Price", "Usage Type", "Staff in Charge", "Remarks");

							printf("\n\t| %-17s | %-9s | %-11s | %-11s | %d/%02d/%d | %-9s | %-11s | %-5.2f | %-10s | %-5s          | %-17s          |\n\n",
								facUse[numRec].facUseID, facUse[numRec].memberID, facUse[numRec].facEvent, facUse[numRec].facID, facUse[numRec].walkInDate.day,
								facUse[numRec].walkInDate.month, facUse[numRec].walkInDate.year, facUse[numRec].walkInTime, facUse[numRec].memberType,
								facUse[numRec].walkInPrice, facUse[numRec].usageType, facUse[numRec].staffID, facUse[numRec].remarks);

							printf("\tIs this your modification correct (Y/N) > ");
							cont = YesNoValidation(toupper(CharInput()));
							break;
						}
					default:
						printf("Wrong input!");
						break;
					}
			} while (cont == 'N');

			printf("\tConfirm modification (Y/N) > ");
			cont = YesNoValidation(toupper(CharInput()));
			if (cont == 'Y')
			{
				FILE* fptr;
				fptr = fopen("facUsageList.txt", "w");

				if (!fptr)
				{
					printf("\tError! unable to open file facUsageList.txt");
					return;
				}
				for (int a = 0; a < i; a++)
				{
					fprintf(fptr, "|%s|%s|%s|%s|%d/%d/%d|%s|%s|%.2f|%s|%s|%s|\n",
						facUse[a].facUseID, facUse[a].memberID, facUse[a].facEvent, facUse[a].facID,
						facUse[a].walkInDate.day, facUse[a].walkInDate.month, facUse[a].walkInDate.year,
						facUse[a].walkInTime, facUse[a].memberType, facUse[a].walkInPrice,
						facUse[a].usageType, facUse[a].staffID, facUse[a].remarks);
				}
				fclose(fptr);
			}
		}
		else
		{
			printf("\tSuch a record doesn't exist.");
		}
	} while (cont == 'N');

	system("cls");
}

/// <summary>
/// To delete records of Facility Usage
/// </summary>
/// <param name="staffIDLogin"></param>
void DeleteFacilityUsageHistory(char* staffIDLogin)
{
	FILE* fptr = fopen("facUsageList.txt", "r");
	if (!fptr)

	{
		printf("\tError! cannot detect facUsageList.txt");
		return;
	}

	facilityUsage facUse[99];

	int i = 0, numRec = 0, skip = 0;
	char cont;

	printf("\n\t|     | %-17s | %-9s |    %-5s    | %-11s |    %-4s    |  %-9s  | %-11s | %-5s | %-10s | %-5s |          %-17s |\n",
		"Facility Usage ID", "Member ID", "Event", "Facility ID", "Date",
		"Time Slot", "Member Type", "Price", "Usage Type", "Staff in Charge", "Remarks");

	while (fscanf(fptr, "|%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%[^|]|%[^|]|%f|%[^|]|%[^|]|%[^|]|\n",
		&facUse[i].facUseID, &facUse[i].memberID, &facUse[i].facEvent, &facUse[i].facID, &facUse[i].walkInDate.day,
		&facUse[i].walkInDate.month, &facUse[i].walkInDate.year, &facUse[i].walkInTime, &facUse[i].memberType,
		&facUse[i].walkInPrice, &facUse[i].usageType, &facUse[i].staffID, &facUse[i].remarks) != EOF)
	{
		numRec++;
		skip++;

		printf("\n\t| %02d. | %-17s | %-9s | %-11s | %-11s | %02d/%02d/%d | %-9s | %-11s | %-5.2f | %-10s | %-5s          | %-17s          |",
			i + 1, facUse[i].facUseID, facUse[i].memberID, facUse[i].facEvent, facUse[i].facID, facUse[i].walkInDate.day,
			facUse[i].walkInDate.month, facUse[i].walkInDate.year, facUse[i].walkInTime, facUse[i].memberType,
			facUse[i].walkInPrice, facUse[i].usageType, facUse[i].staffID, facUse[i].remarks);
		i++;
	}

	fclose(fptr);

	printf("\n\n\tEnter the record you would like to delete > ");
	scanf("%d", &skip);

	if (skip > 0) {
		printf("\n\t| %d. | %-17s | %-9s | %-11s | %-11s | %02d/%02d/%d | %-9s | %-11s | %-5.2f | %-10s | %-5s          | %-17s          |",
			skip--,
			facUse[skip].facUseID,
			facUse[skip].memberID,
			facUse[skip].facEvent,
			facUse[skip].facID,
			facUse[skip].walkInDate.day,
			facUse[skip].walkInDate.month,
			facUse[skip].walkInDate.year,
			facUse[skip].walkInTime,
			facUse[skip].memberType,
			facUse[skip].walkInPrice,
			facUse[skip].usageType,
			facUse[skip].staffID,
			facUse[skip].remarks);
	}

	printf("\n\n\tAre you sure you want to delete this record (Y/N) > ");
	cont = YesNoValidation(toupper(CharInput()));

	system("cls");

	printf("\n\t| %-17s | %-9s |    %-5s    | %-11s |    %-4s    |  %-9s  | %-11s | %-5s | %-10s | %-5s |          %-17s |\n",
		"Facility Usage ID", "Member ID", "Event", "Facility ID", "Date",
		"Time Slot", "Member Type", "Price", "Usage Type", "Staff in Charge", "Remarks");

	if (cont == 'Y')
	{
		for (numRec = 0; numRec < i; numRec++)
		{
			if (numRec == skip)
			{
				continue;
			}
			printf("\n\t| %-17s | %-9s | %-11s | %-11s | %02d/%02d/%d | %-9s | %-11s | %-5.2f | %-10s | %-5s          | %-17s          |",
				facUse[numRec].facUseID, facUse[numRec].memberID, facUse[numRec].facEvent, facUse[numRec].facID,
				facUse[numRec].walkInDate.day, facUse[numRec].walkInDate.month, facUse[numRec].walkInDate.year,
				facUse[numRec].walkInTime, facUse[numRec].memberType, facUse[numRec].walkInPrice, facUse[numRec].usageType,
				facUse[numRec].staffID, facUse[numRec].remarks);
		}

		printf("\n\n\tThese are the remaining records. Are you sure to proceed (Y/N) > ");
		cont = YesNoValidation(toupper(CharInput()));

		system("cls");
		if (cont == 'Y')
		{
			FILE* writeFptr = fopen("facUsageList.txt", "w");
			if (!writeFptr)
			{
				printf("\tError! Could not load facUsageList.txt");
				return;
			}

			/*THIS INT IS USED FOR WHEN A RECORD IS SKIPPED(DELETED), IT WILL ADD INTO THE facUseID SO
			THAT THE FLOW OF THE facUseID WILL BE CONSISTNT (F001, F002, F003...). IF THIS WAS NOT ADDED,
			THE FLOW OF facUseID WILL LOOK LIKE THIS (F001, F002, F004..)*/
			int a = 0;
			for (numRec = 0; numRec < i; numRec++)
			{
				if (numRec == skip)
				{
					continue;
					a++;
				}

				fprintf(writeFptr, "|%s|%s|%s|%s|%d/%d/%d|%s|%s|%.2f|%s|%s|%s|\n",
					facUse[numRec].facUseID, facUse[numRec].memberID, facUse[numRec].facEvent, facUse[numRec].facID,
					facUse[numRec].walkInDate.day, facUse[numRec].walkInDate.month, facUse[numRec].walkInDate.year,
					facUse[numRec].walkInTime, facUse[numRec].memberType, facUse[numRec].walkInPrice, facUse[numRec].usageType,
					facUse[numRec].staffID, facUse[numRec].remarks);
			}
			fclose(writeFptr);
		}
	}
	system("cls");
}

/// <summary>
/// To printf different types of Facility Usage summary
/// </summary>
/// <param name="staffIDLogin"></param>
void FacilityUsageSummary(char* staffIDLogin)
{
	int choose;
	char cont = 'N';

	FILE* fptr = fopen("facUsageList.txt", "a");
	FILE* writeFptr = fopen("facUsageSummary.txt", "w");

	do {
		system("cls");
		printf("\n\tFacility Usage Summary: \n\n\t1. Daily\n\t2. Monthly\n\t3. Annually (Yearly)\n\t0. Exit\n");
		printf("\n\tWhich type of summary would you like printed? > ");
		scanf("%d", &choose);

		switch (choose)
		{
		case 1:

			system("cls");
			DailyFacUseSummary();
			system("cls");
			break;
		case 2:

			system("cls");
			MonthlyFacUseSummary();
			system("cls");
			break;
		case 3:

			system("cls");
			YearlyFacUseSummary();
			system("cls");
			break;
		case 0:
			system("cls");
			printf("\tYou wish to return to the Facility Usage Submenu? (Y/N) > ");
			cont = YesNoValidation(toupper(CharInput()));
			system("cls");
			break;
		default:
			printf("\tWrong Input!");
			break;
		}
	} while (cont == 'N');
}

/*-------------------- Out of Mudule -------------------------*/
/// <summary>
/// Main Menu for accessing all modules
/// </summary>
/// <returns>Selection of main menu</returns>
int MainMenu() {
	int selection;

	//Main Menu
	printf("\t---------------\n");
	printf("\t | Main Menu |\n");
	printf("\t---------------\n\n");

	//selection module
	printf("\t1 - Staff Information\n");
	printf("\t2 - Facility\n");
	printf("\t3 - Member Information\n");
	printf("\t4 - Booking\n");
	printf("\t5 - Facility Usage\n\n");

	printf("\t0 - Logout Staff\n");
	printf("\t------------------------\n");

	printf("\tEnter your selection : ");
	selection = IntInput();

	system("cls");

	return selection;
}

/// <summary>
/// Function for all staff login
/// </summary>
/// <param name="staffID"></param>
void StaffLogin(char staffID[]) {
	struct Account accountLogin;
	struct Staff staffAccount;
	FILE* fLogin;
	char nameLogin[46], idLogin[7];

	int numStaff = 0, numOfRecord, checkEOF = 0, check = 0;

	//get number of staff (ACTIVE and UNACTIVE)
	while (numStaff == 0) {
		//get number of staff, record and info all staff from bit file
		FILE* fileStaff;
		fileStaff = fopen("StaffInfo.bin", "rb");

		if (fileStaff == NULL) {			//if first time open, no file
			printf("<Creating \"StaffInfo.bin\">\n");
			fileStaff = fopen("StaffInfo.bin", "wb");
			fclose(fileStaff);
			fileStaff = fopen("StaffInfo.bin", "rb");
		}

		numStaff = 0;
		numOfRecord = 0;

		//get num of record and num of staff
		while (fread(&staffAccount, sizeof(staffAccount), 1, fileStaff) != 0) {
			if (feof(fileStaff))
				break;
			if (strcmp(staffAccount.status, "ACTIVE") == 0 || strcmp(staffAccount.status, "UNACTIVE") == 0 || strcmp(staffAccount.status, "RESIGN") == 0)
				numOfRecord++;
			if (strcmp(staffAccount.status, "ACTIVE") == 0 || strcmp(staffAccount.status, "UNACTIVE") == 0)
				numStaff++;
		}
		fclose(fileStaff);

		if (numStaff == 0)
			AddStaff(numOfRecord);
	}

	do {
			check = 0;
		do {			//check ID
			checkEOF = 0;
			system("cls");
			//Header
			printf("\n");
			printf("\t-----------------\n");
			printf("\t | Staff Login |\n");
			printf("\t-----------------\n");

			//Enter ID
			staffIDInput(accountLogin.id);

			fLogin = fopen("StaffInfo.bin", "rb");
			while (!feof(fLogin)) {
				fread(&staffAccount, sizeof(staffAccount), 1, fLogin);				//Check ID in bit file line by line

				if (strcmp(staffAccount.sAccount.id, accountLogin.id) == 0)			//Stop at same id in file
					break;
			}
			if (feof(fLogin)) {			//if all file checked no result
				checkEOF = 1;
				printf("\tNo result found.\n\n");
			}
			fclose(fLogin);

			//if file have id
			if (checkEOF != 1) {
				//Check status
				if (strcmp(staffAccount.status, "ACTIVE") == 0) {				//ACTIVE, login
					printf("\tPassword (Max 30) : ");
					StringInput(accountLogin.password, 30);
				}
				else if (strcmp(staffAccount.status, "UNACTIVE") == 0) {		//UNACTIVE, create password, activate
					check++;
					printf("\tFirst time login. Create your password.\n");
					CreatePassword(accountLogin.password);
					CreateQnA(accountLogin.recoveryQues, accountLogin.recoveryAns);
					strcpy(nameLogin, staffAccount.name);
					strcpy(idLogin, staffAccount.sAccount.id);

					//write the new password to file
					FILE* fPassword;
					fLogin = fopen("StaffInfo.bin", "rb");										//open file
					fPassword = fopen("StaffInfoTemp.bin", "wb");								//open temp file
					while (!feof(fLogin)) {
						fread(&staffAccount, sizeof(staffAccount), 1, fLogin);					//read line by line
						if (feof(fLogin))
							break;
						if (strcmp(staffAccount.sAccount.id, accountLogin.id) == 0) {			//id selected indicate
							strcpy(staffAccount.sAccount.password, accountLogin.password);			//assign new password
							strcpy(staffAccount.sAccount.recoveryQues, accountLogin.recoveryQues);	//assign new recovery Question
							strcpy(staffAccount.sAccount.recoveryAns, accountLogin.recoveryAns);	//assign new recovery Ans
							strcpy(staffAccount.status, "ACTIVE");									//change status to ACTIVE
						}
						fwrite(&staffAccount, sizeof(staffAccount), 1, fPassword);				//write line by line until eof
					}
					strcpy(staffAccount.sAccount.password, accountLogin.password);			//assign new password
					fclose(fLogin);
					fclose(fPassword);
					//replace temp file to main file
					remove("StaffInfo.bin");
					rename("StaffInfoTemp.bin", "StaffInfo.bin");
				}
				else															//Resign, re-enter user
					printf("Staff Resign. Login with another account.\n\n");
			}

		} while (checkEOF == 1 || strcmp(staffAccount.status, "RESIGN") == 0);			//loop back when read until eof or Resign account

		//check password
		//password correct
		if (strcmp(staffAccount.sAccount.password, accountLogin.password) == 0) {
			if (check == 1) {
				strcpy(staffAccount.name, nameLogin);
				strcpy(staffAccount.sAccount.id, idLogin);
			}
			printf("\n\t\tWelcome, %s (%s).\n", staffAccount.name, staffAccount.sAccount.id);
			strcpy(staffID, staffAccount.sAccount.id);				//passback staffID to main()
		}
		//password not correct
		else {
			int count = 0;
			//try another 2 times or "R" to change password
			for (int i = 0; i < 2; i++) {
				printf("\t\tWrong password.\n");
				printf("\tPassword (R - Recovery Password) : ");
				StringInput(accountLogin.password, 30);
				if (strcmp(staffAccount.sAccount.password, accountLogin.password) == 0 || strcmp(accountLogin.password, "R") == 0) {
					strcpy(staffID, staffAccount.sAccount.id);
					break;
				}
				count = i;
			}

			//After another 2 time wrong, "R" change password or change ID
			if (count == 1) {
				printf("\tRe-(L)ogin / (R)ecovery Password : ");
				StringInput(accountLogin.password, 30);
			}

			//"R" change password
			if (strcmp(accountLogin.password, "R") == 0) {
				//if QnA success 'S', write the new password to file
				if (RecoveryPassword(accountLogin.password, staffAccount.sAccount.recoveryQues, staffAccount.sAccount.recoveryAns) == 'S') {
					FILE* fPassword;
					fLogin = fopen("StaffInfo.bin", "rb");										//open file
					fPassword = fopen("StaffInfoTemp.bin", "wb");								//open temp file
					while (!feof(fLogin)) {
						fread(&staffAccount, sizeof(staffAccount), 1, fLogin);					//read line by line
						if (feof(fLogin))
							break;
						if (strcmp(staffAccount.sAccount.id, accountLogin.id) == 0) 			//id selected indicate
							strcpy(staffAccount.sAccount.password, accountLogin.password);		//assign new password

						fwrite(&staffAccount, sizeof(staffAccount), 1, fPassword);				//write line by line until eof
					}
					fclose(fLogin);
					fclose(fPassword);
					//replace temp file to main file
					remove("StaffInfo.bin");
					rename("StaffInfoTemp.bin", "StaffInfo.bin");
				}
			}
		}
	} while (strcmp(staffAccount.sAccount.password, accountLogin.password) != 0);
}

/// <summary>
/// Create Password and recovery QnA for first time login.
/// </summary>
/// <param name="password">New password</param>
void CreatePassword(char password[]) {
	char passwordEnter[30], passwordConfirm[30];

	do {
		//prompt and get new password
		printf("\tNew password : ");
		StringInput(passwordEnter, 30);

		printf("\tRe-enter password : ");
		StringInput(passwordConfirm, 30);

		if (strcmp(passwordEnter, passwordConfirm) != 0)
			printf("\tBoth passwords are not same! Please re-enter.\n");

	} while (strcmp(passwordEnter, passwordConfirm) != 0);

	strcpy(password, passwordEnter);
}

/// <summary>
/// For first time login or changing QnA
/// </summary>
/// <param name="recoveryQues"></param>
/// <param name="recoveryAns"></param>
void CreateQnA(char recoveryQues[], char recoveryAns[]) {
	char next;
	//Enter security question and answer
	do {
		printf("\tEnter security question : ");
		StringInput(recoveryQues, 80);
		printf("\tEnter security answer : ");
		StringInput(recoveryAns, 80);

		printf("\tConfirm (Y)es/(N)o : ");
		scanf("%c", &next);
		next = YesNoValidation(toupper(next));
	} while (next == 'N');
}

/// <summary>
/// </summary>
/// <param name="password"></param>
/// <param name="recoveryQues"></param>
/// <param name="recoveryAns"></param>
/// <returns></returns>
char RecoveryPassword(char password[], char recoveryQues[], char recoveryAns[]) {
	char answer[80];

	//Display recovery Question
	printf("\tYour Security Question : \n");
	printf("%s\n", recoveryQues);

	//Prompt and get answer
	printf("\tYour Security Answer : ");
	StringInput(answer, 80);

	//Compare answer
	do {
		if (strcmp(answer, recoveryAns) == 0) {			//if correct
			CreatePassword(password);
			return 'S';
		}
		else {									//if wrong, prompt and get answer another 2 times
			for (int i = 0; i < 2 || strcmp(answer, recoveryAns) != 0; i++) {
				printf("\t\tSecurity answer wrong. Please enter again.\n");
				StringInput(answer, 80);
			}

			//if wrong 3 times, return 'F'
			if (strcmp(answer, recoveryAns) != 0) {
				printf("\t\tPlease re-login.\n");
				return 'F';
			}
		}
	} while (strcmp(answer, recoveryAns) == 0);
}

/*-------------- General Function Definition ----------------*/
/// <summary>
/// Function that scans for a valid string, ensuring that there are no empty inputs.
/// </summary>
/// <param name="passedString">The string input.</param>
/// <param name="lengthOfArray">The size of the string.</param>
void StringInput(char passedString[], int lengthOfArray) {
	do {
		rewind(stdin);
		//ask for string input from user.
		fgets(passedString, lengthOfArray, stdin);
		//replaces '\n' at the end of the string with '\0' character.
		passedString[strcspn(passedString, "\n")] = 0;
		//if user did not enter anything or the first character is a space, ask again.
		if (passedString[0] == '\0' || passedString[0] == ' ') {
			printf("\t\tYou did not enter anything for this field.\n");
			printf("\t\tPlease ensure that you have entered something.\n");
			printf("\t\tTry again: ");
		}
	} while (passedString[0] == '\0' || passedString[0] == ' ');
}
//Example usage: StringInput(name, 51);

/// <summary>
/// Function that does input validation to check if the responses given are 'Y' or 'N'.
/// </summary>
/// <param name="yesNoChar">Character inputted by user</param>
/// <returns>The character inputted if it is valid.</returns>
char YesNoValidation(char yesNoChar) {
	//Input validation: if user inputted anything other than 'Y' or 'N', ask again.
	while (yesNoChar != 'Y' && yesNoChar != 'N') {
		printf("\n\t\tPlease input 'Y' or 'N': ");
		yesNoChar = CharInput();
		//Convert status to uppercase to accept lowercase input from user.
		yesNoChar = toupper(yesNoChar);
	}
	//Return the character that has either 'Y' or 'N'.
	return yesNoChar;
}

/// <summary>
/// Function that scans for a string and returns the first character only if user inputted a character.
/// </summary>
/// <returns>A character</returns>
char CharInput() {
	//variable declaration to store the string input to check if user entered a character.
	char validChar[99];
	//input validation loop for character input.
	do {
		rewind(stdin);
		//get string input from user.
		fgets(validChar, 99, stdin);
		//if user did not enter a character, or first character is a space, or did not enter anything,
		//print invalid input and ask for character input again.
		if (validChar[0] == '\n' || validChar[0] == ' ' || validChar[1] != '\n') {
			printf("\n\t\tInvalid input detected, enter a character. Please try again. : ");
		}
	} while (validChar[0] == '\n' || validChar[0] == ' ' || validChar[1] != '\n');
	return validChar[0];
}

/// <summary>
/// Function that scans for an integer.
/// </summary>
/// <returns>A valid integer</returns>
int IntInput() {
	//variable declaration used to store the valid integer to be returned back to main function.
	int validInt;
	//variable declaration to store the return value of scanf to determine if the scanf was successful
	int numValidInput;
	//variable declaration to store the second character input to be used to check if it was a newline.
	char input2;

	//input validation loop for integer input.
	do {
		//get integer input from user.
		rewind(stdin);
		numValidInput = scanf("%d%c", &validInt, &input2);
		//if user did not enter an integer, print invalid input and ask for integer input again.
		if (numValidInput != 2 || input2 != '\n') {
			printf("\n\t\tInvalid input detected, enter an integer. Please try again. : ");
		}
	} while (numValidInput != 2 || input2 != '\n');
	return validInt;
}

/// <summary>
/// Function for date input with validation or validation for date paased by parameter.
/// </summary>
/// <param name="day">Output parameter for day.</param>
/// <param name="month">Output parameter for month.</param>
/// <param name="year">Output parameter for year.</param>
/// /// <param name="selection">( date input - date input | date validation - validate date format )</param>
/// /// <returns>Validation for date format</returns>
int DateInput(int* day, int* month, int* year, char selection[]) {
	do {
		if (strcmp(selection, "date input") == 0) {
			//ask for year input from user.
			printf("\tYear  : ");
			*year = IntInput();

			//ask for month input from user.
			printf("\tmonth : ");
			*month = IntInput();

			//ask for year input from user.
			printf("\tday   : ");
			*day = IntInput();
		}

		//validate it is the correct range of date.
		//check year
		if ((*year >= 1900 && *year <= 9999) || strcmp(selection, "date validation") == 0)
		{
			//check month
			if (*month >= 1 && *month <= 12)
			{
				//check days
				if ((*day >= 1 && *day <= 31) && (*month == 1 || *month == 3 || *month == 5 || *month == 7 || *month == 8 || *month == 10 || *month == 12)) {
					break;
				}
				else if ((*day >= 1 && *day <= 30) && (*month == 4 || *month == 6 || *month == 9 || *month == 11)) {
					break;
				}
				else if ((*day >= 1 && *day <= 28) && (*month == 2)) {
					break;
				}
				else if (*day == 29 && *month == 2 && (*year % 4 == 0 && (*year % 100 != 0 || *year % 400 == 0))) {
					break;
				}
				else {
					//Display error message when the input format is invalid
					if (strcmp(selection, "date input") == 0) {
						printf("\t\tDay is not valid.\n");
						printf("\t\tPlease ensure that you have enter correct day value.\n");
						printf("\t\tTry again\n");
					}
					else {
						return 0;
					}
				}
			}
			else {
				//Display error message when the input format is invalid
				if (strcmp(selection, "date input") == 0) {
					printf("\t\tMonth is not valid.\n");
					printf("\t\tPlease ensure that you have enter correct month value.\n");
					printf("\t\tTry again\n");
				}
				else {
					return 0;
				}
			}
		}
		else {
			//Display error message when the input format is invalid
			printf("\t\tYear is not valid.\n");
			printf("\t\tPlease ensure that you have enter correct year value.\n");
			printf("\t\tTry again\n");
		}

	} while (1);
}
//Example usage: DateInput(&day, &month, &year, "date validation");
//Example usage for structure array: DateInput(&(member[10].memBirthDate.day), &(member[10].memBirthDate.month), &(member[10].memBirthDate.year),"date input");
//Example usage for structure pointer: DateInput(&(member->memBirthDate.day), &(member->memBirthDate.month), &(member->memBirthDate.year),"date input");

// Need to include time.h header
/// <summary>
/// Function that return part of the current date.
/// </summary>
/// <param name="selection">( DD - day | MM - Month | YY - 2digits Year | YYYY - 4digits Year</param>
int CurrentDate(char selection[]) {
	time_t t;
	t = time(NULL);
	struct tm tm = *localtime(&t);

	if (strcmp(selection, "YYYY") == 0) {
		return tm.tm_year + 1900;
	}
	else if (strcmp(selection, "YY") == 0) {
		return tm.tm_year - 100;
	}
	else if (strcmp(selection, "MM") == 0) {
		return tm.tm_mon + 1;
	}
	else if (strcmp(selection, "DD") == 0) {
		return tm.tm_mday;
	}
}
//Example usage:  CurrentDate("YYYY") return 4 digit exp:1999
//Example usage:  CurrentDate("YY") return 4 digit exp:99

/// <summary>
/// Function extract date from string and store it as integer in different variable.
/// Remark: put zero for output parameter if you do not need it.
/// </summary>
/// <param name="passedString[]">Input parameter of string contain date.</param>
/// <param name="dateFormat[]">Date format</param>
/// <param name="starPosition">String array index of the first date char</param>
/// <param name="passedDay">Output parameter for day extracted from string</param>
/// <param name="passedMonth">Output parameter for month extracted from string</param>
/// <param name="passedYear">Output parameter for year extracted from string</param>
/// <returns></returns>
void DateExtract(char passedString[], char dateFormat[], int startPosition, int* passedDay, int* passedMonth, int* passedYear) {
	char day[3], month[3], year[5];

	if (strcmp(dateFormat, "YYYYMMDD") == 0) {
		strncpy(year, &passedString[startPosition], 4);
		year[4] = '\0';

		strncpy(month, &passedString[startPosition + 4], 2);
		month[2] = '\0';

		strncpy(day, &passedString[startPosition + 6], 2);
		day[2] = '\0';

		*passedDay = atoi(day);
		*passedMonth = atoi(month);
		*passedYear = atoi(year);

	}
	else if (strcmp(dateFormat, "YYMMDD") == 0) {
		strncpy(year, &passedString[startPosition], 2);
		year[2] = '\0';

		strncpy(month, &passedString[startPosition + 2], 2);
		month[2] = '\0';

		strncpy(day, &passedString[startPosition + 4], 2);
		day[2] = '\0';

		*passedDay = atoi(day);
		*passedMonth = atoi(month);
		*passedYear = atoi(year);

	}
	else if (strcmp(dateFormat, "YYMM") == 0) {
		strncpy(year, &passedString[startPosition], 2);
		year[2] = '\0';

		strncpy(month, &passedString[startPosition + 2], 2);
		month[2] = '\0';

		*passedMonth = atoi(month);
		*passedYear = atoi(year);

	}
	else if (strcmp(dateFormat, "MMDD") == 0) {
		strncpy(month, &passedString[startPosition], 2);
		month[2] = '\0';

		strncpy(day, &passedString[startPosition + 2], 2);
		day[2] = '\0';

		*passedDay = atoi(day);
		*passedMonth = atoi(month);

	}
	else if (strcmp(dateFormat, "MM") == 0) {
		strncpy(day, &passedString[startPosition], 2);
		month[2] = '\0';

		*passedMonth = atoi(month);

	}
	else if (strcmp(dateFormat, "DD") == 0) {
		strncpy(day, &passedString[startPosition], 2);
		day[2] = '\0';

		*passedDay = atoi(day);

	}

}
//Example usage: DateExtract(addMember[1].memIC, "YYMMDD", 0, &day, &month, 0); output : 1125

/// <summary>
/// Function to calculate age with the birthdate passed by parameter
/// </summary>
/// <param name="day">Birthday</param>
/// <param name="month">Birthmonth</param>
/// <param name="year">Birthyear</param>
/// <returns>Age</returns>
int AgeCalc(int day, int month, int year) {
	int currentYear, currentMonth, currentDay;

	currentYear = CurrentDate("YYYY");
	currentMonth = CurrentDate("MM");
	currentDay = CurrentDate("DD");

	if (currentYear >= year) {
		if (currentMonth > month || (currentMonth == month && currentDay >= day)) {
			return currentYear - year;
		}
		else {
			return currentYear - year - 1;

		}

	}
	else {
		return -1;

	}

}
//Example usage: age = AgeCalc(AddMember.Birthdate.day, AddMember.Birthdate.month, AddMember.Birthdate.year) output = 25

/// <summary>
/// Ask for month input from user
/// </summary>
/// <param name="month">output parameter: stores the month input</param>
void MonthInput(int* month) {
	do {
		//ask for month input from user.
		printf("\tMonth : ");
		*month = IntInput();
		//check month
		if (*month >= 1 && *month <= 12) {
			break;
		}
		else {
			printf("\t\tMonth is not valid.\n");
			printf("\t\tPlease ensure that you have entered the correct month value.\n");
			printf("\t\tTry again.\n");
		}
	} while (1);

}

/// <summary>
/// Function used for time input only for hours in 12 hour format.
/// </summary>
/// <param name="tInput">string variable to store time input</param>
void TimeInput(char* tInput) {
	char timeString[6];
	char hoursString[3] = "";
	int hours;
	char amPm[3] = "";

	do {
		//Input Time in the format "HHam/pm"
		StringInput(timeString, 6);

		//VALIDATION
		if (strlen(timeString) > 4) {
			printf("\t\tTime length invalid.\n\n");
			printf("\t\tTry again: ");
			continue;
		}

		//If first character or first 2 character is digits, store it into hourString, and store their amPm values.
		if (isdigit(timeString[0]) != 0) {
			if (isdigit(timeString[1]) != 0) {
				strncpy(hoursString, timeString, 2);
				strncpy(amPm, &timeString[2], 2);
			}
			else {
				strncpy(hoursString, timeString, 1);
				strncpy(amPm, &timeString[1], 2);
			}
		}
		else {
			printf("\t\tEnsure your time is inputted in this format EX: 12pm \n\n");
			printf("\t\tTry again: ");
			continue;
		}

		//Convert the hours part of the string into integer.
		hours = atoi(hoursString);
		strupr(amPm);

		//Check for valid hours
		if (hours < 1 || hours > 12) {
			printf("\t\t12-hour time format is being used. Please try again.\n\n");
			printf("\t\tTry again: ");
		}
		//Check for am/pm
		else if (strcmp(amPm, "AM") != 0 && strcmp(amPm, "PM") != 0) {
			printf("\t\tInvalid input. Please input (am/pm).\n\n");
			printf("\t\tTry again: ");
		}
		else {
			sprintf(tInput, "%02d%s", hours, amPm);
			break;
		}
	} while (1);
}
//Example input: 2pm 
//2pm will be stored as 02PM

/// <summary>
/// Validate IC length and format and return gender
/// </summary>
/// <param name="icNum">The Ic input</param>
/// /// <param name="selection">get ic input or ic gender</param>
/// <returns>gender code.</returns>
char IcInfo(char icNum[], char selection[]) {
	int genderCode, validation, day, month, year;
	char gender, icLastNum[2];

	if (strcmp(selection, "ic input") == 0) {
		do {
			validation = 1;
			rewind(stdin);
			//ask for IC input from user.
			StringInput(icNum, 14);

			//Validate IC length
			if (strlen(icNum) != 12) {
				printf("\t\tIC length invalid.\n");
				printf("\t\tTry again : ");
				validation = 0;
				continue;

			}

			//Validate only int in IC
			for (int i = 0; i < strlen(icNum); i++) {
				if (isdigit(icNum[i]) == 0) {
					printf("\t\tIC format invalid.\n");
					printf("\t\tTry again : ");
					validation = 0;
					break;
				}
			}

			//Validate birthdate format in IC
			DateExtract(icNum, "YYMMDD", 0, &day, &month, &year);
			validation = DateInput(&day, &month, &year, "date validation");
			if (validation == 0) {
				printf("\t\tIC birthdate format invalid.\n");
				printf("\t\tTry again : ");
			}

		} while (validation == 0);

	}

	strcpy(icLastNum, "");
	icLastNum[0] = icNum[11];

	//Gender
	genderCode = atoi(icLastNum);
	if (genderCode % 2 == 0)
		gender = 'F';
	else
		gender = 'M';

	return gender;
}
//Example usage:  IcInfo(AddMember.memIC, "ic input") for ic input
//Example usage:  gender = IcInfo(AddMember.memIC, "ic gender") for getting ic gender

/// <summary>
/// User input for staff ID
/// </summary>
/// <param name="staffID">String that stores the staff ID</param>
void staffIDInput(char staffID[]) {
	int validation;

	//Staff id input validation

	printf("\tStaff Id : ");
	do {
		validation = 1;
		StringInput(staffID, 8);
		strupr(staffID);

		if (staffID[0] == 'S' && staffID[1] == 'T' && staffID[2] == '-') {
			if (strlen(staffID) != 6) {
				printf("\t\tInvalid staffID length\n");
				printf("\t\tTry again : ");
				validation = 0;
				continue;

			}
			for (int i = 3; i < 6; i++) {
				if (isdigit(staffID[i]) == 0) {
					printf("\t\tInvalid staffID format\n");
					printf("\t\tTry again : ");
					validation = 0;
					break;

				}
			}
		}
		else {
			printf("\t\tInvalid staffID format.\n");
			printf("\t\tTry again : ");
			validation = 0;
		}
	} while (validation == 0);
}

/// <summary>
/// Function that scans for float
/// </summary>
/// <returns>A valid float</returns>
float FloatInput() {
	//variable declaration used to store the valid float to be returned back to main function.
	float validFloat;
	//variable declaration to store the return value of scanf to determine if the scanf was successful
	int floatValidInput;
	//variable declaration to store the second character input to be used to check if it was a newline.
	char input2;

	//input validation loop for integer input.
	do {
		//get integer input from user.
		rewind(stdin);
		floatValidInput = scanf("%f%c", &validFloat, &input2);
		//if user did not enter an integer, print invalid input and ask for integer input again.
		if (floatValidInput != 2 || input2 != '\n') {
			printf("\n\t\tInvalid input detected, enter an float number. Please try again. : ");
		}
	} while (floatValidInput != 2 || input2 != '\n');

	return validFloat;
}

/// <summary>
/// Function that to do the validation for Facility ID.
/// </summary>
/// <param name="facilityID">Facility ID</param>
/// <returns>The validation result</returns>
int FacilityIDValidation(char facilityID[]) {
	int validation = 0;
	char facilityIDNum[5] = " ";

	if (strlen(facilityID) > 4) {
		validation = 1;
		printf("\t\tYou have already entered too long for facility ID. Try again.\n\n");
	}
	else {
		strupr(facilityID);

		for (int i = 0; i < strlen(facilityID); i++) {

			if (isdigit(facilityID[i]) != 0) {
				validation = 0;
				break;
			}
		}

		if (validation == 1) {
			printf("\t\tPlease make sure that there is a number inside the facility ID.\n\n");
		}
	}
	return validation;
}

/// <summary>
/// Function that to do the validation for Facility ID and Facility description
/// </summary>
/// <param name="facilityID">Facility ID</param>
/// <param name="description">Facility Description</param>
/// <returns>The validation result</returns>
int FacilityIdAndDesc(char facilityID[], char description[]) {

	char facilityIDNum[5] = " ", facilityDescNum[5] = " ";
	int validation = 0;

	for (int i = 0; i < strlen(facilityID); i++) {
		if (isdigit(facilityID[i]) != 0) {
			strncpy(facilityIDNum, &facilityID[i], strlen(facilityID) - i);
			break;
		}
	}
	for (int j = 0; j < strlen(description); j++) {
		if (isdigit(description[j]) != 0) {
			strncpy(facilityDescNum, &description[j], strlen(description) - j);
			break;
		}
	}

	if (strcmp(facilityIDNum, facilityDescNum) != 0) {
		validation = 1;
	}
	if (validation == 1) {
		printf("\t\tPlease make sure your number of facility description match to facility ID.\n\n");
	}

	return validation;
}

/// <summary>
/// Function that check that there is all alphabet inside the string
/// </summary>
/// <param name="string">The string input</param>
/// <returns>Validation result</returns>
int AlphabetCheck(char string[]) {
	int validation = 0;

	for (int x = 0; x < strlen(string); x++) {
		if (string[x] == ' ') {
			continue;
		}
		else if (isalpha(string[x]) == 0) {
			validation = 1;
			printf("\t\tPlease make sure there is all alphabet.\n\n");
			break;
		}
	}

	return validation;
}

/// <summary>
/// Function to uppercase the first character and the character after blank and lowercase the other characters
/// </summary>
/// <param name="string">The String input</param>
void UppercaseFunction(char string[]) {
	for (int i = 0; i < strlen(string); i++) {
		if (i == 0 && string[i] != ' ' || string[i] != ' ' && string[i - 1] == ' ') {
			if (string[i] >= 'a' && string[i] <= 'z') {
				string[i] = toupper(string[i]);
			}
		}
		else if (string[i] >= 'A' && string[i] <= 'Z') {
			string[i] = tolower(string[i]);
		}
	}
}

/*-------------------- Member Information General Function Definitions -------------------------*/
/// <summary>
/// Function that search member record using member ic or member id. 
/// </summary>
/// <param name="member">Output parameter Member structure.</param>
/// <returns>Validation if (0 - record not found || 1 - record found) </returns>
int MemberSearching(struct MemberInfo* member) {
	char option, memID[11], memIC[14];
	int validation;

	FILE* fptr = fopen("Member information.bin", "rb");

	//Search member by member id or member ic
	do {
		validation = 1;
		printf("\tSearch by : \n");
		printf("\tA - Member ID \n");
		printf("\tB - Member IC \n");
		printf("\tOption : ");
		option = CharInput();
		option = toupper(option);

		switch (option) {
		case 'A':
			printf("\n\tMember ID : ");
			do {
				validation = 1;
				StringInput(memID, 11);

				if (memID[4] != '-' || strlen(memID) != 9) {
					printf("\t\tInvalid member id format\n");
					printf("\t\tTry again : ");
					validation = 0;
					continue;
				}

				for (int i = 0; i < 9; i++) {

					if (isdigit(memID[i]) == 0 && i != 4) {
						printf("\t\tInvalid member id format.\n");
						printf("\t\tTry again : ");
						validation = 0;
					}
				}

			} while (validation == 0);
			break;

		case 'B':
			printf("\n\tMember IC : ");
			IcInfo(memIC, "ic input");
			break;

		default:
			printf("\t\tInvalid selection for member searching type.\n");
			printf("\t\tTry again\n");
			validation = 0;
		}

	} while (validation == 0);

	validation = 0;

	while (!feof(fptr)) {
		fread(member, sizeof(struct MemberInfo), 1, fptr);

		if (option == 'A') {
			if (strcmp(memID, member->memID) == 0) {
				validation = 1;
				break;
			}
		}
		else {
			if (strcmp(memIC, member->memIC) == 0) {
				validation = 1;
				break;
			}
		}
	}

	if (validation == 0) {
		printf("\n\t\tMember record not found.\n");
	}

	fclose(fptr);
	return validation;
}
//Example usage: int validation = MemberSearching(&member); 

/// <summary>
/// Function that display menu for Member information module
/// </summary>
/// <returns>Selection for menu</returns>
int MemberModuleMenu(char staffID[]) {
	int selection;

	//Logo

	//Header
	printf("\t----------------\n");
	printf("\t| Member Info |\n");
	printf("\t----------------\n");
	printf("\tstaff ID : %s\n\n", staffID);

	//Prompt menu and get selection
	printf("\t1 - Add a new member\n");
	printf("\t2 - Search member\n");
	printf("\t3 - Modify member infomation\n");
	printf("\t4 - Display all member\n");
	printf("\t5 - Membership management\n");
	printf("\t6 - Membership report\n\n");
	printf("\t0 - Main Menu\n\n");

	printf("\tEnter selection : ");
	//Input type validation
	selection = IntInput();

	//Input range validation
	if (selection != 1 && selection != 2 && selection != 3 && selection != 4 && selection != 5 && selection != 6 && selection != 0) {
		printf("\t\tInvalid input detected, Enter the selection stated above. Please try again.\n");
	}

	return selection;
}

/// <summary>
/// Function that display menu for Member report function
/// </summary>
/// <returns>Selection for menu</returns>
int MemberReportMenu(char staffID[]) {
	int selection;

	//Logo
	printf("\t------------------\n");
	printf("\t| Member Report |\n");
	printf("\t------------------\n");
	printf("\tstaff ID : %s\n\n", staffID);

	//Prompt menu and get selection
	printf("\tTypes of reports\n");
	printf("\t---------------------------\n");
	printf("\t1 - Member Loyalty Report\n");
	printf("\t2 - Member duration Report\n");
	printf("\t3 - Member status Report\n");
	printf("\t0 - Main Menu\n\n");

	printf("\tEnter selection : ");
	//Input type validation
	selection = IntInput();

	//Input range validation
	if (selection != 1 && selection != 2 && selection != 3 && selection != 0) {
		printf("\t\tInvalid input detected, Enter the selection stated above. Please try again.\n");
	}

	return selection;
}

/// <summary>
/// Function that display menu for Member loyalty report function
/// </summary>
/// <returns>Selection for menu</returns>
int MemberLoyaltyReportMenu(char staffID[]) {
	int selection;

	system("cls");

	//Logo
	printf("\t------------------\n");
	printf("\t| Member Report |\n");
	printf("\t------------------\n");
	printf("\tstaff ID : %s\n\n", staffID);

	//Prompt menu and get selection
	printf("\tTypes of Member Loyalty Report\n");
	printf("\t-------------------------------\n");
	printf("\t1 - All member type\n");
	printf("\t2 - Only VIP\n");
	printf("\t3 - Only Normal\n");

	printf("\n\tEnter selection : ");
	//Input type validation
	selection = IntInput();

	//Input range validation
	if (selection != 1 && selection != 2 && selection != 3) {
		printf("\t\tInvalid input detected, Enter the selection stated above. Please try again.\n");
	}

	return selection;
}

/// <summary>
/// Function that display menu for Member status report function
/// </summary>
/// <returns>Selection for menu</returns>
int MemberStatusReportMenu(char staffID[]) {
	int selection;

	system("cls");

	//Logo
	printf("\t------------------\n");
	printf("\t|  Member Report |\n");
	printf("\t------------------\n");
	printf("\tstaff ID : %s\n\n", staffID);

	//Prompt menu and get selection
	printf("\tTypes of Member Status Report\n");
	printf("\t-------------------------------\n");
	printf("\t1 - Active\n");
	printf("\t2 - Inactive\n");

	printf("\n\tEnter selection : ");
	//Input type validation
	selection = IntInput();

	//Input range validation
	if (selection != 1 && selection != 2) {
		printf("\t\tInvalid input detected, Enter the selection stated above. Please try again.\n");
	}

	return selection;
}

/// <summary>
/// Function for member information input selection 
/// </summary>
/// <param name="memberInput">Member structure to be modify in the function</param>
void MemberInputSelection(struct MemberInfo* memberInput, char staffID[]) {
	char option;
	char validation;

	do {
		system("cls");

		//Display member information
		MemberInfoDisplay(*memberInput);

		//Ask user about which field to be modified
		validation = 'Y';
		printf("\n\tChoose 1 field to edit\n");
		printf("\tA - Name\n");
		printf("\tB - IC, Birth date and Gender\n");
		printf("\tC - Address\n");
		printf("\tD - Phone No\n");
		printf("\tSelection : ");
		option = CharInput();
		option = toupper(option);

		switch (option) {
		case 'A':
			//Modify name
			MemberNameInput(memberInput->memName);
			break;

		case 'B':
			//Modify Ic, birthdate and gender
			MemberICInput(memberInput->memIC);
			MemberBirthDateInput(&(memberInput->memBirthDate.day), &(memberInput->memBirthDate.month), &(memberInput->memBirthDate.year), memberInput->memIC);
			MemberGenderInput(&(memberInput->memGender), memberInput->memIC);
			break;

		case 'C':
			//Modify address
			MemberAddressInput(memberInput->memAdd);
			break;

		case 'D':
			//Modify phone number
			MemberPhoneInput(memberInput->memPhoneNo);
			break;

		default:
			//Display error message when the field selection is out of range
			validation = 'N';
			printf("\t\tInvalid input.\n");
			printf("\t\tTry again.\n");
			break;
		}

		//Ask user whether they finish editing
		if (validation == 'Y') {
			printf("\n\tFinish editing ? (Y/N) : ");
			validation = CharInput();
			validation = toupper(validation);
			validation = YesNoValidation(validation);
		}

	} while (validation == 'N');
}

/// <summary>
/// Function for input member IC
/// </summary>
/// <param name="memIC">Pass back Member IC No entered in the function</param>
void MemberICInput(char memIC[]) {
	FILE* readFptr;
	struct MemberInfo memRead;
	int validation;

	//Ask user to enter IC and validate its format
	printf("\n\tMember IC No : ");
	do {
		readFptr = fopen("Member information.bin", "rb");

		validation = 1;
		IcInfo(memIC, "ic input");

		while (!feof(readFptr)) {
			fread(&memRead, sizeof(struct MemberInfo), 1, readFptr);

			if (strcmp(memIC, memRead.memIC) == 0) {
				printf("\t\tDuplicate IC found.\n");
				printf("\t\tTry again : ");
				validation = 0;
				break;
			}
		}

		fclose(readFptr);

	} while (validation == 0);
}

/// <summary>
/// Function for input member Name
/// </summary>
/// <param name="memName">Pass back Member name entered in the function</param>
void MemberNameInput(char memName[]) {
	//Ask user to enter name
	printf("\n\tMember name : ");
	StringInput(memName, 41);
	UppercaseFunction(memName);
}

/// <summary>
/// Function for input member gender
/// </summary>
/// <param name="gender">Pointer pass back the valid gender entered in the function </param>
/// <param name="memIC">Member ic passed in for validation purpose</param>
void MemberGenderInput(char* gender, char memIC[]) {
	int validation;

	//Prompt and get gender and validate gender with the ic
	printf("\n\tMember gender (M/F) : ");
	do {
		validation = 1;

		*gender = CharInput();
		*gender = toupper(*gender);

		switch (*gender) {
		case 'M':
		case 'F':
			break;

			//Display error message when gender format entered invalid
		default:
			printf("\t\tInvalid input for gender.\n");
			printf("\t\tTry again : ");
			validation = 0;
			continue;
		}

		//Display error message when gender format entered invalid
		if (*gender != IcInfo(memIC, "ic validation")) {
			printf("\t\tGender entered not match with IC.\n");
			printf("\t\tTry again : ");
			validation = 0;
		}

	} while (validation == 0);
}

/// <summary>
/// Function for input member address
/// </summary>
/// <param name="memAdd"></param>
void MemberAddressInput(char memAdd[]) {
	//Ask user to enter address
	printf("\n\tMember address : ");
	StringInput(memAdd, 101);
	UppercaseFunction(memAdd);
}

/// <summary>
/// Function for input member phone number
/// </summary>
/// <param name="memAdd">Pass back member phone number entered in the function</param>
void MemberPhoneInput(char memPhoneNo[]) {
	int validation;

	//Prompt and get phone number and validate its format
	printf("\n\tMember Phone No : ");
	do {
		validation = 1;
		StringInput(memPhoneNo, 13);

		if (strlen(memPhoneNo) < 9 || strlen(memPhoneNo) > 11 || memPhoneNo[0] != '0') {
			printf("\t\tPhone number format invalid\n");
			printf("\t\tTry again : ");
			validation = 0;
		}

	} while (validation == 0);
}

/// <summary>
/// Function to input member birthdate
/// </summary>
/// <param name="day">pass back member birth date day entered in the function</param>
/// <param name="month">pass back member birth date month entered in the function</param>
/// <param name="year">pass back member birth date year entered in the function</param>
/// <param name="memIC">Member ic for checking purpose</param>
/// <returns>(1 - member age meet the requirement | -1 - member age doesnt meet the requirement)</returns>
int MemberBirthDateInput(int* day, int* month, int* year, char memIC[]) {
	int validation, icDay, icMonth, icYear;

	//Prompt and get member birthdate and validate its format
	printf("\n\tMember birthdate : \n");
	do {
		validation = 1;
		DateInput(day, month, year, "date input");

		DateExtract(memIC, "YYMMDD", 0, &icDay, &icMonth, &icYear);

		if (*day == icDay && *month == icMonth) {

			validation = 0;

			for (int i = 1900; (*year - i) >= 0; i = i + 100) {

				if ((*year - i) == icYear) {
					validation = 1;
					break;
				}
			}
		}
		else {
			validation = 0;
		}

		//Display error message if the birthdate entered is not same with the birthdate on ic
		if (validation == 0) {
			printf("\tBirthdate of member is not same as the birth date on IC.\n");
			printf("\tTry again\n ");
			continue;
		}

		//Calculate age based on the birthdate entered
		int age = AgeCalc(*day, *month, *year);

		//Display error message when the member age doesnt meet requirement
		if (age < 18) {
			printf("\t\tThis user is not eligible to be member.\n");
			validation = -1;
			continue;
		}

	} while (validation == 0);

	return validation;
}

/// <summary>
/// Function to input member type and pass back the related member price
/// </summary>
/// <param name="memType">Output member type selected in the function</param>
/// <param name="memberPrice">Output member price based on member type selected in the function</param>
/// <param name="normalMemPrice">Normal member price</param>
/// <param name="vipMemPrice">VIP member price</param>
void MemberTypeInput(char memType[], double* memberPrice, double normalMemPrice, double vipMemPrice) {
	int validation;
	char selection;

	//Prompt and get member type
	printf("\n\tMember type : \n");
	printf("\tA - Normal\n");
	printf("\tB - VIP\n");
	do {
		validation = 1;
		printf("\tSelection : ");
		selection = CharInput();
		selection = toupper(selection);

		switch (selection) {
		case 'A':
			//Assign normal member price to memberprice
			strcpy(memType, "Normal");
			*memberPrice = normalMemPrice;
			break;

		case 'B':
			//Assign VIP member price to memberprice
			strcpy(memType, "VIP");
			*memberPrice = vipMemPrice;
			break;

		default:
			//Display error message when member type entered out of range
			printf("\t\tInvalid selection for member type.\n");
			printf("\t\tTry again\n");
			validation = 0;
		}

	} while (validation == 0);
}

/// <summary>
/// Function to input membership duration and update membership expiry date
/// </summary>
/// <param name="membershipDuration">Output memberduration selected in the function for calculation purpose</param>
/// <param name="memExpiryDay">Update membership expiry date day updated by the function</param>
/// <param name="memExpiryMonth">Update membership expiry date month updated by the function</param>
/// <param name="memExpiryYear">Update membership expiry date year updated by the function</param>
/// <param name="selection">(add - update membership expirydate start on current date | update - update membership expirydate on top of the remaining membership expirydate)</param>
void MembershipDurationInput(int* membershipDuration, int* memExpiryDay, int* memExpiryMonth, int* memExpiryYear, char selection[]) {
	int validation;

	//Prompt and get membership duration
	printf("\n\tMembership duration (1-3)year : \n");
	do {
		validation = 1;
		printf("\tSelection : ");
		*membershipDuration = IntInput();

		switch (*membershipDuration) {
		case 1:
		case 2:
		case 3:
			break;

		default:
			//Display error message when the input is out of range
			printf("\t\tInvalid selection for membership duration.\n");
			printf("\t\tTry again\n");
			validation = 0;
		}

	} while (validation == 0);

	//Update membership expiry date
	if (strcmp(selection, "add") == 0) {
		*memExpiryDay = CurrentDate("DD");
		*memExpiryMonth = CurrentDate("MM");
		*memExpiryYear = CurrentDate("YYYY") + *membershipDuration;

		if (*memExpiryMonth == 2 && *memExpiryDay == 29) {
			*memExpiryDay = 1;
			*memExpiryMonth = 3;
		}

	}
	else if (strcmp(selection, "update") == 0) {
		*memExpiryYear = *memExpiryYear + *membershipDuration;
	}
}

/// <summary>
/// Function to display member loyalty report
/// </summary>
/// <param name="selection">( all - display all member loyalty report | vip - display vip member loyalty report | normal - display normal member loyalty report</param>
void MemberLoyaltyReport(char selection[]) {
	FILE* fptr;
	fptr = fopen("Member information.bin", "rb");

	struct MemberInfo report[51], memberReport;

	int numRecord = 0;

	system("cls");

	//Display member loyalty report based on the selection
	if (strcmp(selection, "all") == 0) {

		//Save the member record with total membership duration > 0 into structure array
		while (!feof(fptr)) {
			int freadReturn = fread(&memberReport, sizeof(struct MemberInfo), 1, fptr);

			if (freadReturn == 1) {

				if ((memberReport.normalDuration + memberReport.vipDuration) > 0) {
					report[numRecord] = memberReport;
					numRecord++;
				}
			}
		}

		//Arrange the member record in descending order based on the total membership duration
		for (int i = 0; i < numRecord; i++) {

			for (int j = 0; j < numRecord; j++) {

				if ((report[j].normalDuration + report[j].vipDuration) < (report[i].normalDuration + report[i].vipDuration)) {

					memberReport = report[i];
					report[i] = report[j];
					report[j] = memberReport;
				}
			}
		}

		//Display member record in table form
		printf("\t-------------------------------\n");
		printf("\t|   All Member Loyalty Report |\n");
		printf("\t-------------------------------\n");

		printf("\t-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("\t| %-9s | %-41s | %-12s | %-6s | %-10s | %-12s | %-11s | %-11s | %-12s | %-15s | %-14s |\n", "Member ID", "Member Name",
			"Member IC", "Gender", "Birth date", "Phone number", "Member Type", "Expiry Date", "VIP duration", "Normal duration",
			"Total duration");
		printf("\t-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

		for (int i = 0; i < numRecord; i++) {
			int vipDurationDay, vipDurationMonth, vipDurationYear, normalDurationDay, normalDurationMonth, normalDurationYear, totalDurationDay, totalDurationMonth, totalDurationYear;
			int totalDuration = report[i].normalDuration + report[i].vipDuration;
			//Convert total duration days into duration in months and years
			DurationCalc(0, 0, 0, 0, 0, 0, &vipDurationDay, &vipDurationMonth, &vipDurationYear, &report[i].vipDuration, "duration");
			DurationCalc(0, 0, 0, 0, 0, 0, &normalDurationDay, &normalDurationMonth, &normalDurationYear, &report[i].normalDuration, "duration");
			DurationCalc(0, 0, 0, 0, 0, 0, &totalDurationDay, &totalDurationMonth, &totalDurationYear, &totalDuration, "duration");

			printf("\t| %-9s | %-41s | %-12s |    %c   | %02d-%02d-%4d |  %-11s |    %-6s   | %02d-%02d-%4d  |   %2dY %2dM    |     %2dY %2dM     |    %2dY %2dM     |\n",
				report[i].memID, report[i].memName, report[i].memIC, report[i].memGender, report[i].memBirthDate.day,
				report[i].memBirthDate.month, report[i].memBirthDate.year, report[i].memPhoneNo, report[i].memType, report[i].memExpiry.day,
				report[i].memExpiry.month, report[i].memExpiry.year, vipDurationYear, vipDurationMonth, normalDurationYear, normalDurationMonth,
				totalDurationYear, totalDurationMonth);

		}
		printf("\t-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	}
	else if (strcmp(selection, "vip") == 0) {

		//Save the member record with VIP membership duration > 31 into structure array
		while (!feof(fptr)) {
			int freadReturn = fread(&memberReport, sizeof(struct MemberInfo), 1, fptr);

			if (freadReturn == 1) {

				if (memberReport.vipDuration > 31) {
					report[numRecord] = memberReport;
					numRecord++;
				}
			}
		}

		//Arrange the member record in descending order based on the vip membership duration
		for (int i = 0; i < numRecord; i++) {

			for (int j = 0; j < numRecord; j++) {

				if (report[j].vipDuration < report[i].vipDuration) {

					memberReport = report[i];
					report[i] = report[j];
					report[j] = memberReport;
				}
			}
		}

		//Display member record in table form
		printf("\t-------------------------------\n");
		printf("\t|   VIP Member Loyalty Report |\n");
		printf("\t-------------------------------\n");

		printf("\t--------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("\t| %-9s | %-41s | %-12s | %-6s | %-10s | %-12s | %-11s | %-11s | %-12s |\n", "Member ID", "Member Name",
			"Member IC", "Gender", "Birth date", "Phone number", "Member Type", "Expiry Date", "VIP duration");
		printf("\t--------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		for (int i = 0; i < numRecord; i++) {
			int vipDurationDay, vipDurationMonth, vipDurationYear;
			//Convert total duration days into duration in months and years
			DurationCalc(0, 0, 0, 0, 0, 0, &vipDurationDay, &vipDurationMonth, &vipDurationYear, &report[i].vipDuration, "duration");

			printf("\t| %-9s | %-41s | %-12s |    %c   | %02d-%02d-%4d |  %-11s |    %-6s   | %02d-%02d-%4d  |   %2dY %2dM    |\n",
				report[i].memID, report[i].memName, report[i].memIC, report[i].memGender, report[i].memBirthDate.day,
				report[i].memBirthDate.month, report[i].memBirthDate.year, report[i].memPhoneNo, report[i].memType, report[i].memExpiry.day,
				report[i].memExpiry.month, report[i].memExpiry.year, vipDurationYear, vipDurationMonth);
		}
		printf("\t--------------------------------------------------------------------------------------------------------------------------------------------------------\n");

	}
	else if (strcmp(selection, "normal") == 0) {


		//Save the member record with Normal membership duration > 31 into structure array
		while (!feof(fptr)) {
			int freadReturn = fread(&memberReport, sizeof(struct MemberInfo), 1, fptr);

			if (freadReturn == 1) {

				if (memberReport.normalDuration > 31) {
					report[numRecord] = memberReport;
					numRecord++;
				}
			}
		}

		//Arrange the member record in descending order based on the normal membership duration
		for (int i = 0; i < numRecord; i++) {

			for (int j = 0; j < numRecord; j++) {

				if (report[j].normalDuration < report[i].normalDuration) {

					memberReport = report[i];
					report[i] = report[j];
					report[j] = memberReport;
				}
			}
		}

		//Display member record in table form
		printf("\t-------------------------------\n");
		printf("\t|Normal Member Loyalty Report |\n");
		printf("\t-------------------------------\n");

		printf("\t-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("\t| %-9s | %-41s | %-12s | %-6s | %-10s | %-12s | %-11s | %-11s | %-15s |\n", "Member ID", "Member Name",
			"Member IC", "Gender", "Birth date", "Phone number", "Member Type", "Expiry Date", "Normal duration");
		printf("\t-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");

		for (int i = 0; i < numRecord; i++) {
			int normalDurationDay, normalDurationMonth, normalDurationYear;
			//Convert total duration days into duration in months and years
			DurationCalc(0, 0, 0, 0, 0, 0, &normalDurationDay, &normalDurationMonth, &normalDurationYear, &report[i].normalDuration, "duration");

			printf("\t| %-9s | %-41s | %-12s |    %c   | %02d-%02d-%4d |  %-11s |    %-6s   | %02d-%02d-%4d  |     %2dY %2dM     |\n",
				report[i].memID, report[i].memName, report[i].memIC, report[i].memGender, report[i].memBirthDate.day,
				report[i].memBirthDate.month, report[i].memBirthDate.year, report[i].memPhoneNo, report[i].memType, report[i].memExpiry.day,
				report[i].memExpiry.month, report[i].memExpiry.year, normalDurationYear, normalDurationMonth);

		}
		printf("\t-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");

	}
	fclose(fptr);
	system("\tpause");
}

/// <summary>
/// Function to display member status report
/// </summary>
/// <param name="selection">( inactive - display inactive member report | active - display active member report)</param>
void MemberStatusReport(char selection[]) {

	FILE* fptr;
	fptr = fopen("Member information.bin", "rb");

	struct MemberInfo report[51], memberReport;

	int numRecord = 0, duration[51], temp;

	system("cls");

	//Display member status report based on selection
	if (strcmp(selection, "active") == 0) {

		printf("\t-------------------------------\n");
		printf("\t|     Active Member Report    |\n");
		printf("\t-------------------------------\n");

		printf("\t-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("\t| %-9s | %-41s | %-12s | %-6s | %-10s | %-12s | %-11s | %-11s | %-15s |\n", "Member ID", "Member Name",
			"Member IC", "Gender", "Birth date", "Phone number", "Member Type", "Expiry Date", "Expiry duration");
		printf("\t-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");

		//Save the member record who the status is active into structure array
		while (!feof(fptr)) {
			int freadReturn = fread(&memberReport, sizeof(struct MemberInfo), 1, fptr);

			if (freadReturn == 1) {
				if (strcmp(memberReport.memstatus, "Active") == 0) {
					//Calculate duration between the current date and membership expiry duration
					DurationCalc(CurrentDate("DD"), CurrentDate("MM"), CurrentDate("YYYY"), memberReport.memExpiry.day, memberReport.memExpiry.month, memberReport.memExpiry.year, 0, 0, 0, &duration[numRecord], "day");

					report[numRecord] = memberReport;
					numRecord++;
				}
			}
		}

		//Rearrange the member record in ascending order based on the remaining membership duration
		for (int i = 0; i < numRecord; i++) {

			for (int j = 0; j < numRecord; j++) {

				if (duration[j] > duration[i]) {
					memberReport = report[i];
					report[i] = report[j];
					report[j] = memberReport;
					temp = duration[i];
					duration[i] = duration[j];
					duration[j] = temp;

				}
			}
		}

		//Display member record in table form
		for (int i = 0; i < numRecord; i++) {
			int expiryDurationDay, expiryDurationMonth, expiryDurationYear;

			//Convert remaining membership duration into duration in months and years
			DurationCalc(CurrentDate("DD"), CurrentDate("MM"), CurrentDate("YYYY"), report[i].memExpiry.day, report[i].memExpiry.month, report[i].memExpiry.year, &expiryDurationDay, &expiryDurationMonth, &expiryDurationYear, &duration[i], "duration");

			printf("\t| %-9s | %-41s | %-12s |    %c   | %02d-%02d-%4d |  %-11s |    %-6s   | %02d-%02d-%4d  |   %2dY %2dM %2dD   |\n",
				report[i].memID, report[i].memName, report[i].memIC, report[i].memGender, report[i].memBirthDate.day,
				report[i].memBirthDate.month, report[i].memBirthDate.year, report[i].memPhoneNo, report[i].memType, report[i].memExpiry.day,
				report[i].memExpiry.month, report[i].memExpiry.year, expiryDurationYear, expiryDurationMonth, expiryDurationDay);

		}
		printf("\t-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");

	}
	else if (strcmp(selection, "inactive") == 0) {

		//Save the member record who the status is inactive into structure array
		while (!feof(fptr)) {
			int freadReturn = fread(&memberReport, sizeof(struct MemberInfo), 1, fptr);

			if (freadReturn == 1) {
				if (strcmp(memberReport.memstatus, "Inactive") == 0) {

					DurationCalc(memberReport.memExpiry.day, memberReport.memExpiry.month, memberReport.memExpiry.year, CurrentDate("DD"), CurrentDate("MM"), CurrentDate("YYYY"), 0, 0, 0, &duration[numRecord], "day");

					report[numRecord] = memberReport;
					numRecord++;
				}
			}
		}

		printf("\t-------------------------------\n");
		printf("\t|    Inactive Member Report    |\n");
		printf("\t-------------------------------\n");


		printf("\t-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");
		printf("\t| %-9s | %-41s | %-12s | %-6s | %-10s | %-12s | %-11s | %-11s | %-15s |\n", "Member ID", "Member Name",
			"Member IC", "Gender", "Birth date", "Phone number", "Member Type", "Expiry Date", "Expiry duration");
		printf("\t-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");

		//Rearrange the member record in descending order based on the expired membership duration
		for (int i = 0; i < numRecord; i++) {

			for (int j = 0; j < numRecord; j++) {

				if (duration[j] > duration[i]) {
					memberReport = report[i];
					report[i] = report[j];
					report[j] = memberReport;
					temp = duration[i];
					duration[i] = duration[j];
					duration[j] = temp;

				}
			}
		}

		//Display member record in table form
		for (int i = 0; i < numRecord; i++) {
			int expiryDurationDay, expiryDurationMonth, expiryDurationYear;

			//Convert expired membership duration into duration in months and years
			DurationCalc(report[i].memExpiry.day, report[i].memExpiry.month, report[i].memExpiry.year, CurrentDate("DD"), CurrentDate("MM"), CurrentDate("YYYY"), &expiryDurationDay, &expiryDurationMonth, &expiryDurationYear, &duration[i], "duration");

			printf("\t| %-9s | %-41s | %-12s |    %c   | %02d-%02d-%4d |  %-11s |    %-6s   | %02d-%02d-%4d  |   %2dY %2dM %2dD   |\n",
				report[i].memID, report[i].memName, report[i].memIC, report[i].memGender, report[i].memBirthDate.day,
				report[i].memBirthDate.month, report[i].memBirthDate.year, report[i].memPhoneNo, report[i].memType, report[i].memExpiry.day,
				report[i].memExpiry.month, report[i].memExpiry.year, expiryDurationYear, expiryDurationMonth, expiryDurationDay);

		}
		printf("\t-----------------------------------------------------------------------------------------------------------------------------------------------------------\n");

	}
	fclose(fptr);

	system("\tpause");
}

/// <summary>
/// Function to display member duration report
/// </summary>
void MemberDurationReport() {

	FILE* fptr;
	fptr = fopen("Member information.bin", "rb");

	struct MemberInfo report[51], memberReport;

	int numRecord = 0, duration[51], temp;

	system("cls");

	//Save the member record whose member duration is > 0 into structure array
	while (!feof(fptr)) {
		int freadReturn = fread(&memberReport, sizeof(struct MemberInfo), 1, fptr);

		if (freadReturn == 1) {
			//Calculate duration between member register date and current date and store it into array
			DurationCalc(memberReport.memRegister.day, memberReport.memRegister.month, memberReport.memRegister.year, CurrentDate("DD"), CurrentDate("MM"), CurrentDate("YYYY"), 0, 0, 0, &duration[numRecord], "day");
			if (duration[numRecord] > 0) {
				report[numRecord] = memberReport;
				numRecord++;
			}
		}

	}

	//Rearrange the member record into descending order based on the duration that the member is registered 
	for (int i = 0; i < numRecord; i++) {

		for (int j = 0; j < numRecord; j++) {

			if (duration[j] < duration[i]) {
				memberReport = report[i];
				report[i] = report[j];
				report[j] = memberReport;
				temp = duration[i];
				duration[i] = duration[j];
				duration[j] = temp;

			}
		}
	}

	//Display member record in table
	printf("\t-------------------------------\n");
	printf("\t|    Member duration Report   |\n");
	printf("\t-------------------------------\n");

	printf("\t-----------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("\t| %-9s | %-41s | %-12s | %-6s | %-10s | %-12s | %-13s | %-15s |\n", "Member ID", "Member Name",
		"Member IC", "Gender", "Birth date", "Phone number", "Register Date", "Member duration");
	printf("\t-----------------------------------------------------------------------------------------------------------------------------------------------\n");

	for (int i = 0; i < numRecord; i++) {
		int memberDurationDay, memberDurationMonth, memberDurationYear;

		//Convert the member register duration to duration in day, month and year
		DurationCalc(report[i].memRegister.day, report[i].memRegister.month, report[i].memRegister.year, CurrentDate("DD"), CurrentDate("MM"), CurrentDate("YYYY"), &memberDurationDay, &memberDurationMonth, &memberDurationYear, &duration[i], "duration");

		printf("\t| %-9s | %-41s | %-12s |    %c   | %02d-%02d-%4d |  %-11s |   %02d-%02d-%4d  |   %2dY %2dM %2dD   |\n",
			report[i].memID, report[i].memName, report[i].memIC, report[i].memGender, report[i].memBirthDate.day,
			report[i].memBirthDate.month, report[i].memBirthDate.year, report[i].memPhoneNo, report[i].memRegister.day,
			report[i].memRegister.month, report[i].memRegister.year, memberDurationYear, memberDurationMonth, memberDurationDay);

	}
	printf("\t-----------------------------------------------------------------------------------------------------------------------------------------------\n");

	system("\tpause");
}

/// <summary>
/// Function to display member information
/// </summary>
/// <param name="memberDisplay">Member structure passed in for displaying</param>
void MemberInfoDisplay(struct MemberInfo memberDisplay) {

	//Display member information
	printf("\n\tMember Infomation\n");
	printf("\t----------------------\n");
	printf("\tMember ID              : %-s\n", memberDisplay.memID);
	printf("\tMember IC No           : %-s\n", memberDisplay.memIC);
	printf("\tMember Name            : %-s\n", memberDisplay.memName);
	printf("\tMember Gender          : %c\n", memberDisplay.memGender);
	printf("\tMember Address         : %-s\n", memberDisplay.memAdd);
	printf("\tMember Phone number    : %-s\n", memberDisplay.memPhoneNo);
	printf("\tMember Birthdate       : %02d/%02d/%4d\n", memberDisplay.memBirthDate.day, memberDisplay.memBirthDate.month, memberDisplay.memBirthDate.year);
	printf("\tMember type            : %s\n", memberDisplay.memType);
	printf("\tMembership expiry date : %02d/%02d/%4d\n", memberDisplay.memExpiry.day, memberDisplay.memExpiry.month, memberDisplay.memExpiry.year);
}

/// <summary>
/// Fucntion to display invoice
/// </summary>
/// <param name="memberInvoice">Member structure passed in for displaying</param>
/// <param name="membershipDuration">Membership duration passed in for calculation and display </param>
/// <param name="membershipPrice">Membership price passed in for calculation and display</param>
/// <param name="refund">Refund passed in for calculation and display</param>
void MemberInvoice(struct MemberInfo memberInvoice, int membershipDuration, double membershipPrice, double refund) {
	double total;

	//Display invoice
	printf("\tInvoice\n");
	printf("\t-------\n");
	MemberInfoDisplay(memberInvoice);
	printf("\tMember duration        : %dyears\n", membershipDuration);

	if (refund != 0) {
		printf("\tRefund                 : %.2f\n", refund);
		total = (membershipDuration * membershipPrice) - refund;

	}
	else {
		total = membershipDuration * membershipPrice;

	}

	printf("\tTotal                  : Rm%0.2f\n", total);
}

/// <summary>
/// Function for updating member record in binary file
/// </summary>
/// <param name="updateMember">Passed in member structure for update purpose</param>
/// <param name="selection">( update - update member record in the binary file | expiry - check expiry date and update status of the member)</param>
void UpdateMemberDetails(struct MemberInfo updateMember, char selection[]) {
	FILE* readFptr = fopen("Member information.bin", "rb");
	FILE* writeFptr = fopen("Temp.bin", "wb");

	struct MemberInfo readMember;

	int currentDay, currentMonth, currentYear;

	if (strcmp(selection, "update") == 0) {

		//Read member record from the binary file
		while (!feof(readFptr)) {
			int freadReturn = fread(&readMember, sizeof(struct MemberInfo), 1, readFptr);

			if (freadReturn == 1) {
				//Write the modified member record into the temporary file
				if (strcmp(updateMember.memID, readMember.memID) == 0) {

					fwrite(&updateMember, sizeof(struct MemberInfo), 1, writeFptr);
					continue;
				}

				//Write the member record from the binary file into the temporary file
				fwrite(&readMember, sizeof(struct MemberInfo), 1, writeFptr);

			}
		}
	}
	else if (strcmp(selection, "expiry") == 0) {
		currentDay = CurrentDate("DD");
		currentMonth = CurrentDate("MM");
		currentYear = CurrentDate("YYYY");

		//Read member record from the binary file
		while (!feof(readFptr)) {
			int freadReturn = fread(&readMember, sizeof(struct MemberInfo), 1, readFptr);

			if (freadReturn == 1) {

				//Check member expiry date and update status
				if (readMember.memExpiry.year == currentYear) {

					if (readMember.memExpiry.month == currentMonth) {

						if (readMember.memExpiry.day <= currentDay) {
							strcpy(readMember.memstatus, "Inactive");
						}
					}
					else if (readMember.memExpiry.month < currentMonth) {
						strcpy(readMember.memstatus, "Inactive");
					}
				}
				else if (readMember.memExpiry.year < currentYear) {
					strcpy(readMember.memstatus, "Inactive");
				}
				fwrite(&readMember, sizeof(struct MemberInfo), 1, writeFptr);
			}
		}
	}

	fclose(writeFptr);
	fclose(readFptr);

	//Remove old member information binary file and rename the tempory binary file into new member information binary file
	remove("Member information.bin");
	rename("Temp.bin", "Member information.bin");
}

/// <summary>
/// Function to calculate duration between start date and end date into days , convert days to duration in day month year
/// </summary>
/// <param name="startDay">Start date day for calculate</param>
/// <param name="startMonth">Start date month for calculate</param>
/// <param name="startYear">Start date year for calculate</param>
/// <param name="endDay">End date day for calculate</param>
/// <param name="endMonth">End date month for calculate</param>
/// <param name="endYear">End date year for calculate</param>
/// <param name="durationDay">Duration in day</param>
/// <param name="durationMonth">Duration in month</param>
/// <param name="durationYear">Duration in year</param>
/// <param name="totalDurationDay">Total duration in day</param>
/// <param name="selection">( day - calculate total duration day between start date and end date | duration - convert total duration day into duration in day month year)</param>
void DurationCalc(int startDay, int startMonth, int startYear, int endDay, int endMonth, int endYear, int* durationDay, int* durationMonth, int* durationYear, int* totalDurationDay, char selection[]) {

	//Calculate total duration day between start date and end date
	if (strcmp(selection, "day") == 0) {
		*totalDurationDay = 0;

		if (startYear != endYear) {

			//add days duration of the first month of the startyear to the total duration day
			if (startMonth == 1 || startMonth == 3 || startMonth == 5 || startMonth == 7 || startMonth == 8 || startMonth == 10 || startMonth == 12) {
				*totalDurationDay = 31 - startDay + 1;
			}
			else if (startMonth == 4 || startMonth == 6 || startMonth == 9 || startMonth == 11) {
				*totalDurationDay = 30 - startDay + 1;
			}
			else if (startMonth == 2 && (startYear % 4 == 0 && (startYear % 100 != 0 || startYear % 400 == 0))) {
				*totalDurationDay = 29 - startDay + 1;
			}
			else {
				*totalDurationDay = 28 - startDay + 1;
			}


			//add days duration of the following months of the startyear to the total duration day
			for (int i = (startMonth + 1); i <= 12; i++) {

				if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12) {
					*totalDurationDay += 31;
				}
				else if (i == 4 || i == 6 || i == 9 || i == 11) {
					*totalDurationDay += 30;
				}
				else if (i == 2 && (startYear % 4 == 0 && (startYear % 100 != 0 || startYear % 400 == 0))) {
					*totalDurationDay += 29;
				}
				else {
					*totalDurationDay += 28;
				}
			}

			//add days duration of the last month of the endyear to the total duration day
			*totalDurationDay += endDay - 1;


			//add days duration of the previous months of the endyear to the total duration day
			for (int i = 1; i < endMonth; i++) {

				if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12) {
					*totalDurationDay += 31;
				}
				else if (i == 4 || i == 6 || i == 9 || i == 11) {
					*totalDurationDay += 30;
				}
				else if (i == 2 && (endYear % 4 == 0 && (endYear % 100 != 0 || endYear % 400 == 0))) {
					*totalDurationDay += 29;
				}
				else {
					*totalDurationDay += 28;
				}
			}

			//add days duration of the previous months of the endyear to the total duration day
			for (int i = (startYear + 1); i < endYear; i++) {

				if (i % 4 == 0 && (i % 100 != 0 || i % 400 == 0)) {
					*totalDurationDay += 366;
				}
				else {
					*totalDurationDay += 365;
				}
			}
		}
		else {

			if (startMonth == endMonth) {
				*totalDurationDay = endDay - startDay;
			}
			else {
				if (startMonth == 1 || startMonth == 3 || startMonth == 5 || startMonth == 7 || startMonth == 8 || startMonth == 10 || startMonth == 12) {
					*totalDurationDay = 31 - startDay + 1;
				}
				else if (startMonth == 4 || startMonth == 6 || startMonth == 9 || startMonth == 11) {
					*totalDurationDay = 30 - startDay + 1;
				}
				else if (startMonth == 2 && (startYear % 4 == 0 && (startYear % 100 != 0 || startYear % 400 == 0))) {
					*totalDurationDay = 29 - startDay + 1;
				}
				else {
					*totalDurationDay = 28 - startDay + 1;
				}

				for (int i = (startMonth + 1); i <= (endMonth - 1); i++) {

					if (i == 1 || i == 3 || i == 5 || i == 7 || i == 8 || i == 10 || i == 12) {
						*totalDurationDay += 31;
					}
					else if (i == 4 || i == 6 || i == 9 || i == 11) {
						*totalDurationDay += 30;

					}
					else if (i == 2 && (startYear % 4 == 0 && (startYear % 100 != 0 || startYear % 400 == 0))) {
						*totalDurationDay += 29;

					}
					else {
						*totalDurationDay += 28;
					}
				}
				*totalDurationDay += endDay - 1;
			}
		}
	}//Convert total duration day into duration in day month year
	else if (strcmp(selection, "duration") == 0) {
		*durationYear = 0;
		*durationMonth = 0;
		*durationDay = 0;

		if (endYear != 0 && startYear != 0) {

			*durationDay = *totalDurationDay;
			for (int i = (startYear + 1); i < endYear; i++) {

				if (i % 4 == 0 && (i % 100 != 0 || i % 400 == 0)) {
					*durationDay -= 366;
				}
				else {
					*durationDay -= 365;
				}
				*durationYear += 1;
			}

			if (*durationDay >= 365) {
				if ((startMonth == 1 || startMonth == 2) && (startYear % 4 == 0 && (startYear % 100 != 0 || startYear % 400 == 0)) || (startMonth != 1 && startMonth != 2) && (endYear % 4 == 0 && (endYear % 100 != 0 || endYear % 400 == 0))) {
					*durationDay -= 366;
				}
				else {
					*durationDay -= 365;
				}
				*durationYear += 1;
			}
			if (*durationDay > 30) {
				*durationMonth = *durationDay / (365 / 12);
			}


			switch (*durationMonth) {
			case 1:
				*durationDay = *durationDay - 31;
				break;

			case 2:
				if (endYear % 4 == 0 && (endYear % 100 != 0 || endYear % 400 == 0)) {
					*durationDay = *durationDay - 60;
				}
				else {
					*durationDay = *durationDay - 59;
				}
				break;

			case 3:
				if (endYear % 4 == 0 && (endYear % 100 != 0 || endYear % 400 == 0)) {
					*durationDay = *durationDay - 91;
				}
				else {
					*durationDay = *durationDay - 90;
				}
				break;

			case 4:
				if (endYear % 4 == 0 && (endYear % 100 != 0 || endYear % 400 == 0)) {
					*durationDay = *durationDay - 121;
				}
				else {
					*durationDay = *durationDay - 120;
				}
				break;

			case 5:
				if (endYear % 4 == 0 && (endYear % 100 != 0 || endYear % 400 == 0)) {
					*durationDay = *durationDay - 152;
				}
				else {
					*durationDay = *durationDay - 151;
				}
				break;

			case 6:
				if (endYear % 4 == 0 && (endYear % 100 != 0 || endYear % 400 == 0)) {
					*durationDay = *durationDay - 182;
				}
				else {
					*durationDay = *durationDay - 181;
				}
				break;

			case 7:
				if (endYear % 4 == 0 && (endYear % 100 != 0 || endYear % 400 == 0)) {
					*durationDay = *durationDay - 213;
				}
				else {
					*durationDay = *durationDay - 212;
				}
				break;

			case 8:
				if (endYear % 4 == 0 && (endYear % 100 != 0 || endYear % 400 == 0)) {
					*durationDay = *durationDay - 244;
				}
				else {
					*durationDay = *durationDay - 243;
				}
				break;

			case 9:
				if (endYear % 4 == 0 && (endYear % 100 != 0 || endYear % 400 == 0)) {
					*durationDay = *durationDay - 274;
				}
				else {
					*durationDay = *durationDay - 273;
				}
				break;

			case 10:
				if (endYear % 4 == 0 && (endYear % 100 != 0 || endYear % 400 == 0)) {
					*durationDay = *durationDay - 305;
				}
				else {
					*durationDay = *durationDay - 304;
				}
				break;

			case 11:
				if (endYear % 4 == 0 && (endYear % 100 != 0 || endYear % 400 == 0)) {
					*durationDay = *durationDay - 335;
				}
				else {
					*durationDay = *durationDay - 334;
				}
				break;

			default:
				break;
			}
		}
		else {
			*durationYear = *totalDurationDay / 365;
			*durationDay = (*totalDurationDay % 365);
			*durationMonth = *durationDay / (365 / 12);

			if (endYear != 0) {

				switch (*durationMonth) {
				case 1:
					*durationDay = *durationDay - 31;
					break;

				case 2:
					*durationDay = *durationDay - 59;
					break;

				case 3:
					*durationDay = *durationDay - 90;
					break;

				case 4:
					*durationDay = *durationDay - 120;
					break;

				case 5:
					*durationDay = *durationDay - 151;
					break;

				case 6:
					*durationDay = *durationDay - 181;
					break;

				case 7:
					*durationDay = *durationDay - 212;
					break;

				case 8:
					*durationDay = *durationDay - 243;
					break;

				case 9:
					*durationDay = *durationDay - 273;
					break;

				case 10:
					*durationDay = *durationDay - 304;
					break;

				case 11:
					*durationDay = *durationDay - 334;
					break;

				default:
					break;

				}
			}
		}
	}
}

/*-------------------- Booking Module General Function Definitions -------------------------*/

/// <summary>
/// User input for booking ID.
/// </summary>
/// <param name="bookingId">The variable to store booking ID</param>
void BookingIDInput(char bookingId[]) {

	int validation;

	//Booking ID input validation.
	do {
		validation = 1;
		printf("\tBooking ID: ");
		StringInput(bookingId, 7);
		strupr(bookingId);

		if (bookingId[0] == 'B' && bookingId[1] == 'K') {

			if (strlen(bookingId) != 5) {
				printf("\t\tInvalid booking ID length.\n");
				validation = 0;
				continue;
			}

			for (int i = 2; i < strlen(bookingId); i++) {
				if (isdigit(bookingId[i]) == 0) {
					printf("\t\tInvalid booking ID format.\n");
					validation = 0;
					break;
				}
			}

		}
		else {
			printf("\t\tInvalid booking ID format.\n");
			validation = 0;
		}

	} while (validation == 0);

}

/// <summary>
/// Function that creates time objects
/// </summary>
/// <param name="day">day of date</param>
/// <param name="month">month of date</param>
/// <param name="year">year of date</param>
/// <param name="timeObj">time object variable to store the time object created</param>
void CreateTimeObj(int day, int month, int year, time_t* timeObj) {
	int ret;
	struct tm info;

	info.tm_year = year - 1900;
	info.tm_mon = month - 1;
	info.tm_mday = day;
	info.tm_hour = 0;
	info.tm_min = 0;
	info.tm_sec = 0;
	info.tm_isdst = -1;

	ret = mktime(&info);
	if (ret == -1) {
		printf("\t\tError: unable to make time using mktime\n");
	}
	else {
		*timeObj = mktime(&info);
	}

}

/// <summary>
/// displays menu for booking module and request for selection.
/// </summary>
/// <param name="staffId">accepts the staff ID.</param>
/// <param name="staffName">accepts the staff name.</param>
/// <returns>The booking module selection.</returns>
int BookingMenu(char* staffId, char* staffName) {
	int selection;

	//Header
	BookingHeader(staffId, staffName, 0);

	//Booking module selections.
	printf("\t1 - View all bookings\n");
	printf("\t2 - Search bookings\n");
	printf("\t3 - Add new booking(s)\n");
	printf("\t4 - Edit booking(s)\n");
	printf("\t5 - Cancel booking(s)\n");
	printf("\t6 - View booking summary\n\n");

	printf("\t0 - MAIN MENU\n\n");
	printf("\t-----------------------------------\n");
	printf("\tPlease Enter Your Selection: ");
	selection = IntInput();
	return selection;
}

/// <summary>
/// Displays the header in booking module depending on current selection.
/// </summary>
/// <param name="staffId">accepts the staff ID.</param>
/// <param name="staffName">accepts the staff name.</param>
/// <param name="currentSelection">prints the header depending on the current menu selection.</param>
void BookingHeader(char* staffId, char* staffName, int currentSelection) {
	switch (currentSelection)
	{
	case 0:
		printf("\t------------------\n");
		printf("\t | Booking Menu | \n");
		printf("\t------------------\n");
		break;
	case 1:
		printf("\t------------------\n");
		printf("\t | Booking List | \n");
		printf("\t------------------\n");
		break;
	case 2:
		printf("\t----------------------------\n");
		printf("\t | Searching Booking List | \n");
		printf("\t----------------------------\n");
		break;
	case 3:
		printf("\t------------------------\n");
		printf("\t | Adding New Booking | \n");
		printf("\t------------------------\n");
		break;
	case 4:
		printf("\t------------------\n");
		printf("\t | Edit Booking | \n");
		printf("\t------------------\n");
		break;
	case 5:
		printf("\t--------------------\n");
		printf("\t | Cancel Booking | \n");
		printf("\t--------------------\n");
		break;
	case 6:
		printf("\t-----------------------------\n");
		printf("\t | Monthly Booking Summary | \n");
		printf("\t-----------------------------\n");
		break;
	default:
		printf("\t\tThis booking header does not exist.\n");
	}
	//prints the current staff logged in and his staff name.
	printf("\t[%s] | [%s]\n\n", staffId, staffName);

}

/// <summary>
/// Reads the booking list file, bookingList.bin to find out the number of booking records in the list.
/// </summary>
/// <returns>the number of available booking records</returns>
int BookingCount() {
	//Open bookingList.bin
	FILE* fptr;

	//structure array to store the booking details.
	Booking bk[99];

	//size of bk array
	int bkSize = 99;

	//Used to store the number of booking details available.
	int bCount;
	fptr = fopen("bookingList.bin", "rb");

	//Validate file opening, if the file could not be open, it means that there are still no booking records.
	if (!fptr) {
		return 0;
	}

	//read bookingList.bin to know the actual number of booking records.
	bCount = fread(&bk, sizeof(Booking), bkSize, fptr);

	//Close bookingList.bin
	fclose(fptr);

	return bCount;
}

/// <summary>
/// Reads the booking list
/// </summary>
/// <param name="bk">output parameter (structure array) to store the results from reading bookingList.bin</param>
/// <param name="size">The size of the structure array (integer)</param>
/// <param name="bCount">output parameter (integer) to store the number of booking records available</param>
void ReadBookingList(Booking bk[], int size, int* bCount) {
	//Used for opening bookingList.bin
	FILE* fptr;
	do {

		//open bookingList.bin
		fptr = fopen("bookingList.bin", "rb");

		//Validate file opening, if the file could not be open, create a new one.
		if (!fptr) {
			FILE* createfptr = fopen("bookingList.bin", "ab");

			if (!createfptr) {
				printf("bookingList.bin could not be created.");
				system("\tpause");
				return;
			}

			fclose(createfptr);
			continue;
		}

		//read bookingList.bin and store the number of booking records available.
		*bCount = fread(bk, sizeof(Booking), size, fptr);

		//Close bookingList.bin
		fclose(fptr);
	} while (*bCount < 0);

}

/// <summary>
/// Function that asks user input for facility ID, storing the corresponding facility into the output parameter.
/// </summary>
/// <param name="facilityName">The output parameter that accepts the address of bookedFacility</param>
void SelectBookingFacility(char* facilityName) {
	//Structure variable to store the facility types provided by our company.
	Facility availableFac[99] = { 0 };

	//Variable used to keep track of the number of facility types stored.
	int facTypeCount = 0;

	//Variable used to store the number of strings that are not equal.
	int notSameCount;

	//variable to store the facility ID inputted by user for input validation.
	char facId[3];

	//Used to store all the facilities record from Facilities.txt
	Facility fac[99];

	FILE* facilityPtr = fopen("Facilities.txt", "r");

	if (!facilityPtr) {
		printf("\t\tCould not open Facilities.txt\n");
		system("\tpause");
		return;
	}

	//To keep count of the number of elements in the structure array, fac.
	int fCount = 0;
	//Store it into the structure array, fac
	while (fscanf(facilityPtr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", fac[fCount].staffID, fac[fCount].facilityID, fac[fCount].types, fac[fCount].description, fac[fCount].venue, &fac[fCount].maximumUsers, &fac[fCount].normalPrice, &fac[fCount].vipPrice, &fac[fCount].d.day, &fac[fCount].d.month, &fac[fCount].d.year) != EOF) {
		fCount++;
	}

	fclose(facilityPtr);

	//Take the facility type from Facilities.txt and store it into structure array, availableFac
	for (int i = 0; i < fCount; i++) {
		//store the first facility name and the first 2 letters of the first facility id into structure array, availableFac.
		if (i == 0) {
			strcpy(availableFac[i].types, fac[i].types);
			strncpy(availableFac[i].facilityID, fac[i].facilityID, 2);
			facTypeCount++;
		}
		//For entries other than the first, check with the current stored facilities 
		//in structure array, availableFac.
		//Add the new facility type and id if it was not already in 
		//the current stored facilities in structure array, availableFac.
		else {
			notSameCount = 0;
			for (int j = 0; j < facTypeCount; j++) {

				if (strcmp(availableFac[j].types, fac[i].types) == 0) {
					continue;
				}
				else {
					notSameCount++;
					if (notSameCount == facTypeCount) {
						strcpy(availableFac[j + 1].types, fac[i].types);
						strncpy(availableFac[j + 1].facilityID, fac[i].facilityID, 2);
						facTypeCount++;
					}
					else {
						continue;
					}
				}

			}
		}

	}

	//print the available facilities
	printf("\tFacilities provided : \n");
	printf("\t-------------------------------\n");
	printf("\t| Facility ID | Facility type |\n");
	printf("\t-------------------------------\n");
	for (int i = 0; i < facTypeCount; i++) {
		printf("\t| %11s | %-13s |\n", availableFac[i].facilityID, availableFac[i].types);
	}
	printf("\t-------------------------------\n");
	printf("\n");

	//Loop control variable
	int cont = 1;
	//Input validation for facility ID inputted by user.
	do {
		printf("\tSelect the facility type by ID (Ex: KR): ");
		StringInput(facId, 3);
		strupr(facId);
		for (int i = 0; i < facTypeCount; i++) {
			if (strcmp(availableFac[i].facilityID, facId) == 0) {
				strcpy(facilityName, availableFac[i].types);
				cont = 0;
				break;
			}
		}
		if (cont != 0) {
			printf("\t\tInvalid facility ID inputted, try again\n");
		}
	} while (cont != 0);

}

/// <summary>
/// Function that asks for booking start time and duration.
/// </summary>
/// <param name="uInput">The user input before asking for booking time</param>
/// <returns>1 for successful time booking, 0 for unsuccessful time booking</returns>
int SelectTimeSlot(Booking* uInput) {
	//to store the success or failure of time slot selection.
	int status = 0;

	//structure array to store the booking details.
	Booking bk[99];

	//size of bk array
	int bkSize = 99;

	//structure array to store the specific booking details of the requested booking date for comparison.
	BookingComparison cBk[99] = { 0 };

	//Used to store the number of booking records available.
	int bCount;

	//variable used to keep track of the number of booking records with the requested booking date and facility type
	int cNoOfBooking;


	/*READING THE BOOKING SCHEDULE (TIME SLOT) AND STORE IT INTO AN ARRAY*/
	/*----------------------------------------------------------------------------------------*/

	//read the bookingSchedule.txt for the available time slots.
	FILE* timeFptr = fopen("bookingSchedule.txt", "r");

	//Use to store the strings for the time slots;
	char timeSlot[24][12];

	//Validate file opening.
	if (!timeFptr) {
		printf("\t\tCould not open bookingSchedule.txt\n");
		system("\tpause");
		system("cls");
		return 0;
	}

	//To keep track of the number of available timeslots.
	int timeSlotCount = 0;
	while (fscanf(timeFptr, "%[^\n]\n", timeSlot[timeSlotCount]) != EOF) {
		timeSlotCount++;
	}

	//close the bookingSchedule.txt
	fclose(timeFptr);

	/*----------------------------------------------------------------------------------------*/


	/*TAKING OUT THE BOOKING RECORDS WITH THE REQUESTED BOOKING DATE AND FACILITY NAME*/
	/*----------------------------------------------------------------------------------------*/

	/*READING THE ENTIRE BOOKING LIST INTO A STRUCTURE ARRAY (bk)*/
	/*-----------------------------*/

	ReadBookingList(bk, bkSize, &bCount);

	/*-----------------------------*/


	/*LOOPING THROUGH THE ENTIRE BOOKING LIST, TAKE ONLY BOOKING RECORDS WITH DATE AND FACILITY NAME REQUESTED*/
	/*-----------------------------*/

	cNoOfBooking = 0;
	//Store data with the booking date: the facility ID, booking time's timeSlotNo, bookedTime and duration.
	for (int i = 0; i < bCount; i++) {
		if (bk[i].bookedDate.day == uInput->bookedDate.day && bk[i].bookedDate.month == uInput->bookedDate.month && bk[i].bookedDate.year == uInput->bookedDate.year) {
			if (strcmp(bk[i].bookedFacility, uInput->bookedFacility) == 0) {

				strcpy(cBk[cNoOfBooking].facilityId, bk[i].facilityId);

				//Used to figure the available timeslots.
				for (int j = 0; j < timeSlotCount; j++) {
					if (strncmp(timeSlot[j], bk[i].bookedTime, 4) == 0) {
						cBk[cNoOfBooking].timeSlotNo = j;
						break;
					}
				}

				//Used to display the booked times to the user.
				strcpy(cBk[cNoOfBooking].bookedTime, bk[i].bookedTime);
				cBk[cNoOfBooking].duration = bk[i].duration;
				cNoOfBooking++;
			}
		}
	}

	/*-----------------------------*/

	/*----------------------------------------------------------------------------------------*/


	/*READING THE facilities.txt AND TAKE THE AVAILABLE FACILITY IDs*/
	/*----------------------------------------------------------------------------------------*/

	/*reading the facilities.txt*/
	/*-----------------------------*/

	//Read from Facilities.txt file
	Facility fac[99];
	FILE* facilityPtr = fopen("Facilities.txt", "r");

	if (!facilityPtr) {
		printf("\t\tCould not open Facilities.txt\n");
		system("\tpause");
		return 0;
	}

	//To keep count of the number of elements in the structure array, fac.
	int fCount = 0;
	//Store it into the structure array, fac
	while (fscanf(facilityPtr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", fac[fCount].staffID, fac[fCount].facilityID, fac[fCount].types, fac[fCount].description, fac[fCount].venue, &fac[fCount].maximumUsers, &fac[fCount].normalPrice, &fac[fCount].vipPrice, &fac[fCount].d.day, &fac[fCount].d.month, &fac[fCount].d.year) != EOF) {
		fCount++;
	}

	//Close Facilities.txt
	fclose(facilityPtr);

	/*-----------------------------*/

	/*take the facility IDs*/
	/*-----------------------------*/

	//Used to store the available facility IDs.
	char facId[9][5] = { 0 };

	//Used to keep count for the available facility IDs.
	int facIdCount = 0;
	//take the facility IDs with the customer's desired facility from facilities.txt and store it into facId array.
	for (int i = 0; i < fCount; i++) {
		if (strcmp(uInput->bookedFacility, fac[i].types) == 0) {
			strcpy(facId[facIdCount], fac[i].facilityID);
			facIdCount++;
		}
	}

	/*-----------------------------*/

	/*----------------------------------------------------------------------------------------*/


	//String to store the desired booking start time.
	char bookingStartTime[5];

	//Used to store the string for the booking end time.
	char bookingEndTime[5] = "";

	//Used to store the time booking confirmation.
	char timeBookingConfirmation;

	//loop control variable
	char cont;
	do {
		system("cls");

		/*DISPLAYING THE BOOKING RECORDS WITH THE DATE REQUESTED*/
		/*----------------------------------------------------------------------------------------*/

		printf("\tBooking Date - %02d/%02d/%04d\n\n", uInput->bookedDate.day, uInput->bookedDate.month, uInput->bookedDate.year);
		printf("\tWORKING HOURS: 8AM - 11PM\n\n");
		printf("\tRooms provided : |");
		for (int i = 0; i < facIdCount; i++) {
			printf(" %s |", facId[i]);
		}
		printf("\n\n");

		printf("\tPast booking records :\n");
		printf("\t-----------------------------\n");
		printf("\t| Facility ID | Booked Time |\n");
		printf("\t-----------------------------\n");

		if (cNoOfBooking == 0) {
			printf("\tThere are no past booking records.\n");
		}
		else {
			for (int i = 0; i < cNoOfBooking; i++) {
				printf("\t| %11s | %-11s |\n", cBk[i].facilityId, cBk[i].bookedTime);
			}
		}


		printf("\t-----------------------------\n");
		printf("\n");

		/*----------------------------------------------------------------------------------------*/


		/*USER INPUT*/
		/*----------------------------------------------------------------------------------------*/

		//Used to store the timeSlotNo for the booking start time.
		int bkStartingTsNo = -1;

		//Input validation for starting booking time.
		do {
			printf("\tPlease input the starting time for your booking (EX: 9pm): ");
			TimeInput(bookingStartTime);

			//Find what time slot number does the starting time belong to.
			for (int i = 0; i < timeSlotCount; i++) {
				if (strncmp(bookingStartTime, timeSlot[i], 4) == 0) {
					bkStartingTsNo = i;
					break;
				}
			}

			if (bkStartingTsNo == -1) {
				printf("\t\tPlease ensure your start time is within the working hours (8AM - 11PM)\n\n");
			}

		} while (bkStartingTsNo == -1);



		//Input validation for duration, maximum duration allowed is 3 hours.
		int validation;
		do {
			printf("\tPlease input the duration for the booking (Maximum duration: 3 hours) (in hours, Ex: 2) : ");
			uInput->duration = IntInput();
			if (uInput->duration > 3 || uInput->duration < 1) {
				validation = 0;
				printf("\t\tPlease ensure that duration is not more than 3 hours and is not a negative value.\n\n");
			}
			//Current bookingSchedule timeslot's last index = 14, if after adding duration is more than timeSlotCount (15), deny.
			else if (bkStartingTsNo + uInput->duration > timeSlotCount) {
				validation = 0;
				printf("\t\tOur facilities close at 11PM.\n\n");
			}
			else {
				validation = 1;
			}
		} while (validation == 0);

		/*----------------------------------------------------------------------------------------*/


		/*TO FIND OUT CLASHING BOOKING TIMEs*/
		/*----------------------------------------------------------------------------------------*/
		//Check booking start time, if it is before 8am

		//To store the available facility ID to be booked.
		char aFacId[5];

		//To keep track of the number of available rooms with the desired booking time.
		int aRoomCount = 0;

		//To keep track of the number of times the timeslot is equal with booked timeslots.
		int sameTsCount;

		//The following for loops will find out what are the facility IDs that are available to be booked.

		//Loop through all the available facility IDs
		for (int i = 0; i < facIdCount; i++) {
			sameTsCount = 0;
			//For each facility ID, loop through and compare with the current booking list.
			for (int j = 0; j < cNoOfBooking; j++) {

				//find booking record with the current facility ID
				if (strcmp(cBk[j].facilityId, facId[i]) == 0) {

					//For each booking record with the current facility ID, loop through k number of times, where k = the current booking record duration.
					for (int k = 0; k < cBk[j].duration; k++) {

						//compare the booking start timeSlotNo with k consecutive current booked timeSlotNo, where k = the current booking record duration.
						if (bkStartingTsNo == cBk[j].timeSlotNo + k) {
							sameTsCount++;
							break;
						}

						//compare the current booked timeSlotNo with l consecutive booking start timeSlotNo, where l = the desired duration.
						for (int l = 0; l < uInput->duration; l++) {
							if (cBk[j].timeSlotNo == bkStartingTsNo + l) {
								sameTsCount++;
								break;
							}
						}

						if (sameTsCount > 0) {
							break;
						}

					}

				}

				if (sameTsCount > 0)
					break;

			}

			if (sameTsCount == 0) {
				strcpy(aFacId, facId[i]);
				aRoomCount++;
				break;
			}

		}


		//Show sorry message if there are no available venues for this booking time.
		if (aRoomCount == 0) {
			printf("\n\t\tSorry, all of the available venues for this booking time has already been taken.\n");
			printf("\tDo you want to try another booking time? (Y/N) : ");
			cont = YesNoValidation(toupper(CharInput()));
		}
		else {

			//Store the bookedTime and the facility ID for that time into the output parameter structure (uInput).

			//current last index in timeSlot is 14.
			//If the index after adding the duration is equal to timeSlotCount (15),
			//it means that the end time is the last 4 characters of the last time slot (11PM)
			if (bkStartingTsNo + uInput->duration == timeSlotCount) {
				strncpy(bookingEndTime, &timeSlot[timeSlotCount - 1][7], 4);
			}
			else {
				strncpy(bookingEndTime, timeSlot[bkStartingTsNo + uInput->duration], 4);
			}

			strcpy(uInput->bookedTime, bookingStartTime);
			strcat(uInput->bookedTime, " - ");
			strcat(uInput->bookedTime, bookingEndTime);

			strcpy(uInput->facilityId, aFacId);

			//For storing the price of the facility, can be either be normal or VIP price.
			float price = 0.00;
			for (int i = 0; i < fCount; i++) {
				if (strcmp(uInput->facilityId, fac[i].facilityID) == 0) {
					if (strcmp(uInput->memType, "Normal") == 0) {
						price = fac[i].normalPrice;
					}
					else {
						price = fac[i].vipPrice;
					}
					uInput->bookingPrice = uInput->duration * price;
				}
			}

			//booking time successfully booked, so no need to repeat the loop.
			cont = 'N';

			system("cls");

			printf("\tTime booking successful.\n\n");

			printf("\tBooking details :\n\n");
			printf("\t-------------------------------------\n");
			printf("\t| Facility ID | Booked Time | Price |\n");
			printf("\t-------------------------------------\n");

			printf("\t| %11s | %-s | %.2f |\n", uInput->facilityId, uInput->bookedTime, uInput->bookingPrice);

			printf("\t-------------------------------------\n");

			//Confirmation of time booking.
			printf("\tAre you sure that you want to book this time? (Y/N) : ");
			timeBookingConfirmation = YesNoValidation(toupper(CharInput()));
			if (timeBookingConfirmation == 'Y') {
				status = 1;
			}
			else {
				status = 0;
			}

		}

		/*----------------------------------------------------------------------------------------*/

	} while (cont == 'Y');

	//Return the status of time slot selection, 1 for success, 0 for failure.
	return status;

}

/// <summary>
/// User input for remarks
/// </summary>
/// <param name="remarks">The variable that stores the remarks</param>
void RemarksInput(char remarks[]) {
	//remarks input validation
	do {
		printf("\tEnter remarks (Max: 20 characters) (Press enter if no remarks): ");
		rewind(stdin);
		fgets(remarks, 22, stdin);
		//replaces '\n' at the end of the string with '\0' character.
		remarks[strcspn(remarks, "\n")] = 0;
		if (remarks[0] == ' ') {
			printf("\t\tYou have some space at the front of your sentence.\n");
			continue;
		}
		//Ensure that remarks is not more than 20 characters long.
		else if (strlen(remarks) > 20 && remarks[0] != '\0') {
			printf("\t\tRemarks is too long. Please shorten it.\n");
			continue;
		}
		else {
			break;
		}
	} while (1);
	//if '\0' character is detected, means there was no remarks.
	if (remarks[0] == '\0') {
		strcpy(remarks, "-");
	}
}

/// <summary>
/// User input for booking date with validation.
/// </summary>
/// <param name="day">output parameter: day of booking</param>
/// <param name="month">output parameter: month of booking</param>
/// <param name="year">output parameter: year of booking</param>
void BookingDateInput(int* day, int* month, int* year) {
	//Input validation for booking date.
	do {
		printf("\tEnter booking date: \n");
		DateInput(day, month, year, "date input");
		if (*year < CurrentDate("YYYY")) {
			printf("\t\tBooking must be performed at least one day in advance.\n");
		}
		else if (*month < CurrentDate("MM")) {
			printf("\t\tBooking must be performed at least one day in advance.\n");
		}
		else {
			if (*month == CurrentDate("MM")) {
				if (*day <= CurrentDate("DD")) {
					printf("\t\tBooking must be performed at least one day in advance.\n");
				}
				else {
					break;
				}
			}
			else {
				break;
			}
		}
	} while (1);
}

/// <summary>
/// Function that ask user to input a time to search for.
/// </summary>
/// <param name="timeString">Variable to store the final time string</param>
void SearchForBookedTimeInput(char* timeString) {
	//Variable to store the starting time.
	char startTime[5];

	//Variable to store the ending time.
	char endTime[5];

	printf("\tEnter start time (ex: 2pm) : ");
	TimeInput(startTime);

	printf("\tEnter end time (ex: 10pm) : ");
	TimeInput(endTime);

	//Combining start time and end time to form the time string. Ex output: 08AM - 10AM
	strcpy(timeString, startTime);
	strcat(timeString, " - ");
	strcat(timeString, endTime);
}

/// <summary>
/// Function that receives a string to be search for, and a selection of what field to search for (B, M, S, F, T, D, R): 
/// | Booking ID (B) | Member ID (M) | Staff ID (S) | Facility (F) | Transaction Date (T) | Date (D) | Remarks (R) |
/// Selecting date to search allows the option to search by time.
/// </summary>
/// <param name="searchStr">The value that you want to search for</param>
/// <param name="selection">The selection of what field you want to search for</param>
/// <param name="bkPrinted">structure array: Used to store the booking records that are printed</param>
/// <param name="printCount">output parameter: Used to store the number of booking records that are printed</param>
void PrintfBookingRecord(char searchStr[], char selection, Booking bkPrinted[], int* printCount) {
	//Structure array to store all the booking records.
	Booking bk[99];
	int bkSize = 99;

	//Used to reset a structure array to null values.
	const Booking emptyBk[99] = { 0 };

	//Used to store the number of booking records available.
	int bCount = 0;

	//Used to store the number of booking records with this date.
	int dateCount;

	//Used to store the string form of the date
	char dateString[11];

	//Used to store the booking records with the requested date to be searched.
	Booking dBk[99];

	//Used to store the time input for searching
	char timeString[12];

	//Read the booking list and store the records into bk.
	ReadBookingList(bk, bkSize, &bCount);

	system("cls");

	printf("\tSearch Results:\n\n");

	//Displaying the table headers.
	BookingTableHeader();

	//Ensure printCount always start with 0
	*printCount = 0;

	switch (selection)
	{
	case 'B':
		for (int i = 0; i < bCount; i++) {
			if (strcmp(searchStr, bk[i].bookingId) == 0) {
				PrintSingleRecord(bk[i]);

				//Store the booking records printed as well as the number of booking records printed.
				bkPrinted[*printCount] = bk[i];
				(*printCount)++;
			}
		}
		printf("\t---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

		break;
	case 'M':
		for (int i = 0; i < bCount; i++) {
			if (strcmp(searchStr, bk[i].memberId) == 0) {
				PrintSingleRecord(bk[i]);

				//Store the booking records printed as well as the number of booking records printed.
				bkPrinted[*printCount] = bk[i];
				(*printCount)++;
			}
		}
		printf("\t---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

		printf("\t< %d booking records >\n", *printCount);
		break;
	case 'S':
		for (int i = 0; i < bCount; i++) {
			if (strcmp(searchStr, bk[i].staffId) == 0) {
				PrintSingleRecord(bk[i]);

				//Store the booking records printed as well as the number of booking records printed.
				bkPrinted[*printCount] = bk[i];
				(*printCount)++;
			}
		}
		printf("\t---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

		printf("\t< %d booking records >\n", *printCount);
		break;
	case 'F':
		for (int i = 0; i < bCount; i++) {
			if (strcmp(searchStr, bk[i].bookedFacility) == 0) {
				PrintSingleRecord(bk[i]);

				//Store the booking records printed as well as the number of booking records printed.
				bkPrinted[*printCount] = bk[i];
				(*printCount)++;
			}
		}
		printf("\t---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

		printf("\t< %d booking records >\n", *printCount);
		break;
	case 'T':
	case 'D':
		dateCount = 0;
		for (int i = 0; i < bCount; i++) {

			//forming the date strings to be used in searching the booking list
			if (selection == 'D') {
				sprintf(dateString, "%02d/%02d/%04d", bk[i].bookedDate.day, bk[i].bookedDate.month, bk[i].bookedDate.year);
			}
			else {
				sprintf(dateString, "%02d/%02d/%04d", bk[i].transactionDate.day, bk[i].transactionDate.month, bk[i].transactionDate.year);
			}

			//Searching by date
			if (strlen(searchStr) == 10) {
				if (strcmp(searchStr, dateString) == 0) {
					PrintSingleRecord(bk[i]);

					//Store the booking records with the requested date and the number of booking records with the requested date.
					dBk[dateCount] = bk[i];
					dateCount++;

					//Store the booking records printed as well as the number of booking records printed.
					bkPrinted[*printCount] = bk[i];
					(*printCount)++;
				}
			}

			//Searching by month, for current year
			else {
				if (strncmp(searchStr, &dateString[3], 6) == 0) {
					PrintSingleRecord(bk[i]);

					//Store the booking records with the requested date and the number of booking records with the requested date.
					dBk[dateCount] = bk[i];
					dateCount++;

					//Store the booking records printed as well as the number of booking records printed.
					bkPrinted[*printCount] = bk[i];
					(*printCount)++;
				}
			}

		}
		printf("\t---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

		printf("\t< %d booking records >\n", *printCount);

		//No need to search by time if there are no dates from the search results.
		if (*printCount == 0)
			break;

		//To store user's decision on whether to search by time or not.
		char searchTimeConfirmation;

		//Ask if user also wants to search by time in this date.

		printf("\n\tDo you also want to search by time? (Y/N) : ");
		searchTimeConfirmation = YesNoValidation(toupper(CharInput()));

		printf("\n");

		if (searchTimeConfirmation == 'Y') {
			//Reset the bkPrinted structure array to null values and reset the printCount to 0;
			for (int i = 0; i < *printCount; i++) {
				bkPrinted[*printCount] = emptyBk[*printCount];
			}
			*printCount = 0;

			SearchForBookedTimeInput(timeString);

			printf("\n\tSearch results for time: %s\n\n", timeString);

			//Displaying the table headers.
			BookingTableHeader();

			for (int i = 0; i < dateCount; i++) {
				if (strcmp(timeString, dBk[i].bookedTime) == 0) {
					PrintSingleRecord(dBk[i]);

					//Store the booking records printed as well as the number of booking records printed.
					bkPrinted[*printCount] = dBk[i];
					(*printCount)++;
				}
			}
			printf("\t---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

			printf("\t< %d booking records >\n", *printCount);

		}

		break;
	case 'R':
		for (int i = 0; i < bCount; i++) {
			if (strcmp(searchStr, bk[i].remarks) == 0) {
				PrintSingleRecord(bk[i]);

				//Store the booking records printed as well as the number of booking records printed.
				bkPrinted[*printCount] = bk[i];
				(*printCount)++;
			}
		}
		printf("\t---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");

		printf("\t< %d booking records >\n", *printCount);
		break;
	default:
		printf("\tInvalid selection\n");
		system("\tpause");
	}

	if (*printCount == 0) {
		printf("\tNo records found.\n");
	}

	system("\tpause");
}
//Example: PrintfBookingRecord(mInfo.memID, 'M', bkSearchResults, &searchResultCount);

/// <summary>
/// Prints the booking table header.
/// </summary>
void BookingTableHeader() {
	printf("\t---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("\t| %-10s | %-16s | %-9s | %-11s | %-12s | %-11s | %-12s | %-11s | %-5s | %-15s | %-20s |\n",
		"Booking ID", "Transaction Date", "Member ID", "Member Type", "Facility", "Facility ID",
		"Booking Date", "Time", "Price (RM)", "Staff in Charge", "Remarks");
	printf("\t---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

/// <summary>
/// Prints one line of booking record
/// </summary>
/// <param name="bk">Booking structure that stores the data to be printed</param>
void PrintSingleRecord(Booking bk) {
	printf("\t| %-10s | %02d/%02d/%04d%6s | %-9s | %-11s | %-12s | %-11s | %02d/%02d/%04d%2s | %-11s | %10.2f | %-15s | %-20s |\n",
		bk.bookingId, bk.transactionDate.day, bk.transactionDate.month, bk.transactionDate.year, "",
		bk.memberId, bk.memType, bk.bookedFacility, bk.facilityId,
		bk.bookedDate.day, bk.bookedDate.month, bk.bookedDate.year, "",
		bk.bookedTime, bk.bookingPrice, bk.staffId, bk.remarks);
}

/// <summary>
/// Prints the refunded bookings table header
/// </summary>
void RefundTableHeader() {
	printf("\t-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	printf("\t| %-16s | %-9s | %-11s | %-12s | %-11s | %-12s | %-11s | %-5s | %-15s | %-14s | %-20s |\n",
		"Transaction Date", "Member ID", "Member Type", "Facility", "Facility ID",
		"Booking Date", "Time", "Price (RM)", "Staff in Charge", "Date Cancelled", "Remarks");
	printf("\t-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

/// <summary>
/// Prints one line of refunded booking record.
/// </summary>
/// <param name="refundRecord">Booking structure that stores the data to be printed</param>
void PrintSingleRefundRecord(Booking refundRecord) {
	printf("\t| %02d/%02d/%04d%6s | %-9s | %-11s | %-12s | %-11s | %02d/%02d/%04d%2s | %-11s | %10.2f | %-15s | %02d/%02d/%04d%4s | %-20s |\n",
		refundRecord.transactionDate.day, refundRecord.transactionDate.month, refundRecord.transactionDate.year, "",
		refundRecord.memberId, refundRecord.memType, refundRecord.bookedFacility, refundRecord.facilityId,
		refundRecord.bookedDate.day, refundRecord.bookedDate.month, refundRecord.bookedDate.year, "",
		refundRecord.bookedTime, refundRecord.bookingPrice, refundRecord.staffId,
		refundRecord.refundDate.day, refundRecord.refundDate.month, refundRecord.refundDate.year, "", refundRecord.remarks);
}

/// <summary>
/// Prints the booking table header to the file pointer.
/// </summary>
/// <param name="fp">File pointer to the txt file for the data to be printed to</param>
void FprintBookingTableHeader(FILE* fp) {
	fprintf(fp, "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	fprintf(fp, "| %-10s | %-16s | %-9s | %-11s | %-12s | %-11s | %-12s | %-11s | %-5s | %-15s | %-20s |\n",
		"Booking ID", "Transaction Date", "Member ID", "Member Type", "Facility", "Facility ID",
		"Booking Date", "Time", "Price (RM)", "Staff in Charge", "Remarks");
	fprintf(fp, "---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

/// <summary>
/// Prints one line of booking record to the file pointer.
/// </summary>
/// <param name="bk">Booking structure that stores the data to be printed</param>
/// <param name="fp">File pointer to the txt file for the data to be printed to</param>
void FprintSingleRecord(Booking bk, FILE* fp) {
	fprintf(fp, "| %-10s | %02d/%02d/%04d%6s | %-9s | %-11s | %-12s | %-11s | %02d/%02d/%04d%2s | %-11s | %10.2f | %-15s | %-20s |\n",
		bk.bookingId, bk.transactionDate.day, bk.transactionDate.month, bk.transactionDate.year, "",
		bk.memberId, bk.memType, bk.bookedFacility, bk.facilityId,
		bk.bookedDate.day, bk.bookedDate.month, bk.bookedDate.year, "",
		bk.bookedTime, bk.bookingPrice, bk.staffId, bk.remarks);
}

/// <summary>
/// Prints the refunded bookings table header to the file pointer.
/// </summary>
/// <param name="fp">File pointer to the txt file for the data to be printed to</param>
void FprintRefundTableHeader(FILE* fp) {
	fprintf(fp, "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
	fprintf(fp, "| %-16s | %-9s | %-11s | %-12s | %-11s | %-12s | %-11s | %-5s | %-15s | %-14s | %-20s |\n",
		"Transaction Date", "Member ID", "Member Type", "Facility", "Facility ID",
		"Booking Date", "Time", "Price (RM)", "Staff in Charge", "Date Cancelled", "Remarks");
	fprintf(fp, "-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n");
}

/// <summary>
/// Prints one line of refunded booking record to the file pointer.
/// </summary>
/// <param name="refundRecord">Booking structure that stores the data to be printed</param>
/// <param name="fp">File pointer to the txt file for the data to be printed to</param>
void FprintSingleRefundRecord(Booking refundRecord, FILE* fp) {
	fprintf(fp, "| %02d/%02d/%04d%6s | %-9s | %-11s | %-12s | %-11s | %02d/%02d/%04d%2s | %-11s | %10.2f | %-15s | %02d/%02d/%04d%4s | %-20s |\n",
		refundRecord.transactionDate.day, refundRecord.transactionDate.month, refundRecord.transactionDate.year, "",
		refundRecord.memberId, refundRecord.memType, refundRecord.bookedFacility, refundRecord.facilityId,
		refundRecord.bookedDate.day, refundRecord.bookedDate.month, refundRecord.bookedDate.year, "",
		refundRecord.bookedTime, refundRecord.bookingPrice, refundRecord.staffId,
		refundRecord.refundDate.day, refundRecord.refundDate.month, refundRecord.refundDate.year, "", refundRecord.remarks);
}

/*-------------------- Facility Usage General Function Definition-------------------------*/

/// <summary>
/// Prints the daily summary of Facility Usage
/// </summary>
void DailyFacUseSummary()
{
	int date, month, year, checkNumRec = 0, i = 0;
	char cont;

	facilityUsage facUse[99];

	do {
		printf("\tEnter day > ");
		scanf("%d", &date);
		printf("\tEnter month > ");
		scanf("%d", &month);
		printf("\tEnter year > ");
		scanf("%d", &year);

		system("cls");
		printf("\tThis the date you inputted:\n\t%d/%d/%d\n\tIs it correct? (Y/N) > ", date, month, year);
		cont = YesNoValidation(toupper(CharInput()));
		system("cls");
		if (cont == 'Y')
		{

			FILE* readFptr = fopen("facUsageList.txt", "r");
			if (!readFptr)
			{
				printf("\tError! Could not read facUsageList.txt");
				return;
			}

			printf("\t----------------------------------\n");
			printf("\t|Facility Usage Sumamry (by Date)|\n");
			printf("\t----------------------------------\n");
			printf("\n\t| %-17s | %-9s |    %-5s    | %-11s |    %-4s   |  %-9s  | %-11s | %-5s | %-10s | %-5s |          %-17s |\n",
				"Facility Usage ID", "Member ID", "Event", "Facility ID", "Date",
				"Time Slot", "Member Type", "Price", "Usage Type", "Staff in Charge", "Remarks");

			while (fscanf(readFptr, "|%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%[^|]|%[^|]|%f|%[^|]|%[^|]|%[^|]|\n",
				&facUse[i].facUseID, &facUse[i].memberID, &facUse[i].facEvent, &facUse[i].facID, &facUse[i].walkInDate.day,
				&facUse[i].walkInDate.month, &facUse[i].walkInDate.year, &facUse[i].walkInTime, &facUse[i].memberType,
				&facUse[i].walkInPrice, &facUse[i].usageType, &facUse[i].staffID, &facUse[i].remarks) != EOF)
			{
				if (date == facUse[i].walkInDate.day && month == facUse[i].walkInDate.month && year == facUse[i].walkInDate.year)
				{
					printf("\n\t| %-17s | %-9s | %-11s | %-11s | %d/%d/%d | %-9s | %-11s | %-5.2f | %-10s | %-5s          | %-17s          |",
						facUse[i].facUseID, facUse[i].memberID, facUse[i].facEvent, facUse[i].facID, facUse[i].walkInDate.day,
						facUse[i].walkInDate.month, facUse[i].walkInDate.year, facUse[i].walkInTime, facUse[i].memberType,
						facUse[i].walkInPrice, facUse[i].usageType, facUse[i].staffID, facUse[i].remarks);

					checkNumRec++;
					i++;
				}
			}
			if (checkNumRec == 0)
			{
				system("cls");
				printf("\tNo such records were found that has date %d/%d/%d.\n", date, month, year);
				printf("\tReturning to Summary menu...\n");
				system("pause");
				break;
			}
			else
			{
				printf("\n\n\tAre the records selected correct? (Y/N) > ");
				cont = YesNoValidation(toupper(CharInput()));

				system("cls");
				if (cont == 'Y')
				{
					FILE* writeFptr = fopen("facUsageSummaryDaily.txt", "w");

					fprintf(writeFptr, "----------------------------------\n");
					fprintf(writeFptr, "|Facility Usage Sumamry (by Date)|\n");
					fprintf(writeFptr, "----------------------------------\n\n");

					fprintf(writeFptr, "| %-17s | %-9s |    %-5s    | %-11s |    %-4s   |  %-9s  | %-11s | %-5s | %-10s | %-5s |          %-17s |\n\n",
						"Facility Usage ID", "Member ID", "Event", "Facility ID", "Date", "Time Slot", "Member Type", "Price", "Usage Type", "Staff in Charge", "Remarks");

					for (i = 0; i < checkNumRec; i++)
					{
						fprintf(writeFptr, "| %-17s | %-9s | %-11s | %-11s | %d/%d/%d | %-9s | %-11s | %-5.2f | %-10s | %-5s          | %-17s          |\n",
							facUse[i].facUseID, facUse[i].memberID, facUse[i].facEvent, facUse[i].facID, facUse[i].walkInDate.day,
							facUse[i].walkInDate.month, facUse[i].walkInDate.year, facUse[i].walkInTime, facUse[i].memberType,
							facUse[i].walkInPrice, facUse[i].usageType, facUse[i].staffID, facUse[i].remarks);
					}
					fclose(writeFptr);
				}
			}
			fclose(readFptr);
			break;
		}
	} while (cont == 'Y');
	system("cls");
}


/// <summary>
/// Prints the monthly summary of Facility Usage
/// </summary>
void MonthlyFacUseSummary()
{
	system("cls");

	int month, year, checkNumRec = 0, i = 0;
	char cont;

	facilityUsage facUse[99];

	printf("\tEnter month > ");
	scanf("%d", &month);
	printf("\tEnter year > ");
	scanf("%d", &year);

	printf("\tThe input u entered are Month %d and Year %d? (Y/N) > ", month, year);
	cont = YesNoValidation(toupper(CharInput()));
	system("cls");
	do
	{
		if (cont == 'Y')
		{
			printf("\t----------------------------------\n");
			printf("\t|Facility Usage Sumamry (by Month)|\n");
			printf("\t----------------------------------\n");
			printf("\n\t| %-17s | %-9s |    %-5s    | %-11s |    %-4s   |  %-9s  | %-11s | %-5s | %-10s | %-5s |          %-17s |\n",
				"Facility Usage ID", "Member ID", "Event", "Facility ID", "Date",
				"Time Slot", "Member Type", "Price", "Usage Type", "Staff in Charge", "Remarks");

			FILE* readFptr = fopen("facUsageList.txt", "r");
			if (!readFptr)
			{
				printf("\tError! Could not read facUsageList.txt");
				return;
			}

			while (fscanf(readFptr, "|%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%[^|]|%[^|]|%f|%[^|]|%[^|]|%[^|]|\n",
				&facUse[i].facUseID, &facUse[i].memberID, &facUse[i].facEvent, &facUse[i].facID, &facUse[i].walkInDate.day,
				&facUse[i].walkInDate.month, &facUse[i].walkInDate.year, &facUse[i].walkInTime, &facUse[i].memberType,
				&facUse[i].walkInPrice, &facUse[i].usageType, &facUse[i].staffID, &facUse[i].remarks) != EOF)
			{
				if (month == facUse[i].walkInDate.month && year == facUse[i].walkInDate.year)
				{
					printf("\n\t| %-17s | %-9s | %-11s | %-11s | %d/%d/%d | %-9s | %-11s | %-5.2f | %-10s | %-5s          | %-17s          |",
						facUse[i].facUseID, facUse[i].memberID, facUse[i].facEvent, facUse[i].facID, facUse[i].walkInDate.day,
						facUse[i].walkInDate.month, facUse[i].walkInDate.year, facUse[i].walkInTime, facUse[i].memberType,
						facUse[i].walkInPrice, facUse[i].usageType, facUse[i].staffID, facUse[i].remarks);

					checkNumRec++;
					i++;
				}
			}
			if (checkNumRec == 0)
			{
				system("cls");
				printf("\n\tNo such records were found that has Month %d and Year %d.\n", month, year);
				system("pause");
				break;
			}
			else
			{
				printf("\n\n\tAre the records selected correct? (Y/N) > ");
				cont = YesNoValidation(toupper(CharInput()));
				if (cont == 'Y')
				{
					FILE* writeFptr = fopen("facUsageSummaryMonthly.txt", "w");

					fprintf(writeFptr, "----------------------------------\n");
					fprintf(writeFptr, "|Facility Usage Summary (by Month)|\n");
					fprintf(writeFptr, "----------------------------------\n\n");
					fprintf(writeFptr, "| %-17s | %-9s |    %-5s    | %-11s |    %-4s   |  %-9s  | %-11s | %-5s | %-10s | %-5s |          %-17s |\n\n",
						"Facility Usage ID", "Member ID", "Event", "Facility ID", "Date", "Time Slot", "Member Type", "Price", "Usage Type", "Staff in Charge", "Remarks");

					for (i = 0; i < checkNumRec; i++)
					{
						fprintf(writeFptr, "| %-17s | %-9s | %-11s | %-11s | %d/%d/%d | %-9s | %-11s | %-5.2f | %-10s | %-5s          | %-17s          |\n",
							facUse[i].facUseID, facUse[i].memberID, facUse[i].facEvent, facUse[i].facID, facUse[i].walkInDate.day,
							facUse[i].walkInDate.month, facUse[i].walkInDate.year, facUse[i].walkInTime, facUse[i].memberType,
							facUse[i].walkInPrice, facUse[i].usageType, facUse[i].staffID, facUse[i].remarks);
					}
					fclose(writeFptr);
				}
			}
			fclose(readFptr);
			break;
		}
	} while (cont == 'Y');
	system("cls");
}


/// <summary>
/// Prints the yearly summary of Facility Usage
/// </summary>
void YearlyFacUseSummary()
{
	int year, checkNumRec = 0, i = 0;
	char cont;

	facilityUsage facUse[99];

	printf("\tEnter year > ");
	scanf("%d", &year);
	system("cls");

	printf("\tThis the year you inputted:\n\t%d\n\tIs it correct (Y/N) > ", year);
	cont = YesNoValidation(toupper(CharInput()));
	system("cls");
	do
	{
		if (cont == 'Y')
		{
			printf("\t----------------------------------\n");
			printf("\t|Facility Usage Sumamry (by Year)|\n");
			printf("\t----------------------------------\n\n");
			printf("\t| %-17s | %-9s |     %-5s    | %-11s |    %-4s   |  %-9s  | %-11s | %-5s | %-10s | %-5s |          %-17s |\n",
				"Facility Usage ID", "Member ID", "Event", "Facility ID", "Date",
				"Time Slot", "Member Type", "Price", "Usage Type", "Staff in Charge", "Remarks");

			FILE* readFptr = fopen("facUsageList.txt", "r");
			if (!readFptr)
			{
				printf("\tError! Could not read facUsageList.txt");
				return;
			}

			while (fscanf(readFptr, "|%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%[^|]|%[^|]|%f|%[^|]|%[^|]|%[^|]|\n",
				&facUse[i].facUseID, &facUse[i].memberID, &facUse[i].facEvent, &facUse[i].facID, &facUse[i].walkInDate.day,
				&facUse[i].walkInDate.month, &facUse[i].walkInDate.year, &facUse[i].walkInTime, &facUse[i].memberType,
				&facUse[i].walkInPrice, &facUse[i].usageType, &facUse[i].staffID, &facUse[i].remarks) != EOF)
			{
				if (year == facUse[i].walkInDate.year)
				{
					printf("\n\t| %-17s | %-9s | %-11s | %-11s | %d/%d/%d | %-9s | %-11s | %-5.2f | %-10s | %-5s          | %-17s          |",
						facUse[i].facUseID, facUse[i].memberID, facUse[i].facEvent, facUse[i].facID, facUse[i].walkInDate.day,
						facUse[i].walkInDate.month, facUse[i].walkInDate.year, facUse[i].walkInTime, facUse[i].memberType,
						facUse[i].walkInPrice, facUse[i].usageType, facUse[i].staffID, facUse[i].remarks);
					checkNumRec++;
					i++;
				}
			}
			if (checkNumRec == 0)
			{
				system("cls");
				printf("\tNo such records were found that has Year %d.\n", year);
				system("pause");
				break;
			}
			else
			{
				printf("\n\n\tAre the records selected correct (Y/N) > ");
				cont = YesNoValidation(toupper(CharInput()));
				if (cont == 'Y')
				{
					FILE* writeFptr = fopen("facUsageSummaryYearly.txt", "w");

					fprintf(writeFptr, "----------------------------------\n");
					fprintf(writeFptr, "|Facility Usage Summary (by Year)|\n");
					fprintf(writeFptr, "----------------------------------\n\n");
					fprintf(writeFptr, "| %-17s | %-9s |    %-5s    | %-11s |    %-4s   |  %-9s  | %-11s | %-5s | %-10s | %-5s |          %-17s |\n\n",
						"Facility Usage ID", "Member ID", "Event", "Facility ID", "Date", "Time Slot", "Member Type", "Price", "Usage Type", "Staff in Charge", "Remarks");

					for (i = 0; i < checkNumRec; i++)
					{
						fprintf(writeFptr, "| %-17s | %-9s | %-11s | %-11s | %d/%d/%d | %-9s | %-11s | %-5.2f | %-10s | %-5s          | %-17s          |\n",
							facUse[i].facUseID, facUse[i].memberID, facUse[i].facEvent, facUse[i].facID, facUse[i].walkInDate.day,
							facUse[i].walkInDate.month, facUse[i].walkInDate.year, facUse[i].walkInTime, facUse[i].memberType,
							facUse[i].walkInPrice, facUse[i].usageType, facUse[i].staffID, facUse[i].remarks);
					}
					fclose(writeFptr);
				}
			}
			fclose(readFptr);
			break;
		}
	} while (cont == 'Y');
	system("cls");
}


/// <summary>
/// returns the last recorded facilityID number 
/// </summary>
int LastFacilityUseID()
{
	FILE* fptr = fopen("facUsageList.txt", "r");

	facilityUsage facUse;

	int lastRec = 0;

	while (!feof(fptr)) {
		fscanf(fptr, "|F%d|%[^|]|%[^|]|%[^|]|%d/%d/%d|%[^|]|%[^|]|%f|%[^|]|%[^|]|%[^|]|\n",
			&lastRec, facUse.memberID, facUse.facEvent, facUse.facID, &facUse.walkInDate.day,
			&facUse.walkInDate.month, &facUse.walkInDate.year, facUse.walkInTime, &facUse.memberType,
			&facUse.walkInPrice, facUse.usageType, facUse.staffID, facUse.remarks);
	}

	fclose(fptr);
	printf("%d", lastRec);

	system("cls");
	return lastRec;
}

/// <summary>
/// Selects the facility events available
/// </summary>
/// <param name="facilityName">the full name of facility events</param>
void SelectWalkInFacilityName(char* facilityName)
{

	//Structure variable to store the facilities provided by our company.
	Facility availableFac[99] = { 0 };
	//Variable used to keep track of the number of strings stored.
	int storeCount = 0;
	//Variable used to store the number of strings that are not equal.
	int notSameCount;
	//variable to store the facility ID inputted by user for input validation.
	char facId[3];
	//Read from txt file
	Facility facUse[99];

	FILE* facilityPtr = fopen("Facilities.txt", "r");

	if (!facilityPtr)
	{
		printf("\tCould not open Facilities.txt\n");
		return;
	}

	//To keep count of the number of elements in the structure array, fac.
	int fCount = 0;
	//Store it into the structure array, fac
	while (fscanf(facilityPtr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n", facUse[fCount].staffID, facUse[fCount].facilityID, facUse[fCount].types, facUse[fCount].description, facUse[fCount].venue, &facUse[fCount].maximumUsers, &facUse[fCount].normalPrice, &facUse[fCount].vipPrice, &facUse[fCount].d.day, &facUse[fCount].d.month, &facUse[fCount].d.year) != EOF)
	{
		fCount++;
	}

	fclose(facilityPtr);

	//Parse the Facilities.txt data into structure array, availableFac.
	for (int i = 0; i < fCount; i++)
	{
		//store the first facility name and the first 2 letters of the first facility id into structure array, availableFac.
		if (i == 0)
		{
			strcpy(availableFac[i].types, facUse[i].types);
			strncpy(availableFac[i].facilityID, facUse[i].facilityID, 2);
			storeCount++;
		}
		//For entries other than the first, check with the current stored facilities 
		//in structure array, availableFac.
		//Add the new facility name and id if it was not already in 
		//the current stored facilities in structure array, availableFac.
		else
		{
			notSameCount = 0;
			for (int j = 0; j < storeCount; j++)
			{

				if (strcmp(availableFac[j].types, facUse[i].types) == 0)
				{
					continue;
				}
				else
				{
					notSameCount++;
					if (notSameCount == storeCount)
					{
						strcpy(availableFac[j + 1].types, facUse[i].types);
						strncpy(availableFac[j + 1].facilityID, facUse[i].facilityID, 2);
						storeCount++;
					}
					else
					{
						continue;
					}

				}

			}
		}

	}

	//print the available facilities
	printf("\tFacilities provided:\n");
	printf("\t---------------------------\n");
	printf("\t|Facility ID|Facility type|\n");
	printf("\t---------------------------\n");
	for (int i = 0; i < 99; i++) {
		if (strcmp(availableFac[i].types, "\0") == 0 && strcmp(availableFac[i].facilityID, "\0") == 0)
			break;
		printf("\t|%11s|%-13s|\n", availableFac[i].facilityID, availableFac[i].types);
	}
	printf("\t---------------------------\n");
	printf("\n");

	//Loop control variable
	int cont = 1;
	//Input validation for facility ID inputted by user.
	do {
		printf("\tSelect the facility type you want to book (Choose ID): ");
		StringInput(facId, 3);
		strupr(facId);
		for (int i = 0; i < storeCount; i++) {
			if (strcmp(availableFac[i].facilityID, facId) == 0) {
				strcpy(facilityName, availableFac[i].types);
				cont = 0;
				break;
			}
		}
		if (cont != 0) {
			printf("\tInvalid facility ID inputted, try again\n");
		}
	} while (cont != 0);

	system("cls");
}

/// <summary>
/// To select and find available walk in time slot
/// </summary>
/// <param name="uInput">a variable that is connected to struct facilityUsage</param>
int SelectWalkInTimeSlot(facilityUsage* uInput)
{
	//to store the success or failure of time slot selection.
	int status = 0;

	//structure array to store the booking details.
	Booking bk[99];

	//size of bk array
	int bkSize = 99;

	//structure array to store the specific booking details of the requested booking date for comparison.
	BookingComparison cBk[99] = { 0 };

	//Used to store the number of booking records available.
	int bCount;

	//variable used to keep track of the number of booking records with the requested booking date and facility type
	int cNoOfBooking;

	/*READING THE BOOKING SCHEDULE (TIME SLOT) AND STORE IT INTO AN ARRAY*/
	/*----------------------------------------------------------------------------------------*/

	//read the bookingSchedule.txt for the available time slots.
	FILE* timeFptr = fopen("bookingSchedule.txt", "r");

	//Use to store the strings for the time slots;
	char timeSlot[24][12];

	//Validate file opening.
	if (!timeFptr) {
		printf("\tError! Unable to open bookingSchedule.txt\n");
		system("pause");
		system("cls");
		return 0;
	}

	//To keep track of the number of available timeslots.
	int timeSlotCount = 0;
	while (fscanf(timeFptr, "%[^\n]\n", timeSlot[timeSlotCount]) != EOF) {
		timeSlotCount++;

	}

	//close the bookingSchedule.txt
	fclose(timeFptr);

	/*----------------------------------------------------------------------------------------*/


	/*TAKING OUT THE BOOKING RECORDS WITH THE REQUESTED BOOKING DATE AND FACILITY NAME*/
	/*----------------------------------------------------------------------------------------*/

	/*READING THE ENTIRE BOOKING LIST INTO A STRUCTURE ARRAY (bk)*/
	/*-----------------------------*/

	ReadBookingList(bk, bkSize, &bCount);

	/*-----------------------------*/


	/*LOOPING THROUGH THE ENTIRE BOOKING LIST, TAKE ONLY BOOKING RECORDS WITH DATE AND FACILITY NAME REQUESTED*/
	/*-----------------------------*/

	cNoOfBooking = 0;

	//Store data with the booking date: the facility ID, booking time's timeSlotNo, bookedTime and duration.
	for (int i = 0; i < bCount; i++)
	{
		if (bk[i].bookedDate.day == uInput->walkInDate.day && bk[i].bookedDate.month == uInput->walkInDate.month && bk[i].bookedDate.year == uInput->walkInDate.year)
		{
			if (strcmp(bk[i].bookedFacility, uInput->facEvent) == 0)
			{
				strcpy(cBk[cNoOfBooking].facilityId, bk[i].facilityId);

				//Used to figure the available timeslots.
				for (int j = 0; j < timeSlotCount; j++)
				{
					if (strncmp(timeSlot[j], bk[i].bookedTime, 4) == 0)
					{
						cBk[cNoOfBooking].timeSlotNo = j;
						break;
					}
				}

				//Used to display the booked times to the user.
				strcpy(cBk[cNoOfBooking].bookedTime, bk[i].bookedTime);
				cBk[cNoOfBooking].duration = bk[i].duration;
				cNoOfBooking++;
			}
		}
	}

	/*-----------------------------*/

	/*----------------------------------------------------------------------------------------*/


	/*READING THE facilities.txt AND TAKE THE AVAILABLE FACILITY IDs*/
	/*----------------------------------------------------------------------------------------*/

	/*reading the facilities.txt*/
	/*-----------------------------*/

	//Read from Facilities.txt file
	Facility fac[99];
	FILE* facilityPtr = fopen("Facilities.txt", "r");

	if (!facilityPtr) {
		printf("\tCould not open Facilities.txt\n");
		return 0;
	}

	//To keep count of the number of elements in the structure array, fac.
	int fCount = 0;
	//Store it into the structure array, fac
	while (fscanf(facilityPtr, "%[^|]|%[^|]|%[^|]|%[^|]|%[^|]|%d|%f|%f|%d|%d|%d\n",
		fac[fCount].staffID,
		fac[fCount].facilityID,
		fac[fCount].types,
		fac[fCount].description,
		fac[fCount].venue,
		&fac[fCount].maximumUsers,
		&fac[fCount].normalPrice,
		&fac[fCount].vipPrice,
		&fac[fCount].d.day,
		&fac[fCount].d.month,
		&fac[fCount].d.year) != EOF) {
		fCount++;
	}

	//Close Facilities.txt
	fclose(facilityPtr);

	/*-----------------------------*/

	/*take the facility IDs*/
	/*-----------------------------*/

	//Used to store the available facility IDs.
	char facId[9][5] = { 0 };

	//Used to keep count for the available facility IDs.
	int facIdCount = 0;
	//take the facility IDs with the customer's desired facility from facilities.txt and store it into facId array.
	for (int i = 0; i < fCount; i++)
	{
		if (strcmp(uInput->facEvent, fac[i].types) == 0)
		{
			strcpy(facId[facIdCount], fac[i].facilityID);
			facIdCount++;
		}
	}

	/*-----------------------------*/

	/*----------------------------------------------------------------------------------------*/


	//String to store the desired booking start time.
	char bookingStartTime[5];

	//Used to store the string for the booking end time.
	char bookingEndTime[5] = "";

	//loop control variable
	char cont;
	do {
		system("cls");

		/*DISPLAYING THE BOOKING RECORDS WITH THE DATE REQUESTED*/
		/*----------------------------------------------------------------------------------------*/

		printf("\tBooking Date - %02d/%02d/%04d\n\n", uInput->walkInDate.day, uInput->walkInDate.month, uInput->walkInDate.year);
		printf("\tWORKING HOURS: 8AM - 11PM\n\n");
		printf("\tPast booking records :\n");

		printf("\t--------------------------\n");
		printf("\t|Facility ID|Booked Time|\n");
		printf("\t--------------------------\n");
		for (int i = 0; i < cNoOfBooking; i++) {
			printf("\t|%11s|%-s|\n", cBk[i].facilityId, cBk[i].bookedTime);
		}
		printf("\t--------------------------\n");
		printf("\n");

		/*----------------------------------------------------------------------------------------*/


		/*USER INPUT*/
		/*----------------------------------------------------------------------------------------*/

		//Used to store the timeSlotNo for the booking start time.
		int bkStartingTsNo = -1;

		//Input validation for starting booking time.
		do
		{
			printf("\tPlease input the starting time for your booking (Ex: 9pm): ");
			TimeInput(bookingStartTime);

			//Find what time slot number does the starting time belong to.
			for (int i = 0; i < timeSlotCount; i++)
			{
				if (strncmp(bookingStartTime, timeSlot[i], 4) == 0)
				{
					bkStartingTsNo = i;
					break;
				}
			}
			if (bkStartingTsNo == -1)
			{
				printf("\tPlease ensure your start time is within the working hours (8AM - 11PM)\n\n");
			}
		} while (bkStartingTsNo == -1);

		//Input validation for duration, maximum duration allowed is 3 hours.
		int validation;
		do
		{
			printf("\tPlease input the duration for the booking (Maximum duration: 3 hours) (in hours, Ex: 2) : ");
			uInput->walkInDuration = IntInput();
			if (uInput->walkInDuration > 3 || uInput->walkInDuration < 1)
			{
				validation = 0;
				printf("\tPlease ensure that duration is not more than 3 hours and is not a negative value.\n\n");
			}
			//Current last index = 14, if after adding duration is more than timeSlotCount (15), deny.
			else if (bkStartingTsNo + uInput->walkInDuration > timeSlotCount)
			{
				validation = 0;
				printf("\tOur facilities close at 11PM.\n\n");
			}
			else
			{
				validation = 1;
			}
		} while (validation == 0);

		/*do {
			printf("\tPlease input the starting time for your booking (Ex: 9pm): ");
			TimeInput(bookingStartTime);

			strncpy(amPm, &bookingStartTime[2], 2);
			if (strcmp(bookingStartTime, "08AM") < 0 && strcmp(amPm, "AM") == 0) {
				validation = 0;
			}
			else if (strcmp(bookingStartTime, "12AM") == 0) {
				validation = 0;
			}
			else {
				validation = 1;
			}

			if (validation = 0) {
				printf("\tPlease ensure your start time is within the working hours (8AM - 11PM)\n\n");
			}

		} while (validation == 0);*/


		/*----------------------------------------------------------------------------------------*/

		/*TO FIND OUT CLASHING BOOKING TIMEs*/

		/*----------------------------------------------------------------------------------------*/
		//Check booking start time, if it is before 8am

		//To store the available facility ID to be booked.
		char aFacId[5];

		//To keep track of the number of available rooms with the desired booking time.
		int aRoomCount = 0;

		//To keep track of the number of times the timeslot is equal with booked timeslots.
		int sameTsCount;

		//The following for loops will find out what are the facility IDs that are available to be booked.

		//Loop through all the available facility IDs
		for (int i = 0; i < facIdCount; i++)
		{
			sameTsCount = 0;
			//For each facility ID, loop through and compare with the current booking list.
			for (int j = 0; j < cNoOfBooking; j++)
			{

				//find booking record with the current facility ID
				if (strcmp(cBk[j].facilityId, facId[i]) == 0)
				{

					//For each booking record with the current facility ID, loop through k number of times, where k = the current booking record duration.
					for (int k = 0; k < cBk[j].duration; k++)
					{

						//compare the booking start timeSlotNo with k consecutive current booked timeSlotNo, where k = the current booking record duration.
						if (bkStartingTsNo == cBk[j].timeSlotNo + k)
						{
							sameTsCount++;
							break;
						}

						//compare the current booked timeSlotNo with l consecutive booking start timeSlotNo, where l = the desired duration.
						for (int l = 0; l < uInput->walkInDuration; l++)
						{
							if (cBk[j].timeSlotNo == bkStartingTsNo + l)
							{
								sameTsCount++;
								break;
							}
						}
						if (sameTsCount > 0)
						{
							break;
						}
					}
				}
				if (sameTsCount > 0)
					break;
			}
			if (sameTsCount == 0)
			{
				strcpy(aFacId, facId[i]);
				aRoomCount++;
				break;
			}
		}

		//Show sorry message if there are no available venues for this booking time.
		if (aRoomCount == 0)
		{
			printf("\n\tSorry, all of the available venues for this booking time has already been taken.\n");
			printf("\tDo you want to try another booking time (Y/N) > ");
			cont = YesNoValidation(toupper(CharInput()));
		}
		else
		{
			//Store the bookedTime and the facility ID for that time into the output parameter structure.

			//current last index in timeSlot is 14.
			//If the index after adding the duration is equal to timeSlotCount (15),
			//it means that the end time is the last 4 characters of the last time slot (11PM)
			if (bkStartingTsNo + uInput->walkInDuration == timeSlotCount)
			{
				strncpy(bookingEndTime, &timeSlot[timeSlotCount - 1][7], 4);
			}
			else {
				strncpy(bookingEndTime, timeSlot[bkStartingTsNo + uInput->walkInDuration], 4);
			}

			strcpy(uInput->walkInTime, bookingStartTime);
			strcat(uInput->walkInTime, " - ");
			strcat(uInput->walkInTime, bookingEndTime);

			strcpy(uInput->facID, aFacId);

			//For storing the price of the facility, can be either be normal or VIP price.
			float price = 0.00;
			for (int i = 0; i < fCount; i++) {
				if (strcmp(uInput->facID, fac[i].facilityID) == 0)
				{
					if (strcmp(uInput->memberType, "Normal") == 0)
					{
						price = fac[i].normalPrice;
					}
					else {
						price = fac[i].vipPrice;
					}
					uInput->walkInPrice = uInput->walkInDuration * price;
				}
			}

			//booking time successfully booked, so no need to repeat the loop.
			cont = 'N';

			system("cls");

			printf("\tTime booking successful.\n\n");

			printf("\tBooking details :\n\n");
			printf("\t-------------------------------\n");
			printf("\t|Facility ID|Booked Time|Price|\n");
			printf("\t-------------------------------\n");

			printf("\t|%11s|%-s|%.2f|\n", uInput->facID, uInput->walkInTime, uInput->walkInPrice);

			printf("\t-------------------------------\n");

			status = 1;
		}

		/*----------------------------------------------------------------------------------------*/

	} while (cont == 'Y');

	system("cls");
	//Return the status of time slot selection, 1 for success, 0 for failure.
	return status;
}

/// <summary>
/// Keeps track of the number of walk in records recorded
/// </summary>
int WalkInCount()
{
	FILE* fptr = fopen("facUsageList.txt", "r");

	facilityUsage facUse;

	int walkInCount = 0;

	if (!fptr)
	{
		return 0;
	}

	while (fscanf(fptr, "|%[^|]|%[^|]|%[^|]|%[^|]|%d/%d/%d|%[^|]|%[^|]|%f|%[^|]|%[^|]|%[^|]|\n",
		&facUse.facUseID, &facUse.memberID, &facUse.facEvent, &facUse.facID, &facUse.walkInDate.day,
		&facUse.walkInDate.month, &facUse.walkInDate.year, &facUse.walkInTime, &facUse.memberType,
		&facUse.walkInPrice, &facUse.usageType, &facUse.staffID, &facUse.remarks) != EOF)
	{
		walkInCount++;
	}

	fclose(fptr);

	system("cls");

	return walkInCount;
}



//Lines counts