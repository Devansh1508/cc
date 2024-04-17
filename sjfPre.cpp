#include <bits/stdc++.h> 
using namespace std; 
 
class sjf { 
  public: 
    int processId; 
    int arrivalTime; 
    int burstTime; 
    int remainingTime; 
 
    sjf(int id, int arrival, int burst)  { 
      processId=id; 
      arrivalTime=arrival; 
      burstTime=burst; 
      remainingTime=burst; 
   } 
}; 
class StoreAns{ 
  public: 
  int processId; 
    int arrivalTime; 
    int burstTime; 
    int completionTime,wt,respTime, tat; 
}; 
struct CompareSJF { 
    bool operator()(const sjf& p1, const sjf& p2) 
    { 
        return p1.remainingTime > p2.remainingTime;  
    } 
     
}; 
 
static bool comp(sjf a , sjf b){ 
  if(a.arrivalTime!=b.arrivalTime) 
  return a.arrivalTime<b.arrivalTime; 
  return a.remainingTime<b.remainingTime; 
} 
 
  int main() { 
    vector<sjf> processes = { 
        {1, 2, 6}, 
        {2, 5, 2}, 
        {3, 1, 8}, 
        {4, 0, 3},
        {5,4,4}
    }; 
     
  vector<int>response(processes.size()+1,-1); 
   unordered_map<int,bool>visited; 
  sort(processes.begin(),processes.end(),comp); 
  priority_queue<sjf, vector<sjf>, CompareSJF> readyQueue; 
  readyQueue.push(processes[0]); 
  int count=1; 
  visited[processes[0].processId]=true; 
  cout << " Process Id  "  << " arrival Time  "  << "  Burst_Time is       execution time  "  << "  waiting time  "  <<  " response time "  <<"turnaround time" <<endl; 
 
vector<StoreAns>storeAns(processes.size()+1); 
  while(!readyQueue.empty()){ 
     
    sjf first = readyQueue.top(); 
    readyQueue.pop(); 
     
        
while(count<first.arrivalTime){count++;} 
 
if (response[first.processId] == -1) 
{ 
        response[first.processId] = count; 
        storeAns[first.processId].respTime=max(0,count-first.arrivalTime-1); 
     
} 
    if(first.remainingTime<=1){ 
      first.remainingTime=0; 
         storeAns[first.processId].processId=first.processId; 
     storeAns[first.processId].arrivalTime=first.arrivalTime; 
     storeAns[first.processId].burstTime=first.burstTime; 
     storeAns[first.processId].completionTime=count; 
     storeAns[first.processId].wt=max(0,count-first.burstTime-first.arrivalTime); 
     storeAns[first.processId].tat=first.burstTime+max(0,count-first.burstTime-first.arrivalTime); 
    
    } 
    else{ 
      first.remainingTime-=1; 
      readyQueue.push(first); 
    } 
       
  for (int i = 0; i < processes.size(); ++i) { 
    if (processes[i].arrivalTime <= count && !visited[processes[i].processId]) { 
        visited[processes[i].processId] = true; 
        readyQueue.push(processes[i]); 
    } 
} 
 
      
      if(readyQueue.empty()){ 
      sjf tofind(1e9,1e9,1e9); 
        
      bool flag=0; 
      for(int i=0;i<processes.size();i++){ 
        if(!visited[processes[i].processId]){ 
          if(processes[i].arrivalTime<tofind.arrivalTime){ 
            tofind=processes[i]; 
            flag=1; 
          } 
        } 
      } 
      if(flag){ readyQueue.push(tofind); visited[tofind.processId]=true;} 
    } 
count++; 
  } 
  for(int i=1;i<=processes.size();++i){ 
 
  cout<<setw(4)<<storeAns[i].processId<<setw(15)<<storeAns[i].arrivalTime<<setw(15)<<storeAns[i].burstTime<<setw(18)<<storeAns[i].completionTime<<setw(15)<<storeAns[i].wt<<setw(18)<<storeAns[i].respTime<<setw(15)<<storeAns[i].tat<<endl; 
} 
 
 
 
 
    return 0; 
}