#ifndef CIRCULAR
#define CIRCULAR

class CircularBuffer
{
protected:
    int in_index;
    int out_index;
    int* list;
    int size;
    int free_slots;
public:
    CircularBuffer(){};
    CircularBuffer(int size);
    bool add(int value);
    int remove();
    int inIndex();
    int outIndex();
    int freeSlots();
    int getValueFromIndex(int index);
    float mean();
};
#endif