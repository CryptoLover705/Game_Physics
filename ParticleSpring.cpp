#include <cmath>
#include <sstream>
#include <iostream>

#include "Simulation.hpp"

int main(int argc, char** argv)
{
	World PhysWorld = World();
	PhysWorld.Interval = 0.2;

	Particle P = Particle(); PhysWorld.AddParticle(&P);
	P.PlotName = "plot.dat";
	P.Mass = 1.0;
	P.Location = Vector3(0.0, 0.0, 10.0);
	P.Velocity = Vector3(0.0, 0.0, 0.0);

	P.PreUpdate = [&](double dt)
	{
		double z = P.Location[2];
		P.ApplyForce(Vector3(0.0, 0.0, -P.Mass * 10.0), dt); // Gravity
		if(z <= 0) // Spring
		{
			double k = 10.5;
			P.ApplyForce(Vector3(0.0, 0.0, k*(-z)), dt);
		}
	};
	P.OutputValues = {&P.Location[2], &P.Velocity[2]};
	PhysWorld.EndFunction = [&]()
	{
		return !(P.Location[2] > 9.9 && P.Velocity[2] < 0 && PhysWorld.Time > 0.5);
	};
	PhysWorld.Run();

	return 0;
}
