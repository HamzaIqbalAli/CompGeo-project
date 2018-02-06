#include <iostream>
#include <bits/stdc++.h>
#include <utility>
#include <vector>
#include <stdlib.h>

using namespace std;

//-------Global variables------------------------
vector <pair<float,float> > points;
//-----------------------------------------------


//------------Function Definitions---------------
int findOrientation(int p1,int p2,int p3);
void JarvisMarch();
//-----------------------------------------------
float dist(int a,int b)
{
    return (abs(points[a].first-points[b].first) + abs(points[a].second-points[b].second));
}

int findOrientation(int p1,int p2,int p3)
{
    float slope1,slope2;
    slope1 = (points[p3].second-points[p2].second)*(points[p2].first-points[p1].first);
    slope2 = (points[p2].second-points[p1].second)*(points[p3].first-points[p2].first);
    if(slope1>slope2)
        return 1; //counterclockwise
    else if(slope1<slope2)
        return -1; //clockwise
    else
    {
         if(dist(p3,p1)>dist(p2,p1))
            return 1;
         else
            return -1;
    }
}
void JarvisMarch()
{
    int i,len;
    len = points.size();
    int p1,left_most;   //stores index of smallest x
    float sx = points[0].first;
    vector <int> ConvexHull;
    for(i=0;i<len;i++)
    {
        if(sx<points[i].first)
        {
            sx=points[i].first;
            left_most=i;
        }
    }
    p1=left_most;
    int p2;
    do
    {
        ConvexHull.push_back(p1);
        p2=(p1+1)%len;
        for(i=0;i<len;i++)
        {
            if(findOrientation(p1,p2,i)==1)
            {
                p2=i;
            }
        }
        p1=p2;
    } while(left_most!=p1);

    int sz = ConvexHull.size();
    cout<<"Points on the Convex Hull - "<<sz<<"\n";

    for(i=0;i<sz;i++)
    {
        cout<<(i+1)<<" - ("<<points[ConvexHull[i]].first<<","<<points[ConvexHull[i]].second<<")\n";
    }

}

int main()
{
    cout<<"Input number of points - ";
    int n,i;cin>>n;
    float x,y;
    cout<<"Input coordinates\n";
    for(i=0;i<n;i++)
    {
        cout<<(i+1)<<" - ";
        cin>>x>>y;
        points.push_back(make_pair(x,y));
    }
    JarvisMarch(); //calling function
    return 0;
}



/*#include <bits/stdc++.h>
using namespace std;

struct Point
{
    int x, y;
};

// To find orientation of ordered triplet (p, q, r).
// The function returns following values
// 0 --> p, q and r are colinear
// 1 --> Clockwise
// 2 --> Counterclockwise
int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y) * (r.x - q.x) -
              (q.x - p.x) * (r.y - q.y);

    if (val == 0) return 0;  // colinear
    return (val > 0)? 1: 2; // clock or counterclock wise
}

// Prints convex hull of a set of n points.
void convexHull(Point points[], int n)
{
    // There must be at least 3 points
    if (n < 3) return;

    // Initialize Result
    vector<Point> hull;

    // Find the leftmost point
    int l = 0;
    for (int i = 1; i < n; i++)
        if (points[i].x < points[l].x)
            l = i;

    // Start from leftmost point, keep moving counterclockwise
    // until reach the start point again.  This loop runs O(h)
    // times where h is number of points in result or output.
    int p = l, q;
    do
    {
        // Add current point to result
        hull.push_back(points[p]);

        // Search for a point 'q' such that orientation(p, x,
        // q) is counterclockwise for all points 'x'. The idea
        // is to keep track of last visited most counterclock-
        // wise point in q. If any point 'i' is more counterclock-
        // wise than q, then update q.
        q = (p+1)%n;
        for (int i = 0; i < n; i++)
        {
           // If i is more counterclockwise than current q, then
           // update q
           if (orientation(points[p], points[i], points[q]) == 2)
               q = i;
        }

        // Now q is the most counterclockwise with respect to p
        // Set p as q for next iteration, so that q is added to
        // result 'hull'
        p = q;

    } while (p != l);  // While we don't come to first point

    // Print Result
    for (int i = 0; i < hull.size(); i++)
        cout << "(" << hull[i].x << ", "
              << hull[i].y << ")\n";
}

// Driver program to test above functions
int main()
{
    int n,i;cin>>n;
    Point points[n];
    for(i=0;i<n;i++)
    {
        cin>>points[i].x>>points[i].y;
    }
    cout<<"\n";
    convexHull(points, n);
    return 0;
}*/
