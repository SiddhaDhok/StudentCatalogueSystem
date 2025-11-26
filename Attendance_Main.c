#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include "attendance.h"
void attendance()
{
	int option=0;
	int student_roll_no=0;
	int total_classes=0;
	int attended_classes=0;
	int present=0;
	char subject[50];
	float percentage=0;
	int new_option = 0;
	char name[50];
	printf("Welcome to the Student Attendance System.\n");
	printf("For entering names and subjects with 2 words, join them with an underscore.");
	printf("Please choose an option for the functionality you want.\n");
	printf("1. Mark attendance\n");
	printf("2. View attendance of one student\n");
	printf("3. Update attendance\n");
	printf("4. Calculate percentage\n");
	printf("5. View all attendance\n");
	printf("6. Delete student record\n");
	printf("Press any other number to exit\n");
	printf("Enter an option: ");
	scanf("%d", &option);
	while (option > 0 && option < 7)
	{
		if (option == 1)
		{
			printf("Enter student roll number: ");
			int result1 = scanf("%d", &student_roll_no);
			while (result1 != 1)
			{
				printf("Please enter a valid roll number.\n");
				while (getchar() != '\n');
				printf("Enter student roll number: ");
				result1=scanf("%d", &student_roll_no);
			}
			printf("Enter name in lowercase only: ");
			scanf("%s", name);
			printf("Enter subject in lowercase only: ");
			scanf("%s", subject);
			printf("If present, enter 1. Else enter 0 if absent: ");
			int result2 = scanf("%d", &present);
			while (result2 != 1)
			{
				printf("Please enter a valid number\n");
				while (getchar() != '\n');
				printf("If present, enter 1. Else enter 0 if absent: ");
				result2=scanf("%d", &present);
			}
			int check;
			check = mark_attendance(student_roll_no, name, subject, present);
			if (check == 0)
			{
				printf("Attendance marked successfully.\n");
			}
			else if (check == -2)
			{
				printf("This roll number is already associated with a name. Please enter a valid roll number.\n");
			}
			else
			{
				printf("Error occurred while marking attendance.\n");
			}
			printf("\nEnter next option: ");
			scanf("%d", &new_option);
			option = new_option;
		}
		else if (option == 2)
		{
			printf("Enter student roll number: ");
			int result1=scanf("%d", &student_roll_no);
			while (result1 != 1)
			{
				printf("Please enter a valid roll number.\n");
				while (getchar() != '\n');
				printf("Enter student roll number: ");
				result1=scanf("%d", &student_roll_no);
			}
			printf("Enter name in lowercase only: ");
			scanf("%s", name);
			printf("Enter subject in lowercase only: ");
			scanf("%s", subject);
			get_attendance_for_one_student(student_roll_no, name, subject);
			printf("\nEnter next option: ");
			scanf("%d", &new_option);
			option = new_option;

		}
		else if (option == 3)
		{
			printf("Enter student roll number: ");
			int result1=scanf("%d", &student_roll_no);
			while (result1 != 1)
			{
				printf("Please enter a valid roll number.\n");
				while (getchar() != '\n');
				printf("Enter student roll number: ");
				result1=scanf("%d", &student_roll_no);
			}
			printf("Enter name in lowercase only: ");
			scanf("%s", name);
			printf("Enter subject in lowercase only: ");
			scanf("%s", subject);
			printf("Enter total classes: ");
			int result2=scanf("%d", &total_classes);
			while (result2 != 1)
			{
				printf("Please enter a valid number.\n");
				while (getchar() != '\n');
				printf("Enter total classes: ");
				result2=scanf("%d", &total_classes);
			}
			printf("Enter attended classes: ");
			int result3=scanf("%d", &attended_classes);
			while (result3 != 1)
			{
				printf("Please enter a number.\n");
				while (getchar() != '\n');
				printf("Enter attended classes: ");
				result3=scanf("%d", &attended_classes);
			}
			if (attended_classes > total_classes)
			{
				printf("Please enter valid values for attended classes and total classes.\n");
			}
			else if (update_attendance(student_roll_no, name, subject, total_classes, attended_classes) == 0)
			{
				printf("Attendance updated successfully.\n");
			}
			printf("\nEnter next option: ");
			scanf("%d", &new_option);
			option = new_option;
		}
		else if (option == 4)
		{
			printf("Enter student roll number: ");
			int result1=scanf("%d", &student_roll_no);
			while (result1 != 1)
			{
				printf("Please enter a valid roll number.\n");
				while (getchar() != '\n');
				printf("Enter student roll number: ");
				result1=scanf("%d", &student_roll_no);
			}
			printf("Enter name in lowercase only: ");
			scanf("%s", name);
			printf("Enter subject in lowercase only: ");
			scanf("%s", subject);
			percentage = calculate_percentage(student_roll_no, name, subject);
			if (percentage == -1)
			{
				printf("Record not found.\n");
			}
			else
			{
				printf("%f\n", percentage);
			}
			printf("\nEnter next option: ");
			scanf("%d", &new_option);
			option = new_option;
		}
		else if (option == 5)
		{
			view_all_attendance();
			printf("\nEnter next option: ");
			scanf("%d", &new_option);
			option = new_option;
		}
		else if (option == 6)
		{
			printf("Enter student roll number: ");
			int result1=scanf("%d", &student_roll_no);
			while (result1 != 1)
			{
				printf("Please enter a valid roll number.\n");
				while (getchar() != '\n');
				printf("Enter student roll number: ");
				result1=scanf("%d", &student_roll_no);
			}
			printf("Enter name in lowercase only: ");
			scanf("%s", name);
			printf("Enter subject in lowercase only: ");
			scanf("%s", subject);
			delete_student_record(student_roll_no, name, subject);
			printf("\nEnter next option: ");
			scanf("%d", &new_option);
			option = new_option;
		}
	}
}