#include <cstdio>
#include <iostream>
#include "graphe.h"
#include <Windows.h> //Pour windows (utf8) A ENLEVER

int main() {
	SetConsoleOutputCP(CP_UTF8); //Pour windows (utf8) A ENLEVER

	std::printf("░░░░▒▒▒▒▓▓▓▓ Graphes ▓▓▓▓▒▒▒▒░░░░\n");

	try {
		Graphe gr1 = Graphe("exemple1.txt");
		//Graphe gr1 = Graphe(15, 30);
		gr1.affiche();

		//GridCoord start = { 4, 1 };
		//GridCoord goal = { 26, 14 };

		GridCoord start = { 4, 1 };
		GridCoord goal = { 3, 6 };

		std::cout << "Distance à l'Est de (" << start.i << ", " << start.j << ") : "
			<< gr1.getDistance(start, Direction::Est) << std::endl;

		gr1.parcoursAStar(start, goal);

		gr1.saveFile("resultat.txt");
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "\033[1m\033[41m\033[37m" << "Argument invalide : " << e.what() << "\033[0m" << std::endl;
	}

	std::printf("░░▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒░░\n");

	return 0;
}
