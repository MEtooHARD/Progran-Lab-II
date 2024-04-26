#include <iostream>
#include <queue>
#include <vector>

class Request {
 public:
  int topicId;
  int arrivalTime;
  int serviceTime;

  Request(int topicId, int arrivalTime, int serviceTime)
      : topicId(topicId), arrivalTime(arrivalTime), serviceTime(serviceTime) {}
};

class Staff {
 public:
  int id;
  std::vector<int> expertise;

  Staff(int id, std::vector<int> expertise) : id(id), expertise(expertise) {}
};

class Topic {
 public:
  int id;
  int avgRequestsPerDay;
  int avgTimeBetweenRequests;
  int avgServiceTime;

  Topic(int id, int avgRequestsPerDay, int avgTimeBetweenRequests,
        int avgServiceTime)
      : id(id),
        avgRequestsPerDay(avgRequestsPerDay),
        avgTimeBetweenRequests(avgTimeBetweenRequests),
        avgServiceTime(avgServiceTime) {}
};

class SupportSystem {
 private:
  std::vector<Request> requests;
  std::vector<Staff> staff;
  std::vector<Topic> topics;
  std::queue<int> availableStaff;

 public:
  SupportSystem() {}

  void readScenario() {
    int numTopics;
    std::cin >> numTopics;

    // Read topics
    for (int i = 0; i < numTopics; ++i) {
      int id, requests, elapsed, service, between;
      std::cin >> id >> requests >> elapsed >> service >> between;
      topics.emplace_back(id, requests, elapsed, service, between);
    }

    int numStaff;
    std::cin >> numStaff;

    // Read staff
    for (int i = 0; i < numStaff; ++i) {
      int id, numTopics;
      std::cin >> id >> numTopics;
      std::vector<int> expertise(numTopics);
      for (int j = 0; j < numTopics; ++j) {
        std::cin >> expertise[j];
      }
      staff.emplace_back(id, expertise);
    }
  }

  // Additional methods for processing requests and assigning staff
};

int main() {
  SupportSystem supportSystem;

  int scenario = 1;
  while (true) {
    supportSystem.readScenario();
    // Process scenario or break if end of input
    if (supportSystem.hasEndOfInput()) {
      break;
    }
    ++scenario;
  }

  return 0;
}
