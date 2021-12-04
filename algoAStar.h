#ifndef _ALGOASTAR
#define _ALGOASTAR
#include "graphe.h"
#include "sommet.h"
#include <vector>
#include <string>

enum class Color { Blanc, Gris, Noir };

struct ContentVector {
	GridCoord current;
	GridCoord pred;
	Color color;
	int longueur;
};

class AlgoAStar {
	public :
		AlgoAStar(Graphe* graphe, GridCoord start, GridCoord goal);
		~AlgoAStar();

		void affiche();
		void parcours();

	private :
		std::vector<ContentVector> grid;
		Graphe* graphe;
		GridCoord start;
		GridCoord goal;
};

#endif