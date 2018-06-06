#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>

void inicjuj(char **tablica, int const rozmiar) {
    for (int i = 0; i < rozmiar; i++) {
        for (int j = 0; j < rozmiar; j++) {
            tablica[i][j] = ' ';
        }
    }
}

bool czyZostalRuch(char **tablica, int const rozmiar) {
    for (int i = 0; i < rozmiar; i++) {
        for (int j = 0; j < rozmiar; j++) {
            if (tablica[i][j] == ' ') {
                return true;
            }
        }
    }
    return false;
}

void rysuj(char **tablica, int const rozmiar) {
    std::cout << "Plansza:  " << std::endl;
    for (int i = 0; i < rozmiar; i++) {
        for (int j = 0; j < rozmiar; j++) {
            std::cout << "|" << "     " << tablica[i][j];
        }
        std::cout << "|";
        std::cout << std::endl;
        for (int a = 0; a < rozmiar; a++) {
            std::cout << "-------";
        }
        std::cout << std::endl;
    }
}

int stanGry(char **tablica, int const rozmiar) {
    int iloscX = 0;
    int iloscO = 0;

    for (int i = 0; i < rozmiar; i++) {
        iloscX = 0;
        iloscO = 0;
        for (int j = 0; j < rozmiar; j++) {
            if (tablica[i][j] == 'X') {
                iloscX++;
            } else if (tablica[i][j] == 'O') {
                iloscO++;
            }
            if (iloscX == rozmiar) {
                return 10;
            } else if (iloscO == rozmiar) {
                return -10;
            }
        }
    }
    for (int i = 0; i < rozmiar; i++) {
        iloscX = 0;
        iloscO = 0;
        for (int j = 0; j < rozmiar; j++) {
            if (tablica[j][i] == 'X') {
                iloscX++;
            } else if (tablica[j][i] == 'O') {
                iloscO++;
            }
            if (iloscX == rozmiar) {
                return 10;
            } else if (iloscO == rozmiar) {
                return -10;
            }
        }
    }
    iloscX = 0;
    iloscO = 0;
    for (int i = 0; i < rozmiar; i++) {
        if (tablica[i][i] == 'X') {
            iloscX++;
        } else if (tablica[i][i] == 'O') {
            iloscO++;
        }
    }
    if (iloscX == rozmiar) {
        return 10;
    } else if (iloscO == rozmiar) {
        return -10;
    }
    int i = 0;
    int j = 0;
    iloscX = 0;
    iloscO = 0;
    for (i = 0, j = rozmiar - 1; i < rozmiar; i++, j--) {
        if (tablica[i][j] == 'X') {
            iloscX++;
        } else if (tablica[i][j] == 'O') {
            iloscO++;
        }
    }
    if (iloscX == rozmiar) {
        return 10;
    } else if (iloscO == rozmiar) {
        return -10;
    }
    return 0;
}

int miniMax(char **tablica, int glebokosc, bool czyMax, int const rozmiar, int alfa, int beta) {
    int wynik = stanGry(tablica, rozmiar);
    if (wynik == 10) {
        return wynik;
    }
    if (wynik == -10) {
        return wynik;
    }
    if (!czyZostalRuch(tablica, rozmiar)) {
        return 0;
    }
    if (glebokosc == 7) {
        return 0;
    }
    if (czyMax) {
        int najlepsze = -1000;
        for (int i = 0; i < rozmiar; i++)
            for (int j = 0; j < rozmiar; j++) {
                if (tablica[i][j] == ' ') {
                    tablica[i][j] = 'X';
                    najlepsze = std::max(najlepsze, miniMax(tablica, glebokosc + 1, !czyMax, rozmiar, alfa, beta));
                    tablica[i][j] = ' ';
                    alfa = std::max(alfa, najlepsze);
                    if (beta <= alfa) {
                        break;
                    }
                }

            }
        return najlepsze;
    } else {
        int najlepsze = 1000;
        for (int i = 0; i < rozmiar; i++) {
            for (int j = 0; j < rozmiar; j++) {
                if (tablica[i][j] == ' ') {
                    tablica[i][j] = 'O';
                    najlepsze = std::min(najlepsze, miniMax(tablica, glebokosc + 1, !czyMax, rozmiar, alfa, beta));
                    tablica[i][j] = ' ';
                    beta = std::min(beta, najlepsze);
                    if (beta <= alfa) {
                        break;
                    }
                }
            }
        }
        return najlepsze;
    }
}

void ruchKomputera(char **tablica, int const rozmiar) {
    int wartosc = -1000;
    int kolumny = -1;
    int wiersze = -1;
    for (int i = 0; i < rozmiar; i++) {
        for (int j = 0; j < rozmiar; j++) {
            if (tablica[i][j] == ' ') {
                tablica[i][j] = 'X';
                int tempVal = miniMax(tablica, 0, false, rozmiar, -1000, 1000);
                tablica[i][j] = ' ';
                if (tempVal > wartosc) {
                    kolumny = i;
                    wiersze = j;
                    wartosc = tempVal;
                }
            }
        }
    }
    tablica[kolumny][wiersze] = 'X';
}

int dostepnoscPola(char **tablica, int pole, int const rozmiar) {
    int miejsce = 0;
    for (int i = 0; i < rozmiar; i++) {
        for (int j = 0; j < rozmiar; j++) {
            miejsce++;
            if (miejsce == pole && tablica[i][j] == ' ') {
                return 1;
            }
        }
    }
    return -1;
}

void wprowadz(char **tablica, char znak, int const rozmiar) {
    int pole = 1;
    int ruch = 0;
    int miejsceposadzenia = 0;

    while (ruch != 10) {
        ruch++;
        if (ruch == rozmiar * rozmiar && stanGry(tablica, rozmiar) == 0) {
            rysuj(tablica, rozmiar);
            std::cout << "Remis" << std::endl;
            break;
        }
        if (znak == 'O') {
            znak = 'X';
            ruchKomputera(tablica, rozmiar);
            rysuj(tablica, rozmiar);
            if (stanGry(tablica, rozmiar) == 10) {
                std::cout << "Porazka" << std::endl;
                break;
            }
            if (stanGry(tablica, rozmiar) == -10) {
                std::cout << "Zwyciestwo" << std::endl;
                break;
            }
            continue;
        } else if (znak == 'X') {
            znak = 'O';
            std::cout << "Wprowadz pole: " << std::endl;
            std::cin >> pole;
            while (dostepnoscPola(tablica, pole, rozmiar) == -1) {
                std::cout << "Pole zajete! Popraw: " << std::endl;
                std::cin >> pole;
            }
            for (int i = 0; i < rozmiar; i++) {
                for (int j = 0; j < rozmiar; j++) {
                    miejsceposadzenia++;
                    if (miejsceposadzenia == pole) {
                        tablica[i][j] = znak;
                        rysuj(tablica, rozmiar);
                    }
                }
            }
            miejsceposadzenia = 0;
        }
    }
}

int main() {
    char znak;
    int rozmiar = 0;

    std::cout << "Podaj rozmiar planszy: " << std::endl;
    std::cin >> rozmiar;
    if (rozmiar >= 0 && rozmiar < 3) {
        std::cout << "Rozmiar nieprawidlowy" << std::endl;
        return 0;
    }
    auto **tablica = new char *[rozmiar];
    for (int i = 0; i < rozmiar; i++) {
        tablica[i] = new char[rozmiar];
    }
    std::cout << "Ty zaczynasz? (t/n): " << std::endl;
    std::cin >> znak;
    while (znak != 'T' && znak != 't' && znak != 'N' && znak != 'n') {
        std::cout << "Zly znak. Popraw!: " << std::endl;
        std::cin >> znak;
    }
    if (znak == 'T' || znak == 't') {
        znak = 'X';
        inicjuj(tablica, rozmiar);
        wprowadz(tablica, znak, rozmiar);
    } else if (znak == 'N' || znak == 'n') {
        znak = 'O';
        inicjuj(tablica, rozmiar);
        wprowadz(tablica, znak, rozmiar);
    }
    return 0;
}
