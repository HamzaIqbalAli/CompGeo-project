#include <iostream>
#include <bits/stdc++.h>
#include <utility>
#include <vector>
#include <stdlib.h>
using namespace std;
vector <pair<float,float> > points;
int num_of_points,left_most;
bool isColl(int a,int b, int c)
{
    float s1,s2;
    s1 = (points[b].second - points[a].second) * (points[b].first - points[a].first);
    s2 = (points[c].second - points[a].second) * (points[c].first - points[a].first);
    if(s1==s2)  return 0;
    else    return 1;
}

int findOrientation(int p1,int p2,int p3)
{
    float s1,s2;
    s1 = (points[p3].second - points[p2].second) * (points[p2].first - points[p1].first);
    s2 = (points[p2].second - points[p1].second) * (points[p3].first - points[p2].first);
    if(s1==s2)  return -1;
    else   if(s1>s2)    return 1;
    else return -1;
}

int firstpoint(stack <int> &s)
{
    int top = s.top();
    s.pop();
    int sec_to_top = s.top();
    s.push(top);
    return sec_to_top;
}

int compareFunction(const pair<float,float> &p1, const pair<float,float> &p2)
{
    float s1,s2;
    s1 = (p2.second-p1.second) * (p1.first-points[left_most].first);
    s2 = (p1.second-points[left_most].second) * (p2.first-p1.first);
    if(s1>s2)   return 1;
    else if(s1<s2)  return 0;
    else
    {
        float dist1 = abs(points[left_most].first - p1.first) + abs(points[left_most].second - p1.second);
        float dist2 = abs(points[left_most].first - p2.first) + abs(points[left_most].second - p2.second);
        if(dist1<dist2) return 1;
        else return 0;
    }


}

void swapPoints(int lleft_most)
{
    float swap_x,swap_y;
    swap_x = points[0].first;   points[0].first  = points[lleft_most].first;
    swap_y = points[0].second;  points[0].second = points[lleft_most].second;
    points[lleft_most].first  = swap_x;
    points[lleft_most].second = swap_y;
}

void GrahamScan()
{
    left_most = 0;int i;
    for(i=1;i<num_of_points;i++)
    {
        if((points[i].first<points[left_most].first) || (points[i].first==points[left_most].first && points[i].second<points[left_most].second))
            left_most=i;
    }
    swapPoints(left_most);
    left_most=0;
    sort(points.begin()+1,points.end(),compareFunction);
    int newn = 1;
    for(i=1;i<num_of_points;i++)
    {
        while(i<num_of_points-1 && isColl(left_most,i,i+1)==0)
        {
            i++;
        }
        points[newn]=points[i];
        newn++;
    }
    //------------------*/
    //if(sz<3)    return
    stack <int> s;
    s.push(left_most);
    s.push(1);
    s.push(2);

    for(i=3;i<newn;i++)
    {
        while(findOrientation(firstpoint(s),s.top(),i)!=1)
            s.pop();
        s.push(i);
    }
    cout<<"Number of points in hull - "<<s.size()<<"\n";
    while(s.empty()==false)
    {
        int j = s.top();
        cout<<points[j].first<<" "<<points[j].second<<"\n";
        s.pop();
    }

}

int main()
{
    cout<<"Input number of points - ";
    int i;cin>>num_of_points;
    float x,y;
    cout<<"Input points \n";
    for(i=0;i<num_of_points;i++)
    {
        cout<<(i+1)<<" - ";
        cin>>x>>y;
        points.push_back(make_pair(x,y));
    }
    GrahamScan();
    return 0;
}

