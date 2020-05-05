char *command_list[] = {
    "partition",
    "help",
    "exit",
    NULL
};

int read_partition_list(char *filename);
char **command_completion(const char *, int, int);
char *command_generator(const char *, int);
char *replaceAll(char *s, const char *olds, const char *news);