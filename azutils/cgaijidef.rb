#!/usr/bin/env ruby
require 'optparse'
require 'Qt'

class PngImage < Qt::Image
  def image_text
    s = ""
    height.times {|y|
      width.times {|x|
        s += if (Qt::qRed(pixel(x,y)) < 10) then "#" else "." end
      }
      s += "\n"
    }
    return s
  end
  def valid_size?(sz)
    chk_width = if sz == 8 then 16 else sz end
    if height == sz && width == chk_width then
      true
    else
      false
    end
  end
  
end

class Jis2Uni < Hash
  def initialize(f)
    if !File.exist?(f) then
      puts "not found conversion table. check #{f}"
      exit 0 
    end
    default("0")
    File.readlines(f).each{|line|
      l = line.chomp.split(":")
      self[l[0]] = l[1]
    }
  end
  def unicode(jis)
    u = self[jis]
    l = u.split(",")
    return l[0].hex
  end
end

ebcode = 0xA121
fsize = 16

OptionParser.new {|opt|
  opt.banner = "Output font definition text of EBStudio from image file(.png) \n"
               "Usage: #(File.basename($0) [options] font-image-path"
  opt.on("-e hex_code", "--ebcode hex_code", String,
          "start epwing font code on hex such as 0xA121.\n" +
          " Default is 0xA121"){ |arg|
    ebcode = arg.hex
  }
  opt.on("-p font_pixel_size", "--pixel font_pixel_size", Integer,
          "font size. ex 8(narrow font 8x16),16,24 ...\n" +
          " Default is 16"){ |arg|
    fsize = arg
  }
  opt.on("--help", "print this message and quit."){
    puts opt.help
    exit 0
  }
}.parse!(ARGV)

cnv = Jis2Uni.new(ENV['HOME'] + "/.azutils/jis_uni.txt")
image = PngImage.new
png_files = if ARGV[0] then ARGV[0] + "/*.png" else "*.png" end
reserve_code = 0xE0200


puts '<?xml version="1.0" encoding="Shift_JIS"?>'
puts '<gaijideSet>'

Dir.glob(png_files).sort.each{|f|
  image.load(f)
  if image.valid_size?(fsize) then
    ucode = cnv.unicode(File.basename(f, ".png"))
    if ucode == 0 then
      ucode = reserve_code
      reserve_code += 1
    end
    ustr = "%X" % ucode
    estr = "%X" % ebcode
    puts '<gaijiMap unicode="#x' + ustr + '" ebcode="' + estr + '"/>'
    ebcode += 1
  end
}

puts '</gaijiSet>'
