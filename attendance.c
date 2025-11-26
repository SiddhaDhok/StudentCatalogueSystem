#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include "attendance.h"
// Attendance.h is the header,  where the struct Record and the function prototype are defined

int mark_attendance(int student_roll_no, const char* name, const char* subject, int count)
{
    FILE* fp;
    FILE* new;
    fp = fopen("attendance.txt", "r");
    new = fopen("new.txt", "w");
    struct Record r1;
    int found = 0;
    if (new == NULL)
    {
        return -1;
    }
    // if fp does not exist, create it
    if (fp == NULL)
    {
        fp = fopen("attendance.txt", "w");
        fclose(fp);
        fp = fopen("attendance.txt", "r");
    }
    char buffer[200];
    if (fgets(buffer, sizeof(buffer), fp))
    {
        fputs(buffer, new);
    }
    while (fscanf(fp, "%d %s %s %d %d", &r1.student_roll_no, r1.name, r1.subject, &r1.total_classes, &r1.attended_classes) == 5)
    {
        if (r1.student_roll_no == student_roll_no && strcmp(r1.subject, subject) == 0 && strcmp(r1.name, name)==0)
        {
            found = 1;
            r1.total_classes = r1.total_classes + 1;
            if (count != 1)
            {
                r1.attended_classes = r1.attended_classes + 1;
            }
        }
        else if (r1.student_roll_no == student_roll_no && strcmp(r1.name, name) != 0)
        {
            return -2;
        }
        fprintf(new, "%d %s %s %d %d\n", r1.student_roll_no, r1.name, r1.subject, r1.total_classes, r1.attended_classes);

    }
    if (!found)
    {
        int attended_classes = count ? 1 : 0;
        fprintf(new, "%d %s %s %d %d\n", student_roll_no, name, subject, 1, attended_classes);
    }
    fclose(fp);
    fclose(new);
    remove("attendance.txt");
    rename("new.txt", "attendance.txt");
    return 0;
}

void get_attendance_for_one_student(int student_roll_no, const char* name, const char* subject)
{
    FILE* fp;
    fp = fopen("attendance.txt", "r");
    struct Record r1;
    int found = 0;
    if (fp == NULL)
    {
        printf("Attendance.txt does not exist.\n");
        return;
    }
    char buffer[200];
    if (fgets(buffer, sizeof(buffer), fp))
    {
        printf("%s", buffer);
    }
    while (fscanf(fp, "%d %s %s %d %d", &r1.student_roll_no, r1.name, r1.subject, &r1.total_classes, &r1.attended_classes) == 5)
    {
        if (r1.student_roll_no == student_roll_no && strcmp(r1.subject, subject) == 0 && strcmp(r1.name, name)==0)
        {
            printf("%d %s %s %d %d\n", r1.student_roll_no, r1.name, r1.subject, r1.total_classes, r1.attended_classes);
            found = 1;
            break;
        }
    }
    if (!found)
    {
        printf("Record not found.\n");
    }
    fclose(fp);
    return;
}

float calculate_percentage(int student_roll_no, const char* name, const char* subject)
{
    FILE* fp;
    fp = fopen("attendance.txt", "r");
    struct Record r1;
    if (fp == NULL)
    {
        return -1.0; //record not found
    }
    char buffer[200];
    fgets(buffer, sizeof(buffer), fp);
    while (fscanf(fp, "%d %s %s %d %d", &r1.student_roll_no, r1.name, r1.subject, &r1.total_classes, &r1.attended_classes) == 5)
    {
        if (r1.student_roll_no == student_roll_no && strcmp(r1.subject, subject) == 0 && strcmp(r1.name, name)==0)
        {
            if (r1.total_classes == 0)
            {
                return 0.0; //division by zero not possible
            }
            else
            {
                float percentage = ((float)r1.attended_classes / r1.total_classes) * 100;
                fclose(fp);
                return percentage;
            }

        }
    }
    fclose(fp);
    return -1.0;
}
void view_all_attendance() //prints every record in the file
{
    FILE* fp;
    fp = fopen("attendance.txt", "r");
    struct Record r1;
    if (fp == NULL)
    {
        printf("No records found.\n");
        return;
    }
    char buffer[200];
    if (fgets(buffer, sizeof(buffer), fp))
    {
        printf("%s", buffer);
    }
    while (fscanf(fp, "%d %s %s %d %d", &r1.student_roll_no, r1. name, r1.subject, &r1.total_classes, &r1.attended_classes) == 5)
    {
        printf("%d %s %s %d %d\n", r1.student_roll_no, r1.name, r1.subject, r1.total_classes, r1.attended_classes);
    }
    fclose(fp);
}
void delete_student_record(int student_roll_no, const char* name, const char* subject)
{
    FILE* fp;
    FILE* temp;
    struct Record r1;
    int found = 0;
    fp = fopen("attendance.txt", "r");
    temp = fopen("temp.txt", "w");
    if (fp == NULL)
    {
        printf("No records found.\n");
        return;
    }
    if (temp == NULL)
    {
        printf("Error occured during creation of temporary file.\n");
        return;
    }
    char buffer[200];
    if (fgets(buffer, sizeof(buffer), fp))
    {
        fputs(buffer, temp);
    }
    while (fscanf(fp, "%d %s %s %d %d", &r1.student_roll_no, r1.name, r1.subject, &r1.total_classes, &r1.attended_classes) == 5)
    {
        if (r1.student_roll_no == student_roll_no && strcmp(r1.subject, subject) == 0 && strcmp(r1.name, name)==0)
        {
            found = 1;
            continue;
        }
        else
        {
            fprintf(temp, "%d %s %s %d %d\n", r1.student_roll_no, r1.name, r1.subject, r1.total_classes, r1.attended_classes);
        }
    }
    if (!found)
    {
        printf("No such record exists.\n");
        fclose(fp);
        fclose(temp);
        remove("temp.txt");
        return;
    }
    printf("Record deleted successfully.\n");
    fclose(fp);
    fclose(temp);
    remove("attendance.txt");
    rename("temp.txt", "attendance.txt");
    return;
}
int update_attendance(int student_roll_no, const char* name, const char* subject, int updated_total_classes, int updated_attended_classes)
{
    FILE* fp;
    FILE* new;
    fp = fopen("attendance.txt", "r");
    new = fopen("new.txt", "w");
    struct Record r1;
    int found = 0;
    if (new == NULL)
    {
        return -1;
    }
    // if fp does not exist, create it
    if (fp == NULL)
    {
        fp = fopen("attendance.txt", "w");
        fprintf(fp, "Roll Name Subject Total Attended\n");
        fclose(fp);
        fp = fopen("attendance.txt", "r");
    }
    char buffer[200];
    if (fgets(buffer, sizeof(buffer), fp))
    {
        fputs(buffer, new);
    }
    while (fscanf(fp, "%d %s %s %d %d", &r1.student_roll_no, r1.name, r1.subject, &r1.total_classes, &r1.attended_classes) == 5)
    {
        if (r1.student_roll_no == student_roll_no && strcmp(r1.subject, subject) == 0 && strcmp(r1.name, name)==0)
        {
            r1.total_classes = updated_total_classes;
            r1.attended_classes = updated_attended_classes;
            found = 1;
        }
        fprintf(new, "%d %s %s %d %d\n", r1.student_roll_no, r1.name, r1.subject, r1.total_classes, r1.attended_classes);
    }
    if (found == 0)
    {
        printf("Record not found.\n");
    }
    fclose(fp);
    fclose(new);
    remove("attendance.txt");
    rename("new.txt", "attendance.txt");
    return found ? 0 : -1;
}