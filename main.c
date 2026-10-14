#include "database.h"
int main(void)
{
    int choice;
    char filename[FILE_SIZE];
    char word[WORD_SIZE];
    char response;
    while (1)
    {
        printf("\n===== INVERTED SEARCH =====\n");
        printf("1. Create DATABASE\n");
        printf("2. Display Database\n");
        printf("3. Update DATABASE\n");
        printf("4. Search\n");
        printf("5. Save Database\n");
        printf("6. Load Database\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Exiting.\n");
            break;
        }
        switch (choice)
        {
            case 1:
                printf("Enter filename: ");
                if (scanf("%259s", filename) != 1)
                    break;
                if (create_database(filename))
                    printf("Database created successfully.\n");
                else
                    printf("Database creation failed.\n");
                break;
            case 2:
                display_database();
                break;
            case 3:
                printf("Enter filename to update: ");
                if (scanf("%259s", filename) != 1)
                    break;
                if (update_database(filename))
                    printf("Database updated successfully.\n");
                else
                    printf("Database update failed.\n");
                break;
            case 4:
                printf("Enter word to search: ");
                if (scanf("%99s", word) != 1)
                    break;
                search_word(word);
                break;
            case 5:
                printf("Enter backup filename: ");
                if (scanf("%259s", filename) != 1)
                    break;
                if (save_database(filename))
                    printf("Database saved successfully.\n");
                else
                    printf("Database save failed.\n");
                break;
            case 6:
                printf("Enter backup filename to load: ");
                if (scanf("%259s", filename) != 1)
                    break;
                if (load_database(filename))
                    printf("Database loaded successfully.\n");
                else
                    printf("Database loading failed.\n");
                break;
            case 7:
                printf("Exit? (y/n): ");
                if (scanf(" %c", &response) != 1)
                    break;
                if (response == 'y' || response == 'Y')
                {
                    free_database();
                    return 0;
                }
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    }
    free_database();
    return 0;
}
