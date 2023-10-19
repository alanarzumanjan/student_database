#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int compare(char *s1, char *s2){
    while (*s1 != '\0' && *s2 != '\0'){
        if (*s1 != *s2){
            return 1;
        }
        s1++; s2++;
    } return 0;
}
struct Person {
    char name[30];
    char surname[15];
    int age;
    char class[10];
    int id;
};
int scan_maxid(){
    FILE *database = fopen("database.dat","rb+");
    if (database == NULL) {
        printf("No users in the database.\n");
        return 0;
    }

    struct Person person;
    int max_id = 0;

    while (fread(&person, sizeof(struct Person), 1, database)) {
        if (person.id > max_id) {
            max_id = person.id;
        }
    }

    fclose(database);
    return max_id;
}
void show_user() {

    FILE *database = fopen("database.dat", "rb+");
    if (database == NULL) {
        printf("No users in the database.\n");
        return;
    }

    struct Person person;

    while (fread(&person, sizeof(struct Person), 1, database)) {
        printf("ID: %d\n", person.id);
        printf("Name: %s\n", person.name);
        printf("Surname: %s\n", person.surname);
        printf("Age: %d\n", person.age);
        printf("Class: %s\n", person.class);
        printf("\n");
    }
    
    fclose(database);
}

void add_user(int max_id) {

    FILE *database = fopen("database.dat", "ab+");
    struct Person person;

    printf("User name: ");
    scanf("%s", person.name);

    printf("Surname: ");
    scanf("%s", person.surname);

    printf("Age: ");
    scanf("%d", &person.age);

    printf("Class: ");
    scanf("%s", person.class);
    person.id = max_id + 1;

    fwrite(&person, sizeof(struct Person), 1, database);
    fclose(database);
}

int main() {
    int user_id = 0;
    int max_id;
    bool flag = true;

    do {
        int choice;
        char answer[4];
        printf("=====================\n");
        printf("What do you want?\n");
        printf("1 - show user\n2 - add user\n3 - delete user\n4 - exit\n");
        printf("Your choice: "); 
        scanf("%d", &choice);
        printf("=====================\n");
        switch (choice) {
            case 1:
                show_user();
                break;
            case 2:
                max_id = scan_maxid();
                add_user(max_id);
                break;
            case 3:
                // Implement delete_user function here.
                // printf("Enter user_id to delete: ");
                // int to_delete;
                // scanf("%d", &to_delete);
                // delete_user(to_delete);
                break;
            case 4:
                flag = false;
                break;
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }

    } while(flag);

    return 0;
}
