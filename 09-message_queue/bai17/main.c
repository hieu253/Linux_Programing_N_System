#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <mqueue.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

#define MQ_MODE (S_IRUSR | S_IWUSR)
#define MQUEUE_NAME "/mqueue"

struct sinhvien
{
    char hoten[50];
    int tuoi;
    char quequan[100];
    char sdt[100];
};
typedef struct sinhvien sinhvien;

struct message
{
    long priority;
    sinhvien data;
};
typedef struct message message;

static void inputdata(message *infor, int msg_id)
{
    mq_receive(msg_id, (char *)infor, sizeof(*infor), NULL);
    printf("Input your data\nInput your ID: ");
    scanf("%ld", &infor->priority);
    getchar();
    printf("Input your name: ");
    fgets(infor->data.hoten, sizeof(infor->data.hoten), stdin);
    printf("Input your age: ");
    scanf("%d", &infor->data.tuoi);
    getchar();
    printf("Input your hometown: ");
    fgets(infor->data.quequan, sizeof(infor->data.quequan), stdin);
    printf("Input your phone number: ");
    fgets(infor->data.sdt, sizeof(infor->data.sdt), stdin);
    mq_send(msg_id, (char *)infor, sizeof(*infor), 0);
}

void showdatabyID(message *infor, int msg_id, long sinhvien_id)
{
    mq_receive(msg_id, (char *)infor, sizeof(*infor), NULL);
    printf("Show all data by id %ld\n", sinhvien_id);
    if (sinhvien_id == infor->priority)
    {
        printf("Student name is: %s", infor->data.hoten);
        printf("Student age is: %d\n", infor->data.tuoi);
        printf("Student hometown is: %s", infor->data.quequan);
        printf("Student phone number is: %s", infor->data.sdt);
    }
    else
    {
        printf("Your id does not match the data ID in the queue!\n");
    }
    mq_send(msg_id, (char *)infor, sizeof(*infor), 0);
}

static void showalldata(message *infor, int msg_id)
{
    mq_receive(msg_id, (char *)infor, sizeof(*infor), NULL);
    printf("Show all list student\n");
    while (mq_receive(msg_id, (char *)infor, sizeof(*infor), NULL) >= 0)
    {
        printf("Stundet ID: %ld\n", infor->priority);
        printf("Student Name: %s", infor->data.hoten);
        printf("Age of student: %d\n", infor->data.tuoi);
        printf("Hometown of student: %s", infor->data.quequan);
        printf("Phone Number: %s", infor->data.sdt);
        printf("-----------------------------------\n");
    }
}

static void deletedata(message *infor, int msg_id, long sinhvien_id)
{
    if (sinhvien_id == infor->priority)
    {
        printf("Deleting data ...\n");
        mq_receive(msg_id, (char *)infor, sizeof(*infor), 0);
        mq_send(msg_id, (char *)infor, sizeof(*infor), 0);
    }
    else
    {
        printf("Your id does not match the data in the queue!\n");
    }
}

int main(int argc, char *argv[])
{
    printf("___________MENU_________\n");
    printf("1.Input data\n");
    printf("2.Show data by ID\n");
    printf("3.Show all data\n");
    printf("4.Delete data\n");
    printf("0.Exit\n");
    message sv;
    int choice;
    long id = 0;
    mqd_t mq_id = mq_open(MQUEUE_NAME, O_RDWR | O_CREAT, MQ_MODE, NULL);
    if (mq_id == -1)
    {
        perror("Can't create queue");
        return -2;
    }
    scanf("%d", &choice);
    do
    {
        switch (choice)
        {
        case 0:
            printf("Exit !!\n");
            exit(1);
        case 1:
            inputdata(&sv, mq_id);
            break;
        case 2:
            printf("Input ID: ");
            scanf("%li", &id);
            showdatabyID(&sv, mq_id, id);
            id = 0;
            break;
        case 3:
            showalldata(&sv, mq_id);
            break;
        case 4:
            printf("Input ID: ");
            scanf("%ld", &id);
            deletedata(&sv, mq_id, id);
            id = 0;
            break;
        default:
            printf("Wrong Choice. Enter again\n");
            break;
        }
        printf("1.Input data\n");
        printf("2.Show data by ID\n");
        printf("3.Show all data\n");
        printf("4.Delete data\n");
        printf("0.Exit !!\n");
        scanf("%d", &choice);
    } while (choice != 0);
    if (mq_close(mq_id) == -1)
    {
        perror("Fail to close message queue!\n");
        return -2;
    }
    if (mq_unlink(MQUEUE_NAME) == -1)
    {
        perror("Fail to unlink message queue!\n");
        return -3;
    }
    return 0;
}