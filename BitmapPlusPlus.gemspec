Gem::Specification.new do |spec|
  spec.name          = "BitmapPlusPlus"
  spec.version       = "0.9.0"
  spec.authors       = ["Yordan Kostadinov"]
  spec.email         = 'yordan.milkov.kostadinov@gmail.com'
  spec.summary       = "BitmapPlusPlus library binding gem"
  spec.description   = "A Ruby gem for using library for working with bitmaps."
  spec.licenses      = ['Nonstandard']
  spec.homepage    = 'https://github.com/yordan-milkov/BitmapPlusPlusGem'

  spec.files         = ["lib/BitmapPlusPlus.rb","ext/BitmapPlusPlus/BitmapPlusPlus.cpp","ext/BitmapPlusPlus/BitmapPlusPlus.hpp"]
  spec.extensions    = %w[ext/BitmapPlusPlus/extconf.rb]
end
