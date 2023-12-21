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

static char smmNodeName[SMMNODE_TYPE_MAX][MAX_CHARNAME]={
    "lecture",
    "restaurant",
    "laboratory",
    "home",
    "experiment",//실험실//
    "foodChance",
    "festival"
};

char* smmObj_getTypeName(int type){
	return (char*)smmNodeName[type];
}

struct smmObjet {
	char name[MAX_CHARNAME];
	int type;
	int credit;
	int energy;
}smmObject_t;

static char smmObj_name[MAX_NODE][MAX_CHARNAME];
static int smmObj_type[MAX_NODE];
static int smmObj_credit[MAX_NODE];
static int smmObj_energy[MAX_NODE];
static int smmObj_noNode = 0;

void* smmObj_genObject(char* name, smmObjType_e objType, int type, int credit, int energy, smmObjGrade_e grade){
	smmObject_t* ptr;
	ptr = (smmObject_t*)malloc(sizeof(smmObject_t));
	
	strcpy(ptr->name, name);
	ptr->objType = objType;
	ptr->type = type;
	ptr->credit = credit;
	ptr->energy=energy;
	ptr->grade = grade;
	
	return ptr;
}

//object generation 
//(send to main.c)
/*void smmObj_genNode(char* name, int type, int credit, int energy)
{
	strcpy(smmObj_name[smmObj_noNode].name, name);
	smmObj_type[smmObj_noNode].type =type;
	smmObj_credit[smmObj_noNode].credit = credit;
	smmObj_energy[smmObj_noNode].energy = energy;
	
	smmObj_noNode++;
}*/

char* smmObj_getNodeName(void* obj){
	smmObject_t* ptr = (smmObject_t*)obj;
	return ptr->name;
}


int smmObj_getNodeType(void* obj)
{
	smmObject_t* ptr = (smmObject_t*)obj;
	return ptr->type;
}
//member retrieving



//element to string
char* smmObj_getNodeCredit(void* obj)
{	smmObject_t* ptr = (smmObject_t*)obj;
	return ptr->credit;
}

char* smmObj_getNodeEnergy(void* obj)
{	smmObject_t* ptr = (smmObject_t*)obj;
	return ptr->energy;
}

char* smmObj_getGradeName(void* obj)
{
    return smmGradeName[grade];
}

