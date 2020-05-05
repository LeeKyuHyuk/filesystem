#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <readline/readline.h>
#include "main.h"
#include "mbr.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <file name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    rl_attempted_completion_function = command_completion;
    while (1)
    {
        char *buffer = readline("[FAT32] > ");
        /* Ctrl + D 또는 'exit' 명령어를 입력하면 종료 */
        if (buffer == NULL || strcmp(replaceAll(buffer, " ", ""), "exit") == 0)
        {
            free(buffer);
            break;
        }
        else if (strcmp(replaceAll(buffer, " ", ""), "partition") == 0)
        {
            read_partition_list(argv[1]);
        }
        /* 목록에 없는 명령어를 입력했을 경우 */
        else
        {
            printf("Command '%s' not found.\n", buffer);
        }
        free(buffer);
    }

    return 0;
}

int read_partition_list(char *filename)
{
    FILE *mbr_fd = fopen(filename, "r");
    if (mbr_fd == NULL)
    {
        fprintf(stderr, "Error opening mbr file\n");
        return EXIT_FAILURE;
    }

    mbr_t mbr;
    if (fread((void *)&mbr, 1, sizeof(mbr_t), mbr_fd) != sizeof(mbr_t))
    {
        fprintf(stderr, "Error reading mbr\n");
        return EXIT_FAILURE;
    }

    if (mbr.boot_signature != MBR_BOOT_SIGNATURE)
    {
        fprintf(stderr, "No valid bootsector found\n");
        return EXIT_FAILURE;
    }

    for (int i = 0; i < 4; ++i)
    {
        if (mbr.partition_table[i].type == MBR_TYPE_UNUSED)
        {
            continue;
        }
        fprintf(stdout, "Partition %d\n", i);
        print_partition_status(mbr.partition_table[i].status);
        print_partition_type(mbr.partition_table[i].type);
        print_partition_geom(mbr.partition_table[i]);
    }

    return EXIT_SUCCESS;
}

char **command_completion(const char *text, int start, int end)
{
    rl_attempted_completion_over = 1;
    return rl_completion_matches(text, command_generator);
}

char *command_generator(const char *text, int state)
{
    static int list_index, len;
    char *name;

    if (!state)
    {
        list_index = 0;
        len = strlen(text);
    }

    while ((name = command_list[list_index++]))
    {
        if (strncmp(name, text, len) == 0)
        {
            return strdup(name);
        }
    }

    return NULL;
}

char *replaceAll(char *s, const char *olds, const char *news)
{
    char *result, *sr;
    size_t i, count = 0;
    size_t oldlen = strlen(olds);
    if (oldlen < 1)
        return s;
    size_t newlen = strlen(news);

    if (newlen != oldlen)
    {
        for (i = 0; s[i] != '\0';)
        {
            if (memcmp(&s[i], olds, oldlen) == 0)
                count++, i += oldlen;
            else
                i++;
        }
    }
    else
        i = strlen(s);

    result = (char *)malloc(i + 1 + count * (newlen - oldlen));
    if (result == NULL)
        return NULL;

    sr = result;
    while (*s)
    {
        if (memcmp(s, olds, oldlen) == 0)
        {
            memcpy(sr, news, newlen);
            sr += newlen;
            s += oldlen;
        }
        else
            *sr++ = *s++;
    }
    *sr = '\0';

    return result;
}