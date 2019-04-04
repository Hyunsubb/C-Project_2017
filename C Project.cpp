#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<stdbool.h>

typedef struct 
{
	FILE *fp;
	bool chk;
	char *File_name;
	char **Save_tmp;
	int str_chk;
	int count;
}File;

typedef struct
{
	char Nick_name[40];
	char Champ[40];
	int Kill;
	int Death;
	int Assist;
	int Cs;
	double Avg;
}Game;

typedef struct
{
	char Nick_name[40];
	char Kart[40];
	char Lap_time[40];
	char Time[40];
	char Date[40];
	char Map[40];
}game;

void gotoxy(int,int);
void clear_buff();
void select();
void Beeep();
void cursor();
void printing();
void p_printing(int,int);
void game_select();
int game_select_print();
int game_chk(char **);
void _Search_select();
void main_select();
void np_select();

void File_Create(char ***,int **);
void Data_save(char **,int *);
int File_check(char **);
int Game_check();
void notice();
int File_Count_sub();
void Search_for_champ();
void Search_name();
void Search_filename();
void File_print_sub();
void File_print();
void File_del();
void Modify_file();
void Read_file();
void Log_print();
char **Save_get();
int File_Count();
void Title_set(int);

void Note_title();
void Note_save(char **);
void Note_create(char **);
void Note_list();
void Note_view();
void Note_del();
char **Note_save_get();
int Note_count();
int Note_count_sub();

int clean=0;
//char *_directory;

void clear_buff()
{
	while(getchar()!='\n');
}

void start()
{
	printing();
	int xy=5;
	int yx=9;
	int txy=5;
	int tyx=47;
	int print=0;
	
	for(int i=0;i<5;i++)
	{
		if(print%2==0){
			gotoxy(yx,xy);
			printf("멍!");
			Sleep(50);
			gotoxy(tyx,txy);
			printf("멍!");
		}
		else{
			
			gotoxy(tyx,txy);
			printf("멍!");
			Sleep(50);
			gotoxy(yx,xy);
			printf("멍!");
		}
	
		Sleep(280);
		xy+=4;
		yx+=9;
		txy+=4;
		tyx=tyx-9; 
		print++;
	}
	Sleep(200);
	system("cls");
	main_select();
}

int main()
{
	system("title [Game Record]");
	system("mode con: cols=100 lines=40");
//	_directory = argv[0];
	cursor();
	start();
	return 0;	
}

void main_select()
{
	int select_num;
	printing();
	while(1)
	{
		system("cls");
		printing();
		gotoxy(10,6);
		fprintf(stdout,"1. Notepad");
		gotoxy(10,9);
		fprintf(stdout,"2. Game Log");
		gotoxy(10,12);
		fprintf(stdout,"3. Exit program");
		
		if(_kbhit)
		{
			Beeep();
			select_num=_getch();
			switch(select_num)
			{
				case 49:
					np_select();
					break;
				case 50:
					select();
					break;
				case 51:
					gotoxy(0,28);
					exit(0);				
				default:
					break;
			}
		}
	}
}

void np_select()
{
	int select_num;
	printing();
	while(1)
	{
		system("cls");
		printing();
		gotoxy(10,6);
		fprintf(stdout,"1. 메모 추가");
		gotoxy(10,9);
		fprintf(stdout,"2. 메모 삭제");
		gotoxy(10,12);
		fprintf(stdout,"3. 메모 보기");
		gotoxy(13,21);
		printf("Previous Step - Press the backspace");
		
		if(_kbhit)
		{
			Beeep();
			select_num=_getch();
			switch(select_num)
			{
				case 49:
					Note_title();
					break;
				case 50:
					Note_del();
					break;
				case 51:
					Note_view();
					break;
				case 8:
					system("cls");
					main_select(); 
					break;
				default:
					break;
			}
		} 
	}
}

void Note_title()
{
	system("cls");
	printing();
	
	File _file;

	_file.File_name=NULL;
	_file.File_name=(char *)calloc(50,sizeof(char));
	
	gotoxy(10,9);
	fprintf(stdout,"메모 이름을 입력해주세요 : (enter 두 번)");
	gotoxy(12,21);
	fprintf(stdout,"뒤로 가시려면 'back' 을 입력해주세요.");
	
	gotoxy(10,11);
	fgets(_file.File_name,50,stdin);
	_file.File_name[strlen(_file.File_name)-1]=NULL;
	
	while(getchar()!='\n');
	
	if(strcmp("back",_file.File_name)==0)
	{
		gotoxy(10,13);
		fprintf(stdout,"전 단계로 돌아갑니다.");
		Sleep(500);
		system("cls");
		np_select();
	}

	Note_save(&_file.File_name);
}

void Note_save(char **File_name)
{
	FILE *fp=NULL;
	char *tmp_fname=NULL;
	int n_len;	
	bool lap_chk;	
	
	strcat(*File_name,".txt");
	
	n_len = strlen(*File_name);
	tmp_fname = (char *)calloc(n_len,sizeof(char));
	
	strcpy(tmp_fname,*File_name);

//	lap_chk=File_check(&tmp_fname);
	
	if(lap_chk==true)
	{
		printf("같은 이름의 파일이 존재합니다.\n");
		printf("아무키나 눌러주세요.");
		if(_kbhit())
		{
			main();
			Beeep();
		}
	}
	
	fp=fopen("Save_n.txt","a+");

	fprintf(fp,"%s\n",*File_name);
	fclose(fp);
	
	Note_create(&tmp_fname);
}

void Note_create(char **File_name)
{
	char **note_tmp;
	char pass[20];
	char tmptmp[10]="pass_";
	char compare_tmp[30][50];
	int xy=9;
	bool chk;
	int sel;
	int note_line=0;
	File file;
	
	note_tmp=(char **)calloc(30,sizeof(char *));
	for(int i=0;i<30;i++)
		note_tmp[i]=(char *)calloc(50,sizeof(char));
		
	system("cls");
	p_printing(10,50);
	gotoxy(9,4);
	printf("내용을 입력해주세요");
	gotoxy(9,6);
	printf("그만 입력하시려면 'stop'을 입력해주세요. ");
	gotoxy(9,7);
	printf("(enter 두 번)");
	gotoxy(9,9);
	for(int i=0;i<30;i++)
	{
		gotoxy(8,xy);
		fgets(note_tmp[i],50,stdin);
	//	fscanf(stdin,"%s",note_tmp[i]);
		note_tmp[i][strlen(note_tmp[i])-1]=NULL;
		note_line+=1;
		if(strcmp("stop",note_tmp[i])==0)
		{
			chk=true;
			clear_buff();
			break;
		} 
		xy+=2;
	}
	if(chk==true)
	{
		gotoxy(9,xy+3);
		printf("암호를 설정하시겠습니까? (Y/N)");
		
		while(1)
		{
			if(_kbhit)
			{
				sel=_getch();
				switch(sel)
				{
					case 121:
						system("cls");
						printing();
						gotoxy(10,6);
						printf("설정할 암호를 입력해주세요.");
						gotoxy(10,10);
					//	fscanf(stdin,"%[^\n]",pass);
						fgets(pass,sizeof(pass),stdin);
						pass[strlen(pass)-1]=NULL;
						file.fp=fopen(*File_name,"w");
						for(int i=0;i<note_line;i++)
						{
							fprintf(file.fp,"%s\n",note_tmp[i]);
						}
						fprintf(file.fp,"%s\n",tmptmp);
						fprintf(file.fp,"%s\n",pass);
						fclose(file.fp);
						for(int i=0;i<30;i++)
							free(note_tmp[i]);
						free(note_tmp);
						gotoxy(10,13);
						printf("메모를 저장합니다.");
						Sleep(800);
						np_select();
						break; 
						
					case 110:
						file.fp=fopen(*File_name,"w");
						for(int i=0;i<note_line;i++)
						{
							fprintf(file.fp,"%s\n",note_tmp[i]);
						}
						fclose(file.fp);
						for(int i=0;i<30;i++)
							free(note_tmp[i]);
						free(note_tmp);
						fclose(file.fp);
						gotoxy(9,xy+5);
						printf("입력을 종료합니다.");
						Sleep(800);
						np_select();
						break; 
					case 89:
						system("cls");
						printing();
						gotoxy(10,6);
						printf("설정할 암호를 입력해주세요.");
						gotoxy(10,10);
						fscanf(stdin,"%[^\n]",pass);
						file.fp=fopen(*File_name,"w");
						for(int i=0;i<note_line;i++)
						{
							fprintf(file.fp,"%s\n",note_tmp[i]);
						}
						fprintf(file.fp,"%s\n",tmptmp);
						fprintf(file.fp,"%s\n",pass);
						fclose(file.fp);
						for(int i=0;i<30;i++)
							free(note_tmp[i]);
						free(note_tmp);
						gotoxy(10,13);
						printf("메모를 저장합니다.");
						Sleep(800);
						np_select();
						break; 
					case 78:
						file.fp=fopen(*File_name,"w");
						for(int i=0;i<note_line;i++)
						{
							fprintf(file.fp,"%s\n",note_tmp[i]);
						}
						fclose(file.fp);
						for(int i=0;i<30;i++)
							free(note_tmp[i]);
						free(note_tmp);
						fclose(file.fp);
						gotoxy(9,xy+5);
						printf("입력을 종료합니다.");
						Sleep(700);
						np_select(); 
						break;
					default:
						break;
				}
			}
		}
	}
	
}

void Note_list()
{
	int xy=6;
	int i;
	int count=0;
	char **Save_tmp;
	
	File file;
	
	system("cls");

	count=Note_count();
	
	p_printing(10,50);
	
	Save_tmp = Note_save_get();

	for(i=0;i<count;i++) 
	{
		gotoxy(13,xy);
		xy+=2;
		
		fputs(Save_tmp[i],stdout);
	}
	
	for(i=0;i<count;i++) //free - tmp[];
		free(Save_tmp[i]);
		
	free(Save_tmp);
}

void Note_del()
{
	File file;
	int check = Note_count();
	int i;
	int tmp;
	int str_chk;
	char **Save_tmp;
	
	Note_list();

	gotoxy(10,25);
	fprintf(stdout,"삭제하실 메모의 이름을 입력해주세요 : ");
	gotoxy(10,30);
	fprintf(stdout,"뒤로 가시려면 'back'을 입력해주세요");
	
	file.File_name = (char *)calloc(20,sizeof(char));
	
	gotoxy(10,27);
	fgets(file.File_name,20,stdin);
	
	file.File_name[strlen(file.File_name)-1]=NULL;
	 
	if(strcmp("back",file.File_name)==0)
	{
		gotoxy(10,32);
		fprintf(stdout,"메인으로 돌아갑니다.");
		Sleep(500);
		system("cls");
		np_select();
	}
	
	strcat(file.File_name,".txt");
	
	Save_tmp=Note_save_get();
	
	for(i=0;i<check;i++)
	{
		str_chk = strcmp(Save_tmp[i],file.File_name);
		
		if(str_chk==0)
		{
			file.chk=true;	
			memset(Save_tmp[i],NULL,sizeof(char)*20);
			break;
		}
		else if(str_chk!=0)
			file.chk=false;
	}
	
	if(file.chk==true)
	{
		file.fp = fopen("Save_n.txt","w");
		
		for(i=0;i<check;i++)
		{
			fprintf(file.fp,"%s\n",Save_tmp[i]);
		}
		
		remove(file.File_name);
		fclose(file.fp);
		
		system("cls");
		Note_list();
		gotoxy(10,25);
		fprintf(stdout,"삭제가 완료되었습니다.");
		gotoxy(10,27);
		fprintf(stdout,"아무키나 눌러주세요.");
		
		if(_getch())
		{
			gotoxy(10,31);
			fprintf(stdout,"메인으로 돌아갑니다.");
			Sleep(500); 
			for(i=0;i<check;i++) //free - tmp[];
	    		free(Save_tmp[i]);
		
	        free(Save_tmp);
			system("cls");
			np_select();	
		} 
	}
	else if(file.chk==false)
	{
		system("cls");
		Note_list();
		gotoxy(10,26);
		fprintf(stdout,"입력하신 파일이 없습니다."); 
		gotoxy(10,28);
		fprintf(stdout,"메인으로 돌아갑니다.");
		Sleep(500); 
		for(i=0;i<check;i++) //free - tmp[];
			free(Save_tmp[i]);
		
	    free(Save_tmp);
		system("cls");
		np_select();
	}
	
	for(i=0;i<check;i++) //free - tmp[];
		free(Save_tmp[i]);
		
	free(Save_tmp);
}

void Note_view()
{
	int count = Note_count()-1;
	int s_count = Note_count_sub();
	int select_num;
	int xy=6;
	int qw=6;
	int note_file_count=0;
	char **Save_tmp = NULL;
	char **note_=NULL;
	char *tmp = NULL;
	char pass_tmp[50];
	int pass_chk=1;
	bool chkchkchk;
	File file;
	
	Note_list();
	
	for(int i=0;i<s_count;i++)
	{
		gotoxy(10,xy);
		printf("%d. ",i+1);
		xy+=2;
	}
	gotoxy(10,26);
		
	tmp=(char *)calloc(50,sizeof(char));

	while(1)
	{
		printf("열람하실 메모를 선택해주세요 : ");
		gotoxy(10,29);
		fprintf(stdout,"Previous Step - Press the backspace");
		if(_kbhit)
		{
			Beeep();
			select_num = _getch();
			select_num = select_num - 49;
			
			if(select_num==-41)
			{
				gotoxy(10,31); 
				printf("메인으로 돌아갑니다.");
				Sleep(500);
				system("cls");
				np_select();
			}
			
			system("cls");
			p_printing(10,50);
			
			Save_tmp=Note_save_get();	
			
		
			file.fp=fopen(Save_tmp[select_num],"r");
			
			while(!feof(file.fp))
			{
				if(feof(file.fp))
					break;
				fgets(tmp,50,file.fp);
				note_file_count++;
			}
			fclose(file.fp);
			
			note_=(char **)calloc(note_file_count,sizeof(char *));
			for(int i=0;i<note_file_count;i++)
				note_[i]=(char *)calloc(50,sizeof(char));
		
			file.fp=fopen(Save_tmp[select_num],"r");
			for(int i=0;i<note_file_count;i++)
				fgets(note_[i],50,file.fp);
			fclose(file.fp);
	
			if(strcmp(note_[note_file_count-3],"pass_\n")==0)
			{
				while(pass_chk)
				{
				
					gotoxy(10,6);
					fprintf(stdout,"암호가 설정된 메모입니다.");
					gotoxy(10,9);
					fprintf(stdout,"암호를 입력해주세요 : ");
					gotoxy(10,14);
					fprintf(stdout,"뒤로 가시려면 'back'을 입력해주세요.");
					gotoxy(10,11);
					fgets(pass_tmp,50,stdin);
				//	pass_tmp[strlen(pass_tmp)-1]=NULL;
					if(strcmp("back\n",pass_tmp)==0)
					{
						gotoxy(10,16);
						printf("메인으로 돌아갑니다.");
						Sleep(500);
						system("cls");
						np_select();
					} 
					if(strcmp(note_[note_file_count-2],pass_tmp)==0)
					{
					//	system("cls");
						p_printing(10,50);
						pass_chk=0;
						chkchkchk=true;
						break;
					}
					else
					{
						gotoxy(10,17);
						printf("다시 입력해주세요.");
						Sleep(500);
						system("cls");
						p_printing(10,50); 
					}
					
				}
			}
			else
				chkchkchk=false;
			
			if(chkchkchk==true){
			
				gotoxy(10,17);
				Sleep(200);
				printf("암호가 일치합니다.");
				gotoxy(10,19);
				fprintf(stdout,"로 딩 중");
	
				for(int j=19;j<22;j++)
				{
					Sleep(310);
					gotoxy(j,19);
					printf(".");
				}
					Sleep(400);
					system("cls"); 
					p_printing(10,50);
					
				for(int i=0;i<note_file_count-4;i++)
				{
					gotoxy(10,qw);
					fprintf(stdout,"%s",note_[i]);
					qw+=2;
				}
			}
			else
			{
				for(int i=0;i<note_file_count-2;i++)
				{
					gotoxy(10,qw);
					fprintf(stdout,"%s",note_[i]);
					qw+=2;
				}
			}
			
			
			gotoxy(10,31);
			fprintf(stdout,"아무키나 눌러주시면 메인으로 이동합니다.");
			if(_getch())
			{
				system("cls");
				np_select();	
			}
		}	
	} 
}

int Note_count()
{
	File file;
	char str[30]={0,};
	int count=0;
	bool chkchk;
	
	file.fp=fopen("Save_n.txt","r");
	
	if(file.fp==NULL)
	{
		system("cls");
		printing();
		gotoxy(8,4);
		fprintf(stdout,"Warning!");
		gotoxy(8,6);
		fprintf(stdout,"Save_n.txt 파일을 찾을 수 없습니다.");
		gotoxy(8,8);
		fprintf(stdout,"노트를 기록해 주신 후 사용하세요.");
		Sleep(1200);
		main();
	}
	
	while(!feof(file.fp))
	{
		if(feof(file.fp))
			break;
		fgets(str,30,file.fp);
		for(int i=0;i<30;i++)
		{
			if(str[i]==NULL)
				chkchk=true;
			else
			{
				chkchk=false;
				break;
			}
		}
		if(chkchk==true)
			break;
		count++;
	}
	fclose(file.fp);
	return count;
}

int Note_file_count(char *File_name)
{
	File file;
	char str[30]={0,};
	int count=0;
	
	file.fp=fopen(File_name,"r");
	
	if(file.fp==NULL)
	{
		system("cls");
		printing();
		gotoxy(8,4);
		fprintf(stdout,"Warning!");
		gotoxy(8,6);
		fprintf(stdout,"%s 파일을 찾을 수 없습니다.",File_name);
		gotoxy(8,8);
		fprintf(stdout,"노트를 기록해 주신 후 사용하세요.");
		Sleep(1200);
		main();
	}
	
	while(!feof(file.fp))
	{
		if(feof(file.fp))
			break;
		fgets(str,30,file.fp);
		count++;
	}
	fclose(file.fp);
	return count;
}

char **Note_save_get()
{
	File file;
	char **Save_tmp = NULL;
	int count;
	int i;
	
	count = Note_count();
	
	Save_tmp = (char **)calloc(count,sizeof(char *));
	
	for(i=0;i<count;i++)
		Save_tmp[i] = (char *)calloc(50,sizeof(char));
	
	file.fp = fopen("Save_n.txt","r");
	
	for(i=0;i<count;i++)
		fscanf(file.fp,"%s",Save_tmp[i]);
	
	fclose(file.fp);
	return Save_tmp;	
}


void select()
{
	int select_num;
	printing();
	while(1)
	{
		system("cls");
		printing();
		gotoxy(10,6);
		printf("1. Add record");
		gotoxy(10,9);
		printf("2. Search record");
		gotoxy(10,12);
		printf("3. Delete record");
		gotoxy(10,15);
		printf("4. Modify record");
		gotoxy(10,18);
		printf("5. Read record");
		gotoxy(13,21);
		printf("Previous Step - Press the backspace");
		
		if(_kbhit)
		{
			Beeep();
			select_num=_getch();
			switch(select_num)
			{
				case 49:
					game_select();
					break;
				case 50:
					_Search_select();
					break;
				case 51:
					File_print();
					File_del();
					break;
				case 52:
					Modify_file();
					break;
				case 53:
					Read_file();
					break;
				case 8:
					system("cls");
					main_select();
					break;
			}
		}
	}
}

void game_select()
{
	int select_num;
	
	system("cls");
	printing();
	
	while(1)
	{
		gotoxy(10,8);
		printf("1. League Of Legends");
		gotoxy(10,14);
		printf("2. Kart Rider");
		gotoxy(14,20);
		printf("Previous Step - Press the backspace");
		
		if(_kbhit)
		{
			Beeep();
			select_num=_getch();
			
			switch(select_num)
			{
				case 49:
					Title_set(1);
					break;
				case 50:
					Title_set(2);
					break;
				case 8:
					select();
					break;
			}
		}
	}
}

int game_select_print()
{
	int select_num;
	
	system("cls");
	printing();
	
	while(1)
	{
		gotoxy(10,8);
		printf("1. League Of Legends");
		gotoxy(10,14);
		printf("2. Kart Rider");
		gotoxy(14,20);
		printf("Previous Step - Press the backspace");
		
		if(_kbhit)
		{
			Beeep();
			select_num=_getch();
			
			switch(select_num)
			{
				case 49:
					return 1;
					break;
				case 50:
					return 2;
					break;
				case 8:
					select();
					break;
			}
		}
	}
}

void Title_set(int p)
{
	system("cls");
	printing();
	
	File _file;
	char *tmptmp;

	_file.File_name=NULL;
	_file.File_name=(char *)calloc(40,sizeof(char));
	
	if(clean>0)
	{
		free(_file.File_name);
		_file.File_name=(char *)calloc(40,sizeof(char));
	}
		
	gotoxy(12,9);
	fprintf(stdout,"파일 이름을 입력해주세요 : ");
	gotoxy(12,21);
	fprintf(stdout,"뒤로 가시려면 'back' 을 입력해주세요.");
	
	gotoxy(12,11);
	fgets(_file.File_name,sizeof(_file.File_name),stdin);
	_file.File_name[strlen(_file.File_name)-1]=NULL;
	
	while(getchar()!='\n');
	
	if(strcmp("back",_file.File_name)==0)
	{
		gotoxy(12,13);
		fprintf(stdout,"전 단계로 돌아갑니다.");
		Sleep(500);
		system("cls");
		select(); 
	}

	Data_save(&_file.File_name,&p);
	
}

void Data_save(char **File_name,int *p)
{	
	FILE *fp=NULL;
	char *tmp_fname=NULL;
	int n_len;	
	int lap_chk;	
	
	fp=fopen("Save.txt","a+");
	
	strcat(*File_name,".txt");
	
	n_len = strlen(*File_name);
	tmp_fname = (char *)calloc(n_len,sizeof(char));
	
	strcpy(tmp_fname,*File_name);

	lap_chk=File_check(&tmp_fname);
	
	if(lap_chk)
	{
		
		printf("같은 이름의 파일이 존재합니다.\n");
		printf("아무키나 눌러주세요.");
		if(_kbhit())
		{
			select();
			Beeep();
		}
	}

	fprintf(fp,"%s\n",*File_name);
	fclose(fp);
	
	File_Create(&File_name,&p);
}

void File_Create(char ***File_name,int **p)
{
	FILE *fp=NULL;
	
	system("cls");
	p_printing(8,50);
	
	Game LOL={NULL,NULL,0,0,0,0,0,0.0};
	game Kart={NULL,NULL,NULL,NULL,NULL};
	
	if(**p==1)
	{
		gotoxy(10,6);
		fprintf(stdout,"Nickname : ");
		gotoxy(10,9);
		fprintf(stdout,"Champion : ");
		gotoxy(10,12);
		fprintf(stdout,"Kill : ");
		gotoxy(10,15);
		fprintf(stdout,"Death : ");
		gotoxy(10,18);
		fprintf(stdout,"Assist : ");
		gotoxy(10,21);
		fprintf(stdout,"CS : ");
		
		gotoxy(21,6);
		fgets(LOL.Nick_name,sizeof(LOL.Nick_name),stdin);
		LOL.Nick_name[strlen(LOL.Nick_name)-1]=NULL;
		gotoxy(21,9);
		fgets(LOL.Champ,sizeof(LOL.Champ),stdin);
		LOL.Champ[strlen(LOL.Champ)-1]=NULL;
		gotoxy(16,12);
		fscanf(stdin,"%d",&LOL.Kill);
		gotoxy(17,15);
		fscanf(stdin,"%d",&LOL.Death);
		gotoxy(18,18);
		fscanf(stdin,"%d",&LOL.Assist);
		gotoxy(15,21);
		fscanf(stdin,"%d",&LOL.Cs);
		
		LOL.Avg=(double)(LOL.Kill+LOL.Assist)/(LOL.Death);
		
		fp=fopen(**File_name,"w");
		fprintf(fp,"%s\n%s\n%d\n%d\n%d\n%d\n%.2lf",
		LOL.Nick_name,LOL.Champ,LOL.Kill,LOL.Death,LOL.Assist,LOL.Cs,LOL.Avg);
		
		getchar();
		
		fclose(fp);
	
		clean++;
	
		gotoxy(10,24);
		fprintf(stdout,"메인화면으로 돌아갑니다.");
		Sleep(600);
		
		system("cls");
		
		select();
	}
	else if(**p==2)
	{
		gotoxy(10,6);
		fprintf(stdout,"Nickname : ");
		gotoxy(10,9);
		fprintf(stdout,"Date : ");
		gotoxy(10,12);
		fprintf(stdout,"Kart : ");
		gotoxy(10,15);
		fprintf(stdout,"Lap Time : ");
		gotoxy(10,18);
		fprintf(stdout,"Time : ");
		gotoxy(10,21);
		fprintf(stdout,"Map : ");
		
		gotoxy(21,6);
		fgets(Kart.Nick_name,sizeof(Kart.Nick_name),stdin);
		Kart.Nick_name[strlen(Kart.Nick_name)-1]=NULL;
		gotoxy(17,9);
		fgets(Kart.Date,sizeof(Kart.Date),stdin);
		Kart.Date[strlen(Kart.Date)-1]=NULL;
		gotoxy(17,12);
		fgets(Kart.Kart,sizeof(Kart.Kart),stdin);
		Kart.Kart[strlen(Kart.Kart)-1]=NULL;
		gotoxy(21,15);
		fgets(Kart.Lap_time,sizeof(Kart.Lap_time),stdin);
		Kart.Lap_time[strlen(Kart.Lap_time)-1]=NULL;
		gotoxy(17,18);
		fgets(Kart.Time,sizeof(Kart.Time),stdin);
		Kart.Time[strlen(Kart.Time)-1]=NULL;
		gotoxy(16,21);
		fgets(Kart.Map,sizeof(Kart.Map),stdin);
		Kart.Map[strlen(Kart.Map)-1]=NULL;
		
		fp=fopen(**File_name,"w");
		fprintf(fp,"%s\n%s\n%s\n%s\n%s\n%s\n\n%c",
		Kart.Nick_name,Kart.Date,Kart.Kart,Kart.Lap_time,Kart.Time,Kart.Map,'K');
		
		getchar();
		
		fclose(fp);
	
		clean++;
	
		gotoxy(10,24);
		fprintf(stdout,"메인화면으로 돌아갑니다.");
		Sleep(600);
		
		system("cls");
		
		select();
	}
	
}

int File_check(char **File_name) //Save.txt overlap chk
{
	int i;
	int str_chk;
	int check;
	char **Save_tmp=NULL;
	char *tmptmp; 
	bool chk=false;
	
	check = File_Count();
	
	Save_tmp=Save_get();

	for(i=0;i<check;i++)
	{	
		str_chk = strcmp(*File_name,Save_tmp[i]);
	
		if(str_chk==0)
			chk = 1;
	
		else if(str_chk!=0)
			chk = 0;
	}
	
	for(i=0;i<check;i++) //free - tmp[];
		free(Save_tmp[i]);
	
	free(Save_tmp);
	
	return chk;
}

void notice() //overlap chk fin
{	

		printf("같은 이름의 파일이 존재합니다.\n");
		printf("아무키나 눌러주세요.");
		if(_kbhit())
			main(); 

}

int File_Count() //Save.txt - line 
{
	File file;
	
	int cnt=0;
	char *buff=NULL;
	
	file.fp = fopen("Save.txt","r");
	
	if(file.fp==NULL)
	{
		system("cls");
		printing();
		gotoxy(8,4);
		fprintf(stdout,"Warning!");
		gotoxy(8,6);
		fprintf(stdout,"Save.txt 파일을 찾을 수 없습니다.");
		gotoxy(8,8);
		fprintf(stdout,"전적을 입력해 주신 후 사용하세요.");
		Sleep(1200);
		main();
	}
		
	
	buff=(char *)calloc(50,sizeof(char));
	
	while(!feof(file.fp))
	{
		fgets(buff,sizeof(buff),file.fp);
	//	fscanf(file.fp,"%s",buff);
		cnt++;
	}
	
	free(buff);
	fclose(file.fp);
	
	return cnt;
}

int File_Count_sub()
{
	File file;
	
	int cnt=0;
	char *buff=NULL;
	
	file.fp = fopen("Save.txt","r");
	
	if(file.fp==NULL)
	{
		system("cls");
		printing();
		gotoxy(8,4);
		fprintf(stdout,"Warning!");
		gotoxy(8,6);
		fprintf(stdout,"Save.txt 파일을 찾을 수 없습니다.");
		gotoxy(8,8);
		fprintf(stdout,"전적을 입력해 주신 후 사용하세요.");
		gotoxy(8,14);
		fprintf(stdout,"아무 키나 눌러주시면 메인으로 돌아갑니다.");
		if(_getch()) 
			main();
	}
		
	
	buff=(char *)calloc(50,sizeof(char));
	
	while(!feof(file.fp))
	{
	//	fgets(buff,sizeof(buff),file.fp);
		fscanf(file.fp,"%s",buff);
		cnt++;
	}
	
	free(buff);
	fclose(file.fp);
	
	cnt=cnt-1;
	return cnt;
}

int Note_count_sub()
{
	File file;
	
	int cnt=0;
	char *buff=NULL;
	
	file.fp = fopen("Save_n.txt","r");
	
	if(file.fp==NULL)
	{
		system("cls");
		printing();
		gotoxy(8,4);
		fprintf(stdout,"Warning!");
		gotoxy(8,6);
		fprintf(stdout,"Save.txt 파일을 찾을 수 없습니다.");
		gotoxy(8,8);
		fprintf(stdout,"전적을 입력해 주신 후 사용하세요.");
		gotoxy(8,14);
		fprintf(stdout,"아무 키나 눌러주시면 메인으로 돌아갑니다.");
		if(_getch()) 
			main();
	}
		
	
	buff=(char *)calloc(50,sizeof(char));
	
	while(!feof(file.fp))
	{
	//	fgets(buff,sizeof(buff),file.fp);
		fscanf(file.fp,"%s",buff);
		cnt++;
	}
	
	free(buff);
	fclose(file.fp);
	
	cnt=cnt-1;
	return cnt;
}

void File_print()
{
	int xy=6;
	int i,count=0;
	char **Save_tmp;
	
	File file;
	
	system("cls");

	count = File_Count();
	
	p_printing(10,50);
	
	Save_tmp = Save_get();

	for(i=0;i<count;i++) 
	{
		gotoxy(10,xy);
		xy+=2;
		
		fputs(Save_tmp[i],stdout);
	}
	
	for(i=0;i<count;i++) //free - tmp[];
		free(Save_tmp[i]);
		
	free(Save_tmp);
	
	Sleep(300);
}

void File_print_sub()
{
	int xy=6;
	int i,count=0;
	char **Save_tmp;
	
	File file;
	
	system("cls");

	count = File_Count_sub();
	
	p_printing(10,50);
	
	Save_tmp = Save_get();

	for(i=0;i<count;i++) 
	{
		gotoxy(13,xy);
		xy+=2;
		
		fputs(Save_tmp[i],stdout);
	}
	
	for(i=0;i<count;i++) //free - tmp[];
		free(Save_tmp[i]);
		
	free(Save_tmp);
	
	Sleep(300);
}

int game_chk(char **File_name)
{
	File file;
	int select_g=0;
	char *tmptmp;
	
	file.fp=fopen((char *)*File_name,"r");
	
	tmptmp=(char *)calloc(50,sizeof(char));
			
	for(int i=0;i<8;i++)
	{
		fgets(tmptmp,50,file.fp);
	}
	if(strcmp(tmptmp,"K")==0)
		select_g=2;
	else
		select_g=1;
		
	fclose(file.fp);	
	return select_g;
}

void Read_file()
{
	int count = File_Count_sub();
	int select_num;
	int xy=6;
	int qw=6;
	int select_g=0;
	char **Save_tmp = NULL;
	char *tmp = NULL;
	char *tmptmp = NULL;
	File file;
	Game LOL;
	game Kart;
	
	File_print_sub();
	
	for(int i=0;i<count;i++)
	{
		gotoxy(10,xy);
		printf("%d. ",i+1);
		xy+=2;
	}
	gotoxy(10,xy+2);
	
	while(1)
	{
		printf("열람하실 전적을 선택해주세요 : ");
		gotoxy(10,xy+5);
		fprintf(stdout,"Previous Step - Press the backspace");
		if(_kbhit)
		{
			Beeep();
			select_num = _getch();
			select_num = select_num - 49;
			
			if(select_num==-41)
			{
				gotoxy(10,xy+8); 
				printf("메인으로 돌아갑니다.");
				Sleep(500);
				system("cls");
				select();
			}
			
			system("cls");
			p_printing(8,50);
			
			Save_tmp=Save_get();	
			
			select_g=game_chk(&Save_tmp[select_num]);
		
			file.fp=fopen((char *)Save_tmp[select_num],"r");

			if(select_g==1){
				fscanf(file.fp,"%[^\n]\n%[^\n]\n%d\n%d\n%d\n%d\n%lf",
				LOL.Nick_name,LOL.Champ,&LOL.Kill,&LOL.Death,&LOL.Assist,&LOL.Cs,&LOL.Avg);
		
				fclose(file.fp);
				gotoxy(10,6);
				fprintf(stdout,"Nickname : %s",LOL.Nick_name);
				gotoxy(10,8);
				fprintf(stdout,"Champion : %s",LOL.Champ);
				gotoxy(10,10);
				fprintf(stdout,"Kill : %d",LOL.Kill);
				gotoxy(10,12);
				fprintf(stdout,"Death : %d",LOL.Death);
				gotoxy(10,14);
				fprintf(stdout,"Assist : %d",LOL.Assist);
				gotoxy(10,16);
				fprintf(stdout,"Cs : %d",LOL.Cs);
				gotoxy(10,18);
				fprintf(stdout,"Avg : %.2lf",LOL.Avg);
				
				gotoxy(8,22);
				fprintf(stdout,"아무키나 눌러주시면 메인으로 이동합니다.");
				if(_getch())
				{
					system("cls");
					select();	
				}
			}
			else if(select_g==2)
			{
				fscanf(file.fp,"%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]",
				Kart.Nick_name,Kart.Date,Kart.Kart,Kart.Lap_time,Kart.Time,Kart.Map);
				
				fclose(file.fp);
				gotoxy(10,6);
				fprintf(stdout,"Nickname : %s",Kart.Nick_name);	
				gotoxy(10,9);
				fprintf(stdout,"Date : %s",Kart.Date);
				gotoxy(10,12);
				fprintf(stdout,"Kart : %s",Kart.Kart);
				gotoxy(10,15);
				fprintf(stdout,"Lap Time : %s",Kart.Lap_time);
				gotoxy(10,18);
				fprintf(stdout,"Time : %s",Kart.Time);
				gotoxy(10,21);
				fprintf(stdout,"Map : %s",Kart.Map);
				
				gotoxy(10,25);
				fprintf(stdout,"아무키나 눌러주시면 메인으로 이동합니다.");
				if(_getch())
				{
					system("cls");
					select();	
				}
				
			}
		}	
	} 
}

void File_del()
{
	File file;
	int len = (File_Count())*2+3;
	int check = File_Count();
	int i;
	int tmp;
	int str_chk;
	char **Save_tmp;
	
	gotoxy(10,25);
	fprintf(stdout,"삭제하실 전적의 이름을 입력해주세요 : ");
	gotoxy(10,30);
	fprintf(stdout,"뒤로 가시려면 'back'을 입력해주세요");
	
	file.File_name = (char *)calloc(20,sizeof(char));
	
	gotoxy(10,27);
	fgets(file.File_name,20,stdin);
	
	file.File_name[strlen(file.File_name)-1]=NULL;
	
	if(strcmp("back",file.File_name)==0)
	{
		gotoxy(10,32);
		fprintf(stdout,"메인으로 돌아갑니다.");
		Sleep(500);
		system("cls");
		select();
	}
	
	strcat(file.File_name,".txt");
	
	Save_tmp=Save_get();
	
	for(i=0;i<check;i++)
	{
		str_chk = strcmp(Save_tmp[i],file.File_name);
		
		if(str_chk==0)
		{
			file.chk=true;	
			memset(Save_tmp[i],NULL,sizeof(char)*20);
			break;
		}
		else if(str_chk!=0)
			file.chk=false;
	}
	
	if(file.chk==true)
	{
		file.fp = fopen("Save.txt","w");
		
		for(i=0;i<check;i++)
		{
			fprintf(file.fp,"%s\n",Save_tmp[i]);
		}
		
		remove(file.File_name);
		fclose(file.fp);
		
		system("cls");
		File_print();
		gotoxy(10,25);
		fprintf(stdout,"삭제가 완료되었습니다.");
		gotoxy(10,27);
		fprintf(stdout,"아무키나 눌러주세요.");
		
		if(_getch())
		{
			gotoxy(10,31);
			fprintf(stdout,"메인으로 돌아갑니다.");
			Sleep(500); 
			for(i=0;i<check;i++) //free - tmp[];
	    	free(Save_tmp[i]);
		
	        free(Save_tmp);
			system("cls");
			select();	
		} 
	}
	else if(file.chk==false)
	{
		system("cls");
		File_print();
		gotoxy(10,26);
		fprintf(stdout,"입력하신 파일이 없습니다."); 
		gotoxy(10,28);
		fprintf(stdout,"메인으로 돌아갑니다.");
		Sleep(500); 
		for(i=0;i<check;i++) //free - tmp[];
		free(Save_tmp[i]);
		
	    free(Save_tmp);
		system("cls");
		select();
	}
	
	for(i=0;i<check;i++) //free - tmp[];
		free(Save_tmp[i]);
		
	free(Save_tmp);
}

void _Search_select()
{
	int select_num;
	
	while(1)
	{
		system("cls");
		printing;
		p_printing(6,50);
	
		gotoxy(10,8); 
		printf("1. Search for File name");
		gotoxy(10,11);
		printf("2. Search for Nick name");
		gotoxy(10,14);
		printf("3. Search for Champion");
		gotoxy(13,19);
		printf("Previous Step - Press the backspace");
		
		if(_kbhit)
		{
			Beeep();
			select_num = _getch();
			switch(select_num)
			{
				case 49:
					Search_filename();
					break;
				case 50:
					Search_name();
					break;
				case 51:
					Search_for_champ();
					break;
				case 8:
					select();
					break;
				default :
					break;
			}
		}
	}
}

void Search_name()
{
	char **Save_tmp = NULL; // from Save_get()
	char **Name_tmp = NULL; // Nickname tmp
	char **Correct_file = NULL; // correct Nickname - Filename
	int xy=10;
	int count;
	int qwer=1;
	int select_g=0;
	int select_num;
	int c_index=0;
	int str_chk=0;
	int v_chk=0;
	File file;
	Game LOL;
	game Kart;
	
	Save_tmp = Save_get();
	count = File_Count();
	
	system("cls");
	p_printing(6,50);
	
	gotoxy(9,7);
	fprintf(stdout,"닉네임을 입력해주세요 : ");
	gotoxy(33,7);
	fgets(LOL.Nick_name,sizeof(LOL.Nick_name),stdin);
	LOL.Nick_name[strlen(LOL.Nick_name)-1]=NULL;
	
	Name_tmp = (char **)calloc(count,sizeof(char *));
	for(int i=0;i<count;i++)
		Name_tmp[i]=(char *)calloc(30,sizeof(char));
	
	
	for(int i=0;i<count;i++)
	{
		file.fp=fopen(Save_tmp[i],"r");
		
		fscanf(file.fp,"%[^\n]s",Name_tmp[i]);
		
		str_chk = strcmp(Name_tmp[i],LOL.Nick_name);
		
		if(str_chk==0)
			v_chk++;
	}
	fclose(file.fp);
	
	Correct_file=(char **)calloc(v_chk,sizeof(char *));
	for(int i=0;i<v_chk;i++)
		Correct_file[i]=(char *)calloc(30,sizeof(char));
		
	for(int i=0;i<count;i++)
	{
		str_chk = strcmp(Name_tmp[i],LOL.Nick_name);
		
		if(str_chk==0)
		{	
			strcpy(Correct_file[c_index],Save_tmp[i]);
			c_index++;
		}
	}
	
	{
		gotoxy(10,18);
		fprintf(stdout,"검 색 중");
		
		for(int j=18;j<21;j++)
		{
			Sleep(380);
			gotoxy(j,18);
			printf(".");
		}
		Sleep(400);
	}
	
	system("cls");
	p_printing(7,50);
	
	if(v_chk==0)
	{
		system("cls");
		p_printing(6,50);
		gotoxy(10,8);
		fprintf(stdout,"일치하는 닉네임이 없습니다.");
		gotoxy(10,10);
		fprintf(stdout,"아무키나 눌러주세요.");
		_getch();
		gotoxy(10,13); 
		fprintf(stdout,"메인으로 돌아갑니다.");
		Sleep(500);
		select(); 
	}
	
	gotoxy(8,6);
	fprintf(stdout,"%s 으로 %d 개의 전적이 검색되었습니다.",LOL.Nick_name,v_chk);
	
	
	for(int i=0;i<v_chk;i++)
	{
		gotoxy(10,xy);
		fprintf(stdout,"%d. %s   - %s",qwer,Correct_file[i],LOL.Nick_name);
		xy+=2;
		qwer++;
	}
	
	while(1)
	{
		gotoxy(12,xy+3);
		fprintf(stdout,"열람하실 전적을 선택해주세요.");
		
		if(_kbhit)
		{
			select_num = _getch();
			select_num=select_num-49;
			
			system("cls");
			p_printing(7,50);
			
			file.fp = fopen(Correct_file[select_num],"r");
			
			select_g=game_chk(&Correct_file[select_num]);
			
			memset(LOL.Nick_name,NULL,sizeof(LOL.Nick_name));
			
			if(select_g==1)
			{
				fscanf(file.fp,"%[^\n]\n%[^\n]\n%d\n%d\n%d\n%d\n%lf",
				LOL.Nick_name,LOL.Champ,&LOL.Kill,&LOL.Death,&LOL.Assist,&LOL.Cs,&LOL.Avg);
			
				fclose(file.fp);
				gotoxy(10,6);
				fprintf(stdout,"Nickname : %s",LOL.Nick_name);
				gotoxy(10,8);
				fprintf(stdout,"Champion : %s",LOL.Champ);
				gotoxy(10,10);
				fprintf(stdout,"Kill : %d",LOL.Kill);
				gotoxy(10,12);
				fprintf(stdout,"Death : %d",LOL.Death);
				gotoxy(10,14);
				fprintf(stdout,"Assist : %d",LOL.Assist);
				gotoxy(10,16);
				fprintf(stdout,"Cs : %d",LOL.Cs);
				gotoxy(10,18);
				fprintf(stdout,"Avg : %.2lf",LOL.Avg);
				
				gotoxy(8,22);
				fprintf(stdout,"아무키나 눌러주시면 메인으로 이동합니다.");
				if(_getch())
				{
					system("cls");
					select();	
				} 
			}
			else if(select_g==2)
			{
				fscanf(file.fp,"%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]",
				Kart.Nick_name,Kart.Date,Kart.Kart,Kart.Lap_time,Kart.Time,Kart.Map);
			
				fclose(file.fp);
				gotoxy(10,9);
				fprintf(stdout,"Nick name : %s",Kart.Nick_name);
				gotoxy(10,12);
				fprintf(stdout,"Date : %s",Kart.Date);
				gotoxy(10,15);
				fprintf(stdout,"Kart : %s",Kart.Kart);
				gotoxy(10,18);
				fprintf(stdout,"Lap time : %s",Kart.Lap_time);
				gotoxy(10,21);
				fprintf(stdout,"Time : %s",Kart.Time);
				gotoxy(10,24);
				fprintf(stdout,"Map : %s",Kart.Map);
				
				gotoxy(8,22);
				fprintf(stdout,"아무키나 눌러주시면 메인으로 이동합니다.");
				if(_getch())
				{
					system("cls");
					select();	
				} 
			}
		}
	}
}

void Search_for_champ()
{
	char **Save_tmp = NULL; // from Save_get()
	char **Name_tmp = NULL; // Nickname tmp
	char **Correct_file = NULL; // correct Nickname - Filename
	char tmptmp[30];
	int xy=10;
	int count;
	int select_g=0;
	int qwer=1;
	int select_num;
	int c_index=0;
	int str_chk=0;
	int v_chk=0;
	File file;
	Game LOL;
	
	Save_tmp = Save_get();
	count = File_Count();
	
	system("cls");
	p_printing(6,50);
	
	gotoxy(9,7);
	fprintf(stdout,"챔피언 이름을 입력해주세요 : ");
	gotoxy(9,9);
	fgets(LOL.Nick_name,sizeof(LOL.Nick_name),stdin);
	LOL.Nick_name[strlen(LOL.Nick_name)-1]=NULL;
	
	Name_tmp = (char **)calloc(count,sizeof(char *));
	for(int i=0;i<count;i++)
		Name_tmp[i]=(char *)calloc(30,sizeof(char));
	
	
	for(int i=0;i<count;i++)
	{
		file.fp=fopen(Save_tmp[i],"r");
		
		fgets(tmptmp,sizeof(tmptmp),file.fp); 
		fscanf(file.fp,"%[^\n]s",Name_tmp[i]);
		
		str_chk = strcmp(Name_tmp[i],LOL.Nick_name);
		
		if(str_chk==0)
			v_chk++;
	}
	fclose(file.fp);
	
	Correct_file=(char **)calloc(v_chk,sizeof(char *));
	for(int i=0;i<v_chk;i++)
		Correct_file[i]=(char *)calloc(30,sizeof(char));
		
	for(int i=0;i<count;i++)
	{
		str_chk = strcmp(Name_tmp[i],LOL.Nick_name);
		
		if(str_chk==0)
		{	
			strcpy(Correct_file[c_index],Save_tmp[i]);
			c_index++;
		}
	}
	
	{
		gotoxy(10,16);
		fprintf(stdout,"검 색 중");
		
		for(int j=20;j<22;j++)
		{
			Sleep(380);
			gotoxy(j,16);
			printf(".");
		}
		Sleep(400);
	}
	
	system("cls");
	p_printing(7,50);
	
	if(v_chk==0)
	{
		system("cls");
		p_printing(6,50);
		gotoxy(7,8);
		fprintf(stdout,"일치하는 챔피언의 전적이 없습니다.");
		gotoxy(10,10);
		fprintf(stdout,"아무키나 눌러주세요.");
		_getch();
		Beeep();
		gotoxy(10,13); 
		fprintf(stdout,"메인으로 돌아갑니다.");
		Sleep(500);
		select(); 
	}
	
	gotoxy(8,6);
	fprintf(stdout,"%s 으로 %d 개의 전적이 검색되었습니다.",LOL.Nick_name,v_chk);
	
	
	for(int i=0;i<v_chk;i++)
	{
		gotoxy(10,xy);
		fprintf(stdout,"%d. %s   - %s",qwer,Correct_file[i],LOL.Nick_name);
		xy+=2;
		qwer++;
	}
	
	while(1)
	{
		gotoxy(12,xy+3);
		fprintf(stdout,"열람하실 전적을 선택해주세요.");
		
		if(_kbhit)
		{
			Beeep();
			select_num = _getch();
			select_num=select_num-49;
			
			system("cls");
			p_printing(7,50);
			
			file.fp = fopen(Correct_file[select_num],"r");
			
			memset(LOL.Nick_name,NULL,sizeof(LOL.Nick_name));
			
			fscanf(file.fp,"%[^\n]\n%[^\n]\n%d\n%d\n%d\n%d\n%lf",
			LOL.Nick_name,LOL.Champ,&LOL.Kill,&LOL.Death,&LOL.Assist,&LOL.Cs,&LOL.Avg);
			
			fclose(file.fp);
			gotoxy(10,6);
			fprintf(stdout,"Nickname : %s",LOL.Nick_name);
			gotoxy(10,8);
			fprintf(stdout,"Champion : %s",LOL.Champ);
			gotoxy(10,10);
			fprintf(stdout,"Kill : %d",LOL.Kill);
			gotoxy(10,12);
			fprintf(stdout,"Death : %d",LOL.Death);
			gotoxy(10,14);
			fprintf(stdout,"Assist : %d",LOL.Assist);
			gotoxy(10,16);
			fprintf(stdout,"Cs : %d",LOL.Cs);
			gotoxy(10,18);
			fprintf(stdout,"Avg : %.2lf",LOL.Avg);
			
			gotoxy(8,22);
			fprintf(stdout,"아무키나 눌러주시면 메인으로 이동합니다.");
			if(_getch())
			{
				Beeep();
				system("cls");
				select();	
			} 
		}
	}
}

void Search_filename()
{
	int count;
	char **Save_tmp = NULL;
	char Correct_file[50];
	char name_tmp[50];
	File file;
	Game LOL;
	 
	Save_tmp=Save_get();
	count = File_Count_sub();
	
	system("cls");
	p_printing(7,50);
	
	gotoxy(9,7);
	fprintf(stdout,"파일 이름을 입력해주세요 : ");
	gotoxy(9,9);
	fgets(name_tmp,sizeof(name_tmp),stdin);
	name_tmp[strlen(name_tmp)-1]=NULL;
	strcat(name_tmp,".txt");
	
	for(int i=0;i<count;i++)
	{
		file.str_chk = strcmp(Save_tmp[i],name_tmp);
		if(file.str_chk==0)
		{
			strcpy(Correct_file,Save_tmp[i]);
			break;
		}
	}
	{
		gotoxy(10,16);
		fprintf(stdout,"검 색 중");
		
		for(int j=20;j<23;j++)
		{
			Sleep(380);
			gotoxy(j,16);
			printf(".");
		}
		Sleep(500);
	}
	
	system("cls");
	p_printing(8,50);
	Sleep(300);
	
	file.fp=fopen(Correct_file,"r");
	
	fscanf(file.fp,"%[^\n]\n%[^\n]\n%d\n%d\n%d\n%d\n%lf",
	LOL.Nick_name,LOL.Champ,&LOL.Kill,&LOL.Death,&LOL.Assist,&LOL.Cs,&LOL.Avg);
			
	fclose(file.fp);
	gotoxy(10,6);
	fprintf(stdout,"Nickname : %s",LOL.Nick_name);
	gotoxy(10,8);
	fprintf(stdout,"Champion : %s",LOL.Champ);
	gotoxy(10,10);
	fprintf(stdout,"Kill : %d",LOL.Kill);
	gotoxy(10,12);
	fprintf(stdout,"Death : %d",LOL.Death);
	gotoxy(10,14);
	fprintf(stdout,"Assist : %d",LOL.Assist);
	gotoxy(10,16);
	fprintf(stdout,"Cs : %d",LOL.Cs);
	gotoxy(10,18);
	fprintf(stdout,"Avg : %.2lf",LOL.Avg);
			
	gotoxy(8,22);
	fprintf(stdout,"아무키나 눌러주시면 메인으로 이동합니다.");
	if(_getch())
	{
		Beeep();
		system("cls");
		select();	
	}
	
}

void Modify_file()
{
	system("mode con: cols=140 lines=40");
	File file;
	Game LOL;
	game Kart;
	int count;
	int select_num; 
	int xy=6;
	int select_g=0;
	char **Save_tmp;
	
	count=File_Count_sub();
	Save_tmp=Save_get();
	
	system("cls");
	p_printing(8,50);
	
	File_print_sub();
	
	for(int i=0;i<count;i++)
	{
		gotoxy(10,xy);
		printf("%d. ",i+1);
		xy+=2;
	}
	gotoxy(10,xy+4);
	
	while(1)
	{
		fprintf(stdout,"수정하실 전적을 선택해주세요 : ");
		gotoxy(10,xy+7); 
		fprintf(stdout,"Previous Step - Press the backspace");
		
		if(_kbhit)
		{
			select_num=_getch();
			Beeep();
			select_num=select_num-49;
			
			if(select_num==-41)
			{
				gotoxy(10,xy+8); 
				printf("메인으로 돌아갑니다.");
				Sleep(500);
				system("cls");
				select();
			}
			
			system("cls");
			p_printing(10,100);
	
			for(int i=4;i<33;i++)
			{
				gotoxy(104,i);
				printf("*"); 
			}
			
			file.fp=fopen((char *)Save_tmp[select_num],"r");
			
			select_g=game_chk(&Save_tmp[select_num]);
			
			if(select_g==1)
			{
				fscanf(file.fp,"%[^\n]\n%[^\n]\n%d\n%d\n%d\n%d\n%lf",
				LOL.Nick_name,LOL.Champ,&LOL.Kill,&LOL.Death,&LOL.Assist,&LOL.Cs,&LOL.Avg);
		
				gotoxy(15,8);
				fprintf(stdout,"* 수정 전 *");
				gotoxy(10,11);
				fprintf(stdout,"Nickname : %s",LOL.Nick_name);
				gotoxy(10,13);
				fprintf(stdout,"Champion : %s",LOL.Champ);
				gotoxy(10,15);
				fprintf(stdout,"Kill : %d",LOL.Kill);
				gotoxy(10,17);
				fprintf(stdout,"Death : %d",LOL.Death);
				gotoxy(10,19);
				fprintf(stdout,"Assist : %d",LOL.Assist);
				gotoxy(10,21);
				fprintf(stdout,"Cs : %d",LOL.Cs);
				gotoxy(10,23);
				fprintf(stdout,"Avg : %.2lf",LOL.Avg);
				
				gotoxy(65,8);
				fprintf(stdout,"* 새로 입력 *");
				gotoxy(60,11);
				fprintf(stdout,"Nickname : ");
				gotoxy(60,13);
				fprintf(stdout,"Champion : ");
				gotoxy(60,15);
				fprintf(stdout,"Kill : ");
				gotoxy(60,17);
				fprintf(stdout,"Death : ");
				gotoxy(60,19);
				fprintf(stdout,"Assist : ");
				gotoxy(60,21);
				fprintf(stdout,"CS : ");
				
				gotoxy(71,11);
				fgets(LOL.Nick_name,sizeof(LOL.Nick_name),stdin);
				LOL.Nick_name[strlen(LOL.Nick_name)-1]=NULL;
				gotoxy(71,13);
				fgets(LOL.Champ,sizeof(LOL.Champ),stdin);
				LOL.Champ[strlen(LOL.Champ)-1]=NULL;
				gotoxy(67,15);
				fscanf(stdin,"%d",&LOL.Kill);
				gotoxy(68,17);
				fscanf(stdin,"%d",&LOL.Death);
				gotoxy(69,19);
				fscanf(stdin,"%d",&LOL.Assist);
				gotoxy(65,21);
				fscanf(stdin,"%d",&LOL.Cs);
		
				LOL.Avg=(double)(LOL.Kill+LOL.Assist)/(LOL.Death);
				
				file.fp=fopen((char *)Save_tmp[select_num],"w");
				
				fprintf(file.fp,"%s\n%s\n%d\n%d\n%d\n%d\n%.2lf",
				LOL.Nick_name,LOL.Champ,LOL.Kill,LOL.Death,LOL.Assist,LOL.Cs,LOL.Avg);
				
				getchar();
				
				gotoxy(14,26);
				fprintf(stdout,"수정이 완료되었습니다.");
				gotoxy(15,28);
				fprintf(stdout,"아무키나 눌러주세요.");
				if(_getch())
				{
					Beeep();
					fclose(file.fp);
					for(int i=0;i<count;i++)
						free(Save_tmp[i]);
					free(Save_tmp);
					
					gotoxy(15,31);
					fprintf(stdout,"메인으로 돌아갑니다.");
					Sleep(500);
					system("mode con: cols=100 lines=40");
					select();	
				} 
			}
			if(select_g==2)
			{
				fscanf(file.fp,"%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]\n%[^\n]",
				Kart.Nick_name,Kart.Date,Kart.Kart,Kart.Lap_time,Kart.Time,Kart.Map);
		
				gotoxy(15,8);
				fprintf(stdout,"* 수정 전 *");
				gotoxy(10,11);
				fprintf(stdout,"Nick name : %s",Kart.Nick_name);
				gotoxy(10,14);
				fprintf(stdout,"Date : %s",Kart.Date);
				gotoxy(10,17);
				fprintf(stdout,"Kart : %s",Kart.Kart);
				gotoxy(10,20);
				fprintf(stdout,"Lap time : %s",Kart.Lap_time);
				gotoxy(10,23);
				fprintf(stdout,"Time : %s",Kart.Time);
				gotoxy(10,26);
				fprintf(stdout,"Map : %s",Kart.Map);
				
				gotoxy(65,8);
				fprintf(stdout,"* 새로 입력 *");
				gotoxy(60,11);
				fprintf(stdout,"Nick name : ");
				gotoxy(60,14);
				fprintf(stdout,"Date : ");
				gotoxy(60,17);
				fprintf(stdout,"Kart : ");
				gotoxy(60,20);
				fprintf(stdout,"Lap time : ");
				gotoxy(60,23);
				fprintf(stdout,"Time : ");
				gotoxy(60,26);
				fprintf(stdout,"Map : ");
				
				gotoxy(72,11);
				fgets(Kart.Nick_name,sizeof(Kart.Nick_name),stdin);
				Kart.Nick_name[strlen(Kart.Nick_name)-1]=NULL;
				gotoxy(67,14);
				fgets(Kart.Date,sizeof(Kart.Date),stdin);
				Kart.Date[strlen(Kart.Date)-1]=NULL;
				gotoxy(67,17);
				fgets(Kart.Kart,sizeof(Kart.Kart),stdin);
				Kart.Kart[strlen(Kart.Kart)-1]=NULL;
				gotoxy(71,20);
				fgets(Kart.Lap_time,sizeof(Kart.Lap_time),stdin);
				Kart.Lap_time[strlen(Kart.Lap_time)-1]=NULL;
				gotoxy(67,23);
				fgets(Kart.Time,sizeof(Kart.Time),stdin);
				Kart.Time[strlen(Kart.Time)-1]=NULL;
				gotoxy(66,26);
				fgets(Kart.Map,sizeof(Kart.Map),stdin);
				Kart.Map[strlen(Kart.Map)-1]=NULL;
		
				file.fp=fopen((char *)Save_tmp[select_num],"w");
				
				fprintf(file.fp,"%s\n%s\n%s\n%s\n%s\n%s\n\n%c",
				Kart.Nick_name,Kart.Date,Kart.Kart,Kart.Lap_time,Kart.Time,Kart.Map,'K');
				
				getchar();
				
				gotoxy(14,28);
				fprintf(stdout,"수정이 완료되었습니다.");
				gotoxy(15,30);
				fprintf(stdout,"아무키나 눌러주세요.");
				if(_getch())
				{
					Beeep();
					fclose(file.fp);
					for(int i=0;i<count;i++)
						free(Save_tmp[i]);
					free(Save_tmp);
					
					gotoxy(15,32);
					fprintf(stdout,"메인으로 돌아갑니다.");
					Sleep(500);
					system("mode con: cols=100 lines=40");
					select();	
				}
			}
		}		
	}
}

char **Save_get() //get file list
{
	File file;
	char **Save_tmp = NULL;
	int count;
	int i;
	
	count = File_Count();
	
	Save_tmp = (char **)calloc(count,sizeof(char *));
	
	for(i=0;i<count;i++)
		Save_tmp[i] = (char *)calloc(20,sizeof(char));
	
	file.fp = fopen("Save.txt","r");
	
	for(i=0;i<count;i++)
		fscanf(file.fp,"%s",Save_tmp[i]);
	
	fclose(file.fp);
	return Save_tmp;	
}

void printing()
{
	for(int i=0;i<50;i++)
	{
		gotoxy(i+5,3);
		printf("*");
		gotoxy(i+5,23);
		printf("*");		
	}
	for(int j=0;j<21;j++)
	{
		gotoxy(5,j+3);
		printf("*");
		gotoxy(55,j+3);
		printf("*");
	}
}

void p_printing(int p,int op)
{
	int width = p*3;
	
	if(p<5)
		width = 15; 
	
	for(int i=0;i<op;i++)
	{
		gotoxy(i+5,3);
		printf("*");
		gotoxy(i+5,width+3);
		printf("*");
	}
	for(int j=0;j<width;j++)
	{
		gotoxy(5,j+3);
		printf("*");
		gotoxy(55,j+3);
		printf("*");
	}
} 

void gotoxy(int x,int y)
{
	COORD Cur={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Cur);
}

void cursor()
{
	CONSOLE_CURSOR_INFO cci;
	cci.dwSize = 1;
	cci.bVisible = FALSE;  
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cci);
}

void Beeep()
{
//	Beep(430,600);	
}
