#include <stdint.h>
#include <circular.h>

CircularBuffer::CircularBuffer(int size) {
    this->list = new int[size];
    this->in_index = 0;
    this->out_index = 0;
    this->size = size;
    this->free_slots = size;
}
bool CircularBuffer::add(int value)
{
    this->list[this->in_index] = value;
    if (this->free_slots > 0){
        this->free_slots--;
    }
    else{
        this->free_slots = 0;
    }
    if ((this->in_index + 1) == this->size){
        this->in_index = 0;
    }
    else {
        this->in_index++;
    }
    // Contar espacios libres
    if (this->free_slots == 0) {
        this->out_index = this->in_index;
    }
    return true;
}

int CircularBuffer::remove() {
    if (this->free_slots < this->size) {
        int value = this->list[this->out_index];
        if (this->out_index + 1 == this->size) {
            this->out_index = 0;
        }
        else {
            this->out_index++;
        }
        this->free_slots++;
        return value;
    }
    else {
        return -1;
    }
}

int CircularBuffer::inIndex() {
    return this->in_index;
}

int CircularBuffer::outIndex() {
    return this->out_index;
}

int CircularBuffer::freeSlots() {
    return this->free_slots;
}

int CircularBuffer::getValueFromIndex(int index) {
    return this->list[index];
}

float CircularBuffer::mean() {
    int sum = 0;
    uint8_t max_iterator = (this->freeSlots() == 0) ? this->size : this->in_index;
    for(uint8_t i=0; i < max_iterator; i++) {
        sum += this->list[i];
    }
    return float(sum) / max_iterator;
}