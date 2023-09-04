#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Contact {
    char name[50];
    char phone[20];
    char address[100];
};

void addContact(FILE *file, struct Contact contact) {
    fprintf(file, "%s;%s;%s\n", contact.name, contact.phone, contact.address);
}

void displayContacts(FILE *file) {
    struct Contact contact;
    rewind(file);
    printf("Contact list\n");
    while (fscanf(file, "%[^;];%[^;];%[^\n]\n", contact.name, contact.phone, contact.address) != EOF) {
        printf("Name: %s\nPhone: %s\nAddress: %s\n\n", contact.name, contact.phone, contact.address);
    }
}

void searchContact(FILE *file, const char *name) {
    struct Contact contact;
    rewind(file);
    int found = 0;
    while (fscanf(file, "%[^;];%[^;];%[^\n]\n", contact.name, contact.phone, contact.address) != EOF) {
        if (strcmp(contact.name, name) == 0) {
            printf("Name: %s\nPhone: %s\nAddress: %s\n\n", contact.name, contact.phone, contact.address);
            found = 1;
            break;
        }
    }
    if (!found) {
        printf("Not found! '%s'.\n", name);
    }
}

int main() {
    FILE *file;
    file = fopen("contacts.txt", "a+");

    if (file == NULL) {
        printf("Error to open file!\n");
        return 1;
    }

    int choice;
    struct Contact newContact;

    do {
        printf("\nWelcome to the Contact Manager!\n");
        printf("1. Add a new contact\n");
        printf("2. Display all contacts\n");
        printf("3. Search for a contact\n");
        printf("4. Exit\n");
        printf("Enter your choice:");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter name: ");
                scanf("%s", newContact.name);
                printf("Enter phone number: ");
                scanf("%s", newContact.phone);
                printf("Enter address: ");
                scanf(" %[^\n]", newContact.address);
                addContact(file, newContact);
                printf("\nContact added successfully!\n");
                break;
            case 2:
                displayContacts(file);
                break;
            case 3:
                printf("Enter name to search for: ");
                char searchName[50];
                scanf("%s", searchName);
                searchContact(file, searchName);
                break;
            case 4:
                fclose(file);
                printf("Goodbye!\n");
                return 0;
            default:
                printf("Not found\n");
        }
    } while (choice != 4);

    return 0;
}
