#ifndef __STRATEGY_H__
#define __STRATEGY_H__

#include "container.h"
#include "Base.h"
#include <iostream>

class Sort {
    public: 
        /* Constructors */
        Sort() { }

        /* Pure Virtual Functions */
        virtual void sort(Container* container) = 0;
};
class SelectionSort : public Sort {
    
    public:
        SelectionSort();
        
        void sort(Container* container){
            int pos_min;
            int n = container->size();

	        for (int i=0; i < n-1; i++){
	            pos_min = i;//set pos_min to the current index of array
		        for (int j=i+1; j < n; j++){
		            if (container->at(j)->evaluate() < container->at(pos_min)->evaluate()){
                        pos_min=j;
		            }
	
		        }
                if (pos_min != i){
                 container->swap(pos_min, i);
                }
	        }
        }
    
};
class BubbleSort : public Sort{
    
    public:
        BubbleSort();
        void sort(Container* container){
            bool swapped = true;
            int j = 0;
            int tmp;
            while(swapped){
                swapped = false;
                j++;
                for(int i = 0; i < container->size() - j; i++){
                    if(container->at(i)->evaluate() > container->at(i+1)->evaluate()){
                        container->swap(i, i+1);
                        swapped = true;
                   }
                }
            }
            return;
        }
};

#endif // __STRATEGY_H__
