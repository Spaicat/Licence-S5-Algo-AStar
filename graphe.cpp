#include "graphe.h"
#include "sommet.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <math.h>

Graphe::Graphe(std::string fileName) {
	this->largeur = 0;
	this->hauteur = 0;
	//On copie nos données du fichier dans notre graphe
	std::ifstream grapheFile (fileName);
	if (grapheFile.is_open()) {
		grapheFile >> this->largeur;
		grapheFile >> this->hauteur;

		while (grapheFile.good()) {
			std::string altitudeSommet;
			grapheFile >> altitudeSommet;
			this->grid.push_back(std::stoi(altitudeSommet));
		}
	}
}

Graphe::~Graphe() {
	//delete[] grid;
}

Graphe& Graphe::operator = (const Graphe& graphe) {
	return *this;
}

void Graphe::affiche() {
	for (int i = 0; i < hauteur; i++) {
		for (int j = 0; j < largeur; j++) {
			int alt = this->grid[getIndice(i, j)].getAltitude();

			std::cout << std::setw(6);
			std::cout << alt << " ";
		}
		std::cout << std::endl;
	}
}

void Graphe::saveFile(std::string fileName) {
	std::ofstream grapheFile(fileName);
	if (grapheFile.is_open()) {
		grapheFile << this->largeur << " ";
		grapheFile << this->hauteur << "\n";

		for (int i = 0; i < grid.size() - 1; i++) {
			grapheFile << grid[i].getAltitude() << " ";
		}
		//Le dernier élément n'aura pas d'espace
		if (grid.size() != 0) grapheFile << grid[grid.size()-1].getAltitude();
	}
	std::cout << "Fichier enregistré : \"" << fileName << "\"" << std::endl;
}


int Graphe::getIndice(int i, int j) {
	int val = -1;
	if ((i >= 0 && i < hauteur) && (j >= 0 && j < largeur))
		val = i * largeur + j;
	else
		throw std::invalid_argument("Indice négatif ou supérieur à la taille du tableau");
	return val;
}

int Graphe::getAltitude(int indice) {
	return grid[indice].getAltitude();
}

int Graphe::getNord(int i, int j) {
	return getIndice(i-1, j);
}
int Graphe::getSud(int i, int j) {
	return getIndice(i+1, j);
}
int Graphe::getOuest(int i, int j) {
	return getIndice(i, j-1);
}
int Graphe::getEst(int i, int j) {
	return getIndice(i, j+1);
}


int Graphe::getDistance(int i, int j, Direction dir) {
	int altCurr = getAltitude(getIndice(i, j));
	int altVoisin = 0;

	switch (dir) {
		case Direction::Nord :
			altVoisin = getAltitude(getNord(i, j));
			break;
		case Direction::Sud :
			altVoisin = getAltitude(getSud(i, j));
			break;
		case Direction::Ouest :
			altVoisin = getAltitude(getOuest(i, j));
			break;
		case Direction::Est :
			altVoisin = getAltitude(getEst(i, j));
			break;
	}
	return sqrt(1 + pow(altCurr - altVoisin, 2));
}