#include<stdio.h>
#include<signal.h>

void print_sig(sigset_t *p)
{
	int i = 1;
	for(;i < 32;++i){
		if(sigismember(p,i))
			printf("1");
		else
			printf("0");
	}
	printf("\n");
}
int main()
{
	sigset_t s,p,o;
	sigemptyset(&s);
	sigemptyset(&o);
	sigaddset(&s,SIGINT);
	sigprocmask(SIG_SETMASK,&s,&o);
	int count = 0;
	while(1){
		sigemptyset(&p);
		sigpending(&p);
		print_sig(&p);
		sleep(1);
		if(count++ == 5)
			sigprocmask(SIG_SETMASK,&o,NULL);
	}
}
