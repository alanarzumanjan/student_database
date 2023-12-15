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
    FILE *database = fopen("database.dat", "rb");

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

int str_len(const char *str) {
    int len = 0;
    while (str[len] != '\0') {
        len++;
    }
    return len;
}

int to_int(const char *str) {
    int result = 0;
    int sign = 1;
    int i = 0;

    while (str[i] == ' ') {
        i++;
    }

    if (str[i] == '-') {
        sign = -1;
        i++;
    } else if (str[i] == '+') {
        i++;
    }

    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    return result * sign;
}

bool is_integger(char c) {
    return (c >= '0' && c <= '9');
}

int is_valid_age(const char *age_str) {
    int has_digit = 0;
    for (int i = 0; age_str[i] != '\0'; i++) {
        if (!is_integger(age_str[i])) {
            printf("Invalid character. Please indicate in numbers, example - '7'\n");
            return 0;
        } else {
            has_digit = 1;
        }
    }

    if (has_digit) {
        int age = to_int(age_str);
        return age > 0;
    } else {
        printf("You didn't indicate your age. Please indicate in numbers, example - '7'\n");
        return 0;
    }
}

bool is_valid_char(char c) {
    return ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z') || c == '-');
}

bool is_valid_name(const char *name, const char *what) {
    int str_count = 0;
    for (int i = 0; name[i] != '\0'; i++) {
        if (is_valid_char(name[i])) {
            str_count++;
        } else {
            printf("The %s is invalid. It should contain only letters and '-'\n", what);
            return 0;
        }
    }

    if (str_count >= 2) {
        return 1;
    } else {
        printf("Invalid %s. It should contain at least two letters.\n", what);
        return 0;
    }
}

int is_valid_average(char *average){
    int avg = to_int(average);
    if(avg > 0 && avg <= 10){
        return 1;
    } else {
        printf("The average score can be from 1 to 10\n");
        return 0;
    }
}

void add_user(int max_id) {
    FILE *database = fopen("database.dat", "ab");
    struct Person person;
    printf("If you need to insert spaces, replace them with dashes '-'\nExample: Karlis-Gustavs\n");

    do {
        printf("User name: ");
        scanf("%s", person.name);
    } while (!is_valid_name(person.name, "name"));

    do {
        printf("Surname: ");
        scanf("%s", person.surname);
    } while (!is_valid_name(person.surname, "surname"));


    char age_str[10];
    do {
        printf("Age: ");
        scanf("%s", age_str);
        
    } while (!is_valid_age(age_str));
    person.age = to_int(age_str);

    printf("Class: ");
    scanf("%s", person.class);

    do {
        printf("Average: ");
        scanf("%s", person.average);
        
    } while (!is_valid_average(person.average));
    

    person.id = max_id + 1;

    fwrite(&person, sizeof(struct Person), 1, database);
    fclose(database);
}

void delete_user() {
    do {
        FILE *database = fopen("database.dat", "rb");
        FILE *temp_database = fopen("temp_database.dat", "wb");
        struct Person person;
        printf("Enter user_id to delete: ");
        int id_to_delete;
        scanf("%d", &id_to_delete);

        if (database == NULL || temp_database == NULL) {
            printf("Error: Could not open the database file.\n");
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
            printf("User with ID %d not found in the database.\n\n", id_to_delete);
        }   

        int choice;
        do {
            printf("Do you want to delete another person?");
            printf("\n1 - Delete another person\n2 - No\nYour choice: ");
            scanf("%d", &choice);

            if (choice != 1 && choice != 2) {
                printf("Please enter a valid choice.\n");
            }
        } while (choice != 1 && choice != 2);

        if (choice == 2) {
            break;
        }

    } while (1);
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
                delete_user();

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
