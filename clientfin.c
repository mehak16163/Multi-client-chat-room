#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>

int main(int argc, char const *argv[])
{
	FILE *fp;
	char current[1000];
	getcwd(current, sizeof(current));
	printf("Select an option: \n1. Sign up\n2. Login");
	char *user_name;
	char *user;
	scanf("%s", user_name);
	char *option;
	option = user_name;
	if(strcmp(option, "1")==0)
	{
		printf("Please enter your username: \n");
		scanf("%s", &user_name);
		user = user_name;
		strcat(current, "users.txt");
		fp = fopen(current, 'a');
		fprintf(fp, user_name);
		fclose(fp);
		return 0;
	}
	else
	{
		printf("Please enter your username: \n");
		scanf("%s", &user_name);
		user = user_name;
	}
	printf("Select an option: \n1. Connect to server\n2. Exit");
	char *option_2;
	scanf("%s", user_name);
	option_2 = user_name;
	if(strcmp(option_2, "1")==0)
	{
		char cwd[1024];
		getcwd(cwd , sizeof(cwd));
		char *name  = user;
		strcat(cwd, name);
		int s, len, t;
		struct sockaddr_un remote;
		char str[5000];
		char *txt;
		if ((s=socket(AF_UNIX,SOCK_STREAM,0))==-1){
			perror("Error in creating chat client :(");
			exit(1);
		}
		printf("Trying to connect...\n");
		remote.sun_family = AF_UNIX;
		strcpy(remote.sun_path, cwd);
		len = strlen(remote.sun_path) + sizeof(remote.sun_family);
		if (connect(s,(struct sockaddr *)&remote,len)==-1){
			perror("Client unable to connect to server :(");
			exit(1);
		}

		printf("%s is connected to the server.\n", user);

		while(1){
			printf("Select Option:\n1. Read\n2.Write\n3.Exit");
			scanf("%s", user_name);
			char *option = user_name;
			if (option.strcmp("3") == 0)
			{		
					close(s);
					break;
			}
			else if(option.strcmp("2") == 0){
				printf("Enter message\n");
				scanf("%s", user_name);
				char *msg = user_name;
				printf("Enter id of recipients\n");
				scanf("%s", user_name);
				strcat(str,id);
				strcat(str,"$");
				strcat(str,msg);
				strcat(str,"$");
				strcat(str,user_name);
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
	else
	{
		return 0;
	}
	return 0;
}