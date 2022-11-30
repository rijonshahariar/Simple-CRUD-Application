#include<stdio.h>
#include<string.h>
#include<stdlib.h>

/*
1. a
created a structure named Course
*/

struct Course
{
    char code[20], name[100], enrolled[100][100];
    char section[5], teacher[10];
    int total;

};
struct Course std[100];

// end of 1.a

/*
1. b
showing data of particular teacher
*/
int n;
void readData()
{
    FILE *fp;
    fp = fopen("classDB.txt", "r");

    for(int i = 0; ; i++)
    {
        if(feof(fp))
        {
            break;
        }
        fscanf(fp, "%s", std[i].code);
        fscanf(fp, " %[^\n]", std[i].name);
        fscanf(fp, "%s", std[i].section);
        fscanf(fp, "%s", std[i].teacher);
        fscanf(fp, "%d", &std[i].total);
        if(std[i].total!=0)
        {
            for(int j = 0; j<std[i].total; j++){
            fscanf(fp, "%s", std[i].enrolled[j]);
            }
        }
        n = i; // counting total number of courses
    }
    fclose(fp);
}

void showData()
{
    char t[20];
    printf("Enter Teacher: ");
    scanf("%s", t);
    printf("\n");
    for(int i = 0; i<n; i++)
    {
        if(strstr(std[i].teacher, t) != NULL)
        {
            printf("Code: %s\n", std[i].code);
            printf("Name: %s\n", std[i].name);
            printf("Section: %s\n", std[i].section);
            printf("Number of Students: %d\n", std[i].total);
            if(std[i].total != 0){
                    for(int j = 0; j<std[i].total; j++){
                        printf("%s ", std[i].enrolled[j]);
                    }
                    printf("\n");
            }

        }
    }

}

// end of 1)b

/*
1. c
adding user information
*/

void writeData(){
    FILE *fp;
    fp = fopen("classDB.txt", "w");

    if(fp == NULL){
    fp = fopen("classDB.txt", "w");
    }

    for(int i = 0; i < n ; i++)
    {
        fprintf(fp, "%s\n", std[i].code);
        fprintf(fp, "%s\n", std[i].name);
        fprintf(fp, "%s\n", std[i].section);
        fprintf(fp, "%s\n", std[i].teacher);
        fprintf(fp, "%d\n", std[i].total);
        if(std[i].total!=0)
        {
             for(int j = 0; j<std[i].total; j++){
            fprintf(fp, "%s ", std[i].enrolled[j]);
             }
             fprintf(fp, "\n");
        }
    }
    fclose(fp);
}

void addInfo(){
    char a_code[100],a_name[100], a_section[5];
    char a_teacher[20];
    int a_total = 0;
    printf("Course Code: ");
    scanf("%s", a_code);
    printf("Course Name: ");
    scanf(" %[^\n]", a_name);
    printf("Section: ");
    scanf("%s", a_section);
    printf("Instructor: ");
    scanf("%s", a_teacher);

    strcpy(std[n].code,a_code);
    strcpy(std[n].name,a_name);
    strcpy(std[n].section,a_section);
    strcpy(std[n].teacher,a_teacher);
    std[n].total = a_total;
    n++;
}

// end of 1)c

/*
2. a
add a student in course by ID
*/

void addToCourse(){
    char id[10], ccode[20], sctn[5];
    printf("Enter ID, Course Code & Section: ");
    scanf("%s%s%s", id,ccode,sctn);

    for(int i =0; i<n; i++){
        if(strcmp(std[i].code, ccode) == 0 && strcmp(std[i].section,sctn) == 0){
            strcpy(std[i].enrolled[std[i].total], id);
            std[i].total++;
        }
    }
}

// end of 2)a

/*
2. b
delete courses with no students
*/

void deleteCourse(){
    int pos = -1;
    for(int i = 0; i<n; i++){
        if(std[i].total == 0){
            printf("\n%s IS DELETED\n\n", std[i].code);
            std[i] = std[i+1];
            n--;
        }

    }

}

// end of 2)b

int main()
{
    int inp;
    readData();
    printf("1. Courses by Teacher\n");
    printf("2. Add Information\n");
    printf("3. Add Student in Course\n");
    printf("4. Delete Empty Courses\n");
    printf("Enter Number: ");
    scanf("%d", &inp);

    switch(inp){
    case(1):
    showData();
    break;

    case(2):
    addInfo();
    writeData();
    break;

    case(3):
    addToCourse();
    writeData();
    break;

    case(4):
    deleteCourse();
    writeData();

    case(0):
        exit(0);
    }

}
