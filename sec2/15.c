#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
// #include <string.h>
#include <stdlib.h>
// #include <stdio.h>

int main(){
    char *src_prompt = "please specify source file name:\n";
    // size_t len_src_prompt = strlen(src_prompt);
    write(1,src_prompt, 33);
    char src_name[100];
    int src_len = read(0,src_name,100);
    src_name[src_len-1] = '\0';


    char *dst_prompt = "please specify destination file name:\n";
    // size_t len_dst_prompt = strlen(dst_prompt);
    write(1,dst_prompt, 38);
    char dst_name[100];
    int dst_len = read(0,dst_name,100);
    dst_name[dst_len-1] = '\0';

    int src_fd = open(src_name,O_RDONLY);
    int dst_fd = open(dst_name,O_CREAT|O_RDWR|O_TRUNC|O_EXCL,0777);
    if(src_fd == -1){
        write(1,"no such files\n", 14);
        exit(1);
    }

    char content[10];
    ssize_t bites_read;
    while((bites_read = read(src_fd,content,10)) > 0){

        write(dst_fd,content,bites_read);
        // write(1,content,bites_read);
        // printf("%d\n",bites_read);
    }
    if(bites_read < 0){
        write(1,"error reading file\n",19);
        exit(1);
    }
    close(src_fd);
    close(dst_fd);

    return 0;
}

