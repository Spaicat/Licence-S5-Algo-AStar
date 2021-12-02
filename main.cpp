#include <cstdio>
#include <iostream>
#include "graphe.h"
#include <Windows.h> //Pour windows (utf8) A ENLEVER

int main() {
	SetConsoleOutputCP(CP_UTF8); //Pour windows (utf8) A ENLEVER

	std::printf("░░░░▒▒▒▒▓▓▓▓ Graphes ▓▓▓▓▒▒▒▒░░░░\n");

	try {
		Graphe gr1 = Graphe("exemple1.txt");
		gr1.affiche();

		std::cout << "Distance à l'Est de (0, 0) : " << gr1.getDistance(0, 0, Direction::Est) << std::endl;

		gr1.saveFile("exemple2.txt");
	}
	catch (const std::invalid_argument& e) {
		std::cerr << "Argument invalide: " << e.what() << std::endl;
	}

	std::printf("░░▒▒▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▓▒▒░░\n");

	return 0;
}
