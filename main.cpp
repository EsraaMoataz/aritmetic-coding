#include <iostream>
#include <string>
#include<bits/stdc++.h>
#include<math.h>
using namespace std;

string outputEncoded="";




int charToIndex(char c,string Set)
{
    for(int i=0; i<Set.size(); i++)
    {
        if(Set[i]==c)
        {
            return i;
        }

    }
}

int cnt=0;
double l1=0;
int b=1;

string encoding(string mess,string Set,double L,double U,double cdf[],int Message_size)
{

    if(Message_size==0)
    {
        return outputEncoded;
    }



    int index=charToIndex(mess[cnt],Set);

    if(b)
    {
        if(index==0)
        {
            // L=L;
            U=L+(U-L)*cdf[index];
        }
        else
        {
            l1=L;
            L=L+(U-L)*cdf[index-1];
            U=l1+(U-l1)*cdf[index];

        }

    }


    if(L<0.5 && U<=0.5)
    {
        b=0;
        //cout<<"lower"<<endl;
        outputEncoded+='0';
        L=2*L;
        U=2*U;
        encoding(mess,Set,L,U,cdf,Message_size);


    }
    else if(L>=0.5 && U>0.5)
    {
        b=0;
        //cout<<"upper"<<endl;
        outputEncoded+='1';
        L=2*(L-0.5);
        U=2*(U-0.5);
        encoding(mess,Set,L,U,cdf,Message_size);

    }

    else
    {
        b=1;
        cnt++;
        //cout<<" error2"<<endl;

        encoding(mess,Set,L,U,cdf,Message_size-1);
        //cout<<"error1"<<endl;

    }


    return outputEncoded;

}
double binaryToDecimal(string s)
{
    double decimal_value=0;
    int counter=1;
    for(int i=0; i<s.size(); i++)
    {
        decimal_value+=(s[i]-'0')*pow(2,-counter);
        counter++;
    }
    return decimal_value;

}
int a=1;
string shift(int b,string s)
{
    string temp;
    temp=s.substr(a,b);
    a++;
    /* for(int i=1;i<binaryTag.size();i++){
      temp+=binaryTag[i];
     }
     if(b==1){temp+='1';}
     else {temp+='0';}*/

    return temp;
}
string output;
bool shifting=1;
string decoding(string binaryTag,string Set,double L,double U,double cdf[],int Message_size,double decimalTag,string s,int k)
{
    int x;
    if(Message_size==0)
    {
        /*cout<<"final"<<endl;*/return output;
    }
    double L1=L;
    double U1=U;
    for(int i=0; i<Set.size(); i++)
    {
        if(i==0)  //x=1
        {

            U=L1+(U1-L1)*cdf[i];
            //cout<<L<<" "<<U<<endl;

        }
        else
        {

            L=L1+(U1-L1)*cdf[i-1];
            U=L1+(U1-L1)*cdf[i];
            //cout<<L<<" "<<U<<endl;


        }
        if(decimalTag>=L && decimalTag<=U)
        {

            x=i;
            //cout<<x;
            break;
        }
    }
    output+=Set[x];
    //cout<<output<<endl;
    while((L<0.5 && U<=0.5) || (L>=0.5 && U>0.5))
    {
        binaryTag = shift(k,s);
        // cout<<L<<" "<<U<<endl;
        if(L<0.5 && U<=0.5)
        {

            //cout<<binaryTag<<endl;
            L=2*L;
            U=2*U;
            //cout<<L<<" "<<U<<endl;
        }
        else if(L>=0.5 && U>0.5)
        {

            //cout<<binaryTag<<endl;

            L=2*(L-0.5);
            U=2*(U-0.5);
            //cout<<L<<" "<<U<<endl;
        }


    }

    decimalTag = binaryToDecimal(binaryTag);
    // cout<<decimalTag<<endl;


    return decoding(binaryTag,Set,L,U,cdf,Message_size-1,decimalTag,s,k);
}


int main()
{

    string Set;
    string message;



    cout<<"Enter the set of symbol"<<endl;
    cin>>Set;
    int Size=Set.size();
    double probilityArr[Size]= {0};
    double cdf[Size]= {0};
    int Message_size;
    int sizeOfEncoding=0;
    int option;



    cout<<"Enter the probabilities"<<endl;

    for(int i=0; i<Size; i++)
    {
        cin>>probilityArr[i];
    }

    for(int i=0; i<Size; i++)
    {

        for(int j=0; j<=i; j++)
        {

            cdf[i]+=probilityArr[j];

        }


    }
    cout<<"1) Encoding"<<endl;
    cout<<"2) Decoding"<<endl;
    cout<<"Enter your option"<<endl;
    cin>>option;



    if(option==1)
    {

        cout<<"Enter the meesage to be encoded"<<endl;
        cin>>message;
        Message_size=message.size();
        cout<<"Enter the size of output encoding"<<endl;
        cin>>sizeOfEncoding;



        string finalEncoding=encoding(message,Set,0,1,cdf, Message_size);
        finalEncoding+='1';
        sizeOfEncoding=sizeOfEncoding-finalEncoding.size();


        while(sizeOfEncoding!=0)
        {
            finalEncoding+='0';
            sizeOfEncoding--;

        }
        cout<<finalEncoding<<endl;

    }


    if(option==2)
    {
        string sequence;
        string binaryTag;
        double decimalTag=0;
        int MessageLength=0;
        cout<<"Enter the sequence to be decoded"<<endl;
        cin>>sequence;
        cout<<"Enter the decoded message length"<<endl;
        cin>>MessageLength;
        int k;
        double minInterval=cdf[0];
        for(int i=1; i<Set.size(); i++)
        {
            if(cdf[i]-cdf[i-1]<minInterval)
            {
                minInterval=cdf[i]-cdf[i-1];
            }
        }

        k=-(floor(log2(minInterval)));

        for(int i=0; i<k; i++)
        {
            binaryTag+=sequence[i];
        }
        decimalTag=binaryToDecimal(binaryTag);
//11000110000000000000000000000000
        cout<<"the decoded message is "<<endl;
        cout<<decoding(binaryTag,Set,0,1,cdf,MessageLength,decimalTag,sequence,k)<<endl;

    }

    return 0;
}
