#pragma once
#ifndef MARKS_H
#define MARKS_H

struct Student {
    char name[50];
    int roll;
    float marks;
    float time;
};
int loadStudents(struct Student students[], int max);
void addStudent();
void orderStudents(struct Student students[], int count);
void updateMarks(struct Student students[], int count);
void SectionA(struct Student students[], int count);
void SectionB(struct Student students[], int count);
void movelast5fromAtodem(struct Student students[], int count);
void movetop5fromBtopro(struct Student students[], int count);
void movdemtoB();
void movprotoA();
void sortSectionA(struct Student students[], int count);
void sortSectionB(struct Student students[], int count);
void printStudentsA();
void printStudentsB();
void deleteStudent(int RolltoDelete);
#endif
