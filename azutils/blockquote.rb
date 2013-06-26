#!/usr/bin/env ruby
require 'optparse'

def_indent = true
blk_indent = 2

OptionParser.new {|opt|
  opt.banner = "Usage: #(File.basename($0) [options] conv-file"
  opt.on("-d", "--defindent", "default indent") {
    def_indent = true
  }
  opt.on("-b", "--blkindent", Integer,
         "default block indent") { |arg|
    blk_indent = arg
  }
  opt.on("--help", "print this message and quit."){
    puts opt.help
    exit 0
  }
}.parse!(ARGV)

text = File.read(ARGV[0])

text.gsub!(/(\r\n){2,}/, "\r\n")
text.gsub!(/<br>\r\n(　){1,}/, "<br>\r\n")
if def_indent then
  text.gsub!("<br>\r\n", "<br>\r\n　")
  text.gsub!("<br>\r\n　「", "<br>\r\n「")
  text.gsub!(/<br>\r\n(　){1,}<br>/, "<br>\r\n<br>")
end
text.gsub!(/(　){1,}<h/, "<h")
text.gsub!(/(　){1,}<block/, "<block")

spaces = ""
blk_indent.times { spaces += "　" }

text.scan(/<blockquote>.*?<\/blockquote>/m).each{ |div|
  #puts div
  cnv = div.dup
  cnv.gsub!(/<blockquote>(　){1,}/, "<blockquote>")
  cnv.gsub!(/<blockquote>/, "<blockquote>" + spaces)
  cnv.gsub!(/<br>\r\n(　){1,}/, "<br>\r\n")
  cnv.gsub!(/<br>\r\n/, "<br>\r\n" + spaces)
  cnv.gsub!(/<br>\r\n(　){1,}<br>/, "<br>\r\n<br>")
  cnv.gsub!(/<br>\r\n(　){1,}<\/blockquote>/, "<br>\r\n<\/blockquote>")
  text.gsub!(div, cnv)
}

puts text