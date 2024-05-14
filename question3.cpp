#include <vector>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

struct Component{
  int  id;
  int  early_start_time; //最早可以开始时间 > 0
  int  last_start_time;  //最晚可以开始时间 last_start_time > early_start_time
  int  process_time;     //零件加工时间 > 0
};

struct Worker{
  int  id;
};

struct ComponentResult{
  int  id;
  int  start_time;
};

bool compareComponent(const Component& a, const Component& b) {
    return a.early_start_time < b.early_start_time ||
           (a.early_start_time == b.early_start_time && a.last_start_time < b.last_start_time);
}

class Scheduler {
public:
  int calcLeastTime(vector<Component>& components, vector<Worker>& workers, vector<ComponentResult>& component_ids) {
    std::priority_queue <int,vector<int>,greater<int> >q;
    for (int i = 0; i < workers.size(); ++i){
        q.push(0);
    }
    sort(components.begin(), components.end(), compareComponent);
    int currentTime = 0;
    for (auto& comp : components) {
        currentTime = comp.early_start_time;
        if (q.top() <= currentTime){
            q.pop();
            int nexttime = currentTime + comp.process_time;
            q.push(nexttime);
            ComponentResult cr{comp.id, currentTime};
            component_ids.push_back(cr);
        }
        else{
            while (1){
                ++currentTime;
                if (currentTime > comp.last_start_time){
                    component_ids.clear();
                    return -1;
                }
                if (currentTime >= q.top()){
                    q.pop();
                    int nexttime = currentTime + comp.process_time;
                    q.push(nexttime);
                    ComponentResult cr{comp.id, currentTime};
                    component_ids.push_back(cr);
                    break;
                }
            }
        }
        
    }
    return currentTime + components[components.size()-1].process_time;
  }
};

// Example main function
int main() {
    vector<Component> components = {{1, 0, 2, 3}, {2, 3, 5, 5}, {3, 2, 4, 4}, {4, 3, 6, 4}};
    vector<Worker> workers = {{1}, {2}};
    vector<ComponentResult> component_ids;
    
    Scheduler scheduler;
    int result = scheduler.calcLeastTime(components, workers, component_ids);
    
    for (auto& comp : component_ids) {
        cout << "Component ID: " << comp.id << ", Start Time: " << comp.start_time << endl;
    }
    cout << "Total Process Time: " << result << endl;
    return 0;
}