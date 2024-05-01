#include <algorithm>
#include <deque>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Request {
 public:
  int topicId;
  int arrivalTime;
  int serviceTime;

  Request(int topicId, int arrivalTime, int serviceTime)
      : topicId(topicId), arrivalTime(arrivalTime), serviceTime(serviceTime) {}

  bool available(int time) { return time >= arrivalTime; }
};

class Worker {
  friend class TaskManager;
  int id, lastAssignedTime = 0, task = 0;
  vector<int> types;
  bool availble = true;
  int appear;

 public:
  Worker(int appear) : appear(appear) {
    int n, type;
    cin >> id >> n;
    types.reserve(n);
    for (int i = 0; i < n; ++i) {
      cin >> type;
      types.push_back(type);
    };
  }

  bool takeJob(deque<Request *> &requsts, const int &time) {
    for (int i = 0; i < types.size(); i++)
      for (int j = 0; j < requsts.size(); j++)
        if (requsts[j]->topicId == types[i]) {
          lastAssignedTime = time;
          task = requsts[j]->serviceTime;
          requsts.erase(requsts.begin() + j);
          availble = false;
          return true;
        }
    return false;
  }

  void update() {
    if (task > 0) task--;
    availble = (task == 0);
  }

  static bool compare(Worker *&a, Worker *&b) {
    return a->lastAssignedTime < b->lastAssignedTime
               ? true
               : (a->lastAssignedTime == b->lastAssignedTime
                      ? a->appear < b->appear
                      : false);
  }
};

class Topic {
  int id, count, arriveTime, duration, delay;
  friend class TaskManager;
  queue<Request> requests;

 public:
  Topic() {
    cin >> id >> count >> arriveTime >> duration >> delay;
    for (int i = 0; i < count; i++)
      requests.emplace(id, arriveTime + delay * i, duration);
  }

  bool requestAvailable(const int time) {
    return requests.empty() ? false : requests.front().available(time);
  }
};

class TaskManager {
  vector<Topic> timeline;
  vector<Worker> workers;
  int time = 0, requestsTaken = 0, totalRequests = 0;
  deque<Request *> availableRequests;
  vector<Worker *> availableWorkers;

 public:
  TaskManager(const int count) {
    for (int i = 0; i < count; i++) timeline.emplace_back();
    int worker;
    cin >> worker;
    for (int i = 0; i < worker; i++) workers.emplace_back(i);
    for (int i = 0; i < timeline.size(); i++)
      totalRequests += timeline[i].requests.size();
  }

  void proceed() {
    // ini
    for (int i = 0; i < workers.size(); i++) workers[i].update();
    availableWorkers.clear();

    // collect requests
    for (int i = 0; i < timeline.size(); i++)
      if (timeline[i].requestAvailable(time)) {
        availableRequests.push_back(&timeline[i].requests.front());
        timeline[i].requests.pop();
      }

    // if (availableRequests.size()) {
    // collect workers
    for (int i = 0; i < workers.size(); i++)
      if (workers[i].availble) availableWorkers.push_back(&workers[i]);

    // sort workers
    sort(availableWorkers.begin(), availableWorkers.end(), Worker::compare);

    // taking jobs
    for (int i = 0; i < availableWorkers.size(); i++)
      if (availableWorkers[i]->takeJob(availableRequests, time)) {
        availableWorkers.erase(availableWorkers.begin() + i--);
        requestsTaken++;
      }
    // }

    time++;
  }

  int getTime() { return time; }

  bool finished() {
    // int
    return requestsTaken == totalRequests &&
           availableWorkers.size() == workers.size();
  }
};

int main() {
  int topicCount, scenario = 0;
  cin >> topicCount;
  while (topicCount) {
    scenario++;
    TaskManager manager(topicCount);
    do {
      manager.proceed();
    } while (!manager.finished());
    cout << "Scenario " << scenario << ": All requests are serviced within "
         << manager.getTime() - 1 << " minutes." << endl;
    cin >> topicCount;
  };
}