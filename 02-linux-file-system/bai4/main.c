#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include <fcntl.h>


// lệnh seek để di chuyển con trỏ về đầu tệp
// khi dữ liệu vào tệp bằng lệnh write, nó sẽ được ghi vào cuối tệp do cờ 0_APPEND và không phụ thuộc vào vị trí hiện tại của con trỏ tệp
int main(){
    int fd;
    char buf1[] = "haha\n";
    fd = open("test.txt",O_APPEND|O_RDWR);
    if(fd == -1){
        printf("open() test.txt failed\n");
    }
    lseek(fd,0,SEEK_SET);
    int write_byte = write(fd,buf1,sizeof(buf1));
    printf("Write %d bytes to test.txt",write_byte);
    close(fd);
    return 0;
}