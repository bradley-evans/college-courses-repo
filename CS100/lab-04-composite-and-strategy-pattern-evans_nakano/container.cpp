#include "container.h"
#include "strategy.h"

ListContainer::ListContainer() {

    sz = 0;
   // sort_function = new SelectionSort();
    
}

void ListContainer::sort() {

    sort_function->sort(this); // seems like this would be the way to pass this object into sort as a parameter?
                                // that's where I'm not too sure 
                                        
        
}

void VectorContainer::sort() {
    sort_function->sort(this);
}