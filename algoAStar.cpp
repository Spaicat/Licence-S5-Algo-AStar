#include "algoAStar.h"
#include "graphe.h"
#include "sommet.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <queue>

AlgoAStar::AlgoAStar(Graphe* graphe, GridCoord start, GridCoord goal) {
	this->graphe = graphe;
	this->start = start;
	this->goal = goal;

	this->grid.push_back();
}
AlgoAStar::~AlgoAStar() {
	//TODO
}

void AlgoAStar::affiche() {
	for (int i = 0; i < graphe->hauteur; i++) {
		for (int j = 0; j < graphe->largeur; j++) {
			std::string graphe = graphe->;

			std::cout << std::setw(5);
			std::cout << alt << " ";
		}
		std::cout << std::endl;
	}
}

void AlgoAStar::parcours() {
	std::queue<ContentVector> file;
	ContentVector start = { this->start, this->start, Color::Gris, 0 };
	file.push(start)
}