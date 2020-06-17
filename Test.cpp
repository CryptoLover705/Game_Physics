#include "Simulation.hpp"

#include <sstream>
#include <cmath>

int main(int argc, char** argv)
{
	World PhysWorld = World();
	PhysWorld.Interval = 0.001;

	Particle P = Particle(); PhysWorld.AddParticle(&P);
	P.Mass = 1.0;
	P.PlotName = "plotp.dat";
	P.Location = Vector3(1.0, 0.0, 0.0);

	Particle Q = Particle(); PhysWorld.AddParticle(&Q);
	Q.Mass = 1.0;
	Q.PlotName = "plotq.dat";
	Q.Location = Vector3(-1.0, 0.0, 0.0);

	P.PreUpdate = [&](double dt)
	{
		Vector3 PQ = (Q.Location - P.Location);
		double Distance = PQ.Magnitude();
		Vector3 Direction = PQ.Normalize();
		P.ApplyForce(Direction*(P.Mass * Q.Mass), dt);

	};
	Q.PreUpdate = [&](double dt)
	{
		Vector3 QP = (P.Location - Q.Location);
		double Distance = QP.Magnitude();
		Vector3 Direction = QP.Normalize();
		Q.ApplyForce(Direction*(P.Mass * Q.Mass), dt);
	};

	P.OutputValues = {&P.Location[0], &PhysWorld.Time};
	Q.OutputValues = {&Q.Location[0], &PhysWorld.Time};

	PhysWorld.EndFunction = [&](){ return !(PhysWorld.Time > 10.0); };

	PhysWorld.Run();

	return 0;
}
