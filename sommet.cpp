#include "sommet.h"

Sommet::Sommet() {
	this->altitude = 0;
}
Sommet::Sommet(int alt) {
	this->altitude = alt;
}

int Sommet::getAltitude() {
	return altitude;
}

void Sommet::setAltitude(int alt) {
	altitude = alt;
}
