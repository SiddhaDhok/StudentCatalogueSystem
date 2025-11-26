#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include "attendance.h"
#include "marks.h"
int main()
{
	int choice;
	int new_choice;
	printf("Welcome to the Student Catalogue System!\n");
	printf("To access the marks masterfile, enter 1.\n");
	printf("To access the attendance masterfile, enter 2.\n");
	printf("Enter choice: ");
	int result1 = scanf("%d", &choice);
	while (result1 != 1)
	{
		printf("Please enter a valid choice.\n");
		while (getchar() != '\n');
		printf("Enter choice: ");
		result1 = scanf("%d", &choice);
	}
	while (choice == 1 || choice == 2)
	{
		if (choice == 1)
		{
			marks();
			printf("\nEnter next option(1 for marks, 2 for attendance): ");
			scanf("%d", &new_choice);
			choice = new_choice;
		}
		else if (choice == 2)
		{
			attendance();
			printf("\nEnter next option(1 for marks, 2 for attendance): ");
			scanf("%d", &new_choice);
			choice = new_choice;
		}
	}
	printf("Goodbye!");
}