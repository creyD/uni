#include <iostream>
#include <fstream>
using namespace std;

struct Domino {
	int zahl1;
	int zahl2;
};

struct Temp {
	Domino* element;
	Temp* next;
};

struct Ring {
	Domino* element;
	Ring* last;
	Ring* next;
};

struct AllRings {
	Ring* ring;
	AllRings* next;
};

// Zwischenspeicher fuer geladene Elemente, einfach verkettete Liste
Temp* loaded;
Temp* first;
int numOfElem;

// Vertauscht die beiden Zahlen auf einem Domino Stein
void swapNumbers(Domino* stein) {
	int temp = (*stein).zahl1;
	(*stein).zahl1 = (*stein).zahl2;
	(*stein).zahl2 = temp;
	return;
}

// Liest die Eingabendatei ein
void loadFile(char* pfad) {
	int elemCount;
	ifstream inFile;
	inFile.open(pfad);
	inFile >> elemCount;
	numOfElem = elemCount;
	Temp* temporary = new Temp[elemCount];

	for (int i = 0; i < elemCount; i++) {
		Domino* newStone = new Domino();
		inFile >> (*newStone).zahl1 >> (*newStone).zahl2;
		temporary[i].element = newStone;

		if (i > 0) {
			temporary[i - 1].next = &temporary[i];
		}
		if (i == elemCount) {
			temporary[i].next = NULL;
		}
	}

	// Schlieﬂen des Files und speichern der Elemente
	loaded = temporary;
	first = temporary;
	inFile.close();

	// Ausgeben der eingelesenen Daten
	Temp* element = loaded;
	for (int i = 0; i < elemCount; i++) {
		cout << "[" << element->element->zahl1 << ":" << element->element->zahl2 << "]";
		element = element->next;
	}
	cout << endl;
	return;
}

// Ueberprueft ob zwei Elemente aneinander passen oder nicht (wenn benoetigt dreht es den Dominostein)
bool searchFit(Domino* element, Domino* lastElement) {
	if (lastElement->zahl2 == element->zahl1) {
		return true;
	}
	else if (lastElement->zahl2 == element->zahl2) {
		swapNumbers(element);
		return true;
	}
	return false;
}

// Loescht ein Element aus der Liste und gibt ein valides Listenelement zuruek
Temp* removeElement(Domino* element) {
	Temp* here = loaded;
	Temp* lastOne = here;
	for (int i = 0; i < numOfElem; i++) {
		if (here->element == element) {
			numOfElem--;
			if (i == 0) {
				if (numOfElem == 0) {
					return NULL;
				}
				else {
					first = here;
					loaded->element = here->next->element;
					loaded->next = here->next->next;
					return loaded;
				}
			}
			else {
				lastOne->next = here->next;
				return lastOne;
			}
		}
		else {
			lastOne = here;
			here = here->next;
		}
	}
}

void sort() {
	Domino* sorted = new Domino[numOfElem];
	sorted[0] = *loaded->element;
	cout << "[" << loaded->element->zahl1 << ":" << loaded->element->zahl2 << "]";
	loaded = removeElement(loaded->element);
	int counter = 1;

	while (numOfElem > 0) {
		if (searchFit(loaded->element, &sorted[counter])) {
			sorted[counter] = *loaded->element;
			cout << "[" << loaded->element->zahl1 << ":" << loaded->element->zahl2 << "]";
			loaded = removeElement(loaded->element);
			counter++;
		}
		else {
			if (loaded->next == NULL) {
				loaded = first;
			}
			else {
				loaded = loaded->next;
			}
		}
	}

	// Speichere den zwischengespeicherten Ring in einer Ringliste
	Ring* ring = new Ring();
	for (int i = 0; i < counter; i++) {
		ring[i].element = &sorted[i];

		if (i == counter - 1) {
			ring[i].next->element = &sorted[0];
		}
		else {
			ring[i].next->element = &sorted[i + 1];
		}

		if (i < 1) {
			ring[i].last->element = &sorted[i - 1];
		}
		else {
			ring[i].last->element = &sorted[counter - 1];
		}
	}
	return;
}

int main(int argc, char* argv[]) {
	if (argc > 1) {
		// Komplexitaetsgrad des Ladens der Datei --> O(n)
		loadFile(argv[1]);
		// Komplexitaetsgrad der Listenfindung: O(n^2)
		// Komplexitaetsgrad der Ausgabe --> O(n)
		sort();
	}
	return 0;
}
