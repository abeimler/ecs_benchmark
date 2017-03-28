#ifndef _IMMUTBAG_H
#define _IMMUTBAG_H

#include <cstddef>

namespace artemis {
  template<typename E>
  class ImmutableBag {
  public:
    virtual E get(int index) = 0;
    virtual int getCapacity() = 0;
    virtual int getCount() = 0;
    virtual bool isEmpty() = 0;
    virtual ~ImmutableBag(){};
  };
  
  template<typename E>
  
  
  class Bag : public ImmutableBag<E> {
    
    
  public:
    Bag() {
      init(20);
    };
    
    
    Bag(int capacity) {
      init(capacity);
    };
    
    /**
     *  If set is used, the bag might
     *  contain gaps between indexes. Use this to get a
     *  complete bag. No changes will be made to the original bag.
     */
    Bag<E> * getGapless(){
      
      Bag<E> * bag = new Bag<E>(this->count);
      //int c = 0;
      
      for(int i=0; i < this->size; i++)
      {
        if(this->data[i] != NULL){
          bag->add(data[i]);
        }
      }
      
      return bag;
      
    }
    
    /**
     * Adds an object to the bag.
     * Mixing add and set is not encouraged.
     * Note: set can create gaps between indexes where
     * the object count is irrelevant to the order.
     *
     * Autmatically grows the bag if necessary.
     *
     * @param o The object to be added.
     **/
    void add(E o) {
      if(size == count)grow();
      
      data[count++] = o;
    };
    
    void addAll(Bag<E> & bag) {
      
      for(int i=0; i < bag.size ; i++) {
        add(bag.data[i]);
      }
    };
    
    /**
     * Sets every pointer to NULLs. Does not delete data.
     */
    void clear() {
      for(int i=0; i<size; i++) {
        data[i] = NULL;
      }
      
      count = 0;
      
    };
    
    bool contains(E o) {
      
      for(int i=0; i<count; i++)
        if(o == data[i])
          return true;
      
      return false;
    };
    
    virtual E get(int index) {
      if (index >= size) return NULL;
      return (E)data[index];
    };
    
    virtual int getCapacity() {return size;};
    virtual bool isEmpty() {return count == 0;};
    /**
     * Returns the amount of objects in the bag.
     *
     **/
    virtual int getCount() {return count;};
    
    bool remove(E o) {
      
      for(int i=0; i<count; i++) {
        if(o == data[i]) {
          remove(i);
          return true;
        }
      }
      
      return false;
    };
    
    E remove(int index) {
      if(count == 0) return NULL;
      
      E object = data[index];
      data[index] = data[count-1];
      data[count-1] = NULL;
      count--;
      return (E) object;
    };
    
    bool removeAll(Bag<E> bag) {
      bool mod = false;
      
      for(int i=0; i<bag.count; i++)
        for(int j= 0; j< count ; j++)
          if(bag.data[i] == data[j]) {
            remove(j);
            j--; // ?
            mod = true;
            break;
          }
      
      return mod;
      
    };
    
    
    E removeLast() {
      if(!isEmpty()) {
        E object = data[count-1];
        data[count-1] = NULL;
        --count;
        return (E) object;
      }
      
      return NULL;
    };
    
    
    bool set(int index, E o) {
      
      if(index >= size) grow(index*2);
      
      
      if(o == NULL && data[index] != NULL){
        count--;
      }
      else if(o != NULL && data[index] == NULL){
        count++;
      };
      
      data[index] = o;
      return true;
    };
    
    
    void operator += (Bag<E> &bag) {
      addAll(bag);
    };
    
    
    void deleteData(){
      
      for(int i=0; i<size; i++)
      {
        delete data[i];
        data[i] = NULL;
      }
      count = 0;
    }
    
    virtual ~Bag<E>() {
      delete[] data;
    };
    
    
  private:
    
    int count;
    int size;
    E *data;
    
    void grow() {
      int newCapacity =(size * 3.0f) * 0.5f + 1.0f;
      grow(newCapacity);
    };
    
    void grow(int newCapacity) {
      E* newData = new E[newCapacity];
      
      for (int i = 0; i < size; i++)
        newData[i] = data[i];
      for (int i = size; i < newCapacity; i++)
        newData[i] = NULL;

      delete[] data;

      size = newCapacity;
      data = newData;
    };
    
    void init(int capacity) {
      size = capacity;
      count = 0;
      data = new E[capacity];
      clear();
    }
    
  };
};

#endif // $(Guard token)
