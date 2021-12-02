#ifndef _SOMMET
#define _SOMMET
#include <vector>

class Sommet {
	public :
		Sommet();
		Sommet(int alt);
		int getAltitude();
		void setAltitude(int alt);

	private :
		int altitude;
};

#endif