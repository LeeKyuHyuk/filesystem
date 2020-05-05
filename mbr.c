#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "mbr.h"

void print_partition_geom(partition_t part)
{
    fprintf(stdout, " - Starting LBA: %u\n", part.starting_lba);
    fprintf(stdout, " - Ending LBA: %u\n", part.starting_lba + part.number_of_sectors - 1);
    fprintf(stdout, " - Sectors: %u \n", part.number_of_sectors);
}

void print_partition_status(uint8_t status)
{
    fprintf(stdout, " - Status: ");
    if (status == MBR_STATUS_BOOTABLE)
    {
        fprintf(stdout, "Bootable\n");
        return;
    }
    if (status == MBR_STATUS_NON_BOOTABLE)
    {
        fprintf(stdout, "Non-Bootable\n");
        return;
    }
    if (status == MBR_STATUS_BOOTABLE_LBA)
    {
        fprintf(stdout, "Bootable LBA\n");
        return;
    }
    if (status == MBR_STATUS_NON_BOOTABLE_LBA)
    {
        fprintf(stdout, "Non-Bootable LBA\n");
        return;
    }
    fprintf(stdout, "Invalid Partition Status\n");
}

void print_partition_type(uint8_t type)
{
    fprintf(stdout, " - Type: ");
    switch (type)
    {
    case MBR_TYPE_UNUSED:
        fprintf(stdout, "Unused\n");
        break;
    case MBR_TYPE_NTFS:
        fprintf(stdout, "NTFS\n");
        break;
    case MBR_TYPE_FAT32:
        fprintf(stdout, "FAT32\n");
        break;
    case MBR_TYPE_LINUX_SWAP:
        fprintf(stdout, "Linux Swap\n");
        break;
    case MBR_TYPE_LINUX:
        fprintf(stdout, "Linux\n");
        break;
    case MBR_TYPE_EXTENDED_DOS:
        fprintf(stdout, "Extended Doc\n");
        break;
    case MBR_TYPE_EXTENDED_WINDOWS:
        fprintf(stdout, "Extended Windows\n");
        break;
    default:
        fprintf(stdout, "Unknown (0x%02X)\n", type);
        break;
    }
}