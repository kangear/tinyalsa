#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int, char **);

static void usage()
{
    printf("Repo: https://github.com/tinyalsa/tinyalsa                      \
            \n\nUsage: tinyalsa [function] [arguments]...                   \
            \n\nCurrently defined functions:                                \
            \n\ttinymix/mix, tinycap/cap, tinyplay/play, tinypcminfo/pcminfo\n");
}

static int tinyalsa_main(int argc, char **argv)
{
    // "tinyalsa foo ..." is equivalent to "foo ..."
    if (argc > 1) {
        return main(argc - 1, argv + 1);
    } else {
        printf("Tinyalsa!\n");
        usage();
        return 0;
    }
}

/*
#define TOOL(name) int name##_main(int, char**);
#include "tools.h"
#undef TOOL
*/
extern int tinymix_main(int argc, char **argv);
extern int tinycap_main(int argc, char **argv);
extern int tinyplay_main(int argc, char **argv);
extern int tinypcminfo_main(int argc, char **argv);

static struct
{
    const char *name;
    int (*func)(int, char**);
} tools[] = {
    { "tinyalsa", tinyalsa_main },
    {  "tinymix", tinymix_main  },
    {  "mix", tinymix_main  },
    {  "tinycap", tinycap_main  },
    {  "cap", tinycap_main  },
    {  "tinyplay", tinyplay_main  },
    {  "play", tinyplay_main  },
    {  "tinypcminfo", tinypcminfo_main  },
    {  "pcminfo", tinypcminfo_main  },
/*
#define TOOL(name) { #name, name##_main },
#include "tools.h"
#undef TOOL
*/
    { 0, 0 },
};

int main(int argc, char **argv)
{
    int i;
    char *name = argv[0];

    if((argc > 1) && (argv[1][0] == '@')) {
        name = argv[1] + 1;
        argc--;
        argv++;
    } else {
        char *cmd = strrchr(argv[0], '/');
        if (cmd)
            name = cmd + 1;
    }

    for(i = 0; tools[i].name; i++){
        if(!strcmp(tools[i].name, name)){
            return tools[i].func(argc, argv);
        }
    }

    printf("%s: no such tool\n", argv[0]);
    return -1;
}
