#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{
    char val[100];
    int i;
    int nbAntsTotal = 0;
    int nbAntsIn = 0;
    int nbAntsOut = 0;

    while(1)
    {
        fflush(stdout);
        scanf("%s", val);

        if(strcmp(val, "BEGIN") == 0)
        {
            scanf("%s", val);
            if(strcmp(val, "ANT") == 0)
            {
                printf("EXPLORE\n");
                printf("END\n");
            }
        }

        if(strstr(val, "ANT_COUNT") != NULL)
        {
            scanf("%d", &nbAntsIn);
            scanf("%d", &nbAntsIn);
        }

        if(strstr(val, "MEMORY") != NULL)
        {
            for(i = 0; i < 18; i++)
            {
                scanf("%d", &nbAntsOut);
            }
            scanf("%d", &nbAntsOut);
            scanf("%d", &nbAntsTotal);
        }

        if(strcmp(val, "END") == 0)
        {
            if(nbAntsTotal == 0)
            {
                nbAntsTotal++;
                printf("ANT_NEW 0\n");
                printf("SET_MEMORY 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 %d %d\n", nbAntsOut, nbAntsTotal);
            }

            if(nbAntsIn > 0)
            {
                nbAntsOut++;
                nbAntsIn--;
                printf("SET_MEMORY 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 %d %d\n", nbAntsOut, nbAntsTotal);
                printf("ANT_OUT 0 100 0 0\n");
            }

            printf("END\n");
            fflush(stdout);
        }
    }
    return 0;
}
