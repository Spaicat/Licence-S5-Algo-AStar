#include "graphe.h"
#include "sommet.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <math.h>
#include <queue>

Graphe::Graphe() {
	this->largeur = 0;
	this->hauteur = 0;
}

Graphe::Graphe(int largeur, int hauteur) {
	this->largeur = largeur;
	this->hauteur = hauteur;

	for (int i = 0; i < hauteur * largeur; i++) {
		this->grid.push_back(rand() % 50 + 1); //Altitude aléatoire entre 1 et 50
	}
}

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
			if (std::isdigit(altitudeSommet[0])) {
				this->grid.push_back(std::stoi(altitudeSommet));
			}
			else {
				this->grid.push_back(-1);
			}
		}
	}
	else {
		throw std::invalid_argument("Fichier introuvable");
	}
}

Graphe::~Graphe() {
	//Vector à son propre destructeur donc il n'y a pas besoin d'en mettre
	//delete[] &grid; //Pour les tableaux
}

Graphe& Graphe::operator = (const Graphe& graphe) {
	this->largeur = graphe.largeur;
	this->hauteur = graphe.hauteur;
	this->grid = graphe.grid;
	this->gridParcours = graphe.gridParcours;

	return *this;
}

void Graphe::affiche() {
	for (int i = 0; i < hauteur; i++) {
		for (int j = 0; j < largeur; j++) {
			int alt = this->grid[getIndice(GridCoord{i, j})].getAltitude();

			std::cout << std::setw(4);
			std::cout << alt << " ";
		}
		std::cout << std::endl;
	}
}


int Graphe::getLargeur() {
	return this->largeur;
}
int Graphe::getHauteur() {
	return this->hauteur;
}

int Graphe::getIndice(GridCoord coord) {
	int i = coord.i;
	int j = coord.j;
	int res = -1;
	if ((i >= 0 && i < hauteur) && (j >= 0 && j < largeur))
		res = i * largeur + j;
	return res;
}

int Graphe::getAltitude(int indice) {
	return grid[indice].getAltitude();
}

int Graphe::getNord(GridCoord coord) {
	coord.i -= 1;
	return getIndice(coord);
}
int Graphe::getSud(GridCoord coord) {
	coord.i += 1;
	return getIndice(coord);
}
int Graphe::getOuest(GridCoord coord) {
	coord.j -= 1;
	return getIndice(coord);
}
int Graphe::getEst(GridCoord coord) {
	coord.j += 1;
	return getIndice(coord);
}


double Graphe::getDistance(GridCoord coord, Direction dir) {
	int sommetCurr = getIndice(coord);
	int sommetVoisin = -1;

	switch (dir) {
		case Direction::Sud :
			sommetVoisin = getSud(coord);
			break;
		case Direction::Ouest :
			sommetVoisin = getOuest(coord);
			break;
		case Direction::Nord :
			sommetVoisin = getNord(coord);
			break;
		case Direction::Est :
			sommetVoisin = getEst(coord);
			break;
	}
	double res = -1;
	if (sommetCurr >= 0 && sommetVoisin >= 0)
		res = sqrt(1 + pow(getAltitude(sommetCurr) - getAltitude(sommetVoisin), 2));
	return res;
}

std::vector<std::pair<int, Direction>> Graphe::getVoisins(GridCoord coord) {
	std::vector<std::pair<int, Direction>> voisins;
	voisins.push_back({ getNord(coord), Direction::Nord });
	voisins.push_back({ getOuest(coord), Direction::Ouest });
	voisins.push_back({ getSud(coord), Direction::Sud });
	voisins.push_back({ getEst(coord), Direction::Est });
	return voisins;
}

void Graphe::afficheAlgo(GridCoord start, GridCoord goal, bool showLongueur) {
	for (int i = 0; i < hauteur; i++) {
		for (int j = 0; j < largeur; j++) {
			GridCoord curr = GridCoord{ i, j };
			int indice = getIndice(curr);

			//Renvoie un espace avant et après chaque chose à afficher dans le cas où on affiche l'altitude
			std::string space = (showLongueur) ? "  " : "";

			//Détermine la chaine de caractères à afficher
			std::string toShow = "";
			if (curr == start) {
				toShow = "S";
			}
			else if (curr == goal) {
				toShow = "G";
			}
			else if (getAltitude(indice) == -1) {
				toShow = "X";
			}
			else {
				//Montre l'altitude sous la forme "18.0" sinon montre "-" à la place
				if (showLongueur) {
					std::string textNum = std::to_string(gridParcours[indice].longueur);
					toShow = textNum.substr(0, textNum.find(".") + 2);
				}
				else {
					toShow = "-";
				}
			}

			std::string strColor;
			switch (gridParcours[indice].color) {
				case Color::Blanc :
					strColor = "\033[1m\033[40m\033[37m";
					break;
				case Color::Gris :
					strColor = "\033[1m\033[47m\033[30m";
					break;
				case Color::Noir:
					strColor = "\033[1m\033[41m\033[37m";
					break;
				case Color::Bleu:
					strColor = "\033[1m\033[44m\033[37m";
					break;
			}

			if (showLongueur)
				std::cout << strColor << " " << std::setw(5) << toShow << " \033[0m\033[0m";
			else
				std::cout << strColor << toShow << "\033[0m\033[0m";
		}
		std::cout << std::endl;
	}
}


void Graphe::parcoursAStar(GridCoord start, GridCoord goal, bool bavard, bool showLongueur, double(&fHeuristique)(Graphe*, GridCoord, GridCoord)) {
	if (getIndice(start) == -1 || getIndice(goal) == -1) {
		throw std::invalid_argument("Le départ ou l'arrivée n'est pas dans le graphe");
	}
	for (int i = 0; i < hauteur; i++) {
		for (int j = 0; j < largeur; j++) {
			gridParcours.push_back(ContentParcours{ GridCoord{i, j}, GridCoord{-1, -1}, Color::Blanc, 0, 0 });
		}
	}
	std::priority_queue<ContentParcours> filePriorite;

	//1er élément
	int startIndice = getIndice(start);
	gridParcours[startIndice].color = Color::Gris;
	filePriorite.push(gridParcours[startIndice]);

	double distParcourue = 0;
	while (!filePriorite.empty()) {
		ContentParcours curr = filePriorite.top();
		filePriorite.pop();

		//On arrête la boucle quand on est arrivé à la destination
		if (curr.current == goal) {
			break;
		}

		//On retiens la distance parcourue jusqu'ici
		distParcourue = gridParcours[getIndice(curr.current)].longueur;

		//Pour chaque voisin, on récupère son indice et l'indication de quel voisin c'est (Nord pour le voisin nord)
		for (std::pair<int, Direction> voisinIndication : getVoisins(curr.current)) {
			//Si le voisin existe (cas sur les bords)
			if (voisinIndication.first > -1 && getAltitude(voisinIndication.first) != -1) {
				double distAvecVoisin = distParcourue + getDistance(curr.current, voisinIndication.second);
				ContentParcours* voisin = &(gridParcours[voisinIndication.first]);
				if (voisin->color == Color::Blanc || (distAvecVoisin < voisin->longueur && voisin->color != Color::Noir)) {
					voisin->color = Color::Gris;
					voisin->pred = gridParcours[getIndice(curr.current)].current;
					voisin->longueur = distAvecVoisin;
					voisin->priorite = distAvecVoisin + fHeuristique(this, voisin->current, goal);
					filePriorite.push(*voisin);
				}
			}
		}
		gridParcours[getIndice(curr.current)].color = Color::Noir;

		if (bavard) {
			afficheAlgo(start, goal, showLongueur);
			std::cout << std::endl;
		}
	}

	//On marque et affiche le parcours retenu ({ -1, -1 } = chemin non trouvé)
	GridCoord curr = goal;
	while (curr != start && curr != GridCoord{ -1, -1 }) {
		gridParcours[getIndice(curr)].color = Color::Bleu;
		curr = gridParcours[getIndice(curr)].pred;
	}
	if (curr != GridCoord{ -1, -1 })
		gridParcours[getIndice(curr)].color = Color::Bleu;

	afficheAlgo(start, goal, showLongueur);
	std::cout << std::endl;
}