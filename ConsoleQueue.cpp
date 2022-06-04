// ConsoleQueue.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "busstop.h"

int main()
{
	char c;
	setlocale(LC_ALL, "Russian");
	std::cout << "Параметры модели задаются случайно";

//	std::cin >> c;

	//if (c=='Y') 
	busstop *b= busstop::busstoprandom(50);

	std::cout << *b;
	//return 0;
	std::cout << "\nНачало работы модели\n";
	
	int intervalPass;
	int intervalBus;

	int currentIntPass = 0;
	int currentIntBus = 0;
	for (int hour = 0; hour < 24; hour++)
	{
		intervalPass = b->getIntervalPass(hour);
		intervalBus = b->getIntervalBus(hour);

		for (int min = 0; min <  60; min++)
		{
			if (++currentIntPass > intervalPass)
			{
				if (!b->addPass(1,hour,min)) std::cout<<" ВРЕМЯ: "<<hour<<":"<<min<<"\t ОСТАНОВКА ПЕРЕПОЛНЕНА.\n";
				else std::cout << " ВРЕМЯ: " << hour << ":" << min << "\t Подошел ПАССАЖИР. На остановке пассажиров = "<<b->CountPassOnStopBus()<<"\n";
				currentIntPass = 0;
			}
			if (++currentIntBus > intervalBus)
			{ 
				int nPassInbus = rand() % b->getMaxInBusPass();

				int i=0;
				
				while (b->removePass(1, hour, min))
				{   
					if (++i >=nPassInbus)break;
				}
				currentIntBus = 0;

				std::cout << " ВРЕМЯ: " << hour << ":" << min << "\t Подошел АВТОБУС(Св.мест="<<nPassInbus<<").Забрал " << i<<" пассажиров. На остановке пассажиров = " << b->CountPassOnStopBus() << "\n";
			}
		}
	}
	b->setRunModel(true);

	std ::cout << *b;
}
