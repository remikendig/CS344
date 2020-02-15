#include <stdlib.h>

#include "dynarray.h"

struct dynarray {
  void** data;
  int size;
  int capacity;
};

/*
*   Function: dynarray_create()
*   Status: DONE
*   Purpose: To create a dynarray of size 0 and capacity 2. Returns a pointer to
*            the structure created.
*   Preconditions: N/A
*   Postconditions: A dynarray is allocated in memory.
*/
struct dynarray* dynarray_create() {
  struct dynarray* array = malloc(sizeof(struct dynarray));
  array->size = 0;
  array->capacity = 2;
  array->data = malloc(array->capacity * sizeof(void*));
  return array;
}

/*
*   Function: dynarray_free()
*   Status: DONE
*   Purpose: To free the memory associated with a dynarray.
*   Preconditions: The dynarray memory has already been allocated.
*   Postconditions: The memory has been freed.
*/
void dynarray_free(struct dynarray* da) {
  free(da->data);
  free(da);
  return;
}

/*
*   Function: dynarray_size()
*   Status: DONE
*   Purpose: A getter function for the size of the dynarray.
*   Preconditions: The dynarray in question exists.
*   Postconditions: N/A
*/
int dynarray_size(struct dynarray* da) {
  return da->size;
}

/*
*   Function: dynarray_insert()
*   Status: DONE
*   Purpose: To insert a new item into a dynamic array. If the item would cause the
*            array to be over the size limit, expands the capacity of the array by
*            2x the current capacity.
*   Preconditions: The array in question exists.
*   Postconditions: The new item has been inserted into the array.
*/
void dynarray_insert(struct dynarray* da, void* val) {
  int i;
  if (da->size == da->capacity) {
    da->capacity = 2 * (da->capacity);
    void** new_data = malloc(da->capacity * sizeof(void*));
    for (i = 0; i < da->size; i++) {
      new_data[i] = da->data[i];
    }
    free(da->data);
    da->data = new_data;
  }
  da->size++;
  da->data[da->size - 1] = val;
  return;
}

/*
*   Function: dynarray_remove()
*   Status: DONE
*   Purpose: To remove an item from the dynamic array. Once an item is
*            removed, shifts all items following it down by one index,
*            and decrements the size by 1.
*   Preconditions: The array in question exists; idx is within the bounds
*                  of the size of the array. Does not check either condition.
*   Postconditions: The item in the array has been removed.
*/
void dynarray_remove(struct dynarray* da, int idx) {
  int i;
  for (i = idx; i < (da->size - 1); i++) {
    da->data[i] = da->data[i + 1];
  }
  da->data[da->size] = NULL;
  da->size--;
  return;
}

/*
*   Function: dynarray_get()
*   Status: DONE
*   Purpose: To return the element of the specified index. Essentially
*            a getter.
*   Preconditions: The arary exists; idx is within the bounds of the size.
*                  Does not check either condition.
*   Postconditions: N/A
*/
void* dynarray_get(struct dynarray* da, int idx) {
  return da->data[idx];
}

/*
*   Function: dynarray_set()
*   Status: DONE
*   Purpose: To set the value at the given index to a certain index.
*            Does not insert new elements.
*   Preconditions: The array exists; idx is within the size.
*   Postconditions: The element at idx is now val.
*/
void dynarray_set(struct dynarray* da, int idx, void* val) {
  da->data[idx] = val;
  return;
}
