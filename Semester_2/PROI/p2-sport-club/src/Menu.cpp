//
// Created by wojtek on 15.04.18.
//

#include <iostream>

#include <vector>
#include <cstdlib>
#include "../include/Menu.hpp"

using namespace std;
string errmessage = "-->Error. Try again.";
bool err=1, ok=0;
Menu::Menu(){
    actionNo=-1;
}
Menu::Menu(string t, string q, vector<string>& opt, string w/*=defaultWrite*/){
    if(t.empty()) title = "";
    else title+=t;

    if (q.empty()) question="";
    else question+=q;

    for(int i=0;i<opt.size();++i){
        options.push_back(opt[i]);
    }

    write+=w;

    actionNo=-1;

}
Menu::Menu(string t, string q, string w/*="Enter appropriate command number: "*/){
    if(t.empty()) title = "";
    else title+=t;

    if (q.empty()) question="";
    else question+=q;

    write+=w;

    actionNo=-1;
}

int Menu::show(string message){
#if defined(WIN32) || defined(_WIN32)
    system("cls");
#endif
    cout<<endl;
    if(!message.empty()) cout<<message<<endl;
    cout<<"---"<<title<<"---"<<endl;
    cout<<question<<endl;
    for (int i=0;i<options.size();++i){
        cout<<i+1<<". "<<options[i]<<endl;
    }
    int k;
    while(true){
        cout<<write;
        cin>>k;
        if(!cin || k<1 || k>options.size() ){
            cin.clear();
            cin.ignore(1000,'\n');
            cout<<errmessage<<endl;
            continue;
        }
        break;
    }
    actionNo=--k;
    return k;
}

int Menu::addOption(string opt, int position/*=-1 starting from 0, -1 means end*/){
    if(opt.empty()) return err;

    if(position==-1) options.push_back(opt);
    else options.insert(options.begin()+position, opt);

    return ok;
}

int Menu::eraseOption(int position/*starting from 0*/){
    if(position<0||position>=options.size() ) return err;
    options.erase(options.begin()+position);
    return ok;
}
int Menu::eraseOption(int first, int last){
    if(first>last || first<0 || last<0 || first>=options.size() || last>=options.size() ) return err;

    options.erase(options.begin()+first,options.begin()+last);
    return ok;
}

Menu::~Menu(){
    options.clear();
}