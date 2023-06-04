require "BitmapPlusPlus"

class Shape
    def initialize(x, y, color)
        @color = color
        @x = x
        @y = y
    end

    def draw(image)
        for dx in 0..image.width-1 do
            for dy in 0..image.height()-1 do
                image.set(dx, dy, @color) if (pixel_in_shape(dx, dy))
            end
        end
    end
    def pixel_in_shape(x, y)
        fail NotImplementedError, "Implement for different shapes"
    end
end

class Rectangle < Shape
    def initialize( x, y, w, h, color )
        super x, y, color
        @width = w
        @height = h
    end

    def pixel_in_shape( x, y) 
        return x >= @x && x <= @x + @width && y >= @y && y <= @y + @height
    end
end

class Triangle < Shape
    def initialize(x1, y1, x2, y2, x3, y3, color )
        super x1, y1, color
        @x2 = x2
        @y2 = y2
        @x3 = x3
        @y3 = y3
    end

    def area(x1, y1, x2, y2, x3, y3 )
        return ((x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / 2.0).abs
    end

    def pixel_in_shape( x, y)
        a0 = area(@x, @y, @x2, @y2, @x3, @y3)
        a1 = area( x,  y, @x2, @y2, @x3, @y3)
        a2 = area(@x, @y,   x,   y, @x3, @y3)
        a3 = area(@x, @y, @x2, @y2,   x,   y)
        return (a0 == a1 + a2 + a3)
    end
end

class Circle < Shape
    def initialize(x, y, radius, color)
        super x, y, color
        @radius = radius
    end

    def pixel_in_shape(x, y)
        return ((x - @x) * (x - @x) + (y - @y) * (y - @y)) <= @radius * @radius;
    end
end

def shapesBM fileName
    image = Bitmap.new(640, 256);
    background_color = Pixel.new(0xaaaab4)
    image.clear(background_color);

    shapes =
    [
        Rectangle.new(20, 20, 180, 180, Pixel.new(0xa31d3a)),
        Triangle.new(310, 20, 230, 200, 400, 200, Pixel.new(0x1a5096)),
        Circle.new(500, 110, 90, Pixel.new(0x228035))    
    ];

    shapes.each { |shape|
        shape.draw(image)
    }
    image.save(fileName);
end