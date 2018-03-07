#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<sys/un.h>
int main(){
	char cwd[1024];
	getcwd(cwd , sizeof(cwd));
	char *name  = "server.txt";
	strcat(cwd,name);
	int s ,len,t;
	struct sockaddr_un remote;
	char str[5000];
	printf("Enter your id\n");
	char *txt;
	scanf("%s",txt);
	char *id = txt;
	if ((s=socket(AF_UNIX,SOCK_STREAM,0))==-1){
		perror("Error in creating chat client :(");
		exit(1);
	}
	printf("Trying to connect...\n");
	remote.sun_family = AF_UNIX;
	strcpy(remote.sun_path,cwd);
	len = strlen(remote.sun_path)+sizeof(remote.sun_family);
	if (connect(s,(struct sockaddr *)&remote,len)==-1){
		perror("Client unable to connect to server :(");
		exit(1);
	}

	printf("%s is connected to the server.\n",id);
	
	if(send(s,id,strlen(id),0)==-1){
				perror("Message not sent :(");
				exit(1);
	}

	while(1){
		printf("Select Option:\n1. Read\n2.Write\n3.Exit");
		scanf("%s",txt);
		char*option = txt;
		if (option.strcmp("3") == 0)
		{		
				close(s);
				break;
		}
		else if(option.strcmp("2") == 0){
			printf("Enter message\n");
			scanf("%s",txt);
			char *msg = txt;
			printf("Enter id of recipients\n");
			scanf("%s",txt);
			strcat(str,id);
			strcat(str,"$");
			strcat(str,msg);
			strcat(str,"$");
			strcat(str,txt);
			strcat(str,'\0');
			if(send(s,str,strlen(str),0)==-1){
				perror("Message not sent :(");
				exit(1);
			}
			str="";
		}
		else{
			if((t=recv(s,str,strlen(str),0))>0){
				str[t]='/0';
				printf("%s\n",str);
			}
			else{
				if(t<0){
					perror("No message recieved\n");
				}
				else{
					printf("Server closed connection :(\n");
				}
			}
		}
	}
	return 0;
}