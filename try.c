#include <stdio.h>
int main(int argc, char ** argv)
{
    unsigned int a=6;
    int b=-20;
    long long dd=a+b;
    unsigned int ee=a+b;
    char c;
    (a+b>6)?(c=1):(c=0);
    printf("%d %lld %d\n",c,dd,ee);
    return 0;
}
