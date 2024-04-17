#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 3 };
    int n = pages.size();
    int capacity = 4;
    int page_faults = 0;
    vector<int> frame;
    for (int i = 0; i < n; i++) {
        auto it = find(frame.begin(), frame.end(), pages[i]);
        if (it == frame.end()) { 
            if (frame.size() < capacity) {
                frame.push_back(pages[i]);
            } else {
                int pageToReplace = frame.back();
                frame.erase(find(frame.begin(), frame.end(), pageToReplace));
                frame.push_back(pages[i]);
            }
            page_faults++;
        } else {
            frame.erase(it);
            frame.push_back(pages[i]);
        }
    }
    cout << "Total number of page faults: " << page_faults << "\n";

    return 0;
}
