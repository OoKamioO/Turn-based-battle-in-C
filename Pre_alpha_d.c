/*Description: Battle Sequence pre-alpha.
Date: 24/01/14
Author: Trieu Nguyen
*/

#include<time.h>
#include<stdio.h>
#include<stdlib.h>

#define OPTIONS 2
#define GAMEON 1
#define GAMEOFF 0
#define HSTATS 10
#define ESTATS 10
#define NO_MON 3

#define HP 0
#define MP 1
#define STR 2
#define MAG 3
#define SPD 4
#define DEF 5
#define AGI 6
#define EVA 7
#define MR 8
#define EXP 9

#define EHP 0
#define EMP 1
#define ESTR 2
#define EMAG 3
#define ESPD 4
#define EDEF 5
#define EAGI 6
#define EEVA 7
#define EMR 8
#define MONEXP 9

#define FIRECOST 10
#define CURECOST 15
#define DAMAGED 99 //99 DAMAGED guarantees a hit
#define EVACAP 60

char* monsternames(int);
int monsterstats(int, int, int);

main()
{
    //*All variables*//
    
    //**Command inputs**
    int i = 0;
    int input_a = 0;
    int battle_input = 0;
    int battle_input_2 = 0;
    int game = GAMEON; //On/Off switch of the game
    int hit = 0; //Chances of being attacked
    int Ehit = 0;
    int lvlreq = 0;
    
    //**Name varibles**//
    char* HERO = "Default";
    char* ENAME = "ENEMY";
    char* monname[NO_MON] = {"Bat", "Orc", "Pixie"};
    
    //**Main Hero variables**//
    int herostats[HSTATS];
    
    herostats[HP] = 0;
    herostats[MP] = 0;
    herostats[STR] = 0;
    herostats[MAG] = 0;
    herostats[SPD] = 0;
    herostats[DEF] = 0;
    herostats[AGI] = 0;
    herostats[EVA] = 0;
    herostats[MR] = 0;
    herostats[EXP] = 0;
    
    int fres = 0; 
    int gold = 0;
    int lvl = 1;
    
    //**Magic Variables**//
    int fdmg = 0;
    int cure_a = 0; 
    
    //**Pointers to magic variables**
    int *hfdmg = &fdmg;
    int *hcure_a = &cure_a;
    
    //**Monster variables**//
    int enemystats[ESTATS];
    
    enemystats[EHP] = 0;
    enemystats[EMP] = 0;
    enemystats[ESTR] = 0;
    enemystats[EMAG] = 0;
    enemystats[ESPD] = 0;
    enemystats[EDEF] = 0;
    enemystats[EAGI] = 0;
    enemystats[EEVA] = 0;
    enemystats[EMR] = 0;
    enemystats[MONEXP] = 0;
     
    int efres = 0;
    int egold = 0;
    
    //**Hero Stats and skills**
    int *hhp = &herostats[HP];
    int *hmp = &herostats[MP];
    int *hstr = &herostats[STR];
    int *hmag = &herostats[MAG];
    int *hspd = &herostats[SPD];
    int *hdef = &herostats[DEF];
    int *hagi = &herostats[AGI];
    int *heva = &herostats[EVA];
    int *hmr = &herostats[MR];
    int *hexp = &herostats[EXP]; //Base exp
    
    int *hlvl = &lvl;
    int *hlvlreq = &lvlreq;
    int *hgold = &gold;
    
    //**Pointers to Enemy Stats**
    int *Ehp = &enemystats[EHP];
    int *Emp = &enemystats[EMP];
    int *Estr = &enemystats[ESTR];
    int *Emag = &enemystats[EMAG];
    int *Espd = &enemystats[ESPD];
    int *Edef = &enemystats[EDEF];
    int *Eagi = &enemystats[EAGI];
    int *Eeva = &enemystats[EEVA];
    int *Emr = &enemystats[EMR];
    int *Eexp = &enemystats[MONEXP]; //Exp gained upon being slained
    
    int *Efres = &efres;
    int *Egold = &egold;
    
    while(game!=GAMEOFF)
    {
        printf("Welcome to the game!\n1) Play game\n2) Status\n3) End game\n\n");
        scanf("%d", &input_a);
        system("cls");
        
        //**Sets the Hero's status
        *hhp = lvl*55; //Health points
        *hmp = lvl*35; //Mana points
        *hstr = lvl*2; //Strength
        *hmag = lvl*3; //Magic
        *hspd = lvl*5; //Speed
        *hagi = lvl*4; //Agility
        *heva = *hagi/2; //Evasion
        
        switch(input_a)
        {
            case 3:
            {
                game = GAMEOFF;
                break;
            }
            
            case 2:
            {
                printf("%s:\n1) Health = %d\n2) Mana = %d\n3) Strenght = %d\n4) Magic = %d\n5) Speed = %d\n6) Defense = %d\n7) Agi = %d\n8) Evasion = %d\n9) Magic Resistance = %d\n10) EXP = %d\n", HERO, *hhp, *hmp, *hstr, *hmag, *hspd, *hdef, *hagi, *heva, *hmr, *hexp);
                printf("\nPlease press enter to go back to the menu.\n");
                
                getchar();
                system("cls");
                
                break;
            }
            
            case 1:
            {
                srand(time(NULL));
                int r = rand()%3; //Chooses the monster to be battled
                
                //**Monster selection**
                ENAME = monname[r];
                
                for(i = 0; i<ESTATS; i++)
                {
                    enemystats[i] = monsterstats(r, i, lvl);
                }
                
                //**Checks to balance the game**
                if(*Edef<1) //Makes sure the value of enemy defense never drops below 1
                {
                    *Edef = 1;
                }
                if(*hdef<1) //Makes sure the value of hero defense never drops below 1
                {
                    *hdef = 1;
                }
                if(*Eeva<EVACAP)//Ensures that 100% dodge is not possible for enemies
                {
                    *Eeva = EVACAP;
                }
                if (*heva<EVACAP) //Ensures that 100% dodge is not possible for heroes
                {
                    *heva = EVACAP;
                }
                
                hit = DAMAGED - *heva; //Percent chance to dodge attacks
                Ehit = DAMAGED - *Eeva; //
                
                //**Sequence of action if player hits first**

                while(*Ehp>0&&*hhp>0)
                {
                    printf("%s\nEnemy Health = %d\nMana = %d\n\n%s\nHealth = %d\nMana = %d", ENAME, *Ehp, *Emp, HERO, *hhp, *hmp);
                    printf("\n\nWould you like to do?:\n1) Attack\n2) Magic\n\n");
                    scanf("%d", &battle_input);
                        
                    int Ehit_ran = rand()%100; //Determines if physical attacks have missed this turn
                    int hit_ran = rand()%100;
                    
                    if(battle_input==1)
                    {
                        //**Player attacks first**
                        if((Ehit_ran<=Ehit)&&(*hspd>=*Espd)) //Player is faster than monster and attack hits
                        {
                            *Ehp = *Ehp - *hstr;
                            
                            printf("\nYou've struck %d damage to %s!\n\n", *hstr, ENAME);
                            getchar();
                            
                            if((*Ehp>0)&&(hit_ran<=hit)) //Enemy is still alive and attack connected
                            {
                                *hhp = *hhp - *Estr;
                                
                                printf("You've been hit for %d hp!", *Estr);
                            }else
                            {
                                printf("%s missed his attack!", ENAME);
                            }
                        }else if((Ehit_ran>Ehit)&&(*hspd>=*Espd)) //The attack missed
                        {
                            printf("\n%s has dodged your attack!\n\n", ENAME);
                            getchar();
                            
                            if((Ehp>0)&&(hit_ran<=hit)) //Enemy is still alive and attack hits
                            {
                                *hhp = *hhp - *Estr;
                                
                                printf("You've been hit for %d hp!!", *Estr);
                            }else
                            {
                                printf("%s missed his attack!", ENAME);
                            }
                        }
                        
                        //**Monster attacks first**
                        if((hit_ran<=hit)&&(*Espd>*hspd)) //Attack connects and monster is faster
                        {
                            *hhp = *hhp - *Estr; //Damage dealth as hit connects
                            
                            printf("\nYou've been hit for %d hp!\n\n", *Estr);
                            getchar();
                            
                            if((*hhp>0)&&(Ehit_ran<=Ehit)) //You're still alive and the attack connects N.B -> Debug this if(), the else if() after works
                            {
                                *Ehp = *Ehp - *hstr;
                                
                                printf("You've struck %d damage to %s!", *hstr, ENAME);
                            }else
                            {
                                printf("%s has dodged your attack!", ENAME);
                            }
                        }else if((hit_ran>hit)&&(*Espd>*hspd)) //The Monster's attack missed
                        {
                            printf("\nYou've dodged %s's attack!\n\n", ENAME);
                            getchar();
                            
                            if((*hhp>0)&&(Ehit_ran<=Ehit)) //You're still alive and the attack connects
                            {
                                *Ehp = *Ehp - *hstr;
                                
                                printf("You've struck for %d hp!", *hstr);
                            }else
                            {
                                printf("%s has dodged your attack!", ENAME);
                            }
                        }
                        
                        getchar();
                        system("cls");
                    }else if(battle_input==2) //Magic selection screen
                    {
                        printf("\nWhat spell would you like to use?\n\n1) Fire (%d MP)\n2) Cure (%d MP)\n\n", FIRECOST, CURECOST);
                        scanf("%d", &battle_input_2);
                        
                        switch(battle_input_2)
                        {
                            case 1:
                            {
                                if(*hmp>=FIRECOST)
                                {
                                    if(*hspd>=*Espd) //Magic hits, Hero is faster and checks to see if there is enough mana
                                    {
                                        *hfdmg = (*hmag)*2;
                                        *hmp = *hmp - FIRECOST;
                                        *Ehp = *Ehp - *hfdmg;
                                        
                                        printf("\nYou did %d damage to the %s!\n", *hfdmg, ENAME);
                                        
                                        if((*Ehp>0)&&(hit_ran<=hit)) //Enemy is still alive and attack connected
                                            {
                                                *hhp = *hhp - *Estr;
                                                
                                                printf("\nYou've been hit for %d hp!", *Estr);
                                            }else
                                            {
                                                printf("\n%s missed his attack!", ENAME);
                                            }
                                    }
                                    
                                    if((hit_ran<=hit)&&(*Espd>*hspd)) //Attack hit and Monster is faster
                                    {
                                        *hhp = *hhp - *Estr;
                                                    
                                        printf("\nYou've been hit for %d hp!\n", *Estr);
                                        
                                        if(*hhp>0)
                                        {
                                            *hfdmg = *hmag*2;
                                            *hmp = *hmp - FIRECOST;
                                            *Ehp = *Ehp - *hfdmg;
                                            
                                            printf("\nYou did %d damage to %s!", *hfdmg, ENAME);
                                        }
                                    }else if((hit_ran>=hit)&&(*Espd>*hspd))
                                    {
                                        printf("\nYou've dodged %s's attack!\n", ENAME);
                                        
                                        if(*hhp>0)
                                        {
                                            *hfdmg = *hmag*2;
                                            *hmp = *hmp - FIRECOST;
                                            *Ehp = *Ehp - *hfdmg;
                                            
                                            printf("\nYou did %d damage to %s!", *hfdmg, ENAME);
                                        }
                                    }
                                }else
                                {
                                    printf("\nNot enough mana.");
                                    getchar();
                                }
                                    
                                getchar();
                                getchar();
                                system("cls");
                                break;
                            }
                            
                            case 2:
                            {
                                if(*hmp>=CURECOST)
                                {
                                    if(*hspd>=*Espd) //Magic hits, Hero is faster and checks to see if there is enough mana
                                    {
                                        *hcure_a = *hmag*3;
                                        *hmp = *hmp - CURECOST;
                                        *hhp = *hhp + *hcure_a;
                                        
                                        printf("\nYou have healed by %d!", *hcure_a);
                                        
                                        if((*Ehp>0)&&(hit_ran<=hit)) //Enemy is still alive and attack connected
                                            {
                                                *hhp = *hhp - *Estr;
                                                
                                                printf("\nYou've been hit for %d hp!", *Estr);
                                            }else
                                            {
                                                printf("\n%s missed his attack!", ENAME);
                                            }
                                    }

                                    if((Ehit_ran<=Ehit)&&(*hspd<=*Espd)) //Attack hit and Monster is faster
                                    {
                                        *hhp = *hhp - *Estr;
                                                    
                                        printf("\nYou've been hit for %d hp!", *Estr);
                                        
                                        if(*hhp>0)
                                        {
                                            *hcure_a = *hmag*3;
                                            *hmp = *hmp - CURECOST;
                                            *hhp = *hhp + *hcure_a;
                                        
                                            printf("\nYou have healed by %d!", *hcure_a);
                                        }
                                    }else if((hit_ran<=hit)&&(*Espd>*hspd))
                                    {
                                        printf("\nYou've dodged %s's attack!", ENAME);
                                        
                                        if(*hhp>0)
                                        {
                                            *hcure_a = *hmag*3;
                                            *hmp = *hmp - CURECOST;
                                            *hhp = *hhp + *hcure_a;
                                        
                                            printf("\nYou have healed by %d!", *hcure_a);
                                        }
                                    }
                                }else
                                {
                                    printf("\nNot enough mana.");
                                }
                                    
                                getchar();
                                getchar();
                                system("cls");
                                break;
                            }
                            
                            default:
                            {
                                printf("\nPlease pick a valid command next time");
                                getchar();
                                getchar();
                                system("cls");
                                break;
                            }
                        }//End inner switch() i.e. the magic menu
                    }else
                    {
                        printf("\nPlease choose a real command next time");
                        getchar();
                        getchar();
                        system("cls");
                    }//End else if
                }//End while() i.e. the player battle phase
                if(*hhp<=0)
                {
                    printf("You have died");
                }else
                {
                    *hexp = *hexp + *Eexp;
                    printf("Congratulations, you have defeated %s!\nYou have gained %d experience!", ENAME, *Eexp);
                }
                    getchar();
                    system("cls");
                    break;
            }//End Outer case 1
                    
            default:
            {
                printf("Please choose a real command next time\n\n");
                printf("Please press enter to go back to the menu.\n");
                getchar();
                system("cls");
                break;
            }
        }//End outer switch
    }//End while()
}//End main()

//**Function to determine monster stats**
int monsterstats(int r, int i, int lvl)
{
    int enemystats[ESTATS];
    
    switch(r) //Monster statuses
    {
        case 0:
        {
            //ENAME = "Bat";
            enemystats[EHP] = lvl*3;
            enemystats[EMP] = lvl*9;
            enemystats[ESTR] = lvl*2;
            enemystats[EMAG] = lvl*3;
            enemystats[ESPD] = lvl*3;
            enemystats[EDEF] = lvl*0;
            enemystats[EAGI] = lvl*4;
            enemystats[EEVA] = lvl*3;
            enemystats[EMR] = lvl*0;
            enemystats[MONEXP] = lvl*3;
            break;
        }
        
        case 1:
        {
            //ENAME = "Orc";
            enemystats[EHP] = lvl*6;
            enemystats[EMP] = lvl*0;
            enemystats[ESTR] = lvl*3;
            enemystats[EMAG] = lvl*0;
            enemystats[ESPD] = lvl*5;
            enemystats[EDEF] = lvl*0;
            enemystats[EAGI] = lvl*4;
            enemystats[EEVA] = lvl*3;
            enemystats[EMR] = lvl*0;
            enemystats[MONEXP] = lvl*8;
            break;
        }
        
        case 2:
        {
            //ENAME = "Pixie";
            enemystats[EHP] = lvl*57;
            enemystats[EMP] = lvl*20;
            enemystats[ESTR] = lvl*5;
            enemystats[EMAG] = lvl*9;
            enemystats[ESPD] = lvl*8;
            enemystats[EDEF] = lvl*0;
            enemystats[EAGI] = lvl*5;
            enemystats[EEVA] = lvl*5;
            enemystats[EMR] = lvl*0;
            enemystats[MONEXP] = lvl*16;
            break;
        }
    }
    return enemystats[i];
}