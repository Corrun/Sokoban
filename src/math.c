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
int majuscule_en_minuscule(int lettre) {
	// 65 = A ; Z = 90
	if(lettre >= 'A' && lettre <= 'Z'){
		return lettre + 32;
	}else{
		return lettre;
	}
}