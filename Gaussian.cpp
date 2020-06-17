#include <cstdlib>
#include <cmath>
#include <limits>

#include "Simulation.hpp"

double generateGaussianNoise(double mu, double sigma)
{
	const double epsilon = std::numeric_limits<double>::min();
	const double two_pi = 2.0*3.14159265358979323846;

	static double z0, z1;
	static bool generate;
	generate = !generate;

	if (!generate)
	   return z1 * sigma + mu;

	double u1, u2;
	do
	 {
	   u1 = rand() * (1.0 / RAND_MAX);
	   u2 = rand() * (1.0 / RAND_MAX);
	 }
	while ( u1 <= epsilon );

	z0 = sqrt(-2.0 * log(u1)) * cos(two_pi * u2);
	z1 = sqrt(-2.0 * log(u1)) * sin(two_pi * u2);
	return z0 * sigma + mu;
}

int main(int argc, char** argv)
{
	World PhysWorld = World();
	PhysWorld.Interval = 1.00;

	Particle P = Particle(); PhysWorld.AddParticle(&P);
	P.PlotName = "plot.dat";
	P.Mass = 1.0;

	double mean = 0.0;
	double deviation = 100.0;
	double A = 1.0;

	P.PreUpdate = [&](double dt)
	{
		P.Location[0] = A*generateGaussianNoise(mean, deviation);
		P.Location[1] = A*generateGaussianNoise(mean, deviation);
		P.Location[2] = A*generateGaussianNoise(mean, deviation);
	};
	P.OutputValues = {&P.Location[0], &P.Location[1], &P.Location[2]};

	PhysWorld.EndFunction = [&](){ return !(PhysWorld.Time > 10000.0); };

	PhysWorld.Run();

	return 0;
}
