#include "datTestTypes.h"
#include <random>
#include <cmath>
using namespace std;

Flower::Flower(unsigned int x, unsigned int y, Bin* const bin)
  : Entity::Entity(x, y, bin)
{
  //Random number stuff
  random_device seed;
  mt19937 gen(seed());
  uniform_real_distribution<double> chanceGen (0.0, 1.0);
  chance = chanceGen(gen);
}

void Flower::update(unsigned int resolution)
{
  age += resolution;

  auto gexChance = [=](int age)->double { return double(age-germinationMinAge) / double(germinationMaxAge-germinationMinAge);};
  auto distribution = [=](int age)->double { return pow( 2.0*(-0.1*gexChance(age) / (gexChance(age) - 1.0)), 3.0 ); };

  if (size < maxSize) //If I can grow continue
  {
    //If you're jumping over the grow period due to resolution
    if ((age-resolution <= germinationMinAge) && (age >= germinationMaxAge))
      size = maxSize;

    //If my grow start time has passed
    else if (chance < distribution(age))
    {
      //If this is the first time past my grow time
      if ( !(chance < distribution(age-resolution)) )
        size += (maxSize/(60.0*60.0*12.0))*(( chance-distribution(age) ) * (germinationMaxAge-germinationMinAge)); //How much the chance was missed by in world seconds
      else //If nothing else has happened - everything is normal
        size += (maxSize/(60.0*60.0*12.0))*resolution; //Grows to full size in 12 hours
    }
  }
}

double Flower::getSize() const
{
  return size;
}

void Bunny::update(unsigned int resolution)
{
  age += resolution;
}
