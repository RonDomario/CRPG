#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "names.h"

#define MAX_WORDS 10000
#define MAX_WORD_LEN 64

static char adjectives[MAX_WORDS][MAX_WORD_LEN];
static char nouns[MAX_WORDS][MAX_WORD_LEN];
static int adj_count = 0;
static int noun_count = 0;

static int load_words(const char *filename, char words[][MAX_WORD_LEN], int max)
{
    FILE *f = fopen(filename, "r");
    if (!f)
    {
        perror(filename);
        return -1;
    }

    int count = 0;
    while (count < max && fgets(words[count], MAX_WORD_LEN, f))
    {
        size_t len = strlen(words[count]);
        if (len > 0 && words[count][len - 1] == '\n')
        {
            words[count][len - 1] = '\0';
        }
        count++;
    }

    fclose(f);
    return count;
}

void names_init(const char *adj_file, const char *noun_file)
{
    adj_count = load_words(adj_file, adjectives, MAX_WORDS);
    noun_count = load_words(noun_file, nouns, MAX_WORDS);
    if (adj_count <= 0 || noun_count <= 0)
    {
        fprintf(stderr, "failed to load word lists\n");
        exit(1);
    }
}

void generate_name(char *buffer, int size)
{
    char adj[64];
    char noun[64];

    snprintf(adj, sizeof(adj), "%s", adjectives[rand() % adj_count]);
    snprintf(noun, sizeof(noun), "%s", nouns[rand() % noun_count]);

    adj[0] = toupper(adj[0]);
    noun[0] = toupper(noun[0]);

    snprintf(buffer, size, "%s%s%02d", adj, noun, rand() % 100);
}