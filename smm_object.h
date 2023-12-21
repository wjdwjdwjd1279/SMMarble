//
//  smm_object.h
//  SMMarble object
//
//  Created by Juyeop Kim on 2023/11/05.
//

#ifndef smm_object_h
#define smm_object_h

#define SMMNODE_TYPE_LECTURE

/* node type :
    lecture,
    restaurant,
    laboratory,
    home,
    experiment,
    foodChance,
    festival
*/


/* grade :
    A+,
    A0,
    A-,
    B+,
    B0,
    B-,
    C+,
    C0,
    C-
*/

typedef enum smmObjGrade{
	smmObjGrade_Ap =0,
	smmObjGrade_A0,
	smmObjGrade_Am,
	smmObjGrade_Bp,
	smmObjGrade_B0,
	smmObjGrade_Bm,
	smmObjGrade_Cp,
	smmObjGrade_C0,
	smmObjGrade_Cm,
	smmObjGrade_max
	
}smmObjGrade_e;

typedef enum smmObjGrade smmGrade_e;


//object generation
void smmObj_genNode(char* name, int type, int credit, int energy);

//member retrieving

char*smmObj_getNodeName(int node_nr);
int smmObj_getNodeType(int node_nr);

//element to string

char*smmObj_getNodeName(int type);


#endif /* smm_object_h */
