require "BitmapPlusPlus"

def cehss_boardBM fileName, width, height
    # 8x8 chess board
    image = Bitmap.new(width, height)
    board_dims = 8
    rect_w = image.width / board_dims
    rect_h = image.height / board_dims

    # Iterate over rectangles
    is_white = true
    (0..image.width-1).step(rect_w).each { |x|
        (0..image.height-1).step(rect_h).each { |y|
            color = is_white ? Pixel::WHITE : Pixel::BLACK
            # Fill rect
            for dx in x..x + rect_w-1
                for dy in y..y + rect_h-1
                    image.set(dx, dy, color)
                end
            end
            is_white = !is_white # flip flop
        }
        is_white = !is_white # flip flop
    }

    # Save bitmap to file
    image.save(fileName)
end
