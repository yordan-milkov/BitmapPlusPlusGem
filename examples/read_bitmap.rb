require "BitmapPlusPlus"

def read_bitmap filePath
    image = Bitmap.new

    #Load penguin.bmp bitmap
    image.load(filePath)

    #Modify loaded image (makes half of the image black)
    for y in 0..image.height()-1 do
        for x in 0..(image.width() / 2 )-1 do
            image.set(x, y, Pixel::BLACK)
        end
    end

    # Save
    new_file_name = "modified-" + File.basename(filePath)
    image.save(File.join(File.dirname(filePath), new_file_name))
end