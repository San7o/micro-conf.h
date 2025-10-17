// SPDX-License-Identifier: MIT
// Author:  Giovanni Santini
// Mail:    giovanni.santini@proton.me
// Github:  @San7o

#define MICRO_CONF_IMPLEMENTATION
#include "micro-conf.h"

#include <assert.h>

typedef struct {
  int x;
  int y;
} Vec2;

typedef struct {
  int an_integer;
  float a_float;
  double a_double;
  bool a_bool;
  char a_char;
  char *a_str;
  Vec2 vec;
} MyConf;

int main(void)
{
  MyConf conf;
  // Defaults
  conf.an_integer = 10;
  conf.a_float = 11.0f;
  conf.a_double = 123.123;
  conf.a_bool = true;
  conf.a_char = 'F';
  conf.a_str = "test";
  conf.vec = (Vec2) {
    .x = 1,
    .y = 1,
  };
  
  MicroConf config[] =
    {
      {MICRO_CONF_INT, &conf.an_integer, "an_integer"},
      {MICRO_CONF_FLOAT, &conf.a_float, "a_float"},
      {MICRO_CONF_DOUBLE, &conf.a_double, "a_double"},
      {MICRO_CONF_BOOL, &conf.a_bool, "a_bool"},
      {MICRO_CONF_CHAR, &conf.a_char, "a_char"},
      {MICRO_CONF_STR, &conf.a_str, "a_str"},
      {MICRO_CONF_INT, &conf.vec.x, "vec.x"},
      {MICRO_CONF_INT, &conf.vec.y, "vec.y"},
    };
  size_t num_conf = sizeof(config) / sizeof(config[0]);
  
  int err = micro_conf_parse(config, num_conf, "micro.conf");
  if (err != MICRO_CONF_OK) return -err;

  assert(conf.an_integer == 69);
  assert(conf.a_float == 420.1f);
  assert(conf.a_double == 78.78);
  assert(conf.a_char == 'f');
  assert(strcmp(conf.a_str, "here is a string") == 0);
  assert(conf.vec.x == 500);
  assert(conf.vec.y == 200);

  free(conf.a_str);
  return 0;
}
