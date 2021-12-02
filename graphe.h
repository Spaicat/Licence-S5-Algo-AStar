#ifndef _GRAPHE
#define _GRAPHE
#include "sommet.h"
#include <vector>
#include <string>

enum class Direction { Nord, Sud, Ouest, Est };

class Graphe {
	public :
		Graphe(std::string fileName);
		~Graphe();
		Graphe& operator = (const Graphe& graphe);
		void affiche();
		void saveFile(std::string fileName);

		int getIndice(int i, int j);
		int getAltitude(int indice);
		
		int getNord(int i, int j);
		int getSud(int i, int j);
		int getOuest(int i, int j);
		int getEst(int i, int j);

		int getDistance(int i, int j, Direction dir);

	private :
		int largeur;
		int hauteur;
		std::vector<Sommet> grid;
};

#endif