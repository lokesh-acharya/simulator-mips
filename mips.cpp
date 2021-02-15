#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <cmath>

using namespace std;

int cycles(string s){
  if(s=="add"||"sub"||"sll"||"srl") return 1;
  else if(s=="sw"||"lw"||"j"||"jr"||"jal"||"beq"||"bne"||"bgtz"||"blez") return 2;
  else return 0;  
}

int regIndex(string s){
  
    if (s=="$zero") // code to be executed if n = 1;
      return 0;
    if (s=="$at") // code to be executed if n = 1;
      return 1;
    if (s=="$v0") // code to be executed if n = 1;
      return 2;
    if (s=="$v1") // code to be executed if n = 1;
      return 3;
    if (s=="$a0") // code to be executed if n = 1;
      return 4;
    if (s=="$a1") // code to be executed if n = 1;
      return 5;
    if (s=="$a2") // code to be executed if n = 1;
      return 6;
    if (s=="$a3") // code to be executed if n = 1;
      return 7;
    if (s=="$t0") // code to be executed if n = 1;
      return 8;
    if (s=="$t1") // code to be executed if n = 1;
      return 9;
    if (s=="$t2") // code to be executed if n = 1;
      return 10;
    if (s=="$t3") // code to be executed if n = 1;
      return 11;
    if (s=="$t4") // code to be executed if n = 1;
      return 12;
    if (s=="$t5") // code to be executed if n = 1;
      return 13;
    if (s=="$t6") // code to be executed if n = 1;
      return 14;
    if (s=="$t7") // code to be executed if n = 1;
      return 15;
    if (s=="$t0") // code to be executed if n = 1;
      return 16;
    if (s=="$s1") // code to be executed if n = 1;
      return 17;
    if (s=="$s2") // code to be executed if n = 1;
      return 18;
    if (s=="$s3") // code to be executed if n = 1;
      return 19;
    if (s=="$s4") // code to be executed if n = 1;
      return 20;
    if (s=="$s5") // code to be executed if n = 1;
      return 21;
    if (s=="$s6") // code to be executed if n = 1;
      return 22;
    if (s=="$s7") // code to be executed if n = 1;
      return 23;
    if (s=="$t8") // code to be executed if n = 1;
      return 24;
    if (s=="$t9") // code to be executed if n = 1;
      return 25;
    if (s=="$k0") // code to be executed if n = 1;
      return 26;
    if (s=="$k1") // code to be executed if n = 1;
      return 27;
    if (s=="$gp") // code to be executed if n = 1;
      return 28;
    if (s=="$sp") // code to be executed if n = 1;
      return 29;
    if (s=="$fp") // code to be executed if n = 1;
      return 30;
    if (s=="$ra") // code to be executed if n = 1;
      return 31;
    else // code to be executed if n doesn't match any cases
      return -1;
}

int main(){

  int cc=0;

  int memo[4000];
  string line;
  int lnum=0;
  bool mode=false;
  vector<string> inst;
  vector< pair <string,string> > labels;
  int regs[32];
  for(int j=0;j<32;j++){
    regs[j]=0;
  }
  regs[9]=100;
  regs[10]=400;

  ifstream myfile ("example");
  int i=0;
  while ( getline (myfile,line) )
  {
    lnum++;
    inst.push_back(line);
    cout<<inst[i]<<endl;
    i++;
    
    istringstream ss(line); 
    int num=0;
  
    do { 
        string word; 
        ss >> word;
        num++;
        if(num==2) break;

        if(mode==true){
          if((word!="end")and(word!="")and(word!="add")and (word!="sub")and (word!="sll")and (word!="srl")and (word!="lw")and (word!="sw")and(word!="j")and (word!="jal")and (word!="jr")and (word!="bne")and (word!="beq")and (word!="blez")and (word!="bgtz")){
            if(word.back()==':'){
              word.pop_back();
            }
            labels.push_back(make_pair(word,to_string(lnum)));
            cout<<labels.size()<<endl;
            cout<<labels.back().first<<" "<<labels.back().second<<endl;
            break;
          }
        } 

        if(word==".text"){
          mode=true;
          break;
        } 

        if(word==".data"){
          mode=false;
          break;
        }
  
    } while (ss);

  }
  myfile.close(); 

  bool exe=true;
  int index=0;
  for(int i=0; i<labels.size();i++){
    if(labels.at(i).first=="main"){
      index=stoi(labels.at(i).second);
      cout<<"main found"<<endl;
      exe=true;
      break;
    }
    if(i==labels.size() && labels.at(i).first!="main"){
      exe=false;
      cout<<"main not found"<<endl;
    }
  } 
  while(exe==true){
    while(inst.at(index)=="" && index<inst.size()){
      index++;
    }
    if(index==inst.size()) exe=false;
    else{
    int s,t,d=0;
    string tmp=inst.at(index);
    istringstream ss(tmp); 
    string word;
    ss >> word;

    if(word=="end"){
      exe=false;
      cout<<"cycle count: "<<cc<<endl;
      cout<<"over and out"<<endl;
    }

    if(word=="add"){
      cc=cc+cycles("add");
      ss>>word;
      word.pop_back();
      d=regIndex(word);
      ss>>word;
      word.pop_back();
      s=regIndex(word);
      ss>>word;
      t=regIndex(word);
      regs[d]=regs[s]+regs[t];
      index++;

      cout<<regs[d]<<endl;
      cout<<"add executed"<<endl;
    }

    if(word=="sub"){
      cc=cc+cycles("sub");
      ss>>word;
      word.pop_back();
      d=regIndex(word);
      ss>>word;
      word.pop_back();
      s=regIndex(word);
      ss>>word;
      t=regIndex(word);
      regs[d]=regs[s]-regs[t];
      index++;

      cout<<regs[d]<<endl;
      cout<<"sub executed"<<endl;
    }

    if(word=="sll"){
      cc=cc+cycles("sll");
      ss>>word;
      word.pop_back();
      d=regIndex(word);
      ss>>word;
      word.pop_back();
      t=regIndex(word);
      ss>>word;
      double shamt=stoi(word)+0.0;
      regs[d]=regs[t]*pow(2.0,shamt);
      index++;
      cout<<regs[d]<<endl;
      cout<<"sll executed"<<endl;
    }

    if(word=="srl"){
      cc=cc+cycles("srl");
      ss>>word;
      word.pop_back();
      d=regIndex(word);
      ss>>word;
      word.pop_back();
      t=regIndex(word);
      ss>>word;
      double shamt=stoi(word)+0.0;
      regs[d]=regs[t]/pow(2.0,shamt);
      index++;
      cout<<regs[d]<<endl;
      cout<<"srl executed"<<endl;
    }

    if(word=="lw"){
      cc=cc+cycles("lw");
      cout<<"entered lw"<<endl;

      ss>>word;
      word.pop_back();
      t=regIndex(word);
      ss>>word;
      cout<<word<<endl;

      string sstr = word.substr(0, (word.size()-5));
      cout<<sstr<<endl;

      int off=stoi(sstr);
      cout<<off<<endl;

      string r = word.substr(word.size()-3,word.size()-1);
      s=regIndex(r);
      regs[t]=memo[regs[s]+off/4];
      cout<<regs[t]<<endl;

      index++;
      cout<<"lw executed"<<endl; 
    }

    if(word=="sw"){
      cc=cc+cycles("sw");
      cout<<"entered sw"<<endl;

      ss>>word;
      word.pop_back();
      t=regIndex(word);
      ss>>word;
      cout<<word<<endl;

      string sstr = word.substr(0, (word.size()-5));
      cout<<sstr<<endl;

      int off=stoi(sstr);
      cout<<off<<endl;

      string r = word.substr(word.size()-3,word.size()-1);
      s=regIndex(r);
      memo[regs[s]+off/4]=regs[t];
      index++; 
      cout<<regs[t]<<endl;
      cout<<"sw executed"<<endl;
    }

    if(word=="j"){
      cc=cc+cycles("j");
      ss>>word;
      bool found=false;
      int it=0;
      while(it<labels.size() && found==false){
        if(labels.at(it).first==word){
          found=true;
          index=stoi(labels.at(it).second);
          cout<<index<<endl;
          cout<<"j executed"<<endl;
        }
        it++;
      }
      if(found==false){
        cout<<"label not exist"<<endl;
        exe=false;
        cout<<"cycle count: "<<cc<<endl;
        cout<<"over and out"<<endl;
      }
    }

    if(word=="jr"){
      cc=cc+cycles("jr");
      ss>>word;
      if(0<=regs[31]<inst.size()){
      index=regs[regIndex(word)];
      cout<<"jr executed"<<endl;
      }
      else{
        cout<<"ra address not valid"<<endl;
        exe=false;
        cout<<"cycle count: "<<cc<<endl;
        cout<<"over and out"<<endl;
      }
    }

    if(word=="jal"){
      cc=cc+cycles("jal");
      regs[31]=index+1;
      ss>>word;
      bool found=false;
      int it=0;
      while(it<labels.size() && found==false){
        if(labels.at(it).first==word){
          found=true;
          index=stoi(labels.at(it).second);
          cout<<"jal executed"<<endl;
        }
        it++;
      }
      if(found==false){
        cout<<"label not exist"<<endl;
        exe=false;
        cout<<"cycle count: "<<cc<<endl;
        cout<<"over and out"<<endl;
      }
    }

    if(word=="beq"){
      cc=cc+cycles("beq");
      ss>>word;
      word.pop_back();
      s=regIndex(word);
      ss>>word;
      word.pop_back();
      t=regIndex(word);
      ss>>word;
      if(regs[s]==regs[t]){
      bool found=false;
      int it=0;
      while(it<labels.size() && found==false){
        if(labels.at(it).first==word){
          found=true;
          index=stoi(labels.at(it).second);
          cout<<"beq executed"<<endl;
        }
        it++;
      }
      if(found==false){
        cout<<"label not exist"<<endl;
        exe=false;
        cout<<"cycle count: "<<cc<<endl;
        cout<<"over and out"<<endl;
      }
      }
      else index++;
    }

    if(word=="bne"){
      cc=cc+cycles("bne");
      ss>>word;
      word.pop_back();
      s=regIndex(word);
      ss>>word;
      word.pop_back();
      t=regIndex(word);
      ss>>word;
      if(regs[s]!=regs[t]){
      bool found=false;
      int it=0;
      while(it<labels.size() && found==false){
        if(labels.at(it).first==word){
          found=true;
          index=stoi(labels.at(it).second);
          cout<<"bne executed"<<endl;
        }
        it++;
      }
      if(found==false){
        cout<<"label not exist"<<endl;
        exe=false;
        cout<<"cycle count: "<<cc<<endl;
        cout<<"over and out"<<endl;
      }
      }
      else index++;
    }

    if(word=="blez"){
      cc=cc+cycles("blez");
      ss>>word;
      word.pop_back();
      s=regIndex(word);
      ss>>word;
      if(regs[s]<=0){
      bool found=false;
      int it=0;
      while(it<labels.size() && found==false){
        if(labels.at(it).first==word){
          found=true;
          index=stoi(labels.at(it).second);
          cout<<"blez executed"<<endl;
        }
        it++;
      }
      if(found==false){
        cout<<"label not exist"<<endl;
        exe=false;
        cout<<"cycle count: "<<cc<<endl;
        cout<<"over and out"<<endl;
      }
      }
      else index++;
    }

    if(word=="bgtz"){
      cc=cc+cycles("bgtz");
      ss>>word;
      word.pop_back();
      s=regIndex(word);
      ss>>word;
      if(regs[s]>0){
      bool found=false;
      int it=0;
      while(it<labels.size() && found==false){
        if(labels.at(it).first==word){
          found=true;
          index=stoi(labels.at(it).second);
          cout<<"bgtz executed"<<endl;
        }
        it++;
      }
      if(found==false){
        cout<<"label not exist"<<endl;
        exe=false;
        cout<<"cycle count: "<<cc<<endl;
        cout<<"over and out"<<endl;
      }
      }
      else index++;
    }
    }

  }

  return 0;
}
