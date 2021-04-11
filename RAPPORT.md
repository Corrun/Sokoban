# Projet M2101 - Sokoban (2020 - 2021)
> Un projet réalisé par **Amaury VANOORENBERGHE**, **Hugo ROUX** et **Néo ALMEIDA**
<p align="center"><img src="./img/thonkmentation_fault.png" height="96 px"></img></p>
-----

## Rapport de projet

Lors de la réalisation de ce projet, nous avons pu rencontrer plusieurs problèmes et difficultés prévues:

- Nous avons en premier lieu eu des difficultés en rapport avec des erreurs de segmentation (`Segmentation fault (core dumped)`)  

	Résoudre ces erreurs était compliquer, contrairement à des langages plus haut niveau, on ne sait pas quelle ligne de code a causé l'erreur, rendant le débogage plus lent.

- L'insertion d'un nouveau score dans le top 5 a aussi été compliquée à déboguer car il nous a fallu gérer tous les cas particuliers (ajout d'un score si la liste est pleine, modifier un score existant,...).

- Nous avons aussi rencontrer certains problèmes liés aux disponibilités de chacun, ce qui a failli entraver la réussite du projet.

- Et c'est pour ces mêmes raisons et le fait que chacun progressait a une vitesse différente que nous avons décidé pour ne pas se "voler" le travail entre membres de l'équipe et de travailler sur une interface textuelle via la librairie ncurses en bonus.  
Ce bonus s'est avéré très utile pour ne pas avoir a appuyer sur entrée à chaque déplacement.

Ci-dessous, une image de tortue (c'est cadeau)
<p align="center"><img class="spin" src="./img/turtle_dance.gif" height="100 px"></img></p>

<style>
.spin {
	-webkit-animation:spin 2s linear infinite;
    -moz-animation:spin 2s linear infinite;
    -animation:spin 2s linear infinite;
}

@-moz-keyframes spin {
	100% {
		-moz-transform: rotate(360deg); 
	}
}
@-webkit-keyframes spin {
	100% {
		-webkit-transform: rotate(360deg);
	}
}
@keyframes spin {
	100% {
		-webkit-transform: rotate(360deg); transform:rotate(360deg);
	}
}
</style>