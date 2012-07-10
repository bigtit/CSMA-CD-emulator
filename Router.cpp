#include "Router.h"

#include <cassert>
#include <iostream>

#include "Clock.h"
#include "Debug.h"

using namespace std;

Router Router::instance_;

void Router::OnPacketGenerated(Computer* comp) {
  PRINT("OnPacketGenerated: " << comp << std::endl);
  queue<unsigned long long>& q = packetGeneratedTimes_[comp];
  q.push(Clock::GetTime());
}

void Router::OnPacketDropped(Computer* comp) {
  PRINT("OnPacketDropped: " << comp << std::endl);
  queue<unsigned long long>& q = packetGeneratedTimes_[comp];
  assert(!q.empty());
  q.pop();
}

void Router::OnPacketTransmitted(Computer* comp) {
  PRINT("OnPacketTransmitted: " << comp << std::endl);
  queue<unsigned long long>& q = packetGeneratedTimes_[comp];
  assert(!q.empty());
  packetsArrived_++;
  unsigned long long delay = Clock::GetTime() - q.front();
  q.pop();
  totalPacketDelay_ += delay;
}

void Router::PrintStatistics() {
  cout << "Received " << packetsArrived_ << " packets" << endl;
  if (packetsArrived_ > 0) {
      cout << "Average delay time " << (double)totalPacketDelay_ / packetsArrived_ << " bit-time" << endl;
  }
}
