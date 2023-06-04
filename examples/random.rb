require "BitmapPlusPlus"

def randomBM fileName, width, height
    image = Bitmap.new(width, height)
    
    #Assign a random color to each pixel in the image
    image.each{ |pixel|
        pixel.r = rand(256)
        pixel.g = rand(256)
        pixel.b = rand(256)
    }

    # Save bitmap to new file image.bmp
    image.save(fileName);
end