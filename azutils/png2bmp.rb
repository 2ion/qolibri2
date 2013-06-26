#!/usr/bin/env ruby

require 'Qt'
require 'optparse'

quality = 0
OptionParser.new {|opt|
  opt.banner = "Convert PNG to BMP \n"
               "Usage: #(File.basename($0) [options] font-image-path"
  opt.on("-q value", "--quality value", Integer,
          "quality 0 - 100, 0=Default(Qt System Default)."){ |arg|
    quality = arg
  }
  opt.on("--help", "print this message and quit."){
    puts opt.help
    exit 0
  }
}.parse!(ARGV)

png_files = if ARGV[0] then ARGV[0] + "/*.png" else "*.png" end
image = Qt::Image.new

Dir.glob(png_files).each{|f|
  image.load(f)
  image.save(f.sub(/\.png/, ".bmp"), "BMP", quality)
}

