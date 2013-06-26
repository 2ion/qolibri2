#!/usr/bin/env ruby
require 'optparse'

class Jis2Uni < Hash
  def initialize(f)
    if !File.exist?(f) then
      puts "not found conversion table. check #{f}"
      exit 0
    end
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
  def entity(jis)
    u = self[jis]
    l = u.split(",")
    if l.length > 1
      u2 = l[1].split("+")
      return "&#x" + u2[0] + ";&#x" + u2[1] + ";"
    else
      return "&#x" + u + ";"
    end
  end
end

ebcode = 0xA121

OptionParser.new {|opt|
  opt.banner = "Output font definition text of EBStudio from image file(.png) \n"
               "Usage: #(File.basename($0) [options] font-image-path"
  opt.on("-e hex_code", "--ebcode hex_code", String,
          "start epwing font code on hex such as 0xA121.\n" +
          " Default is 0xA121"){ |arg|
    ebcode = arg.hex
  }
  opt.on("--help", "print this message and quit."){
    puts opt.help
    exit 0
  }
}.parse!(ARGV)

cnv = Jis2Uni.new(ENV['HOME'] + "/.azutils/jis_uni.txt")
png_files = if ARGV[0] then ARGV[0] + "/*.png" else "*.png" end


puts '<html>'
puts '<head>'
puts '  <meta http-equiv="Content-Type" content="text/html;charset=utf-8" />'
puts '  <meta http-equiv="content-style-type" content="text/css" />'
puts '  <title>External Font Information</title>'
puts '</head>'
puts '<body>'
puts '<p>'
puts '<table>'
puts '<tr>'
puts '<th>Font</th><th>epwing</th><th>unicode</th><th>shift-jis</th>'
puts '</tr>'

cnv = Jis2Uni.new(ENV['HOME'] + "/.azutils/jis_uni.txt")

Dir.glob(png_files).sort.each{|fl|
  scode = File.basename(fl, ".png")
  estr = "%X" % ebcode
  hstr = cnv.entity(scode)
  xstr = hstr.gsub("&","&amp;");

  puts '<tr>'
  puts '<td>' + hstr + '</td><td>' + estr + '</th><td>' + xstr +
       '</td><td>' + scode + '</td>'
  puts '</tr>'
  ebcode = ebcode + 1
}

puts '</table>'
puts '</p>'
puts '</body>'
puts '</html>'

