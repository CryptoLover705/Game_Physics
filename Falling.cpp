#include <cmath>
#include <sstream>
#include <iostream>

#include "Simulation.hpp"

int main(int argc, char** argv)
{
	World PhysWorld = World();
	PhysWorld.Interval = 5.0;

	Particle P = Particle(); PhysWorld.AddParticle(&P);
	P.PlotName = "plot.dat";
	P.Mass = 1.0;
	P.Location = Vector3(0.0, 0.0, 0.0);
	P.Velocity = Vector3(0.0, 0.0, 0.0);

	double k = 0.25;
	P.PreUpdate = [&](double dt)
	{
		P.ApplyForce(Vector3(P.Mass * 10.0, 0.0, 0.0), dt);
		P.ApplyForce(Vector3(-k * P.Velocity.Magnitude(), 0.0, 0.0), dt);
	};
	P.OutputValues = {&PhysWorld.Time, &P.Velocity[0]};
	PhysWorld.EndFunction = [&](){ return !(PhysWorld.Time > 60.0); };
	PhysWorld.Run();

	return 0;
}
