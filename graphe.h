#ifndef _GRAPHE
#define _GRAPHE
#include "sommet.h"
#include <vector>
#include <string>

enum class Direction { Nord, Sud, Ouest, Est };
enum class Color { Blanc, Gris, Noir, Bleu };

struct GridCoord {
	int i, j;
	bool operator == (const GridCoord& secondObj) const {
		return (i == secondObj.i && j == secondObj.j);
	}
	bool operator != (const GridCoord& secondObj) const {
		return (i != secondObj.i || j != secondObj.j);
	}
};

struct ContentParcours {
	GridCoord current; //p-e direct mettre indice global
	GridCoord pred;
	Color color;
	double longueur;
	double priorite;

	//Pour la priority queue :
	//Le plus petit doit être mis en premier (et si c'est égale, l'élément ajouté en dernier est prioritaire)
	bool operator < (const ContentParcours& secondObj) const {
		return priorite >= secondObj.priorite;
	}
};

class Graphe {
	public :
		Graphe(int largeur, int hauteur);
		Graphe(std::string fileName);
		~Graphe();
		Graphe& operator = (const Graphe& graphe);
		void affiche();
		void saveFile(std::string fileName);

		int getIndice(GridCoord coord);
		int getAltitude(int indice);
		int getNord(GridCoord coord);
		int getSud(GridCoord coord);
		int getOuest(GridCoord coord);
		int getEst(GridCoord coord);
		double getDistance(GridCoord coord, Direction dir);

		std::vector<std::pair<int, Direction>> getVoisins(GridCoord coord);
		void parcoursAStar(GridCoord start, GridCoord goal, double(&fHeuristique)(Graphe*, GridCoord, GridCoord));
		void afficheAlgo(GridCoord start, GridCoord goal);

	private :
		int largeur;
		int hauteur;
		std::vector<Sommet> grid;
		std::vector<ContentParcours> gridParcours;
};

#endif