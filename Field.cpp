#include <cmath>
#include <sstream>
#include <iostream>

#include "Simulation.hpp"

Vector3 ForceField(Vector3 Location)
{
	Vector3 Direction = -Location.Normalize();
	return Direction*10.0;
}

int main(int argc, char** argv)
{
	World PhysWorld = World();
	PhysWorld.Interval = 0.01;

	Particle P = Particle(); PhysWorld.AddParticle(&P);
	P.PlotName = "plot.dat";
	P.Mass = 1.0;
	P.Location = Vector3(1.0, 1.0, 0.0);
	P.Velocity = P.Location.Normalize().Cross(Vector3(0.0, 0.0, 1.0)) * sqrt(10.0*P.Location.Magnitude()/P.Mass);
	P.PreUpdate = [&](double dt)
	{
		P.ApplyForce(ForceField(P.Location), dt);

		// Damping:
		P.ApplyForce(P.Velocity*-0.2, dt);
	};

	P.OutputValues = {&P.Location[0], &P.Location[1], &PhysWorld.Time};

	PhysWorld.EndFunction = [&](){ return !(PhysWorld.Time > 80.0); };

	PhysWorld.Run();

	return 0;
}
