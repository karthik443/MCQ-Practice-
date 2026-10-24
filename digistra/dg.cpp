#include<iostream>
#include<bits/stdc++.h>

using namespace std;
int main(){
    int n;
    int e;
    cin>>n>>e;

    vector<vector<pair<int,int>>>adj(n+1);

    for(int i=0;i<e;i++){
        int u,v,w;
        cin>>u>>v>>w;
        adj[u].push_back({v,w});
        adj[v].push_back({u,w});
    }
    int a,b;
    cin>>a>>b;

    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>>pq;
    vector<int>vis(n+1,1e9);
    vis[a]=0;
    pq.push({0,a});
    int ans = -1;
    while(pq.size()>0){
        auto &[w,v] = pq.top();pq.pop();

        if(v==b){
            ans = w;break;
        }
        for(auto &[child,dis]:adj[v]){
            if(dis+w<vis[child]){
                vis[child] = dis+w;
                pq.push({dis+w,child});
            }
        }
    }
    cout<<ans<<endl;
}