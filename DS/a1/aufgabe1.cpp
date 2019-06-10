#include <iostream>

// Da auf dem Abgabeserver g++17 und g++14 nicht vorhanden sind wurde dieses Programm nur mit g++11 getestet
// Exponentialfunktion
int power(unsigned int basis, unsigned int exponent) {
	int ergebnis = 1;
	if (exponent != 0) {
		for (int i = 1; i <= exponent; i++) {
			ergebnis *= basis;
		}
	}	
	return ergebnis;
}


// Hilfsfunktion um die naechste/ erste 0 in einem Array zu finden
int getNext(int* zahlen, int n) {
	for (int i = 0; i <= n; i++) {
		if (zahlen[i] == 0) {
			return i;
		}
	}
	return 0;
}


int* siebDesEratosthenes(unsigned int n) {
	// n grosses Array erstellen um die Zahlen abzuarbeiten
	int* zahlen = new int[n];
	// p als Zaehler der Primzahlen im Intervall
	int p = 0;
	// S als die Anzahl an Streichungen im Intervall
	int s = 0;
	// current als die aktuell zu bearbeitende Zahl (Index im zahlen Array)
	int current;

	// Sieb beginnt bei 2, daher 0 und 1 auf markiert (1) setzen
	zahlen[0] = 1;
	zahlen[1] = 1;

	// Alle anderen Zahlen auf 0 setzen (unmarkiert aufschreiben)
	for (int i = 2; i <= n; i++) {
		zahlen[i] = 0;
	}

	while (true) {
		current = getNext(zahlen, n);

		if (power(current, 2) > n) {
			break;
		}

		for (int i = power(current, 2); i <= n; i += current) {
			// Markiere als Vielfaches der aktuellen Zahl (current)
			zahlen[i] = 1;
			// Erhoehe die Anzahl von Streichungen
			s++;
		}

		// Markiere die aktuelle Zahl um im naechsten Schleifendurchlauf nicht erneut erkannt zu werden
		zahlen[current] = 1;
		// Erhoehe die Anzahl von gefundenen Primzahlen
		p++;
	}

	// Fuege die restlichen Primzahlen im Array dem Ergebnis hinzu
	for (int i = 0; i <= n; i++) {
		if (zahlen[i] == 0) {
			p++;
		}
	}

	// Freigeben des Speichers
	delete[] zahlen;

	// Rueckgabe der Werte P und S in Form eines Arrays
	int *ergebnis = new int[1];
	ergebnis[0] = p;
	ergebnis[1] = s;
	return ergebnis;
}


void aufgabeb() {
	std::cout.width(8);
	std::cout << std::right << 'i';
	std::cout.width(6);
	std::cout << std::right << 'P';
	std::cout.width(8);
	std::cout << std::right << 'S' << "\n";

	for (int i = 2; i <= 20; i++) {
		int* ergebnis = siebDesEratosthenes(power(2, i));
		std::cout.width(8);
		std::cout << std::right << power(2, i);
		std::cout.width(6);
		std::cout << std::right << ergebnis[0];
		std::cout.width(8);
		std::cout << std::right << ergebnis[1] << "\n";
		delete[] ergebnis;
	}
}


int main()
{
	aufgabeb();
}
