#include <ruby.h>
#include "BitmapPlusPlus.hpp"
using namespace bmp;

// Ruby Pixel class
static VALUE cPixel;

// Ruby Pixel allocate method
static VALUE pixel_allocate(VALUE self) {
    Pixel* pixel = new Pixel();
    return Data_Wrap_Struct(self, NULL, RUBY_DEFAULT_FREE, pixel);
}

// Ruby method to create a new Pixel object
static VALUE pixel_new(VALUE self, VALUE r, VALUE g, VALUE b) {
    Pixel* pixel = new Pixel(NUM2UINT(r), NUM2UINT(g), NUM2UINT(b));
    return Data_Wrap_Struct(self, NULL, free, pixel);
}

// Ruby method to get the red value of a Pixel object
static VALUE pixel_get_r(VALUE self) {
    Pixel* pixel;
    Data_Get_Struct(self, Pixel, pixel);
    return UINT2NUM(pixel->r);
}

// Ruby method to get the green value of a Pixel object
static VALUE pixel_get_g(VALUE self) {
    Pixel* pixel;
    Data_Get_Struct(self, Pixel, pixel);
    return UINT2NUM(pixel->g);
}

// Ruby method to get the blue value of a Pixel object
static VALUE pixel_get_b(VALUE self) {
    Pixel* pixel;
    Data_Get_Struct(self, Pixel, pixel);
    return UINT2NUM(pixel->b);
}

// Ruby method to set the red value of a Pixel object
static VALUE pixel_set_r(VALUE self, VALUE value) {
    Pixel* pixel;
    Data_Get_Struct(self, Pixel, pixel);

    pixel->r = NUM2UINT(value);

    return value;
}

// Ruby method to set the green value of a Pixel object
static VALUE pixel_set_g(VALUE self, VALUE value) {
    Pixel* pixel;
    Data_Get_Struct(self, Pixel, pixel);

    pixel->g = NUM2UINT(value);

    return value;
}

// Ruby method to set the blue value of a Pixel objects
static VALUE pixel_set_b(VALUE self, VALUE value) {
    Pixel* pixel;
    Data_Get_Struct(self, Pixel, pixel);

    pixel->b = NUM2UINT(value);

    return value;
}


// Define the BitmapWrapper struct for Ruby class
typedef struct {
    Bitmap* bitmap = NULL;
} BitmapWrapper;

// Ruby deallocation method for the BitmapWrapper struct
static void bitmap_wrapper_deallocate(BitmapWrapper* bitmap_wrapper) {
    delete bitmap_wrapper->bitmap;
    ruby_xfree(bitmap_wrapper);
}

// Ruby allocation method for the BitmapWrapper struct
static VALUE bitmap_wrapper_allocate(VALUE self) {
    BitmapWrapper* bitmap_wrapper = ALLOC(BitmapWrapper);
    bitmap_wrapper->bitmap = NULL;
    return Data_Wrap_Struct(self, NULL, bitmap_wrapper_deallocate, bitmap_wrapper);
}

// Ruby initialize method for the BitmapWrapper class
static VALUE bitmap_initialize(int argc, VALUE* argv, VALUE self) {
    BitmapWrapper* bitmap_wrapper;
    Data_Get_Struct(self, BitmapWrapper, bitmap_wrapper);

    if (argc == 0) {
        // Empty constructor
        bitmap_wrapper->bitmap = new Bitmap();
    } else if (argc == 1 && rb_type(argv[0]) == T_STRING) {
        // Constructor with file path
        Check_Type(argv[0], T_STRING);
        VALUE rb_file_path = argv[0];
        std::string file(RSTRING_PTR(rb_file_path), RSTRING_LEN(rb_file_path));
        bitmap_wrapper->bitmap = new Bitmap(file);
    } else if (argc == 2 && FIXNUM_P(argv[0]) && FIXNUM_P(argv[1])) {
        // Constructor with dimensions
        int width = NUM2INT(argv[0]);
        int height = NUM2INT(argv[1]);
        bitmap_wrapper->bitmap = new Bitmap(width, height);
    } else {
        rb_raise(rb_eArgError, "Invalid number or types of arguments");
    }

    return self;
}

static VALUE bitmap_width(VALUE self) {
    BitmapWrapper* bitmap_wrapper;
    Data_Get_Struct(self, BitmapWrapper, bitmap_wrapper);
    return INT2NUM(bitmap_wrapper->bitmap->width());
}

static VALUE bitmap_height(VALUE self) {
    BitmapWrapper* bitmap_wrapper;
    Data_Get_Struct(self, BitmapWrapper, bitmap_wrapper);
    return INT2NUM(bitmap_wrapper->bitmap->height());
}

// Ruby method to modify a pixel in a bitmap
static VALUE bitmap_set_pixel(VALUE self, VALUE x, VALUE y, VALUE pixel_obj) {
    BitmapWrapper* bitmap_wrapper;
    Data_Get_Struct(self, BitmapWrapper, bitmap_wrapper);

    Pixel* pixel;
    Data_Get_Struct(pixel_obj, Pixel, pixel);

    bitmap_wrapper->bitmap->set( NUM2INT(x), NUM2INT(y), *pixel );
    return Qnil;
}

static VALUE bitmap_load(VALUE self, VALUE filename) {
    Check_Type(filename, T_STRING);
    std::string file(RSTRING_PTR(filename), RSTRING_LEN(filename));

    BitmapWrapper* bitmap_wrapper;
    Data_Get_Struct(self, BitmapWrapper, bitmap_wrapper);
    bitmap_wrapper->bitmap->load(file);

    return Qnil;
}

// Ruby method to save the bitmap
static VALUE bitmap_save(VALUE self, VALUE filename) {
    BitmapWrapper* bitmap_wrapper;
    Data_Get_Struct(self, BitmapWrapper, bitmap_wrapper);

    Check_Type(filename, T_STRING);
    std::string file(RSTRING_PTR(filename), RSTRING_LEN(filename));
    
    bitmap_wrapper->bitmap->save(file);

    return Qnil;
}

// Ruby method to iterate over the pixels of a bitmap
static VALUE bitmap_each(VALUE self) {
    BitmapWrapper* bitmap_wrapper;
    Data_Get_Struct(self, BitmapWrapper, bitmap_wrapper);

    for ( Pixel& pixel : *(bitmap_wrapper->bitmap) ) {
      rb_yield(Data_Wrap_Struct(cPixel, NULL, NULL, &pixel));
    }

    return Qnil;
}

// Initialize the extension
extern "C" void Init_BitmapPlusPlus() {
    // Define the Pixel class
    cPixel = rb_define_class("Pixel", rb_cObject);
    rb_define_alloc_func(cPixel, pixel_allocate);
    rb_define_method(cPixel, "initialize", pixel_new, 3);
    rb_define_method(cPixel, "r", pixel_get_r, 0);
    rb_define_method(cPixel, "g", pixel_get_g, 0);
    rb_define_method(cPixel, "b", pixel_get_b, 0);
    rb_define_method(cPixel, "r=", pixel_set_r, 1);
    rb_define_method(cPixel, "g=", pixel_set_g, 1);
    rb_define_method(cPixel, "b=", pixel_set_b, 1);

    VALUE rb_white_pixel = Data_Wrap_Struct(cPixel, NULL, NULL, const_cast<Pixel*>(&White));
    rb_define_const(cPixel, "WHITE", rb_white_pixel);
    VALUE rb_black_pixel = Data_Wrap_Struct(cPixel, NULL, NULL, const_cast<Pixel*>(&Black));
    rb_define_const(cPixel, "BLACK", rb_black_pixel);
    VALUE rb_red_pixel = Data_Wrap_Struct(cPixel, NULL, NULL, const_cast<Pixel*>(&Red));
    rb_define_const(cPixel, "RED", rb_red_pixel);
    VALUE rb_blue_pixel = Data_Wrap_Struct(cPixel, NULL, NULL, const_cast<Pixel*>(&Blue));
    rb_define_const(cPixel, "BLUE", rb_blue_pixel);
    VALUE rb_green_pixel = Data_Wrap_Struct(cPixel, NULL, NULL, const_cast<Pixel*>(&Green));
    rb_define_const(cPixel, "GREEN", rb_green_pixel);

    // Define the Bitmap class
    VALUE cBitmap = rb_define_class("Bitmap", rb_cObject);
    rb_define_alloc_func(cBitmap, bitmap_wrapper_allocate);
    rb_define_method(cBitmap, "initialize", bitmap_initialize, -1);
    rb_define_method(cBitmap, "width", bitmap_width, 0);
    rb_define_method(cBitmap, "height", bitmap_height, 0);
    rb_define_method(cBitmap, "set", bitmap_set_pixel, 3);
    rb_define_method(cBitmap, "load", bitmap_load, 1);
    rb_define_method(cBitmap, "save", bitmap_save, 1);

    // Include the Enumerable module in the Bitmap class
    rb_include_module(cBitmap, rb_const_get(rb_cObject, rb_intern("Enumerable")));
    rb_define_method(cBitmap, "each", bitmap_each, 0);
}
