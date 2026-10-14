#include "database.h"
void search_word(const char *word)
{
    if (word == NULL || word[0] == '\0')
    {
        printf("Invalid search word.\n");
        return;
    }
    char normalized[WORD_SIZE];
    size_t i = 0;
    while (word[i] != '\0' && i < WORD_SIZE - 1)
    {
        normalized[i] =
            (char)tolower((unsigned char)word[i]);
        i++;
    }
    normalized[i] = '\0';
    WordNode *current = index_head;
    while (current != NULL && strcmp(current->word, normalized) < 0)
    {
        current = current->link;
    }
    if (current == NULL || strcmp(current->word, normalized) != 0)
    {
        printf("Word '%s' not found.\n", normalized);
        return;
    }
    printf("\nWord '%s' found:\n", normalized);
    FileNode *file = current->file_list;
    while (file != NULL)
    {
        printf("File: %-25s Occurrences: %d\n", file->filename, file->word_count);
        file = file->link;
    }
}
