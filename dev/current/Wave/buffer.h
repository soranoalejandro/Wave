#pragma once
//#include <stdint.h>

typedef struct {
  uint8_t len;
  uint8_t start;
  uint8_t end;
  uint8_t last;
} buffer_circular;

typedef struct {
  uint8_t len;
  uint8_t start;
  uint8_t start_page;
  uint8_t end;
  uint8_t end_page;
} buffer_paged;


//  C CIRCULAR BUFFER

//  BY VALUE
#define bufferc_add( data, head, array )  { \
  if ( head.len <= head.last ) { \
    array[ head.end++ ] = data; \
    head.end &= head.last; \
    head.len++; \
  } \
}

#define bufferc_add_n( data, head, array, elements )  { \
  if ( head.len <= head.last ) { \
    array[ head.end++ ] = data; \
    head.end &= head.last; \
    head.len++; \
  } \
}

#define bufferc_get( data, head, array )  { \
  if ( head.len > 0 ) { \
    data = array[ head.start++ ]; \
    head.start &= head.last; \
    head.len--; \
  } \
}

//  BY REFFERENCE
#define bufferc_add_ref( data, head, array )  { \
  if ( head->len <= head->last ) { \
    array[ head->end++ ] = data; \
    head->end &= head->last; \
    head->len++; \
  } \
}

#define bufferc_addn_ref( data, head, array, elements )  { \
  if ( head->len <= head->last ) { \
    array[ head->end++ ] = data; \
    head->end &= head->last; \
    head->len++; \
  } \
}

#define bufferc_get_ref( data, head, array )  { \
  if ( head->len > 0 ) { \
    data = array[ head->start++ ]; \
    head->start &= head->last; \
    head->len--; \
  } \
}

//  PAGED BUFFER
#define bufferp_add( data, head, array )  { \
  if ( head.len <= head.last ) { \
    array[ head.end++ ] = data; \
    head.end &= head.last; \
    head.len++; \
  } \
}

#define bufferp_get( data, head, array )  { \
  if ( head.len > 0 ) { \
    data = array[ head.start++ ]; \
    head.start &= head.last; \
    head.len--; \
  } \
}


