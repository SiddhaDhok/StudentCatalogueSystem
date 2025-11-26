    #define _CRT_SECURE_NO_WARNINGS    
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include"marks.h"

        // struct Student{
        //     char name[50];
        //     int roll;
        //     float marks;
        //     float time;
        // };
    void marks();
    int loadStudents(struct Student students[], int max){
        FILE *f = fopen("Students.txt", "r");
        if (!f){
            printf("File not found!");
        }
        int count = 0;
        while (fscanf(f, "%d %s %f %f", &students[count].roll, students[count].name, &students[count].marks, &students[count].time)==4){
            count++;
        }
        fclose(f);
        return count;
    }

    void addStudent(){
        struct Student s;
        printf("Enter the roll number to check if it is already present:\n");
        printf("Roll: ");
        scanf("%d", &s.roll);

        FILE *check = fopen("Students.txt", "r");
        if (!check) {
            printf("Error opening Students.txt\n");
            return;
        }

        struct Student temp;
        while (fscanf(check, "%d %s %f %f", &temp.roll, temp.name, &temp.marks, &temp.time) == 4) {
            if (temp.roll == s.roll) {
                printf("Roll number already present!\n");
                fclose(check);
                return;
            }
        }
        fclose(check);

        printf("Enter the new student's details:\n");
        printf("Enter the roll number (only numbers): ");
        scanf("%d", &s.roll);
        printf("Name: ");
        scanf("%s", s.name);
        printf("Marks: ");
        scanf("%f", &s.marks);
        printf("Time: ");
        scanf("%f", &s.time);

        FILE *f = fopen("Students.txt", "a");
        if (!f) {
            printf("Error opening Students.txt\n");
            return;
        }

        fprintf(f, "%d %s %.2f %.2f\n", s.roll, s.name, s.marks, s.time);
        fclose(f);

        printf("Student added successfully!\n");
    }

    void orderStudents(struct Student students[], int count){
        for (int i=0; i<count-1; i++){
            for (int j=0; j<count-i-1; j++){
                if (students[j].marks<students[j+1].marks){
                    struct Student temp = students[j];
                    students[j]=students[j+1];
                    students[j+1]=temp;
                }
                else if (students[j].marks==students[j+1].marks && (students[j].time>students[j+1].time)){
                    struct Student temp = students[j];
                    students[j]=students[j+1];
                    students[j+1]=temp;
                }
            }
        }
    }

    void updateMarks(struct Student students[], int count){
        int rollNo;
        float newMarks;
        char y;
        printf("Do you want to update any student's marks?(y/n) ");
        scanf(" %c", &y);

        while (y=='Y' || y=='y'){
            printf("Enter the roll number (only numbers): ");
            scanf("%d", &rollNo);
            printf("Enter the new marks: ");
            scanf("%f", &newMarks);

            int found = 0;
            for (int i=0; i<count; i++){
                if (students[i].roll==rollNo){
                    students[i].marks=newMarks;
                    found = 1;
                    printf("Marks updated successfully\n");
                    break;
                }
            }
            if (!found){
                printf("Roll number not found!\n");
            }

            printf("Do you want to update another student's marks?(y/n) ");
            scanf(" %c", &y);
        }

        FILE *f = fopen("Students.txt", "w");
        for (int i=0; i<count; i++){
            fprintf(f, "%d %s %.2f %.2f\n", students[i].roll, students[i].name, students[i].marks, students[i].time);
        }
        fclose(f);   
    }

    void SectionA(struct Student students[], int count){
        FILE *f = fopen("StudentsA.txt", "w");
        if (!f){
            printf("File not found");
        }
        for (int i=0; i<count/2; i++){
            fprintf(f, "%d. %s, %.2f, %.2f\n", students[i].roll, students[i].name, students[i].marks, students[i].time);
        }
        fclose(f);
    }

    void SectionB(struct Student students[], int count){
        FILE *f = fopen("StudentsB.txt", "w");
        if (!f){
            printf("File not found");
        }
        for (int i=count/2; i<count; i++){
            fprintf(f, "%d. %s, %.2f, %.2f\n", students[i].roll, students[i].name, students[i].marks, students[i].time);
        }
        fclose(f);
    }

    void movelast5fromAtodem(struct Student students[], int count){
        int half = count/2;
        int start = half-5;
        FILE *fd = fopen("Demoted.txt", "w");
        for (int i=start; i<half; i++){
            fprintf(fd, "%d %s %.2f %.2f\n", students[i].roll, students[i].name, students[i].marks, students[i].time);
        }
        fclose(fd);

        FILE *fa = fopen("StudentsA.txt", "w");
        for (int i=0; i<start; i++){
            fprintf(fa, "%d %s %.2f %.2f\n", students[i].roll, students[i].name, students[i].marks, students[i].time);
        }
        fclose(fa);
    }

    void movetop5fromBtopro(struct Student students[], int count){
        int half = count/2;
        FILE *fp = fopen("Promoted.txt", "w");
        for (int i=half; i<half+5; i++){
            fprintf(fp, "%d %s %.2f %.2f\n", students[i].roll, students[i].name, students[i].marks, students[i].time);
        }
        fclose(fp);

        FILE *fb = fopen("StudentsB.txt", "w");
        for (int i=half+5; i<count; i++){
            fprintf(fb, "%d %s %.2f %.2f\n", students[i].roll, students[i].name, students[i].marks, students[i].time);
        }
        fclose(fb);
    }

    void movdemtoB(){
        FILE *fd = fopen("Demoted.txt", "r");
        if (!fd){
            printf("Demoted file not found");
        }
        FILE *fb = fopen("StudentsB.txt", "a");
        char line[200];
        while (fgets(line, sizeof(line), fd)){
            fputs(line, fb);
        }
        fclose(fd);
        fclose(fb);
    }

    void movprotoA(){
        FILE *fp = fopen("Promoted.txt", "r");
        if (!fp){
            printf("Promoted file is not found");
        }
        FILE *fa = fopen("StudentsA.txt", "a");
        char line[200];
        while (fgets(line, sizeof(line), fp)){
            fputs(line, fa);
        }
        fclose(fp);
        fclose(fa);
    }

    void sortSectionA(struct Student students[], int count) {
        int half = count/2;

        for (int i=0; i<half-1; i++) {
            for (int j=0; j<half-i-1; j++) {
                if (students[j].marks < students[j+1].marks || (students[j].marks == students[j+1].marks && students[j].time > students[j+1].time)) {
                    struct Student temp = students[j];
                    students[j] = students[j+1];
                    students[j+1] = temp;
                }
            }
        }
    }

    void sortSectionB(struct Student students[], int count){
        int half = count/2;
        for (int i=half; i<count-1; i++){
            for (int j=half; j<count-(i-half)-1; j++){
                if (students[j].marks<students[j+1].marks || (students[j].marks==students[j+1].marks && students[j].time>students[j+1].time)){
                    struct Student temp = students[j];
                    students[j]=students[j+1];
                    students[j+1] = temp;
                }
            }
        }
        FILE *fb = fopen("StudentsB.txt", "w");
        for (int i = half; i < count; i++) {
            fprintf(fb, "%d %s %.2f %.2f\n", students[i].roll, students[i].name, students[i].marks, students[i].time);
        }
        fclose(fb);
    }

    void printStudentsA(){
        FILE *fa = fopen("StudentsA.txt", "r");
        if (!fa){
            printf("StudentsA file now found!\n");
        }
        struct Student s;
        printf("Section A students\n");
        while (fscanf(fa, "%d %s %f %f", &s.roll, s.name, &s.marks, &s.time)==4){
            printf("%d) %s %.2f %.2f\n", s.roll, s.name, s.marks, s.time);
        }
        fclose(fa);
    }

    void printStudentsB(){
        FILE *fb = fopen("StudentsB.txt", "r");
        if (!fb){
            printf("StudentsB file now found!\n");
        }
        struct Student s;
        printf("Section B students\n");
        while (fscanf(fb, "%d %s %f %f", &s.roll, s.name, &s.marks, &s.time)==4){
            printf("%d) %s %.2f %.2f\n", s.roll, s.name, s.marks, s.time);
        }
        fclose(fb);
    }

    void deleteStudent(int RolltoDelete){
        struct Student students[100];
        int count = loadStudents(students, 100);
        int newCount=0;
        int found = 0;
        struct Student updated[100];
        for (int i=0; i<count; i++){
            if (students[i].roll == RolltoDelete){
                found = 1;
                continue;
            }
            updated[newCount++] = students[i];
        }
        if (!found){
            printf("No student with roll number %d is found\n", RolltoDelete);
        }

        FILE *f = fopen("Students.txt", "w");
        if (!f){
            printf("File not found\n");
        }
        for (int i=0; i<newCount; i++){
            fprintf(f, "%d %s %.2f %.2f\n", updated[i].roll, updated[i].name, updated[i].marks, updated[i].time);
        }
        fclose(f);
        if (found)
            printf("Student with roll number %d is deleted successfully.\n", RolltoDelete);
    }

    void marks() {
        struct Student students[100];
        int choice;
        printf("1. Add a new student\n");
        printf("2. Update the student's marks\n");
        printf("3. See the student's and their marks with separate sections\n");
        printf("4. Delete a student record\n");
        printf("5. Exit the program\n");
        printf("Enter the choice: ");
        scanf("%d", &choice);
        while (choice!=5){
            if (choice==1){
                addStudent();
            }
            int num = loadStudents(students, 100);
            if (choice==2){
                updateMarks(students, num);
            }
            orderStudents(students, num);   
            char sect;
            SectionA(students, num);
            SectionB(students, num);
            movelast5fromAtodem(students, num);
            movetop5fromBtopro(students, num);
            movdemtoB();
            sortSectionB(students, num);
            movprotoA();
            sortSectionA(students, num);
            if (choice==3){
                printf("Do you want to see section A or B(press A or B): ");
                scanf(" %c", &sect);
                if (sect=='A' || sect=='a'){
                    printStudentsA();
                }
                else if (sect=='B' || sect=='b'){
                    printStudentsB();
                }
            }
            int rol;
            if (choice==4){
                printf("Enter the roll number of the student you want to delete: ");
                scanf("%d", &rol);
                deleteStudent(rol);
            }
            printf("1. Add a new student\n");
            printf("2. Update the student's marks\n");
            printf("3. See the student's and their marks with separate sections\n");
            printf("4. Delete a student record\n");
            printf("5. Exit the program\n");
            printf("Enter the choice: ");
            scanf("%d", &choice);
        }
        printf("Exitted the program\n");
        return 0;
    }