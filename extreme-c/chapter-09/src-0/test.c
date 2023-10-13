#include <stdio.h>

typedef struct
{
    int width;
    int length;
} rect_t;

int RectArea(const rect_t* const rect)
{
    return rect->width * rect->length;
}

int main(int argc, char* argv[])
{
    rect_t m_rect;
    m_rect.width = 10;
    m_rect.length = 25;
    int area = RectArea(&m_rect);
    printf("Area: %d\n", area);
    return 0;
}

