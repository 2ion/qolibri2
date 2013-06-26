#!/usr/bin/env ruby
require 'optparse'

OptionParser.new {|opt|
  opt.banner = "Usage: #(File.basename($0) [options] conv-file"
  #opt.on("-d", "--div_conv", Boolean,
  #       "<div></div> convert <blockquote></blockquote>") {
  #  div_conv = true
  #}
  opt.on("--help", "print this message and quit."){
    puts opt.help
    exit 0
  }
}.parse!(ARGV)

hs = ["", "",  "", "", ""]
first = true

File.readlines(ARGV[0]).each{|line|
  if /<h1>.+?<\/h1>/i =~ line then
    if !first then
      puts "</p>"
      first = false
    end
    puts line
    s = line.chomp.sub("<h1>","").sub("<\/h1>","")
    hs[0] = s
    puts '<key type="ğŒ">book_title</key>'
    puts '<key type="ğŒ">' + s + '</key>'
    puts "<p>"
    next
  end
  if /<h2>.+?<\/h2>/i =~ line then
    puts "</p>"
    puts line
    s = line.chomp.sub("<h2>","").sub("<\/h2>","")
    hs[1] = s
    puts '<key type="ğŒ">book_title</key>'
    puts '<key type="ğŒ">' + hs[0] + '</key>'
    puts '<key type="ğŒ">' + s + '</key>'
    puts "<p>"
    next
  end
  if /<h3>.+?<\/h3>/i =~ line then
    puts "</p>"
    puts line
    s = line.chomp.sub("<h3>","").sub("<\/h3>","")
    hs[2] = s
    puts '<key type="ğŒ">book_title</key>'
    puts '<key type="ğŒ">' + hs[0] + '</key>'
    puts '<key type="ğŒ">' + hs[1] + '</key>'
    puts '<key type="ğŒ">' + s + '</key>'
    puts "<p>"
    next
  end
  if /<h4>.+?<\/h4>/i =~ line then
    puts "</p>"
    puts line
    s = line.chomp.sub("<h4>","").sub("<\/h4>","")
    hs[3] = s
    puts '<key type="ğŒ">book_title</key>'
    puts '<key type="ğŒ">' + hs[0] + '</key>'
    puts '<key type="ğŒ">' + hs[1] + '</key>'
    puts '<key type="ğŒ">' + hs[2] + '</key>'
    puts '<key type="ğŒ">' + s + '</key>'
    puts "<p>"
    next
  end
  if /<h5>.+?<\/h5>/i =~ line then
    puts "</p>"
    puts line
    s = line.chomp.sub("<h5>","").sub("<\/h5>","")
    hs[4] = s
    puts '<key type="ğŒ">book_title</key>'
    puts '<key type="ğŒ">' + hs[0] + '</key>'
    puts '<key type="ğŒ">' + hs[1] + '</key>'
    puts '<key type="ğŒ">' + hs[2] + '</key>'
    puts '<key type="ğŒ">' + hs[3] + '</key>'
    puts '<key type="ğŒ">' + s + '</key>'
    puts "<p>"
    next
  end
  puts line
    
}


