#include "Router.h"

#include <cassert>
#include <iostream>

#include "Environment.h"
#include "Clock.h"

using namespace std;

Router Router::instance_;

void Router::OnPacketGenerated(Computer* comp) {
  queue<unsigned long long>& q = packetGeneratedTimes_[comp];
  q.push(Clock::GetTime());
}

void Router::OnPacketDropped(Computer* comp) {
  queue<unsigned long long>& q = packetGeneratedTimes_[comp];
  assert(!q.empty());
  packetsDropped_++;
  q.pop();
}

void Router::OnPacketTransmitted(Computer* comp) {
  queue<unsigned long long>& q = packetGeneratedTimes_[comp];
  assert(!q.empty());
  packetsArrived_++;
  unsigned long long delay = Clock::GetTime() - q.front();
  q.pop();
  totalPacketDelay_ += delay;
}

void Router::PrintStatistics() {
  double totalTime = (Clock::GetTime() / (Environment::LAN_SPEED * 1000000));
  cout << "Received " << packetsArrived_ << " packets" << endl;
  cout << "Dropped " << packetsDropped_ << " packets" << endl;
  cout << "Took " << totalTime << " sec (" << Clock::GetTime() << " bit-time)" << endl;

  double delayTime = 0;
  double delayTimeInSecs = 0;
  if (packetsArrived_ > 0) {
    delayTime = (double)totalPacketDelay_ / packetsArrived_;
    delayTimeInSecs = delayTime / (Environment::LAN_SPEED * 1000000);
  }
  cout << "Average delay time: " << delayTimeInSecs << " secs (" << delayTime << " bit-time)" << endl;

  double throughput = Environment::PACKET_LENGTH * ((double) packetsArrived_ / totalTime) / 1000000;
  cout << "Throughput: " << throughput << " Mbps" << endl;
}
