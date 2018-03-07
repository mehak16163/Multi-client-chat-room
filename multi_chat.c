#include<stdio.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<string.h>
#include <stdlib.h>
struct msg_buf{
	long msg_type;
	char msg_text[1000];
} info;

int main(){
	printf("Enter your id: ");
	char *s;
	scanf("%s",s);
	char *my_id = s;
	while(true){
		printf("Select Option:\n1. Read\n2.Write\n3.Exit");
		scanf("%s",s);
		char *option = s;
		if (option.strcmp("3") == 0)
		{
			break;
		}
		else{
			printf("Enter chat id: ");
			scanf("%s",s);
			char *dummy;
			const char *chat_id = (const char *)s;
			long cid = strtol(chat_id ,&dummy , 10 );
			if (option.strcmp("1") == 0){
				key_t key;
				int msgid;
				key = ftok("/home/mehak/Desktop/Semester-4/Operating Systems/HW/HW-2/chat", 'b');
				msgid = msgget(key, 0666 | IPC_CREAT);
				msgrcv(msgid, &info, sizeof(info),cid , 0);
				printf("Message is: %s\n", info.msg_text);
				msgctl(msgid, IPC_RMID, NULL);
			}
		}
	}
}