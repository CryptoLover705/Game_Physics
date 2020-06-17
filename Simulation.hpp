#include <functional>
#include <algorithm>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

#include "Vector3.hpp"

struct Particle
{
	Vector3 Location;
	Vector3 Velocity;
	std::string PlotName;
	std::ofstream PlotFile;
	double Mass;

	std::function<void(double)> PreUpdate;
	std::vector<double*> OutputValues;

	void Output(double dt)
	{
		if(!this->PlotName.empty() && !this->PlotFile.is_open())
		{
			this->PlotFile.open(this->PlotName);
		}
		if(OutputValues.size() > 0)
		{
			for(double* value : OutputValues)
			{
				this->PlotFile << *value << "\t";
			}
			this->PlotFile << "\n";
		}
	};

	void Update(double dt)
	{
		this->Location += this->Velocity*dt;
	};

	void ApplyForce(Vector3 Force, double dt)
	{
		this->Velocity += Force*dt / this->Mass;
	};
};

struct World
{
	double Time;
	double Interval;
	std::function<bool()> EndFunction;
	std::vector<Particle*> Particles;
	int AddParticle(Particle* P)
	{
		Particles.push_back(P);
	};

	void Run()
	{
		this->Time = 0.0;
		while(this->EndFunction())
		{
			for(Particle* P : this->Particles)
			{
				P->Output(Interval);
				P->PreUpdate(Interval);
			}
			for(Particle* P : this->Particles)
			{
				P->Update(Interval);
			}

			this->Time += Interval;
		}
		for(Particle* P : this->Particles)
		{
			if(P->PlotFile.is_open())
			{
				P->PlotFile.close();
			}
		}

	}
};
