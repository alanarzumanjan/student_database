#include <stdio.h>
#include <string.h>
#include <stdbool.h>
void add_user(){
    FILE *database = fopen("database.bin","w");
    printf("User name: ");
    scanf("%s", person.name);

    printf("Surname: ");
    scanf("%s", person.surname);

    printf("Age: ");
    scanf("%d", &person.age);

    printf("Class: ");
    scanf("%c", &person.class);

    fwrite(&person, sizeof(struct Person), 1, database);
    fclose(database);
}
int compare(char *s1, char *s2){
    while (*s1 != '\0' && *s2 != '\0'){
        if (*s1 != *s2){
            return 1;
        } s1++; s2++;
    } return 0;
}

struct person {
    char name[30];
    char surname[15];
    int age;
    char class[10];
};

int main() {
    add_user();
    
    return 0;
}