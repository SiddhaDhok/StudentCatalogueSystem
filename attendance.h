#pragma once
#ifndef ATTENDANCE_H
#define ATTENDANCE_H

struct Record {
    int student_roll_no;
    char name[50];
    char subject[50];
    int total_classes;
    int attended_classes;
};
// if count=1, mark as present, else absent
int mark_attendance(int student_roll_no, const char* name, const char* subject, int count); //
void get_attendance_for_one_student(int student_roll_no, const char* name, const char* subject); //
int update_attendance(int student_roll_no, const char* name, const char* subject, int total_classes, int attended_classes); //
float calculate_percentage(int student_roll_no, const char* name, const char* subject); //
void view_all_attendance(); //
void delete_student_record(int student_roll_no, const char* name, const char* subject); //deletes the record for a student and a subject
#endif