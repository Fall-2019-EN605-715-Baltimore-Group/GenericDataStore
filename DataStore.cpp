#include "DataStore.h"
#include <Arduino.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

const char ts_csv_elem_example[] = "9999999999, -99.9F,\n";

/*** Private Functions ***/
void DataStore::_attach_data_node(data_store_elem *new_node) {
  data_store_elem *new_ts;
  if (_ll_head == NULL) {
    _ll_head = new_node;
    new_ts = _ll_head;
    // Serial.println("Inserted at head!");
  } else {
    // Traverse to the end of the list
    data_store_elem *curr_node = _ll_head;
    while(curr_node->next != NULL) {
      curr_node = curr_node->next;
    }
    curr_node->next = new_node;
    new_ts = curr_node;
    // Serial.println("Inserted at end of list!");
  }
  _num_elements++;
}

unsigned long long DataStore::_get_csv_file_size(void) {
  return sizeof(ts_csv_elem_example) * _num_elements;
}

void DataStore::_print_elem(data_store_elem *ts) {
  //char *ts_csv = (char*)malloc( sizeof(ts_csv_elem_example) );
  unsigned long time_since_start = ts->time - _ll_head->time;

  Serial.print(time_since_start); Serial.print(", ");
  Serial.print(ts->data); Serial.print(";\n");
}

void DataStore::_free_ll(void) {
  data_store_elem *curr_node = _ll_head;
  while(curr_node != NULL) {
    data_store_elem *next = curr_node->next;
    free(curr_node);
    curr_node = next;
  }
}



/*** Public Functions ***/

DataStore::DataStore(void) {
  _ll_head = NULL;
  _num_elements = 0;
}

DataStore::~DataStore(void) {
  dump_list();
}

bool DataStore::store_data(float new_data, unsigned long new_time) {
  // Create the new node
  data_store_elem *new_ts = (data_store_elem*)malloc(sizeof(data_store_elem));
  if (new_ts == NULL) {
    Serial.println("[store_data] failed to allocate memory for new data_store_elem struct!\n");
    return false;
  }

  // Fill in data
  new_ts->data = new_data;
  new_ts->time = new_time;
  new_ts->next = NULL;

  // Attach the new node
  _attach_data_node(new_ts);
  
  return true;
}

void DataStore::to_csv(void) {
  // Should we use a big char buffer? 
  // Maybe print out after we recieve a special char?

  // Print the expected file size?

  
  // Print out one time,dataerature pair at a time?
  data_store_elem *curr_node = _ll_head;
  while(curr_node != NULL) {
    _print_elem(curr_node);
    curr_node = curr_node->next;
  }
  
}

void DataStore::dump_list(void) {
  _free_ll();
  _ll_head = NULL;
  _num_elements = 0;
}