#include <iostream>
#include <random> //ostatecznie nie uzylem do niczego tej biblioteki.
using namespace std;


//klasa odpowiedzialna za tworzenie planszy, generowanie ich, wprowadzanie na nich zmian i wyswietlanie ich (ogolnie obsluga plansz)
class Plansza {
public:

	int** plansza = new int* [szerokosc];	//plansza podstawowa, na ktorej sa generowane ponizsze 2 plansze
	char** ukryta_plansza = new char* [szerokosc];	// plansza dla przeciwnika
	char** widoczna_plansza = new char* [szerokosc];	//plansza dla gracza
	int wysokosc;	//planszy
	int szerokosc;	//planszy
	void stworz();	//tworzenie planszy ( tablic dwuwymiarowych i przypisywanie im domyslnych wartosci ( 0 lub - )
	void przetworz_ukryta();	//edycja planszy
	void przetworz_widoczna();	//edycja planszy
	void pokaz(char komu);	//pokazywanie planszy na ekranie
	int sprawdz(int x, int y);	// sprawdzenie wartosci na planszy w miejscu danych wspolrzednych
	int modyfikuj_plansze(int x, int y, int wartosc);	// edycja planszy

	Plansza()
	{
		this->szerokosc = 10;
		this->wysokosc = 10;
		printf("Plansza zostala stworzona\n");

	}
	Plansza(int x, int y)
	{
		this->szerokosc = x;
		this->wysokosc = y;
		printf("Plansza zostala stworzona\n");
	}
	virtual ~Plansza()
	{
		printf("Plansze zostaly usuniete\n");
	};

};


//klasa tworzaca obiekt na klasie plansza, odpowiedzialna za rozstawianie statkow i strzelanie
class Statki : protected Plansza {
private:
	int* statki = new int[5];	// tablica przechowujaca ilosci poszczegolnych statkow
public:
	int pozostalo;	//liczba pozostalych statkow gracza 
	Plansza* p;		//tworzenie obiektu na klasie plansza
	void pokaz() {	// pokazanie planszy w formacie liczbowym
		p->pokaz('l');
	}
	void pokaz_przeciwnikowi() {
		p->przetworz_ukryta();
		printf("\nPrzeciwnikowi pozostalo %d masztow sumujac wszystkie statki\n", pozostalo);
		p->pokaz('p');
	}
	void pokaz_sobie()
	{
		p->przetworz_widoczna();
		p->pokaz('s');
	}
	void rozstaw();	//obsluga rozstawiania statkow
	int wielomasztowiec(int x, int y, int m, char wybor); // sprawdzenie czy nie ma kolidacji na drodze statku
	int strzelaj();	//obsluga strzalow
	Statki()
	{
		p = new Plansza();
		p->stworz();
		statki[0] = 1;
		statki[1] = 1;
		statki[2] = 1;
		statki[3] = 1;
		statki[4] = 1;
		printf("Statki zostaly stworzone\n");
		pozostalo = 0;

	}
	Statki(int x, int y, int s1, int s2, int s3, int s4, int s5)
	{

		p = new Plansza(x, y);
		p->stworz();
		statki[0] = s1;
		statki[1] = s2;
		statki[2] = s3;
		statki[3] = s4;
		statki[4] = s5;
		pozostalo = 0;
		printf("Statki zostaly stworzone\n");

	}
	~Statki()
	{
		printf("Statki zostaly usuniete\n");
	}

};


// nie mialem czasu dodac funkcji grania z kompuWtrem, po to zostawilem ta klase (wykorzystam ja w przyszlosci)
class RandomGenerator {
public:
	RandomGenerator(int min, int max) : dist_(min, max) {}

	int GenerateInt() {
		cout << dist_(gen_) << endl;
		return dist_(gen_);
	}

private:
	mt19937 gen_{ random_device{}() };
	uniform_int_distribution<> dist_;

};


//klasa odpowiedzialna za obsluge calej gry
class Game {
private:
	int szerokosc;
	int wysokosc;
	int s1, s2, s3, s4, s5;

public:
	Statki* player1;
	Statki* player2;
	void start();
	void graj();
	Game()
	{
		printf("Gra zostala rozpoczeta\n");
		printf("Podaj rozmiary planszy\nszerokosc: ");
		scanf_s("%d", &szerokosc);
		printf("wysokosc: ");
		scanf_s("%d", &wysokosc);
		printf("Podaj ilosci statkow \nJednomasztowych: ");
		scanf_s("%d", &s1);
		printf("Dwumasztowych: ");
		scanf_s("%d", &s2);
		printf("Trzymasztowych: ");
		scanf_s("%d", &s3);
		printf("Czteromasztowych: ");
		scanf_s("%d", &s4);
		printf("Pieciomasztowych: ");
		scanf_s("%d", &s5);
		player1 = new Statki(szerokosc, wysokosc, s1, s2, s3, s4, s5);
		player2 = new Statki(szerokosc, wysokosc, s1, s2, s3, s4, s5);


	}
	Game(int x, int y, int st1, int st2, int st3, int st4, int st5)
	{
		szerokosc = x;
		wysokosc = y;
		s1 = st1;
		s2 = st2;
		s3 = st3;
		s4 = st4;
		s5 = st5;
		player1 = new Statki(szerokosc, wysokosc, s1, s2, s3, s4, s5);
		player2 = new Statki(szerokosc, wysokosc, s1, s2, s3, s4, s5);
	}
	~Game()
	{
		delete player1;
		delete player2;
		printf("Gra zostala zakonczona\n");
	}
};

void Game::start() {
//	player1 = new Statki(szerokosc, wysokosc, s1, s2, s3, s4, s5);
//	player2 = new Statki(szerokosc, wysokosc, s1, s2, s3, s4, s5);
	printf("\n\nPlansza gracza nr 1:\n");
	player1->pokaz();
	printf("Plansza gracza nr 2:\n");
	player2->pokaz();
	printf("Graczu numer 1, rozstaw swoje statki\n");
	player1->rozstaw();
	printf("\n\n\n\n\n\n\n\nGraczu numer 2, rozstaw swoje statki\n");
	player2->rozstaw();
	printf("\n");

}

void Game::graj() {
	while (player1->pozostalo != 0)
	{
		printf("\n\n\nKolejka gracza nr 1");
		player2->pokaz_przeciwnikowi();
		player2->strzelaj();
		if (player2->pozostalo == 0)
		{
			printf("\n\nGracz numer 1 wygral!!!\n\n");
			break;
		}
		printf("\n\n\nKolejka gracza nr 2");
		player1->pokaz_przeciwnikowi();
		player1->strzelaj();
	}
	if (player1->pozostalo == 0)
		printf("\n\nGracz numer 2 wygral!!!\n\n");
}

void Plansza::stworz()
{

	//plansza bazowa (w formacie liczbowym) - w niej sa przechowywane dane planszy
	for (int i = 0; i < szerokosc; i++)
		this->plansza[i] = new int[wysokosc];

	for (int i = 0; i < szerokosc; i++)
		for (int j = 0; j < wysokosc; j++)
			this->plansza[i][j] = 0;

	//plansza pokazywana przeciwnikowi
	for (int i = 0; i < szerokosc; i++)
	{
		this->ukryta_plansza[i] = new char[wysokosc];
		this->widoczna_plansza[i] = new char[wysokosc];
	}

	for (int i = 0; i < szerokosc; i++)
		for (int j = 0; j < wysokosc; j++)
		{
			ukryta_plansza[i][j] = '-';
			widoczna_plansza[i][j] = '-';
		}
}


// pokazanie planszy
void Plansza::pokaz(char komu)
{
	printf("\n x");
	for (int i = 0; i < szerokosc; i++)
		if (i < 10)
			printf(" %d ", i);
		else
			printf("%d ", i);
	printf("x \n  ");
	for (int i = 0; i < szerokosc; i++)
		printf("---");
	printf("  y\n");


	for (int j = 0; j < wysokosc; j++)
		for (int i = 0; i < szerokosc; i++)
		{
			if (i == 0)
				printf(" |");
			if (komu == 'l')
				printf(" %d ", plansza[i][j]);	// pokazanie pola planszy w formacie liczbowym ( z jawnymi wartosciami kazdego pola)
			if (komu == 'p')
				printf(" %c ", ukryta_plansza[i][j]);	// pokazanie pola planszy w formacie znakowym dla przeciwnika
			if (komu == 's')
				printf(" %c ", widoczna_plansza[i][j]);	// pokazanie pola planszy w formacie znakowym dla gracza ( przy ustawianiu statkow )
			if (i == szerokosc - 1)
				printf("| %d\n", j);
		}
	printf("  ");
	for (int i = 0; i < szerokosc; i++)
		printf("---");
	printf("  y\n\n");
};


// przetworzenie planszy z planszy liczbowej na widok dla przeciwnika
void Plansza::przetworz_ukryta()
{

	for (int i = 0; i < szerokosc; i++)
		for (int j = 0; j < wysokosc; j++)
		{
			if (this->plansza[i][j] == 6)
				ukryta_plansza[i][j] = 'X';		//wtrafione
			if (this->plansza[i][j] == 8)
				ukryta_plansza[i][j] = 'o';		//pudlo
		}
}

// przetworzenie planszy z planszy liczbowej na widok dla gracza
void Plansza::przetworz_widoczna()
{

	for (int i = 0; i < szerokosc; i++)
		for (int j = 0; j < wysokosc; j++)
		{
			if (this->plansza[i][j] == 1)
				widoczna_plansza[i][j] = 'O';
			if (this->plansza[i][j] == 2)
				widoczna_plansza[i][j] = '2';	
			if (this->plansza[i][j] == 3)
				widoczna_plansza[i][j] = '3';
			if (this->plansza[i][j] == 4)
				widoczna_plansza[i][j] = '4';
			if (this->plansza[i][j] == 5)
				widoczna_plansza[i][j] = '5';
			if (this->plansza[i][j] == 6)
				widoczna_plansza[i][j] = 'X';
		}
}

//sprawdzanie planszy w miejscu przekazanych wspolrzednych
int Plansza::sprawdz(int x, int y)
{
	if (x >= szerokosc || y >= wysokosc || y < 0 || x < 0)	//porownanie z rozmiarem planszy
	{
		printf("Wyszedles poza plansze, sprobuj jeszcze raz\n");
		return 9;
	}
	if (plansza[x][y] == 0)	// puste pole, bez statku
		return 0;
	if (plansza[x][y] == 1)	// statek
		return 1;
	if (plansza[x][y] == 2)	// przy stawianiu statkow - statek 2 masztowy
		return 2;
	if (plansza[x][y] == 3)	// przy stawianiu statkow - statek 3 masztowy
		return 3;
	if (plansza[x][y] == 4)	// przy stawianiu statkow - statek 4 masztowy
		return 4;
	if (plansza[x][y] == 5)	// przy stawianiu statkow - statek 5 masztowy
		return 5;
	if (plansza[x][y] == 6)	// wtrafiony statek
		return 6;
	if (plansza[x][y] == 7)
		return 7;
	if (plansza[x][y] == 8)	// pudlo (wtrafione puste pole)
		return 8;
	else
		return 10;

}

//wprowadzanie zmian na planszy, brak obslugi bledow poniewaz kazda zmiana jest najpierw sprawdzana przez funkcje Plansza:sprawdz()
int Plansza::modyfikuj_plansze(int x, int y, int wartosc)
{
	plansza[x][y] = wartosc;
	return 0;
}

//obsluga strzelania
int Statki::strzelaj()
{
	int x;
	int y;
	int sprawdz = 9;
	while (sprawdz != 0) // 0 - puste pole
	{
		printf("W jakie pole chcesz strzelic? \nWspolrzedna x : ");
		scanf_s("%d", &x);
		printf("Wspolrzedna y: ");
		scanf_s("%d", &y);
		sprawdz = p->sprawdz(x, y);
		if (sprawdz == 8 || sprawdz == 6)
			printf("Juz tu strzelales, sprobuj jeszcze raz\n");
		if (sprawdz == 1) 
			break; // 1 - statek
	}
	if (sprawdz == 1)
	{
		p->modyfikuj_plansze(x, y, 6);
		pokaz_przeciwnikowi();
		printf("\nWtrafiony!\n");
		pozostalo--;
		if (pozostalo != 0)
			strzelaj();
	}
	if (sprawdz == 0)
	{
		p->modyfikuj_plansze(x, y, 8);
		pokaz_przeciwnikowi();
		printf("\nPudlo!\n");
	}

	return 0;
}

// funkcja odpowiedzialna za rozstawianie wielomasztowcow (sprawdzanie czy nie ma konfliktow, statkow na drodze albo czy nie wychodzi poza plansze)
int Statki::wielomasztowiec(int x, int y, int m, char wybor)
{
	char W = wybor;
	int M = m;	// ilo masztowy statek
	int X = x;
	int Y = y;

	while (M > 1)
	{
		M = M - 1;
		switch (W)	// kierunek rozstawienia i inkrementacja odpowiedniej wspolrzednej
		{
		case 'l':
			X--;
			break;
		case 'p':
			X++;
			break;
		case 'g':
			Y--;
			break;
		case 'd':
			Y++;
			break;
		}	
		int result = p->sprawdz(X, Y);
		if (result == 9)
		{
			return 9;
		}
		if (result == 1)
		{
			printf("%d",X);
			printf("Wszedles na inny statek, wybierz inny kierunek\n");
			return 1;
		}
		printf("Sprawdzam wspolrzedna x: %d i wspolrzedna y: %d\n", X, Y);
	}
	return 0;
};

// funkcja odpowiedzialna za rozstawianie statkow
void Statki::rozstaw()
{
	for (int s = 4; s >= 0; s--)
		for (int i = 1; i <= statki[s]; i++)
		{
			int x;
			int y;
			int sprawdz = 1;

			while (sprawdz != 0)
			{
				pokaz_sobie();
				printf("Podaj wspolrzedne dla statku %d masztowego numer %d \n", s + 1, i);
				printf("Wspolrzedna x: ");
				scanf_s("%d", &x);
				printf("Wspolrzedna y: ");
				scanf_s("%d", &y);
				sprawdz = p->sprawdz(x, y);
				if (sprawdz != 0)
				{
					printf("Wybierz inne pole, \n Podglad twojej aktualnej planszy: \n");
				}

			}

			int m = s + 1;
			int kierunek = 1;
			for (m; m >= 1; m--)
			{
				char wybor;
				p->plansza[x][y] = m;
				pokaz_sobie();
				if (m == 1)
				{
					pozostalo++;
					continue;
				}
				printf("w ktora strone chcesz postawic statek?\nlewo - wpisz 'l'\nprawo - wpisz 'p'\ngora - wpisz 'g'\ndol - wpisz 'd'\n");

				while (kierunek != 0)
				{

					scanf_s("%c", &wybor, sizeof(1));
					printf("\n");
					if (wybor == 'l' || wybor == 'g' || wybor == 'p' || wybor == 'd')
						kierunek = wielomasztowiec(x, y, m, wybor);
					else
						printf("Wpisz litere 'l', 'p', 'g' albo 'd'!\n");
				}

				printf("udalo sie\n");
				
				//dodanie statkow do planszy i iteracja pozostalych statkow
				m = s + 1;
				int X = x;
				int Y = y;
				while (m >= 1)
				{
					m = m - 1;
					p->modyfikuj_plansze(X, Y, 1);
					pozostalo++;
					switch (wybor)
					{
					case 'l':
						X--;
						break;
					case 'p':
						X++;
						break;
					case 'g':
						Y--;
						break;
					case 'd':
						Y++;
						break;
					}
				}
			}
		}
};




int main()

{	
	
	Game* game;

	// konstruktor przypisujacy od razu wartosci do zmiennych, kolejno: 
	// szerokosc planszy; wysokosc planszy; statki 1 masztowe; statki 2 masztowe; statki 3 masztowe; statki 4 masztowe; statki 5 masztowe;
	//game = new Game(10, 10, 1, 1, 0, 2, 0);	

	game = new Game();		// konstruktor ktory prosi uzytkownika o podanie rozmiaru planszy i ilosci statkow 
	game->start();
	game->graj();
	delete game;
	return 0;
}

