#include <stdio.h>

#define DEBUG 0

#if DEBUG
#include <unistd.h>
#endif

int main(int arc, char **arv)// ./get_xor_check_byte a000010000
{
    if(arc == 1)
    {
        printf("format: %s <data> \n"
                "eg: %s a000010000\n",arv[0], arv[0]);
        return -1;
    }
#if DEBUG
    printf("arv[1] = %s\n",arv[1]);
#endif
    char *p = arv[1];
    char *q = arv[1];
    int num[2] ={0};
    unsigned char check = 0;
    unsigned char LastNum = 0;
    int i = 0;
    do
    {
        LastNum = num[0] * 16 + num[1];//LastNum 比 p 慢一个字节
        check = check ^ LastNum;
#if DEBUG
        printf("p = %c, p + 1 = %c\n",*p, *(p + 1));
        printf("LastNum = %x, check = %x\n",LastNum, check);
#endif
        for(i = 0;i < 2;i++)
        {
            if( (*(p+i) - '0' <= 9) && (*(p+i) - '0' >= 0) )
                num[i] = *(p + i) - '0';
            else if( (*(p + i) - 'A' <= 5) && (*(p + i) - 'A' >= 0) )
                num[i] = *(p + i) - 'A' + 10;
            else if( (*(p + i) - 'a' <= 5) && (*(p + i) - 'a' >= 0) )
                num[i] = *(p + i) - 'a' + 10;
            else
                break;//数据错误
        }

        if(i == 1)
        {
            printf("data erro\n");
            return -1;
        }

        p = p + 2;
#if DEBUG
        usleep(500 * 1000);//500ms
#endif
    }while(i == 2);

    printf("calculate data : ");
    while(q != (p - 2))
    {
        putchar(*q);
        q++;
    }

    printf("\ncheck = %#x\n",check);

	return 0;
}
