#include <iostream>
#include <cstdlib>
#include <climits>
#include <ctime> 
using namespace std;
class poin{
  double aa;
  double bb;
public:
  poin(){
      aa=(rand()/(double)RAND_MAX)*100;
      bb=(rand()/(double)RAND_MAX)*100;
  }
    double putx(){
      return aa;
    }
    double puty(){
      return bb;
    }
};

class point{
	double x;
	double y; 
public:
    void copy(poin A[],int i){
       x=A[i].putx();   
       y=A[i].puty();
    }
    void printt(){
      cout<<getx()<<" "<<gety()<<endl;
    }
    double getx(){
      return x;
    }
    double gety(){
      return y;
    }
    void fix(double xx,double yy)
    {
      x=xx;
      y=yy;
    }
    void sety(double l2){
      y=l2;
    }
    void setx(double l1){
      x=l1;
    }
};
 
   class RESULT{
        point cor1;
        point cor2;
         public:
          void add(point a[],int t1,int t2)
          {
            cor1.setx(a[t1].getx());
            cor2.setx(a[t2].getx());
            cor1.sety(a[t1].gety());
            cor2.sety(a[t2].gety());
          }
          void adder(point a[],int t1,point c[],int t2)
          {
            cor1.fix(a[t1].getx(),a[t1].gety());
            cor2.fix(c[t2].getx(),c[t2].gety());
          }
            double SQR(double s)
            {
              double u = s;
              double v = 1;
              double er = 0.000001; 
              while(u - v > er)
              {
                u = (u+v)/2;
                v = s/u;
              }
              return u;
            }
          double sep()
          {
            return SQR((cor1.getx()-cor2.getx())*(cor1.getx()-cor2.getx()) + ((cor1.gety()-cor2.gety())*(cor1.gety()-cor2.gety())));
          }
          void baser(){
            cor1.setx(0);
            cor1.sety(0);
            cor2.setx(100);
            cor2.sety(100);
          }
          void get()
          {
            cout<<"( "<<cor1.getx()<<", "<<cor1.gety()<<")"<<", ";
            cout<<"( "<<cor2.getx()<<", "<<cor2.gety()<<")"<<endl;
          }

      };

class co
{
 
  double SQRT(double s)
{
  double u = s;
  double v = 1;
  double er = 0.000001; 
  while(u - v > er)
  {
    u = (u+v)/2;
    v = s/u;
  }
  return u;
}
      double ABS(double wx){
        if(wx>=0){
          return wx;
        }
        return -1*wx;
      }

      double MIN(double wa,double wb){
        if(wa>=wb){
          return wb;
        }
        return wa;
      }

      int partition(point a[],int l,int r,bool w)
      {
      if(w==0){   // sort wrt  x
      int cur=l;
      for(int i=l+1;i<=r;++i){
        if((a[i].getx() < a[l].getx()) || (a[i].getx() == a[l].getx() && a[i].gety()<a[l].gety())){
         cur++;
         swap(a[cur],a[i]);
        }
      }
       swap(a[cur],a[l]);

      return cur;
      }

      int cur=l;  // sort wrt y
      for(int i=l+1;i<=r;++i){
        if((a[i].gety() < a[l].gety()) || (a[i].gety() == a[l].gety() && a[i].getx()<a[l].getx())){
         cur++;
         swap(a[cur],a[i]);
        }
      }
       swap(a[cur],a[l]);

      return cur;
      }  

      RESULT MERGE(point a[],RESULT delta,double del,int nl,int nr,double partx,double party,point bl[],point br[])
      {
         point bldelta[nl];
         point brdelta[nr];
         int ii=0;
         int cld=0;
         int crd=0;
         for(int yk=0;yk<nl;yk++){
          if(partx-bl[yk].getx()<=del){
            bldelta[ii++].fix(bl[yk].getx(),bl[yk].gety());
            cld++;
          }
         }
         ii=0;
         for(int yk=0;yk<nr;yk++){
          if(br[yk].getx()-partx<=del){
            brdelta[ii++].fix(br[yk].getx(),br[yk].gety());
            crd++;
          }
         }
         // cout<<"*"<<crd<<endl;
        RESULT min=delta;

        if(cld>0 && crd>0) {

         int mark=0;

         for (int ij = 0; ij < cld; ++ij)
         {
          while(1){
              if((bldelta[ij].gety()- del > brdelta[mark].gety()) && mark<crd){
                mark++;
              }else{
                break;
              }
         }
          for(int g=mark;g<=MIN(mark+6,crd-1);++g)
          {
            if(DIST(brdelta,g,bldelta,ij)<min.sep())
            {
              min.adder(brdelta,g,bldelta,ij);
            }
          }
         }

       }
         return min;
     }

          RESULT CLOSEST(point a[],int l,int r,int nb, point b[])
          {
            RESULT R;
          	if(r-l==1){
              R.add(a,l,r);
              return R;
          	}
          	if(r-l<1){
          		 R.baser();
               return R;
          	}
             int mid=(l+r)/2;
             double partx=a[mid].getx();
             double party=a[mid].gety();
             point aly[mid-l+1];
             point ary[r-mid];
             int ql=0;
             int qr=0;
             for(int z=0;z<nb;++z)
             {
                if(b[z].getx()<partx || (b[z].getx()==partx && b[z].gety()<=party))
                {
                  aly[ql++].fix(b[z].getx(),b[z].gety());                  
                }
                else
                { 
                  ary[qr++].fix(b[z].getx(),b[z].gety());
                }

             }
             RESULT delta1=CLOSEST(a,l,mid,mid-l+1,aly);
             RESULT delta2=CLOSEST(a,mid+1,r,r-mid,ary);
             RESULT delta;
             if(delta1.sep()>delta2.sep()){
              delta=delta2;
             }
             else{
              delta=delta1;
             }

             return MERGE(a,delta,delta.sep(),ql,qr,partx,party,aly,ary);
          }

          public:
            RESULT ANS(point a[],int n,point b[])
            {
             return CLOSEST(a,0,n-1,n,b); 
            }
             void quickSrt(point a[],int l,int r,bool w)
            {
              if(r<=l){
                return;
              }
              int k = l + ((rand())%(r-l+1));
              swap(a[k],a[l]);
              int part=partition(a,l,r,w);
              quickSrt(a,l,part-1,w);
              quickSrt(a,part+1,r,w);
            }

      double DIST(point a[],int i,int j)
      {
        return SQRT((a[i].getx()-a[j].getx())*(a[i].getx()-a[j].getx()) + (a[i].gety()-a[j].gety())*(a[i].gety()-a[j].gety()));
      }
      double DIST(point br[],int r,point bl[],int l){
        return SQRT((br[r].getx()-bl[l].getx())*(br[r].getx()-bl[l].getx()) + (br[r].gety()-bl[l].gety())*(br[r].gety()-bl[l].gety()));
      }

};
class call{
public:
void star(int n,poin A[],point ax[],point ay[]){
  for (int i = 0; i < n; ++i)
  {
      ax[i].copy(A,i);
  }
  for (int i = 0; i < n; ++i)
  {
      ay[i].copy(A,i);
  }
    co ans;
    ans.quickSrt(ax,0,n-1,0);
    ans.quickSrt(ay,0,n-1,1);

    RESULT re=ans.ANS(ax,n,ay);
    cout<<"Closest Distance: "<<re.sep()<<endl;
    cout<<"Points: ";
    re.get();
}
};

int main(){
  cout.precision(8);
  cout << fixed;
  srand(time(NULL));
	int n;
  cout<<"Enter number of points: "<<endl;
	cin>>n;
  clock_t start=clock();
  poin A[n];
  point ax[n];
  point ay[n];
  if(n<=1){
    cout<<"No pair exist"<<endl;
    clock_t end=clock();
    cout<<"Time Taken: "<<1000*((double)end-start)/CLOCKS_PER_SEC<<" ms"<<endl;
    return 0;
  }
    call st;
    st.star(n,A,ax,ay);
    clock_t end=clock();
    cout<<"Time Taken: "<<1000*((double)end-start)/CLOCKS_PER_SEC<<" ms"<<endl;
    return 0;
}