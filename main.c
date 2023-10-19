#include <stdio.h>
#include <string.h>
#include <stdbool.h>

int compare(char *s1, char *s2) {
    while (*s1 != '\0' && *s2 != '\0') {
        if (*s1 != *s2) {
            return 1;
        }
        s1++;
        s2++;
    }
    return 0;
}

struct Person {
    char name[20];
    char surname[20];
    int age;
    char class[10];
    char average[5];
    int id;
};

void print_person_data(struct Person person) {
    printf("ID: %d\n", person.id);
    printf("Name: %s\n", person.name);
    printf("Surname: %s\n", person.surname);
    printf("Age: %d\n", person.age);
    printf("Class: %s\n", person.class);
    printf("Average: %s\n\n", person.average);
}

int scan_maxid() {
    FILE *database = fopen("database.dat", "rb+");

    if (database == NULL) {
        printf("No database.\n");
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

void search_user() {
    FILE *database = fopen("database.dat", "rb");
    struct Person person;

    if (database == NULL) {
        printf("Error: Could not open the database file.\n");
        return;
    }

    printf("Enter person id, name, surname, age, class, average with spaces.\nIf you don't know, write 0.\nEnter: ");
    int id, age;
    char name[20], surname[20], class[10], average[5];
    scanf("%d %s %s %d %s %s", &id, name, surname, &age, class, average);
    printf("\n");

    int found = 0;
    while (fread(&person, sizeof(struct Person), 1, database)) {
        if ((id == 0 || id == person.id) &&
            (compare(name, "0") == 0 || compare(name, person.name) == 0) &&
            (compare(surname, "0") == 0 || compare(surname, person.surname) == 0) &&
            (age == 0 || age == person.age) &&
            (compare(class, "0") == 0 || compare(class, person.class) == 0) &&
            (compare(average, "0") == 0 || compare(average, person.average) == 0)) {
            print_person_data(person);
            found = 1;
        }
    }

    if (!found) {
        printf("No matching records found.\n");
    }

    fclose(database);
}

void show_user() {
    FILE *database = fopen("database.dat", "rb");

    struct Person person;
    int is_empty = 1;

    while (fread(&person, sizeof(struct Person), 1, database)) {
        print_person_data(person);
        is_empty = 0;
    }

    fclose(database);

    if (is_empty) {
        printf("No users in the database.\n");
    }

    printf("Do you want to search for a person in the database?\n 1.Yes\n2.No\nEnter number: ");
    char answer[4];
    scanf("%s", answer);

    if (compare(answer, "1") == 0) {
        search_user();
    }
}

void add_user(int max_id) {
    FILE *database = fopen("database.dat", "ab");
    struct Person person;

    printf("User name: ");
    scanf("%s", person.name);

    printf("Surname: ");
    scanf("%s", person.surname);

    printf("Age: ");
    scanf("%d", &person.age);

    printf("Class: ");
    scanf("%s", person.class);

    printf("Average: ");
    scanf("%s", person.average);

    person.id = max_id + 1;

    fwrite(&person, sizeof(struct Person), 1, database);
    fclose(database);
}

void delete_user(int id_to_delete) {
    FILE *database = fopen("database.dat", "r+");
    FILE *temp_database = fopen("temp_database.dat", "w");
    struct Person person;

    if (database == NULL || temp_database == NULL) {
        printf("Error: Could not open the database file(s).\n");
        return;
    }

    int found = 0;
    while (fread(&person, sizeof(struct Person), 1, database)) {
        if (person.id == id_to_delete) {
            found = 1;
        } else {
            fwrite(&person, sizeof(struct Person), 1, temp_database);
        }
    }

    fclose(database);
    fclose(temp_database);

    if (found) {
        remove("database.dat");
        rename("temp_database.dat", "database.dat");
        printf("User with ID %d has been deleted.\n", id_to_delete);
    } else {
        remove("temp_database.dat");
        printf("User with ID %d not found in the database.\n", id_to_delete);
    }
}

int main() {
    int max_id;
    bool flag = true;

    do {
        int choice;
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
                printf("Enter user_id to delete: ");
                int to_delete;
                scanf("%d", &to_delete);
                delete_user(to_delete);
                break;
            case 4:
                flag = false;
                break;
            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    } while (flag);

    return 0;
}
// gcc main.c -o main.c
// /.main.o
