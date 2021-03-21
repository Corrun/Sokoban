#include "main.h"

int min (int premier, int deuxieme){
	if(premier > deuxieme){
		return deuxieme;
	}else{
		return premier;
	}
}

int max (int premier, int deuxieme){
	if(premier < deuxieme){
		return deuxieme;
	}else{
		return premier;
	}
}
