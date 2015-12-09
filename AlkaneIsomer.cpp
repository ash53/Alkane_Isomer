#include <iostream>
#include <vector>

using namespace std;

struct alkane
        {
            vector <unsigned char> rootedTree1;
            vector <unsigned char> rootedTree2;
            vector <unsigned char> rootedTree3;
            vector <unsigned char> rootedTree4;
            bool longestStraightChain;
        };

void FormRootedTree(vector<alkane>& alk,vector< vector <unsigned char> >& rootedTreeList,int cAtom);
void FormAlkane(vector<alkane>& alk,vector< vector <unsigned char> >& rootedTreeList,unsigned int posOfFirstRoot,
                unsigned int height,int cAtom);
void Initialize(vector<alkane>& alk,vector< vector <unsigned char> >& rootedTreeList);
void RootedTreeCase1(int a,int b,int c,vector< vector <unsigned char> >& rootedTreeList,unsigned int height,
                     int cAtom,unsigned int length,unsigned int posOfFirstRoot);
void RootedTreeCase2(int a,int b,int c,vector< vector <unsigned char> >& rootedTreeList,unsigned int height,
                     int cAtom,unsigned int length,unsigned int posOfFirstRoot);
void RootedTreeCase3(int a,int b,int c,vector< vector <unsigned char> >& rootedTreeList,unsigned int height,
                     int cAtom,unsigned int length,unsigned int posOfFirstRoot);
void AlkaneCase1(int a,int b,int c,int d,vector<alkane>& alk,vector< vector <unsigned char> >& rootedTreeList,
                 unsigned int height,int cAtom,unsigned int posOfFirstRoot);
void AlkaneCase2(int a,int b,int c,int d,vector<alkane>& alk,vector< vector <unsigned char> >& rootedTreeList,
                 unsigned int height,int cAtom,unsigned int posOfFirstRoot);
void AlkaneCase3(int a,int b,int c,int d,vector<alkane>& alk,vector< vector <unsigned char> >& rootedTreeList,
                 unsigned int height,int cAtom,unsigned int posOfFirstRoot);
void Add(vector< vector <unsigned char> >& rootedTreeList,int a,int b,int c);
void Add(vector<alkane>& alk,const vector< vector <unsigned char> >& rootedTreeList,unsigned int a,unsigned int b);
void Add(vector<alkane>& alk,const vector< vector <unsigned char> >& rootedTreeList,unsigned int a,unsigned int b,
         unsigned int c,unsigned int d);
void SortRootedTree (vector <vector <unsigned char> > & rootedTreeList,unsigned int length,int cAtom);

int main(void)
{
    int cAtom,hAtom=0;
    unsigned int i,a;
    vector <alkane> alk;
    vector< vector <unsigned char> > rootedTreeList;
    vector<long> output;

    cout<<"Enter the number of Carbon atoms: ";
    cin>>cAtom;
    cout << endl;

    FormRootedTree(alk, rootedTreeList, cAtom);
    output.resize(cAtom+1);
    for(i=0;i<=cAtom;i++)
        output[i]=0;
    for(i=0;i<alk.size();i++)
        {
            a=alk[i].rootedTree1.size()+alk[i].rootedTree2.size();
            if(alk[i].longestStraightChain==true)
                output[a]++;
            else
                output[a+alk[i].rootedTree3.size()+alk[i].rootedTree4.size()+1]++;
        }
    for(i=1;i<=cAtom;i++)
        {
            hAtom=(2*i)+2;
            if(i<10 && hAtom<10)
            cout <<"Alkane C0"<<i<<"H0"<<hAtom<<" Isomorph ";
            else if(i<10 && hAtom>=10)
            cout <<"Alkane C0"<<i<<"H"<<hAtom<<" Isomorph ";
            else
            cout <<"Alkane C"<<i<<"H"<<hAtom<<" Isomorph ";
            cout << output[i] << endl;
            hAtom=0;
        }
return 0;
}

//Form a complete list of all rooted trees of height h with maximum node n-h, here n= no of carbon atoms
void FormRootedTree(vector<alkane>& alk,vector< vector <unsigned char> >& rootedTreeList,int cAtom)
{
    int posOfFirstRoot=1;
    int height,length,a,b,c;

    Initialize(alk,rootedTreeList);
    FormAlkane(alk,rootedTreeList,posOfFirstRoot,1,cAtom);
    for(height=2;height<=int(cAtom/2);height++)
    {
        length=rootedTreeList.size();
        //two rooted trees of height less than h-1 and a rooted tree of height h - 1
        RootedTreeCase1(a,b,c,rootedTreeList,height,cAtom,length,posOfFirstRoot);
        //a rooted tree of height less than h-1 and two rooted trees of height h - 1
        RootedTreeCase2(a,b,c,rootedTreeList,height,cAtom,length,posOfFirstRoot);
        //three rooted trees of height h - 1
        RootedTreeCase3(a,b,c,rootedTreeList,height,cAtom,length,posOfFirstRoot);
        SortRootedTree(rootedTreeList,length,cAtom);
        posOfFirstRoot=length;
        //Form a list of alkanes with longest straight chain of length 2h or 2h-1
        //and maximum n nodes
        FormAlkane(alk,rootedTreeList,posOfFirstRoot,height,cAtom);
    }
}

void Initialize(vector<alkane>& alk,vector< vector <unsigned char> >& rootedTreeList)
{
    rootedTreeList.resize(2);
    rootedTreeList[0].resize(0);
    rootedTreeList[1].resize(1);
    rootedTreeList[1][0]=0;

    alk.resize(2);
    alk[0].longestStraightChain=true;
    alk[0].rootedTree1.resize(0);
    alk[0].rootedTree2.resize(0);
    alk[0].rootedTree3.resize(0);
    alk[0].rootedTree4.resize(0);
    alk[1].longestStraightChain=false;
    alk[1].rootedTree1.resize(0);
    alk[1].rootedTree2.resize(0);
    alk[1].rootedTree3.resize(0);
    alk[1].rootedTree4.resize(0);
}

void FormAlkane(vector<alkane>& alk,vector< vector <unsigned char> >& rootedTreeList,unsigned int posOfFirstRoot,
                unsigned int height,int cAtom)
{
    unsigned int a,b,c,d;
    if(2*height>cAtom) return;
     for(a=posOfFirstRoot;a<rootedTreeList.size();a++)
     {
         if(2*rootedTreeList[a].size()<=cAtom)
         {
             for(b=a;b<rootedTreeList.size();b++)
                if(rootedTreeList[a].size()+rootedTreeList[b].size()<=cAtom)
                {
                    Add(alk,rootedTreeList,a,b);
                }
                else
                    b=rootedTreeList.size();
         }
         else
            a=rootedTreeList.size();
     }
     if(2*height+1<=cAtom)
     {
         //two rooted trees of height less than h and 2 rooted trees of height h
         AlkaneCase1(a,b,c,d,alk,rootedTreeList,height,cAtom,posOfFirstRoot);
         //a rooted tree of height less than h  and 3 rooted trees of height h
         AlkaneCase2(a,b,c,d,alk,rootedTreeList,height,cAtom,posOfFirstRoot);
         //four rooted trees of height h
         AlkaneCase3(a,b,c,d,alk,rootedTreeList,height,cAtom,posOfFirstRoot);
     }
}



void RootedTreeCase1(int a,int b,int c,vector< vector <unsigned char> >& rootedTreeList,unsigned int height,
                     int cAtom,unsigned int length,unsigned int posOfFirstRoot)
{
    for(a=0;a<posOfFirstRoot;a++)
            {
                if(1+2*(int)rootedTreeList[a].size()+(height-1)+height<=cAtom)
                {
                    for(b=a;b<posOfFirstRoot;b++)
                    {
                        if(1+(int)rootedTreeList[a].size()+(int)rootedTreeList[b].size()+(height-1)+height<=cAtom)
                        {
                            for(c=posOfFirstRoot;c<length;c++)
                            {
                                if(1+(int)rootedTreeList[a].size()+(int)rootedTreeList[b].size()+(int)rootedTreeList[c].size()+height<=cAtom)
                                {
                                    Add(rootedTreeList,a,b,c);
                                }
                                else
                                    c=length;
                            }
                        }
                        else
                            b=posOfFirstRoot;
                    }
                }
                else
                    a=posOfFirstRoot;
                }
}

void RootedTreeCase2(int a,int b,int c,vector< vector <unsigned char> >& rootedTreeList,unsigned int height,
                     int cAtom,unsigned int length,unsigned int posOfFirstRoot)
{
    for(a=0;a<posOfFirstRoot;a++)
    {
        if(1+(int)rootedTreeList[a].size()+2*(height-1)+height<=cAtom)
        {
            for(b=posOfFirstRoot;b<length;b++)
            {
                if(1+(int)rootedTreeList[a].size()+2*((int)rootedTreeList[b].size())+height<=cAtom)
                {
                    for(c=b;c<length;c++)
                    {
                        if(1+(int)rootedTreeList[a].size()+(int)rootedTreeList[b].size()+(int)rootedTreeList[c].size()+height<=cAtom)
                        {
                           Add(rootedTreeList,a,b,c);
                        }
                        else
                            c=length;
                    }
                }
                else
                    b=length;
            }
        }
        else
            a=posOfFirstRoot;
    }
}

void RootedTreeCase3(int a,int b,int c,vector< vector <unsigned char> >& rootedTreeList,unsigned int height,
                     int cAtom,unsigned int length,unsigned int posOfFirstRoot)
{
    for(a=posOfFirstRoot;a<length;a++)
        {

            if(1+3*((int)rootedTreeList[a].size())+height<=cAtom)
            {
                for(b=a;b<length;b++)
                {
                    if(1+(int)rootedTreeList[a].size()+2*((int)rootedTreeList[b].size())+height<=cAtom)
                    {
                        for(c=b;c<length;c++)
                        if(1+(int)rootedTreeList[a].size()+(int)rootedTreeList[b].size()+(int)rootedTreeList[c].size()+height<=cAtom)
                        {
                            Add(rootedTreeList,a,b,c);
                        }
                        else
                            c=length;
                    }
                    else
                        b=length;
                }
            }
            else
                a=length;
        }
}

void AlkaneCase1(int a,int b,int c,int d,vector<alkane>& alk,vector< vector <unsigned char> >& rootedTreeList,
                 unsigned int height,int cAtom,unsigned int posOfFirstRoot)
{
    for(a=0;a<posOfFirstRoot;a++)
        {
            if(1+2*rootedTreeList[a].size()+2*height<=cAtom)
            {
                for(b=a;b<posOfFirstRoot;b++)
                {
                    if(1+rootedTreeList[a].size()+rootedTreeList[b].size()+2*height<=cAtom)
                {
                    for(c=posOfFirstRoot;c<rootedTreeList.size();c++)
                    {
                        if(1+rootedTreeList[a].size()+rootedTreeList[b].size()+2*rootedTreeList[c].size()<=cAtom)
                    {
                        for(d=c;d<rootedTreeList.size();d++)
                        if(1+rootedTreeList[a].size()+rootedTreeList[b].size()+rootedTreeList[c].size()+rootedTreeList[d].size()<=cAtom)
                        {
                            Add(alk,rootedTreeList,a,b,c,d);
                        }
                        else
                            d=rootedTreeList.size();
                    }
                    else
                        c=rootedTreeList.size();
                    }

                }
                else
                    b=posOfFirstRoot;
            }
            }
            else
                a=posOfFirstRoot;
        }
}

void AlkaneCase2(int a,int b,int c,int d,vector<alkane>& alk,vector< vector <unsigned char> >& rootedTreeList,
                 unsigned int height,int cAtom,unsigned int posOfFirstRoot)
{
    for(a=0;a<posOfFirstRoot;a++)
        {
            if(1+rootedTreeList[a].size()+3*height<=cAtom)
            {
                for(b=posOfFirstRoot;b<rootedTreeList.size();b++)
                if(1+rootedTreeList[a].size()+3*rootedTreeList[b].size()<=cAtom)
                {
                    for(c=b;c<rootedTreeList.size();c++)
                    if(1+rootedTreeList[a].size()+rootedTreeList[b].size()+2*rootedTreeList[c].size()<=cAtom)
                    {
                        for(d=c;d<rootedTreeList.size();d++)
                        if(1+rootedTreeList[a].size()+rootedTreeList[b].size()+rootedTreeList[c].size()+rootedTreeList[d].size()<=cAtom)
                        Add(alk,rootedTreeList,a,b,c,d);
                        else
                            d=rootedTreeList.size();
                    }
                    else
                        c=rootedTreeList.size();
                }
                    else
                        b=rootedTreeList.size();
            }
                    else
                        a=posOfFirstRoot;
        }
}

void AlkaneCase3(int a,int b,int c,int d,vector<alkane>& alk,vector< vector <unsigned char> >& rootedTreeList,
                 unsigned int height,int cAtom,unsigned int posOfFirstRoot)
{
    for(a=posOfFirstRoot;a<rootedTreeList.size();a++)
    {

      if(1+rootedTreeList[a].size()+3*height<=cAtom)
      {
        for(b=a;b<rootedTreeList.size();b++)
          if(1+rootedTreeList[a].size()+3*rootedTreeList[b].size()<=cAtom)
          {
            for(c=b;c<rootedTreeList.size();c++)
              if(1+rootedTreeList[a].size()+rootedTreeList[b].size()+2*rootedTreeList[c].size()<=cAtom)
              {
                for(d=c;d<rootedTreeList.size();d++)
                  if(1+rootedTreeList[a].size()+rootedTreeList[b].size()+rootedTreeList[c].size()+rootedTreeList[d].size()<=cAtom)
                  {
                    Add(alk,rootedTreeList,a,b,c,d);

                  }
                  else
                    d=rootedTreeList.size();
              }
              else
                c=rootedTreeList.size();
          }
          else
            b=rootedTreeList.size();
      }
      else
        a=rootedTreeList.size();
    }
  }


void Add(vector< vector <unsigned char> >& rootedTreeList,int a,int b,int c)
{
    int p=rootedTreeList.size();
    unsigned int i;
    int a_s=rootedTreeList[a].size();
    int b_s=rootedTreeList[b].size();
    int c_s=rootedTreeList[c].size();
    rootedTreeList.resize(p+1);
    rootedTreeList[p].resize(a_s+b_s+c_s+1);
    rootedTreeList[p][0]=0;
    rootedTreeList[p][1]=0;
    for(i=1;i<rootedTreeList[a].size();i++)
        rootedTreeList[p][i+1]=rootedTreeList[a][i]+1;
    rootedTreeList[p][1+a_s]=0;
    for(i=1;i<rootedTreeList[b].size();i++)
        rootedTreeList[p][i+1+a_s]=rootedTreeList[b][i]+1+a_s;
    rootedTreeList[p][1+a_s+b_s]=0;
    for(i=1;i<rootedTreeList[c].size();i++)
        rootedTreeList[p][i+1+a_s+b_s]=rootedTreeList[c][i]+1+a_s+b_s;
}

void Add(vector<alkane>& alk,const vector< vector <unsigned char> >& rootedTreeList,unsigned int a,unsigned int b)
{
    unsigned int i;
    int p=alk.size();
    alk.resize(p+1);
    alk[p].longestStraightChain=true;
    alk[p].rootedTree1.resize(rootedTreeList[a].size());
    for(i=0;i<rootedTreeList[a].size();i++)
        alk[p].rootedTree1[i]=rootedTreeList[a][i];
    alk[p].rootedTree2.resize(rootedTreeList[b].size());
    for(i=0;i<rootedTreeList[b].size();i++)
        alk[p].rootedTree2[i]=rootedTreeList[b][i];
    alk[p].rootedTree3.resize(0);
    alk[p].rootedTree4.resize(0);
}

void Add(vector<alkane>& alk,const vector< vector <unsigned char> >& rootedTreeList,unsigned int a,
         unsigned int b,unsigned int c,unsigned int d)
{
    unsigned int i;
    int p=alk.size();
    alk.resize(p+1);
    alk[p].longestStraightChain=false;
    alk[p].rootedTree1.resize(rootedTreeList[a].size());
    for(i=0;i<rootedTreeList[a].size();i++)
        alk[p].rootedTree1[i]=rootedTreeList[a][i];
    alk[p].rootedTree2.resize(rootedTreeList[b].size());
    for(i=0;i<rootedTreeList[b].size();i++)
        alk[p].rootedTree2[i]=rootedTreeList[b][i];
    alk[p].rootedTree3.resize(rootedTreeList[c].size());
    for(i=0;i<rootedTreeList[c].size();i++)
        alk[p].rootedTree3[i]=rootedTreeList[c][i];
    alk[p].rootedTree4.resize(rootedTreeList[d].size());
    for(i=0;i<rootedTreeList[d].size();i++)
        alk[p].rootedTree4[i]=rootedTreeList[d][i];
}

void SortRootedTree(vector< vector <unsigned char> >& rootedTreeList,unsigned int length,int cAtom)
{
    int i,j;
    unsigned int k,a,b;
    vector< vector< vector<unsigned char> > > sort;
    sort.resize(cAtom+1);
    for(i=0;i<=cAtom;i++)
        sort[i].resize(0);
    for(i=0;i<length;i++)
        {
            k=rootedTreeList[i].size();
            a=sort[k].size();
            sort[k].resize(a+1);
            sort[k][a].resize(k);
            for(b=0;b<k;b++)
             sort[k][a][b]=rootedTreeList[i][b];
        }
    j=0;
    for(i=0;i<=cAtom;i++)
        {
            for(a=0;a<sort[i].size();a++)
            {
                rootedTreeList[j].resize(i);
                for(b=0;b<(unsigned int)i;b++)
                    rootedTreeList[j][b]=sort[i][a][b];
                j++;
            }
        }
    sort.resize(cAtom+1);
    for(i=0;i<=cAtom;i++)
        {
            for(a=0;a<sort[i].size();a++)
            sort[i][a].resize(0);
            sort[i].resize(0);
        }
    for(i=length;i<(int)rootedTreeList.size();i++)
        {
            k=rootedTreeList[i].size();
            a=sort[k].size();
            sort[k].resize(a+1);
            sort[k][a].resize(k);
            for(b=0;b<k;b++)
                sort[k][a][b]=rootedTreeList[i][b];
        }
        for(i=0;i<=cAtom;i++)
            {
                for(a=0;a<sort[i].size();a++)
                    {
                        rootedTreeList[j].resize(i);
                        for(b=0;b<(unsigned int)i;b++)
                            rootedTreeList[j][b]=sort[i][a][b];
                        j++;
                    }
            }
        sort.resize(cAtom+1);
        for(i=0;i<=cAtom;i++)
            {
                for(a=0;a<sort[i].size();a++)
                sort[i][a].resize(0);
                sort[i].resize(0);
            }
}






