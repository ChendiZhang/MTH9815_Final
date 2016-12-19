
#ifndef GlobalFunction_h
#define GlobalFunction_h
#include <vector>
#include <fstream>
#include <sstream>
 
using namespace std;
template <typename T>
void FileVector(vector<T> vec, string name)
{
    ofstream output;
    output.open(name);
    for(auto i : vec)
    {
        output<<i<<endl;
    }
}

template <typename T>
void PrintVector(vector<T> vec)
{
    for(auto i : vec)
    {
        cout<<i<<endl;
    }
}
void trades_data()
{
    vector<string> v;
    
    for (int i=0; i<=59; i++) {
        string s=to_string(int(rand()%2+99))+'-';
        s+=to_string(int(rand()%4));
        s+=to_string(int(rand()%2));
        s+=to_string(int(rand()%8));
        //        cout<<"ddd"<<s.size();
        if (s[s.size()-1]=='4') {
            s[s.size()-1]='+';
        }
        v.push_back(s);
    }
    FileVector(v,"trades.txt");
}
void prices_data()
{
    vector<string> v;
    for (int i=0; i<=(1e+6)-1; i++) {
        string s;
        //CUSIP
        s="912828M72";
        s+=",";
        //mid
        s+=to_string(int(rand()%2+99))+'-';
        s+=to_string(int(rand()%4));
        s+=to_string(int(rand()%2));
        int rnd=int(rand()%8);
        s+=(rnd==4? "+" : to_string(rnd));
        s+=",";
        //spread
        s+="0-00";
        rnd=int(rand()%3+2);
        s+=(rnd==4? "+" : to_string(rnd));
        s+=",";
        
        v.push_back(s);
    }
    //    vector<string> v2;
    for (int i=0; i<=(1e+6)-1; i++) {
        string s;
        //CUSIP
        s="912828N22";
        s+=",";
        //mid
        s+=to_string(int(rand()%2+99))+'-';
        s+=to_string(int(rand()%4));
        s+=to_string(int(rand()%2));
        int rnd=int(rand()%8);
        s+=(rnd==4? "+" : to_string(rnd));
        s+=",";
        //spread
        s+="0-00";
        rnd=int(rand()%3+2);
        s+=(rnd==4? "+" : to_string(rnd));
        s+=",";
        
        v.push_back(s);
    }
    //    vector<string> v3;
    for (int i=0; i<=(1e+6)-1; i++) {
        string s;
        //CUSIP
        s="912828M98";
        s+=",";
        //mid
        s+=to_string(int(rand()%2+99))+'-';
        s+=to_string(int(rand()%4));
        s+=to_string(int(rand()%2));
        int rnd=int(rand()%8);
        s+=(rnd==4? "+" : to_string(rnd));
        s+=",";
        //spread
        s+="0-00";
        rnd=int(rand()%3+2);
        s+=(rnd==4? "+" : to_string(rnd));
        s+=",";
        
        v.push_back(s);
    }
    //    vector<string> v4;
    for (int i=0; i<=(1e+6)-1; i++) {
        string s;
        //CUSIP
        s="912828M80";
        s+=",";
        //mid
        s+=to_string(int(rand()%2+99))+'-';
        s+=to_string(int(rand()%4));
        s+=to_string(int(rand()%2));
        int rnd=int(rand()%8);
        s+=(rnd==4? "+" : to_string(rnd));
        s+=",";
        //spread
        s+="0-00";
        rnd=int(rand()%3+2);
        s+=(rnd==4? "+" : to_string(rnd));
        s+=",";
        
        v.push_back(s);
    }
    //    vector<string> v5;
    for (int i=0; i<=(1e+6)-1; i++) {
        string s;
        //CUSIP
        s="912828M56";
        s+=",";
        //mid
        s+=to_string(int(rand()%2+99))+'-';
        s+=to_string(int(rand()%4));
        s+=to_string(int(rand()%2));
        int rnd=int(rand()%8);
        s+=(rnd==4? "+" : to_string(rnd));
        s+=",";
        //spread
        s+="0-00";
        rnd=int(rand()%3+2);
        s+=(rnd==4? "+" : to_string(rnd));
        s+=",";
        
        v.push_back(s);
    }
    //    vector<string> v6;
    for (int i=0; i<=(1e+6)-1; i++) {
        string s;
        //CUSIP
        s="912810RP5";
        s+=",";
        //mid
        s+=to_string(int(rand()%2+99))+'-';
        s+=to_string(int(rand()%4));
        s+=to_string(int(rand()%2));
        int rnd=int(rand()%8);
        s+=(rnd==4? "+" : to_string(rnd));
        s+=",";
        //spread
        s+="0-00";
        rnd=int(rand()%3+2);
        s+=(rnd==4? "+" : to_string(rnd));
        s+=",";
        
        v.push_back(s);
    }
    
    
    
    
    FileVector(v,"prices.txt");
    cout<<"finish"<<endl;
}
void marketdata()
{
    vector<string> cusip_string;
    cusip_string.push_back("912828M72");
    cusip_string.push_back("912828N22");
    cusip_string.push_back("912828M98");
    cusip_string.push_back("912828M80");
    cusip_string.push_back("912828M56");
    cusip_string.push_back("912810RP5");
    
    vector<string> v;
    for (int i=1; i<=1e+2; i++) {
        for (int j=0; j<=5; j++) {
            string s;
            //cusip
            string cusip=cusip_string[j];
            //mid
            string midprice;
            midprice+=to_string(int(rand()%2+99))+'-';
            midprice+=to_string(int(rand()%4));
            midprice+=to_string(int(rand()%2));
            int rnd=int(rand()%8);
            midprice+=(rnd==4? "+" : to_string(rnd));
            //            midprice+=",";
            //spread
            for(int k=1; k<=4; k++)
            {
                //cusip
                s+=cusip+","+midprice+",";
                //spread
                s+="0-00";
                s+=(k==2? "+" : to_string((k)*2));
                s+=",";
                //quantity
                s+=to_string(int((k)*1e+7));
                s+=",";
            }
            //cusip
            s+=cusip+","+midprice+",";
            //spread
            s+="0-010";
            s+=",";
            //quantity
            s+=to_string(int((5)*1e+7));
            s+=",";
            
            v.push_back(s);
        }
    }
    //    PrintVector(v);
    FileVector(v,"marketdata_100.txt");
}
double get_price(string string_price)
{
    stringstream ss(string_price);
    string first;
    getline(ss, first, '-');
    string second;
    getline(ss,second);
    if(second[2]=='+') second[2]=4;
    
    int temp=stoi(second);
    int first_two_digits=temp/10;
    int third_digits=temp%10;
    
    double price=stoi(first)+first_two_digits/32.0+third_digits/256.0;
    return price;
    
}
double get_spread(string string_spread)
{
    stringstream ss(string_spread);
    string first;
    getline(ss, first, '-');
    string second;
    getline(ss,second);
    if(second[2]=='+') second[2]=4;
    
    int temp=stoi(second);
    double price=temp/256.0;
    
    return price;
    
}
#endif /* GlobalFunction_h */
