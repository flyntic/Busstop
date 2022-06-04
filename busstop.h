#pragma once
#include <string>
#include <ctime>
#include <iostream>
//#include <rand>
class busstop
{
	std::string name;
	int IntervalTimePass[24];
	int IntervalTimeBus[24];

	int WaitTimePass[24] = {0};
	int CountTimePass[24] = { 0 };

	int maxQueueOfPass;

	int head;
	int length;
	int maxInBusPass;
	
	struct Pass 
	{
		int hour_in_busstop;
		int min_in_bus_stop;
		int Nbus;
	};
	Pass* QueueOfPass;
	bool runModel=false;
	
public:
	busstop(int* intervalTimePass, int* intervalTimeBus, int maxQueueOfPass = 100, int MaxInBusPass=5) : maxQueueOfPass{ maxQueueOfPass },maxInBusPass{ MaxInBusPass }
	{
		head = 0;
		memcpy(IntervalTimePass, intervalTimePass, 24*sizeof(int));
		memcpy(IntervalTimeBus, intervalTimeBus, 24*sizeof(int));
		memset(CountTimePass, 0, 24);
		memset(WaitTimePass, 0, 24);
		length = 0;
		QueueOfPass = new Pass[maxQueueOfPass];
	}

	static busstop * busstoprandom(int maxQueueOfPass = 100,int minIntPass=2,int maxIntPass=15,int minIntBus=5,int maxIntBus=30)
	{
		int intPass[24];
		int intBus[24];
		std::srand(std::time(0));
		for (int i = 0; i < 24; i++)
		{
			intPass[i] = std::rand() % (maxIntPass - minIntPass) + minIntPass;
			intBus[i] = std::rand() % (maxIntBus - minIntBus) + minIntBus;
		}
		
		return new busstop(&intPass[0], &intBus[0], maxQueueOfPass);

	}

	bool addPass(int Nbus,int hour,int min)
	{
		if (length >= maxQueueOfPass) return false;
		QueueOfPass[length].Nbus = Nbus; //
		QueueOfPass[length].hour_in_busstop = hour;
		QueueOfPass[length].min_in_bus_stop = min;
		length++;
		return true;
	}

	bool removePass(int Nbus,int hour,int min)
	{
		if (length <= 0) return false;
		bool find = false;
		for (int i=0;i<length;i++)
		{
			if ((!find)&& (Nbus == QueueOfPass[i].Nbus))
			{
				find = true;
				WaitTimePass[hour] += hour * 60 + min - QueueOfPass[i].hour_in_busstop * 60 - QueueOfPass[i].min_in_bus_stop;
				CountTimePass[hour]++;
				length--;
			}
			if (find)
			{
				memcpy(&QueueOfPass[i], &QueueOfPass[i + 1],sizeof(Pass));
			}
     	}
		return find;
	}

	int CountPassOnStopBus()
	{
		return length;
	}

	int CountPassOnStopBusForNbus(int Nbus)
	{
		int count = 0;
		for (int i = 0; i < length; i++)
		{
			if (Nbus == QueueOfPass[i].Nbus) count++;
			
		}
		return count;
	}

	int getIntervalPass(int hour)
	{
		return IntervalTimePass[hour];
	}

	int getIntervalBus(int hour)
	{
		return IntervalTimeBus[hour];
	}
	int getMaxInBusPass()
	{
	  return maxInBusPass;
	}
	friend std::ostream& operator<<(std::ostream& out, busstop b)
	{
		if (!b.runModel)
		{
			out << "\nПараметры модели:   время,ч   \t";
			for (int i = 0; i < 12; i++)
				out << i << "-" << i + 1 << "\t|";
			out << "\nИнтервал появления людей,мин \t";
			for (int i = 0; i < 12; i++)
				out << "  " << b.IntervalTimePass[i] << "\t|";
			out << "\nИнтервал подъезда такси, мин \t";
			for (int i = 0; i < 12; i++)
				out << "  " << b.IntervalTimeBus[i] << "\t|";

			out << "\nПродолжение:   время,ч   \t";
			for (int i = 0; i < 12; i++)
				out << 12 + i << "-" << 12 + i + 1 << "\t|";
			out << "\nИнтервал появления людей,мин \t";
			for (int i = 0; i < 12; i++)
				out << "  " << b.IntervalTimePass[12 + i] << "\t|";
			out << "\nИнтервал подъезда такси, мин \t";
			for (int i = 0; i < 12; i++)
				out << "  " << b.IntervalTimeBus[12 + i] << "\t|";
		}
		else
		{
			out << "\nРезультат модели:   время,ч   \t";
			for (int i = 0; i < 12; i++)
				out << i << "-" << i + 1 << "\t|";
			out << "\nВремя ожидания людей,мин \t";
			for (int i = 0; i < 12; i++)
			{
				if (b.CountTimePass[i] != 0)
					out << "  " << b.WaitTimePass[i] / b.CountTimePass[i] << "\t|";
				else out << "\t|";
			}
			out << "\nПродолжение:   время,ч   \t";
			for (int i = 0; i < 12; i++)
				out << 12 + i << "-" << 12 + i + 1 << "\t|";
			out << "\nВремя ожидания людей,мин \t";
			for (int i = 0; i < 12; i++)
			{
				if (b.CountTimePass[12+i] != 0)
					out << "  " << b.WaitTimePass[12+i] / b.CountTimePass[12+i] << "\t|";
				else out << "\t|";
			}
		}
		return out;
	}
	void setRunModel(bool runmodel)
	{
		runModel = runmodel;
		
	}

};

