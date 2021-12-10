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

	//Pour la priority queue
	bool operator < (const ContentParcours& secondObj) const {
		//Si les priorités sont égales, l'élément ajouté en dernier est prioritaire
		// (celui avec la plus grande longueur car ce sont les voisins ceux qui sont ajoutés en dernier)
		if (priorite == secondObj.priorite)
			return longueur < secondObj.longueur;

		//Le plus petit doit être mis en premier
		return priorite > secondObj.priorite;
	}
};

class Graphe {
	public :
		Graphe();
		Graphe(int largeur, int hauteur);
		Graphe(std::string fileName);
		~Graphe();
		Graphe& operator = (const Graphe& graphe);
		void affiche();

		int getLargeur();
		int getHauteur();
		int getIndice(GridCoord coord);
		int getAltitude(int indice);
		int getNord(GridCoord coord);
		int getSud(GridCoord coord);
		int getOuest(GridCoord coord);
		int getEst(GridCoord coord);
		double getDistance(GridCoord coord, Direction dir);

		std::vector<std::pair<int, Direction>> getVoisins(GridCoord coord);
		void parcoursAStar(GridCoord start, GridCoord goal, bool bavard, double(&fHeuristique)(Graphe*, GridCoord, GridCoord));
		void afficheAlgo(GridCoord start, GridCoord goal);

	private :
		int largeur;
		int hauteur;
		std::vector<Sommet> grid;
		std::vector<ContentParcours> gridParcours;
};

#endif