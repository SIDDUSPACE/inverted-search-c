#include "database.h"
WordNode *index_head = NULL;
static WordNode *create_word_node(const char *word)
{
    WordNode *new_node = malloc(sizeof(WordNode));
    if (new_node == NULL)
    {
        perror("Memory allocation failed");
        return NULL;
    }
    snprintf(new_node->word, sizeof(new_node->word), "%s", word);
    new_node->file_list = NULL;
    new_node->link = NULL;
    return new_node;
}
WordNode *insert_word(const char *word)
{
    WordNode *current = index_head;
    WordNode *previous = NULL;
    while (current != NULL && strcmp(current->word, word) < 0)
    {
        previous = current;
        current = current->link;
    }
    if (current != NULL &&
        strcmp(current->word, word) == 0)
    {
        return current;
    }
    WordNode *new_node = create_word_node(word);
    if (new_node == NULL)
    {
        return NULL;
    }
    new_node->link = current;
    if (previous == NULL)
    {
        index_head = new_node;
    }
    else
    {
        previous->link = new_node;
    }
    return new_node;
}
int insert_file(WordNode *word_node, const char *filename)
{
    if (word_node == NULL || filename == NULL)
    {
        return 0;
    }
    FileNode *current = word_node->file_list;
    FileNode *previous = NULL;
    while (current != NULL)
    {
        if (strcmp(current->filename, filename) == 0)
        {
            current->word_count++;
            return 1;
        }
        previous = current;
        current = current->link;
    }
    FileNode *new_file = malloc(sizeof(FileNode));
    if (new_file == NULL)
    {
        perror("Memory allocation failed");
        return 0;
    }
    snprintf(new_file->filename, sizeof(new_file->filename), "%s", filename);
    new_file->word_count = 1;
    new_file->link = NULL;
    if (previous == NULL)
    {
        word_node->file_list = new_file;
    }
    else
    {
        previous->link = new_file;
    }
    return 1;
}
int create_database(const char *filename)
{
    if (filename == NULL)
        return 0;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror(filename);
        return 0;
    }
    char word[WORD_SIZE];
    int ch;
    int length = 0;
    int success = 1;
    while ((ch = fgetc(fp)) != EOF)
    {
        if (isalnum((unsigned char)ch) || ch == '_')
        {
            if (length < WORD_SIZE - 1)
            {
                word[length++] = (char)tolower((unsigned char)ch);
            }
        }
        else if (length > 0)
        {
            word[length] = '\0';
            WordNode *node = insert_word(word);
            if (node == NULL ||
                !insert_file(node, filename))
            {
                success = 0;
                break;
            }
            length = 0;
        }
    }
    if (success && length > 0)
    {
        word[length] = '\0';
        WordNode *node = insert_word(word);
        if (node == NULL || !insert_file(node, filename))
        {
            success = 0;
        }
    }
    fclose(fp);
    return success;
}
void display_database(void)
{
    WordNode *word_node = index_head;
    printf("\n========== INVERTED INDEX ==========\n");
    printf("%-20s %-20s %s\n", "WORD", "FILENAME", "COUNT");
    printf("------------------------------------" "----------------\n");
    while (word_node != NULL)
    {
        FileNode *file_node = word_node->file_list;
        while (file_node != NULL)
        {
            printf("%-20s %-20s %d\n", word_node->word, file_node->filename, file_node->word_count);
            file_node = file_node->link;
        }
        word_node = word_node->link;
    }
    printf("====================================\n");
}
void free_database(void)
{
    WordNode *word_node = index_head;
    while (word_node != NULL)
    {
        WordNode *next_word = word_node->link;
        FileNode *file_node = word_node->file_list;
        while (file_node != NULL)
        {
            FileNode *next_file = file_node->link;
            free(file_node);
            file_node = next_file;
        }
        free(word_node);
        word_node = next_word;
    }
    index_head = NULL;
}
