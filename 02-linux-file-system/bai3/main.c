#include<stdio.h>
#include<time.h>
#include<fcntl.h> 
#include<sys/stat.h>

int main() {
    // Lấy thông tin về tệp tin
    struct stat fileStat;
    if (stat("test.txt", &fileStat) != 0) {
        printf("Error\n");
        return 1;
    }
    // Hiển thị thông tin về tệp tin
    printf("File type: ");
    if (S_ISREG(fileStat.st_mode)) {
        printf("Regular file\n");
    } 
    else if (S_ISDIR(fileStat.st_mode)) {
        printf("Thu muc (Directory)\n");
    } 
    else {
        printf("Unknown\n");
    }
    printf("File name: test.txt\n");
    printf("Last modified time: %s", ctime(&fileStat.st_mtime));
    printf("Size: %ld bytes\n", fileStat.st_size);
    close(fd);
    return 0;
}