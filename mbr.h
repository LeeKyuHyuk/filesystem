#define MBR_STATUS_NON_BOOTABLE     0x00
#define MBR_STATUS_NON_BOOTABLE_LBA 0x01
#define MBR_STATUS_BOOTABLE         0x80
#define MBR_STATUS_BOOTABLE_LBA     0x81

#define MBR_TYPE_UNUSED             0x00
#define MBR_TYPE_EXTENDED_DOS       0x05
#define MBR_TYPE_NTFS               0x07
#define MBR_TYPE_FAT32              0x0C
#define MBR_TYPE_EXTENDED_WINDOWS   0x0F
#define MBR_TYPE_LINUX_SWAP         0x82
#define MBR_TYPE_LINUX              0x83

#define MBR_COPY_PROTECTED          0x5A5A

#define MBR_BOOT_SIGNATURE          0xAA55

#pragma pack(1)

typedef struct
{
    uint8_t status;
    struct
    {
        uint8_t h;
        uint16_t cs;
    } start_chs;
    uint8_t type;
    struct
    {
        uint8_t h;
        uint16_t cs;
    } end_chs;
    uint32_t starting_lba;
    uint32_t number_of_sectors;
} partition_t;

typedef struct
{
    uint8_t bootstrap_code[440];
    uint32_t disk_signiture;
    uint16_t copy_protected;
    partition_t partition_table[4];
    uint16_t boot_signature;
} mbr_t;

#pragma pack()

void print_partition_geom(partition_t part);
void print_partition_status(uint8_t status);
void print_partition_type(uint8_t type);
