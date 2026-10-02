/******************************************************************************
Detect Big Endian vs Little Endian without library calls
*******************************************************************************/
#include<iostream>

using namespace std;

void DetectEndianNess()
{
    unsigned int num = 1;
    char * ch = (char*)&num;
    if(*ch) cout << "Little Endian";
    else cout << "Big Endian";
}

int main()
{
    DetectEndianNess();
    return 0;
}

/*
// Withoug pinter casting
union {
    uint32_t value;
    uint8_t byte;
} data;

daata.value = 1;
q
if (data.byte == 1)
    // little endian

*/


/*
With structure:
// Find endianess

#include<iostream>

using namespace std;

struct ele {
    unsigned char ch1,ch2,ch3,ch4;
};


int main() {
    int a = 1;
    struct ele *obj  = (struct ele*)&a;
    if(obj->ch1) cout << "Little Endian\n";
    else cout <<"Big Endian\n";
    return 0;
}

*/
