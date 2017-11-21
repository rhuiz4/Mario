
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    
    int READ = 0;
    int WRITE = 1;
    int pipe0[2];
    int pipe1[2];
    int kid;
    
    pipe(pipe0);
    pipe(pipe1);
    
    kid = fork();
    
    if(!kid) { //child
        
        printf("child: Lemme see...\n");
        close(pipe0[READ]);
        close(pipe1[WRITE]);
        
        int num;
        read(pipe1[READ], &num, sizeof(num));
        printf("child: Did you say %d + 10?\n", num);
        num += 10;
        
        printf("child: Oh I know! it's %d!\n", num);
        write(pipe0[WRITE], &num, sizeof(num));
        
    }
    
    else{ //parent
    
        printf("parent: Yo kid, I have a question.\n");
        close(pipe0[WRITE]);
        close(pipe1[READ]);
       
        int num = 9;
        printf("parent: Whats %d + 10\n", num);
        write(pipe1[WRITE], &num, sizeof(num));
        
        read(pipe0[READ], &num, sizeof(num));
        printf("parent: Lets see. You said %d? No, it's 21, stoopid!\n", num);
        
    }
    
}
