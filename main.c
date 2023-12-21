//
//  main.c
//  SMMarble
//
//  Created by Juyeop Kim on 2023/11/05.
//

#include <time.h>
#include <string.h>
#include "smm_object.h"
#include "smm_database.h"
#include "smm_common.h"

#define BOARDFILEPATH "marbleBoardConfig.txt"
#define FOODFILEPATH "marbleFoodConfig.txt"
#define FESTFILEPATH "marbleFestivalConfig.txt"


//board configuration parameters
static int board_nr;
static int food_nr;
static int festival_nr;

static int player_nr;

typedef struct player{
	int energy;
	int position;
	char name[MAX_CHARNAME];
	int accumCredit;
	int flag_graduate;
}player_t;

static player_t *cur_player;

static int player_energy[MAX_PLAYER];
static int player_position[MAX_PLAYER];
static int player_name[MAX_PLAYER][MAX_CHARNAME];


//function prototypes

int isGraduated(void); //check if any player is graduated
void generatePlayers(int n, int initEnergy); //generate a new player
void printGrades(int player); //print grade history of the player
void goForward(int player, int step); //make player go "step" steps on the board (check if player is graduated)
void printPlayerStatus(void); //print all player status at the beginning of each turn
float calcAverageGrade(int player); //calculate average grade of the player
smmGrade_e takeLecture(int player, char *lectureName, int credit); //take the lecture (insert a grade of the player)
void* findGrade(int player, char *lectureName); //find the grade from the player's grade history
void printGrades(int player); //print all the grade history of the player


void printGrades(int player){
	int i;
	void *gradePtr;
	for (i=0; i<smmdb_len(LISTNO_OFFSET_GRADE + player);i++){
		gradePtr = smmdb_getData(LISTNO_OFFSET_GRADE + player, i);
		printf("%s : %i\n", smmObj_getNodeName(gradePtr), smmObj_getNodeGrade(gradePtr));
	}
}

void printPlayerStatus(void){
	int i;
	
	for (i=0; i<player_nr;i++){
		printf("%s : credit %i, energy %i, position %i\n", cur_player[i].name,cur_player[i].accumCredit,cur_player[i].energy,cur_player[i].position);
	}
}

void generatePlayers(int n, int initEnergy){
	int i;
	//ntime loop
	for (i=0;i<n;i++){
		//input name
		printf("please input player %i's name:",i);//inform
		scanf("%s",cur_player[i].name);
		fflush(stdin);
		
		//set position
		cur_player[i].position = 0;
		
		//set energy
		cur_player[i].energy = initEnergy;
		cur_player[i].accumCredit = 0;
		cur_player[i].flag_graduate = 0;
	}
}

int rolldie(int player) //roll the dice
{
    char c;
    printf(" Press any key to roll a die (press g to see grade): ");
    c = getchar();
    fflush(stdin);
    
    if (c == 'g')
        printGrades(player);
    
	int die_result = rand()%6 +1 ;
	printf("result is %i\n/", die_result);
	    
    return (rand()%MAX_DIE + 1);
}


//action code when a player stays at a node
void actionNode(int player)
{
	void *boardPtr = smmdb_getData(LISTNO_NODE, cur_player[player].position);
	int type = smmObj_getNodeType( boardPtr );
	char *name = smmObj_getNodeName(boardPtr);
	void *gradePtr;
	
    switch(type)
    {
        //case lecture:
        case SMMNODE_TYPE_LECTURE:
        {
        	printf("Are you going to take the lecture %s? (y/n)",name);
        	char take_lec;
        	scanf("%c",&take_lec);
        	
        	if(take_lec=='y'){ //join the lecture
        		if (cur_player[player].energy >= smmObj_getNodeEnergy(boardPtr)){//enough energy to take lecture
        			int grade = (smmObjGrade_e)(rand() % smmObjGrade_max); //generate grade randomly
        			int gradePtr = smmObj_genObject(name, smmObjType_grade, 0, smmObj_getNodeCredit(boardPtr) ,0, grade);
					//save the grade					        	
		        	cur_player[player].accumCredit += smmObj_getNodeCredit(boardPtr);
		        	cur_player[player].energy -= smmObj_getNodeEnergy(boardPtr);
				}
				else{//not enough energy to take lecture
					printf("not enough energy to take lectur %s",name);
				}
			}
			else{ // not join the lecture
				printf("you dropped the lecture%s",name);
			}
			break;
		}//lecture end
			
        case SMMNODE_TYPE_RESTAURANT:{
			break;
		}
		
        case SMMNODE_TYPE_LABORATORY:{
			break;
		}
		
        case SMMNODE_TYPE_HOME:{
			break;
		}
		
        case SMMNODE_TYPE_EXPERIMENT:{
			break;
		}
		
        case SMMNODE_TYPE_FOODCHANCE:{
			break;
		}
        	
        case SMMNODE_TYPE_FESTIVAL:{
			break;
		}
				

        
        default:
            break;
    }
}

void goForward(int player, int step){
	cur_player[player].position += step;
}

int main(int argc, const char * argv[]) {
    
    FILE* fp;
    char name[MAX_CHARNAME];
    int type;
    int credit;
    int energy;
    int i;
    int initEnergy;
    int turn=0;
    
    board_nr = 0;
    food_nr = 0;
    festival_nr = 0;
    
    srand(time(NULL));
    
    
    //1. import parameters ---------------------------------------------------------------------------------
    //1-1. boardConfig 
    if ((fp = fopen(BOARDFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", BOARDFILEPATH);
        getchar();
        return -1;
    }
    
    printf("Reading board component......\n");
    while ( fscanf(fp, "%s %i %i %i",name, &type, &credit, &energy) == 4) //read a node parameter set
    {
        //store the parameter set
        smmObj_genNode(name, type, credit, energy);
        //(char* name, snnObjType_e objType, int type, int credit, int energy msnnObjGrade_e grade)
        board_nr++;
    }
    fclose(fp);
    printf("Total number of board nodes : %i\n", board_nr);
    
    for (int i = 0; i<board_nr; i++){
    	printf("node %i : %s, %i(%s), credit %i, energy %i\n", i, smmObj_getNodeName(i),smmObj_getNodeType(i), smmObj_getTypeName(smmObj_getNodeType(i)),smmObj_getCredit(i),smmObj_getEnergy(i));
	}
  
	printf("(%s)", smmObj_getTypeName(SMMNODE_TYPE_LECTURE));
    
    //2. food card config 
    if ((fp = fopen(FOODFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FOODFILEPATH);
        return -1;
    }
    
    printf("\n\nReading food card component......\n");
    while (fsancf(fp, "%s %i",name, &energy)==2) //read a food parameter set
    {
        //store the parameter set
    }
    fclose(fp);
    printf("Total number of food cards : %i\n", food_nr);
    
    
    
    //3. festival card config 
    if ((fp = fopen(FESTFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FESTFILEPATH);
        return -1;
    }
    
    printf("\n\nReading festival card component......\n");
    while (fscanf(fp, "%s", name)==1) //read a festival card string
    {
        //store the parameter set
    }
    fclose(fp);
    printf("Total number of festival cards : %i\n", festival_nr);
    
    
    
    //2. Player configuration ---------------------------------------------------------------------------------
    
    do
    {
        //input player number to player_nr
        printf("input player no. :");
        scanf("%d", &player_nr);
        fflusf(stdin);
    }
    while (player_nr < 0 || player_nr > MAX_PLAYER);
    generatePlayers(player_nr, initEnergy);
    
    
    //3. SM Marble game starts ---------------------------------------------------------------------------------
    while (!isGraduated()) //is anybody graduated?
    {
        int die_result;
        
        //4-1. initial printing
        printPlayerStatus();
        
        //4-2. die rolling (if not in experiment)
        die_result = rolldie(turn);
        
        //4-3. go forward
        goForward(turn, die_result);

		//4-4. take action at the destination node of the board
        actionNode(turn);
        
        //4-5. next turn
        turn = (turn + 1)%player_nr;
        
    }
    
    return 0;
}
