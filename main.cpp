#include <cstdio>
#include <iostream>
#include <cstdlib>

#include "Events.h"
#include "Environment.h"
#include "Simulation.h"

using std::cerr;
using std::atoi;
using std::atof;

int main(int argc, char** argv) {
  if (argc != 5) {
    cerr << "Usage: " << argv[0] << " N A W L\n";
    return -1;
  }

  Environment::NUM_COMPS = atoi(argv[1]);
  Environment::LAN_SPEED = atof(argv[3]);
  Environment::PACKET_LENGTH = atoi(argv[4]);

  Environment::ARRIVAL_RATE = atof(argv[2]) / (Environment::LAN_SPEED * 1000000);
  Environment::PROP_TIME = 300;

  Simulation();
}

