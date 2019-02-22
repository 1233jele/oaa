#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <stack>
#include <queue>
#include <limits>

#define INF std::numeric_limits<int>::max()


void print_adj_list(std::map<std::string, std::set<std::string>> adj_list)
{
    std::cout<<"adj_list: "<<std::endl;
    for(std::map<std::string, std::set<std::string>>::iterator it=adj_list.begin(); it!=adj_list.end(); ++it)
    {
        std::cout<<it->first<<" = ";
        for(std::set<std::string>::iterator it2=it->second.begin(); it2!=it->second.end(); ++it2)
            std::cout<<*it2<<" ";
        std::cout<<std::endl;
    }
    std::cout<<std::endl;

}

bool doublets(std::string s1, std::string s2)
{
    if(s1==s2 || s1.size()!=s2.size()) return false;

    int cnt=0;

    for(size_t i=0; i<s1.size(); ++i){
        if(s1[i]!=s2[i] && ++cnt>1) return false;
    }

    return true;

}

void fill(std::vector<std::string> dict,std::map<std::string, std::set<std::string>>& adj_list, std::string w)
{
    std::set<std::string> s;
    adj_list[w]=s;
    for(size_t i=0; i<dict.size(); ++i)
        if(doublets(dict[i], w))
            {
                adj_list[w].insert(dict[i]);
                adj_list[dict[i]].insert(w);
            }
}

void shortest_path(std::string i, std::string j, std::vector<std::string> dict ,std::map<std::string, std::set<std::string>> adj_list)
{
    std::map<std::string, std::string> parent;
    parent[i]="0";
    std::map<std::string, int> dist;

    std::map<std::string, bool> sptSet;
    for(size_t i=0; i<dict.size(); ++i)
    {
        dist[dict[i]]=INF;
        sptSet[dict[i]]=false;
    }

    dist[i]=0;

    int flag=0;
    for(size_t count=0; count < dict.size(); ++count)
    {
        std::string min_index;
        int min=INF;
        for(size_t u=0; u<dict.size(); ++u)
            if(sptSet[dict[u]]==false &&  dist[dict[u]]<=min)
            {
                min=dist[dict[u]];
                min_index=dict[u];
            }
        std::string u=min_index;

        if(u==j) break;
        sptSet[u]=true;

        flag=0;
        for(size_t v=0; v<dict.size(); ++v)
        {
            if(!sptSet[dict[v]] && adj_list[u].find(dict[v])!=adj_list[u].end() && dist[u]<INF && (dist[u]+1) < dist[dict[v]])
            {
                dist[dict[v]]=dist[u]+1;
                parent[dict[v]]=u;
                flag=1;
            }
        }

    }

    if(flag)
    {
        std::cout<<"Output: \n";
        std::string a=j, b=parent[j];
        std::stack<std::string> S;
        while(parent[a]!="0")
        {
            S.push(a);
            a=parent[a];
            b=parent[a];

        }
        S.push(i);
        while(!S.empty())
        {
            std::cout<<S.top()<<std::endl;
            S.pop();
        }
    }
    else {
        std::cout<<"No solution."<<std::endl;
    }

    return;
}

int main()
{
    std::ifstream myfile;
    std::string line;
    myfile.open("C:/Users/Jelena/Documents/4.godina/OAA/OAA_zadaca/dictionary.txt");
    if(!myfile.is_open())
    {
        std::cout<<"nije ucitana datoteka: "<<std::endl;
        exit(-1);
    }

        //std::cout<<"good"<<std::endl;


    std::vector<std::string> dict;
    std::vector<std::pair<std::string, std::string>> pairs;

    std::map<std::string, std::set<std::string>> adj_list;
    getline(myfile, line);
    if(line.empty())
        std::cout<<"nema rijecnika"<<std::endl;

    std::stringstream ss1(line);
    std::string p;
    ss1 >> p;
    dict.push_back(p);
    std::set<std::string> s;
    adj_list[p]=s;
    getline(myfile, line);
    while(!line.empty())
    {
        std::stringstream ss(line);
        std::string w;
        ss >> w;
        fill(dict, adj_list, w);
        dict.push_back(w);
        getline(myfile, line);
    }

    //print_adj_list(adj_list);

    while(getline(myfile,line))
    {
        std::stringstream ss1(line);
        std::string p1, p2;
        ss1 >> p1 >> p2;
        shortest_path(p1,p2,dict, adj_list);
        std::cout<<std::endl;
    }

    myfile.close();
    return 0;
}
