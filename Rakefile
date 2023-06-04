require 'rake/extensiontask'
require "rake/testtask"

Rake::TestTask.new do |t|
  t.libs << "test"
end

desc "Run tests"

Rake::ExtensionTask.new "BitmapPlusPlus" do |ext|
  ext.lib_dir = "lib/BitmapPlusPlus"
end

task default: :test