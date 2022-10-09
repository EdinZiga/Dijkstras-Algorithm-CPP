#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
#include <string>
#include <strstream>
#include <sstream>
using namespace std;


/*
MATH209 Discrete Mathematics 2 Final Project
Implementation of Dijkstra's Algorithm
By Edin Ziga
   ⠀⠀⠀⠀⠀⠀⠀⠀⣠⣤⣤⣤⣤⣤⣶⣦⣤⣄⡀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⣿⡿⠛⠉⠙⠛⠛⠛⠛⠻⢿⣿⣷⣤⡀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⣼⣿⠋⠀⠀⠀⠀⠀⠀⠀⢀⣀⣀⠈⢻⣿⣿⡄⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⣸⣿⡏⠀⠀⠀⣠⣶⣾⣿⣿⣿⠿⠿⠿⢿⣿⣿⣿⣄⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⣿⣿⠁⠀⠀⢰⣿⣿⣯⠁⠀⠀⠀⠀⠀⠀⠀⠈⠙⢿⣷⡄⠀
⠀⠀⣀⣤⣴⣶⣶⣿⡟⠀ ⠀⢸⣿⣿⣿⣆⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣷⠀
⠀⢰⣿⡟⠋⠉⣹⣿⡇⠀⠀⠘⣿⣿⣿⣿⣷⣦⣤⣤⣤⣶⣶⣶⣶⣿⣿⣿⠀
⠀⢸⣿⡇⠀⠀⣿⣿⡇⠀⠀⠀⠀⠹⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⡿⠃⠀
⠀⣸⣿⡇⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠉⠻⠿⣿⣿⣿⣿⡿⠿⠿⠛⢻⣿⡇⠀⠀
⠀⣿⣿⠁⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣧⠀⠀
⠀⣿⣿⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⠀⠀
⠀⣿⣿⠀⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⠀⠀
⠀⢿⣿⡆⠀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⡇⠀⠀
⠀⠸⣿⣧⡀⠀⣿⣿⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⠃⠀⠀
⠀⠀⠛⢿⣿⣿⣿⣿⣇⠀ ⠀⠀⣰⣿⣿⣷⣶⣶⣶⣶⠶⠀⢠⣿⣿⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⣿⣿⡇⠀⣽⣿⡏⠁⠀⠀⢸⣿⡇⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⣿⣿⠀⠀⠀⠀⠀⣿⣿⡇⠀⢹⣿⡆⠀⠀⠀⣸⣿⠇⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⢿⣿⣦⣄⣀⣠⣴⣿⣿⠁⠀⠈⠻⣿⣿⣿⣿⡿⠏⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠈⠛⠻⠿⠿⠿⠿⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀

*/
//First utility function that
//transferes all the connections
//from the .csv file to a vector array
//Returns true if passed
bool PathsBootLoader(vector<int> connections[]){
  bool sw=0;
  int a,b;
  string line,fline="",sline="";
  ifstream myfile ("FromTo.csv");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
        sw=0;
      for(int i=0; i<line.size(); i++){

        if(line[i]==',') {
            sw=1;
            i++;
            for(int j=i; j<line.size();j++){
                sline.push_back(line[j]);
            }
        }

        if(line[i]!=',' && sw==0)
            fline.push_back(line[i]);
      }

      a=stoi(fline);
      b=stoi(sline);
      connections[a].push_back(b);
      connections[b].push_back(a);
      fline.clear();
      sline.clear();
    }
    myfile.close();
  }
  else{
    cout << "Unable to open file";
    return false;
  }
 cout<<"Paths bootloader passed "<<endl;
return true;
}

//Second utility function
//transfers city names into
//single vector. Vector indexes
//correspond with city indexes within
//the file given
//Returns true if passed
bool StringBootLoader(vector<string> &IToS){
  string line,sline="";
  ifstream myfile ("cityName.csv");
  IToS.push_back("");
  if (myfile.is_open())
  {
    while ( getline (myfile,line) )
    {
      for(int i=0; i<line.size(); i++){

        if(line[i]==',') {
            i++;
            for(int j=i; j<line.size();j++ ){
                sline.push_back(line[j]);
                i=j;
            }
        }

      }
      IToS.push_back(sline);
      sline.clear();
    }
    myfile.close();
  }
  else{
    cout << "Unable to open file";
    return false;
  }
 cout<<"String bootloader passed"<<endl;
return true;
}

//Converts inputed strings(city names)
//into their numerical counterparts
//Returns true if passed
bool StringConverter(vector<string> &IToS,
                     string sc1, string sc2,
                     int &c1, int &c2){
    bool sw1=0,sw2=0;
    for(int i=1; i<IToS.size(); i++){
        if(sc1==IToS[i]) {c1=i;sw1=1;}
        if(sc2==IToS[i]) {c2=i;sw2=1;}
    }

    if(sw1==1 && sw2==1){
        cout<<"StringConverter Passed"<<endl;
        return true;
    } else {
        cout<<"StringConverter Failed, please enter names from the list."<<endl;
        return false;
    }
}

void DijkstraAlgorithm(vector<int> connections[],
                       vector<string> IToS, int np,
                       int str, int fin){
    vector<int> q; //Simple queue system for finding algorithm
    //Previous-saves previous point of the index number point.
    //Distance-saves distance of that index number point from given start.
    int previous[np],dist[np];
    int inf=INT_MAX; //representation of infinity
    bool covered[np]; //Array that saves point coverage

    //Fills all the arrays
    for (int i = 0; i < np; i++) {
        dist[i] = inf;
        previous[i] = NULL;
        covered[i] = false;
    }

    //Adds the starting point to the queue
    //sets the starting as covered and its
    //distance as 0
    q.push_back(str);
    covered[str] = true;
    dist[str] = 0;

    //Algorithm that tries to find the
    //final point by searching the reachable
    //points from the start, while
    //saving the previous point for every point reached.
    bool sw=0;
     while (q.empty()==false) {
        int qfront = q.front();
        q.erase(q.begin());
        for (int i = 0; i < connections[qfront].size(); i++) {
            if (covered[connections[qfront][i]] == false)
                {
                q.push_back(connections[qfront][i]);
                covered[connections[qfront][i]] = true;
                dist[connections[qfront][i]] = dist[qfront] + 1;
                previous[connections[qfront][i]] = qfront;

                //Stops when it finds fin
                if (connections[qfront][i] == fin)
                    {sw=1;break;}
            }
        }
        //Second break to stop queue
        if(sw) break;
    }


    //If it find the final point, backtracks it's way
    //through the previous array and saves ever step into
    //pathFinder
    if(sw){
    vector<int> pathFinder;
    int Dijk = fin;
    pathFinder.push_back(Dijk);
    while (previous[Dijk] != NULL) {
        pathFinder.push_back(previous[Dijk]);
        Dijk = previous[Dijk];}

    //Console output function
    cout << IToS[str]<<" to "<<IToS[fin]<<" path length is: "<<pathFinder.size()-1<<endl;
    cout << "Path is: "<<endl;
    for (int i = pathFinder.size() - 1; i >= 0; i--)
        cout << IToS[pathFinder[i]]<<" ";
        cout<<endl;
    }else{
        cout << IToS[str]<<" to "<<IToS[fin]<<" path length is: infinity"<<endl;
        cout<<"In English - that specific combination cannot be reached"<<endl;
    }


}


//Main function for testing everything
int main(){
    int c1,c2;
    string sc1, sc2;
    int np=1175; //Number of points
    vector<int> connections[np]; //Storage for paths for individual points
    vector<string> IToS; //City Names storage

    //Loop that starts if both bootloaders pass
    if(PathsBootLoader(connections)==true && StringBootLoader(IToS)==true){
           while (1){
                //Lists the cities and their numbers
                for(int i=1; i<IToS.size(); i++){
                cout<<i<<" - "<<IToS[i]<<" ";
                if(i%4==0)cout<<endl;
            }
            cout<<endl;
                cout<<"Enter the start city, then the destination city"<<endl;
                cout<<"To break the loop, enter 0"<<endl;
                getline(cin, sc1);
                getline(cin, sc2);
                if (sc1=="0" || sc2=="0") break;
                if(StringConverter(IToS,sc1,sc2,c1,c2))
                {
                    system("CLS");
                DijkstraAlgorithm(connections,IToS,np,c1,c2);
                }
                system("PAUSE");
                system("CLS");
            }
    }

return 0;
}
