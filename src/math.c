#include "main.h"

// Renvoie la valeur minimale entrée en paramètre
int min (int premier, int deuxieme){
//Compare les deux paramètres, et permet de renvoyer le plus petit
	if(premier > deuxieme){
		return deuxieme;
	}else{
		return premier;
	}
}

// Renvoie la valeur maximale entrée en paramètre
int max (int premier, int deuxieme){
	//Compare les deux paramètres, et permet de renvoyer le plus grand
	if(premier < deuxieme){
		return deuxieme;
	}else{
		return premier;
	}
}

// Renvoie la lettre majuscule en minuscule.
char majuscule_to_minuscule(char lettre){
	// 65 = A ; Z = 90
	if(lettre >=65 && lettre <= 90){
		return lettre + 32;
	}else{
		return lettre;
	}
}