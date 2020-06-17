#include <cmath>
#include <sstream>
#include <iostream>
#include <algorithm>

#include "Simulation.hpp"

#define PI 3.14159265

int main(int argc, char** argv)
{
	double f = 0.5;
	double f_driv = 0.25;

	World PhysWorld = World();
	PhysWorld.Interval = 0.01;

	Particle P = Particle(); PhysWorld.AddParticle(&P);
	P.PlotName = "plot.dat";
	P.Mass = 1.0;
	P.Location = Vector3(1.0, 0.0, 0.0);
	P.Velocity = Vector3(0.0, 0.0, 0.0);
	P.PreUpdate = [&](double dt)
	{
		// Restoring Force:
		double k = P.Mass * pow(2*PI*f, 2);
		P.ApplyForce(P.Location * -1 * k, dt);

		// Driving Force:
		P.ApplyForce(Vector3(1.0, 0.0, 0.0) * 10.0 * sin(2*PI*f_driv * PhysWorld.Time), dt);
		
		// Damping:
		P.ApplyForce(P.Velocity*-0.1, dt);
	};
	P.OutputValues = {&PhysWorld.Time, &P.Location[0]};

	PhysWorld.EndFunction = [&](){ return !(PhysWorld.Time > 40.0); };

	PhysWorld.Run();

	return 0;
}
