#include <iostream>
#include <random>
using namespace std;



class Plansza {
private:
	
protected:



public:

	int** plansza = new int* [szerokosc];
	char** ukryta_plansza = new char* [szerokosc];
	char** widoczna_plansza = new char* [szerokosc];
	int wysokosc;
	int szerokosc;
	void stworz();
	void przetworz_ukryta();
	void przetworz_widoczna();
	void pokaz(char komu);
	int modyfikuj_plansze(int x, int y, int wartosc);
	int sprawdz(int x, int y);

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

class Statki : protected Plansza {
private:
	int* statki = new int[5];
public:
	int pozostalo;
	Plansza* p;
	void pokaz() {
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
	int strzelaj();
	void rozstaw();
	int wielomasztowiec(int x, int y, int m, char wybor); // sprawdzenie czy nie ma kolidacji na drodze statku
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




// nie mialem czasu dodac funkcji grania z komputrem
class RandomGenerator {
public:
	RandomGenerator(int min, int max) : dist_(min, max) {}

	int GenerateInt() {
		cout << dist_(gen_) << endl;
		return dist_(gen_);
	}

private:
	std::mt19937 gen_{ std::random_device{}() };
	std::uniform_int_distribution<> dist_;

};



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
				printf(" %d ", plansza[i][j]);
			if (komu == 'p')
				printf(" %c ", ukryta_plansza[i][j]);
			if (komu == 's')
				printf(" %c ", widoczna_plansza[i][j]);
			if (i == szerokosc - 1)
				printf("| %d\n", j);
		}
	printf("  ");
	for (int i = 0; i < szerokosc; i++)
		printf("---");
	printf("  y\n\n");
};



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

int Plansza::sprawdz(int x, int y)
{

	if (x >= szerokosc || y >= wysokosc || y < 0 || x < 0)
	{
		printf("Wyszedles poza plansze, sprobuj jeszcze raz\n");
		return 9;
	}
	if (plansza[x][y] == 0)
		return 0;
	if (plansza[x][y] == 1)
		return 1;
	if (plansza[x][y] == 2)
		return 2;
	if (plansza[x][y] == 3)
		return 3;
	if (plansza[x][y] == 4)
		return 4;
	if (plansza[x][y] == 5)
		return 5;
	if (plansza[x][y] == 6)
		return 6;
	if (plansza[x][y] == 7)
		return 7;
	if (plansza[x][y] == 8)
		return 8;
	else
		return 10;

}
int Plansza::modyfikuj_plansze(int x, int y, int wartosc)
{
	plansza[x][y] = wartosc;
	return 0;
}


int Statki::strzelaj()
{
	int x;
	int y;
	int sprawdz = 9;
	while (sprawdz != 0)
	{
		printf("W jakie pole chcesz strzelic? \nWspolrzedna x : ");
		scanf_s("%d", &x);
		printf("Wspolrzedna y: ");
		scanf_s("%d", &y);
		sprawdz = p->sprawdz(x, y);
		if (sprawdz == 8 || sprawdz == 6)
			printf("Juz tu strzelales, sprobuj jeszcze raz\n");
		if (sprawdz == 1)
			break;
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
int Statki::wielomasztowiec(int x, int y, int m, char wybor)
{
	char W = wybor;
	int M = m;
	int X = x;
	int Y = y;

	while (M > 1)
	{
		M = M - 1;
		switch (W)
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
					continue;
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
	}
	~Game()
	{
		delete player1;
		delete player2;
		printf("Gra zostala zakonczona\n");
	}
};

void Game::start() {
	player1 = new Statki(szerokosc, wysokosc, s1, s2, s3, s4, s5);
	player2 = new Statki(szerokosc, wysokosc, s1, s2, s3, s4, s5); 
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

int main()

{	

	Game* game;
	//game = new Game(10, 10, 1, 1, 0, 2, 0);
	game = new Game();
	game->start();
	game->graj();
	delete game;
	return 0;
}

