#include <bits/stdc++.h>
#include <array>
using namespace std;

int main()
{
    vector <int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 3 };
    int n = pages.size();
    int capacity = 4;
    int page_faults = 0;
    vector <int> frame;
    for (int i=0;i<n;i++){
        if(frame.size()<capacity){
            if(find(frame.begin(),frame.end(),pages[i])==frame.end()){
                frame.push_back(pages[i]);
                page_faults++;
            }
            else{
                frame.push_back(pages[i]);
            }
        }
        else{
            if(find(frame.begin(),frame.end(),pages[i])==frame.end()){
                frame.erase(frame.begin());
                frame.push_back(pages[i]);
                page_faults++;
            }
            else{
                frame.push_back(pages[i]);
            }
        }
        
    }
    cout<<"total number of page faults: "<<page_faults<<"\n";

    return 0;
}