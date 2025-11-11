#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define sz(x) (int)x.size();

int main(){
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n;cin>>n;
    ll p1;cin>>p1;
    vector<int> a(p1);
    for(int i =0;i<p1;i++){
        cin>>a[i];
    }
    ll p2;cin>>p2;
    vector<int> b(p2);
    for(int i = 0;i<p2;i++){
        cin>>b[i];
    }
    vector<vector<bool>> v(n+1,vector<bool>(n+1,0));
    for(int i = 1;i<p1;i++){
        if(v[a[i-1]][a[i]]){
            cout<<"N"<<endl;
            return 0;
        }
        v[a[i-1]][a[i]] = 1;
        v[a[i]][a[i-1]] = 1;
    }

    for(int i = 1;i<p2;i++){
        if(v[b[i-1]][b[i]]){
            cout<<"N"<<endl;
            return 0;
        }
        v[b[i-1]][b[i]] = 1;
        v[b[i]][b[i-1]] = 1;
    }
    vector<int> d(n+1,0);
    vector<bool> m(n+1,0);
    int beg = -1;
    for(int i = 1;i<=n;i++){
        for(int j = 1;j<=n;j++){
            if(i==j){
                if(v[i][i]){
                    cout<<"N"<<endl;
                    return 0;
                }
                continue;
            }
            v[i][j] = 1-v[i][j];
            if(v[i][j]){
                d[i]++;
                m[i] = 1;
                beg = i;
            }
        }
    }

    if(beg == -1){
        if(p1*p2!=0){
            cout<<"N"<<endl;
        }
        else{
            cout<<"Y"<<endl;
        }
        return 0;
    }
    queue<int> q;
    vector<bool> vis(n+1,0);
    vis[beg] = 1;
    q.push(beg);
    while(!q.empty()){
        int p = q.front();
        q.pop();
        for(int i = 1;i<=n;i++){
            if(!vis[i]&&v[p][i]){
                vis[i] = 1;
                q.push(i);
            }
        }
    }
    if(vis!=m){
        cout<<"N"<<endl;
        return 0;
    }

    vector<int> odd;
    for(int i  = 1;i<=n;i++){
        if(d[i]%2){
            odd.push_back(i);
        }
    }
    if(odd.size()>2){
        cout<<"N"<<endl;
        return 0;
    }
    if(p1*p2 == 0){
        if(p1 == p2){
            cout<<"Y"<<endl;
            return 0;
        }
        if(odd.size() == 0){
            if(p1!=0){
                if(d[a[p1-1]]!=0){
                    cout<<"Y"<<endl;
                    return 0;
                }
                cout<<"N"<<endl;
                return 0;
            }
            if(d[b[0]]!=0){
                cout<<"Y"<<endl;
                return 0;
            }
            cout<<"N"<<endl;
            return 0;
        }
        if(p1 == 0){
            if(b[0] == odd[0] || b[0]== odd[1]){
                cout<<"Y"<<endl;
                return 0;
            }
            cout<<"N"<<endl;
            return 0;
        }
        if(a[p1-1] == odd[0]|| a[p1-1] == odd[1]){
            cout<<"Y"<<endl;
            return 0;
        }
        cout<<"N"<<endl;
        return 0;
    }
    if(odd.size() == 0){
        if(a[p1-1]!=b[0]){
            cout<<"N"<<endl;
            return 0;
        }
        else{
            if(d[b[0]]!=0){
                cout<<"Y"<<endl;
                return 0;

            }
            else{
                cout<<"N"<<endl;
                return 0;

            }
        }
        return 0;
    }
    sort(odd.begin(),odd.end());
    if(min(a[p1-1],b[0])!=odd[0] || max(a[p1-1],b[0])!= odd[1]){
        cout<<"N"<<endl;
        return 0;
    }
    cout<<"Y"<<endl;
    return 0;

    
    

}