require "minitest/autorun"
require "BitmapPlusPlus"
require_relative "../examples/random.rb"
require_relative "../examples/chess_board.rb"
require_relative "../examples/read_bitmap.rb"

class BitmapPlusPlusTest < Minitest::Test
    def get_results_path
        current_file_path = __FILE__
        current_folder_path = File.dirname(current_file_path)
        new_file_path = File.join(current_folder_path, 'results')
        FileUtils.mkdir_p(new_file_path) unless File.directory?(new_file_path)
        return new_file_path
    end

    def test_random
        randomBM File.join(get_results_path, 'random.bmp'), 512, 512
    end
    def test_chess_board
        cehss_boardBM File.join(get_results_path, 'chess_board.bmp'), 640, 640
    end
    def test_read_bitmap
        read_bitmap get_results_path
    end
end