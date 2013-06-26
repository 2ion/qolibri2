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

idir = "images"
div_conv = true

OptionParser.new {|opt|
  opt.banner = "Usage: #(File.basename($0) [options] font-image-path"
  opt.on("-i image_directory", "--idir image_directory", String,
         "Image directory where you copied all images\n" +
         ' Default is "images') {|arg|
    idir = arg
  }
  #opt.on("-d", "--div_conv", Boolean,
  #       "<div></div> convert <blockquote></blockquote>") {
  #  div_conv = true
  #}
  opt.on("--help", "print this message and quit."){
    puts opt.help
    exit 0
  }
}.parse!(ARGV)

cnv = Jis2Uni.new(ENV['HOME'] + "/.azutils/jis_uni.txt")

text = File.read(ARGV[0])
text.gsub!(/<rp>(.)<\/rp>/i, "")
text.gsub!(/<span>/i,"<i>")
text.gsub!(/<span.+?>/i,"<i>")
text.gsub!(/<\/span>/i,"</i>")
#text.gsub!(/<strong.+?>/i,"<strong>")
#text.gsub!(/<\/strong>/i,"</strong>")
#text.gsub!(/<h1.+?>/i,"<h1>")
#text.gsub!(/<h2.+?>/i,"<h2>")
text.gsub!(/<em.+?>/i,"<em>")
#text.gsub!(/<\/h1>/i,"</h1>")
#text.gsub!(/<\/h2>/i,"</h2>")
text.gsub!(/<\/em>/i,"</em>")
text.gsub!(/<i>/i,"<i>")
text.gsub!(/<\/i>/i,"</i>")
text.gsub!(/<b>/i,"<b>")
text.gsub!(/<\/b>/i,"</b>")
text.gsub!(/<br>/i,"<br>")
text.gsub!(/<br\/>/i,"<br>")
text.gsub!(/<br \/>i/,"<br>")
text.gsub!(/<title>/i,"<title>")
text.gsub!(/<\/title>/i,"</title>")

text.scan(/\d*-\d*-\d*\.png/).each{ |png|
  ent = cnv.entity(png.split(".")[0])
  r = Regexp.new("<img.+?" + png + ".+?>")
  text.gsub!(r,ent)
}

text.scan(/\/.*?\.png/).each{ |png|
  r = Regexp.new("<img.+?" + png + ".+?>")
  text.gsub!(r, '<img src="' + idir + png.split(".")[0] + '.bmp">')
}

if div_conv then
  text.scan(/<div.+?>/).each{ |div|
    text.gsub!(div, "<blockquote>")
  }
  text.gsub!(/<\/div>/,"</blockquote>")
else
  text.scan(/<div.+?>/).each{ |div|
    text.gsub!(div, "<!-- DIV START" + div.sub(/<div/,"").sub(/>/,"") + "-->")
  }
  text.gsub!(/<\/div>/,"<!-- END DIV -->")
end


#title = text.slice(/<title>.*<\/title>/i)
#puts '<html>'
#puts '<head>'
#puts '  <meta http-equiv="Content-Type" content="text/html;charset=Shift_JIS" />'
#puts '  <meta http-equiv="content-style-type" content="text/css" />'
#puts '  ' + title
#puts '</head>'
#print '<body>'
#m = /<body>/.match(text)
#puts m.post_match
puts text

