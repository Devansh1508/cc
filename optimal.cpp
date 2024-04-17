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
    vector<int> v;
    vector<int> pages = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2, 3};
    int fault = 0;

    for (int i = 0; i < pages.size(); i++)
    {

        if(find(v.begin(),v.end(),pages[i])!=v.end()){
            cout << pages[i] << " is already present in the frame" << endl;
            for (auto x : v)
            {
                cout << x << " ";
            }
            cout << endl;
        }
        else if (v.size() < 4)
        {
            v.push_back(pages[i]);
            for (auto x : v)
            {
                cout << x << " ";
            }
            cout << endl;
            fault++;
        }
        else
        {
            set<int> s;
            for (int j = 0; j < 3; j++)
            {
                s.insert(v[j]);
            }
            for (int j = i + 1; j < pages.size(); j++)
            {
                if (s.find(pages[j]) != s.end())
                {
                    s.erase(pages[j]);
                }
                if (s.size() == 1)
                {
                    break;
                }
            }
                auto it=s.begin();
                for (int q=0;q<3;q++){
                    if(v[q]==*it){
                        v[q]=pages[i];
                        break;
                    }
                }
                fault++;
                cout<<pages[i]<<" is not present in the frame"<<endl;
                for (auto x : v)
                {
                    cout << x << " ";
                }
                cout << endl;
                s.clear();
        }
    }
    cout << "\ntotal number of faults " << fault << endl;

    return 0;
}


