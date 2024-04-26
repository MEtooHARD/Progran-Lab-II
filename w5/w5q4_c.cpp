#include <algorithm>
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
  int avgElapsedTime;
  int avgServiceTime;
  int avgTimeBetweenRequests;

  Topic(int id, int avgRequestsPerDay, int avgElapsedTime, int avgServiceTime,
        int avgTimeBetweenRequests)
      : id(id),
        avgRequestsPerDay(avgRequestsPerDay),
        avgElapsedTime(avgElapsedTime),
        avgServiceTime(avgServiceTime),
        avgTimeBetweenRequests(avgTimeBetweenRequests) {}
};

class SupportSystem {
 private:
  std::vector<Request> requests;
  std::vector<Staff> staff;
  std::vector<Topic> topics;
  std::queue<int> availableStaff;
  int currentTime;  // Track current time

 public:
  SupportSystem() : currentTime(0) {}

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

  int processRequests() {
    int totalTime = 0;

    // Sort requests based on arrival time
    std::sort(requests.begin(), requests.end(),
              [](const Request& a, const Request& b) {
                return a.arrivalTime < b.arrivalTime;
              });

    for (const auto& request : requests) {
      // Advance time to arrival time of request
      currentTime = std::max(currentTime, request.arrivalTime);
      assignRequest(request);
      totalTime = std::max(totalTime, currentTime + request.serviceTime);
    }

    return totalTime;
  }

  void assignRequest(const Request& request) {
    // Find available staff with expertise in the request's topic
    for (const auto& staffMember : staff) {
      for (int topicId : staffMember.expertise) {
        if (topicId == request.topicId) {
          availableStaff.push(staffMember.id);
          break;
        }
      }
    }

    // Assign request to available staff member
    if (!availableStaff.empty()) {
      int assignedStaffId = availableStaff.front();
      availableStaff.pop();
      // Additional logic to handle request servicing
      currentTime += request.serviceTime;
    } else {
      std::cout << "No available staff to handle the request." << std::endl;
    }
  }

  bool hasEndOfInput() {
    // Check if end of input is reached (no more scenarios)
    return topics.empty() && staff.empty();
  }
};

int main() {
  SupportSystem supportSystem;

  int scenario = 1;
  while (true) {
    std::cout << "Scenario " << scenario << ":\n";

    supportSystem.readScenario();
    int totalTime = supportSystem.processRequests();

    std::cout << "All requests are serviced within " << totalTime
              << " minutes.\n";

    // Check for end of input
    if (supportSystem.hasEndOfInput()) {
      break;
    }
    ++scenario;
  }

  return 0;
}
