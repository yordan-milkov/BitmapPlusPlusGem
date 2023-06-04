require 'rbconfig'
require 'mkmf'
dest_path = mkintpath("D:/ChaosGroup/BitmapPlusPlusGem/lib/BitmapPlusPlus")
RbConfig::MAKEFILE_CONFIG['sitearchdir'] = dest_path
RbConfig::CONFIG['sitearchdir'] = dest_path
RbConfig::MAKEFILE_CONFIG['sitelibdir'] = dest_path
RbConfig::CONFIG['sitelibdir'] = dest_path
