
#include "database.h"
int update_database(const char *filename)
{
    if (filename == NULL)
        return 0;
    for (WordNode *word = index_head;
         word != NULL;
         word = word->link)
    {
        for (FileNode *file = word->file_list;
             file != NULL;
             file = file->link)
        {
            if (strcmp(file->filename, filename) == 0)
            {
                printf("File is already indexed: %s\n", filename);
                return 0;
            }
        }
    }
    return create_database(filename);
}
int save_database(const char *filename)
{
    if (filename == NULL)
        return 0;
    FILE *fp = fopen(filename, "w");
    if (fp == NULL)
    {
        perror(filename);
        return 0;
    }
    for (WordNode *word = index_head;
         word != NULL;
         word = word->link)
    {
        for (FileNode *file = word->file_list; file != NULL; file = file->link)
        {
            if (fprintf(fp, "%s:%s:%d\n", word->word, file->filename, file->word_count) < 0)
            {
                fclose(fp);
                return 0;
            }
        }
    }
    if (fclose(fp) != 0)
        return 0;
    return 1;
}
int load_database(const char *filename)
{
    if (filename == NULL)
        return 0;
    FILE *fp = fopen(filename, "r");
    if (fp == NULL)
    {
        perror(filename);
        return 0;
    }
    char line[FILE_SIZE + WORD_SIZE + 64];
    int success = 1;
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        char *word = strtok(line, ":");
        char *file = strtok(NULL, ":");
        char *count_text = strtok(NULL, ":\r\n");
        if (count_text != NULL)
        {
            count_text[strcspn(count_text, "\r\n")] = '\0'; 
        }
        if (word == NULL || file == NULL || count_text == NULL)
        {
            success = 0;
            break;
        }
        char *end;
        long count = strtol(count_text, &end, 10);
        if (*end != '\0' || count < 1 || count > 2147483647L)
        {
            success = 0;
            break;
        }
        WordNode *node = insert_word(word);
        if (node == NULL)
        {
            success = 0;
            break;
        }
        FileNode *existing = node->file_list;
        while (existing != NULL &&  strcmp(existing->filename, file) != 0)
        {
            existing = existing->link;
        }
        if (existing != NULL)
        {
            success = 0;
            break;
        }
        if (!insert_file(node, file))
        {
            success = 0;
            break;
        }
        FileNode *target = node->file_list;
        while (target != NULL && strcmp(target->filename, file) != 0)
        {
            target = target->link;
        }
        if (target == NULL)
        {
            success = 0;
            break;
        }
        target->word_count = (int)count;
        }
    if (ferror(fp))
        success = 0;
    fclose(fp);
    if (!success)
    {
        free_database();
        printf("Invalid or unreadable database backup.\n");
        return 0;
    }
    return 1;
}

