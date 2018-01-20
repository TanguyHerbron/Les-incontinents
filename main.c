#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    int isFar;
    int dist;
    int amount;
} foodSee;

typedef struct
{
    int id;
    int isFar;
    int dist;
    int isFriend;
} nestSee;

typedef struct
{
    int id;
    int isFar;
    int dist;
    int isFriend;
    int stamina;
} antSee;

typedef struct
{
    int id;
    int isFar;
    int dist;
    int type;
    int persistance;
} pheromone;

typedef struct
{
    int type;
    int nb;
} antNest;

typedef struct
{
    int type;
    int memory[2];
    int isAttacked;
    int stamina;
    int stock;
    pheromone psee[500];
    int nbPheromone;
    antSee antHey[500];
    int nbAntSee;
    nestSee nestHey[500];
    int nbNestSee;
    foodSee foodHey[500];
    int nbFoodSee;
} ant;

typedef struct
{
    int id;
    int memory[2];
} antIn;

typedef struct
{
    int stock;
    int memory[20];
    antNest alist[500];
    int nbAntNest;
    antIn antGoBack[500];
    int nbAntIn;
} nest;

int main()
{
    char val[100];
    int i;
    int isOver = 0;
    ant newAnt;
    nest newNest;

    while(1)
    {
        fflush(stdout);
        isOver = 0;
        scanf("%s", val);

        if(strcmp(val, "BEGIN") == 0)
        {
            scanf("%s", val);
            if(strcmp(val, "ANT") == 0)
            {
                newAnt.nbPheromone = 0;
                newAnt.nbAntSee = 0;
                newAnt.nbNestSee = 0;
                newAnt.nbFoodSee = 0;
                /*while(!isOver)
                {
                    scanf("%s", val);

                    if(strcmp(val, "TYPE") == 0)
                    {
                        scanf("%d", &newAnt.type);
                    }

                    if(strcmp(val, "MEMORY") == 0)
                    {
                        for(i = 0; i < 2; i++)
                        {
                            scanf("%d", &newAnt.memory[i]);
                        }
                    }

                    if(strcmp(val, "ATTACKED") == 0)
                    {
                        newAnt.isAttacked = 1;
                    }

                    if(strcmp(val, "STAMINA") == 0)
                    {
                        scanf("%d", &newAnt.stamina);
                    }

                    if(strcmp(val, "STOCK") == 0)
                    {
                        scanf("%d", &newAnt.stock);
                    }

                    if(strcmp(val, "SEE_PHEROMONE") == 0)
                    {
                        scanf("%d", &newAnt.psee[newAnt.nbPheromone].id);
                        scanf("%s", val);

                        if(strcmp(val, "FAR") == 0)
                        {
                            newAnt.psee[newAnt.nbPheromone].isFar = 1;
                        }
                        else
                        {
                            newAnt.psee[newAnt.nbPheromone].isFar = 0;
                        }

                        scanf("%d", &newAnt.psee[newAnt.nbPheromone].type);
                        scanf("%d", &newAnt.psee[newAnt.nbPheromone].persistance);
                        newAnt.nbPheromone++;
                    }

                    if(strcmp(val, "SEE_ANT") == 0)
                    {
                        scanf("%d", &newAnt.antHey[newAnt.nbAntSee].id);
                        scanf("%s", val);

                        if(strcmp(val, "FAR") == 0)
                        {
                            newAnt.antHey[newAnt.nbAntSee].isFar = 1;
                        }
                        else
                        {
                            newAnt.antHey[newAnt.nbAntSee].isFar = 0;
                        }

                        scanf("%d", &newAnt.antHey[newAnt.nbAntSee].dist);
                        scanf("%s", val);

                        if(strcmp(val, "FRIEND") == 0)
                        {
                            newAnt.antHey[newAnt.nbAntSee].isFriend = 1;
                        }
                        else
                        {
                            newAnt.antHey[newAnt.nbAntSee].isFriend = 0;
                        }

                        scanf("%d", &newAnt.antHey[newAnt.nbAntSee].stamina);
                    }

                    if(strcmp(val, "SEE_NEST") == 0)
                    {
                        scanf("%d", &newAnt.nestHey[newAnt.nbNestSee].id);
                        scanf("%s", val);

                        if(strcmp(val, "FAR") == 0)
                        {
                            newAnt.nestHey[newAnt.nbNestSee].isFar = 1;
                        }
                        else
                        {
                            newAnt.nestHey[newAnt.nbNestSee].isFar = 0;
                        }

                        scanf("%d", &newAnt.nestHey[newAnt.nbNestSee].dist);
                        scanf("%d", val);

                        if(strcmp(val, "FRIEND") == 0)
                        {
                            newAnt.nestHey[newAnt.nbNestSee].isFriend = 1;
                        }
                        else
                        {
                            newAnt.nestHey[newAnt.nbNestSee].isFriend = 0;
                        }

                        newAnt.nbNestSee++;
                    }

                    if(strcmp(val, "SEE_FOOD") == 0)
                    {
                        scanf("%d", &newAnt.foodHey[newAnt.nbFoodSee].id);
                        scanf("%s", val);

                        if(strcmp(val, "FAR") == 0)
                        {
                            newAnt.foodHey[newAnt.nbFoodSee].isFar = 1;
                        }
                        else
                        {
                            newAnt.foodHey[newAnt.nbFoodSee].isFar = 0;
                        }

                        scanf("%d", &newAnt.foodHey[newAnt.nbFoodSee].dist);
                        scanf("%d", &newAnt.foodHey[newAnt.nbFoodSee].amount);

                        newAnt.nbFoodSee++;
                    }

                    if(strcmp(val, "END") == 0)
                    {
                        isOver = 1;
                    }
                }

                printf("EXPLORE\n");

                //SEND ANT

                if(newAnt.stamina > 0)
                {
                    printf("EXPLORE\n");
                }

                if(newAnt.stamina >= 150)
                {
                    if(newAnt.stock >= 500)
                    {
                        if(newAnt.nbNestSee > 0)
                        {
                            int closest = newAnt.nestHey[0].dist;
                            int bestChoice = 0;
                            int isGone = 0;
                            int compteur = 0;

                            while(!isGone && compteur <= newAnt.nbNestSee)
                            {
                                if(!newAnt.nestHey[compteur].isFar)
                                {
                                    printf("NEST %d\n", newAnt.nestHey[compteur].id);
                                    isGone = 1;
                                }
                                else
                                {
                                    if(newAnt.nestHey[compteur].dist < closest)
                                    {
                                        closest = newAnt.nestHey[compteur].dist;
                                        bestChoice = compteur;
                                    }
                                }
                                compteur++;
                            }

                            if(!isGone)
                            {
                                printf("MOVE_TO %d\n", newAnt.nestHey[bestChoice].id);
                            }
                        }
                        else
                        {
                            printf("EXPLORE\n");
                        }
                    }
                    else
                    {
                        if(newAnt.nbFoodSee > 0)
                        {
                            int isGone = 0;
                            int compteur = 0;

                            while(!isGone && compteur < newAnt.nbFoodSee)
                            {
                                if(!newAnt.foodHey[compteur].isFar)
                                {
                                    if(newAnt.stamina < 10000)
                                    {
                                        if(10000-newAnt.stamina <= newAnt.foodHey[compteur].amount * 10)
                                        {
                                            printf("EAT %d", (10000-newAnt.stamina)/10);
                                        }
                                        else
                                        {
                                            printf("EAT %d", newAnt.stock);
                                        }
                                        isGone = 1;
                                    }
                                    else
                                    {
                                        if(newAnt.stock < 1000)
                                        {
                                            if(newAnt.foodHey[compteur].amount < 10000 - newAnt.stock)
                                            {
                                                printf("COLLECT %d %d\n", newAnt.foodHey[compteur].id, newAnt.foodHey[compteur].amount);
                                            }
                                            else
                                            {
                                                printf("COLLECT %d %d\n", newAnt.foodHey[compteur].id, 10000 - newAnt.stock);
                                            }

                                            isGone = 1;
                                        }
                                    }
                                }
                                compteur++;
                            }

                            if(!isGone)
                            {

                            }
                        }
                        else
                        {

                        }
                    }
                }
                else
                {
                    if(10000-newAnt.stamina <= newAnt.stock * 10)
                    {
                        printf("EAT %d", (10000-newAnt.stamina)/10);
                    }
                    else
                    {
                        printf("EAT %d", newAnt.stock);
                    }
                }

                printf("END\n");
            */}
            else
            {
                if(strcmp(val, "NEST") == 0)
                {
                    newNest.nbAntNest = 0;
                    newNest.nbAntIn = 0;
                    while(!isOver)
                    {
                        scanf("%s", val);

                        if(strcmp(val, "STOCK") == 0)
                        {
                            scanf("%d", &newNest.stock);
                        }

                        if(strcmp(val, "MEMORY") == 0)
                        {
                            for(i = 0; i < 20; i++)
                            {
                                scanf("%d", &newNest.memory[i]);
                            }
                        }

                        if(strcmp(val, "ANT_COUNT") == 0)
                        {
                            scanf("%d", &newNest.alist[newNest.nbAntNest].type);
                            scanf("%d", &newNest.alist[newNest.nbAntNest].nb);
                            newNest.nbAntNest++;
                        }

                        if(strcmp(val, "ANT_IN") == 0)
                        {
                            scanf("%d", &newNest.antGoBack[newNest.nbAntIn].id);
                            scanf("%d", &newNest.antGoBack[newNest.nbAntIn].memory[0]);
                            scanf("%d", &newNest.antGoBack[newNest.nbAntIn].memory[1]);
                        }

                        if(strcmp(val, "END") == 0)
                        {
                            isOver = 1;
                        }
                    }

                    //SEND NEST

                    /*if(newNest.memory[0] == 0)
                    {
                        printf("ANT_NEW 0\n");
                        printf("SET_MEMORY 1 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n");
                    }*/



                    if(newNest.nbAntNest > 0)
                    {
                        printf("ANT_OUT %d %d 0 0\n", newNest.alist[newNest.nbAntNest-1].type, 10);
                    }
                    else
                    {
                        if(newNest.stock > 10)
                        {
                            printf("ANT_NEW 0\n");
                            printf("SET_MEMORY %d 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n", newNest.memory[0]+1);
                        }
                    }

                    printf("END\n");

                }
            }
        }

        fflush(stdout);
    }

    return 0;
}
