#include <algorithm>
#include <deque>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Request {
  friend class Worker;
  int arrivalTime;

 public:
  Request(int arrivalTime) : arrivalTime(arrivalTime) {}

  bool available(int time) { return time >= arrivalTime; }
};

class Topic {
  int id, amount, arriveTime, task, delay;
  friend class TaskManager;
  friend class Worker;
  queue<Request> requests;

 public:
  Topic(int id, int amount, int arriveTime, int task, int delay)
      : id(id),
        amount(amount),
        arriveTime(arriveTime),
        task(task),
        delay(delay) {
    for (int i = 0; i < amount; i++) requests.emplace(arriveTime + delay * i);
  }

  bool requestAvailable(const int time) {
    return requests.empty() ? false : requests.front().available(time);
  }
};

class Worker {
  friend class TaskManager;
  int id, lastAssignedTime = 0, task = 0;
  vector<int> types;
  bool availble = true, inQueue = false;
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

  bool takerequest(vector<Topic> &timeline, const int &time) {
    for (int i = 0; i < types.size(); i++)
      for (int j = 0; j < timeline.size(); j++)
        if (timeline[j].id == types[i] && timeline[j].requestAvailable(time)) {
          lastAssignedTime = time;
          task = timeline[j].task;
          timeline[j].requests.pop();
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

class TaskManager {
  vector<Topic> timeline;
  vector<Worker> workers;
  int time = 0, requestsTaken = 0, totalRequests = 0;
  vector<Worker *> availableWorkers;

 public:
  TaskManager(const int count) {
    int id, amount, arriveTime, task, delay;
    for (int i = 0; i < count; i++) {
      cin >> id >> amount >> arriveTime >> task >> delay;
      timeline.emplace_back(id, amount, arriveTime, task, delay);
    }

    int worker;
    cin >> worker;
    for (int i = 0; i < worker; i++) workers.emplace_back(i);
    for (int i = 0; i < timeline.size(); i++)
      totalRequests += timeline[i].requests.size();
  }

  void proceed() {
    // collect workers
    for (int i = 0; i < workers.size(); i++) {
      workers[i].update();
      if (workers[i].availble && !workers[i].inQueue) {
        workers[i].inQueue = true;
        availableWorkers.push_back(&workers[i]);
      }
    }
    // sort workers
    sort(availableWorkers.begin(), availableWorkers.end(), Worker::compare);
    // taking jobs
    for (int i = 0; i < availableWorkers.size(); i++)
      if (availableWorkers[i]->takerequest(timeline, time)) {
        availableWorkers[i]->inQueue = false;
        availableWorkers.erase(availableWorkers.begin() + i--);
        requestsTaken++;
      }
    time++;
  }

  int getTime() { return time; }

  bool finished() {
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