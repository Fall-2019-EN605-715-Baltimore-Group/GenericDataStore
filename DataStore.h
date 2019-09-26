#ifndef data_STORE_H_
#define data_STORE_H_

#include <stdlib.h>
#include <stdint.h>

/*
 * dataerature "Storage" and "Transmit" Lib
 */
typedef struct data_store_elem {
  float data; // Expects a single decimal place of precision in farenheight  
  unsigned long time;
  data_store_elem *next;
} _data_store_elem;

class DataStore {
  public:
    DataStore(void);
    ~DataStore(void);
    bool store_data (float new_data, unsigned long new_time);
    void to_csv(void);
    void dump_list(void);
    
  private:
    data_store_elem *_ll_head;
    unsigned long _num_elements;
    void _attach_data_node(data_store_elem *new_node);
    unsigned long long _get_csv_file_size(void);
    void _print_elem(data_store_elem *ts);
    void _free_ll(void);
};



#endif /* data_STORE_CSV_H_ */