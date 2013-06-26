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

ebcode = 0xA121
fsize = 16

OptionParser.new {|opt|
  opt.banner = "Output GAIJI(font) text of EBStudio from image file(.png) \n"
               "Usage: #(File.basename($0) [options] font-image-path"
  opt.on("-e hex_code", "--ebcode hex_code", String,
          "start epwing font code on hex such as 0xA121.\n" +
          " Default is 0xA121"){ |arg|
    ebcode = arg.hex
  }
  opt.on("-p font_pixel_size", "--pixel font_pixel_size", Integer,
          "font pixel size. ex 8(narrow font 8x16), 16, 24 ...\n" +
          " Default is 16"){ |arg|
    fsize = arg
  }
  opt.on("--help", "print this message and quit."){
    puts opt.help
    exit 0
  }
}.parse!(ARGV)

png_files = if ARGV[0] then ARGV[0] + "/*.png" else "*.png" end

image = PngImage.new




puts '<?xml version="1.0" encoding="Shift_JIS"?>'
puts '<gaijiData xml:space="preserve">'
s = if fsize == 8 then "8X16" else fsize.to_s + "X" + fsize.to_s end
puts '<fontSet size="' + s + '" start="' + ("%X" % ebcode) + '">'

Dir.glob(png_files).sort.each{ |f|
  image.load(f)
  if image.valid_size?(fsize) then
    puts '<fontData ebcode="' + ("%X" % ebcode ) + '"/>'
    puts image.image_text
    puts '</fontData>'
    puts ""
    ebcode += 1
  end
}
puts '</fontSet>'
puts '</gaijiData>'


