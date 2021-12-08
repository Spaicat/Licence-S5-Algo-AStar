#include <cstdio>
#include <iostream>
#include "graphe.h"
#include <Windows.h> //Pour windows (utf8) A ENLEVER


double approxEuclidienne(Graphe* graph, GridCoord sommet, GridCoord goal) {
	return sqrt(pow(sommet.i - goal.i, 2) + pow(sommet.j - goal.j, 2));
}

double approxManhattan(Graphe* graph, GridCoord sommet, GridCoord goal) {
	double distManhattan = pow(abs(sommet.i - goal.i) + abs(sommet.j - goal.j), 2);
	double distHauteur = pow(graph->getAltitude(graph->getIndice(sommet)) - graph->getAltitude(graph->getIndice(goal)), 2);
	return sqrt(distManhattan + distHauteur);
}

int main() {
	SetConsoleOutputCP(CP_UTF8); //Pour windows (utf8) A ENLEVER

	//TODO : Faire tous les choix dans la console
	// Ecriture du chemin du fichier (si oui)
	// Start et Goal
	// ...

	std::printf("░░░░▒▒▒▒▓▓▓▓ Graphes ▓▓▓▓▒▒▒▒░░░░\n");

	try {
		//Graphe gr1 = Graphe("exemple1.txt");
		Graphe gr1 = Graphe(8, 8);
		gr1.affiche();

		GridCoord start = { 0, 0 };
		GridCoord goal = { 7, 7 };

		//GridCoord start = { 4, 1 };
		//GridCoord goal = { 3, 6 };

		std::cout << "Distance à l'Est de (" << start.i << ", " << start.j << ") : "
			<< gr1.getDistance(start, Direction::Est) << std::endl;

		gr1.parcoursAStar(start, goal, approxManhattan);

		gr1.saveFile("resultat.txt");
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "\033[1m\033[41m\033[37m" << "Argument invalide : " << e.what() << "\033[0m" << std::endl;
	}

	std::printf("░░▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒░░\n");

	return 0;
}
