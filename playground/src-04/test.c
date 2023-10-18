
int main(int argc, char* argv[])
{
    volatile int x;

    if (__builtin_expect(argc % 2, EXPECT))
    {
        x = 1;
    } 
    else 
    {
        x = 0;
    }

    return x;
}

