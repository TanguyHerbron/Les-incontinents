#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE_BUFF 1024
#define SIZE_COMMANDE 255
#define NB_TYPE_FOURMIS 255
#define SIZE_MEMORY_NEST 20
#define SIZE_MEMORY_ANT 2
#define MAX_ANT_BACK_TO_NEST 100
#define MAX_PHERO_SEE 100
#define MAX_ANT_SEE 100
#define MAX_NEST_SEE 5
#define MAX_FOOD_SEE 50

int nbAntBack = 0;

int nbPhero = 0, nbAnt = 0, nbNest = 0, nbFood = 0;


typedef enum
{
    STOCK_NEST = 0,
    MEMORY_NEST,
    ANT_COUNT,
    ANT_IN,
    END_NEST
} CmdNestOut;

typedef enum
{
    TYPE = 0,
    MEMORY_ANT,
    ATTACKED,
    STAMINA,
    STOCK_ANT,
    SEE_PHEROMONE,
    SEE_ANT,
    SEE_NEST,
    SEE_FOOD,
    END_ANT
} CmdAntOut;

typedef struct
{
    int id; //id de l'objet
    unsigned char zone; //0 near 1 far
    unsigned char dist; // entre 0 et 100
    unsigned char type; //type de la fourmis qui l'a déposée
    unsigned char persi; // entre 0 et 100
} Pheromone;

typedef struct
{
    int id; //id de l'objet
    unsigned char zone; //0 near 1 far
    unsigned char dist; // entre 0 et 100
    unsigned char isFriend; //1 friend, 0 not friend
    int stamina; // entre 0 et 10000
} Ant;

typedef struct
{
    int id; //id de l'objet
    unsigned char zone; //0 near 1 far
    unsigned char dist; // entre 0 et 100
    unsigned char isFriend; //1 friend, 0 not friend
} Nest;

typedef struct
{
    int id; //id de l'objet
    unsigned char zone; //0 near 1 far
    unsigned char dist; // entre 0 et 100
    long amount; //max 1000000
} Food;

typedef struct
{
    unsigned char type; //type de la fourmis
    unsigned char memory[SIZE_MEMORY_ANT]; //Mémoire
} AntIn;

typedef struct
{
    long stock; //Stock de la fourmilière
    unsigned char memory[SIZE_MEMORY_NEST]; //Mémoire
    long nbFourmis[NB_TYPE_FOURMIS]; //tableau des type de fourmis(contient le nombre)
    AntIn tabAntIn[MAX_ANT_BACK_TO_NEST]; //tableau des fourmis de retour dans le nest

} NEST_INFO;

typedef struct
{
    unsigned char type; //type de la fourmis
    unsigned char memory[SIZE_MEMORY_ANT]; //Mémoire
    unsigned char attacked; // 0 non atackée 1 attackée
    unsigned int stamina; //Max 10000
    unsigned int stock; //Max 1000
    Pheromone tabPheromone[MAX_PHERO_SEE];
    Ant tabAnt[MAX_ANT_SEE];
    Nest tabNest[MAX_NEST_SEE];
    Food tabFood[MAX_FOOD_SEE];

} ANT_INFO;

CmdAntOut CmdAntCheck(char strCmd[SIZE_BUFF])
{
    CmdAntOut cmd;

    if(strstr(strCmd, "TYPE") != NULL)
    {
        cmd = TYPE;
    }
    else
    {
        if(strstr(strCmd, "MEMORY") != NULL)
        {
            cmd = MEMORY_ANT;
        }
        else
        {
            if(strstr(strCmd, "ATTACKED") != NULL)
            {
                cmd = ATTACKED;
            }
            else
            {
                if(strstr(strCmd, "STAMINA") != NULL)
                {
                    cmd = STAMINA;
                }
                else
                {
                    if(strstr(strCmd, "STOCK") != NULL)
                    {
                        cmd = STOCK_ANT;
                    }
                    else
                    {
                        if(strstr(strCmd, "SEE_PHEROMONE") != NULL)
                        {
                            cmd = SEE_PHEROMONE;
                        }
                        else
                        {
                            if(strstr(strCmd, "SEE_ANT") != NULL)
                            {
                                cmd = SEE_ANT;
                            }
                            else
                            {
                                if(strstr(strCmd, "SEE_NEST") != NULL)
                                {
                                    cmd = SEE_NEST;
                                }
                                else
                                {
                                    if(strstr(strCmd, "SEE_FOOD") != NULL)
                                    {
                                        cmd = SEE_FOOD;
                                    }
                                    else
                                    {
                                        if(strstr(strCmd, "END") != NULL)
                                        {
                                            cmd = END_ANT;
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    return cmd;
}

CmdNestOut CmdNestCheck(char strCmd[SIZE_BUFF])
{
    CmdNestOut cmd;

    if(strstr(strCmd, "STOCK") != NULL)
    {
        cmd = STOCK_NEST;
    }
    else
    {
        if(strstr(strCmd, "MEMORY") != NULL)
        {
            cmd = MEMORY_NEST;
        }
        else
        {
            if(strstr(strCmd, "ANT_COUNT") != NULL)
            {
                cmd = ANT_COUNT;
            }
            else
            {
                if(strstr(strCmd, "ANT_IN") != NULL)
                {
                    cmd = ANT_IN;
                }
                else
                {
                    if(strstr(strCmd, "END") != NULL)
                    {
                        cmd = END_NEST;
                    }
                }
            }
        }
    }
    return cmd;
}

NEST_INFO ObtenirInfoNest()
{
    NEST_INFO info;
    AntIn tempAntIn; //stockage temporaire du la fourmis entrente
    int i; //compteur
    int typeTemp; //stockage temporaire du type
    int fin = 0; //boolean de fin
    char buffer[SIZE_BUFF]; //buffer de la commande
    while(fin != 1)
    {
        scanf("%s", buffer);
        switch(CmdNestCheck(buffer))
        {
        case STOCK_NEST:
            scanf("%d", &info.stock);
            break;
        case MEMORY_NEST:
            for(i = 0 ; i < SIZE_MEMORY_NEST ; i++)
            {
                scanf("%d ", &info.memory[i]);
            }
            break;
        case ANT_COUNT:
            scanf("%d ", &typeTemp);
            scanf("%d", &info.nbFourmis[typeTemp]);
            break;
        case ANT_IN:
            scanf("%d ", &info.tabAntIn[nbAntBack].type);
            scanf("%d ", &info.tabAntIn[nbAntBack].memory[0]);
            scanf("%d", &info.tabAntIn[nbAntBack].memory[1]);
            nbAntBack ++;
            break;
        case END_NEST:
            fin = 1;
            break;
        }
    }
    return info;
}

ANT_INFO ObtenirInfoANT()
{
    ANT_INFO info;
    int fin = 0; //boolean de fin
    char buffer[SIZE_BUFF]; //buffer de la commande
    while(fin != 1)
    {
        scanf("%s", buffer);
        switch(CmdAntCheck(buffer))
        {
        case TYPE:
            scanf("%d", &info.type);
            break;
        case MEMORY_ANT:
            scanf("%d %d", &info.memory[0], &info.memory[1]);
            break;
        case ATTACKED:
            info.attacked = 1;
            break;
        case STAMINA:
            scanf("%d", &info.stamina);
            break;
        case STOCK_ANT:
            scanf("%d", &info.stock);
            break;
        case SEE_PHEROMONE:
            scanf("%d", &info.tabPheromone[nbPhero].id);
            scanf("%s ", buffer);
            if(strcmp(buffer, "FAR") == 0)
            {
                info.tabPheromone[nbPhero].zone = 1;
            }
            scanf("%d %d %d", &info.tabPheromone[nbPhero].dist, &info.tabPheromone[nbPhero].type, &info.tabPheromone[nbPhero].persi);
            nbPhero ++;
            break;
        case SEE_ANT:
            scanf("%d", &info.tabAnt[nbAnt].id);
            scanf("%s ", buffer);
            if(strcmp(buffer, "FAR") == 0)
            {
                info.tabAnt[nbAnt].zone = 1;
            }
            scanf("%d ", &info.tabAnt[nbAnt].dist);
            scanf("%s ", buffer);
            if(strcmp(buffer, "FRIEND") == 0)
            {
                info.tabAnt[nbAnt].isFriend = 1;
            }
            scanf("%d", &info.tabAnt[nbAnt].stamina);
            nbAnt ++;
            break;
        case SEE_NEST:
            scanf("%d", &info.tabNest[nbNest].id);
            scanf("%s ", buffer);
            if(strcmp(buffer, "FAR") == 0)
            {
                info.tabNest[nbNest].zone = 1;
            }
            scanf("%d ", &info.tabNest[nbNest].dist);
            scanf("%s ", buffer);
            if(strcmp(buffer, "FRIEND") == 0)
            {
                info.tabNest[nbNest].isFriend = 1;
            }
            nbNest ++;
            break;
        case SEE_FOOD:
            scanf("%d", &info.tabFood[nbFood].id);
            scanf("%s", buffer);
            if(strcmp(buffer, "FAR") == 0)
            {
                info.tabFood[nbFood].zone = 1;
            }
            scanf("%d %d", &info.tabFood[nbFood].dist, &info.tabFood[nbFood].amount);
            nbFood ++;
            break;
        case END_ANT:
            fin = 1;
            break;
        }
    }
    return info;
}

void NestSortirFourmis()
{
    printf("ANT_OUT 0 0 0 0\n");
    printf("END\n");
}

void NestCreerFourmis()
{
    printf("ANT_NEW 0\n");
    printf("END\n");
}

void AntExplore()
{
    printf("EXPLORE\n");
    printf("END\n");
}

void AntManger(int quantite)
{
    printf("EAT %d\n", quantite);
    printf("END\n");
}

void AntGoInNest(int id)
{
    printf("NEST %d\n", id);
    printf("END\n");
}

void AntMoveTo(int id)
{
    printf("MOVE_TO %d\n", id);
    printf("END\n");
}

void AntPutPheromone(int type)
{
    printf("PUT_PHEROMONE %d\n", type);
    printf("END\n");
}

void AntMemory(int mem0, int mem1)
{
    printf("SET_MEMORY %d %d\n", mem0, mem1);
}

void AntCollect(int id, int quantite)
{
    printf("COLLECT %d %d\n", id, quantite);
    printf("END\n");
}

int main()
{
    char buffer[SIZE_BUFF];
    int cptNest = 0;
    int idClosestPhero = -1;
    int cptPhero = 0;
    while(1)
    {
        scanf(" %s", &buffer);
        //Programme de la fourmilière
        if(strcmp(buffer, "NEST") == 0)
        {
            NEST_INFO infoNest;
            infoNest = ObtenirInfoNest();
            infoNest.memory[0] += nbAntBack;
            printf("SET_MEMORY %d 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n", infoNest.memory[0]);

            //Phase d'action
            if(infoNest.memory[0] > 1 && infoNest.stock > 1)
            {
                printf("SET_MEMORY %d 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n", infoNest.memory[0] - 1);
                NestSortirFourmis();
            }
            else
            {
                if(infoNest.stock >= 6)
                {
                    printf("SET_MEMORY %d 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n", infoNest.memory[0] + 1);
                    NestCreerFourmis();
                }
            }
            fflush(stdout);
        }
        if(strcmp(buffer, "ANT") == 0)
        {
            ANT_INFO infoAnt;
            infoAnt = ObtenirInfoANT();

            switch(infoAnt.type)
            {
            case 0:
                if(infoAnt.stamina < 150 && infoAnt.stock >= 2)
                {
                    AntManger(2);
                }
                else
                {
                    if(infoAnt.stock >= 500)
                    {
                        if(nbNest > 0)
                        {
                            while(cptNest < nbNest)
                            {
                                if(infoAnt.tabNest[cptNest].isFriend == 1)
                                {
                                    if(infoAnt.tabNest[cptNest].zone == 0)
                                    {
                                        AntGoInNest(infoAnt.tabNest[cptNest].id);
                                    }
                                    else
                                    {
                                        AntMoveTo(infoAnt.tabNest[cptNest].id);
                                    }
                                }
                                cptNest ++;
                            }
                        }
                        else
                        {
                            if(nbPhero > 0)
                            {
                                for(cptPhero = 0 ; cptPhero < nbPhero ; cptPhero ++)
                                {
                                    if(infoAnt.tabPheromone[cptPhero].type < infoAnt.memory[1])
                                    {
                                        AntMemory(infoAnt.memory[1], infoAnt.tabPheromone[cptPhero].type);
                                        idClosestPhero = infoAnt.tabPheromone[cptPhero].id;
                                    }
                                }
                                AntMoveTo(idClosestPhero);
                            }
                            else
                            {
                                AntExplore();
                            }
                        }
                    }
                    else
                    {
                        if(nbFood == 0)
                        {
                            infoAnt.memory[0] ++;
                            AntMemory(infoAnt.memory[0], infoAnt.memory[1]);

                            if(infoAnt.memory[0] > 9)
                            {
                                infoAnt.memory[0] = 0;
                                infoAnt.memory[1] ++;
                                AntMemory(infoAnt.memory[0], infoAnt.memory[1]);
                                AntPutPheromone(infoAnt.memory[1]);
                            }
                            else
                            {
                                AntExplore();
                            }
                        }
                        else
                        {
                            if(infoAnt.tabFood[0].zone == 1)
                            {
                                AntMoveTo(infoAnt.tabFood[0].id);
                            }
                            else
                            {
                                AntCollect(infoAnt.tabFood[0].id, 1000 - infoAnt.stock);
                            }
                        }
                    }
                }
                fflush(stdout);
                break;
            case 1:
                break;
            }
        }
    }
    return 0;
}
