#include<iostream>
#include<iomanip>
#include<fstream>
#include<cmath>
#include<ctime>
#define M 10000000  //��
#define h 3   //���  ��
#define Dx 50  //m^2/s
#define Dy 0.5
#define u 0.5   //m/s
#define v 0
#define ROW 788  //������
#define VOL 2   //������
#define R 6371393  //����뾶
#define Pi 3.1415926
#define kc 1.15e-06  // 1/s
#define c0 5    //����Ũ��
#define shichang 1440  //��ʱ��
#define jiange 60    //���
using namespace std;
int main()
{
	double d[ROW][VOL];  //����
	double mid[ROW/2][VOL]; //�е�
	double L[ROW/2-1];  //�������
	double xs[ROW/2][VOL]; //ÿ�����淽��ϵ��
	double bj[ROW/2];   //�ֶ�λ��ȾԴ�ı��
	double D[ROW*7/2][5]; //������
	double wuran_d; //��ȾԴ�����ڶ������ߵľ���
	double k,b; //��ȾԴ���ڶ��������ߵ�б����ؾ�
	double x_jd,y_jd; //��ȾԴ���ڶ��������ߵĽ�������
	int xiabiao=0;
	double wuran_sx[5]; //  ��ȾԴλ������
	double Length_dm[ROW/2]; //ÿ������ĳ���
	double dian[ROW*7/2][2]; //���㵽��ȾԴ��x��y�����ϵľ���
	double s[ROW/2]={0}; //�����泤���ۼӺ�
	double C[ROW*7/2][24]; //��ͬʱ����Ⱦ�̶�
	int flag=0; //��¼��ͬyֵ�Ķ���
	//�ļ�����
	ifstream in("C:\\Users\\TR\\Desktop\\������.txt");
	for(int i = 0; i < ROW; ++i)
	{
		for(int j = 0; j < VOL; ++j){
			in >> d[i][j];
		}
	}
	in.close();
	/*for(int i = 0; i < ROW; ++i){
		for(int j = 0; j < VOL; ++j){
			cout<<d[i][j]<<" ";
		}
		cout<<endl;
	}*/
	/*for(int i=0;i<ROW;i=i+2)
    {
        if(d[i][1]==d[i+1][1])
        flag++;
    }
    cout<<flag<<endl;*/
	for(int i=0;i<ROW-1;i=i+2)
    {
        //�Ӱ��е�
        mid[i/2][0]=(d[i][0]+d[i+1][0])/2;
        mid[i/2][1]=(d[i][1]+d[i+1][1])/2;
        //ֱ�߷���ϵ��
        xs[i/2][0]=(d[i][0]-d[i+1][0])/(d[i][1]-d[i+1][1]);
        xs[i/2][1]=d[i][0]-xs[i/2][0]*d[i][1];
        //cout<<xs[i/2][0]<<"  "<<xs[i/2][1]<<endl;
    }
    /*for(int i = 0; i < ROW/2; ++i){
		for(int j = 0; j < VOL; ++j){
			cout<<mid[i][j]<<" ";
		}
		cout<<endl;
	}*/
	//���������ļ��
	for(int i=0;i<ROW/2-1;i=i+1)
    {

        L[i]=sqrt((mid[i][0]-mid[i+1][0])*(mid[i][0]-mid[i+1][0])+(mid[i][1]-mid[i+1][1])*(mid[i][1]-mid[i+1][1]));
        //cout<<L[i]<<endl;
    }
    double x_wuran,y_wuran;
    x_wuran=494000;y_wuran=3228500;
    //cin>>x_wuran>>y_wuran;
    for(int i=0;i<ROW/2;i=i+1)
    {
        bj[i]=y_wuran*xs[i][0]+xs[i][1]-x_wuran;
        //cout<<bj[i]<<endl;
    }
    for(int i=0;i<ROW/2-1;i++)
    {
        if(bj[i]*bj[i+1]<=0&&(sqrt((mid[i][0]-x_wuran)*(mid[i][0]-x_wuran)+(mid[i][1]-y_wuran)*(mid[i][1]-y_wuran)))<500)
        {
            wuran_sx[0]=i+1;
            k=(mid[i][0]-mid[i+1][0])/(mid[i][1]-mid[i+1][1]);
            b=(mid[i][0]-k*mid[i][1]);
            y_jd=(-k*b+k*x_wuran+y_wuran)/(1+k*k);
            x_jd=k*y_jd+b;
            wuran_sx[2]=sqrt((x_wuran-x_jd)*(x_wuran-x_jd)+(y_wuran-y_jd)*(y_wuran-y_jd));
            wuran_sx[3]=sqrt((mid[i][0]-x_jd)*(mid[i][0]-x_jd)+(mid[i][1]-y_jd)*(mid[i][1]-y_jd));
            wuran_sx[4]=L[i]-wuran_sx[3];
            if((k*y_wuran-x_wuran+b)>=0)
               wuran_sx[1]=1;
            else
               wuran_sx[1]=-1;
        }
    }
    //cout<<wuran_sx[0]<<" "<<wuran_sx[1]<<"  "<<wuran_sx[2]<<endl;
    for(int i=0;i<ROW/2;i++)
    {
        Length_dm[i]=sqrt((d[2*i][0]-d[2*i+1][0])*(d[2*i][0]-d[2*i+1][0])+(d[2*i][1]-d[2*i+1][1])*(d[2*i][1]-d[2*i+1][1]));
    }
    for(int i=0;i<ROW/2;i++)
    {
        for(int j=0;j<7;j++)
        {
            D[xiabiao+j][0]=((6-j)/6.0)*d[i][0]+(j/6.0)*d[i+1][0];
            D[xiabiao+j][1]=((6-j)/6.0)*d[i][1]+(j/6.0)*d[i+1][1];
            D[xiabiao+j][2]=abs(j-3)*Length_dm[i]/12;  //�����ڶ������ߵľ���
            D[xiabiao+j][3]=i;    //��¼���ڶ���
            if(j<=3)
                D[xiabiao+j][4]=1;
            else
                D[xiabiao+j][4]=-1;
        }
        xiabiao=xiabiao+7;
    }
    for(int i=1;i<ROW/2;i++)
    {
        s[i]=s[i-1]+L[i-1];
    }

    for(int i=0;i<ROW*7/2;i++)
    {
        if(D[i][3]<wuran_sx[0])  //����
        {
            dian[i][0]=abs(s[(int)(wuran_sx[0]-1)]-s[(int)(D[i][3])])+wuran_sx[3];
            if(D[i][4]*wuran_sx[1]>0)
            {
                dian[i][1]=abs(wuran_sx[2]-D[i][2]);
            }
            else
            {
                dian[i][1]=wuran_sx[2]+D[i][2];
            }
        }
        else
        {
            dian[i][0]=abs(s[(int)(wuran_sx[0]-1)]-s[(int)(D[i][3])])-wuran_sx[3];
            if(D[i][4]*wuran_sx[1]>0)
            {
                dian[i][1]=abs(wuran_sx[2]-D[i][2]);
            }
            else
            {
                dian[i][1]=wuran_sx[2]+D[i][2];
            }
        }
        //cout<<dian[i][0]<<"  "<<dian[i][1]<<endl;
    }
    for(int i=0;i<=wuran_sx[0]*7;i++)
    {
       for(int t=0;t<shichang;t=t+jiange)
        {
            C[i][t]=c0;                          //�иĶ�
        }
    }
    for(int i=wuran_sx[0]*7;i<ROW*7/2;i++)
    {
        for(int t=0;t<shichang;t=t+jiange)
        {
            C[i][t/jiange]=M*exp(-pow((dian[i][0]-u*(t+jiange)*60),2)/(4*Dx*(t+jiange)*60))*exp(-pow((dian[i][1]-v*(t+jiange)*60),2)/(4*Dy*(t+jiange)*60))*exp(-kc*(t+jiange)*60)/(4*Pi*h*(t+jiange)*60*sqrt(Dx*Dy))+c0;
        }
    }
    /*for(int i=0;i<ROW*7/2;i++)
    {
        cout << setprecision(10) << setiosflags(ios::fixed | ios::showpoint) <<C[i][0]<<endl;
    }*/
    time_t ss;
    struct tm *p;
    FILE *fp;
    char *fname="wuran.txt";
    ss=time((time_t*)NULL);
    p=gmtime(&ss);

    fp=fopen(fname,"w+");
    for(int t=0;t<shichang;t=t+jiange)
    {
        /*if((t+1)+p->tm_hour<=23)
        fprintf(fp,"%d-%d-%d %d:%d:%d\n",1900+p->tm_year,1+p->tm_mon, \
        p->tm_mday,(t+9)+p->tm_hour,p->tm_min,p->tm_sec);
        else
            fprintf(fp,"%d-%d-%d %d:%d:%d\n",1900+p->tm_year,1+p->tm_mon, \
        1+p->tm_mday,((t+9)+p->tm_hour)%24,p->tm_min,p->tm_sec);*/
        for(int i=0;i<ROW*7/2;i++)
        {
            fprintf(fp,"%f %f %f\n",D[i][0],D[i][1],C[i][t/jiange]);
            //fout<<D[i][0]<<" "<<D[i][1]<<" "<<C[i][t]<<endl;
        }
    }
    fclose(fp);
	return 0;
}
