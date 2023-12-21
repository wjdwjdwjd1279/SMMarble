//
//  smm_node.c
//  SMMarble
//
//  Created by Juyeop Kim on 2023/11/05.
//

#include "smm_common.h"
#include "smm_object.h"
#include <string.h>

#define MAX_NODETYPE    7
#define MAX_GRADE       9
#define MAX_NODE       100

struct smmObjet {
	char name[MAX_CHRNAME];
	int type;
	int credit;
	int energy;
};

static char smmObj_name[MAX_NODE][MAX_CHARNAME];
static int smmObj_type[MAX_NODE];
static int smmObj_credit[MAX_NODE];
static int smmObj_energy[MAX_NODE];
static int smmObj_noNode = 0;


//object generation 
//(send to main.c)
void smmObj_genNode(char* name, int type, int credit, int energy)
{
	strcpy(smmObj_name[smmObj_noNode], name);
	smmObj_type[smmObj_noNode]=type;
	smmObj_credit[smmObj_noNode] = credit;
	smmObj_energy[smmObj_noNode] = energy;
	
	smmObj_noNode++;
}

char* smmObj_getNodeName(int node_nr){
	return smmObj_name[node_nr];
}


int smmObj_genType(int node_nr)
{
	return smmObj_type[node_nr];
}
//member retrieving



//element to string
char* smmObj_getNodeName(smmNode_e type)
{
    return smmNodeName[type];
}

char* smmObj_getGradeName(smmGrade_e grade)
{
    return smmGradeName[grade];
}

