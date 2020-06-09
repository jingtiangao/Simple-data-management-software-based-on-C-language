#include<stdio.h>
#include <string>
#include<stdlib.h> 
#include <iostream> 
#include <fstream>
#include<string.h>
using namespace std;

typedef struct{
	char stunum[17];
	char name[8];
	char sex[7];
	char classroom[7];

}stuinfor;
typedef struct{
char kcnum[4];
char kcname[22];
char    xuefen[5];
}kc;
typedef struct{
char stunum[17];
char kc[4];
char  score[8];    
}chengji;
typedef struct{
char stunum[17];
char kc[4];
float  score;
}chengjif;


class database
{
public:
	stuinfor si[10];//ѧ����Ϣ�ṹ������
	kc       kk[10];//�γ���Ϣ����
	chengji  cj[10];//�ɼ���Ϣ����
	chengjif  cjf[10];//�ɼ���Ϣת������
	int size;//����
	
	//��a,b,c����Ϣ����ṹ��������
		void load()
	{
		//����a��Ϣ
	    ifstream infile1("E:\\a.txt",ios::in);
		if(!infile1)
		{
        cout<<"open error!"<<endl;
        exit(1);
		}
		infile1.seekg(35,ios::beg);
		for(int i=0;i<size;i++)
		{
		infile1.get(si[i].stunum,17);
		infile1.get(si[i].name,8);
		infile1.get(si[i].sex,7);
		infile1.getline(si[i].classroom,7,'\n');
		}
		infile1.close();
		//����b��Ϣ
		ifstream infile2("E:\\b.txt",ios::in);
		if(!infile2)
		{
        cout<<"open error!"<<endl;
        exit(1);
		}
		infile2.seekg(31,ios::beg);
		for(int i=0;i<size;i++)
		{
			infile2.get(kk[i].kcnum,4);
			infile2.get(kk[i].kcname,22);//���ֳ������Ϊ6.5
			infile2.getline(kk[i].xuefen,5);
		
		}
		infile2.close();
		//����c��Ϣ
		ifstream infile3("E:\\c.txt",ios::in);
		if(!infile3)
		{
        cout<<"open error!"<<endl;
        exit(1);
		}
		infile3.seekg(28,ios::beg);
		for(int i=0;i<size;i++)
		{
			infile3.get(cj[i].stunum,17);
			infile3.get(cj[i].kc,4);
			infile3.getline(cj[i].score,8);
		
		}
		infile3.close();


	}
	//���ɼ����еķ���ת��Ϊ������
	void trans()
	{
		for(int i=0;i<size;i++)
		{
			strcpy(cjf[i].stunum,cj[i].stunum);
			strcpy(cjf[i].kc,cj[i].kc);
			if(cj[i].score[6]>'0')
			cjf[i].score=(cj[i].score[3]-'0')*10+(cj[i].score[4]-'0')+(cj[i].score[6]-'0')*0.1;
			else
			cjf[i].score=(cj[i].score[3]-'0')*10+(cj[i].score[4]-'0');
			
		}

	}
	//��ʾѧ����Ϣ
		void display(stuinfor a[] )
	{
		for(int i=0;i<size;i++)
		{
		cout<<a[i].stunum<<a[i].name<<a[i].sex<<a[i].classroom<<endl;				
		}
	}
	//��ʾ�γ̵���Ϣ
		void display(kc a[])
		{
			for(int i=0;i<size;i++)
			{
			cout<<a[i].kcnum<<a[i].kcname<<a[i].xuefen<<endl;				
			}
		}
	//��ʾ�ɼ��ļ�����Ϣ�����γ̺����Ϊ�γ�����
		void display(chengji a[],database& d)
				{
					
					for(int i=0;i<size;i++)
					{
					int t=0;
					cout<<a[i].stunum;
					while(strcmp(a[i].kc,d.kk[t].kcnum)!=0)
					{
						t++;
					}
					cout<<d.kk[t].kcname;
					cout<<a[i].score<<endl;
					}
				}
	//������ݵ�a�ļ���ѧ���ظ�����������
		void inserta()
	 {
		 
		 char ch1[17]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
		 char ch11[5]={' ',' ',' ',' ','\0'};
		 ofstream outfile("E:\\a.txt",ios::out|ios::app);
		 cout<<"������ѧ��(12λ)"<<endl;
		 
		again: cin>>ch1;
		 strcat(ch1,ch11);
				 for(int i=0;i<size;i++)//�Ƚ�ѧ���Ƿ��ظ�
				 {
					 if(strcmp(si[i].stunum,ch1)==0)
					 {
						 cout<<"ѧ�������ظ�������������ѧ��(12λ)"<<endl;
						 goto again;
					 }
				 }
		
		 outfile.write(ch1,16);
		 char ch2[8];
		 char ch22[4]={' ',' ',' ','\0'};
		 char ch222[2]={' ','\0'};
		 cout<<"����������"<<endl;
		 cin>>ch2;
		 if(strlen(ch2)==4)
		 strcat(ch2,ch22);
		 else
		 strcat(ch2,ch222);
		 outfile.write(ch2,7);
		 char ch3[7]={' ',' ',' ',' ',' ',' ','\0'};
		 char ch33[5]={' ',' ',' ',' ','\0'};
		 cout<<"�������Ա�"<<endl;
		 cin>>ch3;
		 strcat(ch3,ch33);
		 outfile.write(ch3,6);
		 char ch4[7]={' ',' ',' ',' ',' ',' ','\0'};
		 cout<<"������༶"<<endl;
		 cin>>ch4;
		 outfile.write(ch4,6);
		 outfile.put('\n');
		 outfile.close();				
	 }
	 //����һ��ѧ��ʱ����ѯ�����������пγ����,�ɼ�������ʱʵ��ѧ��Ϊ0
		 void select(database& d)
			 {
				 char ch1[17]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
				 char ch2[5]={' ',' ',' ',' ','\0'};
				 cout<<"������ѧ��(12λ)"<<endl;
				 cin>>ch1;
				 strcat(ch1,ch2);
		 			int t=0;
					int count=0;
					int sum=0;
					cout<<"ѧ�ţ�"<<ch1;
									 while((strcmp(ch1,d.si[t].stunum)!=0)&&(t<d.size))
										{
											t++;
											
										}
									 if(t<d.size){ cout<<"������"<<d.si[t].name<<endl;}
									 else{cout<<"�޴�������"<<endl;}
					 for(int i=0;i<d.size;i++)
					 {
						 if(strcmp(d.cj[i].stunum,ch1)==0)
						 {		
								count++;
								 t=0;
								 cout<<"�γ̺ţ�"<<d.cj[i].kc;
								while(strcmp(d.cj[i].kc,d.kk[t].kcnum)!=0&&t<d.size)
								{
									t++;
								}
								if(t<d.size)
								{
										cout<<"�γ�����"<<d.kk[t].kcname;
										cout<<"�ɼ���"<<d.cj[i].score;
									
										if(d.cj[i].score[3]<'6')
											cout<<"		ʵ��ѧ�֣�������"<<endl;
										else
											{
												cout<<"		ʵ��ѧ�֣�"<<d.kk[t].xuefen<<endl;
												sum=sum+d.kk[t].xuefen[1]-'0';
											}	
								}
								else
								{
									cout<<"�޴˿γ�";
								}
				
						

						 }

					 }
					 cout<<"���ޣ�"<<count<<"�ƣ�ʵ���ܵ�ѧ�֣�"<<sum<<endl;
					 
	

			 }
	//����ɾ���������ܣ�����A.TXT��B.TXT��ɾ��ѧ����γ���Ϣʱ���ܷ�����ɾ��C.TXT�����Ϣ
		 void dela()
		 {
			 
			 int t=0;
			 int q=0;
			 char ch1[17]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
			 char ch3[]="ѧ��            ����   �Ա�  �༶";
			 char ch4[]="ѧ��            �γ�  �ɼ�";
			 char ch2[5]={' ',' ',' ',' ','\0'};
			 cout<<"��������Ҫɾ����ѧ��"<<endl;
			 cin>>ch1;
			 strcat(ch1,ch2);
			 while((strcmp(ch1,si[t].stunum)!=0)&&(t<size))
				{
				t++;
											
				}
				 if(t<size)
				 {
					// outfile.seekp((34+t*36+1),ios::beg);
					 ofstream outfile("E:\\a.txt",ios::out);
					 outfile.write(ch3,33);
					 outfile.put('\n');
					 for(int i=0;i<size&&(si[i].stunum[0]>='0');i++)
					 {
									
									 if(i!=t)
									 {
										 outfile.write(si[i].stunum,16);					 
										 outfile.write(si[i].name,7);
										 outfile.write(si[i].sex,6);
										 outfile.write(si[i].classroom,6);
										 outfile.put('\n');
									 }
					 }
					 outfile.close();
					 //����a��Ϣ
					ifstream infile1("E:\\a.txt",ios::in);
					if(!infile1)
					{
					cout<<"open error!"<<endl;
					exit(1);
					}
					infile1.seekg(35,ios::beg);
					for(int i=0;i<size;i++)
					{
					infile1.get(si[i].stunum,17);
					infile1.get(si[i].name,8);
					infile1.get(si[i].sex,7);
					infile1.getline(si[i].classroom,7,'\n');
					}
					infile1.close();
										
				 }
				 else
				 cout<<"��ѧ�Ų�����"<<endl;
				 //ofstream outfile("E:\\a.txt",ios_base::ate);
				 //outfile.close();
												//���ļ�C���з�����ɾ��
												  while(q<size)
												  {
													  q=0;
													   while((strcmp(ch1,cj[q].stunum)!=0)&&(q<size))//������˵ļ�¼
														{
														q++;
											
														}
													   //��C�ļ���ɾ��
													   if(q<size)
													   {
															   ofstream outfile("E:\\c.txt",ios::out);
															   outfile.write(ch4,26);
															   outfile.put('\n');
																for(int i=0;i<size&&(cj[i].stunum[0]>='0');i++)
																 {
									
																				 if(i!=q)
																				 {
																					 outfile.write(cj[i].stunum,16);					 
																					 outfile.write(cj[i].kc,3);
																					 outfile.write(cj[i].score,7);
																					 outfile.put('\n');
																				 }
																 }
																 outfile.close();
																 //����c��Ϣ
																ifstream infile3("E:\\c.txt",ios::in);
																if(!infile3)
																{
																cout<<"open error!"<<endl;
																exit(1);
																}
																infile3.seekg(28,ios::beg);
																for(int i=0;i<size;i++)
																{
																	infile3.get(cj[i].stunum,17);
																	infile3.get(cj[i].kc,4);
																	infile3.getline(cj[i].score,8);
		
																}
																infile3.close();
													   }


												  }
		 }
		 void delb()
		 {
			  int t=0;
			  int q=0;
			  char ch1[4];
			  char ch3[]="�γ̱�� �γ�����        ѧ��";
			  char ch4[]="ѧ��            �γ�  �ɼ�";
			  cout<<"��������Ҫɾ���Ŀγ̺�(����C01)"<<endl;
			  cin>>ch1;
			  //��B�в���˼�¼��ɾ��
			  while((strcmp(ch1,kk[t].kcnum)!=0)&&(t<size))
				{
				t++;
											
				}
				 if(t<size)
				 {
					// outfile.seekp((34+t*36+1),ios::beg);
					 ofstream outfile("E:\\b.txt",ios::out);
					 outfile.write(ch3,29);
					 outfile.put('\n');
					 for(int i=0;i<size&&(kk[i].kcnum[0]>='A');i++)
					 {
									
									 if(i!=t)
									 {
										 outfile.write(kk[i].kcnum,3);					 
										 outfile.write(kk[i].kcname,21);
										 outfile.write(kk[i].xuefen,2);
										 outfile.put('\n');
									 }
					 }
					 outfile.close();
					 //����b��Ϣ
						ifstream infile2("E:\\b.txt",ios::in);
						if(!infile2)
						{
						cout<<"open error!"<<endl;
						exit(1);
						}
						infile2.seekg(31,ios::beg);
						for(int i=0;i<size;i++)
						{
							infile2.get(kk[i].kcnum,4);
							infile2.get(kk[i].kcname,22);//���ֳ������Ϊ6.5
							infile2.getline(kk[i].xuefen,5);
		
						}
						infile2.close();
				 }
				 else
				 cout<<"�˿γ̺Ų�����"<<endl;
												//���ļ�C���з�����ɾ��
												  while(q<size)
												  {
													  q=0;
													  while((strcmp(ch1,cj[q].kc)!=0)&&(q<size))//����˿γ̵ļ�¼
														{
														q++;
											
														}
													   //��C�ļ���ɾ��
													   if(q<size)
													   {
															   ofstream outfile("E:\\c.txt",ios::out);
															   outfile.write(ch4,26);
															   outfile.put('\n');
															   for(int i=0;i<size&&(cj[i].stunum[0]>='0');i++)
																 {
									
																				 if(i!=q)
																				 {
																					 outfile.write(cj[i].stunum,16);					 
																					 outfile.write(cj[i].kc,3);
																					 outfile.write(cj[i].score,7);
																					 outfile.put('\n');
																				 }
																 }
																 outfile.close();
																 //����c��Ϣ
																ifstream infile3("E:\\c.txt",ios::in);
																if(!infile3)
																{
																cout<<"open error!"<<endl;
																exit(1);
																}
																infile3.seekg(28,ios::beg);
																for(int i=0;i<size;i++)
																{
																	infile3.get(cj[i].stunum,17);
																	infile3.get(cj[i].kc,4);
																	infile3.getline(cj[i].score,8);
		
																}
																infile3.close();
													   }


												  }






		 }
	//	�����ܣ���ָ���Ŀ�Ŀ���ܹ����ճɼ����������������ʾ����
		 //���򿴳ɼ�
		 void sortrise()
		 {
							chengjif tem;//�м����
							float sum=0;
							int count=0;
							int t=0;
							int q=0;
							cout<<"��������Ҫ����鿴�Ŀγ̺�";
							char ch1[4];
							cin>>ch1;

							 for(int i=0;i<size-1;i++)//�Ӵ�С����
							 {
								 for(int j=0;j<size-1-i;j++)
								 {
									 if(cjf[j].score<cjf[j+1].score)
									 {
										strcpy(tem.stunum,cjf[j].stunum);
										strcpy(tem.kc,cjf[j].kc);
										tem.score=cjf[j].score;
										strcpy(cjf[j].stunum,cjf[j+1].stunum);
										strcpy(cjf[j].kc,cjf[j+1].kc);
										cjf[j].score=cjf[j+1].score;
										strcpy(cjf[j+1].stunum,tem.stunum);
										strcpy(cjf[j+1].kc,tem.kc);
										cjf[j+1].score=tem.score;
						 

									 }
								 }
							 }
							 while(t<size)
							 {
											 while((strcmp(ch1,cjf[t].kc)!=0)&&(t<size))//��ɼ����пγ̺�ΪCH1�ļ�¼
												{
												t++;
											
												}
											 if(t<size)//������ǲ����ˣ����������,�鵽��
											 {
												cout<<"ѧ�ţ�"<<cjf[t].stunum;
												while(strcmp(cjf[t].kc,kk[q].kcnum)!=0&&q<size)
												{
													q++;
												}
												if(q<size)
												{
												cout<<"�γ���"<<kk[q].kcname;
												cout<<"�γ̺�"<<cjf[t].kc;
												cout<<"�ɼ���"<<cjf[t].score<<endl;
												count++;
												sum=sum+cjf[t].score;
												}
												else
												{
												cout<<"  �޴˿γ� ";
												cout<<"�γ̺�"<<cjf[t].kc;
												cout<<"�ɼ���"<<cjf[t].score<<endl;
												count++;
												sum=sum+cjf[t].score;
												}
											 }
										t++;
											
			 
							 
							 }
							 if(count>0)
							 {
							 cout<<"ƽ���ɼ���"<<(sum/count)<<endl;
							 }
							 else
							 {
								cout<<"��û�д˿γ̵ĳɼ�"<<endl;
							 }
		 }
		 //���򿴳ɼ�
		 void sortdown()
		 {
							chengjif tem;//�м����
							float sum=0;
							int count=0;
							int t=0;
							int q=0;
							cout<<"��������Ҫ����鿴�Ŀγ̺�";
							char ch1[4];
							cin>>ch1;

							 for(int i=0;i<size-1;i++)//��С��������
							 {
								 for(int j=0;j<size-1-i;j++)
								 {
									 if(cjf[j].score>cjf[j+1].score)
									 {
										strcpy(tem.stunum,cjf[j].stunum);
										strcpy(tem.kc,cjf[j].kc);
										tem.score=cjf[j].score;
										strcpy(cjf[j].stunum,cjf[j+1].stunum);
										strcpy(cjf[j].kc,cjf[j+1].kc);
										cjf[j].score=cjf[j+1].score;
										strcpy(cjf[j+1].stunum,tem.stunum);
										strcpy(cjf[j+1].kc,tem.kc);
										cjf[j+1].score=tem.score;
						 

									 }
								 }
							 }
							 while(t<size)
							 {
											 while((strcmp(ch1,cjf[t].kc)!=0)&&(t<size))//��ɼ����пγ̺�ΪCH1�ļ�¼
												{
												t++;
											
												}
											 if(t<size)//������ǲ����ˣ����������
											 {
												cout<<"ѧ�ţ�"<<cjf[t].stunum;
												while(strcmp(cjf[t].kc,kk[q].kcnum)!=0&&q<size)
												{
													q++;
												}
												if(q<size)
												{
												cout<<"�γ���"<<kk[q].kcname;
												cout<<"�γ̺�"<<cjf[t].kc;
												cout<<"�ɼ���"<<cjf[t].score<<endl;
												count++;
												sum=sum+cjf[t].score;
												}
												else
												{
												cout<<"  �޴˿γ� ";
												cout<<"�γ̺�"<<cjf[t].kc;
												cout<<"�ɼ���"<<cjf[t].score<<endl;
												count++;
												sum=sum+cjf[t].score;
												}
											 }
										t++;
											
			 
							 
							 }
							  if(count>0)
							 {
							 cout<<"ƽ���ɼ���"<<(sum/count)<<endl;
							 }
							 else
							 {
								cout<<"��û�д˿γ̵ĳɼ�"<<endl;
							 }
		 }
		//�����ļ��е��������͵Ĵ���
		 void check()
		 {
			 for(int i=0;i<size&&si[i].classroom[5]>='0';i++)
			 {
				 for(int j=0;j<12;j++)
				 {
					 if(si[i].stunum[j]<'0'||si[i].stunum[j]>'9')
					 {
						 cout<<"ѧ����Ϣ�ļ���"<<si[i].stunum<<"ѧ����Ϣ�������Ͳ���"<<endl;
					 }
				 }
			 }

		 }

private:
	
};


int main()
{	
	database d1;
	
	d1.size=10;
	d1.load();
	
	while(1)
	{
		d1.load();
		cout<<endl;
		cout<<"****************************"<<endl;
		cout<<"��ӭ�����ɼ�����ϵͳ"<<endl;
		cout<<"1 ��ʾѧ����Ϣ"<<endl;
		cout<<"2 ��ʾ�γ̵���Ϣ"<<endl;
		cout<<"3 ��ʾ���п�Ŀ�ɼ�����Ϣ"<<endl;
		cout<<"4 ������ʾĳ��Ŀ�ɼ�����Ϣ"<<endl;
		cout<<"5 ������ʾ�ɼ�����Ϣ"<<endl;
		cout<<"6 ���ѧ����Ϣ"<<endl;
		cout<<"7 ��ѯѧ���Ŀγ���ɼ�"<<endl;
		cout<<"8 ɾ��ѧ����Ϣ"<<endl;
		cout<<"9 ɾ���γ���Ϣ"<<endl;
		cout<<"10 �����ļ��е��������͵Ĵ���"<<endl;
		cout<<"****************************"<<endl;
		cout<<endl;
		int c;
		cin>>c;
		if(c==1)
		{
			d1.display(d1.si);
		}
		else if(c==2)
		{
			d1.display(d1.kk);
		}
		else if(c==3)
		{
			d1.display(d1.cj,d1);
		}
		else if(c==4)
		{
			d1.trans();
			d1.sortdown();
			

		}
		else if(c==5)
		{
			d1.trans();
			d1.sortrise();
			

		}
		else if(c==6)
		{
			d1.inserta();
	
		}
		else if(c==7)
		{
			d1.select(d1);
		}
		else if(c==8)
		{
			d1.display(d1.si);
			d1.display(d1.cj,d1);
			d1.dela();

		}
		else if(c==9)
		{
			d1.display(d1.kk);
			d1.display(d1.cj,d1);
			d1.delb();

		}
		else if(c==10)
		{
			d1.check();
		}
		else
			cout<<"����������"<<endl;
	}
	//d1.trans();

	//d1.display(d1.si);
	//d1.display(d1.kk);
	//d1.display(d1.cj,d1);
	//d1.check();
	//d1.select(d1);
	//d1.inserta();
	//d1.inserta();
	//d1.delb();
	//d1.load();
	//d1.display(d1.si);
	//d1.sortrise();
	//d1.sortdown();
	//d1.display(d1.kk);
	//d1.display(d1.cj,d1);
	int q;
	cin>>q;

}