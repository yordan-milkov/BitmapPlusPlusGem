require "minitest/autorun"
require "BitmapPlusPlus"
require_relative "../examples/random.rb"

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
end