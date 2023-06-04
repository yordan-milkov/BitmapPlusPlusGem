#include <ruby.h>
#include "BitmapPlusPlus.hpp"

using namespace std;

// Ruby method bindings for BitmapPlusPlus class
VALUE tRuby(VALUE self, VALUE x) {
  int result = NUM2INT(x) + 1;
  bmp::Pixel pix;
  pix.r = result;
  return INT2NUM(pix.r);
}

// Initialization method for the extension
extern "C" void Init_BitmapPlusPlus() {
  VALUE bitmap_module = rb_define_module("BitmapPlusPlus");

  // Define the bitmap class
  rb_define_singleton_method(bitmap_module, "hitest", RUBY_METHOD_FUNC(tRuby), 1);
}
