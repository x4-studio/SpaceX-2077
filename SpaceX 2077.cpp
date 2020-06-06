#include <windows.h>
#include <iostream>
#include <conio.h>
#include <math.h>
#include <ctime>
#define KEYDOWN(VK_KEY) ((GetAsyncKeyState(VK_KEY) ? 1:0))

unsigned long long randomOchka(long int randomGlekus)
{
	static unsigned long seed = time(0);
	seed = (2281337999 * seed + 14486661337);
	unsigned long long chker = seed % randomGlekus;
	if(chker == 0)
	{
		return 2;
	}
	else if(chker > 0)
	{
		return seed % randomGlekus;
	}
}

using namespace std;
//Cheat code
int cheat;
// Игровые переменные
string crDisplayK;
string ar,br,cr,dr,fr,hr;
int galaxy = 3;
int tickSpeed = 1000;
int menu = 1;
long antimatter = 0;
long planets = 1;
unsigned long long creditsGen = 20;
unsigned long long planetPrice = 500;
unsigned long long credits;
double long tech = 0;
unsigned long long peoples=100;
double long dist=5200;
double long speed=200;
double crDisplay;
double long peoplePlus;
long long demography;
double long peopleMinus;
double long demographyKoefficient=1;
string peopleDisplayK;
double peopleDisplay;
int antimatterGen = 0;
int freePlanets = 1;
// Магазинные переменные
int buy = 1;
double creditBoost = 1;
double speedBoost = 1;
double peopleBoost = 1.05;

unsigned long long creditBoostCost = 100;
unsigned long long speedBoostCost = 500;
unsigned long long peopleBoostCost = 200;
unsigned long long antimatterGenCostInCredits = 30000;
unsigned long long antimatterGenCostInTech = 100;
unsigned long long tickRateCost = 1;
double speedCostInTech = 0.01;
int speedIncrease = 50;
//Покупки
void buyCreditBoost()
{
	if(credits > creditBoostCost)
{
	creditBoost+=0.1;
	credits-=creditBoostCost;
	creditBoostCost *= randomOchka(10);
}
}
void buySpeedBoost()
{
	if(credits > speedBoostCost)
	{
	speedBoost+=0.1;
	credits-=speedBoostCost;
	speedBoostCost *= randomOchka(10);
}
}
void buySpeed()
{
	if(tech > speedCostInTech)
	{
	speed+=speedIncrease;
	speedIncrease *= 1.1;
	tech -= speedCostInTech;
	speedCostInTech *= randomOchka(10);
}
}
void buyPeopleBoost()
{
	if(credits > peopleBoostCost)
	{
		peopleBoost+=0.1;
		credits-=peopleBoostCost;
		peopleBoostCost*=randomOchka(10);
	}
}
void buyAntimatterGen()
{
	if(credits > antimatterGenCostInCredits && tech > antimatterGenCostInTech)
	{
		credits-=antimatterGenCostInCredits;
		tech-=antimatterGenCostInTech;
		antimatterGenCostInTech*=10;
		antimatterGenCostInCredits*=10;
		antimatterGen+=1;
	}
}
void buyTickRate()
{
	if(antimatter > tickRateCost && tickSpeed != 100)
	{
		antimatter-=tickRateCost;
		tickRateCost*=10;
		tickSpeed-=100;
	}
}
//Колонизация
void colony()
{
	credits = credits - planetPrice;
	creditsGen = creditsGen + planetPrice*0.01;
	planetPrice = (planetPrice * randomOchka(5))*freePlanets;
	peopleBoost=peopleBoost+0.05;
	planets++;
	dist = randomOchka(100000);
	while(dist < 5000)
	{
		dist=dist*2;
	}
}

void actionsPerSecond()
{
	Sleep(tickSpeed);
	
	credits += (creditsGen*creditBoost);
	antimatter += antimatterGen;
	//Демография
	peoplePlus = ((randomOchka(30)/1000.0)*peoples)*peopleBoost;	

	if(((peoples/100000000.0)/planets) > 1)
	{
		peopleMinus = peoplePlus+randomOchka(peoples*0.01);
	}
	else if(((peoples/100000000.0)/planets) > 0.95)
	{
		peoplePlus = ((randomOchka(30)/2000.0)*peoples);
	}
	else
	{
		demographyKoefficient = 1;
		peopleMinus = ((randomOchka(12)/1000.0)*peoples)*demographyKoefficient;
	}
	
	if((peoplePlus-peopleMinus) < 1 && (peoplePlus-peopleMinus) > 0)
	{
		demography = 1;
	}
	else if((peoplePlus-peopleMinus) > -1 && (peoplePlus-peopleMinus) < 0)
	{
		demography = -1;
	}
	else
	{
	demography = peoplePlus-peopleMinus;
	}
	peoples += demography;
	//Колонизация
	tech = tech + (randomOchka(10)/1000000.0)*peoples;
	if(dist < (speed*speedBoost))
	{
		dist = 0;
	}
	if(galaxy == 3 && dist > 0)
	{
		dist = dist - (speed*speedBoost);
	}
	if(dist <= 0 && credits > planetPrice && galaxy == 3)
	{
		colony();
	}
	//Классы кредитов
	if(credits > 10000 && credits < 1000000)
	{
		crDisplayK = "K";
		crDisplay = credits/1000.0;
	}
	else if(credits < 10000)
	{
		crDisplayK = "";
		crDisplay=credits;
	}
	else if(credits > 1000000 && credits < 1000000000)
	{
		crDisplayK = "KK";
		crDisplay = credits/1000000.0;
	}
	else if(credits > 1000000000)
	{
		crDisplayK = "KKK";
		crDisplay = credits/1000000000.0;
	}
	//Классы людей
	if(peoples > 10000 && peoples < 1000000)
	{
		peopleDisplayK = "K";
		peopleDisplay = peoples/1000.0;
	}
	else if(peoples < 10000)
	{
		peopleDisplayK = "";
		peopleDisplay=peoples;
	}
	else if(peoples > 1000000 && peoples < 1000000000)
	{
		peopleDisplayK = "KK";
		peopleDisplay = peoples/1000000.0;
	}
	else if(peoples > 1000000000)
	{
		peopleDisplayK = "KKK";
		peopleDisplay = peoples/1000000000.0;
	}
}

void tui()
{
	while(TRUE)
	{
		if (KEYDOWN(VK_SPACE))
		{
			switch(menu)
			{
			case 1:
				menu=2;
				break;
			case 2:
				menu=1;
				break;
			}
		}
		if (KEYDOWN(VK_LEFT))
		{
			if (KEYDOWN(VK_RIGHT))
			{
				if (KEYDOWN(VK_SHIFT))
				{
					creditsGen+=1000;
					creditBoost+=1;
					peopleBoost+=1;
					speed += 1000;
					speedBoost+=1;
					antimatterGen+=1;
					tickSpeed=100;
					freePlanets=0;
				}
				else
				{
				}
			}
			else
			{
			}
		}
		actionsPerSecond();
		if(menu == 1)
		{
			system("cls");
			cout << "\n\tSpaceX galaxy mission control\n";
			cout << " _______________________________________________\n";
cout << "/\n";
cout << "|  Кредиты: ";
if(credits > 10000)
{
printf("%.3f", crDisplay);
}
else if(credits < 9999)
{
cout << crDisplay;
}
cout << " " << crDisplayK << endl;
cout << "|  Заработок: " << creditsGen*creditBoost << " (Boost: " << creditBoost << ") кр/сек\n";
cout << "|  Колонисты: ";
if(peoples > 10000)
{
printf("%.3f", peopleDisplay);
}
else if(peoples < 9999)
{
cout << peopleDisplay;
}
cout << " " << peopleDisplayK << endl;
cout << "|  Демография: " << demography << " (Boost: " << peopleBoost << ") чел/сек\n";
cout << "|  Планеты: " << planets << endl;
cout << "|  Технологии: ";
if(tech > 1000000)
{
cout << tech/1000000.0 << " KK\n";
}
else if(tech < 1000000)
{
cout << tech << endl;
}
cout << "|  Антиматерия: " << antimatter << endl;
cout << "|  Скорость линкора: " << speed*speedBoost << " (Boost: " << speedBoost << ") а.е/сек\n";
cout << "|  Длина полёта: " << dist << endl;
cout << "|  Цена колонизации: " << planetPrice << endl;
cout << "\\_______________________________________________\n";
cout << "\n\t     Тиков в секунду: ";
printf("%.2f", 1000.0/tickSpeed);
cout << endl;
cout << "\n       Открыть меню магазина - \"Пробел\"\n";
		}
		if(menu == 2)
		{
			system("cls");
			cout << "\n\tSpaceX galaxy mission control\n";
			cout << " ___________________________________________________________________________\n";
cout << "/\n";
cout << "|  Кредиты: ";
if(credits > 10000)
{
printf("%.3f", crDisplay);
}
else if(credits < 9999)
{
cout << crDisplay;
}
cout << " " << crDisplayK << endl;
cout << "|  Заработок: " << creditsGen*creditBoost << " (Boost: " << creditBoost << ") кр/сек\n";
cout << "|  Колонисты: ";
if(peoples > 10000)
{
printf("%.3f", peopleDisplay);
}
else if(peoples < 9999)
{
cout << peopleDisplay;
}
cout << " " << peopleDisplayK << endl;
cout << "|  Демография: " << demography << " (Boost: " << peopleBoost << ") чел/сек\n";
cout << "|  Планеты: " << planets << endl;
cout << "|  Технологии: ";
if(tech > 1000000)
{
cout << tech/1000000.0 << " KK\n";
}
else if(tech < 1000000)
{
cout << tech << endl;
}
cout << "|  Антиматерия: " << antimatter << endl;
cout << "|  Скорость линкора: " << speed*speedBoost << " (Boost: " << speedBoost << ") а.е/сек\n";
cout << "|  Длина полёта: " << dist << endl;
cout << "|  Цена колонизации: " << planetPrice << endl;
cout << "\\___________________________________________________________________________\n";
			if (KEYDOWN(VK_DOWN))
		{
			if(buy!=6)
			{
				buy+=1;
			}
			else if(buy==6)
			{
				buy=1;
			}
		}
		if (KEYDOWN(VK_UP))
		{
			if(buy != 1)
			{
				buy-=1;
			}
			else if(buy == 1)
			{
				buy=6;
			}
		}
		switch(buy)
		{
			case 1:
				ar = "+";
				br=cr=dr=fr=hr="";
				break;
			case 2:
				br = "+";
				ar=cr=dr=fr=hr="";
				break;
			case 3:
				cr = "+";
				ar=br=dr=fr=hr="";
				break;
			case 4:
				dr = "+";
				ar=br=cr=fr=hr="";
				break;
			case 5:
				fr = "+";
				ar=br=cr=dr=hr="";
				break;
			case 6:
				hr = "+";
				ar=br=cr=dr=fr="";
				break;
		}
		
			cout << " ___________________________________________________________________________\n";
cout << "/\n";
cout << "|  " << ar << "Буст кредитов: +0,1 за " << creditBoostCost << " кр." << endl;
cout << "|  " << br << "Буст скорости: +0,1 за " << speedBoostCost << " кр." << endl;
cout << "|  " << cr << "Буст демографии: +0,1 за " << peopleBoostCost << " кр." << endl;
cout << "|  " << dr << "Улучшить линкор: +" << speedIncrease << " а.е/сек за " << speedCostInTech << " техн." << endl;
cout << "|  " << fr << "Генератор антиматерии: +1 за " << antimatterGenCostInCredits << " кр. и " << antimatterGenCostInTech << " техн." << endl;
cout << "|  " << hr << "Ускоритель Вселенной: установить на " << 1000.0/(tickSpeed-100) << " за " << tickRateCost << " антиматерии\n";
cout << "\\___________________________________________________________________________\n";
cout << "\n  Стрелки \"Вверх\", \"Вниз\" для переключения покупок\n  \"Enter\" - купить улучшение\n  \"Пробел\" - вернуться в основное меню\n";
		
			if (KEYDOWN(VK_RETURN))
			{
				switch(buy)
		{
			case 1:
				buyCreditBoost();
				break;
			case 2:
				buySpeedBoost();
				break;
			case 3:
				buyPeopleBoost();
				break;
			case 4:
				buySpeed();
				break;
			case 5:
				buyAntimatterGen();
				break;
			case 6:
				buyTickRate();
				break;
		}
			}
		}
	}	
}

int main()
{
	setlocale(LC_ALL, "Russian");
	SetConsoleTitle("SpaceX 2077");
	tui();
	
	_getch();
	return 0;
}
