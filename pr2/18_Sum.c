#include <stdio.h>
#include <assert.h>

int main ()
{
    int N, a, Ans = 0;
    int num = scanf("%d", &N);
    assert(num > 0);

    int i = 1;
    for(i; i <= N; i++)
    {
        num = scanf("%d", &a);
        assert(num > 0);
        
        Ans += a-i;
    }
    printf("%d", Ans);
    return 0;
}