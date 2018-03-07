#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include<sys/types.h>
#include<sys/un.h>
#include <unistd.h>
int main(){
	char cwd[1024];
	char txt[5000];
	getcwd(cwd , sizeof(cwd));
	int s ,len,t,s2;
	char *name  = "server.txt";
	strcat(cwd,name);
	struct sockaddr_un local, remote;
	if((s=socket(AF_UNIX,SOCK_STREAM,0))==-1){
		perror("Error in creating chat server :(");
		exit(1);
	}
	local.sun_family = AF_UNIX;
	strcpy(local.sun_path,cwd);
	unlink(local.sun_path);
	len = strlen(local.sun_path)+sizeof(local.sun_family);
	if (bind(s,(struct sockaddr *)&local,len)==-1){
		perror("Server unable to bind :(");
		exit(1);
	}
	printf("Server successfully binded\n");
	if (listen(s,5)==-1){
		perror("Server not able to listen :((");
		exit(1);
	}
	int client[10]; 
	char* client_name[10];
	int count=0;
	while(1){
		int done ,n ;
		printf("Waiting for a connection...\n");
		t = sizeof(remote);
		if((s2=accept(s,(struct sockaddr *)&remote,&t))==-1){
			perror("Unable to accept connections :(");
			exit(1);
		}
		else{
			client[count]=s2;
			count++;
			recv
		}
		printf("Connected to client %d\n",s2 );
		if(revc(s2,txt,5000,0)<0){
			perror("Unable to recieve first block from client");
			exit(1);
		}
		
	}

}