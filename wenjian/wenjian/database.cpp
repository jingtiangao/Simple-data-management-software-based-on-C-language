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
	stuinfor si[10];//学生信息结构体数组
	kc       kk[10];//课程信息数组
	chengji  cj[10];//成绩信息数组
	chengjif  cjf[10];//成绩信息转换数组
	int size;//容量
	
	//将a,b,c中信息读入结构体数组中
		void load()
	{
		//读入a信息
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
		//读入b信息
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
			infile2.get(kk[i].kcname,22);//名字长度最大为6.5
			infile2.getline(kk[i].xuefen,5);
		
		}
		infile2.close();
		//读入c信息
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
	//将成绩表中的分数转换为浮点数
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
	//显示学生信息
		void display(stuinfor a[] )
	{
		for(int i=0;i<size;i++)
		{
		cout<<a[i].stunum<<a[i].name<<a[i].sex<<a[i].classroom<<endl;				
		}
	}
	//显示课程的信息
		void display(kc a[])
		{
			for(int i=0;i<size;i++)
			{
			cout<<a[i].kcnum<<a[i].kcname<<a[i].xuefen<<endl;				
			}
		}
	//显示成绩文件的信息，将课程号输出为课程名称
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
	//输出数据到a文件，学号重复将重新输入
		void inserta()
	 {
		 
		 char ch1[17]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
		 char ch11[5]={' ',' ',' ',' ','\0'};
		 ofstream outfile("E:\\a.txt",ios::out|ios::app);
		 cout<<"请输入学号(12位)"<<endl;
		 
		again: cin>>ch1;
		 strcat(ch1,ch11);
				 for(int i=0;i<size;i++)//比较学号是否重复
				 {
					 if(strcmp(si[i].stunum,ch1)==0)
					 {
						 cout<<"学号输入重复，请重新输入学号(12位)"<<endl;
						 goto again;
					 }
				 }
		
		 outfile.write(ch1,16);
		 char ch2[8];
		 char ch22[4]={' ',' ',' ','\0'};
		 char ch222[2]={' ','\0'};
		 cout<<"请输入姓名"<<endl;
		 cin>>ch2;
		 if(strlen(ch2)==4)
		 strcat(ch2,ch22);
		 else
		 strcat(ch2,ch222);
		 outfile.write(ch2,7);
		 char ch3[7]={' ',' ',' ',' ',' ',' ','\0'};
		 char ch33[5]={' ',' ',' ',' ','\0'};
		 cout<<"请输入性别"<<endl;
		 cin>>ch3;
		 strcat(ch3,ch33);
		 outfile.write(ch3,6);
		 char ch4[7]={' ',' ',' ',' ',' ',' ','\0'};
		 cout<<"请输入班级"<<endl;
		 cin>>ch4;
		 outfile.write(ch4,6);
		 outfile.put('\n');
		 outfile.close();				
	 }
	 //输入一个学号时，查询出此生的所有课程情况,成绩不及格时实得学分为0
		 void select(database& d)
			 {
				 char ch1[17]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
				 char ch2[5]={' ',' ',' ',' ','\0'};
				 cout<<"请输入学号(12位)"<<endl;
				 cin>>ch1;
				 strcat(ch1,ch2);
		 			int t=0;
					int count=0;
					int sum=0;
					cout<<"学号："<<ch1;
									 while((strcmp(ch1,d.si[t].stunum)!=0)&&(t<d.size))
										{
											t++;
											
										}
									 if(t<d.size){ cout<<"姓名："<<d.si[t].name<<endl;}
									 else{cout<<"无此人姓名"<<endl;}
					 for(int i=0;i<d.size;i++)
					 {
						 if(strcmp(d.cj[i].stunum,ch1)==0)
						 {		
								count++;
								 t=0;
								 cout<<"课程号："<<d.cj[i].kc;
								while(strcmp(d.cj[i].kc,d.kk[t].kcnum)!=0&&t<d.size)
								{
									t++;
								}
								if(t<d.size)
								{
										cout<<"课程名："<<d.kk[t].kcname;
										cout<<"成绩："<<d.cj[i].score;
									
										if(d.cj[i].score[3]<'6')
											cout<<"		实得学分：不及格"<<endl;
										else
											{
												cout<<"		实得学分："<<d.kk[t].xuefen<<endl;
												sum=sum+d.kk[t].xuefen[1]-'0';
											}	
								}
								else
								{
									cout<<"无此课程";
								}
				
						

						 }

					 }
					 cout<<"共修："<<count<<"科，实际总得学分："<<sum<<endl;
					 
	

			 }
	//数据删除、整理功能：当在A.TXT、B.TXT中删除学生或课程信息时，能分析并删除C.TXT相关信息
		 void dela()
		 {
			 
			 int t=0;
			 int q=0;
			 char ch1[17]={' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','\0'};
			 char ch3[]="学号            姓名   性别  班级";
			 char ch4[]="学号            课程  成绩";
			 char ch2[5]={' ',' ',' ',' ','\0'};
			 cout<<"请输入您要删除的学号"<<endl;
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
					 //读入a信息
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
				 cout<<"此学号不存在"<<endl;
				 //ofstream outfile("E:\\a.txt",ios_base::ate);
				 //outfile.close();
												//对文件C进行分析并删除
												  while(q<size)
												  {
													  q=0;
													   while((strcmp(ch1,cj[q].stunum)!=0)&&(q<size))//查出此人的记录
														{
														q++;
											
														}
													   //从C文件中删除
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
																 //读入c信息
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
			  char ch3[]="课程编号 课程名称        学分";
			  char ch4[]="学号            课程  成绩";
			  cout<<"请输入您要删除的课程号(例：C01)"<<endl;
			  cin>>ch1;
			  //从B中查出此记录并删除
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
					 //读入b信息
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
							infile2.get(kk[i].kcname,22);//名字长度最大为6.5
							infile2.getline(kk[i].xuefen,5);
		
						}
						infile2.close();
				 }
				 else
				 cout<<"此课程号不存在"<<endl;
												//对文件C进行分析并删除
												  while(q<size)
												  {
													  q=0;
													  while((strcmp(ch1,cj[q].kc)!=0)&&(q<size))//查出此课程的记录
														{
														q++;
											
														}
													   //从C文件中删除
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
																 //读入c信息
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
	//	排序功能：对指定的科目，能够按照成绩降序或升序排序显示数据
		 //降序看成绩
		 void sortrise()
		 {
							chengjif tem;//中间变量
							float sum=0;
							int count=0;
							int t=0;
							int q=0;
							cout<<"输入您想要降序查看的课程号";
							char ch1[4];
							cin>>ch1;

							 for(int i=0;i<size-1;i++)//从大到小排序
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
											 while((strcmp(ch1,cjf[t].kc)!=0)&&(t<size))//查成绩表中课程号为CH1的记录
												{
												t++;
											
												}
											 if(t<size)//如果不是查完了，就输出数据,查到了
											 {
												cout<<"学号："<<cjf[t].stunum;
												while(strcmp(cjf[t].kc,kk[q].kcnum)!=0&&q<size)
												{
													q++;
												}
												if(q<size)
												{
												cout<<"课程名"<<kk[q].kcname;
												cout<<"课程号"<<cjf[t].kc;
												cout<<"成绩："<<cjf[t].score<<endl;
												count++;
												sum=sum+cjf[t].score;
												}
												else
												{
												cout<<"  无此课程 ";
												cout<<"课程号"<<cjf[t].kc;
												cout<<"成绩："<<cjf[t].score<<endl;
												count++;
												sum=sum+cjf[t].score;
												}
											 }
										t++;
											
			 
							 
							 }
							 if(count>0)
							 {
							 cout<<"平均成绩："<<(sum/count)<<endl;
							 }
							 else
							 {
								cout<<"还没有此课程的成绩"<<endl;
							 }
		 }
		 //升序看成绩
		 void sortdown()
		 {
							chengjif tem;//中间变量
							float sum=0;
							int count=0;
							int t=0;
							int q=0;
							cout<<"输入您想要升序查看的课程号";
							char ch1[4];
							cin>>ch1;

							 for(int i=0;i<size-1;i++)//从小到大排序
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
											 while((strcmp(ch1,cjf[t].kc)!=0)&&(t<size))//查成绩表中课程号为CH1的记录
												{
												t++;
											
												}
											 if(t<size)//如果不是查完了，就输出数据
											 {
												cout<<"学号："<<cjf[t].stunum;
												while(strcmp(cjf[t].kc,kk[q].kcnum)!=0&&q<size)
												{
													q++;
												}
												if(q<size)
												{
												cout<<"课程名"<<kk[q].kcname;
												cout<<"课程号"<<cjf[t].kc;
												cout<<"成绩："<<cjf[t].score<<endl;
												count++;
												sum=sum+cjf[t].score;
												}
												else
												{
												cout<<"  无此课程 ";
												cout<<"课程号"<<cjf[t].kc;
												cout<<"成绩："<<cjf[t].score<<endl;
												count++;
												sum=sum+cjf[t].score;
												}
											 }
										t++;
											
			 
							 
							 }
							  if(count>0)
							 {
							 cout<<"平均成绩："<<(sum/count)<<endl;
							 }
							 else
							 {
								cout<<"还没有此课程的成绩"<<endl;
							 }
		 }
		//查找文件中的数据类型的错误
		 void check()
		 {
			 for(int i=0;i<size&&si[i].classroom[5]>='0';i++)
			 {
				 for(int j=0;j<12;j++)
				 {
					 if(si[i].stunum[j]<'0'||si[i].stunum[j]>'9')
					 {
						 cout<<"学生信息文件中"<<si[i].stunum<<"学号信息数据类型不对"<<endl;
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
		cout<<"欢迎来到成绩管理系统"<<endl;
		cout<<"1 显示学生信息"<<endl;
		cout<<"2 显示课程的信息"<<endl;
		cout<<"3 显示所有科目成绩的信息"<<endl;
		cout<<"4 升序显示某科目成绩的信息"<<endl;
		cout<<"5 降序显示成绩的信息"<<endl;
		cout<<"6 添加学生信息"<<endl;
		cout<<"7 查询学生的课程与成绩"<<endl;
		cout<<"8 删除学生信息"<<endl;
		cout<<"9 删除课程信息"<<endl;
		cout<<"10 查找文件中的数据类型的错误"<<endl;
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
			cout<<"请重新输入"<<endl;
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