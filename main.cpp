#include <cstdio>
#include <iostream>
#include "graphe.h"
#include <Windows.h> //Pour windows (utf8) A ENLEVER


double approxEuclidienne2D(Graphe* graph, GridCoord sommet, GridCoord goal) {
	return sqrt(pow(sommet.i - goal.i, 2) + pow(sommet.j - goal.j, 2));
}

double approxEuclidienne3D(Graphe* graph, GridCoord sommet, GridCoord goal) {
	double distHauteur = pow(graph->getAltitude(graph->getIndice(sommet)) - graph->getAltitude(graph->getIndice(goal)), 2);
	return sqrt(pow(sommet.i - goal.i, 2) + pow(sommet.j - goal.j, 2) + distHauteur);
}

double approxManhattan2D(Graphe* graph, GridCoord sommet, GridCoord goal) {
	//Deux variables séparé pour eviter le warning
	double first = abs(sommet.i - goal.i);
	double second = abs(sommet.j - goal.j);
	return first + second;
}

double approxManhattan3D(Graphe* graph, GridCoord sommet, GridCoord goal) {
	double distManhattan = pow(abs(sommet.i - goal.i) + abs(sommet.j - goal.j), 2);
	double distHauteur = pow(graph->getAltitude(graph->getIndice(sommet)) - graph->getAltitude(graph->getIndice(goal)), 2);
	return sqrt(distManhattan + distHauteur);
}

std::string printQuestionOuiNon(std::string message) {
	std::string rep;
	do {
		std::cout << message;
		std::cin >> rep;
	} while (!std::cin.fail() && rep != "o" && rep != "O" && rep != "n" && rep != "N");
	return rep;
}

int main() {
	SetConsoleOutputCP(CP_UTF8); //Pour windows (utf8) A ENLEVER

	std::printf("░░░░▒▒▒▒▓▓▓▓ Graphes ▓▓▓▓▒▒▒▒░░░░\n");

	try {
		std::string rep;

		Graphe gr1;
		rep = printQuestionOuiNon("Graphe généré à partir d'un fichier (sinon aléatoire) ? (o/n) ");
		if (rep == "o" || rep == "O") {
			std::cout << "Nom de votre fichier : ";
			std::cin >> rep;

			gr1 = Graphe(rep);
		}
		else {
			int hauteur;
			int largeur;
			std::cout << "Hauteur du graphe : ";
			std::cin >> hauteur;
			std::cout << "Largeur du graphe : ";
			std::cin >> largeur;


			gr1 = Graphe(largeur, hauteur);
		}

		bool bavard = false;
		rep = printQuestionOuiNon("Algorithme bavard ? (o/n) ");
		if (rep == "o" || rep == "O") {
			bavard = true;
		}

		bool afficheLongueur = false;
		rep = printQuestionOuiNon("Afficher l'altitude (Sinon prends moins de place) ? (o/n) ");
		if (rep == "o" || rep == "O") {
			afficheLongueur = true;
		}

		GridCoord start = { 0, 0 };
		GridCoord goal = { 0, 0 };
		rep = printQuestionOuiNon("Saisir départ et arrivée (sinon aléatoire) ? (o/n) ");
		if (rep == "o" || rep == "O") {
			std::cout << "Départ i (hauteur) : ";
			std::cin >> start.i;
			std::cout << "Départ j (largeur) : ";
			std::cin >> start.j;

			std::cout << "Arrivée i (hauteur) : ";
			std::cin >> goal.i;
			std::cout << "Arrivée j (largeur) : ";
			std::cin >> goal.j;
		}
		else {
			start = { rand() % gr1.getHauteur(), rand() % gr1.getLargeur() };
			goal = { rand() % gr1.getHauteur(), rand() % gr1.getLargeur() };
		}

		gr1.parcoursAStar(start, goal, bavard, afficheLongueur, approxManhattan3D);
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "\033[1m\033[41m\033[37m" << "Argument invalide : " << e.what() << "\033[0m" << std::endl;
	}

	std::printf("░░▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒░░\n");

	return 0;
}
