#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "mbr.h"

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        fprintf(stderr, "Usage: %s <file name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE *mbr_fd = fopen(argv[1], "r");
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