#ifndef DATABASE_H
#define DATABASE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define WORD_SIZE 100
#define FILE_SIZE 260
typedef struct FileNode
{
    char filename[FILE_SIZE];
    int word_count;
    struct FileNode *link;
} FileNode;
typedef struct WordNode
{
    char word[WORD_SIZE];
    FileNode *file_list;
    struct WordNode *link;
} WordNode;
extern WordNode *index_head;
WordNode *insert_word(const char *word);
int insert_file(WordNode *word_node, const char *filename);
int create_database(const char *filename);
void display_database(void);
void free_database(void);
void search_word(const char *word);
int update_database(const char *filename);
int save_database(const char *filename);
int load_database(const char *filename);
#endif
