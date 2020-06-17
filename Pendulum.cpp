#include <cmath>
#include <iostream>
#include <algorithm>

#include "Simulation.hpp"

#define PI 3.14159265

int main(int argc, char** argv)
{
	World PhysWorld = World();
	PhysWorld.Interval = 0.01;

	Particle P = Particle(); PhysWorld.AddParticle(&P);
	P.PlotName = "plot.dat";
	P.Mass = 1.0;
	P.Location = Vector3(0.0, 0.0, -1.0);
	P.Velocity = Vector3(0.0, 0.0, 0.0);

	Vector3 Peg = Vector3(0.0, 0.0, 0.0);
	double l = (Peg - P.Location).Magnitude();
	double AngleRad = 90.0*(PI/180.0);
	P.Location = Vector3(l*sin(AngleRad), 0.0, -l*cos(AngleRad));

	double k = 0.2;
	P.PreUpdate = [&](double dt)
	{
		P.ApplyForce(Vector3(0.0, 0.0, -10.0), dt);
		Vector3 OP = P.Location - Peg;
		P.ApplyForce((OP.Normalize() * -1) * 1000.0 * (OP.Magnitude() - l), dt);
		P.ApplyForce(P.Velocity*-k, dt);
	};
	P.OutputValues = {&P.Location[0], &PhysWorld.Time, &P.Location[2]};
	PhysWorld.EndFunction = [&](){ return !(PhysWorld.Time > 40.0); };
	PhysWorld.Run();

	return 0;
}
