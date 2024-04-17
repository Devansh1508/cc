#include <bits/stdc++.h>
#include <array>
using namespace std;

void inp(vector<int> v, int n)
{
    for (int i = 0; i < n; i++)
    {
        cin >> v[i];
    }
}

// sort(start,end,logic);
// this logic can be any function or any statement

int main()
{
    int fault=0;
    vector<int> pages={1, 3, 0, 3, 5, 6, 3};
    vector<int> v;
    for (int i = 0; i < pages.size(); i++)
    {
        if (v.size() < 3)
        {
                for(auto x:v)
                {
                    cout<<x<<" ";
                }
                cout<<endl;
            v.push_back(pages[i]);
            fault++;
        }
        else
        {
            if (find(v.begin(), v.end(), pages[i]) == v.end())
            {
                for(auto x:v)
                {
                    cout<<x<<" ";
                }
                cout<<endl;
                cout<<pages[i]<<" is not present in the frame"<<endl;
                v.erase(v.begin());
                v.push_back(pages[i]);
                fault++;
            }
            else {
                for(auto x:v)
                {
                    cout<<x<<" ";
                }
                cout<<endl;
                cout<<pages[i]<<" is already present in the frame"<<endl;
            }
        }
    }
    cout <<"\ntotal number of faults "<< fault<<endl;
    return 0;
}
