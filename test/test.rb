require "minitest/autorun"
require "BitmapPlusPlus"

class BitmapPlusPlusTest < Minitest::Test
    def test_it
        assert_equal 6,
            BitmapPlusPlus.hitest( 5)
    end
end