#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main(){
	printf("Select an option: \n1. Sign up\n2. Login\n");
	char user_name[1000];
	scanf("%s", user_name);
	FILE * fp;
	char * option = user_name;
	char * current;
	char  id[100];
	if(strcmp(option,"1")==0)
	{
		printf("Please enter your username: \n");
		scanf("%s",id);
		//id = user_name;
		strcat(id,".txt");
		fp = fopen(id,"w");
		fclose(fp);
		return 0;
	}
	else
	{
		printf("Please enter your username: \n");
		scanf("%s", id);
		//id = user_name;
	}
	while(1){
		printf("Select Option:\n1. Read\n2. Write\n3. Exit\n");
		scanf("%s", user_name);
		option = user_name;
		if (strcmp(option,"3")==0)
		{		
			return 0;			
		}
		else if(strcmp("2",option) == 0){
			printf("Enter message \n");
			char msg[1000];
			getchar();
			scanf("%[^\n]", msg);
			printf("Enter number of recipients: \n");
			scanf("%s", user_name);
			int num = atoi(user_name);
			for(int i=0;i<num;i++){
				printf("Enter id of recipients\n");
				scanf("%s", user_name);
				strcat(user_name,".txt");
				key_t key = ftok(user_name,65);
				int shmid = shmget(key,1024,0666|IPC_CREAT);
				char *str = (char *) shmat(shmid,(void *)0,0);
				strcat(str,"\n");
				strcat(str , id);
				strcat(str,": ");
				strcat(str, msg);
				shmdt(str);
			}
		}
		else
		{
				char *id1 = strdup(id);
				strcat(id1,".txt");
				key_t key = ftok(id1,65);
				int shmid = shmget(key,1024,0666|IPC_CREAT);
				char *str = (char*) shmat(shmid,(void*)0,0);
				printf("%s\n", str);
				shmdt(str);
				shmctl(shmid,IPC_RMID,NULL);
		}
	}
	return 0;
}